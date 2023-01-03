/*
 * Copyright (c) 2023 EdgeImpulse Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an "AS
 * IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language
 * governing permissions and limitations under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "model-parameters/model_metadata.h"
#if defined(EI_CLASSIFIER_SENSOR) && (EI_CLASSIFIER_SENSOR == EI_CLASSIFIER_SENSOR_CAMERA)
#include "edge-impulse-sdk/classifier/ei_run_classifier.h"
#include "edge-impulse-sdk/dsp/image/image.hpp"
#include "firmware-sdk/jpeg/encode_as_jpg.h"
#include "firmware-sdk/ei_camera_interface.h"
#include "ei_run_impulse.h"
#include "ei_camera_ov2640.h"
#include <cstdio>

#define DWORD_ALIGN_PTR(a)   ((a & 0x3) ?(((uintptr_t)a + 0x4) & ~(uintptr_t)0x3) : a)

typedef enum {
    INFERENCE_STOPPED,
    INFERENCE_WAITING,
    INFERENCE_SAMPLING,
    INFERENCE_DATA_READY
} inference_state_t;

static inference_state_t state = INFERENCE_STOPPED;
static uint64_t last_inference_ts = 0;
static bool debug_mode = false;
static bool continuous_mode = false;
static uint8_t *snapshot_buf = nullptr;
static uint32_t snapshot_buf_size;
static ei_device_snapshot_resolutions_t snapshot_resolution;
static bool resize_required = false;
static bool crop_required = false;
static uint32_t inference_delay;

static int ei_camera_get_data(size_t offset, size_t length, float *out_ptr)
{
    // we already have a RGB888 buffer, so recalculate offset into pixel index
    size_t pixel_ix = offset * 3;
    size_t pixels_left = length;
    size_t out_ptr_ix = 0;

    while (pixels_left != 0) {
        out_ptr[out_ptr_ix] = (snapshot_buf[pixel_ix] << 16) + (snapshot_buf[pixel_ix + 1] << 8) + snapshot_buf[pixel_ix + 2];

        // go to the next pixel
        out_ptr_ix++;
        pixel_ix+=3;
        pixels_left--;
    }

    // and done!
    return 0;
}

void ei_run_impulse(void)
{
    switch(state) {
        case INFERENCE_STOPPED:
            // nothing to do
            return;
        case INFERENCE_WAITING:
            if(ei_read_timer_ms() < (last_inference_ts + inference_delay)) {
                return;
            }
            state = INFERENCE_DATA_READY;
            break;
        case INFERENCE_SAMPLING:
        case INFERENCE_DATA_READY:
            if(continuous_mode == true) {
                state = INFERENCE_WAITING;
            }
            break;
        default:
            break;
    }

    int res;
    EiCameraOV2640 *cam = static_cast<EiCameraOV2640*>(EiCameraOV2640::get_camera());
 
    ei_printf("Taking photo...\n");

    if(cam->ei_camera_capture_rgb888_packed_big_endian(snapshot_buf, snapshot_buf_size) == false) {
        ei_printf("ERR: Failed to take a snapshot!\n");
        return;
    }

    if (resize_required || crop_required) {
        ei::image::processing::crop_and_interpolate_rgb888(
            snapshot_buf,
            snapshot_resolution.width,
            snapshot_resolution.height,
            snapshot_buf,
            EI_CLASSIFIER_INPUT_WIDTH,
            EI_CLASSIFIER_INPUT_HEIGHT); // bytes per pixel
    }

    ei::signal_t signal;
    signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;
    signal.get_data = &ei_camera_get_data;

    // print and discard JPEG buffer before inference to free some memory
    if (debug_mode) {
        ei_printf("Begin output\n");
        ei_printf("Framebuffer: ");
        int ret = encode_rgb888_signal_as_jpg_and_output_base64(&signal, EI_CLASSIFIER_INPUT_WIDTH, EI_CLASSIFIER_INPUT_HEIGHT);
        ei_printf("\r\n");
        if(ret != 0) {
            ei_printf("ERR: Failed to encode frame as JPEG (%d)\n", ret);
        }
    }

    // run the impulse: DSP, neural network and the Anomaly algorithm
    ei_impulse_result_t result = { 0 };

    EI_IMPULSE_ERROR ei_error = run_classifier(&signal, &result, false);
    if (ei_error != EI_IMPULSE_OK) {
        ei_printf("ERR: Failed to run impulse (%d)\n", ei_error);
        return;
    }

    // print the predictions
    ei_printf("Predictions (DSP: %d ms., Classification: %d ms., Anomaly: %d ms.): \n",
                result.timing.dsp, result.timing.classification, result.timing.anomaly);
#if EI_CLASSIFIER_OBJECT_DETECTION == 1
    bool bb_found = result.bounding_boxes[0].value > 0;
    for (size_t ix = 0; ix < result.bounding_boxes_count; ix++) {
        auto bb = result.bounding_boxes[ix];
        if (bb.value == 0) {
            continue;
        }
        ei_printf("    %s (", bb.label);
        ei_printf_float(bb.value);
        ei_printf(") [ x: %u, y: %u, width: %u, height: %u ]\n", bb.x, bb.y, bb.width, bb.height);
    }
    if (!bb_found) {
        ei_printf("    No objects found\n");
    }
#else
    for (size_t ix = 0; ix < EI_CLASSIFIER_LABEL_COUNT; ix++) {
        ei_printf("    %s: %.5f\n", result.classification[ix].label,
                                    result.classification[ix].value);
    }

#if EI_CLASSIFIER_HAS_ANOMALY == 1
        ei_printf("    anomaly score: %.3f\n", result.anomaly);
#endif
#endif

    if (debug_mode) {
        ei_printf("End output\n");
    }

    if(continuous_mode == false) {
        ei_printf("Starting inferencing in %d seconds...\n", inference_delay / 1000);
    }
}

void ei_start_impulse(bool continuous, bool debug, bool use_max_uart_speed)
{
    EiCameraOV2640 *cam = static_cast<EiCameraOV2640*>(EiCameraOV2640::get_camera());

    debug_mode = debug;
    continuous_mode = continuous;

    if (cam->is_camera_present() == false) {
        ei_printf("ERR: Failed to start inference, camera is missing!\n");
        return;
    }

    snapshot_resolution = cam->search_resolution(EI_CLASSIFIER_INPUT_WIDTH, EI_CLASSIFIER_INPUT_HEIGHT);
    if(cam->set_resolution(snapshot_resolution) == false) {
        ei_printf("ERR: Failed to set snapshot resolution (%ux%u)!\n", EI_CLASSIFIER_INPUT_WIDTH, EI_CLASSIFIER_INPUT_HEIGHT);
        return;
    }

    if(snapshot_resolution.width > EI_CLASSIFIER_INPUT_WIDTH || snapshot_resolution.height > EI_CLASSIFIER_INPUT_HEIGHT) {
        crop_required = true;
        resize_required = false;
    }
    else if(snapshot_resolution.width < EI_CLASSIFIER_INPUT_WIDTH || snapshot_resolution.height < EI_CLASSIFIER_INPUT_HEIGHT) {
        crop_required = false;
        resize_required = true;
    }
    else {
        crop_required = false;
        resize_required = false;
    }

    snapshot_buf_size = snapshot_resolution.width * snapshot_resolution.height * 3;
 
    // if we have to resize, then allocate bigger buffer
    // (resize means camera can't get big enough spanshot)
    if(resize_required) {
        snapshot_buf = (uint8_t*)ei_malloc(EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT * 3);
    }
    else {
        snapshot_buf = (uint8_t*)ei_malloc(snapshot_buf_size);
    }

    // check if allocation was succesful
    if(snapshot_buf == nullptr) {
        ei_printf("ERR: Failed to allocate snapshot buffer!\n");
        return;
    }

    // summary of inferencing settings (from model_metadata.h)
    ei_printf("Inferencing settings:\n");
    ei_printf("\tImage resolution: %dx%d\n", EI_CLASSIFIER_INPUT_WIDTH, EI_CLASSIFIER_INPUT_HEIGHT);
    ei_printf("\tFrame size: %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
    ei_printf("\tNo. of classes: %d\n", sizeof(ei_classifier_inferencing_categories) / sizeof(ei_classifier_inferencing_categories[0]));

    if(continuous_mode == true) {
        inference_delay = 0;
        state = INFERENCE_DATA_READY;
    }
    else {
        inference_delay = 2000;
        state = INFERENCE_WAITING;
        ei_printf("Starting inferencing in %d seconds...\n", inference_delay / 1000);
    }
}

void ei_stop_impulse(void)
{
    state = INFERENCE_STOPPED;
    ei_free(snapshot_buf);
}

bool is_inference_running(void)
{
    return (state != INFERENCE_STOPPED);
}

#endif /* defined(EI_CLASSIFIER_SENSOR) && EI_CLASSIFIER_SENSOR == EI_CLASSIFIER_SENSOR_CAMERA */

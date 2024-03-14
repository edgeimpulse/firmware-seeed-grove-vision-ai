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
#include "firmware-sdk/ei_camera_interface.h"
#include "ei_run_impulse.h"
#include "ei_camera_himax.h"
#include "ei_encode_jpeg.h"
#include <cstdio>
#include <forward_list>

#define DWORD_ALIGN_PTR(a) ((a & 0x3) ? (((uintptr_t)a + 0x4) & ~(uintptr_t)0x3) : a)

typedef enum
{
    INFERENCE_STOPPED,
    INFERENCE_WAITING,
    INFERENCE_SAMPLING,
    INFERENCE_DATA_READY
} inference_state_t;

static inference_state_t state = INFERENCE_STOPPED;
static uint64_t last_inference_ts = 0;
static bool debug_mode = false;
static bool continuous_mode = false;
static float confidence_threshold = 0.5f;
static uint8_t *snapshot_buf = nullptr;
static uint32_t snapshot_buf_size;
static uint32_t inference_delay;

static std::forward_list<object_detection_t> l_obj_det;
static std::forward_list<object_counting_t> l_obj_cnt;

void ei_get_last_framebuf(uint8_t** buf, uint32_t* buf_size)
{
    *buf = snapshot_buf;
    *buf_size = snapshot_buf_size;
}

static int ei_camera_get_data(size_t offset, size_t length, float *out_ptr)
{
    // we already have a RGB888 buffer, so recalculate offset into pixel index
    size_t pixel_ix = offset * 3;
    size_t pixels_left = length;
    size_t out_ptr_ix = 0;

    while (pixels_left != 0)
    {
        out_ptr[out_ptr_ix] = (snapshot_buf[pixel_ix] << 16) + (snapshot_buf[pixel_ix + 1] << 8) + snapshot_buf[pixel_ix + 2];

        // go to the next pixel
        out_ptr_ix++;
        pixel_ix += 3;
        pixels_left--;
    }

    // and done!
    return 0;
}

void ei_run_impulse(void)
{
    switch (state)
    {
    case INFERENCE_STOPPED:
        // nothing to do
        return;
    case INFERENCE_WAITING:
        if (ei_read_timer_ms() < (last_inference_ts + inference_delay))
        {
            return;
        }
        state = INFERENCE_DATA_READY;
        break;
    case INFERENCE_SAMPLING:
    case INFERENCE_DATA_READY:
        if (continuous_mode == true)
        {
            state = INFERENCE_WAITING;
        }
        break;
    default:
        break;
    }

    int res;
    uint32_t jpeg_image_addr;
    uint32_t jpeg_size;
    EiCameraHimax *cam = static_cast<EiCameraHimax *>(EiCameraHimax::get_camera());

    ei_printf("Taking photo...\n");

    if (cam->ei_camera_capture_rgb888_packed_big_endian(snapshot_buf, snapshot_buf_size) == false)
    {
        ei_printf("ERR: Failed to take a snapshot!\n");
        return;
    }

    ei::signal_t signal;
    signal.total_length = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT;
    signal.get_data = &ei_camera_get_data;

    // print and discard JPEG buffer before inference to free some memory
    if (debug_mode)
    {
        ei_printf("Begin output\n");
        ei_printf("Framebuffer: ");
        encode_as_jpeg_send(&signal, EI_CLASSIFIER_INPUT_WIDTH, EI_CLASSIFIER_INPUT_HEIGHT);
        ei_printf("\r\n");
    }

    // run the impulse: DSP, neural network and the Anomaly algorithm
    ei_impulse_result_t result = {0};

    EI_IMPULSE_ERROR ei_error = run_classifier(&signal, &result, false);
    if (ei_error != EI_IMPULSE_OK)
    {
        ei_printf("ERR: Failed to run impulse (%d)\n", ei_error);
        return;
    }

    display_results(&result);

    auto& impulse = *(ei_default_impulse.impulse);

#if EI_CLASSIFIER_OBJECT_DETECTION == 1
    bool bb_found = result.bounding_boxes[0].value > 0;
    l_obj_det.clear();
    l_obj_cnt.clear();
    for (size_t ix = 0; ix < result.bounding_boxes_count; ix++)
    {
        auto bb = result.bounding_boxes[ix];
        if (bb.value <= confidence_threshold)
        {
            continue;
        }
        // convert bounding box to object detection
        object_detection_t obj_det;
        obj_det.x = bb.x;
        obj_det.y = bb.y;
        obj_det.w = bb.width;
        obj_det.h = bb.height;
        obj_det.confidence = bb.value * 100;
        for (int i = 0; i < impulse.label_count; i++)
        {
            if (strcmp(impulse.categories[i], bb.label) == 0)
            {
                obj_det.target = i;
                break;
            }
        }
        l_obj_det.emplace_front(obj_det);
    }
    // count objects
    for (std::forward_list<object_detection_t>::iterator detection_it = l_obj_det.begin(); detection_it != l_obj_det.end(); ++detection_it)
    {
        uint8_t hit = 0;
        for (std::forward_list<object_counting_t>::iterator count_it = l_obj_cnt.begin(); count_it != l_obj_cnt.end(); ++count_it)
        {
            if (count_it->target == detection_it->target)
            {
                hit = 1;
                count_it->count++;
            }
        }
        if (hit == 0)
        {
            object_counting_t obj;
            obj.count = 1;
            l_obj_cnt.emplace_front(obj);
        }
    }
#endif

    if (debug_mode)
    {
        ei_printf("End output\n");
    }

    if (continuous_mode == false)
    {
        ei_printf("Starting inferencing in %d seconds...\n", inference_delay / 1000);
    }
}

void ei_start_impulse(bool continuous, bool debug, bool use_max_uart_speed, float confidence)
{
    EiCameraHimax *cam = static_cast<EiCameraHimax *>(EiCameraHimax::get_camera());

    debug_mode = debug;
    continuous_mode = continuous;
    confidence_threshold = confidence;

    if (cam->is_camera_present() == false)
    {
        ei_printf("ERR: Failed to start inference, camera is missing!\n");
        return;
    }

    if (cam->init(EI_CLASSIFIER_INPUT_WIDTH, EI_CLASSIFIER_INPUT_HEIGHT) == false)
    {
        return;
    }

    snapshot_buf_size = EI_CLASSIFIER_INPUT_WIDTH * EI_CLASSIFIER_INPUT_HEIGHT * 3;

    snapshot_buf = (uint8_t *)ei_malloc(snapshot_buf_size);
    // check if allocation was succesful
    if (snapshot_buf == nullptr)
    {
        ei_printf("ERR: Failed to allocate snapshot buffer!\n");
        return;
    }

    // summary of inferencing settings (from model_metadata.h)
    ei_printf("Inferencing settings:\n");
    ei_printf("\tImage resolution: %dx%d\n", EI_CLASSIFIER_INPUT_WIDTH, EI_CLASSIFIER_INPUT_HEIGHT);
    ei_printf("\tFrame size: %d\n", EI_CLASSIFIER_DSP_INPUT_FRAME_SIZE);
    ei_printf("\tNo. of classes: %d\n", sizeof(ei_classifier_inferencing_categories) / sizeof(ei_classifier_inferencing_categories[0]));

    if (continuous_mode == true)
    {
        inference_delay = 0;
        state = INFERENCE_DATA_READY;
    }
    else
    {
        inference_delay = 2000;
        state = INFERENCE_WAITING;
        ei_printf("Starting inferencing in %d seconds...\n", inference_delay / 1000);
    }
}

void ei_stop_impulse(void)
{
    state = INFERENCE_STOPPED;
    ei_free(snapshot_buf);
    snapshot_buf_size = 0;
}

bool is_inference_running(void)
{
    return (state != INFERENCE_STOPPED);
}

uint16_t ei_get_det_result_len()
{

    return std::distance(l_obj_det.begin(), l_obj_det.end());
}

uint16_t ei_get_cnt_result_len()
{

    return std::distance(l_obj_det.begin(), l_obj_det.end());
}

void ei_get_det_result_data(uint16_t index, void *obj)
{

    object_detection_t *p_obj = (object_detection_t *)obj;

    if (p_obj == NULL || index >= ei_get_det_result_len())
    {
        ei_printf("ERR: Index out of bounds!\n");
        return;
    }
    auto front = l_obj_det.begin();
    std::advance(front, index);

    p_obj->x = front->x;
    p_obj->y = front->y;
    p_obj->w = front->w;
    p_obj->h = front->h;
    p_obj->confidence = front->confidence;
    p_obj->target = front->target;

    return;
}

void ei_get_cnt_result_data(uint16_t index, void *obj)
{

    object_counting_t *p_obj = (object_counting_t *)obj;

    if (p_obj == NULL || index >= ei_get_cnt_result_len())
    {
        ei_printf("ERR: Index out of bounds!\n");
        return;
    }
    auto front = l_obj_cnt.begin();
    std::advance(front, index);

    p_obj->target = front->target;
    p_obj->count = front->count;

    return;
}

#endif /* defined(EI_CLASSIFIER_SENSOR) && EI_CLASSIFIER_SENSOR == EI_CLASSIFIER_SENSOR_CAMERA */

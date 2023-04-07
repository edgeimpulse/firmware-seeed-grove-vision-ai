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

#include "ei_camera_himax.h"
#include "ei_device_sense_cap.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "edge-impulse-sdk/dsp/image/image.hpp"
#include "firmware-sdk/at_base64_lib.h"
#include <cmath>
extern "C"
{
#include "datapath.h"
#include "sensor_core.h"
#include "camera_core.h"
#include "error_code.h"
#include "hx_drv_pmu.h"
};

#define CLIP(value) (unsigned char)(((value) > 0xFF) ? 0xff : (((value) < 0) ? 0 : (value)))

ei_device_snapshot_resolutions_t EiCameraHimax::resolutions[] = {
    {.width = 64, .height = 64},
    {.width = 96, .height = 96},
    {.width = 128, .height = 128},
    {.width = 160, .height = 160},
};

static void yuv422p2rgb(uint8_t *pdst, const uint8_t *psrc, int h, int w, int c, int target_h, int target_w)
{
    int32_t y;
    int32_t cr;
    int32_t cb;

    int32_t r, g, b;
    uint32_t init_index, cbcr_index, index;
    uint32_t pixs = w * h;
    uint32_t u_chunk = w * h;
    uint32_t v_chunk = w * h + w * h / 2;
    float beta_h = (float)h / target_h, beta_w = (float)w / target_w;

    for (int i = 0; i < target_h; i++)
    {
        for (int j = 0; j < target_w; j++)
        {
            int tmph = i * beta_h, tmpw = beta_w * j;
            // select pixel
            index = i * target_w + j;
            init_index = tmph * w + tmpw; // ou
            cbcr_index = init_index % 2 ? init_index - 1 : init_index;

            y = psrc[init_index];
            cb = psrc[u_chunk + cbcr_index / 2];
            cr = psrc[v_chunk + cbcr_index / 2];
            r = (int32_t)(y + (14065 * (cr - 128)) / 10000);
            g = (int32_t)(y - (3455 * (cb - 128)) / 10000 - (7169 * (cr - 128)) / 10000);
            b = (int32_t)(y + (17790 * (cb - 128)) / 10000);

#if defined(ROTATION_LEFT)
            index = (target_w - 1 - index % target_w) * (target_h) + index / target_w;
#endif

            if (c == 1)
            {
                // rgb to gray
                uint8_t gray = (r * 299 + g * 587 + b * 114) / 1000;
                pdst[index] = (uint8_t)CLIP(gray);
            }
            else if (c == 3)
            {
                pdst[index * 3 + 0] = (uint8_t)CLIP(r);
                pdst[index * 3 + 1] = (uint8_t)CLIP(g);
                pdst[index * 3 + 2] = (uint8_t)CLIP(b);
            }
        }
    }
}

EiCameraHimax::EiCameraHimax()
{
    stream_active = false;

    // hardcoded
    // TODO: get camera detect form sensor_init
    camera_present = true;
}

bool EiCameraHimax::init(uint16_t width, uint16_t height)
{
    ERROR_T ret = ERROR_NONE;
    Sensor_Cfg_t sensor_cfg = {
        .sensor_type = SENSOR_CAMERA,
        .data = {
            .camera_cfg = {
                .width = width,
                .height = height,
            }}};

    ret = datapath_init(sensor_cfg.data.camera_cfg.width,
                        sensor_cfg.data.camera_cfg.height);
    if (ret != ERROR_NONE)
    {
        ei_printf("ERROR: Failed to initialize datapath (%d)\n", ret);
        return false;
    }

    ret = camera_init(&sensor_cfg.data.camera_cfg);
    if (ret != ERROR_NONE)
    {
        hx_drv_pmu_set_ctrl(PMU_SEN_INIT, 0);
        ei_printf("ERROR: Failed to initialize camera (%d)\n", ret);
        return false;
    }

    // find a proper resolution that is same or higher than the requested one
    ei_device_snapshot_resolutions_t sensor_res = this->search_resolution(width, height);

    if (set_resolution(sensor_res) == 0)
    {
        ei_printf("ERR: Failed to set camera resolution!\n");
        return false;
    }

    return true;
}

bool EiCameraHimax::deinit(void)
{
    camera_deinit();

    return true;
}

bool EiCameraHimax::set_resolution(const ei_device_snapshot_resolutions_t res)
{
    width = res.width;
    height = res.height;

    return true;
}

ei_device_snapshot_resolutions_t EiCameraHimax::get_min_resolution(void)
{
    return resolutions[0];
}

EiCamera *EiCamera::get_camera(void)
{
    static EiCameraHimax cam;

    return &cam;
}

bool EiCameraHimax::is_camera_present(void)
{
    return camera_present;
}

bool EiCameraHimax::ei_camera_capture_rgb888_packed_big_endian(uint8_t *image, uint32_t image_size)
{
    uint32_t raw_img_addr;

    datapath_start_work();

    while (!datapath_get_img_state());
    raw_img_addr = datapath_get_yuv_img_addr();
    yuv422p2rgb(image, (uint8_t *)raw_img_addr, this->height, this->width, 3, this->height, this->width);

    return true;
}

void EiCameraHimax::get_resolutions(ei_device_snapshot_resolutions_t **res, uint8_t *res_num)
{
    *res = &EiCameraHimax::resolutions[0];
    *res_num = sizeof(EiCameraHimax::resolutions) / sizeof(ei_device_snapshot_resolutions_t);
}

bool EiCameraHimax::start_stream(uint32_t width, uint32_t height)
{
    // try to set required resolution, returned is what has been set
    ei_device_snapshot_resolutions_t sensor_res = {width, height};
    this->init(width, height);

    if (set_resolution(sensor_res) == 0)
    {
        ei_printf("ERR: Failed to set camera resolution!\n");
        return false;
    }

    this->stream_buffer_size = this->width * this->height * 3;
    this->stream_buffer = (uint8_t *)ei_malloc(stream_buffer_size);
    if (this->stream_buffer == nullptr)
    {
        ei_printf("ERR: Failed to allocate stream buffer!\n");
        return false;
    }

    this->stream_active = true;
    return true;
}

bool EiCameraHimax::run_stream(void)
{
    if (stream_active == false)
    {
        return false;
    }

    ei_camera_capture_rgb888_packed_big_endian(this->stream_buffer, this->stream_buffer_size);

    // TODO: use camera color_depth size instead of fixed 3
    base64_encode((char *)this->stream_buffer,
                  this->width * this->height * 3,
                  ei_putchar);
    ei_printf("\r\n");

    return true;
}

bool EiCameraHimax::is_stream_active(void)
{
    return stream_active;
}

bool EiCameraHimax::stop_stream(void)
{
    auto dev = EiDeviceSenseCap::get_device();

    ei_printf("OK\r\n");
    // we can call it even if the baudrate wasn't changed
    dev->set_default_data_output_baudrate();
    ei_sleep(100);
    ei_printf("Snapshot streaming stopped by user\n");
    ei_printf("OK\n");
    ei_free(this->stream_buffer);

    this->deinit();

    stream_active = false;

    return true;
}

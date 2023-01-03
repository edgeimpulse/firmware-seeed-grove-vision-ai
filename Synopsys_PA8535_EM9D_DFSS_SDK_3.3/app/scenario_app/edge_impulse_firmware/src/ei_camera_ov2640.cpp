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

#include "ei_camera_ov2640.h"
#include "ei_device_vision_ai.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "edge-impulse-sdk/dsp/image/image.hpp"
#include "firmware-sdk/at_base64_lib.h"
#include <cmath>
extern "C" {
#include "datapath.h"
#include "sensor_core.h"
};

// 4:3 aspcet ratio
#define CAMERA_WIDTH 320
#define CAMERA_HEIGHT 240

#define CLIP(value) (unsigned char)(((value) > 0xFF) ? 0xff : (((value) < 0) ? 0 : (value)))

ei_device_snapshot_resolutions_t EiCameraOV2640::resolutions[] = {
        { .width = 128, .height = 96 },
        { .width = 160, .height = 120 },
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

  for (int i=0; i< target_h; i++)
  {
    for (int j=0; j<target_w; j++)
    {
      int tmph = i * beta_h, tmpw = beta_w * j;
      // select pixel
      index = i * target_w + j;
      init_index = tmph * w + tmpw;    //ou
      cbcr_index = init_index % 2 ? init_index - 1 : init_index;

      y = psrc[init_index];
      cb = psrc[u_chunk + cbcr_index / 2];
      cr = psrc[v_chunk + cbcr_index / 2];
      r = (int32_t)(y + (14065 * (cr - 128)) / 10000);
      g = (int32_t)(y - (3455 * (cb - 128)) / 10000 - (7169 * (cr - 128)) / 10000);
      b = (int32_t)(y + (17790 * (cb - 128)) / 10000);

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

EiCameraOV2640::EiCameraOV2640()
{
    stream_active = false;

    // hardcoded
    // TODO: get camera detect form sensor_init
    camera_present = true;
}

bool EiCameraOV2640::init(uint16_t width, uint16_t height)
{
    // find a proper resolution that is same or higher than the requested one
    ei_device_snapshot_resolutions_t sensor_res = this->search_resolution(width, height);

    if(set_resolution(sensor_res) == 0) {
        ei_printf("ERR: Failed to set camera resolution!\n");
        return false;
    }

    return true;
}

bool EiCameraOV2640::set_resolution(const ei_device_snapshot_resolutions_t res)
{
    // check if requested res is lower than the camera native one (currently fixed to 320x240)
    //TODO: is it possible to get here not correct resolution?
    width = res.width;
    height = res.height;

    return true;
}

ei_device_snapshot_resolutions_t EiCameraOV2640::get_min_resolution(void)
{
    return resolutions[0];
}

EiCamera* EiCamera::get_camera(void)
{
    static EiCameraOV2640 cam;

    return &cam;
}

bool EiCameraOV2640::is_camera_present(void)
{
    return camera_present;
}

bool EiCameraOV2640::ei_camera_capture_rgb888_packed_big_endian(uint8_t *image, uint32_t image_size)
{
    uint32_t raw_img_addr;

    datapath_start_work();

    while (!datapath_get_img_state());
    raw_img_addr = datapath_get_yuv_img_addr();
    yuv422p2rgb(image, (uint8_t*)raw_img_addr, CAMERA_HEIGHT, CAMERA_WIDTH, 3, this->height, this->width);

    return true;
}

void EiCameraOV2640::get_resolutions(ei_device_snapshot_resolutions_t **res, uint8_t *res_num)
{
    *res = &EiCameraOV2640::resolutions[0];
    *res_num = sizeof(EiCameraOV2640::resolutions) / sizeof(ei_device_snapshot_resolutions_t);
}

bool EiCameraOV2640::start_stream(uint32_t width, uint32_t height)
{
    // try to set required resolution, returned is what has been set
    ei_device_snapshot_resolutions_t sensor_res = this->search_resolution(width, height);

    if(set_resolution(sensor_res) == 0) {
        ei_printf("ERR: Failed to set camera resolution!\n");
        return false;
    }

    // store required output res
    this->output_width = width;
    this->output_height = height;

    // check if we have to do resize/crop
    this->stream_do_resize = this->width != width || this->height != height;

    // get bigger image resolution (snapshot or output) to allocate big enough buffer
    //TODO: get color depth (here 3 bytes) from camera props
    this->stream_buffer_size = std::max(this->width * this->height, this->output_width * this->output_height) * 3;
    this->stream_buffer = (uint8_t*)ei_malloc(stream_buffer_size);
    if(this->stream_buffer == nullptr) {
        ei_printf("ERR: Failed to allocate stream buffer!\n");
        return false;
    }

    this->stream_active = true;
    return true;
}

bool EiCameraOV2640::run_stream(void)
{
    if(stream_active == false) {
        return false;
    }

    ei_camera_capture_rgb888_packed_big_endian(this->stream_buffer, this->stream_buffer_size);

    if (this->stream_do_resize) {
        // interpolate in place
        ei::image::processing::crop_and_interpolate_rgb888(
            this->stream_buffer,
            this->width,
            this->height,
            this->stream_buffer,
            this->output_width,
            this->output_height);
    }

    //TODO: use camera color_depth size instead of fixed 3
    base64_encode((char*)this->stream_buffer,
        this->output_height * this->output_width * 3,
        ei_putchar);
    ei_printf("\r\n");

    return true;
}

bool EiCameraOV2640::is_stream_active(void)
{
    return stream_active;
}

bool EiCameraOV2640::stop_stream(void)
{
    auto dev = EiDeviceVisionAI::get_device();

    ei_printf("OK\r\n");
    // we can call it even if the baudrate wasn't changed
    dev->set_default_data_output_baudrate();
    ei_sleep(100);
    ei_printf("Snapshot streaming stopped by user\n");
    ei_printf("OK\n");
    ei_free(this->stream_buffer);

    stream_active = false;

    return true;
}

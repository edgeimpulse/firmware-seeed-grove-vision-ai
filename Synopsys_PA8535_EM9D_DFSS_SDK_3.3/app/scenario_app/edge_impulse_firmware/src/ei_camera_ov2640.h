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

#ifndef EI_CAMERA_OV2640_H
#define EI_CAMERA_OV2640_H
#include "firmware-sdk/ei_camera_interface.h"
//TODO: only for ei_device_snapshot_resolutions_t
#include "firmware-sdk/ei_device_info_lib.h"

class EiCameraOV2640 : public EiCamera {
private:
    static ei_device_snapshot_resolutions_t resolutions[];
    bool stream_active;
    uint32_t width;
    uint32_t height;
    uint32_t output_width;
    uint32_t output_height;
    bool stream_do_resize;
    uint8_t *stream_buffer;
    uint32_t stream_buffer_size;
    bool camera_present;

public:
    EiCameraOV2640();
    bool init(uint16_t width, uint16_t height);
    bool ei_camera_capture_rgb888_packed_big_endian(uint8_t *image, uint32_t image_size);
    bool set_resolution(const ei_device_snapshot_resolutions_t res);
    ei_device_snapshot_resolutions_t get_min_resolution(void);
    bool is_camera_present(void);
    void get_resolutions(ei_device_snapshot_resolutions_t **res, uint8_t *res_num);

    bool start_stream(uint32_t width, uint32_t height);
    bool run_stream(void);
    bool is_stream_active(void);
    bool stop_stream(void);
};

#endif /* EI_CAMERA_OV2640_H */
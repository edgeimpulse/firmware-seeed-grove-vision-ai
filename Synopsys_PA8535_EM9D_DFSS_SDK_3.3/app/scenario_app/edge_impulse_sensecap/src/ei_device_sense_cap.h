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

#ifndef EI_DEVICE_SENSE_CAP_H
#define EI_DEVICE_SENSE_CAP_H

#include "firmware-sdk/ei_device_info_lib.h"
#include "firmware-sdk/ei_device_memory.h"
#include "ei_camera_himax.h"

class EiDeviceSenseCap : public EiDeviceInfo {
private:
    EiDeviceSenseCap() = delete;
    std::string mac_address = "00:11:22:33:44:55:66";
    EiState state;
    static const int standalone_sensor_num = 0;
    ei_device_sensor_t standalone_sensor_list[standalone_sensor_num];
    bool camera_present;
    EiCameraHimax *cam;

public:
    std::string get_mac_address(void);

    EiDeviceSenseCap(EiDeviceMemory* mem);
    ~EiDeviceSenseCap();

    void (*sample_read_callback)(void);
    void init_device_id(void);
    void clear_config(void);
    bool is_camera_present(void);
    bool start_sample_thread(void (*sample_read_cb)(void), float sample_interval_ms) override;
    bool stop_sample_thread(void) override;

    void set_state(EiState state) override;
    EiState get_state(void);

    bool get_sensor_list(const ei_device_sensor_t **sensor_list, size_t *sensor_list_size) override;
    EiSnapshotProperties get_snapshot_list(void);
    uint32_t get_data_output_baudrate(void) override;
};

#endif /* EI_DEVICE_SENSE_CAP_H */

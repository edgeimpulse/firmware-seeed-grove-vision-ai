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

#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include "ei_device_vision_ai.h"
#include "ei_ram_memory.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "firmware-sdk/ei_device_memory.h"
#include "ei_microphone.h"
#include "ei_accelerometer.h"

using namespace std;

EiDeviceVisionAI::EiDeviceVisionAI(EiDeviceMemory* mem)
{
    EiDeviceInfo::memory = mem;

    init_device_id();

    load_config();

    device_type = "SEEED_VISION_AI";

    cam = static_cast<EiCameraOV2640*>(EiCameraOV2640::get_camera());
    camera_present = cam->is_camera_present();

    standalone_sensor_list[0].name = "Microphone";
    standalone_sensor_list[0].frequencies[0] = 16000.0f;
    standalone_sensor_list[0].start_sampling_cb = &ei_microphone_sample_start;
    standalone_sensor_list[0].max_sample_length_s = mem->get_available_sample_bytes() / (16000 * sizeof(microphone_sample_t));

    standalone_sensor_list[1].name = "Accelerometer";
    standalone_sensor_list[1].frequencies[0] = 50.0f;
    standalone_sensor_list[1].frequencies[1] = 62.5f;
    standalone_sensor_list[1].frequencies[2] = 100.0f;
    standalone_sensor_list[1].start_sampling_cb = &ei_accel_setup_data_sampling;
    standalone_sensor_list[1].max_sample_length_s = mem->get_available_sample_bytes() / (100 * SIZEOF_N_AXIS_SAMPLED);

}

EiDeviceVisionAI::~EiDeviceVisionAI()
{

}

string EiDeviceVisionAI::get_mac_address(void)
{
    return mac_address;
}

bool EiDeviceVisionAI::is_camera_present(void)
{
    return camera_present;
}

void EiDeviceVisionAI::init_device_id(void)
{
    //TODO: get uniqe ID of the MCU
    uint64_t id = 0x1122334455667788;
    char temp[18];

    snprintf(temp, 18, "%02x:%02x:%02x:%02x:%02x:%02x",
            (uint8_t)(id>>56),
            (uint8_t)(id>>48),
            (uint8_t)(id>>40),
            (uint8_t)(id>>16),
            (uint8_t)(id>>8),
            (uint8_t)(id));

    device_id = string(temp);
    mac_address = string(temp);
}

/**
 * @brief get_device is a static method of EiDeviceInfo class
 * It is used to implement singleton paradigm, so we are returning
 * here pointer always to the same object (dev)
 * 
 * @return EiDeviceInfo* 
 */
EiDeviceInfo* EiDeviceInfo::get_device(void)
{
    //TODO: memory is not required for camera only
    static EiRamMemory memory(sizeof(EiConfig));
    static EiDeviceVisionAI dev(&memory);

    return &dev;
}

void EiDeviceVisionAI::clear_config(void)
{
    EiDeviceInfo::clear_config();

    init_device_id();
    save_config();
}

bool EiDeviceVisionAI::start_sample_thread(void (*sample_read_cb)(void), float sample_interval_ms)
{
    //TODO: not required for camera only
    this->sample_read_callback = sample_read_cb;

    return true;
}

bool EiDeviceVisionAI::stop_sample_thread(void)
{
    //TODO: not required for camera only
    return true;
}

void EiDeviceVisionAI::set_state(EiState state)
{
    this->state = state;

    switch(state) {
        case eiStateErasingFlash:
        case eiStateSampling:
        case eiStateUploading:
        case eiStateFinished:
        case eiStateIdle:
        default:
            break;
    }
}

EiState EiDeviceVisionAI::get_state(void)
{
    return this->state;
}

bool EiDeviceVisionAI::get_sensor_list(const ei_device_sensor_t **sensor_list, size_t *sensor_list_size)
{
    *sensor_list = this->standalone_sensor_list;
    *sensor_list_size = this->standalone_sensor_num;

    return true;
}

EiSnapshotProperties EiDeviceVisionAI::get_snapshot_list(void)
{
    ei_device_snapshot_resolutions_t *res;
    uint8_t res_num = 0;

    EiSnapshotProperties props = {
        .has_snapshot = false,
        .support_stream = false,
        .color_depth = "",
        .resolutions_num = 0,
        .resolutions = res
    };

    if(this->cam->is_camera_present() == true) {
        this->cam->get_resolutions(&res, &res_num);
        props.has_snapshot = true;
        props.support_stream = true;
        props.color_depth = "RGB";
        props.resolutions_num = res_num;
        props.resolutions = res;
    }

    return props;
}

uint32_t EiDeviceVisionAI::get_data_output_baudrate(void)
{
    return 921600;
}

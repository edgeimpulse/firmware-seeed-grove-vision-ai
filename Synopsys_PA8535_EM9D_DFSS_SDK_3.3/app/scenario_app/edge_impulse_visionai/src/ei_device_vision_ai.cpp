/* The Clear BSD License
 *
 * Copyright (c) 2025 EdgeImpulse Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 *   * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
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

/*
 * Copyright (c) 2022 EdgeImpulse Inc.
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

#include "at_base64_lib.h"
#include "ei_device_lib.h"
#include "ei_device_info_lib.h"
#include "ei_device_memory.h"
#include "ei_device_interface.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"

/**
 * @brief      Call this function periocally during inference to 
 *             detect a user stop command
 *
 * @return     true if user requested stop
 */
extern bool ei_user_invoke_stop_lib(void)
{
    char ch;
    while(1) { 
        ch = ei_getchar();
        if(ch == 0) { return false; }
        if(ch == 'b') { return true; }
    }
}

/**
 * @brief Helper function for sending a data from memory over the
 * serial port. Data are encoded into base64 on the fly.
 * 
 * @param address address of samples
 * @param length number of samples (bytes)
 * @return true if eferything went fin
 * @return false if some error occured (error during samples read)
 */
bool read_encode_send_sample_buffer(size_t address, size_t length)
{
    EiDeviceInfo *dev = EiDeviceInfo::get_device();
    EiDeviceMemory *memory = dev->get_memory();
    // we are encoiding data into base64, so it needs to be divisible by 3
    const int buffer_size = 513;
    uint8_t* buffer = (uint8_t*)ei_malloc(buffer_size);

    while (1) {
        size_t bytes_to_read = buffer_size;

        if (bytes_to_read > length) {
            bytes_to_read = length;
        }

        if (bytes_to_read == 0) {
            ei_free(buffer);
            return true;
        }

        if (memory->read_sample_data(buffer, address, bytes_to_read) != bytes_to_read) {
            ei_free(buffer);
            return false;
        }

        base64_encode((char *)buffer, bytes_to_read, ei_putchar);

        address += bytes_to_read;
        length -= bytes_to_read;
    }

    return true;
}

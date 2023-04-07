/*
 * Copyright (c) 2022 Edge Impulse Inc.
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

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "grove_ai_config.h"
#include "ei_i2c_server.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "inference/ei_run_impulse.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "hx_drv_iomux.h"
#include "hx_drv_timer.h"
#include "i2c_comm.h"
#ifdef __cplusplus
}
#endif

// CRC8 x^8+x^5+x^4+x^0
const uint8_t CRC8Table[] = {
    0, 94, 188, 226, 97, 63, 221, 131, 194, 156, 126, 32, 163, 253, 31, 65,
    157, 195, 33, 127, 252, 162, 64, 30, 95, 1, 227, 189, 62, 96, 130, 220,
    35, 125, 159, 193, 66, 28, 254, 160, 225, 191, 93, 3, 128, 222, 60, 98,
    190, 224, 2, 92, 223, 129, 99, 61, 124, 34, 192, 158, 29, 67, 161, 255,
    70, 24, 250, 164, 39, 121, 155, 197, 132, 218, 56, 102, 229, 187, 89, 7,
    219, 133, 103, 57, 186, 228, 6, 88, 25, 71, 165, 251, 120, 38, 196, 154,
    101, 59, 217, 135, 4, 90, 184, 230, 167, 249, 27, 69, 198, 152, 122, 36,
    248, 166, 68, 26, 153, 199, 37, 123, 58, 100, 134, 216, 91, 5, 231, 185,
    140, 210, 48, 110, 237, 179, 81, 15, 78, 16, 242, 172, 47, 113, 147, 205,
    17, 79, 173, 243, 112, 46, 204, 146, 211, 141, 111, 49, 178, 236, 14, 80,
    175, 241, 19, 77, 206, 144, 114, 44, 109, 51, 209, 143, 12, 82, 176, 238,
    50, 108, 142, 208, 83, 13, 239, 177, 240, 174, 76, 18, 145, 207, 45, 115,
    202, 148, 118, 40, 171, 245, 23, 73, 8, 86, 180, 234, 105, 55, 213, 139,
    87, 9, 235, 181, 54, 104, 138, 212, 149, 203, 41, 119, 244, 170, 72, 22,
    233, 183, 85, 11, 136, 214, 52, 106, 43, 117, 151, 201, 74, 20, 246, 168,
    116, 42, 200, 150, 21, 75, 169, 247, 182, 232, 10, 84, 215, 137, 107, 53};

uint8_t i2c_handler_crc8(uint8_t *p, char counter, uint8_t crc8)
{

    for (; counter > 0; counter--)
    {
        crc8 = CRC8Table[crc8 ^ *p];
        p++;
    }
    return (crc8);
}


I2CServer::I2CServer()
{
    _state = I2C_IDLE;
}

I2CServer::I2CServer(I2CCommand_t *commands, size_t length)
{
    if (length == 0 || commands == nullptr)
    {

        return;
    }
    for (unsigned int i = 0; i < length; i++)
    {
        this->register_command(commands[i]);
    }

    _state = I2C_IDLE;
}

I2CServer::~I2CServer()
{
}

/**
 * @brief Register a new command. If the same command already exists
 * (by comparing \ref I2CCommand_t.command field) then overwrite it.
 *
 * @param command
 * @return true if the command has been registered
 * @return false if some sanity checks failed
 */
bool I2CServer::register_command(I2CCommand_t &command)
{

    // check if command exists
    for (auto it = this->registered_commands.begin(); it != this->registered_commands.end(); ++it)
    {
        if (it->feature == command.feature && it->cmd == command.cmd)
        {
            // remove command that is already exist
            this->registered_commands.erase(it);
            // there shouldn't be another handler for same command
            break;
        }
    }

    this->registered_commands.push_back(command);

    return true;
}

bool I2CServer::register_command(
    uint8_t feature,
    uint8_t cmd,
    uint8_t length,
    bool check_busy,
    I2CState_t (*run_handler)(),
    I2CState_t (*read_handler)(const uint8_t *read_buf, uint8_t *write_buff, uint8_t *len),
    I2CState_t (*write_handler)(const uint8_t *read_buf, uint8_t *write_buff))
{
    I2CCommand_t temp_cmd;

    temp_cmd.feature = feature;
    temp_cmd.cmd = cmd;
    temp_cmd.length = length;
    temp_cmd.check_busy = check_busy;
    temp_cmd.run_handler = run_handler;
    temp_cmd.read_handler = read_handler;
    temp_cmd.write_handler = write_handler;

    return this->register_command(temp_cmd);
}

bool I2CServer::register_handlers(
    uint8_t feature,
    uint8_t cmd,
    I2CState_t (*run_handler)(),
    I2CState_t (*read_handler)(const uint8_t *read_buf, uint8_t *write_buff, uint8_t *len),
    I2CState_t (*write_handler)(const uint8_t *read_buf, uint8_t *write_buff))
{
    for (auto it = registered_commands.begin(); it != registered_commands.end(); ++it)
    {
        if (it->feature == feature && it->cmd == cmd)
        {
            // TODO: add sanity checks?
            it->run_handler = run_handler;
            it->read_handler = read_handler;
            it->write_handler = write_handler;
            return true;
        }
    }

    return false;
}

I2CState_t I2CServer::get_state()
{
    return _state;
}

void I2CServer::set_state(I2CState_t state)
{
    _state = state;
}

void I2CServer::register_task(void (*task)(void *arg))
{
    _task = task;
}

void I2CServer::task(void *arg)
{
    if (_task != nullptr)
    {
        _task(arg);
    }
}

void I2CServer::onService(uint8_t feature, uint8_t cmd, uint8_t *read_buf, uint8_t *write_buf)
{
    I2CState_t state = I2C_IDLE;
    uint8_t crc8 = 0;
    uint8_t len = 0;

    for (auto it = registered_commands.begin(); it != registered_commands.end(); ++it)
    {
        if (it->feature == feature && it->cmd == cmd)
        {
            if (it->check_busy && _state == I2C_BUSY)
            {
                return;
            }

            if (it->run_handler != nullptr)
            {
                state = it->run_handler();
            }
            else if (it->read_handler != nullptr)
            {
                state = it->read_handler(read_buf, write_buf, &len);
#ifdef I2C_READ_CRC
                crc8 = i2c_handler_crc8(write_buf, len, 0);
                write_buf[len] = crc8;
#endif
            }
            else if (it->write_handler != nullptr)
            {
#ifdef I2C_WRITE_CRC
                crc8 = i2c_handler_crc8(&feature, 1, 0);
                crc8 = i2c_handler_crc8(&cmd, 1, crc8);
                crc8 = i2c_handler_crc8(read_buf, it->length, crc8);
                if (read_buf[it->length] != crc8)
                {
                    _state = I2C_ERROR;
                    return;
                }
#endif
                state = it->write_handler(read_buf, write_buf);
            }

            if (it->check_busy)
            {
                _state = state;
                return;
            }
        }
    }
    return;
}
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

#ifndef I2C_SERVER_H
#define I2C_SERVER_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <functional>
#include <string>
#include <vector>
#include "grove_ai_config.h"

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

typedef enum
{
    I2C_IDLE = 0x0,
    I2C_BUSY = 0x01,
    I2C_ERROR = 0x02
} I2CState_t;

typedef std::function<I2CState_t(void)> I2CRunHandler_t;
typedef std::function<I2CState_t(const uint8_t *read_buf, uint8_t *write_buff, uint8_t *len)> I2CReadHandler_t;
typedef std::function<I2CState_t(const uint8_t *read_buf, uint8_t *write_buff)> I2CWriteHandler_t;
typedef std::function<void(void *arg)> I2CTask_t;

typedef struct
{
    uint8_t feature;
    uint8_t cmd;
    uint8_t length;
    bool check_busy;
    I2CRunHandler_t run_handler;
    I2CReadHandler_t read_handler;
    I2CWriteHandler_t write_handler;
} I2CCommand_t;

class I2CServer
{
private:
    std::vector<I2CCommand_t> registered_commands;
    I2CState_t _state;
    I2CTask_t _task;

protected:
    I2CServer();
    I2CServer(I2CCommand_t *commands, size_t length);
    ~I2CServer();

public:
    I2CServer(I2CServer &other) = delete;
    void operator=(const I2CServer &) = delete;
    void onService(uint8_t feature, uint8_t cmd, uint8_t *read_buf, uint8_t *write_buf);
    I2CState_t get_state();
    void set_state(I2CState_t state);

    static I2CServer *get_instance();
    static I2CServer *get_instance(
        I2CCommand_t *commands,
        size_t length);

    void register_task(void (*task)(void *arg));
    void task(void *arg);

    bool register_command(I2CCommand_t &command);
    bool register_command(
        uint8_t feature,
        uint8_t cmd,
        uint8_t length,
        bool check_busy,
        I2CState_t (*run_handler)(void),
        I2CState_t (*read_handler)(const uint8_t *read_buf, uint8_t *write_buff, uint8_t *len),
        I2CState_t (*write_handler)(const uint8_t *read_buf, uint8_t *write_buff));
    bool register_handlers(
        uint8_t feature,
        uint8_t cmd,
        I2CState_t (*run_handler)(void),
        I2CState_t (*read_handler)(const uint8_t *read_buf, uint8_t *write_buff, uint8_t *len),
        I2CState_t (*write_handler)(const uint8_t *read_buf, uint8_t *write_buff));
};

#endif /* I2C_SERVER_H */
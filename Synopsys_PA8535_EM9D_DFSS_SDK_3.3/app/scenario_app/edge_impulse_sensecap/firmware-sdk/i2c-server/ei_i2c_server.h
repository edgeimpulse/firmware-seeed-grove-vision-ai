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
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

/* Include ----------------------------------------------------------------- */
#include <cstdlib>
#include <cstdio>
#include "board_config.h"
#include "hx_drv_timer.h"
#include "hx_drv_uart.h"
#include "grove_ai_config.h"
#include "logger.h"
#include "console_io.h"
#include "debugger.h"

extern "C" {
#include "datapath.h"
#include "sensor_core.h"
};

#include "external_flash.h"
#include "webusb.h"

#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "firmware-sdk/at_base64_lib.h"
#include "firmware-sdk/at-server/ei_at_server.h"
#include "firmware-sdk/at-server/ei_at_command_set.h"
#include "firmware-sdk/i2c-server/ei_i2c_server.h"

#include "ei_camera_ov2640.h"
#include "ei_device_vision_ai.h"
#include "ei_at_handlers.h"
#include "ei_i2c_handlers.h"
#include "ei_run_impulse.h"
#include "ei_microphone.h"
#include "ei_accelerometer.h"

static DEV_UART *console_uart;

extern "C" int edge_impulse_visionai(void)
{
    char c;
    ATServer *at;
    I2CServer *i2c;
    
    EiDeviceVisionAI* dev = static_cast<EiDeviceVisionAI*>(EiDeviceInfo::get_device());
    EiCameraOV2640* cam = static_cast<EiCameraOV2640*>(EiCameraOV2640::get_camera());

    hx_drv_timer_init();
    debugger_init();
    webusb_init();
    external_flash_xip_enable();
    ei_microphone_init();
    ei_accel_init();
    console_uart = hx_drv_uart_get_dev((USE_SS_UART_E)CONSOLE_UART_ID);

    dev->set_state(eiStateFinished);
    ei_printf("Edge Impulse firmware for Seeed Studio Grove Vision AI Module\n");

    i2c = ei_i2c_init(dev);

    at = ei_at_init(dev);
    at->print_prompt();

    while (1) {
        if(console_uart->uart_read_nonblock((void*)&c, 1) != 0) {
            if(is_inference_running() && c == 'b') {
                ei_stop_impulse();
                at->print_prompt();
                continue;
            }

            if(cam->is_stream_active() && c =='b') {
                cam->stop_stream();
                at->print_prompt();
                continue;
            }
            at->handle(c);
        }

        if(cam->is_stream_active()) {
            cam->run_stream();
        }

        if(is_inference_running() == true) {
            ei_run_impulse();
        }

        // Handle I2C commands
        i2c->task(nullptr);
    }

    return 0;
}

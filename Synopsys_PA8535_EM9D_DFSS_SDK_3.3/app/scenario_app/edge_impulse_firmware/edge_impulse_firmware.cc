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
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "firmware-sdk/at_base64_lib.h"
#include "firmware-sdk/at-server/ei_at_server.h"
#include "firmware-sdk/at-server/ei_at_command_set.h"

#include "ei_camera_ov2640.h"
#include "ei_device_vision_ai.h"
#include "ei_at_handlers.h"
#include "ei_run_impulse.h"

static DEV_UART *console_uart;

extern "C" int edge_impulse_firmware(void)
{
    char c;
    ATServer *at;
    
    EiDeviceVisionAI* dev = static_cast<EiDeviceVisionAI*>(EiDeviceInfo::get_device());
    EiCameraOV2640* cam = static_cast<EiCameraOV2640*>(EiCameraOV2640::get_camera());

    hx_drv_timer_init();
    debugger_init();
    external_flash_xip_enable();
    console_uart = hx_drv_uart_get_dev((USE_SS_UART_E)CONSOLE_UART_ID);

    dev->set_state(eiStateFinished);
    ei_printf("Edge Impulse firmware for Seeed Studio Grove Vision AI Module\n");

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
    }

    return 0;
}

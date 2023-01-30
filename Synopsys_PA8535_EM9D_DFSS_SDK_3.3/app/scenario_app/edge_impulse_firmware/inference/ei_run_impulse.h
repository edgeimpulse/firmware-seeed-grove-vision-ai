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

#ifndef EI_RUN_IMPULSE_H
#define EI_RUN_IMPULSE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

typedef struct
{
    uint16_t x;
    uint16_t y;
    uint16_t w;
    uint16_t h;
    uint8_t confidence;
    uint8_t target;
} object_detection_t;

typedef struct
{
    uint8_t target;
    uint8_t count;
} object_counting_t;

void ei_start_impulse(bool continuous, bool debug, bool use_max_uart_speed, float confidence);
void ei_run_impulse();
void ei_stop_impulse(void);
bool is_inference_running(void);

uint16_t ei_get_det_result_len();
void ei_get_det_result_data(uint16_t index, void *obj);

uint16_t ei_get_cnt_result_len();
void ei_get_cnt_result_data(uint16_t index, void *obj);

#ifdef __cplusplus
}
#endif

#endif /* EI_RUN_IMPULSE_H */

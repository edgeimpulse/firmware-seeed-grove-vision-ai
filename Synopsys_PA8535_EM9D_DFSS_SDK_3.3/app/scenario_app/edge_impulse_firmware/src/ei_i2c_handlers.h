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

#ifndef EI_I2C_HANDLERS_H
#define EI_I2C_HANDLERS_H

#include "firmware-sdk/i2c-server/ei_i2c_server.h"
#include "ei_device_vision_ai.h"

I2CServer *ei_i2c_init(EiDeviceVisionAI *device);

#endif /* EI_I2C_HANDLERS_H */
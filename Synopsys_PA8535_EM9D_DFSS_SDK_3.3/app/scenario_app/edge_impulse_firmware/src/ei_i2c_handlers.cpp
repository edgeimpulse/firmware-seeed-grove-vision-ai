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

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <forward_list>

#include "grove_ai_config.h"
#include "ei_i2c_handlers.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
#include "inference/ei_run_impulse.h"

#ifdef __cplusplus
extern "C"
{
#endif
#include "hx_drv_iomux.h"
#include "hx_drv_timer.h"
#include "powermode.h"
#include "i2c_comm.h"
#include "internal_flash.h"
#ifdef __cplusplus
}
#endif

/* Exported macros ---------------------------------------------------------*/
#define GROVE_AI_ADDRESS (0x62)

#define GROVE_AI_CAMERA_ID 0x0100

#define FEATURE_SYSTEM 0x80
#define FEATURE_ALGO 0xA0

#define FEATURE_INVAILD 0xFF
#define CMD_INVAILD 0xFF

#define CMD_SYS_READ_VERSION 0x01
#define CMD_SYS_VERSION_LENGTH 2
#define CMD_SYS_READ_ID 0x02
#define CMD_SYS_ID_LENGTH 2
#define CMD_SYS_READ_STATE 0x03
#define CMD_SYS_STATE_LENGTH 1
#define CMD_SYS_READ_ERROR_CODE 0x04
#define CMD_SYS_CODE_LENGTH 1
#define CMD_SYS_RESET 0x20

#define CMD_ALGO_READ_ALGO 0x00
#define CMD_ALGO_WRITE_ALGO 0x01
#define CMD_ALGO_ALGO_LENGTH 0x01
#define CMD_ALGO_READ_MODEL 0x10
#define CMD_ALGO_WRITE_MODEL 0x11
#define CMD_ALGO_MODEL_LENGTH 0x01
#define CMD_ALGO_READ_VALID_MODEL 0x12
#define CMD_ALGO_VALID_MODEL_LENGTH 0x04
#define CMD_ALGO_READ_PERIOD 0x20
#define CMD_ALGO_WRITE_PERIOD 0x21
#define CMD_ALGO_PERIOD_LENGTH 0x04
#define CMD_ALGO_READ_CONFIDENCE 0x40
#define CMD_ALGO_WRITE_CONFIDENCE 0x41
#define CMD_ALGO_CONFIDENCE_LENGTH 0x01
#define CMD_ALGO_READ_IOU 0x50
#define CMD_ALGO_WRITE_IOU 0x51
#define CMD_ALGO_IOU_LENGTH 0x01
#define CMD_ALGO_INOVKE 0xA0
#define CMD_ALGO_READ_RET_LEN 0xA1
#define CMD_ALGO_READ_RET_LEN_LENGTH 0x02
#define CMD_ALGO_READ_RET 0xA2
#define CMD_ALGO_CONFIG_SAVE 0xEE
#define CMD_ALGO_CONFIG_CLEAR 0xEF

typedef enum
{
    ALGO_OBJECT_DETECTION = 0,
    ALGO_OBJECT_COUNT = 1,
    ALGO_MAX,
} ALGO_INDEX_T;

typedef enum
{
    MODEL_PRE_INDEX_1 = 0x00,
    MODEL_EXT_INDEX_1 = 0x01,
    MODEL_EXT_INDEX_2 = 0x02,
    MODEL_EXT_INDEX_3 = 0x03,
    MODEL_EXT_INDEX_4 = 0x04,
    MODEL_MAX = 0x20,
} MODEL_INDEX_T;

typedef enum
{
    CMD_ALGO_INVOKE_STOP = 0x00,
    CMD_ALGO_INVOKE_START = 0x01
} CMD_ALGO_STATE_T;

/* config file */
#define ALGO_CONFIG_MAGIC1 0xc2d25ec8
#define ALGO_CONFIG_MAGIC2 0xfe3cda40

typedef struct
{
    uint32_t start_magic1;
    uint32_t start_magic2;
    uint8_t algo;
    uint8_t model;
    uint8_t invoke;
    uint32_t period;
    uint8_t confidence;
    uint8_t iou;
    uint16_t ret_len;
    uint32_t end_magic1;
    uint32_t end_magic2;
} algoConfig_t;

I2CServer *i2c;
algoConfig_t _algoConfig;

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
} object_count_t;

#define CMD_HEADER_LENGTH 0x02

/* Private variable -------------------------------------------------------*/
static uint8_t _i2c_read_buf[I2CCOMM_MAX_WBUF_SIZE] = {0};
static uint8_t _i2c_write_buf[I2CCOMM_MAX_RBUF_SIZE] = {0};

static std::forward_list<object_detection_t> _l_obj_det;
static std::forward_list<object_count_t> _l_obj_cnt;

/**
 * @brief  i2c event irq handle
 * @param  *param
 * @retval none
 */
static void i2c_event_rx_cb(void *param)
{
    (void)param;

#ifdef I2C_SYNC_PIN
    // set I2C sync pin to busy
    hx_drv_iomux_set_outvalue(I2C_SYNC_PIN, 1 - I2C_SYNC_STATE);
#endif

    uint8_t feature = _i2c_read_buf[I2CFMT_FEATURE_OFFSET];
    uint8_t cmd = _i2c_read_buf[I2CFMT_COMMAND_OFFSET];

    memset(_i2c_write_buf, 0x00, I2CCOMM_MAX_RBUF_SIZE);

    i2c->onService(feature, cmd, _i2c_read_buf + CMD_HEADER_LENGTH, _i2c_write_buf);

end:
    memset(_i2c_read_buf, 0x00, CMD_HEADER_LENGTH);

    hx_lib_i2ccomm_enable_write(_i2c_write_buf);
    hx_lib_i2ccomm_enable_read(_i2c_read_buf, I2CCOMM_MAX_RBUF_SIZE);

#ifdef I2C_SYNC_PIN
    // set I2C sync pin to idle
    hx_drv_iomux_set_outvalue(I2C_SYNC_PIN, I2C_SYNC_STATE);
#endif
    return;
}

static void i2c_event_tx_cb(void *param)
{
    (void)param;
}
static void i2c_event_err_cb(void *param)
{
    (void)param;
    memset(_i2c_read_buf, 0xFF, CMD_HEADER_LENGTH);
    hx_lib_i2ccomm_enable_read(_i2c_read_buf, I2CCOMM_MAX_RBUF_SIZE);
}

I2CState_t ei_i2c_read_version(const uint8_t *read_buf, uint8_t *write_buf, uint8_t *len)
{
    write_buf[0] = GROVE_AI_FAMILY_MAIN_VER;
    write_buf[1] = GROVE_AI_FAMILY_SUB_VER;

    *len = CMD_SYS_VERSION_LENGTH;

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_read_id(const uint8_t *read_buf, uint8_t *write_buf, uint8_t *len)
{
    write_buf[0] = GROVE_AI_FAMILY_MAIN_ID;
    write_buf[1] = GROVE_AI_FAMILY_SUB_ID;

    *len = CMD_SYS_ID_LENGTH;

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_read_state(const uint8_t *read_buf, uint8_t *write_buf, uint8_t *len)
{
    write_buf[0] = i2c->get_state();

    *len = CMD_SYS_STATE_LENGTH;

    return I2CState_t::I2C_IDLE;
}

void ei_i2c_algo_init()
{
    memset(&_algoConfig, 0, sizeof(_algoConfig));
    // read algo config from flash
    if (internal_flash_read(ALGO_CONFIG_ADDR, &_algoConfig, sizeof(_algoConfig)) == 0)
    {
        // check magic number
        if (_algoConfig.start_magic1 != ALGO_CONFIG_MAGIC1 || _algoConfig.start_magic2 != ALGO_CONFIG_MAGIC2 ||
            _algoConfig.end_magic1 != ALGO_CONFIG_MAGIC1 || _algoConfig.end_magic2 != ALGO_CONFIG_MAGIC2)
        {
            // write default config to flash
            _algoConfig.algo = ALGO_OBJECT_DETECTION;
            _algoConfig.model = MODEL_EXT_INDEX_1;
            _algoConfig.period = 0;
            _algoConfig.ret_len = 0;
            _algoConfig.invoke = 0;
            _algoConfig.confidence = 50;
            _algoConfig.iou = 45;

            _algoConfig.start_magic1 = ALGO_CONFIG_MAGIC1;
            _algoConfig.start_magic2 = ALGO_CONFIG_MAGIC2;
            _algoConfig.end_magic1 = ALGO_CONFIG_MAGIC1;
            _algoConfig.end_magic2 = ALGO_CONFIG_MAGIC2;

            internal_flash_write(ALGO_CONFIG_ADDR, &_algoConfig, sizeof(_algoConfig));
        }
    }
    else
    {
        // write default config
        _algoConfig.algo = ALGO_OBJECT_DETECTION;
        _algoConfig.model = MODEL_EXT_INDEX_1;
        _algoConfig.period = 0;
        _algoConfig.invoke = 0;
        _algoConfig.ret_len = 0;
        _algoConfig.confidence = 50;
        _algoConfig.iou = 45;
    }
}

I2CState_t ei_i2c_reset()
{

#ifdef EXTERNAL_LDO
    hx_lib_pm_chip_rst(PMU_WE1_POWERPLAN_EXTERNAL_LDO);
#else
    hx_lib_pm_chip_rst(PMU_WE1_POWERPLAN_INTERNAL_LDO);
#endif

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_read_algo(const uint8_t *read_buf, uint8_t *write_buf, uint8_t *len)
{
    write_buf[0] = _algoConfig.algo;

    *len = CMD_ALGO_ALGO_LENGTH;

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_write_algo(const uint8_t *read_buf, uint8_t *write_buf)
{
    uint8_t algo = read_buf[0];

    if (algo < ALGO_MAX)
    {
        _algoConfig.algo = algo;
    }

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_read_model(const uint8_t *read_buf, uint8_t *write_buf, uint8_t *len)
{
    write_buf[0] = _algoConfig.model;

    *len = CMD_ALGO_MODEL_LENGTH;

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_write_model(const uint8_t *read_buf, uint8_t *write_buf)
{
    // !!! EI MODEL COULDENT BE CHANGED
    _algoConfig.model = MODEL_EXT_INDEX_1;

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_read_valid_model(const uint8_t *read_buf, uint8_t *write_buf, uint8_t *len)
{
    // !!! EI VALID MODEL IS ALWAYS  1 << MODEL_EXT_INDEX_1
    write_buf[0] = 1 << MODEL_EXT_INDEX_1;

    *len = CMD_ALGO_ALGO_LENGTH;

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_read_confidence(const uint8_t *read_buf, uint8_t *write_buf, uint8_t *len)
{

    write_buf[0] = _algoConfig.confidence;

    *len = CMD_ALGO_CONFIDENCE_LENGTH;

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_write_confidence(const uint8_t *read_buf, uint8_t *write_buf)
{
    uint8_t confidence = read_buf[0];

    if (confidence <= 100)
    {
        _algoConfig.confidence = confidence;
    }
    else
    {
        _algoConfig.confidence = 100;
    }

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_read_ret_len(const uint8_t *read_buf, uint8_t *write_buf, uint8_t *len)
{

    write_buf[0] = (_algoConfig.ret_len >> 8) & 0xFF;
    write_buf[1] = _algoConfig.ret_len & 0xFF;

    *len = CMD_ALGO_READ_RET_LEN_LENGTH;

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_read_ret(const uint8_t *read_buf, uint8_t *write_buf, uint8_t *len)
{

    uint16_t index = ((uint16_t)read_buf[0] << 8) + read_buf[1];

    if (index >= _algoConfig.ret_len)
    {
        *len = 0;
        return I2CState_t::I2C_ERROR;
    }

    if (_algoConfig.algo == ALGO_OBJECT_DETECTION)
    {
        auto front = _l_obj_det.begin();
        std::advance(front, index);

        *len = sizeof(object_detection_t);

        object_detection_t obj;
        obj.x = front->x;
        obj.y = front->y;
        obj.w = front->w;
        obj.h = front->h;
        obj.confidence = front->confidence;
        obj.target = front->target;
        //ei_printf("x:%d y:%d w:%d h:%d confidence:%d target:%d, index:%d\n", obj.x, obj.y, obj.w, obj.h, obj.confidence, obj.target, index);
        memcpy(write_buf, &obj, *len);
    }
    else
    {
        auto front = _l_obj_cnt.begin();
        std::advance(front, index);

        *len = sizeof(object_count_t);
        object_count_t obj;
        obj.count = front->count;
        obj.target = front->target;
        //ei_printf("count:%d target:%d, index:%d\n", obj.count, obj.target, index);
        memcpy(write_buf, &obj, *len);
    }

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_algo_config_save()
{
    _algoConfig.start_magic1 = ALGO_CONFIG_MAGIC1;
    _algoConfig.start_magic2 = ALGO_CONFIG_MAGIC2;
    _algoConfig.end_magic1 = ALGO_CONFIG_MAGIC1;
    _algoConfig.end_magic2 = ALGO_CONFIG_MAGIC2;

    if (internal_flash_write(ALGO_CONFIG_ADDR, &_algoConfig, sizeof(_algoConfig)) != 0)
    {
        return I2CState_t::I2C_ERROR;
    }

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_algo_config_clear()
{

    if (internal_flash_clear(ALGO_CONFIG_ADDR, sizeof(_algoConfig)) != 0)
    {
        return I2CState_t::I2C_ERROR;
    }

    return I2CState_t::I2C_IDLE;
}

I2CState_t ei_i2c_algo_invoke()
{

    _algoConfig.invoke = CMD_ALGO_INVOKE_START;

    return I2CState_t::I2C_BUSY;
}

void ei_i2c_algo_task()
{
    if (_algoConfig.invoke == CMD_ALGO_INVOKE_START)
    {
        // TODO : invoke algo
        //ei_printf("invoke algo\n");
        _algoConfig.ret_len = 0;

        _l_obj_det.clear();
        _l_obj_cnt.clear();

        // ei_run_impulse();
        //for()

        /* fake result */
        board_delay_ms(200);

        object_count_t obj_cnt;
        obj_cnt.target = 0;
        obj_cnt.count = 1;

        _l_obj_cnt.emplace_front(obj_cnt);

        object_detection_t obj_det;
        obj_det.target = 0;
        obj_det.x = 50;
        obj_det.y = 50;
        obj_det.w = 50;
        obj_det.h = 50;
        obj_det.confidence = 50;

        _l_obj_det.emplace_front(obj_det);

        _algoConfig.ret_len = std::distance(_l_obj_cnt.begin(), _l_obj_cnt.end());

        _algoConfig.invoke = CMD_ALGO_INVOKE_STOP;
        i2c->set_state(I2CState_t::I2C_IDLE);
        //ei_printf("invoke algo done\n");
    }
}

void ei_i2c_task(void *arg)
{
    ei_i2c_algo_task();
}

I2CServer *ei_i2c_init(EiDeviceVisionAI *device)
{

    i2c = I2CServer::get_instance();

    if (i2c == NULL)
    {
        ei_printf("i2c init failed");
        return NULL;
    }

    i2c->register_task(ei_i2c_task);

    /* register i2c event callback */

    // system command
    i2c->register_command(FEATURE_SYSTEM, CMD_SYS_READ_VERSION, CMD_SYS_VERSION_LENGTH, false, nullptr, ei_i2c_read_version, nullptr);
    i2c->register_command(FEATURE_SYSTEM, CMD_SYS_READ_ID, CMD_SYS_ID_LENGTH, false, nullptr, ei_i2c_read_id, nullptr);
    i2c->register_command(FEATURE_SYSTEM, CMD_SYS_READ_STATE, CMD_SYS_STATE_LENGTH, false, nullptr, ei_i2c_read_state, nullptr);
    i2c->register_command(FEATURE_SYSTEM, CMD_SYS_RESET, 0, false, ei_i2c_reset, nullptr, nullptr);

    // algorithm command
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_READ_ALGO, CMD_ALGO_ALGO_LENGTH, false, nullptr, ei_i2c_read_algo, nullptr);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_WRITE_ALGO, CMD_ALGO_ALGO_LENGTH, true, nullptr, nullptr, ei_i2c_write_algo);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_READ_MODEL, CMD_ALGO_MODEL_LENGTH, false, nullptr, ei_i2c_read_model, nullptr);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_WRITE_MODEL, CMD_ALGO_MODEL_LENGTH, true, nullptr, nullptr, ei_i2c_write_model);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_READ_VALID_MODEL, CMD_ALGO_VALID_MODEL_LENGTH, false, nullptr, ei_i2c_read_valid_model, nullptr);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_READ_CONFIDENCE, CMD_ALGO_CONFIDENCE_LENGTH, false, nullptr, ei_i2c_read_confidence, nullptr);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_WRITE_CONFIDENCE, CMD_ALGO_CONFIDENCE_LENGTH, true, nullptr, nullptr, ei_i2c_write_confidence);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_READ_RET_LEN, CMD_ALGO_READ_RET_LEN_LENGTH, true, nullptr, ei_i2c_read_ret_len, nullptr);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_READ_RET, 0, true, nullptr, ei_i2c_read_ret, nullptr);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_CONFIG_SAVE, 0, true, ei_i2c_algo_config_save, nullptr, nullptr);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_CONFIG_CLEAR, 0, true, ei_i2c_algo_config_clear, nullptr, nullptr);
    i2c->register_command(FEATURE_ALGO, CMD_ALGO_INOVKE, 0, true, ei_i2c_algo_invoke, nullptr, nullptr);

    /* init i2c */
    ei_i2c_algo_init();

    memset(_i2c_read_buf, 0x00, sizeof(_i2c_read_buf));
    memset(_i2c_write_buf, 0x00, sizeof(_i2c_write_buf));

    I2CCOMM_CFG_T i2c_cfg;
    i2c_cfg.slv_addr = I2C_SLAVE_ADDR;
    i2c_cfg.read_cb = i2c_event_rx_cb;
    i2c_cfg.write_cb = NULL;           // i2c_event_tx_cb;
    i2c_cfg.err_cb = i2c_event_err_cb; // i2c_event_err_cb;
    hx_lib_i2ccomm_init(i2c_cfg);

    hx_lib_i2ccomm_enable_write(_i2c_write_buf);
    hx_lib_i2ccomm_start(_i2c_read_buf, I2CCOMM_MAX_RBUF_SIZE);

#ifdef I2C_SYNC_PIN
    /*
     In order to make the E5 cat detect the finish of himax startup.
     we set the GPIO of i2c sync to unavailable first and then
     available.
     */
    hx_drv_iomux_set_pmux(I2C_SYNC_PIN, 3);
    hx_drv_iomux_set_outvalue(I2C_SYNC_PIN, 1 - I2C_SYNC_STATE);
    board_delay_ms(5);
    hx_drv_iomux_set_outvalue(I2C_SYNC_PIN, I2C_SYNC_STATE);
#endif

    return i2c;
}

/**
*****************************************************************************************
*     Copyright(c) 2022, Seeed Technology Corporation. All rights reserved.
*****************************************************************************************
* @file      debugger.c
* @brief     debugger
* @author    Hongtai Liu (lht856@foxmail.com)
* @date      2022-05-17
* @version   v1.0
**************************************************************************************
* @attention
* <h2><center>&copy; COPYRIGHT 2022 Seeed Technology Corporation</center></h2>
**************************************************************************************
*/

#include "grove_ai_config.h"
#include "logger.h"

#include "debugger.h"
#include "hx_drv_iomux.h"

// volatile static bool _attach = false;

// #ifdef DEBUGGER_ATTACH_PIN
// static void debugger_attach_signale_cb(void *event)
// {

//     uint8_t value = 0;
//     hx_drv_iomux_get_invalue(DEBUGGER_ATTACH_PIN, &value);

//     if (value == DEBUGGER_ATTACH_STATE)
//     {
//         _attach = true;
//         hx_drv_iomux_set_outvalue(IOMUX_PGPIO6, 0);
//     }
//     else
//     {
//         hx_drv_iomux_set_outvalue(IOMUX_PGPIO6, 1);
//         _attach = false;
//     }
//     return;
// }
// #endif

void debugger_init()
{
#ifdef DEBUGGER_ATTACH_PIN
    hx_drv_iomux_set_pmux(DEBUGGER_ATTACH_PIN, 2);
    // hx_drv_iomux_cb_register(DEBUGGER_ATTACH_PIN, debugger_attach_signale_cb);
    // hx_drv_iomux_set_intenable(DEBUGGER_ATTACH_PIN, 1);
    // hx_drv_iomux_set_intmask(DEBUGGER_ATTACH_PIN, 0);
#endif
    return;
}

bool debugger_available()
{
#ifdef DEBUGGER_ATTACH_PIN
    uint8_t value = 0;
    hx_drv_iomux_get_invalue(DEBUGGER_ATTACH_PIN, &value);
    if (value == DEBUGGER_ATTACH_STATE)
    {
        return true;
    }
    else
    {
        return false;
    }
#endif
    return true;
}

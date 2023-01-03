/*
 * tflm_cis_sensor_defcfg.h
 *
 *  Created on: 2020¦~2¤ë12¤é
 *      Author: 902447
 */

#ifndef TFLM_CIS_SENSOR_DEFCFG_H_
#define TFLM_CIS_SENSOR_DEFCFG_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "embARC.h"
#include "embARC_debug.h"
#include "board_config.h"
#include "arc_timer.h"
#include "hx_drv_CIS_common.h"
#include "hx_drv_tflm.h"

#define CIS_AOS_MODE
//#define CIS_HM0360_MONO_MCLK_12M
//#define CIS_HM0360_MONO_CCM_EXTLDO_MCLK12M			//HM0360 V11
//#define CIS_HM0360_MONO_CCM_INTLDO_MCLK12M		//HM0360 V10
//#define CIS_HM0360_MONO_CCM_INTLDO_MCLK12M
//#define CIS_HM0360_MONO_MCLK_24M
//#define CIS_HM0360_MONO_CCM_EXTLDO_MCLK24M
//#define CIS_HM0360_MONO_CCM_INTLDO_MCLK24M

//#define CIS_HM0360_M_REVB_EXTLDO_MCLK12M
//#define CIS_HM0360_M_REVB_EXTLDO_MCLK24M

#ifdef SDK_LIB_CIS_HM0360_M_REVB_EXTLDO_MCLK24M
#define CIS_HM0360_MONO_CCM_EXTLDO_MCLK24M
#define CIS_HM0360_M_REVB_EXTLDO_MCLK24M
#endif

#ifdef SDK_LIB_CIS_HM01B0_MONO
#define CIS_HM01B0_MONO
#endif
//#define CIS_HM11B1_REVC_MCLK_24M_FPS60

HX_DRV_ERROR_E tflm_cis_set_cfg(uint8_t tp_enable);
HX_DRV_ERROR_E tflm_sensor_streamon();
HX_DRV_ERROR_E tflm_sensor_streamoff();

#endif /* TFLM_CIS_SENSOR_DEFCFG_H_ */

/*
 * hx_startup_data_bss_handle.c
 *
 *  Created on: 2020¦~6¤ë3¤é
 *      Author: 902447
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "arc_builtin.h"
#include "embARC_error.h"
#include "embARC_debug.h"
#include "board_config.h"
#include "apexextensions.h"
#include "hardware_config.h"
#include "hx_drv_pmu.h"

extern uint32_t _f_bss;
extern uint32_t _e_bss;
extern uint32_t _f_bss_tensor_arena;
extern uint32_t _e_bss_tensor_arena;


void hx_clear_bss()
{
	PMU_WAKEUPEVENT_E wakeup_event;
	PMU_BOOTFLOW_E boot_flow;
	uint32_t bss_size = 0, temp_data_bss_size = 0, tensor_arena_bss_size = 0;
	hx_drv_pmu_get_ctrl(PMU_WAKEUP_CPU_EVT_PMU, &wakeup_event);
	if(((wakeup_event & PMU_WAKEUP_SLP1_EXTGPIO) != 0)
			|| ((wakeup_event & PMU_WAKEUP_SLP1_SEXTINTSC4_RTCSC5) != 0)
			|| ((wakeup_event & PMU_WAKEUP_SLP1_ADCRTC_SC45) != 0)
			|| ((wakeup_event & PMU_WAKEUP_EXP_CPU8ADCINT_CPU12ADC) != 0)
			|| ((wakeup_event & PMU_WAKEUP_CAP_XDMA_ABN_INT) != 0)
			|| ((wakeup_event & PMU_WAKEUP_CAP_DP_ABN_INT) != 0)
			|| ((wakeup_event & PMU_WAKEUP_CAP_CPU4_CDM_MOTION) != 0)
			|| ((wakeup_event & PMU_WAKEUP_CAP_CPU12_CDM_ADCINT) != 0)
			|| ((wakeup_event & PMU_WAKEUP_CAP_CPU12_CDM_ADCNOINT) != 0)
			|| ((wakeup_event & PMU_WAKEUP_CAP_CPU12_NOMOTION_ADCINT) != 0))//
	{
		hx_drv_pmu_get_bootflow(&boot_flow);
		if(boot_flow == PMU_BOOTFLOW_FROM_RETENTION)
		{

		}else{
			bss_size = (uint32_t)&_e_bss - (uint32_t)&_f_bss;
			memset(&_f_bss, 0, bss_size);
			tensor_arena_bss_size =  (uint32_t)&_e_bss_tensor_arena - (uint32_t)&_f_bss_tensor_arena;
			memset(&_f_bss_tensor_arena, 0, tensor_arena_bss_size);
		}
	}else{
		bss_size = (uint32_t)&_e_bss - (uint32_t)&_f_bss;
		memset(&_f_bss, 0, bss_size);
		tensor_arena_bss_size =  (uint32_t)&_e_bss_tensor_arena - (uint32_t)&_f_bss_tensor_arena;
		memset(&_f_bss_tensor_arena, 0, tensor_arena_bss_size);
	}
}

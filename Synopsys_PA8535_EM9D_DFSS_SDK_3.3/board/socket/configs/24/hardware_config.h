/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */
/**
 *
 * \file
 * \ingroup	BOARD_SOCKET_COMMON_INIT
 * \brief	socket hardware resource definitions
 */

/**
 * \addtogroup BOARD_SOCKET_COMMON_INIT
 * @{
 */
#ifndef _HARDWARE_CONFIG_H_
#define _HARDWARE_CONFIG_H_

#include "../24/apexextensions.h"
#include "../24/io_config.h"

/* Choose work freq. */
/* WORK_FREQ_SPEED = 0 , 40MHz or custom.
 * WORK_FREQ_SPEED = 1 , 400MHz
 * */
#define WORK_FREQ_SPEED				1

/* System clock domains */
#define BOARD_REF_CLK			(100000000U)

/* System clock root */
#define BOARD_RC_OSC_CLK_32K	(32000U)/* SOCKET Platform */ // (32000U) /* Real Chip */
#define BOARD_RC_OSC_CLK_36M	(36000000U)
#define BOARD_XTAL_CLK_32K		(32768U)
#define BOARD_XTAL_CLK_24M		(24000000U)

#if(WORK_FREQ_SPEED)
#ifdef CPU_CLK_32M
#define BOARD_PLL_CLK_400M		(32000000U)
	#else
#define BOARD_PLL_CLK_400M		(400000000U)
	#endif
	
#else
/* 40MHz */
#define BOARD_PLL_CLK_40M		(40000000U)
#endif

#define BOARD_CIS_PCLK			(12000000U)

/* System regen clk */
#if(WORK_FREQ_SPEED)
#define BOARD_DFSS_CORE_CLK		(BOARD_PLL_CLK_400M)/* socket DFSS clock (including ARC EM) */
#else
#define BOARD_DFSS_CORE_CLK		(BOARD_PLL_CLK_40M)
#endif

#define BOARD_DFSS_IO_CLK		BOARD_DFSS_CORE_CLK	/* socket DFSS IO peripherals clock */
#define BOARD_DFSS_AHB_CLK		BOARD_DFSS_CORE_CLK	/* socket top-level AHB peripherals clock as DFSS */
#define BOARD_DFSS_APB_CLK		BOARD_DFSS_CORE_CLK	/* socket top-level APB peripherals clock as DFSS */
#define BOARD_APB_CLK 			(BOARD_DFSS_APB_CLK)/* socket top-level APB peripherals clock */
#define BOARD_DPPATH_CLK		(BOARD_RC_OSC_CLK_36M) /* HWACC Data Path Clock */
#define BOARD_PWM_CLK			(BOARD_RC_OSC_CLK_36M) /* PWM Clock */
#define BOARD_SPI_CLK			(100000000U)		/* socket SPI clock*/

/* CPU clock frequency definition */
#ifdef BOARD_DFSS_CORE_CLK
/* Get CPU clock frequency from BOARD_DFSS_CORE_CLK defined in specification */
	#define CLK_CPU		(BOARD_DFSS_CORE_CLK)
#elif defined(ARC_FEATURE_CPU_CLOCK_FREQ)
/* Get CPU clock frequency definition from TCF file */
	#define CLK_CPU		(ARC_FEATURE_CPU_CLOCK_FREQ)
#else
/* Default CPU clock frequency */
	#define CLK_CPU		(BOARD_REF_CLK)
#endif

/** Peripheral Bus Reference Clock definition */
#ifdef BOARD_APB_CLK
	/*!< Get peripheral bus reference clock defintion from build system */
	#define CLK_BUS_APB		(BOARD_APB_CLK)
#else
	/*!< Default peripheral bus reference clock defintion */
	#define CLK_BUS_APB		(50000000U)
#endif

/* Device Register Base Address */
#define BASE_ADDR_BOOT_SPI 		(0x10000000)
#define BASE_ADDR_FLASH 		(0x28000000)
#define BASE_ADDR_SYSCONFIG		(0xB0000000)

// DFSS_APB_BUS
#define BASE_ADDR_DW_SPI0 		(0x28000000)
#define BASE_ADDR_DW_SPI1 		(0x30000000)
#define BASE_ADDR_DW_I2S		(0xF0000000)
#define BASE_ADDR_I2S_TX		BASE_ADDR_DW_I2S
#define BASE_ADDR_I2S_RX		BASE_ADDR_DW_I2S


// REGBK0
#define HW_CKGEN_BASE_ADDR		(0xB0000000)
#define HW_SWRST_BASE_ADDR		(0xB0000020)	// HW_CKGEN_BASE_ADDR + SWRST_OFFSET
#define HW_GPIO_BASE_ADDR 		(0xB0000030)	// HW_CKGEN_BASE_ADDR + GPIO_OFFSET
#define HW_GPIO_BASE_ADDR1		(0xB0000080)
#define HW_RTC_BASE_ADDR 		(0xB0000050)	// HW_CKGEN_BASE_ADDR + RTC_OFFSET
#define HW_RTCADC_BASE_ADDR 	(0xB0000060)	// HW_CKGEN_BASE_ADDR + RTCADC_OFFSET
#define HW_PMU_BASE_ADDR 		(0xB0000090)	// HW_CKGEN_BASE_ADDR + PMU_OFFSET
#define HW_ADCC_BASEADDR 		(0xB0000200)
#define HW_ADC_BASEADDR 		(0xB0000300)
#define HW_LDO_BASEADDR 		(0xB0000400)
#define HW_POR_BASEADDR 		(0xB0000500)
#define HW_PWM0_BASEADDR 		(0xB0000600)
#define HW_SENSORCTRL_BASEADDR  (0xB0001000)
#define HW_INP_BASEADDR  		(0xB0001100)
#define HW_CDM_BASEADDR  		(0xB0001200)
#define HW_DP_BASEADDR  		(0xB0001300)
#define HW_2X2_BASEADDR  		(0xB0001400)
#define HW_5X5_BASEADDR 	    (0xB0001500)
#define HW_TPG_BASEADDR  		(0xB0001600)
#define HW_XDMA_BASEADDR  		(0xB0001700)
#define HW_JPEG_BASEADDR  		(0xB0001800)
#define HW_SRAMTEST_BASEADDR  	(0xB0001900)
#define HW_SSIREGBK_BASEADDR  	(0xB0001A00)
#define HW_ARCREGBK_BASEADDR  	(0xB0001B00)
#define HW_EDM_BASEADDR  		(0xB0001C00)
#define HW_INP1BITPARSER_BASEADDR  		(0xB0001D00)

// REGBK1
#define HW_ARCREGBK1_BASEADDR   (0xB0010000)
#define HW_PWM1_BASEADDR   		(0xB0010200)
#define HW_PWM2_BASEADDR   		(0xB0010224)
#define HW_HOG_BASEADDR  		(0xB0010400)
#define HW_HOGDMA_BASEADDR 		(0xB0010600)
#define HW_RS_BASEADDR   		(0xB0010800)
#define HW_RSDMA_BASEADDR  		(0xB0010A00)
#define HW_AHB_BASEADDR  		(0xB0010B00)
#define HW_I2S_BASEADDR  		(0xB0010C00)
#define HW_I2C_BASEADDR  		(0xB0010D00)





#endif	/* _HARDWARE_CONFIG_H_ */

/** @} end of group BOARD_SOCKET_COMMON_INIT  */

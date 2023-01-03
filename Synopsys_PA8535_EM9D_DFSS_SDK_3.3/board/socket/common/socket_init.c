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
 * \defgroup	BOARD_SOCKET_COMMON_INIT	SOCKET Common Init Module
 * \ingroup	BOARD_SOCKET_COMMON
 * \brief	SOCKET Board Common Init Module
 * \details
 * 		SOCKET timer/gpio/interrupt init process. Device-driver installation is done while
 *	getting the device object for the first time.
 */

/**
 * \file
 * \ingroup	BOARD_SOCKET_COMMON_INIT
 * \brief	common socket init module
 */

/**
 * \addtogroup	BOARD_SOCKET_COMMON_INIT
 * @{
 */
#include "arc_builtin.h"
#include "arc.h"
#include "arc_timer.h"
#include "arc_exception.h"
#include "embARC_debug.h"

#include "board.h"
#include "hx_drv_timer.h"
#ifndef EMZA_SIMULATOR		// For EMZA_SIMULATOR(RTL,XCAM), skip peripheral and hwacc
#include "hx_drv_rtc.h"
#include "hx_drv_ckgen.h"
#ifdef __Xdmac
#include "arc_udma.h"
#endif
#include "hx_drv_iic_m.h"
#include "hx_drv_iic_s.h"
#include "hx_drv_uart.h"
#include "hx_drv_spi_m.h"
#include "hx_drv_spi_s.h"
#include "hx_drv_iomux.h"
#include "hx_drv_pwm.h"
#include "hx_drv_pmu.h"
#include "hx_drv_cdm.h"
#include "hx_drv_dp.h"
#include "hx_drv_hog.h"
#include "hx_drv_hogdma.h"
#include "hx_drv_hw2x2.h"
#include "hx_drv_hw5x5.h"
#include "hx_drv_inp.h"
#include "hx_drv_inp1bitparser.h"
#include "hx_drv_jpeg.h"
#include "hx_drv_rs.h"
#include "hx_drv_rsdma.h"
#include "hx_drv_sensorctrl.h"
#include "hx_drv_tpg.h"
#include "hx_drv_xdma.h"
#include "hx_drv_edm.h"
#ifdef LIB_PWRMGMT
#include "powermode.h"
#endif
#include "sensor_dp_lib.h"

#ifdef I2C_COMM
#include "i2c_comm.h"
#endif

#include "hx_drv_basic_def.h"
#include "hx_hal_sec.h"
#include "hx_OTP_HSM.h"
#endif


/****************************************************
 * Constant Definition                              *
 ***************************************************/
#define APP_VER_TYPE	APP_TYPE_DEV	/* version number is used to indicate firmware design for which product */
#define APP_VER_MAJOR	2	/* version number is incremented for infrastructure update and new feature support */
#define APP_VER_MINOR	0	/* version number is incremented for API update  */
#define APP_VER_PATCH   0	/* version number is incremented for bug fixed */

/****************************************************
 * Variable Declaration                             *
 ***************************************************/
uint32_t g_pad_dir_78;
uint32_t g_pad_dir_7c;
uint32_t g_pad_dir_524;
uint32_t g_pad_dir_52C;

extern uint32_t g_bsp_version;


/****************************************************
 * Function Implementation                          *
 ***************************************************/
/**
 * \brief	Board init routine MUST be called in each application
 * \note	It is better to disable interrupts when calling this function
 *	remember to enable interrupt when you want to use them
 */
void board_init(void)
{
	uint32_t reg_addr= 0xB0000078;
	/* Set BSP version number */
	g_bsp_version = (APP_VER_TYPE<<24) | (APP_VER_MAJOR<<16) | (APP_VER_MINOR<<8) | (APP_VER_PATCH);

#ifndef EMZA_SIMULATOR // For EMZA_SIMULATOR(RTL,XCAM), skip peripheral and hwacc
#ifdef __Xdmac
	 static dma_state_t 		g_udma;
#endif
#endif
	/* enable all interrupts and levels */
	arc_unlock_restore((1<<4) /* enable interrupts */ | 15 /* and set maximal priority to enable */) ;

	reg_addr= 0xB0000078;
	g_pad_dir_78 = 	_arc_read_uncached_32((void*)reg_addr);
	_arc_write_uncached_32((void *)reg_addr, 0);
	reg_addr= 0xB000007C;
	g_pad_dir_7c = 	_arc_read_uncached_32((void*)reg_addr);
	_arc_write_uncached_32((void *)reg_addr, 0);

#ifdef BOARD_PLL_CLK_40M
	//24M x 5 / 4 = 40MHz
	HX_UNCACHE_BIT_SET(0xb0000524,32,0,0x38611003);//bit[7:0]  division 
	HX_UNCACHE_BIT_SET(0xb000052C,32,0,0x00000516);//bit[15:8] multiplication 
#endif

	timer_init();
	hx_drv_timer_init();
#ifndef EMZA_SIMULATOR // For EMZA_SIMULATOR(RTL,XCAM), skip peripheral and hwacc
	hx_drv_pmu_init(); // put before rtc because some HW workaround

	hx_drv_rtc_init();
	hx_drv_ckgen_init();
	hx_drv_swrst_init();
#ifdef __Xdmac
	/** Must init uDMA before use it */
	dmac_init(&g_udma);
#endif
	hx_drv_i2cm_init(USE_SS_IIC_ALL, IIC_SPEED_FAST);
	hx_drv_i2cs_init();
	hx_drv_uart_init(USE_SS_UART_ALL);
	hx_drv_spi_mst_init(USE_DW_SPI_MST_ALL);
	hx_drv_spi_slv_init(USE_DFSS_SPI_SLV_ALL);
	hx_drv_iomux_init();
	hx_drv_pwm_init();

	hx_drv_cdm_init();

	hx_drv_dp_init();

	hx_drv_hog_init();
	hx_drv_hogdma_init();

	hx_drv_hw2x2_init();
	hx_drv_hw5x5_init();
	hx_drv_inp_init();
	hx_drv_inp1bitparser_init();
	hx_drv_jpeg_init();

	hx_drv_rs_init();
	hx_drv_rsdma_init();

	hx_drv_sensorctrl_init();
	hx_drv_tpg_init();
	hx_drv_xdma_init();
	hx_drv_edm_init();

	// Library Initialize
	sensordplib_init();
#ifdef LIB_PWRMGMT
	hx_lib_pm_init();
#endif
#ifdef I2C_COMM
	hx_lib_i2ccomm_open();
#endif

#endif
}

void specific_board_init(BOARD_INIT_SPEC_E INIT_ITEM)
{
	uint32_t reg_addr= 0xB0000078;
	/* Set BSP version number */
	g_bsp_version = (APP_VER_TYPE<<24) | (APP_VER_MAJOR<<16) | (APP_VER_MINOR<<8) | (APP_VER_PATCH);

#ifndef EMZA_SIMULATOR // For EMZA_SIMULATOR(RTL,XCAM), skip peripheral and hwacc
#ifdef __Xdmac
	static dma_state_t g_udma;
#endif
#endif
	/* enable all interrupts and levels */
	arc_unlock_restore((1<<4) /* enable interrupts */ | 15 /* and set maximal priority to enable */);

	reg_addr= 0xB0000078;
	g_pad_dir_78 = 	_arc_read_uncached_32((void*)reg_addr);
	_arc_write_uncached_32((void *)reg_addr, 0);
	reg_addr= 0xB000007C;
	g_pad_dir_7c = 	_arc_read_uncached_32((void*)reg_addr);
	_arc_write_uncached_32((void *)reg_addr, 0);

	timer_init();
	hx_drv_timer_init();
#ifndef EMZA_SIMULATOR // For EMZA_SIMULATOR(RTL,XCAM), skip peripheral and hwacc
	hx_drv_pmu_init(); // put before rtc because some HW workaround

	hx_drv_rtc_init();
	hx_drv_ckgen_init();
	hx_drv_swrst_init();
#ifdef __Xdmac
	/** Must init uDMA before use it */
	dmac_init(&g_udma);
#endif

	if(INIT_ITEM&BOARD_INIT_SPEC_PERI_I2CM)
		hx_drv_i2cm_init(USE_SS_IIC_ALL, IIC_SPEED_STANDARD);

	//if(INIT_ITEM&BOARD_INIT_SPEC_PERI_I2CS)
	//	hx_drv_i2cs_init();

	if(INIT_ITEM&BOARD_INIT_SPEC_PERI_UART)
		hx_drv_uart_init(USE_SS_UART_ALL);

	if(INIT_ITEM&BOARD_INIT_SPEC_PERI_SPIM)
		hx_drv_spi_mst_init(USE_DW_SPI_MST_ALL);

	//if(INIT_ITEM&BOARD_INIT_SPEC_PERI_SPIS)
	//	hx_drv_spi_slv_init(USE_DFSS_SPI_SLV_ALL);

	if(INIT_ITEM&BOARD_INIT_SPEC_PERI_GPIO)
		hx_drv_iomux_init();

	if(INIT_ITEM&BOARD_INIT_SPEC_PWM)
		hx_drv_pwm_init();

	if(INIT_ITEM&BOARD_INIT_SPEC_DP)
	{
		hx_drv_cdm_init();

		hx_drv_dp_init();

		hx_drv_hog_init();
		hx_drv_hogdma_init();

		hx_drv_hw2x2_init();
		hx_drv_hw5x5_init();
		hx_drv_inp_init();
		hx_drv_inp1bitparser_init();
		hx_drv_jpeg_init();

		hx_drv_rs_init();
		hx_drv_rsdma_init();

		hx_drv_sensorctrl_init();
		hx_drv_tpg_init();
		hx_drv_xdma_init();
		hx_drv_edm_init();

		// Library Initialize
		sensordplib_init();
	}

	if(INIT_ITEM&BOARD_INIT_SPEC_EVT)
#ifdef I2C_COMM
	//hx_lib_i2ccomm_open();
#endif
	if(INIT_ITEM&BOARD_INIT_SPEC_SECURITY )
	{
	    //Hx_System_Info sec_info;
	    //sec_info.cpu_clk= BOARD_PLL_CLK_400M;
		//sec_info.sec_system_mem = 0x20010000;
		//himax_sec_init(&sec_info);
	}

#endif
}

/** @} end of group BOARD_SOCKET_COMMON_INIT */

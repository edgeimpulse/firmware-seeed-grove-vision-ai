/**
 ********************************************************************************************
 *  @file      sensor_dp_config.h
 *  @details   This file contains all sensor datapath configuration
 *  @author    himax/902447
 *  @version   V1.0.0
 *  @date      14-May-2019
 *  @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 *******************************************************************************************/


#ifndef SENSOR_DP_CONFIG_H_
#define SENSOR_DP_CONFIG_H_

#include "target_mem_config.h"
/**
 * \defgroup	SENSOR_DP_LIB_MACRO	Sensor Datapath Macro
 * \ingroup	SENSOR_DP_LIB
 * \brief	Defines some macros of Sensor Datapath Library need.
 * @{
 */
#define WMDA2_YUV420_TARGET_LOOP_CNT         6	/*!< JPEG YUV420 default buffer count*/
#define WMDA2_YUV422_TARGET_LOOP_CNT         3  /*!< JPEG YUV422 default buffer count*/
#define WMDA2_YUV400_TARGET_LOOP_CNT         10	/*!< JPEG YUV400 default buffer count*/

/*
 * \def WE1_DP_WDMA1_OUT_SRAM_ADDR  WDMA1 base memory address
 * \def WE1_DP_WDMA2_OUT_SRAM_ADDR  WDMA2 base memory address
 * \def WE1_DP_WDMA3_OUT_SRAM_ADDR  WDMA3 base memory address
*/
#if defined(CLI_ENABLE) || defined(PMU_LIB_TEST)
#define WE1_DP_WDMA1_OUT_SRAM_ADDR   	0x20080000//(EXT_RAM_START + 0)/*!< WDMA1 default base memory address*/
#define WE1_DP_WDMA2_OUT_SRAM_ADDR    	0x200A8400//(EXT_RAM_START + 0xA0800)/*!< WDMA2 default base memory address*/
#define WE1_DP_WDMA3_OUT_SRAM_ADDR    	0x200F3400//(EXT_RAM_START + 0xEB800)/*!< WDMA3 default base memory address*/
#elif defined(HWACCBYTPG_AUTO_TEST)
#define WE1_DP_WDMA1_OUT_SRAM_ADDR   	0x20000000//(EXT_RAM_START + 0)/*!< WDMA1 default base memory address*/
#define WE1_DP_WDMA2_OUT_SRAM_ADDR    	0x200A0800//(EXT_RAM_START + 0xA0800)/*!< WDMA2 default base memory address*/
#define WE1_DP_WDMA3_OUT_SRAM_ADDR    	0x200EB800//(EXT_RAM_START + 0xEB800)/*!< WDMA3 default base memory address*/
#else
#define WE1_DP_WDMA1_OUT_SRAM_ADDR   	(EXT_RAM_START + 0x50000)/*!< WDMA1 default base memory address*/ //300KB////(WE1_DP_BASE_ADDR + 0x34000)//
#define WE1_DP_WDMA2_OUT_SRAM_ADDR    	(EXT_RAM_START + 0x9B000)/*!< WDMA2 default base memory address*///300KB//(WE1_DP_BASE_ADDR + 0xA4800)
#define WE1_DP_WDMA3_OUT_SRAM_ADDR    	(EXT_RAM_START + 0xE6000)/*!< WDMA3 default base memory address*///450KB 0x156800 end//(WE1_DP_BASE_ADDR + 0xEF800)
#endif
#define WE1_DP_YUV422_WDMA3_OUT_SRAM_ADDR    	(EXT_RAM_START + 0x0)/*!< WDMA3 YUV422 format base memory address*/

#define WE1_DP_JPEG_HWAUTOFILL_SRAM_ADDR    (EXT_RAM_START + 0x15FE70)  /*!< JPEG HW auto fill memory start address*/

#if defined(CLI_ENABLE) || defined(HWACCBYTPG_AUTO_TEST)
#define WE1_DP_RS_IN_SRAM_ADDR			(EXT_RAM_START + 0xF3400)	/*!< Resampler input default memory address*/
#define WE1_DP_RS_OUT_SRAM_ADDR			(EXT_RAM_START + 0x5DC00)	/*!< Resampler output default memory address*/
#else
#define WE1_DP_RS_IN_SRAM_ADDR			(WE1_DP_WDMA3_OUT_SRAM_ADDR)  /*!< Resampler input default memory address*/
#define WE1_DP_RS_OUT_SRAM_ADDR			(WE1_DP_WDMA1_OUT_SRAM_ADDR)	/*!< Resampler output default memory address*/
#endif

#if defined(CLI_ENABLE) || defined(HWACCBYTPG_AUTO_TEST)
#define WE1_DP_HOG_OUT_SRAM_ADDR     (EXT_RAM_START + 0)		/*!< HOG input default memory address*/
#define WE1_DP_HOG_Y_IN_SRAM_ADDR    (EXT_RAM_START + 0xF3400)  /*!< HOG output default memory address*/
#else
#define WE1_DP_HOG_OUT_SRAM_ADDR     (WE1_DP_WDMA1_OUT_SRAM_ADDR)	/*!< HOG input default memory address*/
#define WE1_DP_HOG_Y_IN_SRAM_ADDR    (WE1_DP_WDMA3_OUT_SRAM_ADDR)	/*!< HOG output default memory address*/
#endif


#define SUPPORT_EDM_PULSE_TIMING_DETECT	/*!< EDM after INP Timing detect compiler flag(enable/disable) debug purpose*/

#define SUPPORT_EDM_CONV_TIMING_DETECT	/*!< EDM Conventional Timing detect compiler flag(enable/disable) debug purpose*/
//#define SUPPORT_EDM_PULSE_TIMING_DETECT_ISR
//#define SUPPORT_EDM_CONV_TIMING_DETECT_ISR

#define SUPPORT_EDM_WDT_DETECT  /*!< EDM WDT compiler flag for Datapath abnormal to avoid system hang up */
#ifdef SUPPORT_EDM_WDT_DETECT
#define WDT_TIMEOUT_PERIOD    5000 /*!< EDM WDT fire period */
#endif
/** @} */
#endif /* SENSOR_DP_CONFIG_H_ */

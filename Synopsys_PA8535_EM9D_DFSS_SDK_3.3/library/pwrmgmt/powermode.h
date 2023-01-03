/**
 ********************************************************************************************
 *  @file      powermode.h
 *  @details   This file contains all power mode related function
 *  @author    himax/902449
 *  @version   V1.0.0
 *  @date      8-Aug-2019
 *  @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 *******************************************************************************************/
/**
 * \defgroup	PWRMGMT_LIB	Power Manager Library
 * \ingroup	PWRMGMT_LIB
 * \brief	Power Manager library Declaration
 */

#ifndef LIBRARY_PWRMGMT_POWERMODE_H_
#define LIBRARY_PWRMGMT_POWERMODE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "embARC_toolchain.h"
#include "embARC_error.h"
#include "embARC_debug.h"
#include "hx_drv_pmu.h"
/**
 * \defgroup	PWRMGMT_LIB	Sensor Control Driver
 * \ingroup		PWRMGMT_LIB
 * \brief	Power Management Library Declaration
 * \details Application can use Power Management API and data structure(PM_CFG_T) to control WE-1 Power Management Unit\n
 * <pre>
 * For Example
 * Ex1: PMU CDM Wakeup Setting
 * 		PM_CFG_T aCfg;
 * 		aCfg.mode = PM_MODE_AOS_ONLY;
 * 		aCfg.sensor_rtc = 500;
 * 		aCfg.pmu_timeout = 500;
 * 		aCfg.adc_rtc = 0;
 * 		aCfg.adc_timeout = 0;
 * 		aCfg.powerplan = PMU_WE1_POWERPLAN_INTERNAL_LDO; //
 * 		aCfg.io_mask = io_mask;  //GPIO Interrupt mask
 * 		aCfg.bootromspeed = PMU_BOOTROMSPEED_PLL_400M_50M;
 * 		aCfg.s_ext_int_mask = app_cust_config.we1_driver_cfg.s_ext_int_mask;
 * 		aCfg.iccm_retention = 1;
 * 		aCfg.dccm_retention = 1;
 * 		aCfg.xccm_retention = 1;
 * 		aCfg.yccm_retention = 1;
 * 		aCfg.skip_bootflow = 0;
 * 		aCfg.support_bootwithcap = 0;
 * 		aCfg.mclk_alwayson = 0;
 * 		aCfg.flash_pad_high = 1;
 * 		aCfg.ultra_lowpower = 0;
 * 		aCfg.support_debugdump = 0;
 *
 * 		hx_lib_pm_mode_set(aCfg);
 *
 * Ex2: PMU GPIO Wakeup Setting
 * 		PM_CFG_T aCfg;
 * 		aCfg.mode = PM_MODE_GPIO;
 * 		aCfg.sensor_rtc = 0;
 * 		aCfg.pmu_timeout = 0;
 * 		aCfg.adc_rtc = 0;
 * 		aCfg.adc_timeout = 0;
 * 		aCfg.powerplan = PMU_WE1_POWERPLAN_INTERNAL_LDO; //
 * 		aCfg.io_mask = 0x1FD;  //P-GPIO1 no Interrupt mask
 * 		aCfg.bootromspeed = PMU_BOOTROMSPEED_PLL_400M_50M;
 * 		aCfg.s_ext_int_mask = 0;
 * 		aCfg.iccm_retention = 0;
 * 		aCfg.dccm_retention = 0;
 * 		aCfg.xccm_retention = 0;
 * 		aCfg.yccm_retention = 0;
 * 		aCfg.skip_bootflow = 0;
 * 		aCfg.support_bootwithcap = 0; //GPIO wakeup can select
 * 		aCfg.mclk_alwayson = 0;
 * 		aCfg.ultra_lowpower = 0;
 * 		aCfg.support_debugdump = 0;
 *
 * 		hx_lib_pm_mode_set(aCfg);
 *
 * Ex3: PMU Prerolling GPIO Wakeup Setting
 * 		PM_CFG_T aCfg;
 * 		aCfg.mode = PM_MODE_AOS_ONLY;
 * 		aCfg.sensor_rtc = 500;
 * 		aCfg.pmu_timeout = 500;
 * 		aCfg.adc_rtc = 0;
 * 		aCfg.adc_timeout = 0;
 * 		aCfg.powerplan = PMU_WE1_POWERPLAN_INTERNAL_LDO; //
 * 		aCfg.io_mask = 0x1FD;  //P-GPIO1 no Interrupt mask
 * 		aCfg.bootromspeed = PMU_BOOTROMSPEED_PLL_400M_50M;
 * 		aCfg.s_ext_int_mask = 0
 * 		aCfg.iccm_retention = 1;
 * 		aCfg.dccm_retention = 1;
 * 		aCfg.xccm_retention = 1;
 * 		aCfg.yccm_retention = 1;
 * 		aCfg.skip_bootflow = 1;
 * 		aCfg.support_bootwithcap = 0;
 * 		aCfg.mclk_alwayson = 0;
 * 		aCfg.flash_pad_high = 1;
 * 		aCfg.ultra_lowpower = 0;
 * 		aCfg.support_debugdump = 0;
 *
 * 		hx_lib_pm_mode_set(aCfg);
 *
 * Ex4: PMU Timer Wakeup Setting
 * 		PM_CFG_T aCfg;
 * 		aCfg.mode = PM_MODE_TIMER_QUICKBOOT;
 * 		aCfg.sensor_rtc = 10000;
 * 		aCfg.pmu_timeout = 0;
 * 		aCfg.adc_rtc = 0;
 * 		aCfg.adc_timeout = 0;
 * 		aCfg.powerplan = PMU_WE1_POWERPLAN_INTERNAL_LDO; //
 * 		aCfg.io_mask = io_mask;  //GPIO Interrupt mask
 * 		aCfg.bootromspeed = PMU_BOOTROMSPEED_PLL_400M_50M;
 * 		aCfg.s_ext_int_mask = app_cust_config.we1_driver_cfg.s_ext_int_mask;
 * 		aCfg.iccm_retention = 1;
 * 		aCfg.dccm_retention = 1;
 * 		aCfg.xccm_retention = 1;
 * 		aCfg.yccm_retention = 1;
 * 		aCfg.skip_bootflow = 1;
 * 		aCfg.support_bootwithcap = 0;
 * 		aCfg.mclk_alwayson = 0;
 * 		aCfg.flash_pad_high = 1;
 * 		aCfg.ultra_lowpower = 0;
 * 		aCfg.support_debugdump = 0;
 *
 * 		hx_lib_pm_mode_set(aCfg);
 *
 * 		When firmware boot from PMU to all on, the program flow should be as follow,
 * 		1. hx_lib_pm_pmutoallon_ready_check(a, b, c, d);
 * 		   This function is used to confirm pre-capture is done by PMU.
 * 		   If you don't use pre-capture feature, parameters (a, b, c, d) should be 0.
 * 		   If you use pre-capture feature, you should consider which DMA you use for pre-capture.
 * 		      For example, pre-capture use WDMA2, WDMA3
 * 		           hx_lib_pm_pmutoallon_ready_check(0, 1, 1, 0);
 * 		2. If you need know xDMA information such as current JPEG¡@capture slot, you should store to parameter in this step.
 * 		   After step3, xDMA information in HW registers will be reset.
 * 		    	hx_drv_xdma_get_WDMA2_loopflag(&g_jpegloop_flag);
 * 		    	hx_drv_xdma_get_WDMA2NextFrameIdx(&g_nextjpeg_frame_no);
 * 		    	hx_drv_xdma_get_WDMA2_bufferNo(&g_jpeg_total_slot);
 * 		    	hx_drv_xdma_get_WDMA2FirstFrameCapflag(&g_firstframe_cap);
 * 		3. hx_lib_pm_ctrl_handoverfromPMUtoCPU();
 * 		   This function is set control owner from PMU to CPU and clear some HW status.
 * 		4. After step3, CPU can control all data path function
 * </pre>
 */
/**
 * \defgroup	PWRMGMT_LIB_ENUM	Power Manager Enumeration
 * \ingroup	PWRMGMT_LIB
 * \brief	Defines some enumeration of Power Manager Library need.
 * @{
 */
/****************************************************
 * ENUM Declaration                                 *
 ***************************************************/
/** PMU Errors Type **/
/**
 * \enum PM_ERROR_E
 * \brief PM API ERROR Code
 */
typedef enum PM_ERROR_S
{
	PM_NO_ERROR                     	= 0,	/**< No ERROR */
	PM_ERROR_NOT_INIT              		= 1,	/**< ERROR MSG: not init */
	PM_ERROR_DRIVER						= 2,	/**< ERROR MSG: pmu driver error */
	PM_ERROR_ALREADY_INIT              	= 3,	/**< ERROR MSG: already init */
	PM_ERROR_INVALID_PARAMETERS        	= 4,	/**< ERROR MSG: Invalid parameters */
	PM_ERROR_NULL_POINTER				= 5,	/**< ERROR MSG: NULL pointer */
 	PM_UNKNOWN_ERROR      				= 6,	/**< ERROR MSG: UNKNOWN ERROR*/
} PM_ERROR_E;

/**
 * \enum PM_CFG_PWR_MODE_E
 * \brief Power Manager Configuration Mode
 */
typedef enum PM_CFG_PWR_MODE_S
{
	PM_MODE_ALL_ON = 0,	/**< All on without any configuration for Power Management**/
	PM_MODE_AOS_ADC_BOTH,	/**< AOS Mode and ADC both to wake up to All on**/
	PM_MODE_AOS_ONLY,	/**< CDM Mode Only to wake up to All on **/
	PM_MODE_GPIO,		/**< GPIO Only to wake up to All On such as Digital PIR**/
	PM_MODE_ADC_ONLY,		/**< ADC Only to wake up to All On such as Analog PIR**/
	PM_MODE_RTC,		/**< Periodical wake up to PS_ALL**/
	PM_MODE_PERIODICAL_CAP_QUICKBOOT,		/**< Periodical capture and quick wake up to PS_ALL**/
	PM_MODE_TIMER_QUICKBOOT,		/**< Timer quick wake up to PS_ALL**/
	PM_MODE_CPU_SLEEP,  /**< CPU Sleep wait Interrupt wake up CPU**/
} PM_CFG_PWR_MODE_E;

/**
 * \enum PM_CFG_PMU_TYPE_E
 * \brief Power Manager Configuration PMU TYPE
 */
typedef enum PM_CFG_PMU_TYPE_S
{
	PM_CFG_PMU_TYPE_PSALL 				= 0,    		/**< PMU Type - PS_ALL*/
	PM_CFG_PMU_TYPE_SD_PSALL_1 			= 1,        /**< PMU Type - SD->PS_ALL (0001)*/
	PM_CFG_PMU_TYPE_PSSLP2_PSALL_2 		= 2,        /**< PMU Type - PS_SLP2-> PS_ALL (0010)*/
	PM_CFG_PMU_TYPE_PSSLP1_PSALL_3 		= 3,        /**< PMU Type - PS_SLP1-> PS_ALL (0011) */
	PM_CFG_PMU_TYPE_PSSLP1_EXP_CAP_4 	= 4,        /**< PMU Type - PS_SLP1->EXP->CAP (only Support AOS) (0100) */
	PM_CFG_PMU_TYPE_PSSLP1_EXP_8 		= 8,        /**< PMU Type - PS_SLP1-> EXP (only Support ADC) (1000) */
	PM_CFG_PMU_TYPE_PSSLP1_EXP_CAP_12 	= 12,        /**< PMU Type - PS_SLP1-> EXP-> CAP (both Support AOS and ADC) (1100) */
} PM_CFG_PMU_TYPE_E;

/**
 * \enum PMU_GPIO_MASK_BIT_E
 * \brief Power Manager GPIO Mask Bit (1:mask, 0:unmask)
 */
typedef enum PMU_GPIO_MASK_BIT_S
{
	PMU_GPIO_MASK_BIT_PGPIO0 = 0, /*[0]: ext_pgpio0*/
	PMU_GPIO_MASK_BIT_PGPIO1 = 1, /*[1]: ext_pgpio1*/
	PMU_GPIO_MASK_BIT_PGPIO2 = 2, /*[2]: ext_pgpio2*/
	PMU_GPIO_MASK_BIT_PGPIO3 = 3, /*[3]: ext_pgpio3*/
	PMU_GPIO_MASK_BIT_PGPIO4 = 4, /*[4]: ext_pgpio4*/
	PMU_GPIO_MASK_BIT_PGPIO5 = 5, /*[5]: ext_pgpio5*/
	PMU_GPIO_MASK_BIT_PGPIO6 = 6, /*[6]: ext_pgpio6*/
	PMU_GPIO_MASK_BIT_SGPIO0 = 7, /*[7]: ext_sgpio0*/
	PMU_GPIO_MASK_BIT_SGPIO1 = 8, /*[8]: ext_sgpio1*/
}PMU_GPIO_MASK_BIT_E;

/**
 * \enum PMU_DP_ABNORMAL_MASK_BIT_E
 * \brief Power Manager DP Abnormal Mask Bit (1:mask, 0:unmask)
 *
 */
typedef enum
{
	PMU_DP_ABNORMAL_MASK_BIT_WDMA1 = 0, /*[0]: wdma1 abnormal*/
	PMU_DP_ABNORMAL_MASK_BIT_WDMA2 = 1, /*[1]: wdma2 abnormal*/
	PMU_DP_ABNORMAL_MASK_BIT_WDMA3 = 2, /*[2]: wdma3 abnormal*/
	PMU_DP_ABNORMAL_MASK_BIT_RDMA = 3, /*[3]: rdma abnormal*/
}PMU_DP_ABNORMAL_MASK_BIT_E;

/**
 * \enum PMU_DP_NORMAL_MASK_BIT_E
 * \brief Power Manager DP normal Mask Bit (1:mask, 0:unmask)
 *
 */
typedef enum
{
	PMU_DP_NORMAL_MASK_BIT_WDMA1 = 0, /*[0]: wdma1 normal*/
	PMU_DP_NORMAL_MASK_BIT_WDMA2 = 1, /*[1]: wdma2 normal*/
	PMU_DP_NORMAL_MASK_BIT_WDMA3 = 2, /*[2]: wdma3 normal*/
	PMU_DP_NORMAL_MASK_BIT_RDMA = 3, /*[3]: rdma normal*/
}PMU_DP_NORMAL_MASK_BIT_E;

/**
 * \enum PMU_DP_AND_NORMAL_MASK_BIT_E
 * \brief Power Manager DP normal Mask Bit (1:mask, 0:unmask)
 *
 */
typedef enum
{
	PMU_DP_AND_NORMAL_MASK_BIT = 0, /*[0]: And xDMA all interrupt mask*/
}PMU_DP_AND_NORMAL_MASK_BIT_E;

/**
 * \enum PMU_WE1_POWERPLAN_E
 * \brief Power Manager Power Plan (0:External LDO)
 *
 */
typedef enum
{
	PMU_WE1_POWERPLAN_EXTERNAL_LDO = 0, /*Power Plan 1 External LDO*/
	PMU_WE1_POWERPLAN_INTERNAL_LDO = 1, /*Power Plan 2 Internal LDO*/
}PMU_WE1_POWERPLAN_E;
/** @} */

/****************************************************
 * Structure Definition                             *
 ***************************************************/
/**
 * \defgroup	PWRMGMT_LIB_REGSTRUCT		Power Manager Library Structure
 * \ingroup	PWRMGMT_LIB
 * \brief	contains definitions of Power Manager library structure.
 * @{
 */

/**
 * \struct PM_CFG_T
 * \brief Power manager configuration
 */
typedef struct PM_CFG_S{
	PM_CFG_PWR_MODE_E mode;					/**< /ref PM_CFG_PWR_MODE_E **/
	uint32_t	sensor_rtc;					/**< sensor rtc timer setting(ms) to trigger RTC_timer_int **/
	uint32_t	adc_rtc;					/**< adc rtc timer setting(ms) to trigger RTC_timer_int **/
	uint32_t	pmu_timeout;				/**< pmu watchdog timeout setting(ms) to trigger pmu_wdg_timeout_int **/
	uint32_t	adc_timeout;				/**< pmu adc timeout setting(ms) to trigger ADC_timeout_int **/
	PMU_WE1_POWERPLAN_E powerplan;         /**< pmu power plan **/
	PMU_BOOTROMSPEED_E bootromspeed;       /**< boot rom Speed **/
	uint16_t	io_mask;	/**< PMU gpio Interrupt Mask **/
	uint8_t 	s_ext_int_mask;	/**< PMU Sensor External Interrupt Mask **/
	uint8_t 	iccm_retention;		/**< Only Support in PM_MODE_AOS_ADC_BOTH, PM_MODE_AOS_ONLY, PM_MODE_ADC_ONLY, PM_MODE_PERIODICAL_CAP_QUICKBOOT**/
	uint8_t 	dccm_retention;		/**< Only Support in PM_MODE_AOS_ADC_BOTH, PM_MODE_AOS_ONLY, PM_MODE_ADC_ONLY, PM_MODE_PERIODICAL_CAP_QUICKBOOT**/
	uint8_t 	xccm_retention;		/**< Only Support in PM_MODE_AOS_ADC_BOTH, PM_MODE_AOS_ONLY, PM_MODE_ADC_ONLY, PM_MODE_PERIODICAL_CAP_QUICKBOOT**/
	uint8_t 	yccm_retention;		/**< Only Support in PM_MODE_AOS_ADC_BOTH, PM_MODE_AOS_ONLY, PM_MODE_ADC_ONLY, PM_MODE_PERIODICAL_CAP_QUICKBOOT**/
	uint8_t 	skip_bootflow;		/**< Only Support in PM_MODE_AOS_ADC_BOTH, PM_MODE_AOS_ONLY, PM_MODE_ADC_ONLY, PM_MODE_PERIODICAL_CAP_QUICKBOOT and ICCM retention on**/
	uint8_t 	support_bootwithcap;		/**< Support capture when boot up (PM_MODE_GPIO and PM_MODE_RTC support only)**/
	uint8_t 	mclk_alwayson;		/**< Support 1(Non-AOS): mclk always on even in SD, SLP2, SLP1, 0: control by PMU**/
	uint8_t  	disable_xtal24M;    /**< For ultra low power Disable XTAL24M but you need to confirm MCLK is from RC36M and RC36M is trimmed**/
	uint8_t  	peripheral_pad_as_input;    /**< For ultra low power, let all peripheral PADs(not include PGPIO) as input mode in PMU**/
	uint8_t  	flash_pad_high;    /**< For ultra low power, let CSN is high, flash in standby mode in PMU(RevB Chip only support in Skip Boot flow case)**/
	uint8_t 	support_debugdump;			/**< Support debug register dump**/
	uint8_t 	ultra_lowpower;			/**< ultra low power only support in SD/SLP2. SLP1 no effect**/
}PM_CFG_T;
/** @} */



/****************************************************
 * Function Declaration                             *
 ***************************************************/
/**
 * \defgroup	PWRMGMT_LIB_FUNCDLR	Power Manager library Function Declaration
 * \ingroup	PWRMGMT_LIB
 * \brief	Contains declarations of Power Manager library functions.
 * @{
 */

/**
 * \brief	Initialization of power manager library
 *
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_init(void);

/**
 * \brief	De-Initialization of power manager library
 *
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_deinit(void);


/**
 * \brief	check PMU done capture frame done when PMU to ALLON.
 *
 *
 * \param[in] wdma1_use		WDMA1 is used in PMU mode or not (1: used, 0: not used)
 * \param[in] wdma2_use		WDMA2 is used in PMU mode or not (1: used, 0: not used)
 * \param[in] wdma3_use		WDMA3 is used in PMU mode or not (1: used, 0: not used)
 * \param[in] rdma_use		RDMA is used in PMU mode or not (1: used, 0: not used)
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_pmutoallon_ready_check(uint8_t wdma1_use, uint8_t wdma2_use, uint8_t wdma3_use, uint8_t rdma_use);

/**
 * \brief	hand over control from PMU to CPU. Then CPU can control everything
 *
 *
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_ctrl_handoverfromPMUtoCPU();


/**
 * \brief	Configure the power manager library for specific power mode
 *
 * \param[in] PM_CFG_T		configuration of power mode
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_get_defcfg_bymode(PM_CFG_T *aCfg, PM_CFG_PWR_MODE_E mode);

/**
 * \brief	Configure the power manager library for specific power mode
 *
 * \param[in] PM_CFG_T		configuration of power mode
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_mode_set(PM_CFG_T aCfg);

/**
 * \brief	Get Current power mode in the power manager library
 *
 * \param[out] PM_CFG_T		configuration of power mode
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_mode_get(PM_CFG_T *aCfg);



/**
 * \brief	The function is used to trigger to enter PMU mode. It is handled by PMU library hx_lib_pm_mode_set so application doesn't need take care it.
 *
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_trigger(void);

/**
 * \brief	The function is used to get the PMU wake up event
 *
 * \param[out] aWakeupEvt	store the PMU wakeup event
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_get_event(uint32_t *aWakeupEvt);

/**
 * \brief	The function is used to clear the PMU wake up event flag
 *
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_clear_event(void);

/**
 * \brief	The function is used to perform CPU software reset
 *
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_cpu_rst(void);

/**
 * \brief	The function is used to perform Chip reset
 *
 * \param[in] powerplan	WE-1 is internal LDO or External LDO
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_chip_rst(PMU_WE1_POWERPLAN_E powerplan);

/**
 * \brief	The function is used to deinitial some BSP driver for retention reboot. It is handled by PMU library hx_lib_pm_mode_set so application doesn't need take care it.
 *
 */
void hx_lib_pm_deinit_bsp_driver();

/**
 * \brief	The function is used to Control CLDO switch
 *
 * \param[in] cldo_en	WE-1 CLDO Enable Control
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_cldo_en(uint8_t cldo_en);

/**
 * \brief	The function is used to destructor cplus;
 *
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_cplus_deinit();


/**
 * \brief	The function is used to convert decrease value to OTP value
 *
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_get_ultralowpower_level(uint8_t decrease_val, uint8_t *level);

/**
 * \brief	The function is used to get slt decrease val
 *
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_get_slt_decreaseval(uint8_t *decrease_val);

/**
 * \brief	The function is used to set slt decrease val
 *
 * \retval	PM_NO_ERROR		success
 * \retval	others			fail
 */
PM_ERROR_E hx_lib_pm_set_slt_decreaseval(uint8_t decrease_val);


/** @} */


#endif /* LIBRARY_PWRMGMT_POWERMODE_H_ */

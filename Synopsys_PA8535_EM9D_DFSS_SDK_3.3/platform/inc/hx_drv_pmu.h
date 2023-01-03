/*
 * hx_drv_pmu.h
 *
 *  Created on: 2019¦~1¤ë18¤é
 *      Author: 902452
 */

#ifndef PLATFORM_INC_HX_DRV_PMU_H_
#define PLATFORM_INC_HX_DRV_PMU_H_

/**
 * \defgroup	PMU_DRV	Power Management Driver
 * \ingroup		PMU_DRV
 * \brief	Power Management Driver Declaration
 * \details Application can use PMU driver Data Structure and Power Management library to control WE-1 Power Management\n
 */
/**
 * \defgroup	PMU_DRV_MACRO	Power Management Driver MACRO
 * \ingroup	PMU_DRV
 * \brief	contains definitions of Power Management Driver MACRO.
 * @{
 */

#define PMU_CHIP_VERSION_A          0x008535A0
#define PMU_CHIP_VERSION_B          0x008535A1
#define PMU_CHIP_VERSION_C          0x0C8535A1

#define PMU_EN						1
#define PMU_DIS						0

#define PMU_MODE_PMU				0
#define PMU_MODE_WDT				1

#define PMU_CTRL_GET				0
#define PMU_CTRL_SET				1
/** @} */

/**
 * \defgroup	HWACC_RS_DRV_ENUM	RS Driver Enumeration
 * \ingroup	HWACC_RS_DRV
 * \brief	Defines some enumeration of RS Driver need.
 * @{
 */
/**
 * \enum PMU_INT_INDEX_E
 * \brief PMU Interrupt SRC Type
 */
typedef enum PMU_INT_INDEX_S
{
	PMU_INT_RC36_FINISH = 0,
	PMU_INT_RC36_DONE,
	PMU_INT_RC36_ERR,
	PMU_INT_RC32_FINISH = 0,
	PMU_INT_RC32_DONE,
	PMU_INT_RC32_ERR,
	PMU_INT_WDT_TIMEOUT,
	PMU_INT_ADC_TIMEOUT,
	PMU_INT_MAX
}PMU_INT_INDEX_E;

/**
 * \enum PMU_PS_E
 * \brief PMU Power State
 */
typedef enum PMU_PS_S
{
	PMU_PS_ALL = 0,
	PMU_PS_CAP,
	PMU_PS_EXP,
	PMU_PS_SLP1,
	PMU_PS_SLP2,
	PMU_PS_SD,
	PMU_PS_MAX
}PMU_PS_E;


/**
 * \enum PMU_CTRL_TYPE_E
 * \brief PMU Power Driver Contrl Type
 */
typedef enum PMU_CTRL_TYPE_S
{
	/* Control Register 90h */
	PMU_REG_CTRL1         		= 0x0000,
	PMU_CPU_EVT_STATE,			// not support after PMU_V3.0
	PMU_CPU_EVT_TRI,
	PMU_PWR_PLAN,
	PMU_CPU_BOOT,
	PMU_SEN_INIT,
	PMU_CAP_NSTATE,				// not support after PMU_V3.0
	PMU_CPU_SCENARIO,
	PMU_ADC_NSTATE,				// not support after PMU_V3.0
	PMU_DC18_EN,				// not support after PMU_V3.0
	PMU_DC09_EN,
	PMU_DC33_EN,
	PMU_DC18_EN_SW,				// not support after PMU_V3.0
	PMU_DC09_EN_SW,
	PMU_DC33_EN_SW,
	PMU_DCDC09_POL,
	PMU_DCDC33_POL,
	PMU_I2C_ID,

	/* Control Register 94h */
	PMU_REG_CTRL2 				= 0x0100,
	PMU_S_FAE,	                // CPU control. connect to PMU_S_FAE (pass through PMU)
	PMU_S_XSLEEP,               // CPU control. connect to PMU_S_XSLEEP (pass through PMU)                                                     
	PMU_S_CXTSW,                // a path controlled by CPU. BIT[2] 0 - sensor w/o output data, BIT[2] 1 - sensor output frame; BIT[3] reserved
	PMU_S_NAOS_MCLK_MUX,        // 1 - For Non-AOS sensor ; 0 - For AOS sensor (MCLK by sensor_ctrl)                                           
	PMU_PRE_CAPTURED_ON,             // REG_PRE_CAPTURED_ON VerB
	PMU_EN_PLL_SW,              // PLL's EN_PLL,PWRGAT, RSTN controlled by CPU(1)/PMU<SLP1,ALL>(0)                                             
	PMU_SLP1_ALL_PLL_EN,        //                                                                                                             
	PMU_CLDO_MODSEL_SW,                                                                                                                        
	PMU_CLDO_MODSEL,                                                                                                                           
	PMU_BOR_09V_EN_SW,          // 1: BOR's BOR_09V_EN controlled by REG_BOR_09V_EN                                                            
	PMU_BOR_09V_EN,                                                                                                                            
	PMU_OSC36M_EN_SW,           // 1: OSC's OSC36M_EN controlled by REG_OSC36M_EN                                                              
	PMU_OSC36M_EN,                                                                                                                             
	PMU_OSC36M_TRIM_EN,                                                                                                                        
	PMU_CDM_INIT_MAP_EN,
	PMU_SLD0_ULPLD_EN_SW,       // 1: CPU control the SLDO_ULPLDO_EN                                                                           
	PMU_SLD0_ULPLD_EN,                                                                                                                         
	PMU_SLD0_ROK_MAN_SW,        // 1: CPU control the SLDO_ROK_MANUAL                                                                          
	PMU_SLD0_ROK_MAN,                                                                                                                          
	PMU_SLD0_MODSEL_SW,         // 1: CPU control the SLDO_MODE_SEL                                                                            
	PMU_SLD0_MODSEL,                                                                                                                           
	PMU_SLD0_VREF_SEL_SW,       // 1: CPU control the SLDO_VREF_SEL                                                                            
	PMU_SLD0_VEFF_SEL,                                                                                                                         
	PMU_S_XSLEEP_SW,            // 1: CPU control the S_XSLEEP (from REG_PMU_S_XSLEEP)                                                         
	PMU_S_CXTSW_SW,             // 1: CPU control the S_CXTSW (from REG_PMU_S_CXTSW)                                                           
	PMU_S_TRIGGER_SW,           // 1: CPU control the S_TRIGGER (from REG_PMU_S_TRIGGER)                                                       
	PMU_S_TRIGGER,              // 1: CPU control S_TRIGGER =1                                                                                 

	/* Control Register 98h */
	PMU_REG_CTRL3          		= 0x0200,
	PMU_WAKE_EVT_CLR,             	// W1C - Clear the record of wakeup_cpu_event_pmu
	PMU_ADC_RSTN_INC_CLR,         	// W1C - When ADC_active=1, could be OFF by CPU.
	PMU_SEN_RSTN_INT_CLR,         	// W1C - When PMU SEN_active=1, could be clear PMU sen_active =0 by CPU.
	PMU_SIF_PWSW,					// power domain GPIO SIF power gating or not @PS_SD
	PMU_PIF_PWSW,					// power domain GPIO PIF power gating or not @PS_SD
	PMU_ADC_PMU_CTRL_SW,          	// PMU(1)/CPU(0) control ADC IP and ADCC
	PMU_RTC_GC,						// RTC Timer input clock GC or not
	PMU_RC32K_GC,					// RC32K output clock GC or not
	PMU_XTAL32K_GC,					// XTAL32K output clock GC or not
	PMU_RTC_GC_SW,					// PMU(1)/CPU(0) control the RTC clock gating by REG_RTC_GC.
	PMU_RC32K_GC_SW,              	// PMU(1)/CPU(0) control the RC32K clock gating by REG_RC32K_OUT_GC.
	PMU_XTAL32K_GC_SW,				// PMU(1)/CPU(0) control the XTAL32K clock gating by REG_XTAL32K_OUT_GC.
	PMU_XTAL24M_EN_SW,				// 1: CPU control the XTAL24 enable.
	PMU_XTAL24M_EN,					// XTAL24 enable/disable
	PMU_SLDO_VERF_SEL_063V,
	PMU_SLDO_VERF_SEL_090V,
    PMU_CLDO_VREF_SEL_RET,
    PMU_CLDO_VREF_SEL_NORMAL,

	/* Control Register 9Ch */ 
	PMU_REG_INTMASK          	= 0x0300,
	PMU_INT_MASK,            	// Pre-masking of PMU_INT0~8
	PMU_INT_CLR,               	// W1C - Pre-masking of PMU_INT0~8 Clear
	PMU_DMA_ABNORMAL_MASK,     	// Pre-masking of xDMAx_abnormal_int
	PMU_DMA_CFG,	           	// DMA CONFIG for ANDs 4 DMAs Int together to PMU
	PMU_DMA_CFG_MASK,			// All these INT ANDs together mean DMAs finish and issue INT to PMU.
	REG_PMU_S_INT_MASK,         //Pre-masking of PMU_S_INT (which from Sensor Int to PMU path)

	/* COntrol Register  A0h */
	PMU_REG_LDO_CTRL1		= 0x0400,
	PMU_TSTABLE_N2R_CLDO,
	PMU_TSTABLE_R2N_CLDO,
	PMU_TSTABLE_N2R_SLDO,
	PMU_TSTABLE_R2N_SLDO,

	/* Control Register A4h */
	PMU_REG_LDO_CTRL2		= 0x0500,
	PMU_TDCSTABLE_SLDO,
	PMU_TVREF2N_SLDO,
	PMU_TWKEUP_SLDO,
	PMU_TROK_DCOFF_SLDO,
	PMU_TDCOFF_RON_SLDO,

	/* Control Register A8h */
	PMU_REG_WAKEUP_EVT			= 0x0600,
	PMU_TDCSTABLE_CLDO,
	PMU_WAKEUP_CPU_EVT_PMU,

	/* Control Register ACh */
	PMU_REG_MEM32_RET_PMU		= 0x0700,
	PMU_MEM32_RET_PMU,

	/* Control Register BOh */
	PMU_REG_MEM46_RET_PMU		= 0x0800,
	PMU_MEM46_RET_PMU,			// not support after PMU_V3.0
	PMU_XCCM_RET_PMU,
	PMU_YCCM_RET_PMU,
	PMU_ICCM_RET_PMU,

	/* Control Register B4h */
	PMU_REG_DCCM_RET_PMU		= 0x0900,
	PMU_DCCM_RET_PMU,
	PMU_TSCTL_PWSW,
	PMU_TCV_PWSW,
	PMU_TRAM_PWSW,

	/* Control Register B8h/BCh */
	/* Control Register B8h */
	PMU_REG_WDT_RTC				= 0x0A00,
	PMU_WDT_RTC_LOAD_COUNTER,
	PMU_WDT_RTC_PRE_SCALE,
	PMU_WDT_RTC_LOAD_EN1T,
	PMU_WDT_RTC_EN,
	PMU_WDT_RTC_INT_MASK,

	/* Control Register BCh */
	PMU_REG_WDT_ADC				= 0x0B00,
	PMU_WDT_ADC_LOAD_COUNTER,
	PMU_WDT_ADC_PRE_SCALE,
	PMU_WDT_ADC_LOAD_EN1T,
	PMU_WDT_ADC_EN,
	PMU_WDT_ADC_INT_MASK,

	/* Control Register C0h */
	PMU_REG_INT					= 0x0C00,
	PMU_PIO_INT_NXT,
	PMU_RTC_PMU_INT_NXT,
	PMU_RTC_ADC_INT_NXT,
	PMU_RC36M_CAL_PMU_MODE,
	PMU_RC32K_CAL_PMU_MODE,
	PMU_WDT_RESETN_EN,

	/* Control Register C4h */
	PMU_REG_CAL_CTRL1			= 0x0D00,
	PMU_CAL_AUTO_TRM_PRD,
	PMU_CAL_TRM_N,
	PMU_CAL_TRM_PRD,
	PMU_CAL_FUN_EN,

	/* Control Register C8h */
	PMU_REG_CAL_CTRL2			= 0x0E00,
	PMU_CAL_TRM_STP,
	PMU_CAL_MANUAL_MODE,
	PMU_CAL_MANUAL_TRIM_SET,
	PMU_CAL_CNT_RANGE,
	PMU_CAL_AUTO_MODE,
	PMU_CAL_DONE_CLR,
	PMU_CAL_CNT_N_RESULT,
	PMU_CAL_OSC36M_OVFINT,
	PMU_CAL_OSC36M_FINISH,
	PMU_CAL_OSC36M_DONE,
	PMU_CAL_OVF_CLR,

	/** MEMORY CPU POWER MODE SETTING **/
	/* Control Register CCh/D0h/D4h */
	PMU_REG_MEM_PW_STATE0		= 0x0F00,
	PMU_SYSMEM_PW_STATE0_GRP1,
	PMU_SYSMEM_PW_STATE0_GRP2,
	PMU_SYSMEM_PW_STATE0_GRP3,
	PMU_SYSMEM_PW_STATE0_GRP4,
	PMU_SYSMEM_PW_STATE0_GRP5,
	PMU_SYSMEM_PW_STATE0_GRP6,
	PMU_SYSMEM_PW_STATE0_GRP7,
	PMU_SYSMEM_PW_STATE0_GRP8,
	PMU_SYSMEM_PW_STATE0_GRP9,
	PMU_SYSMEM_PW_STATE0_GRP10,
	PMU_SYSMEM_PW_STATE0_GRP11,
	PMU_SYSMEM_PW_STATE0_GRP12,
	PMU_SYSMEM_PW_STATE0_GRP13,
	PMU_SYSMEM_PW_STATE0_GRP14,
	PMU_SYSMEM_PW_STATE0_GRP15,
	PMU_SYSMEM_PW_STATE0_GRP16,

	/* Control Register D0h */
	PMU_REG_MEM_PW_STATE1		= 0x1000,
	PMU_SYSMEM_PW_STATE0_GRP17,
	PMU_SYSMEM_PW_STATE0_GRP18,
	PMU_SYSMEM_PW_STATE0_GRP19,
	PMU_SYSMEM_PW_STATE0_GRP20,
	PMU_SYSMEM_PW_STATE0_GRP21,
	PMU_SYSMEM_PW_STATE0_GRP22,
	PMU_SYSMEM_PW_STATE0_GRP23,
	PMU_SYSMEM_PW_STATE0_GRP24,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP25,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP26,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP27,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP28,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP29,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP30,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP31,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP32,		// not support after PMU_V3.0

	/* Control Register D4h */
	PMU_REG_MEM_PW_STATE2		= 0x1100,
	PMU_SYSMEM_PW_STATE0_GRP33,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP34,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP35,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP36,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP37,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP38,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP39,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP40,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP41,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP42,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP43,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP44,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP45,		// not support after PMU_V3.0
	PMU_SYSMEM_PW_STATE0_GRP46,		// not support after PMU_V3.0
	PMU_XCCM_PW_STATE,
	PMU_YCCM_PW_STATE,

	/* Control Register D8h */
	PMU_REG_MEM_PW_STATE3		= 0x1200,
	PMU_ICCM_PW_STATE0_GRP1,
	PMU_ICCM_PW_STATE0_GRP2,
	PMU_ICCM_PW_STATE0_GRP3,
	PMU_ICCM_PW_STATE0_GRP4,
	PMU_ICCM_PW_STATE0_GRP5,
	PMU_ICCM_PW_STATE0_GRP6,
	PMU_ICCM_PW_STATE0_GRP7,
	PMU_ICCM_PW_STATE0_GRP8,
	PMU_ICCM_PW_STATE0_GRP9,
	PMU_ICCM_PW_STATE0_GRP10,

	/* Control Register DCh */
	PMU_REG_MEM_PW_STATE4		= 0x1300,
	PMU_DCCM_PW_STATE0_GRP1,
	PMU_DCCM_PW_STATE0_GRP2,
	PMU_DCCM_PW_STATE0_GRP3,
	PMU_DCCM_PW_STATE0_GRP4,
	PMU_DCCM_PW_STATE0_GRP5,
	PMU_DCCM_PW_STATE0_GRP6,
	PMU_DCCM_PW_STATE0_GRP7,
	PMU_DCCM_PW_STATE0_GRP8,

	/* Control Register E0h */
	PMU_REG_WDT_RTC_COUNT		= 0x1400,
	PMU_WDT_RTC_CUR_COUNT,

	/* Control Register E4h */
	PMU_REG_WDT_ADC_COUNT		= 0x1500,
	PMU_WDT_ADC_CUR_COUNT,

	/* Control Register E8h */
	PMU_REG_PMU_STATE			= 0x1600,
	PMU_PMU_STATE_EXT_INT,
	PMU_PMU_STATE_DBG_BUS,
	PMU_PMU_STATE_OSC36_TREM,
	PMU_PMU_STATE_RC32K_TREM,

	/* Control Register ECh */
	PMU_REG_RC32_CAL_CTRL1		= 0x1700,
	PMU_RC32K_CAL_AUTO_TRM_PRD,
	PMU_RC32K_CAL_TRM_N,
	PMU_RC32K_CAL_PMU_TRM_PRD,
	PMU_RC32K_CAL_FUNC_EN,

	/* Control Register F0h */
	PMU_REG_RC32_CAL_CTRL2		= 0x1800,
	PMU_RC32K_CAL_TRM_STP,
	PMU_RC32K_CAL_MANUAL_MODE,
	PMU_RC32K_CAL_MANUAL_TRIM_SET,
	PMU_RC32K_CAL_CNT_RANGE,
	PMU_RC32K_CAL_AUTO_MODE_EN,
	PMU_RC32K_CAL_DONE_CLR,
	PMU_RC32K_CAL_CNT_N_RST,
	PMU_RC32K_CAL_OVF_INT,
	PMU_RC32K_CAL_FINISH,
	PMU_RC32K_CAL_DONE,
	PMU_RC32K_CAL_OVF_CLR,

	/* Control Register FCh */
	PMU_BOOT_OPTION				= 0x1900,
	PMU_CHIP_VERSION,
	PMU_CTRL_TYPE_MAX
} PMU_CTRL_TYPE_E;

/**
 * \enum PMU_WAKEUP_E
 * \brief PMU Trigger wakeup to all on event
 */
typedef enum PMU_WAKEUP_S
{
	PMU_WAKEUP_NONE                     = 0x0,
	PMU_WAKEUP_SD_I2C_EXTFORCE 			= 0x1,  	//[0] : PS_SD : wakeup by (i2c_fsm_sd_all_trig || ext_force_pmu_allon)
	PMU_WAKEUP_SD_EXTGPIO	   			= 0x2,  	//[1] : PS_SD wakeup by ext_int_nxt_all(GPIO)
	PMU_WAKEUP_SD_S_EXT_INT	    		= 0x4,  	//[2]: PS_SD wakeup by REG_CPU_SCENARIO=4'b0001&S_EXT_INT
	PMU_WAKEUP_SLP2_I2C_EXTFORECE  		= 0x8,  	//[3]: PS_SLP2 wakeup by i2c_fsm_slp2_all_trig || ext_force_pmu_allon
	PMU_WAKEUP_SLP2_EXTGPIO				= 0x10, 	//[4]: PS_SLP2 wakeup by ext_int_nxt_all(GPIO)
	PMU_WAKEUP_SLP2_S_EXT_INT			= 0x20, 	//[5]: PS_SLP2 wakeup by REG_CPU_SCENARIO=4'b0010&S_EXT_INT
	PMU_WAKEUP_SLP2_SENRTC 				= 0x40, 	//[6]: PS_SLP2 wakeup by REG_CPU_SCENARIO=4'b0010& RTC_timer
	PMU_WAKEUP_SLP2_ADCRTC				= 0x80,  	//[7]: PS_SLP2 wakeup by REG_CPU_SCENARIO=4'b0010& RTC_ADC_timer_int
	PMU_WAKEUP_SLP1_I2C_EXTFORCE   		= 0x100, 	//[8]: PS_SLP1 wakeup by i2c_fsm_slp1_all_trig || ext_force_pmu_allon
	PMU_WAKEUP_SLP1_EXTGPIO				= 0x200, 	//[9]: PS_SLP1 wakeup by ext_int_nxt_all(GPIO)
	PMU_WAKEUP_SLP1_SEXTINTSC4_RTCSC5	= 0x400,	//[10]: PS_SLP1 wakeup by (Sensor_EXT_INT && REG_CPU_SCENARIO[3:0]==4'b0011 && REG_SENCTRL_MODE==3'd4)|| (RTC_timer_int  && REG_CPU_SCENARIO[3:0]==4'b0011 && REG_SENCTRL_MODE==3'd5)
	PMU_WAKEUP_SLP1_ADCRTC_SC45			= 0x800,	//[11]: PS_SLP1 wakeup by (RTC_ADC_timer_int && REG_CPU_SCENARIO[3:0]==4'b0011 && (REG_SENCTRL_MODE==3'd4 ||  REG_SENCTRL_MODE==3'd5)
	PMU_WAKEUP_EXP_I2C_EXTFORCE_WDG		= 0x1000,   //[12]: PS_EXP wakeup by i2c_fsm_exp_all_trig || ext_force_pmu_allon || pmu_wdg_timeout_int )
	PMU_WAKEUP_EXP_CPU8ADCINT_CPU12ADC	= 0x2000,	//[13]: PS_EXP wakeup by ((REG_CPU_SCENARIO==4'b1000 && ADCC_int) ||(REG_CPU_SCENARIO==4'b1100 && ~pmu_sen_active && ADCC_int))
	PMU_WAKEUP_CAP_I2C_FORCE_WDG		= 0x4000,	//[14]: PS_CAP wakeup by i2c_fsm_cap_all_trig || ext_force_pmu_allon || pmu_wdg_timeout_int
	PMU_WAKEUP_CAP_XDMA_ABN_INT			= 0x8000,	//[15]: PS_CAP wakeup by WRDMAx_abnormal_int
	PMU_WAKEUP_CAP_DP_ABN_INT			= 0x10000, 	//[16]: PS_CAP wakeup by DP_ABNORMAL_INT
	PMU_WAKEUP_CAP_CPU4_CDM_MOTION		= 0x20000,  //[17]: PS_CAP wakeup by (REG_CPU_SCENARIO==4'b0100 && SC_nframe_end && all_cfg_xDMAx_int && DP_CDM_MOTION_INT)
	PMU_WAKEUP_CAP_CPU12_CDM_ADCINT  	= 0x40000,  //[18]: PS_CAP wakeup by(REG_CPU_SCENARIO==4'b1100 && SC_nframe_end && all_cfg_xDMAx_int && DP_CDM_MOTION_INT && pmu_adc_active && ACC_int)
	PMU_WAKEUP_CAP_CPU12_CDM_ADCNOINT	= 0x80000, 	//[19]: PS_CAP wakeup by (REG_CPU_SCENARIO==4'b1100 && SC_nframe_end && all_cfg_xDMAx_int && DP_CDM_MOTION_INT && pmu_adc_active && ADC_timeout && ~ADCC_int)
	PMU_WAKEUP_CAP_CPU12_CDM_NOADC		= 0x100000,	//[20]: PS_CAP wakeup by (REG_CPU_SCENARIO==4'b1100 && SC_nframe_end && all_cfg_xDMAx_int && DP_CDM_MOTION_INT && ~pmu_adc_active)
	PMU_WAKEUP_CAP_CPU12_NOMOTION_ADCINT =0x200000//[21]: PS_CAP wakeup by (REG_CPU_SCENARIO==4'b1100 && SC_nframe_end && all_cfg_xDMAx_int && ~DP_CDM_MOTION_INT && ADCC_int)
}PMU_WAKEUPEVENT_E;

/**
 * \enum PMU_ERROR_E
 * \brief PMU Errors Type
 */
typedef enum PMU_ERROR_S
{
	PMU_NO_ERROR                     	= 0,	/**< No ERROR */
	PMU_ERROR_NOT_INIT              	= 1,	/**< ERROR MSG: not init */
	PMU_ERROR_ALREADY_INIT              = 2,	/**< ERROR MSG: already init */
	PMU_ERROR_INVALID_PARAMETERS        = 3,	/**< ERROR MSG: Invalid parameters */
	PMU_ERROR_NULL_POINTER				= 4,	/**< ERROR MSG: NULL pointer */
 	PMU_UNKNOWN_ERROR      				= 5,	/**< ERROR MSG: UNKNOWN ERROR*/
} PMU_ERROR_E;

/**
 * \enum PMU_TIMEOUT_E
 * \brief PMU Timeout Type WDT is for CIS Sensor, ADC is for ADC sampling timeout
 */
typedef enum PMU_TIMEOUT_S
{
	PMU_TIMEOUT_WDT = 0,  /**< Timeout for CIS sensor capture frame */
	PMU_TIMEOUT_ADC = 1   /**< Timeout for ADC sampling data */
}PMU_TIMEOUT_E;

/**
 * \enum PMU_EXT_INT_E
 * \brief PMU GPIO wakeup to all on Interrupt Source
 */
typedef enum PMU_EXT_INT_S
{
	PMU_EXT_INT_PGPIO0_INT = 0x1, /**< [0]: ext_pint0*/
	PMU_EXT_INT_PGPIO1_INT = 0x2, /**< [1]: ext_pint1*/
	PMU_EXT_INT_PGPIO2_INT = 0x4, /**< [2]: ext_pint2*/
	PMU_EXT_INT_PGPIO3_INT = 0x8, /**< [3]: ext_pint3*/
	PMU_EXT_INT_PGPIO4_INT = 0x10, /**< [4]: ext_pint4*/
	PMU_EXT_INT_PGPIO5_INT = 0x20, /**< [5]: ext_pint5*/
	PMU_EXT_INT_PGPIO6_INT = 0x40, /**< [6]: ext_pint6*/
	PMU_EXT_INT_SGPIO0_INT = 0x80, /**< [7]: ext_sint0*/
	PMU_EXT_INT_SGPIO1_INT = 0x100, /**< [8]: ext_sint1*/
}PMU_EXT_INT_E;

/**
 * \enum PMU_BOOTFLOW_E
 * \brief PMU Boot up to allon flow selection (OTA: not use in PMU wakeup boot)
 */
typedef enum PMU_BOOTFLOW_S
{
	PMU_BOOTFLOW_FROM_FLASH,	/**< BootRom and Bootloader move code from flash*/
	PMU_BOOTFLOW_FROM_OTA,		/**< Over The Air update code not use in PMU wakeup*/
	PMU_BOOTFLOW_FROM_RETENTION /**< BootRom and Bootloader run code directly by memory retention*/
}PMU_BOOTFLOW_E;

/**
 * \enum PMU_BOOTROMSPEED_E
 * \brief PMU Boot up to allon Speed Selection
 */
typedef enum PMU_BOOTROMSPEED_S
{
	PMU_BOOTROMSPEED_DISABLE_PLL, /**< bit[9:8] 00b -> disable PLL*/
	PMU_BOOTROMSPEED_PLL_400M_50M,/**< bit[9:8] 01b -> 400M/50M(AHB1/SSI)*/
	PMU_BOOTROMSPEED_PLL_400M_25M,/**< bit[9:8] 10b -> 400M/25M(AHB1/SSI)*/
	PMU_BOOTROMSPEED_PLL_200M_25M,/**< bit[9:8] 11b -> 200M/25M(AHB1/SSI)*/
}PMU_BOOTROMSPEED_E;

typedef enum PMU_POWERPLAN_S
{
	PMU_POWERPLAN_EXTERNAL = 0,
	PMU_POWERPLAN_INTERNAL,
}PMU_POWERPLAN_E;
/** @} */

/**
 * \defgroup	PMU_DRV_FUNCDLR	Power Management Driver Function Declaration
 * \ingroup	PMU_DRV
 * \brief	Contains declarations of Power Management Driver functions.
 * @{
 */
/**
 * \brief	Power Managements interrupt callback function
 *
 * \param[in]	param	 Power Management interrupt callback event
 * \return	void.
 */
typedef void (*pmu_cb_t) (void* param);

/**
 * \brief	initial Power Management Driver
 *
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_init(void);
/**
 * \brief	de-initial Power Management Driver
 *
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_deinit(void);
/**
 * \brief   Power Management Driver register interrupt callback function
 *
 * \param[in]	aIndex	 Interrupt type
 * \param[in]	aIndex	 Interrupt callback function to upper layer
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_register_cb(PMU_INT_INDEX_E aIndex, pmu_cb_t  cb_fun);
/**
 * \brief   Power Management Driver set control function
 *
 * \param[in]	aCtrl	 Control type
 * \param[in]	aValue	 Control value
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_set_ctrl(PMU_CTRL_TYPE_E aCtrl, uint32_t aValue);
/**
 * \brief   Power Management Driver get control function
 *
 * \param[in]	aCtrl	 Control type
 * \param[out]	param	 Control value
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_get_ctrl(PMU_CTRL_TYPE_E aCtrl, void* param);

/**
 * \brief   Power Management Driver Timeout Set function
 *
 * \param[in]	aType	 Timeout type
 * \param[in]	aTime	 Timeout value
 * \param[in]	aEnable	 Enable Start
 * \param[in]	cb_fun	 Callbcak function to upper layer when interrupt occurs
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_wdt_start(PMU_TIMEOUT_E aType, uint32_t aTime, uint8_t aEnable, pmu_cb_t  cb_fun);
/**
 * \brief   Power Management Driver Timeout Stop function
 *
 * \param[in]	aType	 Timeout type
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_wdt_stop(PMU_TIMEOUT_E aType);
/**
 * \brief   Power Management Driver get wakeup to allon event function
 *
 * \param[out]	wakeup_event	 Wakeup event value
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_get_wakeupevt(PMU_WAKEUPEVENT_E *wakeup_event);
/**
 * \brief   Power Management Driver after PMU wake up to all on, check PMU already done ADC path function
 *
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_set_ADCResetNClr();
/**
 * \brief   Power Management Driver after PMU wake up to all on, check PMU already done Sensor path function
 *
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_set_SenResetNClr();

PMU_ERROR_E hx_drv_pmu_set_ADCTimerWorkaound(uint32_t val);
PMU_ERROR_E hx_drv_pmu_set_SenTimerWorkaound(uint32_t val);
PMU_ERROR_E hx_drv_pmu_get_ADCTimerWorkaound(uint32_t *val);
PMU_ERROR_E hx_drv_pmu_get_SenTimerWorkaound(uint32_t *val);


/**
 * \brief   Power Management Driver for application test purpose function
 *
 * \param[in]	val	 0 ~ 31
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_firmware_test_set(uint16_t val);
/**
 * \brief   Power Management Driver for application test purpose function
 *
 * \param[out]	val	 0 ~ 31
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_firmware_test_get(uint16_t *val);
/**
 * \brief   Power Management Driver set PMU wake up boot flow function
 *
 * \param[in]	boot_flow	 boot flow selection
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_set_bootflow(PMU_BOOTFLOW_E boot_flow);
/**
 * \brief   Power Management Driver get PMU wake up boot flow function
 *
 * \param[out]	boot_flow	 boot flow selection
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_get_bootflow(PMU_BOOTFLOW_E *boot_flow);
/**
 * \brief   Power Management Driver Set PLL Disable/Enable function
 *
 * \param[in]	pll_enable	 PLL enable/disable
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_set_pllenable(uint8_t pll_enable);
/**
 * \brief   Power Management Driver Get PLL Disable/Enable function
 *
 * \param[out]	pll_enable	 PLL enable/disable
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_get_pllenable(uint8_t *pll_enable);

/**
 * \brief   Power Management Driver set after PMU wakeup to all ons move code by XIP or EIP function
 *
 * \param[in]	xip_by_eip	 1: use eip, 0: use xip
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_set_xipbyeip(uint8_t xip_by_eip);
/**
 * \brief   Power Management Driver get after PMU wakeup to all ons move code by XIP or EIP function
 *
 * \param[out]	xip_by_eip	 1: use eip, 0: use xip
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_get_xipbyeip(uint8_t *xip_by_eip);

/**
 * \brief   Power Management Driver set bootrom speed after PMU wakeup function
 *
 * \param[in]	bootromspeed	bootrom speed
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_set_bootromspeed(PMU_BOOTROMSPEED_E bootromspeed);
/**
 * \brief   Power Management Driver get bootrom speed after PMU wakeup function
 *
 * \param[out]	bootromspeed	bootrom speed
 * \return	PMU_ERROR_E.
 */
PMU_ERROR_E hx_drv_pmu_get_bootromspeed(PMU_BOOTROMSPEED_E *bootromspeed);
/** @} */

#endif /* PLATFORM_INC_HX_DRV_PMU_H_ */

/*
 * hx_drv_pmu_reg.h
 *
 *  Created on: 2019¦~8¤ë20¤é
 *      Author: 902452
 */

#ifndef SYS_PMU_HX_DRV_PMU_REG_H_
#define SYS_PMU_HX_DRV_PMU_REG_H_


#define PMU_IP_VERSION	3

/** Register BIT Offset **/
/* Control Register 90h */
#define	PMU_CPU_EVT_STATE_OFFSET	0		// not support after v3.0
#define	PMU_CPU_EVT_TRI_OFFSET		3
#define	PMU_PWR_PLAN_OFFSET			4
#define	PMU_CPU_BOOT_OFFSET			5
#define	PMU_SEN_INIT_OFFSET			6
#define	PMU_CAP_NSTATE_OFFSET		7		// not support after v3.0
#define PMU_CPU_SCENARIO_OFFSET		8
#define	PMU_ADC_NSTATE_OFFSET		12		// not support after v3.0
#define	PMU_DC18_EN_OFFSET			16		// not support after v3.0
#define	PMU_DC09_EN_OFFSET			17
#define	PMU_DC33_EN_OFFSET			18
#define	PMU_DC18_EN_SW_OFFSET		19		// not support after v3.0
#define	PMU_DC09_EN_SW_OFFSET		20
#define	PMU_DC33_EN_SW_OFFSET		21
#define PMU_DC09_POL_OFFSET			22
#define PMU_DC33_POL_OFFSET			23
#define	PMU_I2C_ID_OFFSET			24

#define	PMU_ADC_NSTATE_WORKAROUND_SEN_OFFSET		12		// not support after v3.0
#define	PMU_ADC_NSTATE_WORKAROUND_ADC_OFFSET		13		// not support after v3.0


#define	PMU_CPU_EVT_STATE_WIDTH		3		// At PMU_FSM = ALLON, the next FSM will be informed by CPU with REG_CPU_EVENT_TRIGGER
#define	PMU_CPU_EVT_TRI_WIDTH		1		// At PMU_FSM = ALLON, PMU jump the FSM based on REG_CPU_EVENT_NSTATE
#define	PMU_PWR_PLAN_WIDTH			1
#define	PMU_CPU_BOOT_WIDTH			1		// when CPU wakeup from ROM code, will check the bit determine to do boot flow.
#define	PMU_SEN_INIT_WIDTH			1		// when CPU wakeup from ROM code,will check the bit determine to do sensor init flow.
#define	PMU_CAP_NSTATE_WIDTH		1
#define PMU_CPU_SCENARIO_WIDTH		4
#define	PMU_ADC_NSTATE_WIDTH		3
#define	PMU_DC18_EN_WIDTH			1		// When REG_DCDC18_EN_SW = 1,
#define	PMU_DC09_EN_WIDTH			1		// When REG_DCDC09_EN_SW = 1,
#define	PMU_DC33_EN_WIDTH			1		// When REG_DCDC33_EN_SW = 1, ((OTP_PW_SW)
#define	PMU_DC18_EN_SW_WIDTH		1		// CPU(1)/PMU(0) control the config external DCDC18 ON/OFF
#define	PMU_DC09_EN_SW_WIDTH		1		// CPU(1)/PMU(0) control the config external DCDC09 ON/OFF
#define	PMU_DC33_EN_SW_WIDTH		1		// CPU(1)/PMU(0) control the config external DCDC33 ON/OFF
#define PMU_DC09_POL_WIDTH			1
#define PMU_DC33_POL_WIDTH			1
#define	PMU_I2C_ID_WIDTH			7

#define	PMU_ADC_NSTATE_WORKAROUND_WIDTH		1

/* Control Register 94h */
#define	PMU_S_FAE_OFFSET			0
#define	PMU_S_XSLEEP_OFFSET			1
#define	PMU_S_CXTSW_OFFSET			2
#define	PMU_S_NAOS_MCLK_MUX_OFFSET	4
#define	PMU_PRE_CAPTURED_ON_OFFSET		5
#define	PMU_EN_PLL_SW_OFFSET		6
#define	PMU_SLP1_ALL_PLL_EN_OFFSET	7
#define	PMU_CLDO_MODSEL_SW_OFFSET	8
#define	PMU_CLDO_MODSEL_OFFSET		9
#define	PMU_BOR_09V_EN_SW_OFFSET	10
#define	PMU_BOR_09V_EN_OFFSET		11
#define	PMU_OSC36M_EN_SW_OFFSET		12
#define	PMU_OSC36M_EN_OFFSET		13
#define	PMU_OSC36M_TRIM_EN_OFFSET	14
#define	PMU_CDM_INIT_MAP_EN_OFFSET	15
#define	PMU_SLD0_ULPLD_EN_SW_OFFSET	16
#define	PMU_SLD0_ULPLD_EN_OFFSET	17
#define	PMU_SLD0_ROK_MAN_SW_OFFSET	18
#define	PMU_SLD0_ROK_MAN_OFFSET		19
#define	PMU_SLD0_MODSEL_SW_OFFSET	20
#define	PMU_SLD0_MODSEL_OFFSET		21
#define	PMU_SLD0_VREF_SEL_SW_OFFSET	22
#define	PMU_SLD0_VEFF_SEL_OFFSET	24
#define PMU_S_XSLEEP_SW_OFFSET		28
#define PMU_S_CXTSW_SW_OFFSET		29
#define PMU_S_TRIGGER_SW_OFFSET		30
#define PMU_S_TRIGGER_OFFSET		31

#define	PMU_S_FAE_WIDTH				1		// CPU control. connect to PMU_S_FAE (pass through PMU)
#define	PMU_S_XSLEEP_WIDTH			1		// CPU control. connect to PMU_S_XSLEEP (pass through PMU)
#define	PMU_S_CXTSW_WIDTH			2		// a path controlled by CPU. BIT[2] 0 - sensor w/o output data, BIT[2] 1 - sensor output frame; BIT[3] reserved
#define	PMU_S_NAOS_MCLK_MUX_WIDTH	1		// 1 - For Non-AOS sensor ; 0 - For AOS sensor (MCLK by sensor_ctrl)
#define	PMU_PRE_CAPTURED_ON_WIDTH		1		//
#define	PMU_EN_PLL_SW_WIDTH			1		// PLL's EN_PLL,PWRGAT, RSTN controlled by CPU(1)/PMU<SLP1,ALL>(0)
#define	PMU_SLP1_ALL_PLL_EN_WODTH	1		//
#define	PMU_CLDO_MODSEL_SW_WIDTH	1
#define	PMU_CLDO_MODSEL_WIDTH		1
#define	PMU_BOR_09V_EN_SW_WIDTH		1		// 1: BOR's BOR_09V_EN controlled by REG_BOR_09V_EN
#define	PMU_BOR_09V_EN_WIDTH		1
#define	PMU_OSC36M_EN_SW_WIDTH		1		// 1: OSC's OSC36M_EN controlled by REG_OSC36M_EN
#define	PMU_OSC36M_EN_WIDTH			1
#define	PMU_OSC36M_TRIM_EN_WIDTH	1
#define	PMU_CDM_INIT_MAP_EN_WIDTH	1
#define	PMU_SLD0_ULPLD_EN_SW_WIDTH	1		// 1: CPU control the SLDO_ULPLDO_EN
#define	PMU_SLD0_ULPLD_EN_WIDTH		1
#define	PMU_SLD0_ROK_MAN_SW_WIDTH	1		// 1: CPU control the SLDO_ROK_MANUAL
#define	PMU_SLD0_ROK_MAN_WIDTH		1
#define	PMU_SLD0_MODSEL_SW_WIDTH	1		// 1: CPU control the SLDO_MODE_SEL
#define	PMU_SLD0_MODSEL_WIDTH		1
#define	PMU_SLD0_VREF_SEL_SW_WIDTH	1		// 1: CPU control the SLDO_VREF_SEL
#define	PMU_SLD0_VEFF_SEL_WIDTH		4
#define PMU_S_XSLEEP_SW_WIDTH		1		// 1: CPU control the S_XSLEEP (from REG_PMU_S_XSLEEP)
#define PMU_S_CXTSW_SW_WIDTH		1		// 1: CPU control the S_CXTSW (from REG_PMU_S_CXTSW)
#define PMU_S_TRIGGER_SW_WIDTH		1		// 1: CPU control the S_TRIGGER (from REG_PMU_S_TRIGGER)
#define PMU_S_TRIGGER_WIDTH			1		// 1: CPU control S_TRIGGER =1


/* Control Register 98h */
#define PMU_WAKE_EVT_CLR_OFFSET		0		// W1C - Clear the record of wakeup_cpu_event_pmu
#define	PMU_ADC_RSTN_INC_CLR_OFFSET	1		// W1C - When ADC_active=1, could be OFF by CPU.
#define	PMU_SEN_RSTN_INT_CLR_OFFSET 2		// W1C - When PMU SEN_active=1, could be clear PMU sen_active =0 by CPU.
#define PMU_SIF_PWSW_OFFSET			3		// power domain GPIO SIF power gating or not @PS_SD
#define PMU_PIF_PWSW_OFFSET			4		// power domain GPIO PIF power gating or not @PS_SD
#define PMU_ADC_PMU_CTRL_SW_OFFSET	5		// PMU(1)/CPU(0) control ADC IP and ADCC
#define	PMU_RTC_GC_OFFSET			8		// RTC Timer input clock GC or not
#define	PMU_RC32K_GC_OFFSET			9		// RC32K output clock GC or not
#define PMU_XTAL32K_GC_OFFSET		10		// XTAL32K output clock GC or not
#define PMU_RTC_GC_SW_OFFSET		11		// PMU(1)/CPU(0) control the RTC clock gating by REG_RTC_GC.
#define	PMU_RC32K_GC_SW_OFFSET		12		// PMU(1)/CPU(0) control the RC32K clock gating by REG_RC32K_OUT_GC.
#define PMU_XTAL32K_GC_SW_OFFSET	13		// PMU(1)/CPU(0) control the XTAL32K clock gating by REG_XTAL32K_OUT_GC.
#define PMU_XTAL24M_EN_SW_OFFSET	14		// 1: CPU control the XTAL24 enable.
#define PMU_XTAL24M_EN_OFFSET		15		// XTAL24 enable/disable
#define PMU_SLDO_VERF_SEL_063V_OFFSET	16		// Be used based on OTP trim code "sldo_063v_trim_en"
#define PMU_SLDO_VERF_SEL_090V_OFFSET	20		// Be used based on OTP trim code "sldo_090v_trim_en"
#define PMU_CLDO_VREF_SEL_RET_OFFSET	24		// Be used based on OTP trim code "This register will be used based on OTP trim code "cldo_ret_trim_en""
#define PMU_CLDO_VREF_SEL_NORMAL_OFFSET	28		// Be used based on OTP trim code This register will be used based on OTP trim code "cldo_normal_trim_en"


#define PMU_WAKE_EVT_CLR_WIDTH		1
#define	PMU_ADC_RSTN_INC_CLR_WIDTH	1
#define	PMU_SEN_RSTN_INT_CLR_WIDTH 	1
#define PMU_SIF_PWSW_WIDTH			1
#define PMU_PIF_PWSW_WIDTH			1
#define PMU_ADC_PMU_CTRL_SW_WIDTH	1
#define	PMU_RTC_GC_WIDTH			1
#define	PMU_RC32K_GC_WIDTH			1
#define PMU_XTAL32K_GC_WIDTH		1
#define PMU_RTC_GC_SW_WIDTH			1
#define	PMU_RC32K_GC_SW_WIDTH		1
#define PMU_XTAL32K_GC_SW_WIDTH		1
#define PMU_XTAL24M_EN_SW_EIDTH		1
#define PMU_XTAL24M_EN_WIDTH		1
#define PMU_SLDO_VERF_SEL_063V_WIDTH	4
#define PMU_SLDO_VERF_SEL_090V_WIDTH	4
#define PMU_CLDO_VREF_SEL_RET_WIDTH		4		// Be used based on OTP trim code "This register will be used based on OTP trim code "cldo_ret_trim_en""
#define PMU_CLDO_VREF_SEL_NORMAL_WIDTH	4		// Be used based on OTP trim code This register will be used based on OTP trim code "cldo_normal_trim_en"


/* Control Register 9Ch */
#define	PMU_INT_MASK_OFFSET				0	// Pre-masking of PMU_INT0~8
#define	PMU_INT_CLR_OFFSET 				9	// W1C - Pre-masking of PMU_INT0~8 Clear
#define	PMU_DMA_ABNORMAL_MASK_OFFSET	20	// Pre-masking of xDMAx_abnormal_int
#define	PMU_DMA_CFG_OFFSET				24	// DMA CONFIG for ANDs 4 DMAs Int together to PMU
#define	PMU_DMA_CFG_MASK_OFFSET			28	// All these INT ANDs together mean DMAs finish and issue INT to PMU.
#define	PMU_S_INT_MASK_OFFSET			29	// Pre-masking of PMU_S_INT (which from Sensor Int to PMU path)

#define	PMU_INT_MASK_WIDTH			9
#define	PMU_INT_CLR_WIDTH 			9
#define	PMU_DMA_ABNORMAL_MASK_WIDTH	4
#define	PMU_DMA_CFG_WIDTH			4
#define	PMU_DMA_CFG_MASK_WIDTH		1
#define	PMU_S_INT_MASK_WIDTH		1

/* COntrol Register  A0h */
#define	PMU_TSTABLE_N2R_CLDO_OFFSET	0		// CLDO Timing TSTABLE_N2R configuration by register setting.(unit: pmu_clk)
#define	PMU_TSTABLE_R2N_CLDO_OFFSET	8		// CLDO Timing TSTABLE_R2N configuration by register setting.(unit: pmu_clk)
#define	PMU_TSTABLE_N2R_SLDO_OFFSET	16		// SLDO Timing TStable_N2R configuration by register setting (unit: pmu_clk)
#define	PMU_TSTABLE_R2N_SLDO_OFFSET	24		// SLDO Timing TStable_R2N configuration by register setting (unit: pmu_clk)

#define	PMU_TSTABLE_N2R_CLDO_WIDTH	5
#define	PMU_TSTABLE_R2N_CLDO_WIDTH	5
#define	PMU_TSTABLE_N2R_SLDO_WIDTH	5
#define	PMU_TSTABLE_R2N_SLDO_WIDTH	5


/* Control Register A4h */
#define	PMU_TDCSTABLE_SLDO_OFFSET	0		// SLDO Timing TDCtable configuration by register setting (unit: pmu_clk)
#define	PMU_TVREF2N_SLDO_OFFSET		8		// SLDO Timing TVREF2N configuration by register setting (unit: pmu_clk)
#define	PMU_TWKEUP_SLDO_OFFSET		16		// SLDO Timing TWAKEUP : PMU_SLDO_ROK_MANUAL's rising is after 1ms of PMU_SLDO_ULPLDO_EN's rising (unit: pmu_clk)
#define	PMU_TROK_DCOFF_SLDO_OFFSET	24		// SLDO Timing TRok_DCoff configuration by register setting (unit: pmu_clk)
#define	PMU_TDCOFF_RON_SLDO_OFFSET	28		// SLDO Timing TRok_DCoff configuration by register setting (unit: pmu_clk)

#define	PMU_TDCSTABLE_SLDO_WIDTH	5
#define	PMU_TVREF2N_SLDO_WIDTH		4
#define	PMU_TWKEUP_SLDO_WIDTH		6
#define	PMU_TROK_DCOFF_SLDO_WIDTH	4
#define	PMU_TDCOFF_RON_SLDO_WIDTH	4


/* Control Register A8h */
#define PMU_TDCSTABLE_CLDO_OFFSET		0
#define PMU_WAKEUP_CPU_EVT_PMU_OFFSET	8

#define	PMU_TDCSTABLE_CLDO_WIDTH		5
#define	PMU_WAKEUP_CPU_EVT_PMU_WIDTH	22
//[0] : PS_SD : wakeup by (i2c_fsm_sd_all_trig || ext_force_pmu_allon)
//[1]: PS_SD wakeup by ext_int_nxt_all(GPIO)
//[2]: PS_SD wakeup by REG_CPU_SCENARIO=4'b0001&S_EXT_INT
//[3]: PS_SLP2 wakeup by i2c_fsm_slp2_all_trig || ext_force_pmu_allon
//[4]: PS_SLP2 wakeup by ext_int_nxt_all(GPIO)
//[5]: PS_SLP2 wakeup by REG_CPU_SCENARIO=4'b0010&S_EXT_INT
//[6]: PS_SLP2 wakeup by REG_CPU_SCENARIO=4'b0010& RTC_timer
//[7]: PS_SLP2 wakeup by REG_CPU_SCENARIO=4'b0010& RTC_ADC_timer_int
//[8]: PS_SLP1 wakeup by i2c_fsm_slp1_all_trig || ext_force_pmu_allon
//[9]: PS_SLP1 wakeup by ext_int_nxt_all(GPIO)
//[10]: PS_SLP1 wakeup by (Sensor_EXT_INT && REG_CPU_SCENARIO[3:0]==4'b0011 && REG_SENCTRL_MODE==3'd4)||
//                                        (RTC_timer_int  && REG_CPU_SCENARIO[3:0]==4'b0011 && REG_SENCTRL_MODE==3'd5)
//[11]: PS_SLP1 wakeup by (RTC_ADC_timer_int && REG_CPU_SCENARIO[3:0]==4'b0011 && (REG_SENCTRL_MODE==3'd4 ||  REG_SENCTRL_MODE==3'd5)
//[12]: PS_EXP wakeup by i2c_fsm_exp_all_trig || ext_force_pmu_allon)
//[13]: PS_EXP wakeup by ((REG_CPU_SCENARIO==4'b1000 && ADCC_int) ||(REG_CPU_SCENARIO==4'b1100 && ~pmu_sen_active && ADCC_int))
//[14]: PS_CAP wakeup by i2c_fsm_cap_all_trig || ext_force_pmu_allon
//[15]: PS_CAP wakeup by WRDMAx_abnormal_int
//[16]: PS_CAP wakeup by DP_ABNORMAL_INT
//[17]: PS_CAP wakeup by (REG_CPU_SCENARIO==4'b0100 && SC_nframe_end && all_cfg_xDMAx_int && DP_CDM_MOTION_INT)
//[18]: PS_CAP wakeup by(REG_CPU_SCENARIO==4'b1100 && SC_nframe_end && all_cfg_xDMAx_int && DP_CDM_MOTION_INT && pmu_adc_active && ACC_int)
//[19]: PS_CAP wakeup by (REG_CPU_SCENARIO==4'b1100 && SC_nframe_end && all_cfg_xDMAx_int && DP_CDM_MOTION_INT && pmu_adc_active && ADC_timeout && ~ADCC_int)
//[20]: PS_CAP wakeup by (REG_CPU_SCENARIO==4'b1100 && SC_nframe_end && all_cfg_xDMAx_int && DP_CDM_MOTION_INT && ~pmu_adc_active)
//[21]: PS_CAP wakeup by (REG_CPU_SCENARIO==4'b1100 && SC_nframe_end && all_cfg_xDMAx_int && ~DP_CDM_MOTION_INT && ADCC_int)


/* Control Register ACh */
#define PMU_MEM32_RET_PMU_OFFSET 	0 	// Power mode of nth SYSMEM on SLP1/EXP state

#define PMU_MEM32_RET_PMU_WIDTH		23


/* Control Register B0h */
#define PMU_MEM46_RET_PMU_OFFSET	0	// not support after v3.0
#define PMU_XCCM_RET_PMU_OFFSET		14	// Power mode of nth XCCM on SLP1/EXP state
#define PMU_YCCM_RET_PMU_OFFSET		15	// Power mode of nth YCCM on SLP1/EXP state
#define PMU_ICCM_RET_PMU_OFFSET		16	// Power mode of nth ICCM on SLP1/EXP state

#define PMU_MEM46_RET_PMU_WIDTH		14
#define PMU_XCCM_RET_PMU_WIDTH		1
#define PMU_YCCM_RET_PMU_WIDTH		1
#define PMU_ICCM_RET_PMU_WIDTH		10


/* Control Register B4h */
#define PMU_DCCM_RET_PMU_OFFSET		0	// Power mode of nth DCCM on SLP1/EXP state
#define PMU_TSCTL_PWSW_OFFSET		8	// Timing Tsctl delay time for PD_SCTL power ready (unit: PMU clock)
#define PMU_TCV_PWSW_OFFSET			12	// Timing Tsctl delay time for PD_TCV power ready (unit: PMU clock)
#define PMU_TRAM_PWSW_OFFSET		16	// Timing Tsctl delay time for PD_TRAM power ready (unit: PMU clock)

#define PMU_DCCM_RET_PMU_WIDTH		8
#define PMU_TSCTL_PWSW_WIDTH		4
#define PMU_TCV_PWSW_WIDTH			4
#define PMU_TRAM_PWSW_WIDTH			4


/* Control Register B8h */
#define	PMU_WDT_RTC_LOAD_COUNTER_OFFSET	0		// PMU Watchdog RTC counter pre-load counter value
#define	PMU_WDT_RTC_PRE_SCALE_OFFSET	24		// PMU Watchdog Counter Pre-scalar
#define	PMU_WDT_RTC_LOAD_EN1T_OFFSET	28		// PMU Watchdog RTC counter pre-load counter enable 1T and this will also clear the PMU Timeout Int.
#define	PMU_WDT_RTC_EN_OFFSET			29		// 1: PMU watchdog enable
#define	PMU_WDT_RTC_INT_MASK_OFFSET		30		// 1: PMU watchdog interrupt masking

#define	PMU_WDT_RTC_LOAD_COUNTER_WIDTH	24
#define	PMU_WDT_RTC_PRE_SCALE_WIDTH		3
#define	PMU_WDT_RTC_LOAD_EN1T_WIDTH		1
#define	PMU_WDT_RTC_EN_WIDTH			1
#define	PMU_WDT_RTC_INT_MASK_WIDTH		1


/* Control Register BCh */
#define	PMU_WDT_ADC_LOAD_COUNTER_OFFSET	0		// PMU Watchdog RTC counter pre-load counter value
#define	PMU_WDT_ADC_PRE_SCALE_OFFSET	24		// PMU Watchdog Counter Pre-scalar
#define	PMU_WDT_ADC_LOAD_EN1T_OFFSET	28		// PMU Watchdog RTC counter pre-load counter enable 1T and this will also clear the PMU Timeout Int.
#define	PMU_WDT_ADC_EN_OFFSET			29		// 1: PMU watchdog enable
#define	PMU_WDT_ADC_INT_MASK_OFFSET		30		// 1: PMU watchdog interrupt masking

#define	PMU_WDT_ADC_LOAD_COUNTER_WIDTH	24
#define	PMU_WDT_ADC_PRE_SCALE_WIDTH		3
#define	PMU_WDT_ADC_LOAD_EN1T_WIDTH		1
#define	PMU_WDT_ADC_EN_WIDTH			1
#define	PMU_WDT_ADC_INT_MASK_WIDTH		1


/* Control Register C0h */
#define PMU_PIO_INT_NXT_OFFSET			0		//not support after v3.0 // Config the Next State for PMU_PINT0~6, PMU_SINT0~1 interrupt goto
#define PMU_RTC_PMU_INT_NXT_OFFSET		24		//not support after v3.0 // Config the Next State for RTC timer interrupt goto
#define PMU_RTC_ADC_INT_NXT_OFFSET		26		//not support after v3.0 // Config the Next State for RTC timer interrupt goto
#define PMU_RC36M_CAL_PMU_MODE_OFFSET	28		// 1: Calibration function in PMU mode enable (RC36M Calib)
#define PMU_RC32K_CAL_PMU_MODE_OFFSET	29		// 1: Calibration function in PMU mode enable (RC32K Calib)
#define PMU_WDT_RESETN_EN_OFFSET		30		// 1: PMU WDG reset whole chip enable

#define PMU_PIO_INT_NXT_WIDTH			18
#define PMU_RTC_PMU_INT_NXT_WIDTH		2
#define PMU_RTC_ADC_INT_NXT_WIDTH		2
#define PMU_RC36M_CAL_PMU_MODE_WIDTH	1
#define PMU_RC32K_CAL_PMU_MODE_WIDTH	1
#define PMU_WDT_RESETN_EN_WIDTH			1


/* Control Register C4h */
#define PMU_CAL_AUTO_TRM_PRD_OFFSET		0		// The period of calibration for Auto mode (clock: XTAL clock), range 1ms~1sec
#define PMU_CAL_TRM_N_OFFSET			16		// The target value of calibration result, count by 36MHz OSC clock
#define PMU_CAL_TRM_PRD_OFFSET			28		// The period of calibration for PMU mode (clock: XTAL clock)
#define PMU_CAL_FUN_EN_OFFSET			31		// 1: Calibration function enable, use pmu_osc36m_trim.
												// 0: Disable use pmu_osc36m_trim, use sec_aip_trim or RC36M_TRIM_SEL.
#define PMU_CAL_AUTO_TRM_PRD_WIDTH		16
#define PMU_CAL_TRM_N_WIDTH				12
#define PMU_CAL_TRM_PRD_WIDTH			3
#define PMU_CAL_FUN_EN_WIDTH			1


/* Control Register C8h */
#define PMU_CAL_TRM_STP_OFFSET			0
#define PMU_CAL_MANUAL_MODE_OFFSET		6
#define PMU_CAL_MANUAL_TRIM_SET_OFFSET	7
#define PMU_CAL_CNT_RANGE_OFFSET		8
#define PMU_CAL_AUTO_MODE_OFFSET		14
#define PMU_CAL_DONE_CLR_OFFSET			15
#define PMU_CAL_CNT_N_RESULT_OFFSET		16
#define PMU_CAL_OSC36M_OVFINT_OFFSET	28
#define PMU_CAL_OSC36M_FINISH_OFFSET	29
#define PMU_CAL_OSC36M_DONE_OFFSET		30
#define PMU_CAL_OVF_CLR_OFFSET			31

#define PMU_CAL_TRM_STP_WIDTH			6
#define PMU_CAL_MANUAL_MODE_WIDTH		1
#define PMU_CAL_MANUAL_TRIM_SET_WIDTH	1
#define PMU_CAL_CNT_RANGE_WIDTH			6
#define PMU_CAL_AUTO_MODE_WIDTH			1
#define PMU_CAL_DONE_CLR_WIDTH			1
#define PMU_CAL_CNT_N_RESULT_WIDTH		12
#define PMU_CAL_OSC36M_OVFINT_WIDTH		1
#define PMU_CAL_OSC36M_FINISH_WIDTH		1
#define PMU_CAL_OSC36M_DONE_WIDTH		1
#define PMU_CAL_OVF_CLR_WIDTH			1


/** MEMORY CPU POWER MODE SETTING **/
/* Control Register CCh/D0h/D4h */
#define PMU_SYSMEM_PW_STATE0_GRP1_OFFSET	0	// Power mode of 1th SYSMEM on ALLON/CAP state
#define PMU_SYSMEM_PW_STATE0_GRP2_OFFSET	2
#define PMU_SYSMEM_PW_STATE0_GRP3_OFFSET	4
#define PMU_SYSMEM_PW_STATE0_GRP4_OFFSET	6
#define PMU_SYSMEM_PW_STATE0_GRP5_OFFSET	8
#define PMU_SYSMEM_PW_STATE0_GRP6_OFFSET	10
#define PMU_SYSMEM_PW_STATE0_GRP7_OFFSET	12
#define PMU_SYSMEM_PW_STATE0_GRP8_OFFSET	14
#define PMU_SYSMEM_PW_STATE0_GRP9_OFFSET	16
#define PMU_SYSMEM_PW_STATE0_GRP10_OFFSET	18
#define PMU_SYSMEM_PW_STATE0_GRP11_OFFSET	20
#define PMU_SYSMEM_PW_STATE0_GRP12_OFFSET	22
#define PMU_SYSMEM_PW_STATE0_GRP13_OFFSET	24
#define PMU_SYSMEM_PW_STATE0_GRP14_OFFSET	26
#define PMU_SYSMEM_PW_STATE0_GRP15_OFFSET	28
#define PMU_SYSMEM_PW_STATE0_GRP16_OFFSET	30


/* Control Register D0h */
#define PMU_SYSMEM_PW_STATE0_GRP17_OFFSET	0
#define PMU_SYSMEM_PW_STATE0_GRP18_OFFSET	2
#define PMU_SYSMEM_PW_STATE0_GRP19_OFFSET	4
#define PMU_SYSMEM_PW_STATE0_GRP20_OFFSET	6
#define PMU_SYSMEM_PW_STATE0_GRP21_OFFSET	8
#define PMU_SYSMEM_PW_STATE0_GRP22_OFFSET	10
#define PMU_SYSMEM_PW_STATE0_GRP23_OFFSET	12
#define PMU_SYSMEM_PW_STATE0_GRP24_OFFSET	14	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP25_OFFSET	16	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP26_OFFSET	18	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP27_OFFSET	20	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP28_OFFSET	22	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP29_OFFSET	24	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP30_OFFSET	26	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP31_OFFSET	28	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP32_OFFSET	30	//not support after v3.0


/* Control Register D4h */
#define PMU_SYSMEM_PW_STATE0_GRP33_OFFSET	0	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP34_OFFSET	2	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP35_OFFSET	4	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP36_OFFSET	6	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP37_OFFSET	8	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP38_OFFSET	10	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP39_OFFSET	12	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP40_OFFSET	14	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP41_OFFSET	16	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP42_OFFSET	18	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP43_OFFSET	20	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP44_OFFSET	22	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP45_OFFSET	24	//not support after v3.0
#define PMU_SYSMEM_PW_STATE0_GRP46_OFFSET	26	//not support after v3.0
#define PMU_XCCM_PW_STATE_OFFSET			28
#define PMU_YCCM_PW_STATE_OFFSET			30


/* Control Register D8h */
#define PMU_ICCM_PW_STATE0_GRP1_OFFSET		0	// Power mode of 1th SYSMEM on ALLON/CAP state
#define PMU_ICCM_PW_STATE0_GRP2_OFFSET		2
#define PMU_ICCM_PW_STATE0_GRP3_OFFSET		4
#define PMU_ICCM_PW_STATE0_GRP4_OFFSET		6
#define PMU_ICCM_PW_STATE0_GRP5_OFFSET		8
#define PMU_ICCM_PW_STATE0_GRP6_OFFSET		10
#define PMU_ICCM_PW_STATE0_GRP7_OFFSET		12
#define PMU_ICCM_PW_STATE0_GRP8_OFFSET		14
#define PMU_ICCM_PW_STATE0_GRP9_OFFSET		16
#define PMU_ICCM_PW_STATE0_GRP10_OFFSET		18


/* Control Register DCh */
#define PMU_DCCM_PW_STATE0_GRP1_OFFSET		0	// Power mode of 1th SYSMEM on ALLON/CAP state
#define PMU_DCCM_PW_STATE0_GRP2_OFFSET		2
#define PMU_DCCM_PW_STATE0_GRP3_OFFSET		4
#define PMU_DCCM_PW_STATE0_GRP4_OFFSET		6
#define PMU_DCCM_PW_STATE0_GRP5_OFFSET		8
#define PMU_DCCM_PW_STATE0_GRP6_OFFSET		10
#define PMU_DCCM_PW_STATE0_GRP7_OFFSET		12
#define PMU_DCCM_PW_STATE0_GRP8_OFFSET		14

#define	PMU_MEMORY_PW_STATE_WIDTH  			2


/* Control Register E0h */
#define PMU_WDT_RTC_CUR_COUNT_OFFSET		0	//WDT Timeout counter status to register bank(read only)
#define PMU_WDT_RTC_CUR_COUNT_WIDTH			24


/* Control Register E4h */
#define PMU_WDT_ADC_CUR_COUNT_OFFSET		0	//ADC Timeout counter status to register bank(read only)
#define PMU_WDT_ADC_CUR_COUNT_WIDTH			24


/* Control Register E8h */
#define PMU_PMU_STATE_RB_OFFSET				0  //PMU Status to register bank(read only)
#define PMU_PMU_STATE_EXT_INT_OFFSET		0
#define PMU_PMU_STATE_DBG_BUS_OFFSET		9
#define PMU_PMU_STATE_OSC36_TREM_OFFSET		16
#define PMU_PMU_STATE_RC32K_TREM_OFFSET		22

#define PMU_PMU_STATE_EXT_INT_WIDTH			9
#define PMU_PMU_STATE_DBG_BUS_WIDTH			6
#define PMU_PMU_STATE_OSC36_TREM_WIDTH		6
#define PMU_PMU_STATE_RC32K_TREM_WIDTH		6
//[0]: ext_pint0
//[1]: ext_pint1
//[2]: ext_pint2
//[3]: ext_pint3
//[4]: ext_pint4
//[5]: ext_pint5
//[6]: ext_pint6
//[7]: ext_sint0
//[8]: ext_sint1
//[14:9] : PMU_DB_BUS[5:0]
//[15]: 1'b0
//[21:16] :PMU_OSC36M_TRIM[5:0]
//[27:22] :PMU_RC32K_TRIM[5:0]
//[31:28]: 4'b0


/* Control Register ECh */
#define PMU_RC32K_CAL_AUTO_TRM_PRD_OFFSET	0	// The period of calibration for Auto mode (clock: RC 32K clock), range 1ms~1sec
#define PMU_RC32K_CAL_TRM_N_OFFSET			16	// The target value of calibration result, count by 24MHz OSC clock
#define PMU_RC32K_CAL_PMU_TRM_PRD_OFFSET	28	// The period of calibration for PMU mode (clock:  RC 32K clock)
#define PMU_RC32K_CAL_FUNC_EN_OFFSET		31

#define PMU_RC32K_CAL_AUTO_TRM_PRD_WIDTH	16
#define PMU_RC32K_CAL_TRM_N_WIDTH			12
#define PMU_RC32K_CAL_PMU_TRM_PRD_WIDTH		3
#define PMU_RC32K_CAL_FUNC_EN_WIDTH			1


/* Control Register F0h */
#define PMU_RC32K_CAL_TRM_STP_OFFSET			0
#define PMU_RC32K_CAL_MANUAL_MODE_OFFSET		6
#define PMU_RC32K_CAL_MANUAL_TRIM_SET_OFFSET	7
#define PMU_RC32K_CAL_CNT_RANGE_OFFSET			8
#define PMU_RC32K_CAL_AUTO_MODE_EN_OFFSET		14
#define PMU_RC32K_CAL_DONE_CLR_OFFSET			15	// W1C
#define PMU_RC32K_CAL_CNT_N_RST_OFFSET			16	// RO
#define PMU_RC32K_CAL_OVF_INT_OFFSET			28	// RO
#define PMU_RC32K_CAL_FINISH_OFFSET				29 	// RO
#define PMU_RC32K_CAL_DONE_OFFSET				30 	// RO
#define PMU_RC32K_CAL_OVF_CLR_OFFSET			31 	// W1C

#define PMU_RC32K_CAL_TRM_STP_WIDTH				6
#define PMU_RC32K_CAL_MANUAL_MODE_WIDTH			1
#define PMU_RC32K_CAL_MANUAL_TRIM_SET_WIDTH		1
#define PMU_RC32K_CAL_CNT_RANGE_WIDTH			6
#define PMU_RC32K_CAL_AUTO_MODE_EN_WIDTH		1
#define PMU_RC32K_CAL_DONE_CLR_WIDTH			1	// W1C
#define PMU_RC32K_CAL_CNT_N_RST_WIDTH			12	// RO
#define PMU_RC32K_CAL_OVF_INT_WIDTH				1	// RO
#define PMU_RC32K_CAL_FINISH_WIDTH				1 	// RO
#define PMU_RC32K_CAL_DONE_WIDTH				1 	// RO
#define PMU_RC32K_CAL_OVF_CLR_WIDTH				1 	// W1C


/* Control Register FCh */
#define PMU_BOOTOPTION_OFFSET					0
#define PMU_VERSION_OFFSET						8

#define PMU_BOOTOPTION_WIDTH					8
#define PMU_VERSION_WIDTH						24

#endif /* SYS_PMU_HX_DRV_PMU_REG_H_ */

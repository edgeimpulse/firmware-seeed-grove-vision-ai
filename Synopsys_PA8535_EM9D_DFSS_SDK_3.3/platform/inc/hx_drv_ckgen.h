/**
 * @file hx_drv_ckgen.h
 * @author himax/902452
 * @brief 
 * @version V1.0.0
 * @date 2018/12/06
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef PLATFORM_INC_HX_DRV_CKGEN_H_
#define PLATFORM_INC_HX_DRV_CKGEN_H_

#include "embARC_toolchain.h"

/***********************************************
 * CONSTANT DEFINITION
 **********************************************/
/**
 * \brief	CLK GATED Selection
 * 
 */
#define GATED_EN                 1
#define GATED_DIS                0

/**
 * \brief CLK DIVIDER Selection : 4BITS WIDTH <MIN:1, MAX:16, STEP:1) 
 * 
 */
#define CKDIV_4BIT_STEP1_1       0
#define CKDIV_4BIT_STEP1_2       1
#define CKDIV_4BIT_STEP1_3       2
#define CKDIV_4BIT_STEP1_4       3
#define CKDIV_4BIT_STEP1_5       4
#define CKDIV_4BIT_STEP1_6       5
#define CKDIV_4BIT_STEP1_7       6
#define CKDIV_4BIT_STEP1_8       7
#define CKDIV_4BIT_STEP1_9       8
#define CKDIV_4BIT_STEP1_10      9
#define CKDIV_4BIT_STEP1_11     10
#define CKDIV_4BIT_STEP1_12     11
#define CKDIV_4BIT_STEP1_13     12
#define CKDIV_4BIT_STEP1_14     13
#define CKDIV_4BIT_STEP1_15     14
#define CKDIV_4BIT_STEP1_16     15

/**
 * \brief CLK DIVIDER Selection : 4BITS WIDTH <MIN:4, MAX:64, STEP:4) 
 * 
 */
#define CKDIV_4BIT_STEP4_4       0
#define CKDIV_4BIT_STEP4_8       1
#define CKDIV_4BIT_STEP4_12      2
#define CKDIV_4BIT_STEP4_16      3
#define CKDIV_4BIT_STEP4_20      4
#define CKDIV_4BIT_STEP4_24      5
#define CKDIV_4BIT_STEP4_28      6
#define CKDIV_4BIT_STEP4_32      7
#define CKDIV_4BIT_STEP4_36      8
#define CKDIV_4BIT_STEP4_40      9
#define CKDIV_4BIT_STEP4_44     10
#define CKDIV_4BIT_STEP4_48     11
#define CKDIV_4BIT_STEP4_52     12
#define CKDIV_4BIT_STEP4_56     13
#define CKDIV_4BIT_STEP4_60     14
#define CKDIV_4BIT_STEP4_64     15

/**
 * \brief CLK DIVIDER Selection : 2BITS WIDTH <MIN:1, MAX:4, STEP:1) 
 * 
 */
#define CKDIV_2BIT_STEP1_1       0
#define CKDIV_2BIT_STEP1_2       1
#define CKDIV_2BIT_STEP1_3       2
#define CKDIV_2BIT_STEP1_4       3

/**
 * \brief CLK RTC MUX Selection 
 * 
 */
#define CLK_RTC_MUX_SEL_RC32K   0   /**< RC_32K */
#define CLK_RTC_MUX_SEL_XTAL    1   /**< XTAL   */

/**
 * \brief CLK PMU MUX Selection 
 * 
 */
#define CLK_PMU_MUX_SEL_RC32K   0   /**< RC_32K */
#define CLK_PMU_MUX_SEL_XTAL    1   /**< XTAL   */

/**
 * \brief   CLK AHB MUX Selection 
 * 
 */
#define CLK_AHB_MUX_SEL_RC36M   0   /**< RC_36M   */
#define CLK_AHB_MUX_SEL_PLL     1   /**< PLL_400M */

/**
 * \brief CLK INPRX MUX Selection  
 * 
 */
#define CLK_INP_MUX_SEL_RX      0   /**< RX PCLK */
#define CLK_INP_MUX_SEL_DP      1   /**< DP CLK  */

/**
 * \brief CLK Datapath clock sources gated by PMU selection
 * 
 */
#define CLK_DP_GATED_SEL_CPU        0   /**< DP CLK GATED Selection CPU         */
#define CLK_DP_GATED_SEL_CPU_PMU    1   /**< DP CLK GATED Selection CPU and PMU */

/**
 * \brief CLK ADC MUX Selection
 * 
 */
#define CLK_ADC_MUX_SEL_INT     0   /**< Internal(XTAL/RC/PLL_FB) */
#define CLK_ADC_MUX_SEL_EXT     1   /**< External(test_clk3)      */  

/**
 * \brief CLK ADC internal MUX Selection
 * 
 */
#define CLK_ADC_MUX_SEL_XTAL    0   /**< XTAL/RC_36M    */
#define CLK_ADC_MUX_SEL_PLLFB   1   /**< PLL_FB         */

/**
 * \brief CLK PDM internal MUX Selection
 * 
 */
#define CLK_PDM_MUX_SEL_XTAL    0   /**< XTAL/RC_36M */
#define CLK_PDM_MUX_SEL_PLLFB   1   /**< PLL_FB      */

/**
 * \brief CLK I2S MUX Selection
 * 
 */
#define CLK_I2S_MUX_SEL_INT     0   /**< Internal(xtal/rc/pllfb) */
#define CLK_I2S_MUX_SEL_EXT     1   /**< External(test_clk4)     */

/**
 * \brief CLK PDM MUX Selection
 * 
 */
#define CLK_PDM_MUX_SEL_INT     0   /**< Internal(RC36M / PLL_FB) */
#define CLK_PDM_MUX_SEL_EXT     1   /**< External(test_clk5)      */

/**
 * \brief CLK MCLK MUX Selection
 * 
 */
#define CLK_MCLK_MUX_SEL_INT    0   /**< Internal(xtal/rc/pllfb) */    
#define CLK_MCLK_MUX_SEL_EXT    1   /**< External(test_clk6)     */    

/**
 * \brief CLK PLL REF MUX Selectio
 * 
 */
#define CLK_PLLREF_MUX_SEL_RC36M    0   /**< RC_36M         */
#define CLK_PLLREF_MUX_SEL_XTAL     1   /**< XTAL_24M_POST  */

/**
 * \brief CLK PCLK MUX Selection
 * 
 */
#define CLK_PCLK_MUX_SEL_RC36M      0   /**< RC_36M         */
#define CLK_PCLK_MUX_SEL_XTAL       1   /**< XTAL_24M_POST  */

/**
 * \brief CLK MCLK MUX Selection
 * 
 */
#define CLK_MCLK_MUX_SEL_RC36M      0   /**< RC_36M     */
#define CLK_MCLK_MUX_SEL_XTAL       1   /**< XTAL_24M   */    

/**
 * \brief CLK RC36M MUX Selection
 * 
 */
#define CLK_RC36M_MUX_SEL_RC36M     0   /**< RC_36M     */
#define CLK_RC36M_MUX_SEL_TEST      1   /**< test_clk2  */

/**
 * \brief SOFTWARE RESET Selection
 * 
 */
#define SWRST_EN                    1
#define SWRST_DIS                   0

/***********************************************
 * EMULATOR DECLARATION
 **********************************************/
/**
 * \enum SYS_ERROR_E
 * \brief CKGEN Errors Type
 */
typedef enum SYS_ERROR_S
{
    SYS_NO_ERROR                    = 0,        /**< No ERROR */
    SYS_ERROR_NOT_INIT              = 1,        /**< ERROR MSG: not init */
    SYS_ERROR_ALREADY_INIT          = 2,        /**< ERROR MSG: already init */
    SYS_ERROR_INVALID_PARAMETERS    = 3,        /**< ERROR MSG: Invalid parameters */
    SYS_ERROR_NULL_POINTER          = 4,        /**< ERROR MSG: NULL pointer */
    SYS_UNKNOWN_ERROR               = 5,        /**< ERROR MSG: UNKNOWN ERROR*/
} SYS_ERROR_E;

/**
 * \enum SYS_INDEX_E
 * \brief CKGEN Gated INDEX
 */
typedef enum SYS_INDEX_S
{
    SYS_INP = 0,
    SYS_SENCTRL,
    SYS_2x2,
    SYS_5x5,
    SYS_CDM,
    SYS_JPEG,
    SYS_TPG,
    SYS_EDM,
    SYS_DP,
    SYS_DMAW1,
    SYS_DMAW2,
    SYS_DMAW3,
    SYS_DMAR,
    SYS_SEC,
    SYS_CPU,
    SYS_DATAMEM,
    SYS_RS,                 
    SYS_HOG,
    SYS_MCLK,
    SYS_ADC,
    SYS_PWM0,
    SYS_PWM1,
    SYS_PWM2,
    SYS_PDM,
    SYS_I2S,
    SYS_RESERVED0,
    SYS_DWSSI0,
    SYS_DWSSI1,
    SYS_RTC,
    SYS_OTP_WRAPPER,
    SYS_REGBK1,
    SYS_RESERVED1,          /**< SYS_PMU, reg_table_grp_aon_190917.xls: reserved */
    SYS_RC_36M_CAL,
    SYS_OTP_LCC,
} SYS_INDEX_E;

/**
 * \enum CLKDIV_INDEX_E
 * \brief CLK DIV INDEX
 */
typedef enum CLKDIV_INDEX_S
{
    CLKDIV_PCLK = 0,
    CLKDIV_MCLK,
    CLKDIV_AHB2_BRG,
    CLKDIV_OTP,
    CLKDIV_PWM,
    CLKDIV_RSHOG,
    CLKDIV_CPUPER,
    CLKDIV_ADCC,
    CLKDIV_I2S,
    CLKDIV_PDM
} CLKDIV_INDEX_E;

/**
 * \enum CLKMUX_INDEX_E
 * \brief CLK MUX INDEX
 */
typedef enum CLKMUX_INDEX_S
{
    CLKMUX_RTC              = 0,
    CLKMUX_PMU              = 1,
    CLKMUX_AHB              = 2,
    CLKMUX_INPRX            = 3,
    CLKMUX_DP_GATED         = 4,
    CLKMUX_32K              = 5,
    CLKMUX_ADC_INTERNAL     = 6,
    CLKMUX_ADC_CLK_SRC      = 7,
    CLKMUX_PDM              = 8,
    CLKMUX_I2S              = 9,
    CLKMUX_PDM_INTERNAL     = 10,
    CLKMUX_MCLK             = 11,
    CLKMUX_PLL              = 12,
    CLKMUX_PCLK             = 13,
    CLKMUX_MCLK_INTER       = 14,
    CLKMUX_RC36M            = 15
} CLKMUX_INDEX_E;

/**
 * \enum SYS_RST_INDEX_E
 * \brief CKGEN SWRST INDEX
 */
typedef enum SYS_RST_INDEX_S
{
    SYS_RST_INP = 0,
    SYS_RST_SENCTRL,
    SYS_RST_2x2,
    SYS_RST_5x5,
    SYS_RST_CDM,
    SYS_RST_JPEG,
    SYS_RST_TPG,
    SYS_RST_EDM,
    SYS_RST_DP,
    SYS_RST_DMAW1,
    SYS_RST_DMAW2,
    SYS_RST_DMAW3,
    SYS_RST_DMAR,
    SYS_RST_SEC,
    SYS_RST_CPU,
    SYS_RST_DATAMEM,
    SYS_RST_RS,
    SYS_RST_HOG,
    SYS_RST_MCLK,
    SYS_RST_ADC,
    SYS_RST_PWM0,
    SYS_RST_PWM1,
    SYS_RST_PWM2,
    SYS_RST_PDM,
    SYS_RST_I2S,
    SYS_RST_RESERVED0,
    SYS_RST_DWSSI0,
    SYS_RST_DWSSI1,
    SYS_RST_RTC,
    SYS_RST_OTP_WRAPPER,
    SYS_RST_REGBK1,
    SYS_RST_PMU,       
    SYS_RST_RESERVED1, /* SYS_RST_CPU_JTAG,  reg_table_grp_aon_190917.xls: reserved */
    SYS_RST_RESERVED2, /* SYS_RST_CPU_I2CM1, reg_table_grp_aon_190917.xls: reserved */
    SYS_RST_RESERVED3, /* SYS_RST_CPU_I2CM0, reg_table_grp_aon_190917.xls: reserved */
    SYS_RST_RESERVED4, /* SYS_RST_CPU_I2CM2, reg_table_grp_aon_190917.xls: reserved */
    SYS_RST_RESERVED5, /* SYS_RST_CPU_I2CS,  reg_table_grp_aon_190917.xls: reserved */
    SYS_RST_RESERVED6, /* SYS_RST_CPU_SPIS,  reg_table_grp_aon_190917.xls: reserved */
    SYS_RST_RESERVED7, /* SYS_RST_CPU_UART0, reg_table_grp_aon_190917.xls: reserved */
    SYS_RST_RESERVED8, /* SYS_RST_CPU_UART1, reg_table_grp_aon_190917.xls: reserved */
    SYS_RST_CPU_APB,
    SYS_RST_REGBK0,
    SYS_RST_RC_CAL,
    SYS_RST_OTT_LCC,
    SYS_RST_RC_32K_CAL,
    SYS_RST_RC_36M_CAL,
} SYS_RST_INDEX_E;

/**
 * \enum SENCTRL_RST_SEL_E
 * \brief Sensor Control SWRST Sel
 */
typedef enum SENCTRL_RST_SEL_S
{
    SENCTRL_RST_SEL_CPU = 0,
    SENCTRL_RST_SEL_PMU,
} SENCTRL_RST_SEL_E;

/**
 * \enum ADC_RST_SEL_E
 * \brief ADC Reset Control SWRST Sel
 */
typedef enum ADC_RST_SEL_S
{
    ADC_RST_SEL_CPU = 0,
    ADC_RST_SEL_PMU = 1,
} ADC_RST_SEL_E;


/**
 * \enum PLL_REF_SEL_E
 * \brief PLL Reference Sel
 */
typedef enum PLL_REF_SEL_S
{
	PLL_REF_SEL_RC36M = 0,
	PLL_REF_SEL_XTAL24M = 1,
} PLL_REF_SEL_E;


/**
 * \enum APP_CPU_FREQ_T
 * \brief Application CPU frequency
 */
typedef enum APP_CPU_FREQ_S{
	APP_FREQ_400M_FROM_RC36M = 0,
	APP_FREQ_300M_FROM_RC36M,
	APP_FREQ_200M_FROM_RC36M,
	APP_FREQ_100M_FROM_RC36M,
	APP_FREQ_400M_FROM_XTAL24M,
	APP_FREQ_300M_FROM_XTAL24M,
	APP_FREQ_200M_FROM_XTAL24M,
	APP_FREQ_100M_FROM_XTAL24M,
	APP_FREQ_32M_FROM_XTAL24M,
	APP_FREQ_400M_FROM_XTAL24576M,
	APP_FREQ_12dot5M_FROM_XTAL24M,
}APP_CPU_FREQ_T;

/***********************************************
 * TYPEDEF DECLARATION
 **********************************************/

/***********************************************
 * FUNCTION DECLARATION
 **********************************************/
/**
 * \brief initial clock generate 
 * 
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_ckgen_init(void);

/**
 * \brief de-initial clock generate 
 * 
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_ckgen_deinit(void);

/**
 * \brief gate clock generate 
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_ckgen_set_gated(SYS_INDEX_E aIndex, uint32_t aValue);

/**
 * \brief set clock divisor 
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_ckgen_set_div(CLKDIV_INDEX_E aIndex, uint32_t aValue);

/**
 * \brief  set clock selection
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_ckgen_set_sel(CLKMUX_INDEX_E aIndex, uint8_t aValue);

/**
 * \brief  set application CPU clock
 *
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_ckgen_app_cpu_freq(APP_CPU_FREQ_T cpu_freq);

/**
 * \brief init sw reset
 * 
 * \return SYS_ERROR_E
 */

SYS_ERROR_E hx_drv_swrst_init(void);

/**
 * \brief de-init sw reset
 * 
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_swrst_deinit(void);

/**
 * \brief enable sw reset
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_swrst_en(SYS_RST_INDEX_E aIndex, uint32_t aValue);

/**
 * \brief set sc_ctrl sw reset
 * 
 * \param[in] sc_ctrl
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_swrst_sensorctrl_set(SENCTRL_RST_SEL_E sc_ctrl);

/**
 * \brief  set adc_ctrl sw reset 
 * 
 * \param[in] adc_ctrl
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_swrst_adcctrl_set(ADC_RST_SEL_E adc_ctrl);

/**
 * \brief get sc_ctrl sw reset
 * 
 * \param[out] sc_ctrl
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_swrst_sensorctrl_get(SENCTRL_RST_SEL_E *sc_ctrl);

/**
 * \brief  get adc_ctrl sw reset  
 * 
 * \param[out] adc_ctrl
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_swrst_adcctrl_get(ADC_RST_SEL_E *adc_ctrl);


/**
 * \brief  get PLL Reference
 *
 * \param[out] pll_ref
 * \return SYS_ERROR_E
 */
SYS_ERROR_E hx_drv_swrst_pllref_get(PLL_REF_SEL_E *pll_ref);


#endif /* PLATFORM_INC_HX_DRV_CKGEN_H_ */

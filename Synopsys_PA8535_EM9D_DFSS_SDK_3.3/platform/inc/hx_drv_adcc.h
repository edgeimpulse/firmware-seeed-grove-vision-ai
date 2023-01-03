/**
 * @file hx_drv_adcc.h
 * @author himax/902453
 * @brief 
 * @version V1.0.0
 * @date 2018-11-28
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef INC_HX_DRV_ADCC_H_
#define INC_HX_DRV_ADCC_H_

#include "embARC_toolchain.h"
#include "hx_drv_ckgen.h"
#include "hx_drv_pmu.h"


/**
 * \defgroup	ADCC_DRV	ADC Driver
 * \ingroup		ADCC_DRV
 * \brief		ADC Driver  Declaration
 */


/**
 * \enum    ADCC_ERROR_E
 * \brief   ADCC Errors Type 
 * 
 */
typedef enum ADCC_ERROR_S
{
	ADCC_NO_ERROR                     		= 0,	/**< No ERROR */
	ADCC_ERROR_NOT_INIT              	    = 1,	/**< ERROR MSG: not init */
	ADCC_ERROR_ALREADY_INIT                 = 2,	/**< ERROR MSG: already init */
	ADCC_ERROR_INVALID_PARAMETERS     		= 3,	/**< ERROR MSG: Invalid parameters */
 	ADCC_UNKNOWN_ERROR      				= 4,	/**< ERROR MSG: UNKNOWN ERROR*/
} ADCC_ERROR_E;


/**
 * \enum    ADCC_CHANNEL
 * \brief   ADCC Channel
 * 
 */
typedef enum adcc_channel {
	ADCC_CHANNEL0 = 0,		/*!< ADCC channel 0  */
	ADCC_CHANNEL1 = 1,		/*!< ADCC channel 1 */
	ADCC_CHANNEL2 = 2,		/*!< ADCC channel 2 */
	ADCC_CHANNEL3 = 3		/*!< ADCC channel 3 */
} ADCC_CHANNEL;


/**
 * \enum    ADCC_CALLBACK_E
 * \brief   ADCC Interrupt Callback
 * 
 */
typedef enum adcc_callback {
	ADCC_CH0_CB = 0,		/*!< ADCC channel 0 callback */
	ADCC_CH1_CB = 1,		/*!< ADCC channel 1 callback */
	ADCC_CH2_CB = 2,		/*!< ADCC channel 2 callback */
	ADCC_CH3_CB = 3,		/*!< ADCC channel 3 callback */
	ADCC_CONSTRAIN_CB = 4,	/*!< ADCC constrain callback */
	ADCC_SG_CB = 5			/*!< ADCC single shot callback */
} ADCC_CALLBACK_E;


/**
 * \enum    ADCC_DATA_TYPE
 * \brief   ADCC data type
 * 
 */
typedef enum adcc_data_type {
	ADCC_DATA_BYPASS = 0,		/*!< ADCC data type bypass  */
	ADCC_DATA_AVERAGE = 1,		/*!< ADCC data type average */
} ADCC_DATA_TYPE;


/**
 * \enum    ADCC_DATA_SEL
 * \brief   ADCC data select
 * 
 */
typedef enum adcc_data_select {
	ADCC_DATA_MUX = 0,			/*!< ADCC data select Mux  */
	ADCC_DATA_OFFSET = 1,		/*!< ADCC data select Offset */
} ADCC_DATA_SEL;


/**
 * \struct  ADCC_CFG_T
 * \brief   ADCC configuration
 */
typedef struct ADCC_CFG_S
{
	uint16_t enable;
	uint16_t single_shot_enable;
	uint16_t channel_mask;
	uint16_t sample_rate[4];
	uint16_t data_type[4];
	uint16_t offset[4];
	uint16_t high_threshold[4];
	uint16_t low_threshold[4];
	uint16_t int_delay;
	uint32_t int_mask;
	uint32_t int_status;
	uint16_t data_select[4];
} ADCC_CFG_T;


/**
 * \brief	ADCC Interrupt callback function
 *
 * \return	void
 */
typedef void (*ADCC_ISR_CB) (uint32_t int_status);


/**
 * \struct  ADCC_REG
 * \brief   ADCC register
 */
typedef volatile struct adcc_reg {
	uint32_t REG_ADCC_EN;				/*!< (0x000) : ADCC module enable */
	uint32_t REG_ADCC_SINGLE;			/*!< (0x004) : Single shot mode control enable */
	uint32_t REG_ADCC_CH_MASK;			/*!< (0x008) : input channel mask */
	uint32_t REG_ADCC_SR;				/*!< (0x00C) : channel 0~3 sample rate */
	uint32_t REG_ADCC_DATA_TYPE;		/*!< (0x010) : data type select (bypass/average) */
	uint32_t REG_ADCC_CH0_OFFSET;		/*!< (0x014) : CH0 offset(signed) */
	uint32_t REG_ADCC_CH1_OFFSET;		/*!< (0x018) : CH1 offset(signed) */
	uint32_t REG_ADCC_CH2_OFFSET;		/*!< (0x01C) : CH2 offset(signed) */
	uint32_t REG_ADCC_CH3_OFFSET;		/*!< (0x020) : CH3 offset(signed) */
	uint32_t REG_ADCC_CH0_TH_H;			/*!< (0x024) : CH0 Window High in/out interrupt threshold */
	uint32_t REG_ADCC_CH1_TH_H;			/*!< (0x028) : CH1 Window High in/out interrupt threshold */
	uint32_t REG_ADCC_CH2_TH_H;			/*!< (0x02C) : CH2 Window High in/out interrupt threshold */
	uint32_t REG_ADCC_CH3_TH_H;			/*!< (0x030) : CH3 Window High in/out interrupt threshold */
	uint32_t REG_ADCC_CH0_TH_L;			/*!< (0x034) : CH0 Window Low in/out interrupt threshold */
	uint32_t REG_ADCC_CH1_TH_L;			/*!< (0x038) : CH1 Window Low in/out interrupt threshold */
	uint32_t REG_ADCC_CH2_TH_L;			/*!< (0x03C) : CH2 Window Low in/out interrupt threshold */
	uint32_t REG_ADCC_CH3_TH_L;			/*!< (0x040) : CH3 Window Low in/out interrupt threshold */
	uint32_t REG_ADCC_INT_DELAY;		/*!< (0x044) : Interrupt disable time setting */
	uint32_t REG_ADCC_INT_MASK;			/*!< (0x048) : interrupt mask */
	uint32_t REG_ADCC_INT_CLR;			/*!< (0x04C) : ADCC interrupt clear flag */
	uint32_t REG_ADCC_DBG_SEL;			/*!< (0x050) : Debug signal select */
	uint32_t REG_ADCC_CH0_GETDATA;		/*!< (0x054) : CH0 Sample data output */
	uint32_t REG_ADCC_CH1_GETDATA;		/*!< (0x058) : CH1 Sample data output */
	uint32_t REG_ADCC_CH2_GETDATA;		/*!< (0x05C) : CH2 Sample data output */
	uint32_t REG_ADCC_CH3_GETDATA;		/*!< (0x060) : CH3 Sample data output */
	uint32_t REG_ADCC_GETDATA_SEL;		/*!< (0x064) : Sample data output select (0: Data Mux / 1: Data Offset) */
	uint32_t REG_ADCC_INT_STATUS;		/*!< (0x068) : Channel 0~3 interrupt saving */
} ADCC_REG, *ADCC_REG_PTR;


/**
 * \struct  ADC_REG
 * \brief   ADC register
 */
typedef volatile struct adc_reg {
	uint32_t REG_ADC_EN;				/*!< (0x000) : ADC module enable */
	uint32_t REG_ADC_PWRGAT;			/*!< (0x004) : ADC_PWRGAT */
	uint32_t REG_ADC_AREG0;				/*!< (0x008) : AREG0 */
	uint32_t REG_ADC_AREG1;				/*!< (0x00C) : AREG1 */
	uint32_t REG_ADC_AREG2;				/*!< (0x010) : AREG2 */
	uint32_t REG_ADC_AREG3;				/*!< (0x014) : AREG3 */
	uint32_t REG_ADC_AREG4;				/*!< (0x018) : AREG4 */
	uint32_t REG_ADC_DBG;				/*!< (0x01C) : DBG */
	uint32_t REG_ADC_XTAL_24M_CFG;		/*!< (0x020) : XTAL_24M_CFG */
} ADC_REG, *ADC_REG_PTR;


/**
 * \brief	Contains definitions of ADDC MACRO.
 * 
 */
#define ADCC_CH0					(1)
#define ADCC_CH1					(2)
#define ADCC_CH2					(4)
#define ADCC_CH3					(8)
#define ADCC_DATA_BYPASS			(0)
#define ADCC_DATA_AVERAGE			(1)
#define ADCC_DATA_SEL_MUX			(0)
#define ADCC_DATA_SEL_OFFSET		(1)

#define ADCC_CH0_SR_MASK			(0x0000001F)	/*!< [4:0]   = channel 0 sample rate */
#define ADCC_CH1_SR_MASK			(0x00001F00)	/*!< [12:8]  = channel 1 sample rate */
#define ADCC_CH2_SR_MASK			(0x001F0000)	/*!< [20:16] = channel 2 sample rate */
#define ADCC_CH3_SR_MASK			(0x1F000000)	/*!< [28:24] = channel 3 sample rate */

#define ADCC_CH0_INT_MASK			(0x0000003F)	/*!< [5:0]   = channel 0 interrupt status */
#define ADCC_CH1_INT_MASK			(0x00000FC0)	/*!< [11:6]  = channel 1 interrupt status */
#define ADCC_CH2_INT_MASK			(0x0003F000)	/*!< [17:12] = channel 2 interrupt status */
#define ADCC_CH3_INT_MASK			(0x00FC0000)	/*!< [23:18] = channel 3 interrupt status */
#define ADCC_CONSTRAIN_INT_MASK		(0x01000000)	/*!< [24] 	 = constrain interrupt status */
#define ADCC_SG_INT_MASK			(0x02000000)	/*!< [25] 	 = Single Shot interrupt status */
#define ADCC_ALL_INT_MASK			(0x03FFFFFF)

#define ADCC_CH0_SR_BIT_SFT			(0)				/*!< [4:0]   = channel 0 sample rate */
#define ADCC_CH1_SR_BIT_SFT			(8)				/*!< [12:8]  = channel 1 sample rate */
#define ADCC_CH2_SR_BIT_SFT			(16)			/*!< [20:16] = channel 2 sample rate */
#define ADCC_CH3_SR_BIT_SFT			(24)			/*!< [28:24] = channel 3 sample rate */

#define ADCC_CH0_DATA_TYPE_BIT_SFT	(0)				/*!< [0] = channel 0 data type */
#define ADCC_CH1_DATA_TYPE_BIT_SFT	(1)				/*!< [1] = channel 1 data type */
#define ADCC_CH2_DATA_TYPE_BIT_SFT	(2)				/*!< [2] = channel 2 data type */
#define ADCC_CH3_DATA_TYPE_BIT_SFT	(3)				/*!< [3] = channel 3 data type */

#define ADCC_CH0_DATA_SEL_BIT_SFT	(0)				/*!< [0] = channel 0 data select */
#define ADCC_CH1_DATA_SEL_BIT_SFT	(1)				/*!< [1] = channel 1 data select */
#define ADCC_CH2_DATA_SEL_BIT_SFT	(2)				/*!< [2] = channel 2 data select */
#define ADCC_CH3_DATA_SEL_BIT_SFT	(3)				/*!< [3] = channel 3 data select */

#define ADCC_CH0_HIGH_OUT_INT_BIT	(1<<0)
#define ADCC_CH0_HIGH_IN_INT_BIT	(1<<1)
#define ADCC_CH0_LOW_OUT_INT_BIT	(1<<2)
#define ADCC_CH0_LOW_IN_INT_BIT		(1<<3)
#define ADCC_CH0_HIGH_INT_BIT		(1<<4)
#define ADCC_CH0_LOW_INT_BIT		(1<<5)
#define ADCC_CH1_HIGH_OUT_INT_BIT	(1<<6)
#define ADCC_CH1_HIGH_IN_INT_BIT	(1<<7)
#define ADCC_CH1_LOW_OUT_INT_BIT	(1<<8)
#define ADCC_CH1_LOW_IN_INT_BIT		(1<<9)
#define ADCC_CH1_HIGH_INT_BIT		(1<<10)
#define ADCC_CH1_LOW_INT_BIT		(1<<11)
#define ADCC_CH2_HIGH_OUT_INT_BIT	(1<<12)
#define ADCC_CH2_HIGH_IN_INT_BIT	(1<<13)
#define ADCC_CH2_LOW_OUT_INT_BIT	(1<<14)
#define ADCC_CH2_LOW_IN_INT_BIT		(1<<15)
#define ADCC_CH2_HIGH_INT_BIT		(1<<16)
#define ADCC_CH2_LOW_INT_BIT		(1<<17)
#define ADCC_CH3_HIGH_OUT_INT_BIT	(1<<18)
#define ADCC_CH3_HIGH_IN_INT_BIT	(1<<19)
#define ADCC_CH3_LOW_OUT_INT_BIT	(1<<20)
#define ADCC_CH3_LOW_IN_INT_BIT		(1<<21)
#define ADCC_CH3_HIGH_INT_BIT		(1<<22)
#define ADCC_CH3_LOW_INT_BIT		(1<<23)
#define ADCC_CONSTRAIN_INT_BIT		(1<<24)
#define ADCC_SG_INT_BIT				(1<<25)


/**
 * \brief  Register default value
 * 
 */
#define DEFAULT_ADCC_CLK			(1000000)       /*!< 1MHz */ 
#define DEFAULT_ADCC_SR				3               /*!< 125Khz = maxRate / (2^div) */
#define DEFAULT_ADCC_ENABLE			0
#define DEFAULT_ADCC_SINGLE_SHOT	0
#define DEFAULT_ADCC_CH_MASK		(ADCC_CH0 | ADCC_CH1 | ADCC_CH2 | ADCC_CH3)
#define DEFAULT_ADCC_DATA_TYPE		ADCC_DATA_BYPASS
#define DEFAULT_ADCC_OFFSET			0
#define DEFAULT_ADCC_HIGH_TH		(0x900)
#define DEFAULT_ADCC_LOW_TH			(0x300)
#define DEFAULT_ADCC_INT_DELAY		0				/*!< 10ms, 0:There will be no delay 1,2,1023 : 5ms, 10ms, 5.115s */
#define DEFAULT_ADCC_INT_MASK		0	            /*!< (ADCC_CH0_INT_MASK | ADCC_CH1_INT_MASK | ADCC_CH2_INT_MASK | ADCC_CH3_INT_MASK | ADCC_CONSTRAIN_INT_MASK | ADCC_SG_INT_MASK) */
#define DEFAULT_ADCC_DATA_SELECT	ADCC_DATA_SEL_MUX


/**
 * \brief	init ADC Single End Mode
 *
 * \param[in]	none
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adc_init(void);


/**
 * \brief  init ADC Calculate Offset Mode
 *
 * \param[in]	none
 * \return	ADCC_ERROR_E
 *  */
ADCC_ERROR_E hx_drv_adc_calculate_offset_init();


/**
 * \brief Start ADC calculate offset
 *
 * \param[in]	adc_offset	 ADC offset
 * \return	ADCC_ERROR_E
 *  */
ADCC_ERROR_E hx_drv_adc_calculate_offset(uint16_t *adc_offset);


/**
 * \brief Start ADC calculate gain
 *
 * \param[in]	adc_gain	 ADC gain
 * \return	ADCC_ERROR_E
 *  */
ADCC_ERROR_E hx_drv_adc_calculate_gain(uint16_t *adc_gain);


/**
 * \brief	init ADCC Driver
 *
 * \param[in]	adcc_cfg	 ADCC configuration
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_init(ADCC_CFG_T *adcc_cfg);


/**
 * \brief	deinit ADCC Driver
 *
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_deinit();

/**
 * \brief	get ADCC default configuration
 *
 * \param[out]	adcc_cfg     ADCC configuration
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_get_defCfg(ADCC_CFG_T *adcc_cfg);


/**
 * \brief	set ADCC enable
 *
 * \param[in]	enable     enable addc setting
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_enable(uint8_t enable);

/**
 * \brief	 set ADCC single shot mode
 *
 * \param[in]	enable     enable addc single shot
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_single_shot(uint8_t enable);


/**
 * \brief	 set ADCC channel mask
 *
 * \param[in]	channel_mask     mask addc channel
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_channel_mask(uint8_t channel_mask);


/**
 * \brief	 get ADCC channel mask
 *
 * \param[out]	channel_mask     mask addc channel
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_get_channel_mask(uint8_t *channel_mask);


/**
 * \brief	  set ADCC channel sample rate
 *
 * \param[in]	channel         addc channel
 * \param[in]	sample_rate     addc sample rate
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_sample_rate(uint8_t channel, uint16_t sample_rate);


/**
 * \brief	  set ADCC channel data type
 *
 * \param[in]	data_type         adcc data type
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_data_type(uint16_t data_type);


/**
 * \brief	  set ADCC channel data offset
 *
 * \param[in]	channel         adcc channel
 * \param[in]	offset          adcc offset
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_data_offset(uint8_t channel, uint16_t offset);


/**
 * \brief	  set ADCC channel Window High in/out interrupt threshold
 *
 * \param[in]	channel             adcc channel
 * \param[in]	high_threshold      high threshold
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_high_threshold(uint8_t channel, uint16_t high_threshold);


/**
 * \brief	  set ADCC channel Window Low in/out interrupt threshold
 *
 * \param[in]	channel             adcc channel
 * \param[in]	low_threshold       low threshold
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_low_threshold(uint8_t channel, uint16_t low_threshold);


/**
 * \brief	  set ADCC interrupt delay time
 *
 * \param[in] int_delay           interrupt delay time
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_int_delay(uint16_t int_delay);


/**
 * \brief	  set ADCC channel interrupt mask
 *
 * \param[in] int_mask           interrupt mask
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_int_mask(uint32_t int_mask);


/**
 * \brief	  get ADCC channel interrupt mask
 *
 * \param[out] int_mask           interrupt mask
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_get_int_mask(uint32_t *int_mask);

/**
 * \brief	  set ADCC channel data selection
 *
 * \param[in] data_select          addc channel data selection
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_data_select(uint16_t data_select);


/**
 * \brief	  get ADCC channel sample data
 *
 * \param[in]  channel          addc channel 
 * \param[out] channel_data     addc channel data
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_get_sample_data(uint8_t channel, uint16_t *channel_data);


/**
 * \brief	  get ADCC channel interrupt status
 *
 * \param[out] int_status     addc channel interrupt status
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_get_int_status(uint32_t *int_status);


/**
 * \brief	  set ADCC channel interrupt clear
 *
 * \param[in] int_status     addc channel interrupt status
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_set_int_clear(uint32_t int_status);


/**
 * \brief	  Register ADCC channel callback function
 *
 * \param[in] cb_type     addc callback type
 * \param[in] cb_func     addc callback function
 * \return	ADCC_ERROR_E
 */
ADCC_ERROR_E hx_drv_adcc_register_cb(ADCC_CALLBACK_E cb_type, ADCC_ISR_CB cb_func);

#endif /* INC_HX_DRV_ADCC_H_ */

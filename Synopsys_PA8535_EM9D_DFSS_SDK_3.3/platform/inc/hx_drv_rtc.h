/**
 * @file hx_drv_rtc.h
 * @author himax/902452
 * @brief 
 * @version V1.0.0
 * @date 2018-10-17
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef INC_HX_DRV_RTC_H_
#define INC_HX_DRV_RTC_H_

/***********************************************
 * CONSTANT DEFINITION
 **********************************************/
/**
 * \brief   contains definitions of RTC enable/disable
 * 
 */
#define RTC_EN						1
#define RTC_DIS						0


/**
 * \brief contains definitions of RTC mode
 * 
 */
#define RTC_MODE_RTC				0
#define RTC_MODE_WDT				1
/***********************************************
 * EMULATOR DECLARATION
 **********************************************/
/**
 * \enum RTC_INDEX_E
 * \brief RTC INSTANCE
 */
typedef enum RTC_INDEX_S
{
	RTC_SENSOR                     		= 0,
	RTC_ADC              				= 1,
	RTC_MAX
} RTC_INDEX_E;


/**
 * \enum RTC_ERROR_E
 * \brief RTC Errors Type
 */
typedef enum RTC_ERROR_S
{
	RTC_NO_ERROR                     	= 0,	/**< No ERROR */
	RTC_ERROR_NOT_INIT              	= 1,	/**< ERROR MSG: not init */
	RTC_ERROR_ALREADY_INIT              = 2,	/**< ERROR MSG: already init */
	RTC_ERROR_INVALID_PARAMETERS        = 3,	/**< ERROR MSG: Invalid parameters */
	RTC_ERROR_NULL_POINTER				= 4,	/**< ERROR MSG: NULL pointer */
 	RTC_UNKNOWN_ERROR      				= 5,	/**< ERROR MSG: UNKNOWN ERROR*/
} RTC_ERROR_E;
/***********************************************
 * TYPEDEF DECLARATION
 **********************************************/
typedef void (*rtc_cb_t) (void* param);


/***********************************************
 * FUNCTION DECLARATION
 **********************************************/
/**
 * \brief initialize RTC
 * 
 * \return RTC_ERROR_E
 */
RTC_ERROR_E hx_drv_rtc_init(void);


/**
 * \brief de-initialize RTC
 * 
 * \return RTC_ERROR_E
 */
RTC_ERROR_E hx_drv_rtc_deinit(void);


/**
 * \brief register RTC callback function
 * 
 * \param[in] aIndex
 * \param[in] cb_fun
 * \return RTC_ERROR_E
 */
RTC_ERROR_E hx_drv_rtc_register_cb(RTC_INDEX_E aIndex, rtc_cb_t  cb_fun);


/**
 * \brief start RTC
 * 
 * \param[in] aIndex
 * \param[in] aMode
 * \param[in] aTime
 * \param[in] cb_fun
 * \return RTC_ERROR_E
 */
RTC_ERROR_E hx_drv_rtc_start(RTC_INDEX_E aIndex, uint32_t aMode, uint32_t aTime, rtc_cb_t  cb_fun);


/**
 * \brief stop RTC
 * 
 * \param[in] aIndex
 * \return RTC_ERROR_E
 */
RTC_ERROR_E hx_drv_rtc_stop(RTC_INDEX_E aIndex);


/**
 * \brief enable/disable RTC
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return RTC_ERROR_E
 */
RTC_ERROR_E hx_drv_rtc_set_en(RTC_INDEX_E aIndex, uint32_t aValue);


/**
 * \brief set RTC pre-scale
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return RTC_ERROR_E
 */
RTC_ERROR_E hx_drv_rtc_set_prescl(RTC_INDEX_E aIndex, uint32_t aValue);


/**
 * \brief set RTC preload
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return RTC_ERROR_E
 */
RTC_ERROR_E hx_drv_rtc_set_preld(RTC_INDEX_E aIndex, uint32_t aValue);


/**
 * \brief set RTC refresh
 * 
 * \param[in] aIndex
 * \return RTC_ERROR_E
 */
RTC_ERROR_E hx_drv_rtc_set_rf(RTC_INDEX_E aIndex);


/**
 * \brief set RTC mode
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return RTC_ERROR_E
 */
RTC_ERROR_E hx_drv_rtc_set_mode(RTC_INDEX_E aIndex, uint8_t aValue);

#endif /* INC_HX_DRV_RTC_H_ */

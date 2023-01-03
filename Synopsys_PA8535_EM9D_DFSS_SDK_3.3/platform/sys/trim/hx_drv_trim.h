/*
 * hx_drv_trim.h
 *
 *  Created on: 2020/04/29
 *      Author: 903730
 */
#ifndef SYS_TRIM_HX_DRV_TRIM_H_
#define SYS_TRIM_HX_DRV_TRIM_H_

/**
 * \enum TRIM_ITEM_INDEX
 * \brief TRIM item 
 */ 
typedef enum TRIM_ITEM_INDEX_S
{
    TRIM_RC36M = 0,
    TRIM_RC32K,
    TRIM_CLDO,
    TRIM_CLDO_N,
    TRIM_CLDO_R,
    TRIM_SLDO,
    TRIM_SLDO_N,
    TRIM_SLDO_R,
    TRIM_ADC,
}TRIM_ITEM_INDEX_E;

/**
 * \enum CALIB_MODE_INDEX
 * \brief CALIB mode 
 */ 
typedef enum CALIB_MODE_INDEX_S
{
    CALIB_AUTO = 0,
    CALIB_MANUAL,
}CALIB_MODE_INDEX_E;


void hx_drv_trim_debug_init(void);
void hx_drv_trim_set_value_debug_mode(uint8_t item, uint32_t val);
void hx_drv_trim_set_value_from_otp(uint8_t item);
void hx_drv_trim_fuse(uint8_t item, uint32_t val);
void hx_drv_rc_auto_calib(uint8_t item);
void hx_drv_rc_manual_calib(uint8_t item);

#endif /* SYS_TRIM_HX_DRV_TRIM_H_ */
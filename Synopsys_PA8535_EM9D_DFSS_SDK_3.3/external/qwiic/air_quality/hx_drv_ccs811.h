/*
 * hx_drv_ccs811.h
 *
 *  Created on: 2021/1/11
 *      Author: 904212
 */

#ifndef QWIIC_CCS811_HX_DRV_CCS811_H_
#define QWIIC_CCS811_HX_DRV_CCS811_H_

#include "board.h"
#include "hx_drv_iic_m.h"
#include "hx_drv_qwiic.h"

#define STATUS_REG 0x00
#define MEAS_MODE_REG 0x01
#define ALG_RESULT_DATA 0x02
#define ENV_DATA 0x05
#define NTC_REG 0x06
#define THRESHOLDS 0x10
#define BASELINE 0x11
#define HW_ID_REG 0x20
#define ERROR_ID_REG 0xE0
#define APP_START_REG 0xF4
#define SW_RESET 0xFF
#define CCS_811_ADDRESS_5A 0x5A
#define CCS_811_ADDRESS_5B 0x5B
#define GPIO_WAKE 0x5
#define DRIVE_MODE_IDLE 0x0
#define DRIVE_MODE_1SEC 0x10
#define DRIVE_MODE_10SEC 0x20
#define DRIVE_MODE_60SEC 0x30
#define INTERRUPT_DRIVEN 0x8
#define THRESHOLDS_ENABLED 0x4

HX_DRV_QWIIC_ERROR_E hx_drv_ccs811_initial(uint8_t);
HX_DRV_QWIIC_ERROR_E hx_drv_ccs811_receive_CO2_and_tVOC(uint16_t *,uint16_t *);
HX_DRV_QWIIC_ERROR_E hx_drv_ccs811_setEnvironmentalData(float, float);
#endif /* QWIIC_CCS811_HX_DRV_CCS811_H_ */

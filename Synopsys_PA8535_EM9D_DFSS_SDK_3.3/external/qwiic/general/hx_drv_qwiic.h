/*
 * hx_drv_qwiic.h
 *
 *  Created on: 2021¦~1¤ë11¤é
 *      Author: 902449
 */

#ifndef QWIIC_GENERAL_HX_DRV_QWIIC_H_
#define QWIIC_GENERAL_HX_DRV_QWIIC_H_

typedef enum {
    HX_DRV_QWIIC_PASS = 0,
    HX_DRV_QWIIC_ERROR = -1,
	HX_DRV_QWIIC_MORE_DATA = -2,
	HX_DRV_QWIIC_NO_DATA = -3,
} HX_DRV_QWIIC_ERROR_E;

HX_DRV_QWIIC_ERROR_E hx_drv_qwiic_set_reg(uint8_t slv_addr, uint8_t addr, uint8_t data);
HX_DRV_QWIIC_ERROR_E hx_drv_qwiic_set_multibyte_reg(uint8_t slv_addr, uint8_t addr, uint8_t *data, uint8_t data_len);
HX_DRV_QWIIC_ERROR_E hx_drv_qwiic_get_reg(uint8_t slv_addr, uint8_t addr, uint8_t *data);
HX_DRV_QWIIC_ERROR_E hx_drv_qwiic_set_cmd(uint8_t slv_addr, uint8_t cmd);
HX_DRV_QWIIC_ERROR_E hx_drv_qwiic_get_data(uint8_t slv_addr, uint8_t *data, uint8_t data_len);

#endif /* QWIIC_GENERAL_HX_DRV_QWIIC_H_ */

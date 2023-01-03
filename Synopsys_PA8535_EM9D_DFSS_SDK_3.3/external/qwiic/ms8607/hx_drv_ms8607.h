/*
 * hx_drv_ms8607.h
 *
 *  Created on: 2021¦~1¤ë11¤é
 *      Author: 902449
 */

#ifndef QWIIC_MS8607_HX_DRV_MS8607_H_
#define QWIIC_MS8607_HX_DRV_MS8607_H_

#include "board.h"
#include "hx_drv_iic_m.h"
#include "hx_drv_qwiic.h"


HX_DRV_QWIIC_ERROR_E hx_drv_ms8607_initial();

// p_data and t_data are 100 times of real answer
//temperature and pressure is 100 times of data
HX_DRV_QWIIC_ERROR_E hx_drv_ms8607_receive_t_p(int32_t* t_data, int32_t* p_data);

HX_DRV_QWIIC_ERROR_E hx_drv_ms8607_receive_h(float *humidity);

#endif /* QWIIC_MS8607_HX_DRV_MS8607_H_ */


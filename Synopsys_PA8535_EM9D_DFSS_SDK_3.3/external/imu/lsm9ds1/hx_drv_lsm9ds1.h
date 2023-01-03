/*
 * hx_drv_lsm9ds1.h
 *
 *  Created on: 2020/05/14
 *      Author: 903730
 */

#ifndef INC_HX_DRV_IMU_LSM9DS1_H_
#define INC_HX_DRV_IMU_LSM9DS1_H_

#include "board.h"
#include "hx_drv_iic_m.h"

typedef enum {
    HX_DRV_IMU_PASS = 0,
    HX_DRV_IMU_ERROR = -1,
	HX_DRV_IMU_MORE_DATA = -2,
	HX_DRV_IMU_NO_DATA = -3,
} HX_DRV_IMU_ERROR_E;

HX_DRV_IMU_ERROR_E hx_drv_imu_initial();
HX_DRV_IMU_ERROR_E hx_drv_imu_receive(float *x, float *y, float *z);
HX_DRV_IMU_ERROR_E hx_drv_imu_accelerationAvailable();
uint8_t hx_drv_imu_accelerationAvailableCount();


#endif /* INC_HX_DRV_IMU_LSM9DS1_H_ */

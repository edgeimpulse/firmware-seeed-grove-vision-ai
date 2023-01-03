/*
 * tflm_i2cm_function.h
 *
 *  Created on: 2020¦~8¤ë14¤é
 *      Author: 902449
 */

#ifndef LIBRARY_TFLM_SDK_LIB_INTERNAL_INC_TFLM_I2CM_FUNCTION_H_
#define LIBRARY_TFLM_SDK_LIB_INTERNAL_INC_TFLM_I2CM_FUNCTION_H_

typedef enum {
    HX_DRV_IIC_M_PASS = 0,
    HX_DRV_IIC_M_ERROR = -1,
} HX_DRV_IIC_M_ERROR_E;


HX_DRV_IIC_M_ERROR_E hx_drv_iic_write(uint8_t slave_addr_sft, uint8_t *addr, uint32_t addr_len, uint8_t *data, uint32_t data_len);

HX_DRV_IIC_M_ERROR_E hx_drv_iic_write_read(uint8_t slave_addr_sft, uint8_t *addr, uint32_t addr_len, uint8_t *data, uint32_t data_len);

#endif /* LIBRARY_TFLM_SDK_LIB_INTERNAL_INC_TFLM_I2CM_FUNCTION_H_ */

/*
 * tflm_i2cm_function.c
 *
 *  Created on: 2020¦~8¤ë14¤é
 *      Author: 902449
 */

#include <stdio.h>
#include <string.h>
#include "embARC.h"
#include "embARC_debug.h"

#include "apexextensions.h"
#include "hx_drv_iic_m.h"
#include "tflm_i2cm_function.h"
#include "board_config.h"
#include "hx_drv_timer.h"



#define HX_FLASH_IIC_M_ID         SS_IIC_1_ID     /*for 72 pin HIMAX EVB 2.54mm output use */


HX_DRV_IIC_M_ERROR_E hx_drv_iic_write(uint8_t slave_addr_sft, uint8_t *addr, uint32_t addr_len, uint8_t *data, uint32_t data_len)
{
	//hx_drv_i2cm_write_data return write len
	if(hx_drv_i2cm_write_data(SS_IIC_1_ID, slave_addr_sft, addr, addr_len, data, data_len)!= data_len+addr_len)
		return HX_DRV_IIC_M_ERROR;
	else
		return HX_DRV_IIC_M_PASS;
}

HX_DRV_IIC_M_ERROR_E hx_drv_iic_write_read(uint8_t slave_addr_sft, uint8_t *addr, uint32_t addr_len, uint8_t *data, uint32_t data_len)
{
	if(hx_drv_i2cm_write_stop_read(SS_IIC_1_ID, slave_addr_sft, addr, addr_len, data, data_len)!= addr_len+data_len)
		return HX_DRV_IIC_M_ERROR;
	else
		return HX_DRV_IIC_M_PASS;

}




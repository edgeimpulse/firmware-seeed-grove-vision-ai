/*
 * hx_drv_inp1bitparser_reg.h
 *
 *  Created on: 2019¦~6¤ë19¤é
 *      Author: 902447
 */

#ifndef SYS_INP1BITPARSER_HX_DRV_INP1BITPARSER_REG_H_
#define SYS_INP1BITPARSER_HX_DRV_INP1BITPARSER_REG_H_

#include "embARC_toolchain.h"

/**
 * \brief	INP 1BIT Parser register structure
 * \details	Detailed struct description of INP 1BIT Parser
 *	block register information, implementation of INP
 */
typedef volatile struct inp_1bitparser_reg_s {
	uint32_t reg_inpparser_enable;					/*!< (0x00) : INPParser address*/
	uint32_t reg_inpparser_FS_FD_FE_order_sel;		/*!< (0x04) : INPParser address*/
	uint32_t reg_inpparser_tg2utg;		/*!< (0x08) : INPParser address*/
	uint32_t reg_inpparser_blank_timeout_th;				/*!< (0x0C) : INPParser address*/
	uint32_t reg_inpparser_error_status2int_en;			/*!< (0x10) : INPParser address*/
	uint32_t reg_inpparser_error_status_out;		/*!< (0x14) : INPParser address*/
	uint32_t reg_inpparser_CS_out;		    /*!< (0x18) : INPParser address*/
	uint32_t reg_inpparser_VHsize;		    /*!< (0x1C) : INPParser address*/
	uint32_t reg_inpparser_FS_byte_0_3;		    /*!< (0x20) : INPParser address*/
	uint32_t reg_inpparser_FS_byte_4_7;		    /*!< (0x24) : INPParser address*/
	uint32_t reg_inpparser_FS_byte_8_11;		/*!< (0x28) : INPParser address*/
	uint32_t reg_inpparser_FS_byte_12_15;		/*!< (0x2C) : INPParser address*/
	uint32_t reg_inpparser_CRC16_sensor_hw;		/*!< (0x30) : INPParser address*/
	uint32_t reg_inpparser_error_clear;		/*!< (0x34) : INPParser address*/
	uint32_t reg_inpparser_hw_hvsize;		/*!< (0x38) : INPParser address*/
	uint32_t reg_inpparser_fs_fe_cycle;		/*!< (0x3C) : INPParser address*/
	uint32_t reg_inpparser_rx_dbg_cnt;		/*!< (0x40) : INPParser address*/
	uint32_t reg_inpparser_rx_dbg_31to00_dly_bit;		/*!< (0x44) : INPParser address*/
	uint32_t reg_inpparser_rx_dbg_63to32_dly_bit;		/*!< (0x48) : INPParser address*/
	uint32_t reg_inpparser_rx_dbg_95to64_dly_bit;		/*!< (0x4c) : INPParser address*/
	uint32_t reg_inpparser_fs_cycle_error_cnt_th;		/*!< (0x50) : INPParser address*/
	uint32_t reg_inpparser_fs_cycle_error_cnt;		/*!< (0x54) : INPParser address*/
	uint32_t reg_inpparser_VHsize_sw;				/*!< (0x58) : INPParser address*/
} inp_1bitparser_REG, *inp_1bitparser_REG_PTR;

/*Register default value*/
#define DEFAULT_INP1BITPARSER_ENABLE  		0
#define DEFAULT_INP1BITPARSER_FSORDER  	    0x1
#define DEFAULT_INP1BITPARSER_FDORDER  		0x1
#define DEFAULT_INP1BITPARSER_FEORDER  		0x1
#define DEFAULT_INP1BITPARSER_FESWAP  		0x0
#define DEFAULT_INP1BITPARSER_TG2UTG  		0x5
#define DEFAULT_INP1BITPARSER_BLANKTIMEOUT  0xFFFFFFFF
#define DEFAULT_INP1BITPARSER_ERRINT_EN	    0x1FF

#endif /* SYS_INP1BITPARSER_HX_DRV_INP1BITPARSER_REG_H_ */

/*
 * hx_drv_inp_reg.h
 *
 *  Created on: 2019¦~6¤ë19¤é
 *      Author: 902447
 */

#ifndef SYS_INP_HX_DRV_INP_REG_H_
#define SYS_INP_HX_DRV_INP_REG_H_

#include "embARC_toolchain.h"

/**
 * \brief	INP register structure
 * \details	Detailed struct description of INP
 *	block register information, implementation of INP
 */
typedef volatile struct inp_reg_s {
	uint32_t inp_en;					/*!< (0x00) : INP address*/
	uint32_t io_depth_msbyte_msbit;		/*!< (0x04) : INP address*/
	uint32_t reverse_hvsyncchange_inv;		/*!< (0x08) : INP address*/
	uint32_t fs_regen_en;				/*!< (0x0C) : INP address*/
	uint32_t inp_subsample;			/*!< (0x10) : INP address*/
	uint32_t inp_vsyncpulse_len;		/*!< (0x14) : INP address*/
	uint32_t inp_vsyncDELEFEdelay;		    /*!< (0x18) : INP address*/
	uint32_t inp_s2perrint;		    /*!< (0x1C) : INP address*/
	uint32_t inp_vsynccnt;		    /*!< (0x20) : INP address*/
	uint32_t inp_hsynccnt;		    /*!< (0x24) : INP address*/
	uint32_t inp_out_decnt;		       /*!< (0x28) : INP address*/
	uint32_t inp_out_le_cnt;       /*!< (0x28C) : INP address*/
} inp_REG, *inp_REG_PTR;

/*Register default value*/
#define DEFAULT_INP_ENABLE  		0
#define DEFAULT_INP_IOBIT  			INP_IOBIT_8BIT
#define DEFAULT_INP_DATADEPTH  		INP_DATADEPTH_8BIT
#define DEFAULT_INP_PIXELORDER  	INP_PIXELORDER_P0_P1
#define DEFAULT_INP_DATAENDIAN	    INP_DATAENDIAN_LS_FIRST
#define DEFAULT_INP_DATABUSNORMAL  	INP_DATABUS_NORMAL
#define DEFAULT_INP_HVSYNC_CHANGE   INP_HVSYNC_CHANGE_NORMAL
#define DEFAULT_INP_VSYNC_INVERSE   INP_VSYNC_INVERSE_NORMAL
#define DEFAULT_INP_HSYNC_INVERSE   INP_HSYNC_INVERSE_NORMAL
#define DEFAULT_INP_FS_REGEN	    INP_FS_REGEN_DISABLE
#define DEFAULT_INP_VSYNC_DELAY	    0
#define DEFAULT_INP_HSYNC_DELAY	    0
#define DEFAULT_INP_DE_DELAY	    0
#define DEFAULT_INP_LE_DELAY	    0
#define DEFAULT_INP_FE_DELAY	    0
#define DEFAULT_INP_SUBSAMPLE	    INP_SUBSAMPLE_DISABLE
#define DEFAULT_INP_VSYNCMODE	    INP_VSYNCMODE_CONVENTIONAL
#define DEFAULT_INP_PULSE_FRAMELEN	0

#endif /* SYS_INP_HX_DRV_INP_REG_H_ */

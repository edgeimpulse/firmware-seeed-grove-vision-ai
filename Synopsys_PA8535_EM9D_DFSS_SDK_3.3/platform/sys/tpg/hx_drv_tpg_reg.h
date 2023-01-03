/*
 * hx_drv_tpg_reg.h
 *
 *  Created on: 2019¦~6¤ë19¤é
 *      Author: 902447
 */

#ifndef SYS_TPG_HX_DRV_TPG_REG_H_
#define SYS_TPG_HX_DRV_TPG_REG_H_

#include "embARC_toolchain.h"

/**
 * \brief	TPG register structure
 * \details	Detailed struct description of TPG
 *	block register information, implementation of TPG
 */
typedef volatile struct TPG_reg_s {
	uint32_t TPG_EN_RST;				/*!< (0x00) : TPG address*/
	uint32_t TPG_CH123_DE_EMP_RDY;		/*!< (0x04) : TPG address*/
	uint32_t TPG_TG_V_POLMSWH;			/*!< (0x08) : TPG address*/
	uint32_t TPG_TG_V_FPSYBP;			/*!< (0x0c) : TPG address*/
	uint32_t TPG_TG_V_AC;				/*!< (0x10) : TPG address*/
	uint32_t TPG_TG_H_POL;				/*!< (0x14) : TPG address*/
	uint32_t TPG_TG_H_FPSYBP;			/*!< (0x18) : TPG address*/
	uint32_t TPG_TG_H_AC;				/*!< (0x1C) : TPG address*/
	uint32_t TPG_TG_SEL_DERGMS;			/*!< (0x20) : TPG address*/
	uint32_t TPG_CH1_PGSEL_MS_VAL;		/*!< (0x24) : TPG address*/
	uint32_t TPG_CH2_PGSEL_MS_VAL;		/*!< (0x28) : TPG address*/
	uint32_t TPG_CH3_PGSEL_MS_VAL;		/*!< (0x2C) : TPG address*/
	uint32_t TPG_FRAMEND;		/*!< (0x30) : TPG address*/
} TPG_REG, *TPG_REG_PTR;

/*TPG Register default value*/
#define DEFAULT_TPG_EN  				0
#define DEFAULT_TPG_CASE 				TPG_CASE_USERDEF
#define DEFAULT_TPG_TG_SEL	  			TPG_TG_CTRL_FROM_CH1_DE
#define DEFAULT_TPG_CH1_DE_SEL	  		TPG_TG_CH_DE_SEL_CONTINOUS_DIS
#define DEFAULT_TPG_CH2_DE_SEL	  		TPG_TG_CH_DE_SEL_OFF
#define DEFAULT_TPG_CH3_DE_SEL	  		TPG_TG_CH_DE_SEL_OFF
#define DEFAULT_TPG_CH1_EMPTY_CTRL	  	TPG_CH_EMPTY_CTRL_BYPASS
#define DEFAULT_TPG_CH2_EMPTY_CTRL	  	TPG_CH_EMPTY_CTRL_BYPASS
#define DEFAULT_TPG_CH3_EMPTY_CTRL	  	TPG_CH_EMPTY_CTRL_BYPASS
#define DEFAULT_TPG_CH1_EMPTY_SEL	  	TPG_CH1_EMPTY_SEL_1
#define DEFAULT_TPG_CH2_EMPTY_SEL	  	TPG_CH2_EMPTY_SEL_2
#define DEFAULT_TPG_CH3_EMPTY_SEL	  	TPG_CH3_EMPTY_SEL_3
#define DEFAULT_TPG_CH1_RDY_SEL	  	TPG_RDY_CH_SEL_NOT_CARE
#define DEFAULT_TPG_CH2_RDY_SEL	  	TPG_RDY_CH_SEL_NOT_CARE
#define DEFAULT_TPG_CH3_RDY_SEL	  	TPG_RDY_CH_SEL_NOT_CARE
#define DEFAULT_TPG_TG_DERG_MS	  	TPG_TG_DERG_OFF
#define DEFAULT_TPG_CH1_PG_SEL	  	TPG_CH_PG_SEL_IPG
#define DEFAULT_TPG_CH2_PG_SEL	  	TPG_CH_PG_SEL_IPG
#define DEFAULT_TPG_CH3_PG_SEL	  	TPG_CH_PG_SEL_IPG

#define DEFAULT_TPG_TG_MS	  		TPG_TG_V_MS_LINE
#define DEFAULT_TPG_TG_V_POL	  	TPG_TG_V_POL_VSYNC_HIGH
#define DEFAULT_TPG_TG_V_WH	  		TPG_TG_V_WH_NOHSYNC
#define DEFAULT_TPG_TG_H_POL	  	TPG_TG_H_POL_HSYNC_HIGH
#define DEFAULT_TPG_TG_H_FP	  		48
#define DEFAULT_TPG_TG_H_SY	  		96
#define DEFAULT_TPG_TG_H_BP	  		16
#define DEFAULT_TPG_TG_H_AC	  		640
#define DEFAULT_TPG_TG_V_FP	  		10
#define DEFAULT_TPG_TG_V_SY	  		2
#define DEFAULT_TPG_TG_V_BP	  		33
#define DEFAULT_TPG_TG_V_AC	  		480
#define DEFAULT_TPG_CH1_IPG_PAT		TPG_IPG_TYPE_XOR_ZOOMOUT
#define DEFAULT_TPG_CH1_IPG_PAT_VAL	1
#define DEFAULT_TPG_CH2_IPG_PAT		TPG_IPG_TYPE_XOR_ZOOMOUT
#define DEFAULT_TPG_CH2_IPG_PAT_VAL	1
#define DEFAULT_TPG_CH3_IPG_PAT		TPG_IPG_TYPE_XOR_ZOOMOUT
#define DEFAULT_TPG_CH3_IPG_PAT_VAL	1

#endif /* SYS_TPG_HX_DRV_TPG_REG_H_ */

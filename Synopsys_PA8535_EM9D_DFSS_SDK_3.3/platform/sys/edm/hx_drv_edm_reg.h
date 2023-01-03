/*
 * hx_drv_edm_reg.h
 *
 *  Created on: 2019¦~6¤ë19¤é
 *      Author: 902447
 */

#ifndef SYS_EDM_HX_DRV_EDM_REG_H_
#define SYS_EDM_HX_DRV_EDM_REG_H_

#include "embARC_toolchain.h"

/**
 * \brief	EDM register structure
 * \details	Detailed struct description of EDM
 *	block register information, implementation of EDM
 */
typedef volatile struct EDM_reg_s {
	uint32_t EDM_CRC_CFG;		    /*!< (0x00) : EDM address*/
	uint32_t EDM_CRC_CH0;  		    /*!< (0x04) : EDM address*/
	uint32_t EDM_CRC_CH1;			/*!< (0x08) : EDM address*/
	uint32_t EDM_CRC_CH2;			/*!< (0x0C) : EDM address*/
	uint32_t EDM_CRC_CONV;			/*!< (0x10) : EDM address*/
	uint32_t REG_EDM_CTRL;			/*!< (0x14) : EDM address*/
    uint32_t REG_EDM_MASK;			/*!< (0x18) : EDM address*/
    uint32_t REG_EDM_VTH;			/*!< (0x1C) : EDM address*/
    uint32_t REG_EDM_CON_VTH;		/*!< (0x20) : EDM address*/
    uint32_t REG_EDM_HTH;			/*!< (0x24) : EDM address*/
    uint32_t REG_EDM_CON_HTH;		/*!< (0x28) : EDM address*/
    uint32_t REG_EDM_CH0_DE_TH;		/*!< (0x2C) : EDM address*/
    uint32_t REG_EDM_CH1_DE_TH;		/*!< (0x30) : EDM address*/
    uint32_t REG_EDM_CH2_DE_TH;		/*!< (0x34) : EDM address*/
    uint32_t REG_EDM_HFP_TH;		/*!< (0x38) : EDM address*/
	uint32_t REG_EDM_HBP_TH;		/*!< (0x3C) : EDM address*/
	uint32_t REG_EDM_V_H_D_F_SEL;		/*!< (0x40) : EDM address*/
	uint32_t REG_EDM_DBG_SEL;		/*!< (0x44) : EDM address*/
	uint32_t REG_EDM_CON_FP_BP;		/*!< (0x48) : EDM address*/
	uint32_t REG_EDM_CON_VB_HB;		/*!< (0x4C) : EDM address*/
	uint32_t REG_EDM_STATUS;		/*!< (0x50) : EDM address*/
	uint32_t REG_EDM_INT_CLR;		/*!< (0x54) : EDM address*/
	uint32_t REG_WDT_EN;		/*!< (0x58) : EDM address*/
	uint32_t REG_WDT1_TH;		/*!< (0x5C) : EDM address*/
	uint32_t REG_WDT2_TH;		/*!< (0x60) : EDM address*/
	uint32_t REG_WDT3_TH;		/*!< (0x64) : EDM address*/
	uint32_t REG_EDM_CH0_DECNT;		/*!< (0x68) : EDM address*/
	uint32_t REG_EDM_CH1_DECNT;		/*!< (0x6C) : EDM address*/
	uint32_t REG_EDM_CH2_DECNT;		/*!< (0x70) : EDM address*/
	uint32_t REG_EDM_CONV_DECNT;		/*!< (0x74) : EDM address*/
	uint32_t REG_WDT1_CNT;		/*!< (0x78) : EDM address*/
	uint32_t REG_WDT2_CNT;		/*!< (0x7C) : EDM address*/
	uint32_t REG_WDT3_CNT;		/*!< (0x80) : EDM address*/
	uint32_t REG_EDM_FRAMECNT;		/*!< (0x84) : EDM address*/
	uint32_t REG_EDM_HFP_CNT;		/*!< (0x88) : EDM address*/
	uint32_t REG_EDM_HBP_CNT;		/*!< (0x8C) : EDM address*/
	uint32_t REG_EDM_HTOTAL_CNT;		/*!< (0x90) : EDM address*/
} EDM_REG, *EDM_REG_PTR;

#endif /* SYS_EDM_HX_DRV_EDM_REG_H_ */

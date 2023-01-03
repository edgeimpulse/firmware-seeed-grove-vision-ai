/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */

/**
 * \file
 * \ingroup	DEVICE_DW_SPI
 * \brief	DesignWare SPI driver hardware description related header file
 * \details	detailed hardware related definitions of DesignWare SPI driver
 */

#ifndef _DEVICE_DW_SPI_HAL_H_
#define _DEVICE_DW_SPI_HAL_H_

#include <platform/inc/ioctl.h>
/* DW APB SPI Configuration */
#ifndef DW_SPI_CALC_FIFO_LEN_ENABLE
#define DW_SPI_CALC_FIFO_LEN_ENABLE		(1)	/*!< Defaultly enable calculate fifo length */
#endif

#ifndef DW_SPI_MAX_FIFO_LENGTH
#define DW_SPI_MAX_FIFO_LENGTH			(256)	/*!< Max FIFO depth for designware SPI device */
#endif

#ifndef DW_SPI_MIN_FIFO_LENGTH
#define DW_SPI_MIN_FIFO_LENGTH			(2)	/*!< Min FIFO depth for designware SPI device */
#endif


/* DW APB SPI bit definitions */

/**
 * \name	DesignWare SPI HAL CTRL0 Macros
 * \brief	DesignWare SPI hal ctrl0 macros,
 * 	include dfs, scph, scppl, tmod, etc
 * @{
 */
#define DW_SPI_CTRLR0_DFS_MASK			(0x1f)
#define DW_SPI_CTRLR0_TRANS_MASK		(0xC00)
#define DW_SPI_CTRLR0_FORMAT_MASK		(0xC00000)
#define DW_SPI_CTRLR0_SSTE_MASK			(0x4000)
#define DW_SPI_CTRLR0_FORMAT_POS		22

#define DW_SPI_CTRLR0_SC_OFS			(8)
#define DW_SPI_CTRLR0_SC_MASK			(0x300)
#define DW_SPI_CTRLR0_SCPH_HIGH			(0x40)
#define DW_SPI_CTRLR0_SCPH_LOW			(0)
#define DW_SPI_CTRLR0_SCPOL_HIGH		(0x80)
#define DW_SPI_CTRLR0_SCPOL_LOW			(0)

#define DW_SPI_CTRLR0_TMOD_MASK			(0x300)
#define DW_SPI_TMOD_TRANSMIT_RECEIVE		(0)
#define DW_SPI_TMOD_TRANSMIT_ONLY		(0x100)
#define DW_SPI_TMOD_RECEIVE_ONLY		(0x200)
#define DW_SPI_TMOD_EEPROM_READ_ONLY		(0x300)

#define DW_SPI_CTRLR0_FRF_MOTOROLA		(0x0)
#define DW_SPI_CTRLR0_FRF_TI			(0x10)
#define DW_SPI_CTRLR0_FRF_MICROWIRE		(0x20)

#define DW_SPI_CTRLR0_SLV_OE_DISABLE		(1<<10)
#define DW_SPI_CTRLR0_SLV_OE_ENABLE		(0)

#define DW_SPI_SPI_CTRLR0_INST_L_MASK			(0x300)
#define DW_SPI_SPI_CTRLR0_INST_L_POS			8
#define DW_SPI_SPI_CTRLR0_ADDR_L_MASK			(0x3C)
#define DW_SPI_SPI_CTRLR0_ADDR_L_POS			2
#define DW_SPI_SPI_CTRLR0_TRANSFER_TYPE_MASK	(0x3)
#define DW_SPI_SPI_CTRLR0_TRANSFER_TYPE_POS		0
#define DW_SPI_SPI_CTRLR0_WAIT_CYCLE_MASK		(0xF800)
#define DW_SPI_SPI_CTRLR0_WAIT_CYCLE_POS		11
#define DW_SPI_SPI_CTRLR0_XIP_INST_EN_MASK		0x100000
#define DW_SPI_SPI_CTRLR0_XIP_INST_EN_POS		20
#define DW_SPI_SPI_CTRLR0_XIP_DFS_HC_MASK		0x80000
#define DW_SPI_SPI_CTRLR0_XIP_DFS_HC_POS		19


#define DW_SPI_FLASH_WIP_POS					0
#define DW_SPI_FLASH_WRITE_ENABLE_POS			1
#define DW_SPI_MXIC_FLASH_QUAD_ENABLE_MASK		0x40
#define DW_SPI_MXIC_FLASH_QUAD_ENABLE_POS		6
#define DW_SPI_WINBOND_FLASH_QUAD_ENABLE_MASK	0x02
#define DW_SPI_WINBOND_FLASH_QUAD_ENABLE_POS	1
#define DW_SPI_GIGADEV_E_FLASH_QUAD_ENABLE_MASK	0x02
#define DW_SPI_GIGADEV_E_FLASH_QUAD_ENABLE_POS	1
#define DW_SPI_GIGADEV_E_FLASH_DC_MASK			0x10
#define DW_SPI_GIGADEV_E_FLASH_DC_POS			4



#define DW_SPI_FLASH_CMD_WRITE_STATUS			0x01
#define DW_SPI_FLASH_CMD_WRITE_STATUS2			0x31
#define DW_SPI_FLASH_CMD_VOLATILE_WRITE			0x50
#define DW_SPI_FLASH_CMD_SINGLE_WRITE			0x02
#define DW_SPI_FLASH_CMD_1X_ADDR_QUAD_WRITE		0x32
#define DW_SPI_FLASH_CMD_QUAD_WRITE				0x38
#define DW_SPI_FLASH_CMD_SINGLE_READ			0x03
#define DW_SPI_FLASH_CMD_DUAL_READ_SINGLE_ADDR	0x3B
#define DW_SPI_FLASH_CMD_DUAL_READ				0xBB
#define DW_SPI_FLASH_CMD_QUAD_READ				0xEB
#define DW_SPI_FLASH_CMD_STATUS_CHECK			0x05
#define DW_SPI_FLASH_CMD_STATUS2_CHECK			0x35
#define DW_SPI_FLASH_CMD_WRITE_ENABLE			0x06
#define DW_SPI_FLASH_CMD_ERASE_ALL				0x60
#define DW_SPI_FLASH_CMD_ERASE_SECTOR			0x20
#define DW_SPI_FLASH_CMD_FLASH_INFO				0x9F
#define DW_SPI_FLASH_MXIC_PROTECT_MASK			0xBC
#define DW_SPI_FLASH_WINBOND_PROTECT_MASK		0xFC
#define DW_SPI_FLASH_WINBOND_PROTECT2_MASK		0x79
#define DW_SPI_FLASH_GIGADEV_C_PROTECT_MASK		0x9C
#define DW_SPI_FLASH_GIGADEV_E_PROTECT_MASK		0xFC
#define DW_SPI_FLASH_GIGADEV_E_PROTECT2_MASK	0x5D

#define DW_SPI_XIP_CTRL_FORMAT_MASK				0x3
#define DW_SPI_XIP_CTRL_FORMAT_POS				0
#define DW_SPI_XIP_CTRL_ADDR_L_MASK				(0xF0)
#define DW_SPI_XIP_CTRL_ADDR_L_POS				4
#define DW_SPI_XIP_CTRL_INST_L_MASK				(0x600)
#define DW_SPI_XIP_CTRL_INST_L_POS				9
#define DW_SPI_XIP_CTRL_WAIT_CYCLE_MASK			(0x3E000)
#define DW_SPI_XIP_CTRL_WAIT_CYCLE_POS			13
#define DW_SPI_XIP_CTRL_XIP_EN_MASK				(0x400000)
#define DW_SPI_XIP_CTRL_XIP_EN_POS				22
#define DW_SPI_XIP_CTRL_MODE_BIT_L_MASK			(0xC000000)
#define DW_SPI_XIP_CTRL_MODE_BIT_L_POS			26
#define DW_SPI_XIP_CTRL_DFS_HC_MASK				0x40000
#define DW_SPI_XIP_CTRL_DFS_HC_POS				18

#define DW_SPI_SPI_EEPROM_WINBOND_CH0			0xEF
#define DW_SPI_SPI_EEPROM_WINBOND_CH1			0x60
#define DW_SPI_SPI_EEPROM_WINBOND33V_CH1		0x40

#define DW_SPI_SPI_EEPROM_MXIC_CH0				0xC2
#define DW_SPI_SPI_EEPROM_GIGADEV_CH0			0xC8
#define DW_SPI_SPI_EEPROM_GIGADEV_C_CH1			0x64
#define DW_SPI_SPI_EEPROM_GIGADEV_E_CH1			0x65

/** @} */

/**
 * \name	DesignWare SPI HAL ISR Flags
 * \brief	DesignWare SPI hal Interrupt Status Flags
 * @{
 */
#define DW_SPI_TX_OVERFLOW_ERROR		(0x2)
#define DW_SPI_RX_UNDERFLOW_ERROR		(0x4)
#define DW_SPI_RX_OVERFLOW_ERROR		(0x8)

#define DW_SPI_ISR_RX_FIFO_INT_MASK		(0x10)
#define DW_SPI_ISR_TX_FIFO_INT_MASK		(0x1)
#define DW_SPI_ISR_TX_OVERFLOW_INT_MASK		(0x2)
#define DW_SPI_ISR_RX_UNDERFLOW_INT_MASK	(0x4)
#define DW_SPI_ISR_RX_OVERFLOW_INT_MASK		(0x8)
/** @} */

/**
 * \name	DesignWare SPI HAL SR Flags
 * \brief	DesignWare SPI hal Status Flags
 * @{
 */
#define DW_SPI_SR_DCOL				(0x40)
#define DW_SPI_SR_TXE				(0x20)
#define DW_SPI_SR_RFF				(0x10)
#define DW_SPI_SR_RFNE				(0x8)
#define DW_SPI_SR_TFE				(0x4)
#define DW_SPI_SR_TFNF				(0x2)
#define DW_SPI_SR_BUSY				(0x1)
/** @} */

/**
 * \name	DesignWare SPI HAL SSI Enable Macros
 * \brief	DesignWare SPI hal ssi enable macros
 * @{
 */
/* Macros */
#define DW_SPI_SSI_ENABLE			(1)	/*!< SSI Enable */
#define DW_SPI_SSI_DISABLE			(0)	/*!< SSI Disable */
/** @} */

/**
 * \name	DesignWare SPI HAL IMR Macros
 * \brief	DesignWare SPI hal interrupt mask macros
 * @{
 */
#define DW_SPI_IMR_MSTIM			(0x20)	/*!< Multi-Master Contention Interrupt Mask */
#define DW_SPI_IMR_RXFIM			(0x10)	/*!< Receive FIFO Full Interrupt Mask */
#define DW_SPI_IMR_RXOIM			(0x08)	/*!< Receive FIFO Overflow Interrupt Mask */
#define DW_SPI_IMR_RXUIM			(0x04)	/*!< Receive FIFO Underflow Interrupt Mask */
#define DW_SPI_IMR_TXOIM			(0x02)	/*!< Transmit FIFO Overflow Interrupt Mask */
#define DW_SPI_IMR_TXEIM			(0x01)	/*!< Transmit FIFO Empty Interrupt Mask */

#define DW_SPI_IMR_XFER				(DW_SPI_IMR_TXEIM|DW_SPI_IMR_RXFIM|DW_SPI_IMR_TXOIM|DW_SPI_IMR_RXOIM|DW_SPI_IMR_RXUIM)
/** @} */

#define DW_SPI_SSI_IDLE				(1)
#define DW_SPI_SPI_TRANSMIT			(1)
#define DW_SPI_SPI_RECEIVE			(2)
#define DW_SPI_SSI_MASTER			(1)
#define DW_SPI_SSI_SLAVE			(0)


#endif /* _DEVICE_DW_SPI_HAL_H_ */

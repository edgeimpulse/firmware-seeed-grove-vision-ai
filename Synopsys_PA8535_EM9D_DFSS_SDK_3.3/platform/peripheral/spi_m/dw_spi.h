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
 * \brief	DesignWare SPI driver header file
 * \ingroup	DEVICE_DW_SPI
 */

#ifndef _DEVICE_DW_SPI_H_
#define _DEVICE_DW_SPI_H_


#ifndef BL_USE
#include "hx_drv_spi_m.h"
#include "arc_exception.h"
#else
#include <stdint.h>
#include <stdbool.h>
#endif
/**
 * if this header file is included,
 * will indicate that this designware spi device
 * is used
 */
#ifndef BL_USE
#define DEVICE_USE_DESIGNWARE_SPI

#define DW_SPI_IN_FREE			(0)					/*!< Currently not in spi transfer */
#define DW_SPI_IN_XFER			(DEV_IN_TX|DEV_IN_RX|DEV_IN_XFER)	/*!< Currently in spi transfer */
#define DW_SPI_IN_TX			(DEV_IN_TX|DEV_IN_XFER)			/*!< Currently in spi tx */
#define DW_SPI_IN_RX			(DEV_IN_RX|DEV_IN_XFER)			/*!< Currently in spi rx */

#define DW_SPI_GINT_DISABLED		(0)		/*!< designware interrupt disabled for control spi irq/fiq */
#define DW_SPI_GINT_ENABLE		(1<<0)		/*!< designware interrupt enabled for control spi irq/fiq */

#define DW_SPI_MASTER_SUPPORTED		(0x1)	/*!< Support Designware SPI Master Mode */
#define DW_SPI_SLAVE_SUPPORTED		(0x2)	/*!< Support Designware SPI Slave Mode */
/*!< Support Designware SPI Both Master and Slave Mode */
#define DW_SPI_BOTH_SUPPORTED		(DW_SPI_MASTER_SUPPORTED|DW_SPI_SLAVE_SUPPORTED)
#else
#define DMAC_MEM_CHAN_CNT (16)
#endif
#define DW_SPI_INVALID_INTNO		(DEV_INTNO_INVALID)

typedef void (*spi_drv_cb_t) (void );

#ifndef BL_USE
#define DW_SPI_OBJECT	DEV_SPI*
#else
#define DW_SPI_OBJECT	int
#endif


/**
 * \defgroup	DEVICE_DW_SPI_REGSTRUCT		DesignWare SPI Register Structure
 * \ingroup	DEVICE_DW_SPI
 * \brief	contains definitions of DesignWare SPI register structure.
 * \details	detailed description of DesignWare SPI register information
 * @{
 */
/**
 * \brief	DesignWare SPI register structure
 * \details	Detailed struct description of DesignWare SPI
 * 	block register information, implementation of dev_spi_info::spi_regs
 */
typedef volatile struct dw_spi_reg
{
	/*!< Control Register */
	/*!< SPI Control Register 0  (0x0) */
	uint32_t CTRLR0;
	/*!< SPI Control Register 1  (0x4) */
	uint32_t CTRLR1;
	/*!< Enable Register */
	/*!< SPI Enable Register  (0x8) */
	uint32_t SSIENR;
	/*!< SPI Microwire Control Register  (0xC) */
	uint32_t MWCR;
	/*!< SPI Slave Enable Register  (0x10) */
	uint32_t SER;
	/*!< SPI Baud Rate Select Register  (0x14) */
	uint32_t BAUDR;
	/*!< TX and RX FIFO Control Register */
	/*!< SPI Transmit FIFO Threshold Level Register  (0x18) */
	uint32_t TXFTLR;
	/*!< SPI Receive  FIFO Threshold Level Register  (0x1C) */
	uint32_t RXFTLR;
	/*!< SPI Transmit FIFO Level Register  (0x20) */
	uint32_t TXFLR;
	/*!< SPI Receive  FIFO Level Register  (0x24) */
	uint32_t RXFLR;
	/*!< SPI Status   Register  (0x28) */
	uint32_t SR;
	/*!< Interrupt Enable/Disable/Control Registers */
	/*!< SPI Interrupt Mask Register  (0x2C) */
	uint32_t IMR;
	/*!< SPI Interrupt Status Register  (0x30) */
	uint32_t ISR;
	/*!< SPI Raw Interrupt Status Register (0x34) */
	uint32_t RISR;
	/*!< SPI Transmit FIFO Overflow Interrupt Clear Register  (0x38) */
	uint32_t TXOICR;
	/*!< SPI Receive  FIFO Overflow Interrupt Clear Register  (0x3C) */
	uint32_t RXOICR;
	/*!< SPI Receive FIFO Underflow Interrupt Clear Register  (0x40) */
	uint32_t RXUICR;
	/*!< SPI Multi-Master Interrupt Clear Register  (0x44) */
	uint32_t MSTICR;
	/*!< SPI Interrupt Clear Register  (0x48) */
	uint32_t ICR;
	/*!< DMA Control Register  (0x4C) */
	uint32_t DMACR;
	/*!< DMA Transmit Data Level  (0x50) */
	uint32_t DMATDLR;
	/*!< DMA Receive Data Level  (0x54) */
	uint32_t DMARDLR;
	/*!< SPI Identification Register  (0x58) */
	uint32_t IDR;
	/*!< SPI CoreKit ID Register (Value after Reset : 0x3332322A)  (0x5C) */
	uint32_t SSI_VER_ID;
	/*!< Data Register */
	/*!< SPI DATA Register for both Read and Write  (0x60) */
	uint32_t DATAREG;
	/*!< More SPI DATA Register for both Read and Write  (0x64-0xEC) */
	uint32_t DRS[35];
	/** 0xF0, RxD Sample Delay Register (0xf0) */
	uint32_t RX_SAMPLE_DLY;
	/** 0xF4, SPI_CTRLR0  Register (0xf4) */
	uint32_t SPI_CTRLR0;
	/** 0xF8, DDR_DRIVE_EDGE Register (0xf8) */
	uint32_t DDR_DRIVE_EDGE;
	/** 0xFC, XIP_MODE_BITS Register (0xfc) */
	uint32_t XIP_MODE_BITS;
	/** 0x100, XIP_INCR_INST Register (0x100) */
	uint32_t XIP_INCR_INST;
	/** 0x104, XIP_WRAP_INST  Register (0x104) */
	uint32_t XIP_WRAP_INST;
	/** 0x108, XIP_CTRL  Register (0x108) */
	uint32_t XIP_CTRL;
	/** 0x10C, XIP_SER  Register (0x10c) */
	uint32_t XIP_SER;


} DW_SPI_REG, *DW_SPI_REG_PTR;
/** @} */

typedef volatile struct XIP_spi_reg
{
	uint32_t SSI0_XIP_EN;
	uint32_t SSI1_XIP_EN;
	uint32_t SSI_DMAC_MUX;

} XIP_SPI_REG, *XIP_SPI_REG_PTR;

#ifndef BL_USE
/** Designware SPI Message Transfer */
typedef struct dw_spi_transfer {
	uint32_t xfer_len;
	uint32_t tx_idx;
	uint32_t rx_idx;
	uint32_t nbytes;
	DEV_SPI_TRANSFER *tx_xfer;
	DEV_SPI_TRANSFER *rx_xfer;
} DW_SPI_TRANSFER, *DW_SPI_TRANSFER_PTR;
#endif
/**
 * \brief	DesignWare SPI control structure definition
 * \details	implement of dev_spi_info::dev_spi_info
 */
typedef struct dw_spi_ctrl {
	DW_SPI_REG *dw_spi_regs;	/*!< spi register */
	uint32_t dw_apb_bus_freq;	/*!< spi ip apb bus frequency */
	uint32_t rx_sampledly;		/*!< RxD Sample Delay */
#ifndef BL_USE
	/* Variables which should be set during object implementation */
	uint32_t support_modes;		/*!< supported spi modes */
	uint32_t intno;			/*!< interrupt no */
	uint32_t int_status;		/*!< spi interrupt status */
	uint32_t tx_fifo_len;		/*!< transmit fifo length */
	uint32_t rx_fifo_len;		/*!< receive fifo length */
	INT_HANDLER dw_spi_int_handler;	/*!< spi interrupt handler */
	INT_HANDLER dw_spi_tx_ptl_int_handler;	/*!< spi interrupt handler */
	/* Variables which always change during spi operation */

	DW_SPI_TRANSFER dw_xfer;	/*!< designware spi transfer */
#endif
	uint32_t data_reg_addr;
	uint32_t dmac_mux_val;
} DW_SPI_CTRL, *DW_SPI_CTRL_PTR;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \defgroup	DEVICE_DW_SPI_FUNCDLR		DesignWare SPI Function Declaration
 * \ingroup	DEVICE_DW_SPI
 * \brief	contains declarations of designware spi functions.
 * \details	This are only used in \ref dw_spi_obj.c
 * @{
 */
#ifndef BL_USE
extern int32_t dw_spi_open (DW_SPI_OBJECT spi_obj, uint32_t mode, uint32_t param);
#else
extern int32_t dw_spi_open (DW_SPI_OBJECT spi_obj, uint32_t mode, uint32_t param, uint32_t apb_bus_freq);
#endif
extern int32_t dw_spi_close (DW_SPI_OBJECT spi_obj);
#ifndef BL_USE
extern int32_t dw_spi_control (DW_SPI_OBJECT spi_obj, uint32_t ctrl_cmd, void *param);
extern int32_t dw_spi_write (DW_SPI_OBJECT spi_obj, const void *data, uint32_t len);
extern int32_t dw_spi_write_int (DW_SPI_OBJECT spi_obj, const void *data, uint32_t len);
extern int32_t dw_spi_write_uDMA (DW_SPI_OBJECT spi_obj, const void *data, uint32_t len);
extern int32_t dw_spi_write_ptl_cus_uDMA (DW_SPI_OBJECT spi_obj, void *data, uint32_t len, const void *header_buf, uint32_t header_len);
extern int32_t dw_spi_write_ptl_uDMA (DW_SPI_OBJECT spi_obj, void *data, uint32_t len, uint8_t data_type, SPI_M_ACCESS_MODE_E mode);
extern int32_t dw_spi_write_ptl_halt (DW_SPI_OBJECT spi_obj);
extern int32_t dw_spi_read (DW_SPI_OBJECT spi_obj, void *data, uint32_t len);
extern int32_t dw_spi_read_int (DW_SPI_OBJECT spi_obj, void *data, uint32_t len);
extern int32_t dw_spi_read_uDMA (DW_SPI_OBJECT spi_obj, void *data, uint32_t len);

//for interrupt ISR
extern void dw_spi_isr(DW_SPI_OBJECT spi_obj, void *ptr);
//for uDMA write and uDMA write protocol ISR
extern void dw_spi_tx_ptl_isr(DW_SPI_OBJECT spi_obj, void *ptr);

//for uDMA read check if finish reading. true is finish reading
extern bool dw_spi_read_uDMA_status(DW_SPI_OBJECT spi_obj);
#endif

extern int32_t dw_spi_eeprom_update_flash_info(DW_SPI_OBJECT spi_obj);
extern int32_t dw_spi_eeprom_SetXIP (DW_SPI_OBJECT spi_obj, bool enable);
extern int32_t dw_spi_eeprom_SetXIP_dual (DW_SPI_OBJECT spi_obj, bool enable);
extern int32_t dw_spi_eeprom_erase_all (DW_SPI_OBJECT spi_obj);
extern int32_t dw_spi_eeprom_erase_sector (DW_SPI_OBJECT spi_obj, uint32_t addr);
extern int32_t dw_spi_eeprom_word_dual_read (DW_SPI_OBJECT spi_obj, uint32_t addr, uint32_t *data, uint32_t bytes_len);
extern int32_t dw_spi_eeprom_word_write (DW_SPI_OBJECT spi_obj, uint32_t addr, uint32_t *data, uint32_t bytes_len);
extern int32_t dw_spi_eeprom_write (DW_SPI_OBJECT spi_obj, uint32_t addr, uint8_t *data, uint32_t len, uint8_t word_switch);
extern bool dw_spi_eeprom_GetXIP_status (DW_SPI_OBJECT spi_obj);
extern int32_t dw_spi_eeprom_disable_XIP_base_only(DW_SPI_OBJECT spi_obj);

#ifndef BL_USE
extern int32_t dw_spi_eeprom_ID (DW_SPI_OBJECT spi_obj, unsigned char *id_info);
extern int32_t dw_spi_get_busy_status (DW_SPI_OBJECT spi_obj);
extern int32_t dw_spi_eeprom_Send_Op_code (DW_SPI_OBJECT spi_obj, uint8_t *data, uint32_t len);
extern int32_t dw_spi_eeprom_read (DW_SPI_OBJECT spi_obj, uint32_t addr, uint8_t *data, uint32_t len);
extern int32_t dw_spi_eeprom_2read (DW_SPI_OBJECT spi_obj, uint32_t addr, uint8_t *data, uint32_t len);
extern int32_t dw_spi_eeprom_4read (DW_SPI_OBJECT spi_obj, uint32_t addr, uint8_t *data, uint32_t len);
extern int32_t dw_spi_eeprom_word_single_read (DW_SPI_OBJECT spi_obj, uint32_t addr, uint32_t *data, uint32_t bytes_len);
extern int32_t dw_spi_eeprom_word_quad_read (DW_SPI_OBJECT spi_obj, uint32_t addr, uint32_t *data, uint32_t bytes_len);
extern int32_t dw_spi_eeprom_4write (DW_SPI_OBJECT spi_obj, uint32_t addr, uint8_t *data, uint32_t len);



extern void dw_spi_register_tx_cb(spi_drv_cb_t aRWritecb);
extern void dw_spi_register_rx_cb(spi_drv_cb_t aReadcb);
#endif
/** @} */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* _DEVICE_DW_SPI_H_ */

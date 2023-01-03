/* ------------------------------------------
 * Copyright (c) 2018, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:

 * 1) Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided
 * with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its
 * contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */
#ifndef _SS_SPI_SLAVE_H_
#define _SS_SPI_SLAVE_H_

/* the wrapper of subsystem spi slave driver */
#include <platform/inc/hx_drv_spi_s.h>

#define SS_SPI_SLV_FLAG_TX_READY		(1 << 0) /* interrupt tx */
#define SS_SPI_SLV_FLAG_RX_READY		(1 << 1) /* interrupt rx */
#define SS_SPI_SLV_FLAG_BUSY			(1 << 2)
#define SS_SPI_SLV_FLAG_TX_RX			(1 << 3) /* both tx and rx */
#define SS_SPI_SLV_FLAG_ERROR			(1 << 4)

typedef void (*spiss_cb_t) (void );

typedef struct ss_spi_slave_dev_context
{
	uint32_t reg_base;
	uint32_t dev_id;

	uint8_t intno_rx;
	uint8_t intno_tx;
	uint8_t intno_idle;
	uint8_t intno_err;

	uint32_t bus_freq;
	volatile uint32_t flags;

	DEV_CALLBACK int_rx_cb;
	DEV_CALLBACK int_tx_cb;
	DEV_CALLBACK int_err_cb;
	DEV_SPI_SLV_INFO *info;
} SS_SPI_SLV_DEV_CONTEXT;

extern int32_t ss_spi_slave_open(SS_SPI_SLV_DEV_CONTEXT * ctx, uint32_t mode, uint32_t param);
extern int32_t ss_spi_slave_close(SS_SPI_SLV_DEV_CONTEXT *ctx);
extern int32_t ss_spi_slave_control(SS_SPI_SLV_DEV_CONTEXT * ctx, uint32_t ctrl_cmd, void *param);
extern int32_t ss_spi_slave_write(SS_SPI_SLV_DEV_CONTEXT*ctx, const void *data, uint32_t len);
extern int32_t ss_spi_slave_write_ptl(SS_SPI_SLV_DEV_CONTEXT*ctx, const void *data, uint32_t len, uint8_t data_type);
extern int32_t ss_spi_slave_write_ptl_cus(SS_SPI_SLV_DEV_CONTEXT*ctx, const void *data, uint32_t len, 
										 const void *header_buf, uint32_t header_len);

extern void ss_spi_slave_register_tx_cb(spiss_cb_t aWritecb);
extern void ss_spi_slave_register_rx_cb(spiss_cb_t aReadcb);
extern void ss_spi_slave_register_rx_evt_cb(spiss_cb_t aReadEvtcb);

extern int32_t ss_spi_slave_write_halt(SS_SPI_SLV_DEV_CONTEXT*ctx);
extern int32_t ss_spi_slave_read(SS_SPI_SLV_DEV_CONTEXT*ctx, void *data, uint32_t len);
extern int32_t ss_spi_slave_read_halt(SS_SPI_SLV_DEV_CONTEXT*ctx);
extern int32_t ss_spi_slave_read_pp(SS_SPI_SLV_DEV_CONTEXT*ctx, void *data1, void *data2, uint32_t len);
extern int32_t ss_spi_slave_read_pp_halt(SS_SPI_SLV_DEV_CONTEXT*ctx);

extern void ss_spi_slave_tx_cb(SS_SPI_SLV_DEV_CONTEXT *ctx, void *param);
extern void ss_spi_slave_rx_cb(SS_SPI_SLV_DEV_CONTEXT *ctx, void *param);
extern void ss_spi_slave_err_cb(SS_SPI_SLV_DEV_CONTEXT *ctx, void *param);
#endif /* _SS_SPI_SLAVE_H_ */

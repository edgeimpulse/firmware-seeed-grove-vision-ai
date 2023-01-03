/*
 * ss_i2c_slave.h
 *
 *  Created on: 2018¦~11¤ë22¤é
 *      Author: 902452
 */

#ifndef _SS_I2C_SLAVE_H_
#define _SS_I2C_SLAVE_H_

/* the wrapper of subsystem i2c slave driver */
#include "hx_drv_iic_s.h"

#define SS_IIC_SLAVE_FLAG_TX		(1 << 0) /* interrupt tx */
#define SS_IIC_SLAVE_FLAG_RX		(1 << 1) /* interrupt rx */
#define SS_IIC_SLAVE_FLAG_BUSY		(1 << 2)
#define SS_IIC_SLAVE_FLAG_TX_RX		(1 << 3) /* both tx and rx */
#define SS_IIC_SLAVE_FLAG_ERROR		(1 << 4)

#define IC_TX_RX_FIFO_SIZE		IO_I2C_SLV0_FS	/* TX/RX FIFO size in hardware */

/* IIC STATUS register */
#define IC_STATUS_TFNF			(0x02)	/* (1 << 1) */
#define IC_STATUS_RFNE			(0x08)	/* (1 << 3) */

/* interrupt callback routines select macros definitions */
#define SS_IIC_SLAVE_RDY_SND		(0x1)	/* ready to send callback */
#define SS_IIC_SLAVE_RDY_RCV		(0x2)	/* ready to receive callback */

/** check expressions used in DFSS IIC driver implementation */
#define SS_IIC_SLAVE_CHECK_EXP(EXPR, ERROR_CODE)		CHECK_EXP(EXPR, ercd, ERROR_CODE, error_exit)

typedef struct ss_iic_slave_dev_context
{
	uint32_t reg_base;
	uint32_t dev_id;	    /* Device ID */

	uint8_t int_rx_avail;	/* Interrupt number RX_AVAIL */
	uint8_t int_tx_req;	    /* Interrupt TX_REQ */
	uint8_t int_stop_det;   /* Interrupt STOP_DET */
	uint8_t int_err;	    /* Interrupt number ERR */
	uint8_t int_rd_req;	    /* Interrupt RD_REQ */
	uint8_t int_restart_det;    /* Interrupt RESTART_DET */

	DEV_CALLBACK int_rx_cb;
	DEV_CALLBACK int_tx_cb;
	DEV_CALLBACK int_err_cb;
	DEV_CALLBACK int_stop_cb;
	DEV_CALLBACK int_rdreq_cb;
	DEV_CALLBACK int_restart_cb;

	DEV_CALLBACK int_dev_cb;

	volatile uint32_t flags;	/*  flag */
	DEV_IIC_S_INFO *info;		/* IIC device information */
} SS_IIC_SLAVE_DEV_CONTEXT;

extern int32_t ss_iic_slave_close(SS_IIC_SLAVE_DEV_CONTEXT *ctx);
extern int32_t ss_iic_slave_control(SS_IIC_SLAVE_DEV_CONTEXT *ctx, uint32_t ctrl_cmd, void *param);
extern int32_t ss_iic_slave_open(SS_IIC_SLAVE_DEV_CONTEXT *ctx, uint32_t param);
extern int32_t ss_iic_slave_write(SS_IIC_SLAVE_DEV_CONTEXT *ctx, const void *data, uint32_t len);
extern int32_t ss_iic_slave_read(SS_IIC_SLAVE_DEV_CONTEXT *ctx, void *data, uint32_t len);
extern void ss_iic_slave_rx_cb(SS_IIC_SLAVE_DEV_CONTEXT *ctx, void *param);
extern void ss_iic_slave_tx_cb(SS_IIC_SLAVE_DEV_CONTEXT *ctx, void *param);
extern void ss_iic_slave_stop_cb(SS_IIC_SLAVE_DEV_CONTEXT *ctx, void *param);
extern void ss_iic_slave_err_cb(SS_IIC_SLAVE_DEV_CONTEXT *ctx, void *param);
extern void ss_iic_slave_rereq_cb(SS_IIC_SLAVE_DEV_CONTEXT *ctx, void *param);
extern void ss_iic_slave_restart_cb(SS_IIC_SLAVE_DEV_CONTEXT *ctx, void *param);

#endif /* _SS_I2C_SLAVE_H_ */

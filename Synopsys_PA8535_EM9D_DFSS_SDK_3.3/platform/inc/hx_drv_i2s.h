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
#ifndef _DW_I2S_OBJ_H_
#define _DW_I2S_OBJ_H_

#include "dev_i2s.h"
#include "hx_drv_ckgen.h"

#define DW_I2S_0_ID		0	/*!< I2S 0 ID macro */
#define DW_I2S_1_ID		1	/*!< I2S 1 ID macro */

#define USE_DW_I2S_0		1	/*!< enable use DesignWare I2S 0 as TX */
#define USE_DW_I2S_1		1	/*!< enable use DesignWare I2S 1 as RX */

#ifdef __cplusplus
extern "C" {
#endif

extern DEV_I2S_PTR i2s_get_dev(int32_t i2s_id);

#ifdef __cplusplus
}
#endif

/* I2S Driver Init */
int32_t hx_drv_i2s_init(void);

/* I2S Driver Deinit */
int32_t hx_drv_i2s_deinit(void);

/* Register I2S TX/RX/ERR callback function */
int32_t hx_drv_i2s_register_cb(void *txcb, void *rxcb, void *errcb);

/* I2S Driver RX Read */
int32_t hx_drv_i2s_rx_read(void *data, uint32_t len);

/* I2S Driver Interrupt RX Read */
int32_t hx_drv_i2s_int_rx_read(void *data, uint32_t len);

/* I2S Driver TX Write */
int32_t hx_drv_i2s_tx_write(void *data, uint32_t len);

/* I2S Driver Interrupt TX Write */
int32_t hx_drv_i2s_int_tx_write(void *data, uint32_t len);

/* I2S Set PCM frequency */
int32_t hx_drv_i2s_set_pcm_freq(uint32_t freq);

#endif /* _DW_I2S_OBJ_H_ */

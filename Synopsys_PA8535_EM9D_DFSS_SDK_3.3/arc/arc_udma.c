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
#include "arc_dmac.h"
#include "arc_udma.h"

/** Uncomment this macro to enable uDMA driver check errors */
//#define UDMA_CHECK_ERRORS



/** DMA Build Configuration Register, DMAC_BUILD (0xCD)
 *  31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0
 *  |RESERVED                     |INT     |FIFO |CHANNELS_MEM  |CHANNELS |VERSION
 */

static dma_state_t *g_dmac = NULL;

#ifdef OS_FREERTOS
#define DMAC_LOCK()     while (xSemaphoreTake(g_dmac->lock, portMAX_DELAY) != pdTRUE) {}
#define DMAC_UNLOCK()   xSemaphoreGive(g_dmac->lock)
#elif defined(OS_TX)
#define DMAC_LOCK()     while (tx_semaphore_get(g_dmac->lock, TX_WAIT_FOREVER) != TX_SUCCESS) {}
#define DMAC_UNLOCK()   tx_semaphore_put(g_dmac->lock)
#else
#define DMAC_LOCK()
#define DMAC_UNLOCK()
#endif

/*----- MACRO START */
#define _MEMORY_FENCE()				_arc_sync()

#define _INT_LEVEL_SENS				0

#define DMA_INT_OK_VECTOR(channel)		((channel)+DMA_IRQ_NUM_START)
#define DMA_INT_ERR_VECTOR(channel)		((channel)+DMA_IRQ_NUM_START+DMA_ALL_CHANNEL_NUM)
/*----- MACRO END */


//! Interrupt about DMA transaction completion
/*! Sets the the "complete" status for completed DMA transaction and
 *! starts next transaction from queue. Reset DMA completion IRQ flags
 */
static void _dmac_interrupt_completed(void *ptr);
static void _dmac_interrupt_completed_channel(uint32_t channel);


//! Interrupt about DMA transaction completion with error
/*! Sets the the "complete with error" status for completed DMA transaction
 *! Reset the DMA channel.
 */
static void _dmac_interrupt_error(void *ptr);
static void _dmac_interrupt_error_channel(uint32_t channel);

/*----- INLINE START */
// enable udma and set DMACBASE
Inline void _dmac_enable(void)
{
	_arc_aux_write(AUX_DMACTRL, 1);
	//_arc_aux_write(AUX_DMACBASE, (uint32_t) (g_dmac->mem_dma_descs));
	_arc_aux_write(AUX_DMACBASE, (uint32_t) (g_dmac->mem_dma_ptrs));

}

// disable udma
Inline void _dmac_disable(void)
{
	_arc_aux_write(AUX_DMACTRL, 0);
}

// enable channel by channel number
Inline void _dmac_enable_channel(uint32_t channel)
{
	uint32_t mask = DMACHANNEL(channel);
	_arc_aux_write(AUX_DMACENB, mask);
}

// enable channel by mask
Inline void _dmac_enable_channels(uint32_t mask)
{
	_arc_aux_write(AUX_DMACENB, mask);
}

// enable all channel
Inline void _dmac_enable_all_channels(void)
{
	_arc_aux_write(AUX_DMACENB, DMA_ALL_CHANNEL_MASK);
}

// disable hannel by channel number
Inline void _dmac_disable_channel(uint32_t channel)
{
	uint32_t mask = DMACHANNEL(channel);
	_arc_aux_write(AUX_DMACDSB, mask);
}

// disable channel by mask
Inline void _dmac_disable_channels(uint32_t mask)
{
	_arc_aux_write(AUX_DMACDSB, mask);
}

// disable all channel
Inline void _dmac_disable_all_channels(void)
{
	_arc_aux_write(AUX_DMACDSB, DMA_ALL_CHANNEL_MASK);
}

// reset channel by channel number
Inline void _dmac_reset_channel(uint32_t channel)
{
	uint32_t mask = DMACHANNEL(channel);
	_arc_aux_write(AUX_DMACRST, mask);
}

// reset channel by mask
Inline void _dmac_reset_channels(uint32_t mask)
{
	_arc_aux_write(AUX_DMACRST, mask);
}

// reset all channel
Inline void _dmac_reset_all_channels(void)
{
	_arc_aux_write(AUX_DMACRST, DMA_ALL_CHANNEL_MASK);
}

// get reset status
Inline uint32_t _dmac_reset_status(void)
{
	return _arc_aux_read(AUX_DMACRST);
}

// set high priority
Inline void _dmac_set_hp_channels(uint32_t mask)
{
	_arc_aux_write(AUX_DMACHPRI, mask);
}

// set low priority
Inline void _dmac_set_np_channels(uint32_t mask)
{
	_arc_aux_write(AUX_DMACNPRI, mask);
}

// software trigger by channel number
Inline void _dmac_start_trigger(uint32_t channel)
{
	_arc_aux_write(AUX_DMACREQ, DMACHANNEL(channel));
}

// software trigger by channel mask

Inline void _dmac_start_trigger_mask(uint32_t mask)
{
	_arc_aux_write(AUX_DMACREQ, mask);
}

// clear irq by channel

Inline void _dmac_irq_clear(uint32_t channel)
{
	_arc_aux_write(AUX_DMACIRQ, DMACHANNEL(channel));
}

// clear all of channel irq

Inline void _dmac_irq_clear_all(void)
{
	_arc_aux_write(AUX_DMACIRQ, DMA_ALL_CHANNEL_MASK);
}

// get irq status

Inline uint32_t _dmac_irq_status(void)
{
	return _arc_aux_read(AUX_DMACIRQ);
}

// get channel status <busy, idle>

Inline uint32_t _dmac_channel_status(void)
{
	return _arc_aux_read(AUX_DMACSTAT0);
}

// get channel complete status

Inline uint32_t _dmac_complete_status(void)
{
	return _arc_aux_read(AUX_DMACSTAT1);
}

// clear channel error flash by channel number

Inline void _dmac_clear_error(uint32_t channel)
{
	_arc_aux_write(AUX_DMACSTAT1, DMACHANNEL(channel) << 16);
}

// clear all of channel error flag

Inline void _dmac_clear_all_error(void)
{
	_arc_aux_write(AUX_DMACSTAT1, 0xFFFF0000);
}
/*----- INLINE END */

// wait channel complete by channel number

static dma_status_t _dmac_wait_channel(uint32_t channel)
{
	uint32_t status;
	status = _arc_aux_read(AUX_DMACSTAT1);
	if (_arc_usually(status & DMACHANNEL(channel))) {
		if (_arc_rarely(status & (DMACHANNEL(channel) << 16))) {
			return DMA_ERROR;
		} else {
			status = _arc_aux_read(AUX_DMACSTAT0);
			if (_arc_rarely(status & DMACHANNEL(channel))) {
				return DMA_BUSY;
			} else {
				return DMA_IDLE;
			}
		}
	}
	return DMA_BUSY;
}

// wait channel complete by channel mask

static dma_status_t _dmac_wait_mask(uint32_t mask)
{
	uint32_t status = _arc_aux_read(AUX_DMACSTAT1);
	if (_arc_rarely(status & mask)) {
		if (_arc_rarely(status & (mask << 16))) {
			return DMA_ERROR;
		} else {
			return DMA_IDLE;
		}
	}
	return DMA_BUSY;
}

/** correct size configuration(value & alignment) according to DWINC mode **/
static uint32_t _dmac_memory_addr_gap(uint32_t dmac_mode)
{
	uint32_t size = (dmac_mode & DMACTRLx_SIZE_MASK) >> DMACTRLx_SIZE_OFS;
	uint32_t dwinc = (dmac_mode & DMACTRLx_DWINC_MASK) >> DMACTRLx_DWINC_OFS;
	return size;
	switch (dwinc) {
		case DMA_DW1INC2:
			size <<= 1;
			break;
		case DMA_DW1INC4:
			size <<= 2;
			break;
		case DMA_DW2INC2:
			size &= ~0x1;
			break;
		case DMA_DW2INC4:
			size &= ~0x1;
			size <<= 1;
			break;
		case DMA_DW4INC4:
			size &= ~0x3;
			break;
		case DMA_DW8INC8:
			size &= ~0x7;
			break;
		case DMA_DW1INC1:
		case DMA_DWINC_CLR:
		default:
			break;
	}
	return size;
}

static uint32_t _dmac_aux_addr_gap(uint32_t dmac_mode)
{
	uint32_t size = (dmac_mode & DMACTRLx_SIZE_MASK) >> DMACTRLx_SIZE_OFS;
	uint32_t dwinc = (dmac_mode & DMACTRLx_DWINC_MASK) >> DMACTRLx_DWINC_OFS;

	switch (dwinc) {
		case DMA_DW2INC2:
		case DMA_DW2INC4:
			size >>= 1;
			break;
		case DMA_DW4INC4:
		case DMA_DW8INC8:
			size >>= 2;
			break;
		case DMA_DW1INC1:
		case DMA_DW1INC2:
		case DMA_DW1INC4:
		case DMA_DWINC_CLR:
		default:
			break;
	}
	return size;
}

//#define USE_DMA_CALC_ADDR
#ifndef USE_DMA_CALC_ADDR /* converted to 1 function called _dmac_calc_addr */
static uint32_t _dmac_calc_dst_endaddr(uint32_t dst_addr, uint32_t dmac_mode)
{
	/*
	 * Destination address is not incremented
	 */
	if (_arc_rarely((dmac_mode & DMACTRLx_AM(2)) == 0)) {
		return dst_addr;
	}

	if (_arc_rarely(DMACTRLx_DTT(0x1) & dmac_mode)) {   /* Destination is Auxiliary */
		dst_addr = dst_addr + _dmac_aux_addr_gap(dmac_mode);
	} else {    /* Destination is Memory */
		dst_addr = dst_addr + _dmac_memory_addr_gap(dmac_mode);
	}
	return dst_addr;
}

static uint32_t _dmac_calc_src_endaddr(uint32_t src_addr, uint32_t dmac_mode)
{
	/*
	 * Source address is not incremented
	 */
	if (_arc_rarely((dmac_mode & DMACTRLx_AM(1)) == 0)) {
		return src_addr;
	}

	if (_arc_rarely(DMACTRLx_DTT(0x2) & dmac_mode)) {   /* Source is Auxiliary */
		src_addr = src_addr + _dmac_aux_addr_gap(dmac_mode);
	} else {    /* Source is Memory */
		src_addr = src_addr + _dmac_memory_addr_gap(dmac_mode);
	}

	return src_addr;
}
#else
static void _dmac_calc_addr(uint32_t *src_addr, uint32_t *dst_addr, uint32_t mode)
{
	if (_arc_usually(mode & DMACTRLx_AM(1))) { /* Source address incremented */
		if (_arc_rarely(DMACTRLx_DTT(0x2) & mode)) {   /* Source is Auxiliary */
			*src_addr += _dmac_aux_addr_gap(mode);
		} else {    /* Source is Memory */
			*src_addr += _dmac_memory_addr_gap(mode);
		}
	}
	if (_arc_usually(mode & DMACTRLx_AM(2))) { /* Destination address incremented */
		if (_arc_rarely(DMACTRLx_DTT(0x1) & mode)) {   /* Destination is Auxiliary */
			*dst_addr += _dmac_aux_addr_gap(mode);
		} else {    /* Destination is Memory */
			*dst_addr += _dmac_memory_addr_gap(mode);
		}
	}
}
#endif

static void _dmac_set_desc(dma_desc_t * desc, void *source, void *dest, uint32_t size,
                           uint32_t dmac_mode)
{
	uint32_t src_addr, dst_addr;

	size = DMA_CTRL_BLKSZ(size);
	dmac_mode &= ~DMACTRLx_SIZE_MASK;
	dmac_mode |= DMACTRLx_SIZE(size);

#ifndef USE_DMA_CALC_ADDR
	src_addr = _dmac_calc_src_endaddr((uint32_t)source, dmac_mode);
	dst_addr = _dmac_calc_dst_endaddr((uint32_t)dest, dmac_mode);
#else /* use dma_calc_addr */
	src_addr = (uint32_t)source;
	dst_addr = (uint32_t)dest;
	_dmac_calc_addr(&src_addr, &dst_addr, dmac_mode);
#endif
	desc->DMACTRLx = dmac_mode;
	desc->DMASARx = src_addr;
	desc->DMADARx = dst_addr;
	desc->DMALLPx = (uint32_t) NULL;
}

static void _dmac_fill_descriptor(uint32_t channel, dma_desc_t * desc)
{
	uint32_t desc_ptr = (uint32_t)desc;
	if (_arc_usually(DMA_CHECK_REGISTER(channel))) {
		uint32_t channel_shift = 3 * channel;
		_arc_aux_write(AUX_DMACTRL0 + channel_shift, desc->DMACTRLx);
		_arc_aux_write(AUX_DMASAR0 + channel_shift, desc->DMASARx);
		_arc_aux_write(AUX_DMADAR0 + channel_shift, desc->DMADARx);
		uint32_t *dma_llps = (uint32_t *) _arc_aux_read(AUX_DMACBASE);
		dma_llps[channel] = desc->DMALLPx;
		_MEMORY_FENCE();
	} else {
		uint32_t *dma_ptrs = (uint32_t *) _arc_aux_read(AUX_DMACBASE);
		dma_ptrs[channel] = (uint32_t)desc_ptr;
		_MEMORY_FENCE();
		//_arc_write_uncached_32((void *)(&dma_ptrs[channel]), (uint32_t)desc);
	}
}

bool dmac_active()
{
	if(g_dmac == NULL)
		return 0;
	else
		return 1;
}



int32_t dmac_init(dma_state_t * state)
{
#ifdef UDMA_CHECK_ERRORS
	if (state == NULL) {
		return -1;
	}
#endif
    if(g_dmac != NULL)
    {
        //! Prevent to reinitialize 
        return -1;
    }
    else
    {
        g_dmac = state;

        memset((void *) g_dmac, 0, sizeof(dma_state_t));

#ifdef OS_FREERTOS
		/*
		 * Initialize the lock
		 */
		g_dmac->lock = xSemaphoreCreateMutex();
#elif defined(OS_TX)
		/*
		 * Initialize the lock
		 */
		int ret = -1;
		ret = tx_semaphore_create(&g_dmac->lock, "dmac_lock", 1);
	    if(ret != TX_SUCCESS){
	    	xprintf("dmac_lock create fail err= 0x%x\n",ret);
	    }
#endif

        _dmac_disable();
        _dmac_disable_all_channels();
        _dmac_reset_all_channels();
        _dmac_enable();

        for (int32_t i = 0; i < DMA_ALL_CHANNEL_NUM; i++) {
            int_level_config(DMA_INT_OK_VECTOR(i), _INT_LEVEL_SENS);
            int_enable(DMA_INT_OK_VECTOR(i));
            int_handler_install(DMA_INT_OK_VECTOR(i), _dmac_interrupt_completed);
            int_pri_set(DMA_INT_OK_VECTOR(i), DMA_IRQ_PRIO);

            int_level_config(DMA_INT_ERR_VECTOR(i), _INT_LEVEL_SENS);
            int_enable(DMA_INT_ERR_VECTOR(i));
            int_handler_install(DMA_INT_ERR_VECTOR(i), _dmac_interrupt_error);
            int_pri_set(DMA_INT_ERR_VECTOR(i), DMA_IRQ_PRIO);
        }

        return 0;
    }
}

int32_t dmac_deinit()
{
	dmac_close();
	g_dmac = NULL;
    return 0;
}

static void _dmac_process_desc(dma_desc_t * desc, uint32_t int_enable)
{
	do {
		if (_arc_rarely(desc->DMALLPx)) {
			/*
			 * Force it to be auto-linked transfer when it is not
			 * DMA_MANUAL_LINKED_TRANSFER
			 */
			if (_arc_usually(((desc->DMACTRLx & DMACTRLx_OP_MASK) >> DMACTRLx_OP_OFS) !=
			                 DMA_MANUAL_LINKED_TRANSFER)) {
				desc->DMACTRLx &= ~DMACTRLx_OP_MASK;
				desc->DMACTRLx |= DMACTRLx_OP(DMA_AUTO_LINKED_TRANSFER);
			}
		} else {
			desc->DMACTRLx &= ~DMACTRLx_OP_MASK;
			desc->DMACTRLx |= DMACTRLx_OP(DMA_SINGLE_TRANSFER);
			/* Only forcely change the interrupt bit of the last dma descriptor */
			desc->DMACTRLx &= ~DMACTRLx_INT_MASK;
			desc->DMACTRLx |= DMACTRLx_INT(int_enable);
		}
		/*
		 * TODO: Make sure all linked DMA channel descriptors
		 * stored into memory, not just in data cache
		 */
		_MEMORY_FENCE();
		desc = (dma_desc_t *) desc->DMALLPx;
	} while (desc != 0);
}

#ifdef UDMA_CHECK_ERRORS
static int32_t dmac_valid_channel(int32_t channel, dma_desc_t * desc)
{
	return 0;
}
#endif


static void _dmac_interrupt_completed_channel(uint32_t channel)
{
	_dmac_irq_clear(channel);
	_dmac_disable_channel(channel);

	if (channel >= DMA_ALL_CHANNEL_NUM) return;

	dma_channel_t *dma_chn = (dma_channel_t *) g_dmac->dma_chns[channel];
	dma_chn->status = DMA_IDLE;
	if (_arc_usually(dma_chn->callback)) {
		dma_chn->callback((void *) dma_chn);
	}
}

static void _dmac_interrupt_error_channel(uint32_t channel)
{
	_dmac_irq_clear(channel);
	_dmac_clear_error(channel);
	_dmac_disable_channel(channel);

	if (channel >= DMA_ALL_CHANNEL_NUM) return;

	dma_channel_t *dma_chn = (dma_channel_t *) g_dmac->dma_chns[channel];
	dma_chn->status = DMA_ERROR;
	if (_arc_usually(dma_chn->callback)) {
		dma_chn->callback((void *) dma_chn);
	}
}

static void _dma_claim_channel(int32_t channel, dma_channel_t * dma_chn,
				dma_request_source_t source)
{
	g_dmac->dma_chns[channel] = dma_chn;
	dma_chn->source = source;
	dma_chn->callback = NULL;
	dma_chn->status = DMA_IDLE;
	dma_chn->channel = channel;
}

static void _dmac_interrupt_completed(void *ptr)
{
	uint32_t channel;

	channel = _arc_aux_read(AUX_IRQ_CAUSE) - DMA_IRQ_NUM_START;

	_dmac_interrupt_completed_channel(channel);
}

static void _dmac_interrupt_error(void *ptr)
{
	uint32_t channel;

	channel = _arc_aux_read(AUX_IRQ_CAUSE) - DMA_IRQ_NUM_START - DMA_ALL_CHANNEL_NUM;

	_dmac_interrupt_error_channel(channel);
}

void dmac_close(void)
{
	if (_arc_rarely(!g_dmac)) {
		return;
	}

	_dmac_disable_all_channels();
	_dmac_reset_all_channels();
	_dmac_disable();
#ifdef OS_FREERTOS
	vSemaphoreDelete(g_dmac->lock);
#elif defined(OS_TX)
	tx_semaphore_delete(&g_dmac->lock);
#endif
}

//HMX@WILL 2018.11.20 support registering callback function to specifc dma_channel
int32_t dmac_register_callback(uint32_t channel, dma_callback_t callback)
{
	if (_arc_usually(channel == DMA_CHN_ANY)) {
		return DMA_CHN_INVALID;
	}

	dma_channel_t *dma_chn = (dma_channel_t *) g_dmac->dma_chns[channel];
	dma_chn->callback = callback;

	return 0;
}

int32_t dmac_config_desc(dma_desc_t * desc, void *src, void *dst, uint32_t size,
			dma_ctrl_t * ctrl)
{
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(desc == NULL)) {
		return -1;
	}
#endif

	_dmac_set_desc(desc, src, dst, size, ctrl->value);

	return 0;
}

int32_t dmac_desc_add_linked(dma_desc_t * head, dma_desc_t * next)
{
	if (_arc_rarely(head == NULL)) {
		return -1;
	}
	head->DMALLPx = (uint32_t) next;
	return 0;
}

int32_t dmac_init_channel(dma_channel_t * dma_chn)
{
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(dma_chn == NULL)) {
		return -1;
	}
#endif
	dma_chn->desc = NULL;
	dma_chn->source = DMA_REQ_SOFT;
	dma_chn->callback = NULL;
	dma_chn->status = DMA_IDLE;
	dma_chn->channel = DMA_CHN_INVALID;
	return 0;
}

int32_t dmac_config_channel(dma_channel_t * dma_chn, dma_desc_t * desc)
{
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(dma_chn == NULL)) {
		return -1;
	}
#endif
	dma_chn->desc = desc;
	return 0;
}

int32_t dmac_reserve_channel(int32_t channel, dma_channel_t * dma_chn,
				dma_request_source_t source)
{
	if (_arc_rarely(dma_chn == NULL)) {
		return DMA_CHN_INVALID;
	}

	if (_arc_usually(channel == DMA_CHN_ANY)) {
		for (int32_t i = 0; i < DMA_ALL_CHANNEL_NUM; i++) {
			if (_arc_usually(!g_dmac->dma_chns[i])) {
				g_dmac->dma_chns[i] = dma_chn;
				_dma_claim_channel(i, dma_chn, source);
				return i;
			}
		}
		return DMA_CHN_INVALID;
	}
	if (_arc_rarely((uint32_t) channel >= DMA_ALL_CHANNEL_NUM)) {
		return DMA_CHN_INVALID;
	}

	if (_arc_usually(!g_dmac->dma_chns[channel])) {
		_dma_claim_channel(channel, dma_chn, source);
		return channel;
	}

	return DMA_CHN_INVALID;
}

int32_t dmac_start_channel(dma_channel_t * dma_chn, dma_callback_t callback,
			uint32_t priority)
{
	int32_t channel;
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(dma_chn == NULL)) {
		return -1;
	}
	if (_arc_rarely(dma_chn->desc == NULL)) {
		return -1;
	}
#endif
	channel = dma_chn->channel;

#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(!((uint32_t) channel < DMA_ALL_CHANNEL_NUM))) {
		return -1;
	}
#endif
	if (_arc_rarely(dma_chn->status == DMA_BUSY)) {
		return -1;
	}
	/** Check if aux based registers and linked transfer is not supported */
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(dmac_valid_channel(channel, dma_chn->desc) != 0)) {
		return -2;
	}
#endif

	dma_chn->callback = callback;
	dma_chn->priority = priority;
	/*
	 * When callback function is NULL, disable interrupt, use simple poll
	 * instead
	 */
	if (_arc_rarely(callback)) {
		dma_chn->int_enable = DMA_INT_ENABLE;
	} else {
		dma_chn->int_enable = DMA_INT_DISABLE;
	}

	if (_arc_usually(priority == DMA_CHN_HIGH_PRIO)) {
		_dmac_set_hp_channels(DMACHANNEL(channel));
	} else {
		_dmac_set_np_channels(DMACHANNEL(channel));
	}

	_dmac_clear_error(channel);
	_dmac_reset_channel(channel);
	_dmac_disable_channel(channel);
	_dmac_enable_channel(channel);

	_dmac_process_desc(dma_chn->desc, dma_chn->int_enable);
	_dmac_fill_descriptor(channel, dma_chn->desc);
	dma_chn->status = DMA_BUSY;
	/*
	 * only trigger when software
	 */
	if (_arc_usually(dma_chn->source == DMA_REQ_SOFT)) {
		_dmac_start_trigger(channel);
	}
	return 0;
}

int32_t dmac_stop_channel(dma_channel_t * dma_chn)
{
	int32_t channel;
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(dma_chn == NULL)) {
		return -1;
	}
	if (_arc_rarely(dma_chn->desc == NULL)) {
		return -1;
	}
#endif
	channel = dma_chn->channel;
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(!((uint32_t) channel < DMA_ALL_CHANNEL_NUM))) {
		return -1;
	}
#endif

	_dmac_disable_channel(channel);
	_dmac_clear_error(channel);
	if (_arc_usually(dma_chn->status == DMA_BUSY)) {
		dma_chn->status = DMA_STOP;
	}
	return 0;
}

int32_t dmac_clear_channel(dma_channel_t * dma_chn)
{
	int32_t channel;
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(dma_chn == NULL)) {
		return -1;
	}
	if (_arc_rarely(dma_chn->desc == NULL)) {
		return -1;
	}
#endif
	channel = dma_chn->channel;

#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(!((uint32_t) channel < DMA_ALL_CHANNEL_NUM))) {
		return -1;
	}
#endif

	_dmac_clear_error(channel);
	_dmac_disable_channel(channel);
	_dmac_enable_channel(channel);
	dma_chn->status = DMA_IDLE;

	return 0;
}

int32_t dmac_release_channel(dma_channel_t * dma_chn)
{
	int32_t channel;
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(dma_chn == NULL)) {
		return -1;
	}
	if (_arc_rarely(dma_chn->desc == NULL)) {
		return -1;
	}
#endif
	channel = dma_chn->channel;

#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(!((uint32_t) channel < DMA_ALL_CHANNEL_NUM))) {
		return -1;
	}
#endif

	_dmac_clear_error(channel);
	_dmac_disable_channel(channel);
	g_dmac->dma_chns[channel] = NULL;
	dma_chn->channel = DMA_CHN_INVALID;

	return 0;
}

int32_t dmac_wait_channel(dma_channel_t * dma_chn)
{
	int32_t channel;
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(dma_chn == NULL)) {
		return -1;
	}
	if (_arc_rarely(dma_chn->desc == NULL)) {
		return -1;
	}
#endif
	channel = dma_chn->channel;

#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(!((uint32_t) channel < DMA_ALL_CHANNEL_NUM))) {
		return -1;
	}
#endif
	while (dma_chn->status == DMA_BUSY) {
		if (_arc_usually(dma_chn->int_enable == DMA_INT_DISABLE)) {
			dma_chn->status = _dmac_wait_channel(channel);
		}
	}
	return dma_chn->status;
}

int32_t dmac_check_channel(dma_channel_t * dma_chn)
{
	int32_t channel;
#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(dma_chn == NULL)) {
		return -1;
	}
	if (_arc_rarely(dma_chn->desc == NULL)) {
		return -1;
	}
#endif
	channel = dma_chn->channel;

#ifdef UDMA_CHECK_ERRORS
	if (_arc_rarely(!((uint32_t) channel < DMA_ALL_CHANNEL_NUM))) {
		return -1;
	}
#endif
	if (_arc_usually(dma_chn->int_enable == DMA_INT_DISABLE)) {
		dma_chn->status = _dmac_wait_channel(channel);
	}
	return dma_chn->status;
}

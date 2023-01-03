/*
 * tflm_audio_function.c
 *
 *  Created on: 2020/06/15
 *      Author: 903730
 */

#include <internal_inc/tflm_audio_function.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "embARC.h"
#include "embARC_debug.h"
#include "board_config.h"
#include "arc_timer.h"
#include "aud_lib.h"

//#define AUD_BUF_ADDR        0x200F2BF0   /* 0x200F_2BF0 ( 125KB) */
#define IMAGE_ADDR			0x20111FF0

#define AUD_BLK_SZ          6400        /* 100ms: 2ch, 16bit */  
#define AUD_BLK_SZ_WORD     6400/4
#define AUD_BLK_NUM         5          /* Audio Buffer size: AUD_BLK_NUM x AUD_BLK_SZ */

#define AUD_BUF_ADDR        IMAGE_ADDR-(AUD_BLK_SZ_WORD*AUD_BLK_NUM)   /* 0x2010_A2F0 ( 32000 B) */
audio_config_t tflm_audio_cfg;
volatile uint32_t audio_timestamp = 0;
volatile uint8_t g_audio_data_valid; 

/* model requires 20ms new data from g_audio_capture_buffer and 10ms old data
 * each time , storing old data in the histrory buffer , {
 * history_samples_to_keep = 10 * 16 } */
#ifdef __GNU__
#define history_samples_to_keep 160
#else
const int32_t history_samples_to_keep = 160;
#endif
/* 20ms means 320 samples */
const int32_t new_samples_to_get = 320;

/* with 30ms of 16KHz inputs, which means 480 samples */
#ifdef __GNU__
#define audio_sample_size 512
#else
const uint32_t audio_sample_size = 512;
#endif
int16_t g_audio_output_buffer[audio_sample_size]; 
int16_t g_history_buffer[history_samples_to_keep];
uint8_t g_audio_mono_buffer_100ms[AUD_BLK_SZ/2];
uint8_t g_audio_dual_buffer_100ms[AUD_BLK_SZ];
int8_t g_audio_mono_buffer_cnt; 

#define DBG_TFLM_AUD_PROF        0
#define DBG_TFLM_AUD_MEM_OP      0
#define DBG_TFLM_TIMING          0

static void audio_2ch_split_to_1ch(unsigned char * dst, unsigned char *src, uint32_t sz)
{
    unsigned char        *dp = (unsigned char *) dst;
    const unsigned char  *sp = (unsigned char *) src;
    
    uint32_t convert_size = sz;
    uint32_t dst_idx = 0;

    for(uint32_t src_idx = 0; src_idx < convert_size; src_idx++)
    {
        if((src_idx%4) < 2) /* mono ch */
        {
            *(dp + dst_idx) = *(sp + src_idx);
            dst_idx++;
        }
    }
}

static void tflm_audio_callback_fun(uint32_t status)
{
    uint32_t aud_buf_addr;
    uint32_t block_num;

    audio_timestamp += 100;
    g_audio_data_valid = 1;

    hx_lib_audio_request_read(&aud_buf_addr, &block_num);
    audio_2ch_split_to_1ch((unsigned char *) g_audio_mono_buffer_100ms, (unsigned char *) aud_buf_addr, AUD_BLK_SZ);
    memcpy(g_audio_dual_buffer_100ms, (unsigned char *) aud_buf_addr, AUD_BLK_SZ);
    block_num = 1;
    hx_lib_audio_update_idx(&block_num);

#if DBG_TFLM_TIMING
    xprintf("i\n");
#endif    
}

int tflm_audio_data_get(uint32_t *aud_addr, uint32_t *size) {
	//uint32_t block_num;

	if(g_audio_data_valid == 0)
		return false;
	else {
		g_audio_data_valid = 0;
		/*hx_lib_audio_request_read(aud_addr, &block_num);
		hx_lib_audio_update_idx(&block_num);
		*size = AUD_BLK_SZ*block_num;*/
		*aud_addr = (uint32_t)g_audio_dual_buffer_100ms;
		*size = AUD_BLK_SZ;
	}
	return true;

}

TFLM_AUDIO_ERROR_E tflm_audio_init()
{
    audio_timestamp = 0;
    g_audio_mono_buffer_cnt = 0;
    g_audio_data_valid = 0;

    hx_lib_audio_set_if(AUDIO_IF_PDM);
    if(hx_lib_audio_init()!= AUDIO_NO_ERROR)
    	return TFLM_AUDIO_ERROR_DRIVER;
    hx_lib_audio_register_evt_cb(tflm_audio_callback_fun); 
    
#if DBG_TFLM_AUD_MEM_OP    
    for (uint32_t i = 0; i <  (AUD_BLK_SZ/2); i++)
    {
        if(i < 640)
        {
            g_audio_mono_buffer_100ms[i] = 0xA1;
        }
        else if(i < 1280)
        {
            g_audio_mono_buffer_100ms[i] = 0xB2;
        }
        else if(i < 1920)
        {
            g_audio_mono_buffer_100ms[i] = 0xC3;
        }
        else if(i < 2560)
        {
            g_audio_mono_buffer_100ms[i] = 0xD4;
        }
        else if(i < 3200)
        {
            g_audio_mono_buffer_100ms[i] = 0xE5;
        }        
    }
#endif    

    return TFLM_AUDIO_NO_ERROR;
}

TFLM_AUDIO_ERROR_E tflm_audio_start()
{
	AUDIO_ERROR_E ret = AUDIO_NO_ERROR;
    tflm_audio_cfg.sample_rate = AUDIO_SR_16KHZ;
    tflm_audio_cfg.buffer_addr = (uint32_t *) AUD_BUF_ADDR;
    tflm_audio_cfg.block_num = AUD_BLK_NUM;  
    tflm_audio_cfg.block_sz = AUD_BLK_SZ;    
    tflm_audio_cfg.cb_evt_blk = 1;
    ret = hx_lib_audio_start(&tflm_audio_cfg);

    if(ret == AUDIO_ERROR_NOT_INIT)
    	return  TFLM_AUDIO_ERROR_NOT_INIT;
    else if(ret == AUDIO_ERROR_INVALID_PARAMETERS)
    	return TFLM_AUDIO_ERROR_INVALID_PARAMETERS;

    return TFLM_AUDIO_NO_ERROR;
}

TFLM_AUDIO_ERROR_E tflm_audio_stop()
{
    audio_timestamp = 0;
    g_audio_mono_buffer_cnt = 0;
    g_audio_data_valid = 0;
    if(hx_lib_audio_stop() == AUDIO_ERROR_NOT_INIT)
    	return TFLM_AUDIO_ERROR_NOT_INIT;

    return TFLM_AUDIO_NO_ERROR;

}

void tflm_audio_samples_get(tflm_audio_samples_t *audio_samples)
{
#if DBG_TFLM_AUD_PROF    
    uint32_t g_tick_start;
    uint32_t g_tick_stop;
    uint32_t g_tick_period;
    uint32_t g_period;

    timer_start(TIMER_0, TIMER_CTRL_NH, 0xffffffff);
    g_tick_start = _arc_aux_read(AUX_TIMER0_CNT);
#endif

    /* copy 10ms that is 160 samples (320 bytes) into output_buffer from history 
        memcpy(dst, src, sz)
    */
    memcpy((void*)(g_audio_output_buffer), (void*)(g_history_buffer),
            history_samples_to_keep * sizeof(int16_t));        

    /* copy 20ms that is 320 samples (640 bytes) from g_audio_mono_buffer_100ms 
       at ( int16_t*(g_audio_output_buffer) + 160 ), first 10ms that is 160 samples (320 bytes) will be from history 
       memcpy(dst, src, sz) 
    */

    if((g_audio_mono_buffer_cnt % 16) == 15)
    {
        #if DBG_TFLM_TIMING        
            xprintf(".s\n");
            xprintf(".e\n");
            xprintf("\n\n");
        #endif

        /* Keep that, it also have debounce effect */
        /* 16th audio slice = duplicated 15th audio slice */
        g_audio_mono_buffer_cnt = 4;
        memcpy((void*)((g_audio_output_buffer + history_samples_to_keep)), (void*)(g_audio_mono_buffer_100ms + ((g_audio_mono_buffer_cnt % 5) * new_samples_to_get * 2)),
            new_samples_to_get * sizeof(int16_t));  

        /* reset buffer counter for next start from zero to counter */
        g_audio_mono_buffer_cnt = -1;
        g_audio_data_valid = 0;
    }
    else
    {
        #if DBG_TFLM_TIMING  
            xprintf("s\n");
            while(g_audio_data_valid == 0);
            xprintf("e\n");
        #else
            while(g_audio_data_valid == 0);
        #endif

        memcpy((void*)((g_audio_output_buffer + history_samples_to_keep)), (void*)(g_audio_mono_buffer_100ms + ((g_audio_mono_buffer_cnt % 5) * new_samples_to_get * 2)),
            new_samples_to_get * sizeof(int16_t));
    
        /* Process 1st ~ 15th audio slice */
        if(((g_audio_mono_buffer_cnt % 16) != (15 -1)))
        {
            /* consume 20ms period in each 100ms */
            if((g_audio_mono_buffer_cnt % 5) == 4)
            {
                g_audio_data_valid = 0;
                #if DBG_TFLM_TIMING 
                    xprintf("\n\n");
                #endif    
            }
        }
    }

    /* copy 320 bytes (10ms) from output_buff into history 
        memcpy(dst, src, sz)
    */
    memcpy((void*)(g_history_buffer),
            (void*)(g_audio_output_buffer + new_samples_to_get),
            history_samples_to_keep * sizeof(int16_t));

#if DBG_TFLM_AUD_PROF
    g_tick_stop = _arc_aux_read(AUX_TIMER0_CNT);

    if(g_tick_stop > g_tick_start)
    {
        g_tick_period = g_tick_stop - g_tick_start;
    }else{
        g_tick_period = 0;
    }

    if(is_ref_cpu_clk_by_var()){
        g_period = g_tick_period/(get_ref_cpu_clk()/BOARD_SYS_TIMER_US_HZ);
    }else{
        g_period = g_tick_period/BOARD_SYS_TIMER_US_CONV;
    }	

    xprintf("g_tick_start=%d, g_tick_stop=%d, g_period=%d us ( < 4us)\n",g_tick_start, g_tick_stop, g_period);
#endif

    g_audio_mono_buffer_cnt++;
    audio_samples->audio_data_address = (uint32_t) g_audio_output_buffer;
    audio_samples->audio_data_size = audio_sample_size;
}

uint32_t tflm_audio_timestamp_get(void)
{
    return  audio_timestamp;
}

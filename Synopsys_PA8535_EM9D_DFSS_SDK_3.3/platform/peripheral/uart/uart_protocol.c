/*
 * uart_protocol.c
 *
 *  Created on: 2020¦~4¤ë30¤é
 *      Author: 903935
 */

#include <stdbool.h>
#include "embARC_debug.h"

#include "hx_drv_timer.h"
#include "spi_protocol.h"
#include "hx_drv_uart.h"
#include "board_config.h"
/****************************************************
 * Constant Definition                              *
 ***************************************************/
#define UART_PACKET_SIZE (5*1024)

/****************************************************
 * Variable Declaration                             *
 ***************************************************/
volatile bool uart_cb_tx_flag = false;
//extern unsigned char g_uart_tx_buf[7];

#ifdef OS_FREERTOS
#include "FreeRTOS.h"
#include "portmacro.h"
#include "semphr.h"

extern SemaphoreHandle_t mutex_uart;
#elif defined(OS_TX)
#include "tx_api.h"
extern TX_MUTEX mutex_uart;
#endif
/***************************************************
 * Function Implementation
 **************************************************/
void uart_callback_fun_tx(void)
{
    uart_cb_tx_flag = true;
    //dbg_printf(DBG_LESS_INFO,"uart_1_callback_fun_tx\n");
}

int app_uart_send(uint32_t SRAM_addr, uint32_t img_size, SPI_CMD_DATA_TYPE data_type)
{
    DEV_UART_PTR dev_uart_comm = hx_drv_uart_get_dev(BOARD_COMMAND_UART_ID);
    uint32_t uart_imgsize = 0, uart_cur_pos = 0;
    int s_cmd_count = 0;
    int ret = 0;
    unsigned char g_uart_tx_buf[7];

    #ifdef OS_FREERTOS
    xSemaphoreTake(mutex_uart, portMAX_DELAY);
	#elif defined(OS_TX)
    tx_mutex_get(&mutex_uart, TX_WAIT_FOREVER);
    #endif

    uart_cb_tx_flag = false;

    g_uart_tx_buf[0] = 0xC0; // sync
    g_uart_tx_buf[1] = 0x5A; // sync
    g_uart_tx_buf[2] = data_type; // data type
    g_uart_tx_buf[3] = img_size&0xff; //data size
    g_uart_tx_buf[4] = (img_size>>8)&0xff; //data size
    g_uart_tx_buf[5] = (img_size>>16)&0xff; //data size
    g_uart_tx_buf[6] = (img_size>>24)&0xff; //data size

    if(0 > dev_uart_comm->uart_write(g_uart_tx_buf,7))
    {
        dbg_printf(DBG_LESS_INFO,"uart send error : %s - %d\n",__FUNCTION__,__LINE__);
        ret = -1;
        goto EXIT;
    }

    while(uart_cb_tx_flag == false)
    {
        board_delay_ms(1);
        s_cmd_count +=1;
        if(s_cmd_count >50000)
        {
            ret = -1;
            goto EXIT;
        }
    }

    uart_imgsize = img_size;
    uart_cur_pos = SRAM_addr;
    while(uart_imgsize > 0)
    {
        uart_cb_tx_flag = false;
        s_cmd_count = 0;
        if(uart_imgsize > UART_PACKET_SIZE)
        {
            if(0 > dev_uart_comm->uart_write((const char *)uart_cur_pos,UART_PACKET_SIZE))
            {
                dbg_printf(DBG_LESS_INFO,"uart send error : %s - %d\n",__FUNCTION__,__LINE__);
                ret = -1;
                goto EXIT;
            }
            uart_cur_pos += UART_PACKET_SIZE;
            uart_imgsize -= UART_PACKET_SIZE;
        }
        else
        {
            if(0 > dev_uart_comm->uart_write((const char *)uart_cur_pos,uart_imgsize))
            {
                dbg_printf(DBG_LESS_INFO,"uart send error : %s - %d\n",__FUNCTION__,__LINE__);
                ret = -1;
                goto EXIT;
            }
            uart_imgsize = 0;
        }
        while(uart_cb_tx_flag == false)
        {
            board_delay_ms(1);
            s_cmd_count +=1;
            if(s_cmd_count >50000)
            {
                ret = -1;
                goto EXIT;
            }
        }
    }

EXIT:
    #ifdef OS_FREERTOS
    xSemaphoreGive(mutex_uart);
    #endif

    return ret;
}

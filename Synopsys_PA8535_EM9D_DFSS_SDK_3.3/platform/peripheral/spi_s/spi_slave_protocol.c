#include "spi_slave_protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include "embARC_error.h"
#include "embARC_debug.h"
//#include "cli_debug.h"
//#include "cli_type.h"
//#include "cli_console.h"

#include "apexextensions.h"
#include "hx_drv_spi_s.h"
#include "hx_drv_timer.h"
#include "hx_drv_iomux.h"

#include "io_config.h"

#ifdef __Xdmac
#include "arc_udma.h"
#endif

#ifdef EVT_SPISCOMM
#include "evt_spiscomm.h"
#endif

#define DIRECT_TO_SRAM 1
//#define TIME_COUNT

#define PS_BUFFER_SIZE 1024

#if defined(AIOT_HUMANDETECT_TV) || defined(AIOT_HUMANDETECT_AIRCONDITION) || defined(AIOT_HUMANDETECT_SMARTDOORLOCK) || defined(AIOT_AMR_VIP)
#define PACKET_SIZE 6000
#else
//#define PACKET_SIZE 65500
#define PACKET_SIZE 1000
#endif
volatile static DEV_SPI_SLV_PTR dev_spi_ps;
#ifdef __Xdmac
//volatile static dma_state_t 		udma_ps;
static dma_channel_t 	dma_chn_spi_ps_tx, dma_chn_spi_ps_rx;
#endif
volatile bool s_cb_rx_flag = false, s_cb_tx_flag = false;
volatile bool spis_rx_ptl_busy_flag = false, spis_tx_ptl_busyflag = false;

#ifndef DIRECT_TO_SRAM
volatile unsigned char g_rx_buf[PS_BUFFER_SIZE];
volatile  unsigned char g_tx_buf[PS_BUFFER_SIZE];
#else
volatile unsigned char g_rx_buf[6]={0,0,0,0,0,0};
#if defined(AIOT_HUMANDETECT_TV) || defined(AIOT_HUMANDETECT_AIRCONDITION) || defined(AIOT_HUMANDETECT_SMARTDOORLOCK) || defined(AIOT_AMR_VIP)
volatile  unsigned char g_tx_buf[7]={0,0,0,0,0,0,0};
#else
volatile  unsigned char g_tx_buf[6]={0,0,0,0,0,0};
#endif
#endif
#ifdef TIME_COUNT
uint64_t start_tick,end_tick;
#endif

uint8_t cus_spis_ptl_hdr_buf[16]; /*the maximum block transfer size of 8k for DMA(max len = 2000).*/

DEV_SPI_SLV_INFO_PTR ps_info;
#define CHECK_SPIS_SEND_ADDR 0xb0000008
#define CHECK_SPIS_SEND_MASK 0x00000800

//uint32_t s_imgsize = 0, s_cur_pos = 0;

//int s_cmd_count = 0;
//int img_data_count =0;

//SRAM memory : 0x20000000~0x2016FFFF
//EXT_RAM_PATTERN_START     0x20030000

static void spi_s_callback_fun_rx(void *status)
{
    s_cb_rx_flag = true;
    return;
}

static void spi_s_callback_fun_tx(void *status)
{
    s_cb_tx_flag = true;
    return;
}

static void spi_s_callback_fun_err(void *status)
{
    return;
}

static void spi_s_callback_ptl_tx(void )
{
    hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 0);
    spis_tx_ptl_busyflag = false;
    return;
}

static void spi_s_callback_ptl_rx(void )
{
	spis_rx_ptl_busy_flag = false;
    return;
}


int hx_drv_spi_slv_open()
{
    //1. initial SPI slave
    dev_spi_ps = hx_drv_spi_slv_get_dev(USE_DFSS_SPI_SLV_0);

    ps_info = &(dev_spi_ps->spi_info);

    ps_info->spi_cbs.tx_cb = spi_s_callback_fun_tx;
    ps_info->spi_cbs.rx_cb = spi_s_callback_fun_rx;
    ps_info->spi_cbs.err_cb = spi_s_callback_fun_err;

    dev_spi_ps->spi_open(DEV_SLAVE_MODE,1000000);
    #ifdef __Xdmac
    /** Must init uDMA before use it */
    //move to fpga_init
    //dmac_init(&udma_ps);

    dmac_init_channel(&dma_chn_spi_ps_tx);
    dmac_init_channel(&dma_chn_spi_ps_rx);

    dmac_reserve_channel(IO_SPI_SLV0_DMA_TX, &dma_chn_spi_ps_tx, DMA_REQ_SOFT);
    dmac_reserve_channel(IO_SPI_SLV0_DMA_RX, &dma_chn_spi_ps_rx, DMA_REQ_PERIPHERAL);
    #endif

    //init GPIO TX and RX
    hx_drv_iomux_set_pmux(HANDSHAKE_PIN_TX, 3); //for TX output mux
    hx_drv_iomux_set_pmux(HANDSHAKE_PIN_RX, 2); //for RX input mux


    spis_tx_ptl_busyflag = false;
    spis_rx_ptl_busy_flag = false;

    #ifdef EVT_SPISCOMM
    evt_spiscomm_cmd_read();
    #endif    
    return 0;
}


int hx_drv_spi_slv_protocol_read_simple(uint32_t SRAM_addr, uint32_t *img_size )
{
    uint32_t s_imgsize = 0, s_cur_pos = 0;

    int s_cmd_count = 0;
    int img_data_count =0;

    //2. set read data
    s_cmd_count = 0;
    img_data_count =0;
    s_cur_pos = SRAM_addr;
    do{
        g_rx_buf[0] = 0;
        s_cb_rx_flag = false;
        dev_spi_ps->spi_read((void *) &g_rx_buf[0], 6);
        //dev_spi_ps->spi_read(g_rx_buf, 8);

        while(s_cb_rx_flag == false)
        {
            board_delay_ms(1);
            s_cmd_count +=1;
            if(s_cmd_count >= 10000)
                return -1;
        }

        //EMBARC_PRINTF("[%d]:data[0]=%x/data[1]=%x/data[2]=%x/data[3]=%x/data[4]=%x/data[5]=%x\n",s_cmd_count,g_rx_buf[0],g_rx_buf[1],g_rx_buf[2],g_rx_buf[3],g_rx_buf[4],g_rx_buf[5]);
        s_cmd_count +=1;
    }while(g_rx_buf[0] != 0xc0);
    #ifdef TIME_COUNT
    start_tick = board_get_cur_us();
    #endif

    if(g_rx_buf[1] != 0x5A)
        return -1;

    s_imgsize = (uint32_t)(g_rx_buf[5]<<24) + (uint32_t)(g_rx_buf[4]<<16) + (uint32_t)(g_rx_buf[3]<<8) + g_rx_buf[2];

    *img_size = s_imgsize;

    do{
        s_cb_rx_flag = false;
        img_data_count = 0;
    #ifndef DIRECT_TO_SRAM
        if(s_imgsize>1000)
    #else
        if(s_imgsize>PACKET_SIZE)
    #endif
        {
    #ifndef DIRECT_TO_SRAM
            dev_spi_ps->spi_read(g_rx_buf, 1000);
    #else
            dev_spi_ps->spi_read((uint8_t *)s_cur_pos, PACKET_SIZE);
    #endif
        }
        else
        {
    #ifndef DIRECT_TO_SRAM
            dev_spi_ps->spi_read(g_rx_buf, s_imgsize);
    #else
            dev_spi_ps->spi_read((uint8_t *)s_cur_pos, s_imgsize);
    #endif
        }

        while(s_cb_rx_flag == false)
        {
            board_delay_ms(1);
            img_data_count += 1;

            if(img_data_count >= 3000)
            {
                *img_size = 0;
                return -2;
            }
        }

    #ifndef DIRECT_TO_SRAM
        if(s_imgsize > 1000)
    #else
        if(s_imgsize > PACKET_SIZE)
    #endif
        {
    #ifndef DIRECT_TO_SRAM
                memcpy((uint32_t *)s_cur_pos,g_rx_buf, 1000);
                s_imgsize -= 1000;
                s_cur_pos += 1000;
    #else
            s_imgsize -=PACKET_SIZE;
            s_cur_pos += PACKET_SIZE;
    #endif
        }
        else
        {
    #ifdef TIME_COUNT
            end_tick = board_get_cur_us();
    #endif

    #ifndef DIRECT_TO_SRAM
            memcpy((uint32_t *)s_cur_pos,g_rx_buf, s_imgsize);
            s_cur_pos += s_imgsize;
                        s_imgsize = 0;
    #endif
            s_cur_pos += s_imgsize;
            s_imgsize = 0;
        }

        //EMBARC_PRINTF("\n");


    }while(s_imgsize>0);


    return 0;
}

int hx_drv_spi_slv_protocol_write_halt()
{
    hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 0);

    if(E_OK == dev_spi_ps->spi_write_halt())
    {
        spis_tx_ptl_busyflag = false;
        return 0;
    }
    else
        return -1;
}

int hx_drv_spi_slv_protocol_write_busy_status()
{
    if(spis_tx_ptl_busyflag)
        return -1;
    else
        return 0;
}


int hx_drv_spi_slv_protocol_write_simple(uint32_t SRAM_addr, uint32_t img_size)
{
    int s_cmd_count = 0;


    if(spis_tx_ptl_busyflag)
        return -1;

    spis_tx_ptl_busyflag = true;
    dev_spi_ps = hx_drv_spi_slv_get_dev(USE_DFSS_SPI_SLV_0);
    hx_drv_spi_slv_register_tx_cb(spi_s_callback_ptl_tx);

    //GPIO TX pull high
    hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 1);

    dev_spi_ps->spi_write_ptl((void *)SRAM_addr, img_size, DATA_TYPE_JPG);

    //wait spis_tx_ptl_busyflag
    while(spis_tx_ptl_busyflag == true)
    {
        board_delay_ms(1);
        s_cmd_count +=1;

        if(s_cmd_count >3000)
        {
            hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 0);
            dev_spi_ps->spi_write_halt();
            spis_tx_ptl_busyflag = false;
            return -1;
            //dev_spi_ps->spi_write(g_tx_buf, 6);
        }
    }
	hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 0);
    return 0;
}

int hx_drv_spi_slv_protocol_write_simple_cus(uint32_t SRAM_addr, uint32_t img_size, uint32_t header_len)
{
    int s_cmd_count = 0;
    /*the example format of user-defined protocol header*/
	cus_spis_ptl_hdr_buf[0] = 0xC0; // sync
	cus_spis_ptl_hdr_buf[1] = 0x5A; // sync
	cus_spis_ptl_hdr_buf[2] = (DATA_TYPE_JPG)&0xff; // data_type
	cus_spis_ptl_hdr_buf[3] = img_size&0xff; //data size
	cus_spis_ptl_hdr_buf[4] = (img_size>>8)&0xff; //data size
	cus_spis_ptl_hdr_buf[5] = (img_size>>16)&0xff; //data size
	cus_spis_ptl_hdr_buf[6] = (img_size>>24)&0xff; //data size


    if(spis_tx_ptl_busyflag)
        return -1;

    dev_spi_ps = hx_drv_spi_slv_get_dev(USE_DFSS_SPI_SLV_0);
    spis_tx_ptl_busyflag = true;

    hx_drv_spi_slv_register_tx_cb(spi_s_callback_ptl_tx);
    //hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 0);
    //GPIO TX pull high
    hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 1);

    dev_spi_ps->spi_write_ptl_cus(cus_spis_ptl_hdr_buf, header_len,(void *)SRAM_addr, img_size);

    //wait spis_tx_ptl_busyflag
    while(spis_tx_ptl_busyflag == true)
    {
        board_delay_ms(1);
        s_cmd_count +=1;

        if(s_cmd_count >3000)
        {
            hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 0);
            dev_spi_ps->spi_write_halt();
            spis_tx_ptl_busyflag = false;
            return -1;
            //dev_spi_ps->spi_write(g_tx_buf, 6);
        }
    }
    return 0;
}

int hx_drv_spi_slv_protocol_write_simple_ex(uint32_t SRAM_addr, uint32_t img_size, SPI_CMD_DATA_TYPE data_type)
{
    int s_cmd_count = 0;


    if(spis_tx_ptl_busyflag)
        return -1;

    spis_tx_ptl_busyflag = true;

   
    //GPIO TX pull high
    hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 1);
	
	if(data_type == DATA_TYPE_NONE)
	{
		hx_drv_spi_slv_register_tx_cb(spi_s_callback_ptl_tx);
		dev_spi_ps->spi_write((void *)SRAM_addr, img_size);
	}
	else
	{
		hx_drv_spi_slv_register_tx_cb(spi_s_callback_ptl_tx);
    	dev_spi_ps->spi_write_ptl((void *)SRAM_addr, img_size, data_type);
	}

    //wait spis_tx_ptl_busyflag
    while(spis_tx_ptl_busyflag == true)
    {
        board_delay_ms(1);
        s_cmd_count +=1;

        if(s_cmd_count >3000)
        {
            hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 0);
            dev_spi_ps->spi_write_halt();
            spis_tx_ptl_busyflag = false;
            return -1;
            //dev_spi_ps->spi_write(g_tx_buf, 6);
        }
    }

    hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 0);
    return 0;

}

int hx_drv_spi_slv_protocol_write_simple_ex_timeout(uint32_t SRAM_addr, uint32_t img_size, SPI_CMD_DATA_TYPE data_type, uint32_t timeout)
{
	uint32_t s_cmd_count = 0;


    if(spis_tx_ptl_busyflag)
        return -1;

    spis_tx_ptl_busyflag = true;


    //GPIO TX pull high
    //hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 1);

	if(data_type == DATA_TYPE_NONE)
	{
		hx_drv_spi_slv_register_tx_cb(spi_s_callback_ptl_tx);
		dev_spi_ps->spi_write((void *)SRAM_addr, img_size);
	}
	else
	{
		hx_drv_spi_slv_register_tx_cb(spi_s_callback_ptl_tx);
    	dev_spi_ps->spi_write_ptl((void *)SRAM_addr, img_size, data_type);
	}

    //wait spis_tx_ptl_busyflag
    while(spis_tx_ptl_busyflag == true)
    {
        board_delay_ms(1);
        s_cmd_count +=1;

        if(timeout==0)
        	continue;
        else if(s_cmd_count >timeout)
        {
            //hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 0);
            dev_spi_ps->spi_write_halt();
            spis_tx_ptl_busyflag = false;
            return -1;
        }
    }

    //hx_drv_iomux_set_outvalue(HANDSHAKE_PIN_TX, 0);
    return 0;

}


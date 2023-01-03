#include "spi_master_protocol.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>

#include "embARC_error.h"

#include "apexextensions.h"
#include "hx_drv_spi_m.h"
#include "hardware_config.h"
#include "hx_drv_timer.h"
#include "hx_drv_iomux.h"
#ifdef __Xdmac
#include "arc_udma.h"
#endif

#include "io_config.h"

//master and slave protocol share same TX/RX GPIO pin
#ifdef SPI_SLAVE_HANDSHAKE_IC
#define HANDSHAKE_PIN_TX 4
#define HANDSHAKE_PIN_RX 5
#else
#define HANDSHAKE_PIN_TX 10
#define HANDSHAKE_PIN_RX 1
#endif

#define BUFFER_SIZE 10

static DEV_SPI_PTR dev_spi_m,dev_spi_flash;
static DEV_SPI_INFO_PTR info;

//unsigned char mst_g_rx_buf[BUFFER_SIZE];
//unsigned char mst_g_tx_buf[BUFFER_SIZE];
bool cb_rx_flag = false, cb_tx_flag = false;
bool cb_flash_rx_flag = false, cb_flash_tx_flag = false;
volatile bool spi_m1_rx_ptl_busy_flag = false, spi_m1_tx_ptl_busy_flag = false;
uint32_t imgsize = 0, cur_pos = 0;

static spi_mst_protocol_cb_t g_spi_m1_ptl_tx_cb = NULL;
static spi_mst_protocol_cb_t g_spi_m1_ptl_rx_cb = NULL;

#ifdef __Xdmac
//static dma_state_t 		mst0_udma;
//static dma_channel_t 	dma_chn_spi_m_tx, dma_chn_spi_m_rx;
#endif

int cmd_count = 0;
int img_data_count =0;

bool SPI_Busy_Flag = false;

#define CHECK_SPIM_SEND_ADDR 0xb0000008
#define CHECK_SPIM_SEND_MASK 0x00000800
uint8_t cus_spim_ptl_hdr_buf[16]; /*the maximum block transfer size of 8k for DMA(max len = 2000).*/
//SRAM memory : 0x20000000~0x2016FFFF
//EXT_RAM_PATTERN_START     0x20030000

//==============SPI 1 master ===========================//
static void spi_m_callback_fun_rx(void *status)
{
    cb_rx_flag = true;
    return;
}

static void spi_m_callback_fun_tx(void *status)
{
	cb_tx_flag = true;
    return;
}

static void spi_m_callback_fun_err(void *status)
{
    return;
}

static void spi_m1_callback_ptl_tx(void )
{
	spi_m1_tx_ptl_busy_flag = false;
	SPI_Busy_Flag = false;
	#ifdef IC_PACKAGE_WLCSP38
	hx_drv_iomux_set_func_pin_out(PERI_SSI0_CS1, PERI_ORIGNAL);
	#endif

	hx_drv_iomux_set_outvalue(IOMUX_PGPIO8, 0);

	if(g_spi_m1_ptl_tx_cb)
		g_spi_m1_ptl_tx_cb();

    return;
}

static void spi_m1_callback_ptl_rx(void )
{
	spi_m1_rx_ptl_busy_flag = false;
	if(g_spi_m1_ptl_rx_cb)
		g_spi_m1_ptl_rx_cb();

    return;
}

int hx_drv_spi_mst_open()
{
	dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_1);

	dev_spi_m->spi_open(DEV_MASTER_MODE,10000000, CLK_BUS_APB); //master mode, spi clock, cpu clock

	info = &(dev_spi_m->spi_info);

	info->spi_cbs.tx_cb = spi_m_callback_fun_tx;
	info->spi_cbs.rx_cb = spi_m_callback_fun_rx;
	info->spi_cbs.err_cb = spi_m_callback_fun_err;

#if 0
#ifdef __Xdmac
	/** Must init uDMA before use it */
	//dmac_init(&mst0_udma);

	dmac_init_channel(&dma_chn_spi_m_tx);
	dmac_init_channel(&dma_chn_spi_m_rx);

	dmac_reserve_channel(IO_SPI_MST0_DMA_TX, &dma_chn_spi_m_tx, DMA_REQ_SOFT);
	dmac_reserve_channel(IO_SPI_MST0_DMA_RX, &dma_chn_spi_m_rx, DMA_REQ_PERIPHERAL);

#endif
#endif
    //init GPIO TX and RX
    #if !defined(CAPSULE)
    hx_drv_iomux_set_pmux(HANDSHAKE_PIN_TX, 3); //for TX output mux
    hx_drv_iomux_set_pmux(HANDSHAKE_PIN_RX, 2); //for RX input mux
    #endif
	spi_m1_tx_ptl_busy_flag = false;
	spi_m1_rx_ptl_busy_flag = false;

	return 0;
}

int hx_drv_spi_mst_open_speed(uint32_t spi_clk, uint32_t cpu_clk)
{
    #if defined(CAPSULE) && defined(IC_PACKAGE_WLCSP38)//temp solution
    hx_drv_spi_mst_deinit(USE_DW_SPI_MST_0);
    hx_drv_spi_mst_init(USE_DW_SPI_MST_0);
    
    dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_0);
    #else
    hx_drv_spi_mst_deinit(USE_DW_SPI_MST_1);
    hx_drv_spi_mst_init(USE_DW_SPI_MST_1);
    
    dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_1);
    #endif
    dev_spi_m->spi_open(DEV_MASTER_MODE, spi_clk, cpu_clk);
    info = &(dev_spi_m->spi_info);

    info->spi_cbs.tx_cb = spi_m_callback_fun_tx;
    info->spi_cbs.rx_cb = spi_m_callback_fun_rx;
    info->spi_cbs.err_cb = spi_m_callback_fun_err;

    //init GPIO TX and RX
    #if !defined(CAPSULE)
    hx_drv_iomux_set_pmux(HANDSHAKE_PIN_TX, 3); //for TX output mux
    hx_drv_iomux_set_pmux(HANDSHAKE_PIN_RX, 2); //for RX input mux
    #endif
    spi_m1_tx_ptl_busy_flag = false;
    spi_m1_rx_ptl_busy_flag = false;

    return 0;
}

// register callback function for write / read process. currently event handler& CLI call this API
int hx_drv_spi_mst_protocol_register_tx_cb(spi_mst_protocol_cb_t aRWritecb)
{
	int e_no = E_OK;

	if(aRWritecb)
	{
		//g_spim_tx_cb 	= aRWritecb;
		g_spi_m1_ptl_tx_cb = aRWritecb;
	}

	return e_no;
}

int hx_drv_spi_mst_protocol_register_rx_cb(spi_mst_protocol_cb_t aReadcb)
{
	int e_no = E_OK;

	if(aReadcb)
	{
		//g_spim_rx_cb 	= aReadcb;
		g_spi_m1_ptl_rx_cb = aReadcb;
	}

	return e_no;
}



int hx_drv_spi_mst_protocol_write(uint32_t SRAM_addr, uint32_t img_size)
{
    int s_cmd_count = 0;


    if(spi_m1_tx_ptl_busy_flag)
        return -1;

	dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_1);

    spi_m1_tx_ptl_busy_flag = true;
	//set callback function api
    hx_spimcomm_register_tx_cb((spimcomm_cb_t)spi_m1_callback_ptl_tx);

	//call to low layer with address and image size
	dev_spi_m->spi_write_ptl(SPI_M_MODE_SINGLE, (void *)SRAM_addr, img_size, DATA_TYPE_JPG);

	//if blocking code, add wait busy status flag. wait time now use 3 sec
    //wait spis_tx_ptl_busyflag
    while(spi_m1_tx_ptl_busy_flag == true)
    {
        board_delay_ms(1);
        s_cmd_count +=1;

        if(s_cmd_count >3000)
        {
        	dev_spi_m->spi_write_ptl_halt();
        	spi_m1_tx_ptl_busy_flag = false;
            return -1;
        }
    }
    return 0;

}

int hx_drv_spi_mst_protocol_write_cus(uint32_t SRAM_addr, uint32_t img_size,
									uint32_t header_len)
{
    int s_cmd_count = 0;

	/*the example format of user-defined protocol header*/
	cus_spim_ptl_hdr_buf[0] = 0x0C; // sync
	cus_spim_ptl_hdr_buf[1] = 0xA5; // sync
	cus_spim_ptl_hdr_buf[2] = (DATA_TYPE_JPG)&0xff; // data_type
	cus_spim_ptl_hdr_buf[3] = img_size&0xff; //data size
	cus_spim_ptl_hdr_buf[4] = (img_size>>8)&0xff; //data size
	cus_spim_ptl_hdr_buf[5] = (img_size>>16)&0xff; //data size
	cus_spim_ptl_hdr_buf[6] = (img_size>>24)&0xff; //data size

    if(spi_m1_tx_ptl_busy_flag)
        return -1;
	
	dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_1);

    spi_m1_tx_ptl_busy_flag = true;
	//set callback function api
    hx_spimcomm_register_tx_cb((spimcomm_cb_t)spi_m1_callback_ptl_tx);
	//call to low layer with address and image size	
	dev_spi_m->spi_write_ptl_cus(cus_spim_ptl_hdr_buf, header_len,(void *)SRAM_addr, img_size);
	//if blocking code, add wait busy status flag. wait time now use 3 sec
    //wait spis_tx_ptl_busyflag
    while(spi_m1_tx_ptl_busy_flag == true)
    {
        board_delay_ms(1);
        s_cmd_count +=1;

        if(s_cmd_count >3000)
        {
        	dev_spi_m->spi_write_ptl_halt();
        	spi_m1_tx_ptl_busy_flag = false;
            return -1;
        }
    }
    return 0;

}
int hx_drv_spi_mst_protocol_write_sp(uint32_t SRAM_addr, uint32_t img_size, SPI_CMD_DATA_TYPE data_type)
{
    int s_cmd_count = 0;

    if(spi_m1_tx_ptl_busy_flag)
        return -1;
#if defined(CAPSULE) && defined(IC_PACKAGE_WLCSP38)//temp solution
	dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_0);
#else
	dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_1);
#endif

    spi_m1_tx_ptl_busy_flag = true;

	if(data_type == DATA_TYPE_NONE)
	{
	    hx_spimcomm_register_tx_cb((spimcomm_cb_t)spi_m1_callback_ptl_tx);		
		dev_spi_m->spi_write_dma((void *)SRAM_addr, img_size);
	}
	else
	{	
		//set callback function api	
	    hx_spimcomm_register_tx_cb((spimcomm_cb_t)spi_m1_callback_ptl_tx);
		//call to low layer with address and image size	
		dev_spi_m->spi_write_ptl(SPI_M_MODE_SINGLE, (void *)SRAM_addr, img_size, data_type);
	}

	//if blocking code, add wait busy status flag. wait time now use 3 sec
    //wait spis_tx_ptl_busyflag
    while(spi_m1_tx_ptl_busy_flag == true)
    {
        board_delay_ms(1);
        s_cmd_count +=1;

        if(s_cmd_count >3000)
        {
        	dev_spi_m->spi_write_ptl_halt();
        	spi_m1_tx_ptl_busy_flag = false;
            return -1;
        }
    }

    return 0;

}

int hx_drv_spi_mst_protocol_write_sp_capsule_02(uint32_t SRAM_addr, uint32_t img_size, SPI_CMD_DATA_TYPE data_type)
{
    if(spi_m1_tx_ptl_busy_flag)
        return -1;
#if defined(CAPSULE) && defined(IC_PACKAGE_WLCSP38)//temp solution
	dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_0);
#else
	dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_1);
#endif

    spi_m1_tx_ptl_busy_flag = true;
	SPI_Busy_Flag = true;

	if(data_type == DATA_TYPE_NONE)
	{
	    hx_spimcomm_register_tx_cb((spimcomm_cb_t)spi_m1_callback_ptl_tx);		
		dev_spi_m->spi_write_dma((void *)SRAM_addr, img_size);
	}
	else
	{	
		//set callback function api	
	    hx_spimcomm_register_tx_cb((spimcomm_cb_t)spi_m1_callback_ptl_tx);
		//call to low layer with address and image size	
		dev_spi_m->spi_write_ptl(SPI_M_MODE_SINGLE, (void *)SRAM_addr, img_size, data_type);
	}

    return 0;

}

int hx_drv_spi_mst_protocol_write_halt()
{
	dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_1);

    if(E_OK == dev_spi_m->spi_write_ptl_halt())
    {
    	spi_m1_tx_ptl_busy_flag = false;
        return 0;
    }
    else
        return -1;
}

int hx_drv_spi_mst_protocol_read(uint32_t SRAM_addr, uint32_t *data_len)
{
	uint8_t pin_val= 0;
	int s_cmd_count = 0;

	if(data_len == NULL)
		return -1;

    if(spi_m1_rx_ptl_busy_flag)
        return -1;

    //check GPIO pin first
    hx_drv_iomux_get_invalue(HANDSHAKE_PIN_RX,&pin_val);

    spi_m1_rx_ptl_busy_flag = true;

    //wait pin_val to high
    
    while(pin_val == false)
    {
        board_delay_ms(1);
        hx_drv_iomux_get_invalue(HANDSHAKE_PIN_RX,&pin_val);
        s_cmd_count +=1;

        if(s_cmd_count >3000)
        {
        	spi_m1_rx_ptl_busy_flag = false;
            return -1;
        }
    }

    //TODO: read header and check if 6 bytes header correct by sync bytes


	//register callback for rx
	hx_spimcomm_register_rx_cb((spimcomm_cb_t)spi_m1_callback_ptl_rx);



	dev_spi_m = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_1);

	if(dev_spi_m->spi_read_ptl((uint32_t *)SRAM_addr, data_len)!=E_OK)
		return -1;

	while(spi_m1_rx_ptl_busy_flag == true)
    {
        board_delay_ms(1);
        s_cmd_count +=1;

        if(s_cmd_count >3000)
        {
        	spi_m1_rx_ptl_busy_flag = false;
            return -1;
        }
    }

	return 0;
}


//==============SPI 0 flash ===========================//
static void spi_flash_callback_fun_rx(void *status)
{
	cb_flash_rx_flag = true;
    return;
}

static void spi_flash_callback_fun_tx(void *status)
{
	cb_flash_tx_flag = true;
    return;
}

static void spi_flash_callback_fun_err(void *status)
{
    return;
}


int hx_drv_spi_flash_open(uint8_t dev_no)
{
	unsigned char flash_info[3];

	if(dev_no != 0 && dev_no != 1)
		return -1;

	dev_spi_flash = hx_drv_spi_mst_get_dev((USE_DW_SPI_MST_E)dev_no);

	dev_spi_flash->spi_open(DEV_MASTER_MODE,1000000, CLK_BUS_APB);

	info = &(dev_spi_flash->spi_info);

	info->spi_cbs.tx_cb = spi_flash_callback_fun_tx;
	info->spi_cbs.rx_cb = spi_flash_callback_fun_rx;
	info->spi_cbs.err_cb = spi_flash_callback_fun_err;

	//try to read flash id to change current flash_type in sw_spi level
	dev_spi_flash->flash_id(flash_info);
	//cprintf("info data[%x][%x][%x]\n",flash_info[0],flash_info[1],flash_info[2]);


	return 0;
}

int hx_drv_spi_flash_open_speed(uint32_t spi_clk, uint32_t cpu_clk)
{
    unsigned char flash_info[3];

    hx_drv_spi_mst_deinit(USE_DW_SPI_MST_0);
    hx_drv_spi_mst_init(USE_DW_SPI_MST_0);

    dev_spi_flash = hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_0);
    dev_spi_flash->spi_open(DEV_MASTER_MODE, spi_clk, cpu_clk);

    info = &(dev_spi_flash->spi_info);
    info->spi_cbs.tx_cb = spi_flash_callback_fun_tx;
    info->spi_cbs.rx_cb = spi_flash_callback_fun_rx;
    info->spi_cbs.err_cb = spi_flash_callback_fun_err;

    dev_spi_flash->flash_id(flash_info);
    return 0;
}


int hx_drv_spi_flash_close(uint8_t dev_no)
{
	if(dev_no != 0 && dev_no != 1)
		return -1;

	hx_drv_spi_mst_deinit((USE_DW_SPI_MST_E)dev_no);

	dev_spi_flash = NULL;

	return 0;
}

int hx_drv_spi_flash_protocol_eraseall(uint8_t dev_no)
{
	if(dev_no != 0 && dev_no != 1)
		return -1;

	dev_spi_flash = hx_drv_spi_mst_get_dev((USE_DW_SPI_MST_E)dev_no);

	dev_spi_flash->flash_erase_all();

	return 0;
}

int hx_drv_spi_flash_protocol_erase_sector(uint8_t dev_no, uint32_t flash_addr)
{
	if(dev_no != 0 && dev_no != 1)
		return -1;

	dev_spi_flash = hx_drv_spi_mst_get_dev((USE_DW_SPI_MST_E)dev_no);

	dev_spi_flash->flash_erase_sector(flash_addr);

	return 0;
}

int hx_drv_spi_flash_protocol_write(uint8_t dev_no,uint32_t flash_addr, uint32_t SRAM_addr, uint32_t len, uint8_t mode)
{
	if(dev_no != 0 && dev_no != 1)
		return -1;

	if(mode != 1 && mode != 4)
		return -1;

	dev_spi_flash = hx_drv_spi_mst_get_dev((USE_DW_SPI_MST_E)dev_no);

	dev_spi_flash->flash_word_write(mode, flash_addr, (uint32_t *)SRAM_addr, len);

	return 0;
}

int hx_drv_spi_flash_protocol_read(uint8_t dev_no,uint32_t flash_addr, uint32_t SRAM_addr, uint32_t len, uint8_t mode)
{
	if(dev_no != 0 && dev_no != 1)
		return -1;

	if(mode != SPI_M_MODE_SINGLE && mode != SPI_M_MODE_DUAL && mode != SPI_M_MODE_QUAD )
		return -1;

	dev_spi_flash = hx_drv_spi_mst_get_dev((USE_DW_SPI_MST_E)dev_no);

	dev_spi_flash->flash_word_read(mode, flash_addr, (uint32_t *)SRAM_addr, len);

	return 0;
}

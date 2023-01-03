/*
 * test_capture_frame_do_hog.c
 *
 *  Created on: 2020/3/10
 *      Author: 902447
 *
 *  - Himax website update lib version 0.2 - 06/17/2020
 *  - Himax website update lib version 0.6 - 11/03/2020
 *    - update audio parameter and description. add description about get audio data without history
 *    - update image parameter and description. delete test pattern parameter
 *  - Himax website update lib version 0.16 - 02/04/2021(latest)
 *    - update i2c master return check condition
 */

#ifndef SCENARIO_APP_TFLM_SDK_C_
#define SCENARIO_APP_TFLM_SDK_C_

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include "embARC.h"
#include "embARC_debug.h"
#include "board_config.h"
#include "arc_timer.h"
#include "embARC_error.h"
#include "sensor_dp_lib.h"
#include "hx_drv_spi_s.h"
#include "spi_slave_protocol.h"
#include "spi_master_protocol.h"
#include "hx_drv_spi_m.h"
#include "hx_drv_CIS_common.h"
#include "hx_drv_pmu.h"
#include "hx_drv_adcc.h"
#include "hx_drv_lsm9ds1.h"
#include "hx_drv_ms8607.h"
#include "hx_drv_ccs811.h"
#include "hx_drv_bme280.h"
#include "tflm_cis_sensor_defcfg.h"
#include "hx_drv_uart_sw.h"
#include "hx_drv_tflm.h"


#include "ota.h"
#ifndef PURE_BOARD_INIT
#include "hx_drv_tflm_internal.h"
#endif
#include "console_io.h"
#include <internal_inc/tflm_dp_function.h>
#include <internal_inc/tflm_audio_function.h>
#include <internal_inc/tflm_i2cm_function.h>


#define LIB_MAJOR_VERSION 0
#define LIB_MINOR_VERSION 19

#define TFLLM_CHIP_VER_ADDR				0xB00000FC
#define TFLLM_CHIP_VER_MASK				0xFFFFFF00

#define WEI_IMAGE_TYPE_TFLITE_MODEL_DATA  0xe // = 14.

static DEV_UART_SW_PTR dev_uart_sw;
//#define SRAM_END 0x2017_00000

//volatile static uint32_t memory_end_ptr = SRAM_END;

HX_DRV_ERROR_E hx_drv_lib_version(uint32_t *major_ver, uint32_t *minor_ver)
{
	*major_ver = LIB_MAJOR_VERSION;
	*minor_ver = LIB_MINOR_VERSION;
	return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_id_get(uint32_t *id)
{
	uint32_t chip_id = 0;
	chip_id = _arc_read_uncached_32((void *)TFLLM_CHIP_VER_ADDR);
	chip_id = chip_id & TFLLM_CHIP_VER_MASK;

	*id = chip_id;

	return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_sensor_initial(hx_drv_sensor_image_config_t *pimg_config)
{
	uint8_t tp_enable = 0; //not enable tp pattern
	tflm_set_initial_dp_clk();
	tflm_set_sensor_por();
	tflm_cis_set_cfg(tp_enable);
	tflm_set_initial_dp(pimg_config);

	return HX_DRV_LIB_PASS;
}
#ifndef PURE_BOARD_INIT
HX_DRV_ERROR_E hx_drv_sensor_initial_tp(hx_drv_sensor_image_config_t *pimg_config, unsigned char enable) {

	uint8_t tp_enable = enable;
	tflm_set_initial_dp_clk();
	tflm_set_sensor_por();
	tflm_cis_set_cfg(tp_enable);
	tflm_set_initial_dp(pimg_config);

	return HX_DRV_LIB_PASS;
}
#endif
HX_DRV_ERROR_E hx_drv_sensor_capture(hx_drv_sensor_image_config_t *pimg_config)
{
	tflm_recapture_frame(pimg_config);

	return HX_DRV_LIB_PASS;
}

/**
 * \brief	WE1 Stop capture and Sensor stop streaming
 *
 * \retval	HX_DRV_LIB_PASS		Stop capture and streaming success
 * \retval	HX_DRV_LIB_FAIL		Stop capture and streaming fail
 */
extern HX_DRV_ERROR_E hx_drv_sensor_stop_capture()
{
	return tflm_stop_capture();
}
HX_DRV_ERROR_E hx_drv_sensor_stream_on()
{
	return tflm_sensor_streamon();
}
HX_DRV_ERROR_E hx_drv_sensor_stream_off()
{
	return tflm_sensor_streamoff();
}

HX_DRV_ERROR_E hx_drv_image_rescale(uint8_t*in_image, int32_t in_image_width, int32_t in_image_height,  int8_t*out_image, int32_t out_image_width, int32_t out_image_height)
{
	int32_t x,y;
	int32_t ceil_x, ceil_y, floor_x, floor_y;

	int32_t fraction_x,fraction_y,one_min_x,one_min_y;
	int32_t pix[4];//4 pixels for the bilinear interpolation
	int32_t out_image_fix;
	int32_t nxfactor = (in_image_width<<8)/out_image_width;
	int32_t nyfactor = (in_image_height<<8)/out_image_height;

	if((out_image_width > in_image_width) || (out_image_height > in_image_height))
		return HX_DRV_LIB_ERROR;

	for (y = 0; y < out_image_height; y++) {//compute new pixels
		for (x = 0; x < out_image_width; x++) {
			floor_x = (x*nxfactor) >> 8;//left pixels of the window
			floor_y = (y*nyfactor) >> 8;//upper pixels of the window

			ceil_x = floor_x+1;//right pixels of the window
			if (ceil_x >= in_image_width) ceil_x=floor_x;//stay in image

			ceil_y = floor_y+1;//bottom pixels of the window
			if (ceil_y >= in_image_height) ceil_y=floor_y;

			fraction_x = x*nxfactor-(floor_x << 8);//strength coefficients
			fraction_y = y*nyfactor-(floor_y << 8);

			one_min_x = (1 << 8)-fraction_x;
			one_min_y = (1 << 8)-fraction_y;

			pix[0] = in_image[floor_y * in_image_width + floor_x];//store window
			pix[1] = in_image[floor_y * in_image_width + ceil_x];
			pix[2] = in_image[ceil_y * in_image_width + floor_x];
			pix[3] = in_image[ceil_y * in_image_width + ceil_x];

			//interpolate new pixel and truncate it's integer part
			out_image_fix = one_min_y*(one_min_x*pix[0]+fraction_x*pix[1])+fraction_y*(one_min_x*pix[2]+fraction_x*pix[3]);
			out_image_fix = out_image_fix >> (8 * 2);
			out_image[out_image_width*y+x] = out_image_fix-128;
		}
	}

	return HX_DRV_LIB_PASS;

}

HX_DRV_ERROR_E hx_drv_accelerometer_initial()
{
	if(hx_drv_imu_initial() != HX_DRV_IMU_PASS)
		return HX_DRV_LIB_ERROR;

    return HX_DRV_LIB_PASS;
}

//comment this API, use "hx_drv_accelerometer_available_count" instead
#if 0
uint8_t hx_drv_accelerometer_available()
{
	if(hx_drv_imu_accelerationAvailable() == HX_DRV_IMU_MORE_DATA)
		return 1;
	else
        return 0;
}
#endif

uint8_t hx_drv_accelerometer_available_count()
{
	return hx_drv_imu_accelerationAvailableCount();
}


HX_DRV_ERROR_E hx_drv_accelerometer_receive(float *x, float *y, float *z)
{
	if(hx_drv_imu_receive(x, y, z) != HX_DRV_IMU_PASS)
		return HX_DRV_LIB_ERROR;

    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_mic_initial()
{
    if(tflm_audio_init()!= TFLM_AUDIO_NO_ERROR)
    	return HX_DRV_LIB_ERROR;

    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_mic_capture(hx_drv_mic_data_config_t *pmic_config)
{
    tflm_audio_samples_get((tflm_audio_samples_t *) pmic_config);
    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_mic_timestamp_get(int32_t *time)
{
    *time = tflm_audio_timestamp_get();
    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_mic_on()
{
    if(tflm_audio_start() != TFLM_AUDIO_NO_ERROR)
    	return HX_DRV_LIB_ERROR;

    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_mic_off()
{
    if(tflm_audio_stop() != TFLM_AUDIO_NO_ERROR)
    	return HX_DRV_LIB_ERROR;

    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_mic_capture_dual(hx_drv_mic_data_config_t *pmic_config)
{
	uint32_t *aud_addr = &(pmic_config->data_address);
	uint32_t *size = &(pmic_config->data_size);
	if(tflm_audio_data_get(aud_addr, size) == true)
		return HX_DRV_LIB_PASS;
	else
		return HX_DRV_LIB_ERROR;
}


//HX_DRV_ERROR_E hx_drv_uart_initial()
HX_DRV_ERROR_E hx_drv_uart_initial(HX_DRV_UART_BAUDRATE_E baud_rate)
{
    //xprintf_setup();
	if(xprintf_setup_br((CONSOLE_BAUDRATE_E)baud_rate) != 0)
		return HX_DRV_LIB_ERROR;
	else
		return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_uart_print(const char*fmt, ...)
{
    va_list arp;

    va_start(arp, fmt);
    xvprintf(fmt, arp);
    va_end(arp);

    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_uart_getchar(uint8_t *pch)
{
	int ret = 0;

    //ret = console_getchar();
	ret = console_getchar_nonblock();
    if(ret > 0 )
    	*pch = (uint8_t)ret;
    else if(ret == -1)
    	return HX_DRV_LIB_ERROR;
    else if(ret == -2)
    	return HX_DRV_LIB_NODATA;

    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_gpio_initial(hx_drv_gpio_config_t *pgpio_config)
{
    if((pgpio_config->gpio_direction == HX_DRV_GPIO_INPUT) || (pgpio_config->gpio_direction == HX_DRV_GPIO_OUTPUT))
    {
        hx_drv_iomux_set_pmux((IOMUX_INDEX_E) pgpio_config->gpio_pin, (uint8_t) pgpio_config->gpio_direction);
        return HX_DRV_LIB_PASS;
    }
    else
    {
        hx_drv_uart_print("only support gpio_direction: 2 (input), 3 (output) \n");
        return HX_DRV_LIB_ERROR;
    }
}

HX_DRV_ERROR_E hx_drv_gpio_set(hx_drv_gpio_config_t *pgpio_config)
{
    hx_drv_iomux_set_outvalue((IOMUX_INDEX_E) pgpio_config->gpio_pin, pgpio_config->gpio_data);
    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_gpio_get(hx_drv_gpio_config_t *pgpio_config)
{
    hx_drv_iomux_get_invalue((IOMUX_INDEX_E) pgpio_config->gpio_pin, &(pgpio_config->gpio_data));
    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_led_on(HX_DRV_LED_SELECT_E led)
{
    hx_drv_iomux_set_outvalue((IOMUX_INDEX_E) led, HX_DRV_LED_ON);
    hx_drv_iomux_set_pmux((IOMUX_INDEX_E) led, (uint8_t) HX_DRV_GPIO_OUTPUT);   
    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_led_off(HX_DRV_LED_SELECT_E led)
{
    hx_drv_iomux_set_outvalue((IOMUX_INDEX_E) led, HX_DRV_LED_OFF);    
    hx_drv_iomux_set_pmux((IOMUX_INDEX_E) led, (uint8_t) HX_DRV_GPIO_OUTPUT);   
    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_tick_start(void)
{
	//timer already inital when startup. just set timer value back to zero here
	//use timer 0 here
	// timer 0 - system use timer
	// timer 1 - use as board delay
	timer_stop(TIMER_0);
	timer_start(TIMER_0, TIMER_CTRL_NH, 0xffffffff);			// Set Counter LIMIT to MAX

	return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_tick_get(uint32_t *tick)
{
	//*value = _arc_aux_read(AUX_TIMER0_CNT);
	if(timer_current(TIMER_0, tick) != 0)
		return HX_DRV_LIB_ERROR;

	return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_i2cm_set_data(uint8_t slave_addr_sft, uint8_t *addr, uint32_t addr_len, uint8_t *data, uint32_t data_len)
{

	if(hx_drv_iic_write(slave_addr_sft, addr, addr_len, data, data_len) == HX_DRV_IIC_M_PASS)
		return HX_DRV_LIB_PASS;
	else
		return HX_DRV_LIB_ERROR;

}


HX_DRV_ERROR_E hx_drv_i2cm_get_data(uint8_t slave_addr_sft, uint8_t *addr, uint32_t addr_len, uint8_t *data, uint32_t data_len)
{

	if( hx_drv_iic_write_read(slave_addr_sft, addr, addr_len, data, data_len) == HX_DRV_IIC_M_PASS)
    		return HX_DRV_LIB_PASS;
    	else
    		return HX_DRV_LIB_ERROR;
}


HX_DRV_ERROR_E hx_drv_spim_init() {

	if(hx_drv_spi_mst_open() != 0)
		return HX_DRV_LIB_ERROR;
	else
		return HX_DRV_LIB_PASS;

}
HX_DRV_ERROR_E hx_drv_spim_send(uint32_t addr, uint32_t size, HX_DRV_SPI_TYPE data_type) {
	/*SPI_CMD_DATA_TYPE cmd_type = DATA_TYPE_META_DATA;
	switch(data_type) {
	case SPI_TYPE_JPG:
		cmd_type = DATA_TYPE_JPG;
		break;
	case SPI_TYPE_RAW:
		cmd_type = DATA_TYPE_RAW_IMG;
		break;
	case SPI_TYPE_META_DATA:
		cmd_type = DATA_TYPE_META_DATA;
		break;
	}
	if(hx_drv_spi_mst_protocol_write_sp(addr, size, cmd_type)!=0)
		return HX_DRV_LIB_ERROR;
	else
		return HX_DRV_LIB_PASS;*/
	//USE TYPE define in tflm lib
	if(hx_drv_spi_mst_protocol_write_sp(addr, size, (SPI_CMD_DATA_TYPE) data_type)!=0)
			return HX_DRV_LIB_ERROR;
		else
			return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_flash_init() {

	DEV_SPI_PTR dev_spi_m;

	hx_drv_spi_flash_open_speed(50000000, 400000000); // spi_clk, cpu_clk

	dev_spi_m = hx_drv_spi_mst_get_dev((USE_DW_SPI_MST_E)0);
	dev_spi_m->flash_set_xip(1, 4); //flash enable xip mode

	return HX_DRV_LIB_PASS;

}

/*
void* hx_drv_flash_get_Model_address_at_1MB() {

	return (void*)(BASE_ADDR_FLASH+0x100000);
}
*/



void hx_drv_get_mem_desp_address(uint32_t dest_addr) {
	//XIP_SSI_ADDR = 0x28000000
	memcpy((void*)dest_addr,(void*)(WEI_MEMORY_DSP_OFFSET+(0x28000000)),WE1_MEMORY_DSP_SIZE);
}

uint32_t hx_drv_flash_get_Model_address() {
	uint32_t *mem_dest_tmp_addr = NULL;
	 mem_dest_tmp_addr = malloc(WE1_MEMORY_DSP_SIZE);
	 if ( mem_dest_tmp_addr == NULL ) {
		       /* Error Handling */
		//hx_drv_uart_print("Malloc Error! \n");
		return 0;//HX_DRV_LIB_ERROR;
	 }

	 hx_drv_get_mem_desp_address((uint32_t) mem_dest_tmp_addr);

	 SB_Header_t *SB_Header = NULL;
	 uint32_t imageLen = 0;
	 uint32_t CertificateCount = 0;
	 memory_dsp_t memory_dsp_header = {0};
	 uint32_t modCnt = 0;
	 int i = 0;
	 SB_Header = (SB_Header_t *)mem_dest_tmp_addr;
	 imageLen = SB_Load_BE32(&SB_Header->ImageLen);
	 CertificateCount = SB_Load_BE32(&SB_Header->CertificateCount);

	 //hx_drv_uart_print("imageLen = %d, CertificateCount = %d img_header_ADDR = %x\n", imageLen, CertificateCount,((uint32_t)mem_dest_tmp_addr+sizeof(SB_Header_t)+CertificateCount*sizeof(SB_Certificate_t)));

	 memset(&memory_dsp_header, 0x00, sizeof(memory_dsp_t));
	 memcpy((void *)&memory_dsp_header, (void *)((uint32_t)mem_dest_tmp_addr+sizeof(SB_Header_t)+CertificateCount*sizeof(SB_Certificate_t)), imageLen);

	 for(i = 0; i < memory_dsp_header.info.num_sbs; i++)
	 {
	 	if(memory_dsp_header.item[i].pat_type == WEI_IMAGE_TYPE_TFLITE_MODEL_DATA)//0x0e TFLM_MODEL = pat_type
	 	{
	 		/*
	 	   	  mem_dsp_infor[modCnt].addr = memory_dsp_header.item[i].pat_addr;
	 	   	  mem_dsp_infor[modCnt].size = memory_dsp_header.item[i].pat_size;
	 	   	  modCnt++;

	 	   	  if(modCnt == pat_number)
	 	   	  {
	 	   	      break;
	 	   	  }*/
	 		uint32_t model_address = (memory_dsp_header.item[i].pat_addr + BASE_ADDR_FLASH);
	 		uint32_t model_size = memory_dsp_header.item[i].pat_size;
	 		//hx_drv_uart_print("i = %x, pat_type = %x, mem_dsp_infor->addr = %x, mem_dsp_infor->size = %x\n",i, memory_dsp_header.item[i].pat_type, memory_dsp_header.item[i].pat_addr, memory_dsp_header.item[i].pat_size);
	 		//hx_drv_uart_print("model_address = %x, model_size = %x\n",model_address,model_size);
	 		free(mem_dest_tmp_addr);
	 		return model_address;//HX_DRV_LIB_PASS;
	 	}
	 	//hx_drv_uart_print("i = %x, pat_type = %x, mem_dsp_infor->addr = %x, mem_dsp_infor->size = %x\n",i, memory_dsp_header.item[i].pat_type, memory_dsp_header.item[i].pat_addr, memory_dsp_header.item[i].pat_size);
	 }

	 //hx_drv_uart_print("Couldn't find model_address. Please check if pat_type is 0xe or not.\n");
	 free(mem_dest_tmp_addr);
	 return 0;//HX_DRV_LIB_ERROR;

}

void setMuxToI2C() {
	//0xb000_0044 [15:0] SGPIO_MUX1
	//Bit [9:10] PSPI_SHARE PIN MUX: 0:SPI, 1:debug bus, 2, SPL_SLV+I2c M1

	uint32_t reg_val = 0;
    reg_val = _arc_read_uncached_32((void *)0xB0000044);
    reg_val &= ~(0x1<<9);
    reg_val |= (0x1<<10);
    _arc_write_uncached_32((void *)0xB0000044, reg_val);

    reg_val = _arc_read_uncached_32((void *)0xB0000044);
    //hx_drv_uart_print("0xB0000044 data=0x%x\n", reg_val);
}

void setMuxToSPIM() {
	uint32_t reg_val = 0;
    reg_val = _arc_read_uncached_32((void *)0xB0000044);
    reg_val &= ~(0x1<<9);
    reg_val &= ~(0x1<<10);
    _arc_write_uncached_32((void *)0xB0000044, reg_val);
    reg_val = _arc_read_uncached_32((void *)0xB0000044);
    //hx_drv_uart_print("0xB0000044 data=0x%x\n", reg_val);
}

HX_DRV_ERROR_E hx_drv_share_switch(HX_DRV_SHARE_MODE_E mode) {
	switch(mode) {
	case SHARE_MODE_SPIM:
		setMuxToSPIM();
		return HX_DRV_LIB_PASS;
		break;
	case SHARE_MODE_I2CM:
		setMuxToI2C();
		return HX_DRV_LIB_PASS;
		break;
	default:
		return HX_DRV_LIB_ERROR;
	}

	return HX_DRV_LIB_ERROR;

}

HX_DRV_ERROR_E hx_drv_qwiic_ms8607_initial()
{
	if(hx_drv_ms8607_initial() != HX_DRV_QWIIC_PASS)
		return HX_DRV_LIB_ERROR;

    return HX_DRV_LIB_PASS;
}


HX_DRV_ERROR_E hx_drv_qwiic_ms8607_get_data(float* t_data, float* p_data, float* h_data)
{
	int32_t t100_data=0, p100_data=0;

	if(hx_drv_ms8607_receive_t_p(&t100_data, &p100_data) != HX_DRV_QWIIC_PASS)
			return HX_DRV_LIB_ERROR;

	*t_data = (float)t100_data/100;
	*p_data = (float)p100_data/100;

	if(hx_drv_ms8607_receive_h(h_data) != HX_DRV_QWIIC_PASS)
		return HX_DRV_LIB_ERROR;
    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_qwiic_ccs811_initial(HX_DRV_QWIIC_CCS811_I2C_ADDR_E i2caddr)
{
	if(hx_drv_ccs811_initial(i2caddr) != HX_DRV_QWIIC_PASS)
		return HX_DRV_LIB_ERROR;

    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_qwiic_ccs811_get_data(uint16_t* c_data, uint16_t* t_data)
{
	if(hx_drv_ccs811_receive_CO2_and_tVOC(c_data, t_data) != HX_DRV_QWIIC_PASS)
		return HX_DRV_LIB_ERROR;
    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_qwiic_bme280_initial(HX_DRV_QWIIC_BME280_I2C_ADDR_E i2caddr)
{
	if(hx_drv_bme280_initial(i2caddr) != HX_DRV_QWIIC_PASS)
		return HX_DRV_LIB_ERROR;

    return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_qwiic_bme280_get_data(float* t_data, uint32_t* p_data, float* h_data)
{
	if(hx_drv_bme280_receive_TempC(t_data) != HX_DRV_QWIIC_PASS)
		return HX_DRV_LIB_ERROR;

	if(hx_drv_bme280_receive_IntPressure(p_data) != HX_DRV_QWIIC_PASS)
		return HX_DRV_LIB_ERROR;
	
	if(hx_drv_bme280_receive_FloatHumidity(h_data) != HX_DRV_QWIIC_PASS)
		return HX_DRV_LIB_ERROR;
		
    return HX_DRV_LIB_PASS;
}

/**
 * \brief	read flash data back
 *
 * \param[in] flash_addr		read data from flash with dedicated address
 * \param[out] ram_addr			memory location for store data
 * \param[out] len				data length to read back
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_FAIL		Operation fail
 */
/*HX_DRV_ERROR_E hx_drv_paramter_read(uint32_t flash_addr, uint32_t ram_addr, uint32_t len)
{
	int ret = 0;
	hx_drv_spi_flash_open(0);

	ret = hx_drv_spi_flash_protocol_read(0,flash_addr, ram_addr, len, 4);

	hx_drv_spi_flash_close(0);

	if(ret != 0)
		HX_DRV_LIB_ERROR;
	else
		HX_DRV_LIB_PASS;
}
*/
HX_DRV_ERROR_E hx_drv_swuart_initial(HX_DRV_GPIO_E tx_pin, HX_DRV_GPIO_E rx_pin, HX_DRV_UART_BAUDRATE_E baud_rate)
{
	uint32_t baud = 0;
	// uint8_t test_value = 0;
	// uint8_t test_pin = 2;
	// hx_drv_iomux_set_pmux(test_pin,3);
	// hx_drv_iomux_set_outvalue(test_pin, 1);    
	switch(baud_rate) {
	case UART_BR_9600:
		baud = UART_BAUDRATE_9600;
		break;
	case UART_BR_14400:
		baud = UART_BAUDRATE_14400;
		break;
	case  UART_BR_19200:
		baud = UART_BAUDRATE_19200;
		break;
	case UART_BR_38400:
		baud = UART_BAUDRATE_38400;
		break;
	case UART_BR_57600:
		baud = UART_BAUDRATE_57600;
		break;
	case  UART_BR_115200:
		baud = UART_BAUDRATE_115200;
		break;
	case UART_BR_230400:
		baud = UART_BAUDRATE_230400;
		break;
	case UART_BR_460800:
		baud = UART_BAUDRATE_460800;
		break;
	case UART_BR_921600:
	default:
		return HX_DRV_LIB_ERROR;
		break;
	}
	hx_drv_uart_sw_init(USE_SS_UART_SW_0);
	dev_uart_sw = hx_drv_uart_sw_get_dev(USE_SS_UART_SW_0);
    dev_uart_sw->uart_sw_open(baud,  (IOMUX_INDEX_E)tx_pin, (IOMUX_INDEX_E)rx_pin);
	return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E hx_drv_swuart_write(const uint8_t *data, uint32_t data_len)
{
    dev_uart_sw->uart_sw_write(data, data_len);
	return HX_DRV_LIB_PASS;
}
HX_DRV_ERROR_E hx_drv_swuart_single_read(const uint8_t* data) {
	if(dev_uart_sw->uart_sw_read((void*) data, 1)==1)
			return HX_DRV_LIB_PASS;
		else
			return HX_DRV_LIB_NODATA;
}

HX_DRV_ERROR_E hx_drv_swuart_deinitial() {
	if(E_OK == hx_drv_uart_sw_deinit(USE_SS_UART_SW_0))
		return HX_DRV_LIB_PASS;
	else
		return HX_DRV_LIB_ERROR;

}
#endif /* SCENARIO_APP_EMZA_HOG_TEST_TEST_CAPTURE_FRAME_DO_HOG_C_ */

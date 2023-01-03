/*
 * tflm_dp_function.c
 *
 *  Created on: 2020¦~5¤ë18¤é
 *      Author: 902447
 */

#include <internal_inc/tflm_dp_function.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "embARC.h"
#include "embARC_debug.h"
#include "board_config.h"
#include "arc_timer.h"

#include "hx_drv_hw2x2.h"
#include "hx_drv_hw5x5.h"
#include "hx_drv_cdm.h"
#include "hx_drv_jpeg.h"
#include "hx_drv_hog.h"
#include "hx_drv_rs.h"
#include "hx_drv_dp.h"
#include "hx_drv_xdma.h"
#include "hx_drv_rsdma.h"
#include "hx_drv_hogdma.h"
#include "hx_drv_tpg.h"
#include "hx_drv_inp.h"
#include "hx_drv_inp1bitparser.h"
#include "hx_drv_sensorctrl.h"
#include "hx_drv_rtc.h"
#include "hx_drv_edm.h"
#include "hx_drv_pmu.h"
#include "sensor_dp_lib.h"

static volatile uint32_t g_frame_ready = 0;
static volatile uint32_t g_xdma_abnormal = 0;
static volatile uint32_t g_rs_abnormal = 0;
static volatile uint32_t g_hog_abnormal = 0;
static volatile uint32_t g_rs_frameready = 0;
static volatile uint32_t g_hog_frameready = 0;
static volatile uint32_t g_md_detect = 0;
static volatile uint32_t g_wdt1_timeout = 0;
static volatile uint32_t g_wdt2_timeout = 0;
static volatile uint32_t g_wdt3_timeout = 0;

WE1TFLMCfg_WE1DPDriver_t g_tflm_dp_cfg;

int capture_frame_ready_check();

void capture_dplib_cb(SENSORDPLIB_STATUS_E event)
{
	switch(event)
	{
	case SENSORDPLIB_STATUS_EDM_WDT1_TIMEOUT:
		EMBARC_PRINTF("CB WDT1 Timeout\n");
		g_wdt1_timeout = 1;
		break;
	case SENSORDPLIB_STATUS_EDM_WDT2_TIMEOUT:
		EMBARC_PRINTF("CB WDT2 Timeout\n");
		g_wdt2_timeout = 1;
		break;
	case SENSORDPLIB_STATUS_EDM_WDT3_TIMEOUT:
		EMBARC_PRINTF("CB WDT3 Timeout\n");
		g_wdt3_timeout = 1;
		break;
	case SENSORDPLIB_STATUS_SENSORCTRL_WDT_OUT:
		/*
		 * TODO error happen need check sensor
		 * 1. SWRESET Sensor Control & DP
		 * 2. restart streaming flow
		 */
		break;

	case SENSORDPLIB_STATUS_CDM_FIFO_OVERFLOW:
	case SENSORDPLIB_STATUS_CDM_FIFO_UNDERFLOW:
		g_xdma_abnormal = 1;
		break;

	case SENSORDPLIB_STATUS_XDMA_WDMA1_ABNORMAL1:
	case SENSORDPLIB_STATUS_XDMA_WDMA1_ABNORMAL2:
	case SENSORDPLIB_STATUS_XDMA_WDMA1_ABNORMAL3:
	case SENSORDPLIB_STATUS_XDMA_WDMA1_ABNORMAL4:
	case SENSORDPLIB_STATUS_XDMA_WDMA1_ABNORMAL5:
	case SENSORDPLIB_STATUS_XDMA_WDMA1_ABNORMAL6:
	case SENSORDPLIB_STATUS_XDMA_WDMA1_ABNORMAL7:
	case SENSORDPLIB_STATUS_XDMA_WDMA1_ABNORMAL8:
	case SENSORDPLIB_STATUS_XDMA_WDMA1_ABNORMAL9:

	case SENSORDPLIB_STATUS_XDMA_WDMA2_ABNORMAL1:
	case SENSORDPLIB_STATUS_XDMA_WDMA2_ABNORMAL2:
	case SENSORDPLIB_STATUS_XDMA_WDMA2_ABNORMAL3:
	case SENSORDPLIB_STATUS_XDMA_WDMA2_ABNORMAL4:
	case SENSORDPLIB_STATUS_XDMA_WDMA2_ABNORMAL5:
	case SENSORDPLIB_STATUS_XDMA_WDMA2_ABNORMAL6:
	case SENSORDPLIB_STATUS_XDMA_WDMA2_ABNORMAL7:

	case SENSORDPLIB_STATUS_XDMA_WDMA3_ABNORMAL1:
	case SENSORDPLIB_STATUS_XDMA_WDMA3_ABNORMAL2:
	case SENSORDPLIB_STATUS_XDMA_WDMA3_ABNORMAL3:
	case SENSORDPLIB_STATUS_XDMA_WDMA3_ABNORMAL4:
	case SENSORDPLIB_STATUS_XDMA_WDMA3_ABNORMAL5:
	case SENSORDPLIB_STATUS_XDMA_WDMA3_ABNORMAL6:
	case SENSORDPLIB_STATUS_XDMA_WDMA3_ABNORMAL7:
	case SENSORDPLIB_STATUS_XDMA_WDMA3_ABNORMAL8:
	case SENSORDPLIB_STATUS_XDMA_WDMA3_ABNORMAL9:
		g_xdma_abnormal = 1;
		break;

	case SENSORDPLIB_STATUS_XDMA_RDMA_ABNORMAL1:
	case SENSORDPLIB_STATUS_XDMA_RDMA_ABNORMAL2:
	case SENSORDPLIB_STATUS_XDMA_RDMA_ABNORMAL3:
	case SENSORDPLIB_STATUS_XDMA_RDMA_ABNORMAL4:
	case SENSORDPLIB_STATUS_XDMA_RDMA_ABNORMAL5:
		g_xdma_abnormal = 1;
		break;

	case SENSORDPLIB_STATUS_RSDMA_ABNORMAL1:
	case SENSORDPLIB_STATUS_RSDMA_ABNORMAL2:
	case SENSORDPLIB_STATUS_RSDMA_ABNORMAL3:
	case SENSORDPLIB_STATUS_RSDMA_ABNORMAL4:
	case SENSORDPLIB_STATUS_RSDMA_ABNORMAL5:
	case SENSORDPLIB_STATUS_RSDMA_ABNORMAL6:
	case SENSORDPLIB_STATUS_RSDMA_ABNORMAL7:
		/*
		 *  error happen need
		 * 1. SWRESET RS & RS DMA
		 * 2. Re-run flow again
		 */
	    g_rs_abnormal = 1;
		break;

	case SENSORDPLIB_STATUS_HOGDMA_ABNORMAL1:
	case SENSORDPLIB_STATUS_HOGDMA_ABNORMAL2:
	case SENSORDPLIB_STATUS_HOGDMA_ABNORMAL3:
	case SENSORDPLIB_STATUS_HOGDMA_ABNORMAL4:
	case SENSORDPLIB_STATUS_HOGDMA_ABNORMAL5:
	case SENSORDPLIB_STATUS_HOGDMA_ABNORMAL6:
	case SENSORDPLIB_STATUS_HOGDMA_ABNORMAL7:
		/*
		 *  error happen need
		 * 1. SWRESET HOG & HOG DMA
		 * 2. Re-run flow again
		 */
		EMBARC_PRINTF("HOGDMA abnormal %d\n", event);
		g_hog_abnormal = 1;
		break;

	case SENSORDPLIB_STATUS_CDM_MOTION_DETECT:
		/*
		 * app anything want to do
		 * */
		g_md_detect = 1;
		break;
	case SENSORDPLIB_STATUS_XDMA_FRAME_READY:
    	g_frame_ready = 1;
		break;
	case SENSORDPLIB_STATUS_XDMA_WDMA1_FINISH:
	case SENSORDPLIB_STATUS_XDMA_WDMA2_FINISH:
	case SENSORDPLIB_STATUS_XDMA_WDMA3_FINISH:
	case SENSORDPLIB_STATUS_XDMA_RDMA_FINISH:
		break;

	case SENSORDPLIB_STATUS_RSDMA_FINISH:
		/*
		 * RS Frame result ready
		 */
		g_rs_frameready = 1;
		break;
	case SENSORDPLIB_STATUS_HOGDMA_FINISH:
		/*
		 * HOG Frame result ready
		 */
		g_hog_frameready = 1;
		break;
	case SENSORDPLIB_STATUS_TIMER_FIRE_APP_NOTREADY:
		break;
	case SENSORDPLIB_STATUS_TIMER_FIRE_APP_READY:
		break;
	default:
		EMBARC_PRINTF("event = %d\n", event);
		break;
	}
}

int capture_frame_ready_check()
{
	//int read_status = 0;
	uint32_t de0_count, de1_count, de2_count;
	uint32_t convde_count;
	uint16_t af_framecnt;
	uint16_t be_framecnt;
	//uint8_t sensor_framecnt;
	//uint8_t ready_flag, nframe_end, xdmadone;
	//SENSORCTRL_STATE_E state;
	//uint8_t cur_jpeg_enc_frameno = 0;

	while(1)
	{
		if(g_frame_ready == 1)
		{
			g_frame_ready = 0;
			return 0;
		}//g_frame_ready == 1
		/////////End//////////////////////
    	if(g_xdma_abnormal != 0)
    	{
			hx_drv_edm_get_frame_count(&af_framecnt, &be_framecnt);
			EMBARC_PRINTF("xdma af_framecnt=%d,be_framecnt=%d\n",af_framecnt,be_framecnt);
			hx_drv_edm_get_de_count(0, &de0_count);
			hx_drv_edm_get_conv_de_count(&convde_count);
			EMBARC_PRINTF("xdma de0_count=%d, convde_count=%d\n", de0_count, convde_count);
			hx_drv_edm_get_de_count(1, &de1_count);
			hx_drv_edm_get_de_count(2, &de2_count);
			EMBARC_PRINTF("de1_count=%d, de2_count=%d\n", de1_count, de2_count);

    		sensordplib_stop_capture();
    		sensordplib_start_swreset();
    		sensordplib_stop_swreset_WoSensorCtrl();
			EMBARC_PRINTF("xdma bnormal re-setup by CLI\n");
    		g_xdma_abnormal = 0;

			return -1;
    	}
		if((g_wdt1_timeout == 1) || (g_wdt2_timeout == 1) || (g_wdt3_timeout == 1))
		{
			EMBARC_PRINTF("EDM WDT Timeout\n");
			hx_drv_edm_get_frame_count(&af_framecnt, &be_framecnt);
			EMBARC_PRINTF("WDT af_framecnt=%d,be_framecnt=%d\n",af_framecnt,be_framecnt);
			hx_drv_edm_get_de_count(0, &de0_count);
			hx_drv_edm_get_conv_de_count(&convde_count);
			EMBARC_PRINTF("WDT de0_count=%d, convde_count=%d\n", de0_count, convde_count);
			hx_drv_edm_get_de_count(1, &de1_count);
			hx_drv_edm_get_de_count(2, &de2_count);
			EMBARC_PRINTF("WDT de1_count=%d, de2_count=%d\n", de1_count, de2_count);

    		sensordplib_stop_capture();
    		sensordplib_start_swreset();
    		sensordplib_stop_swreset_WoSensorCtrl();
			g_wdt1_timeout = 0;
			g_wdt2_timeout = 0;
			g_wdt3_timeout = 0;

			return -1;
		}
	}
}

void tflm_set_initial_dp_clk()
{
#if defined(CIS_HM0360_MONO_MCLK_24M) || defined(CIS_HM0360_MONO_CCM_EXTLDO_MCLK24M) || defined(CIS_HM0360_MONO_CCM_INTLDO_MCLK24M)\
	|| defined(CIS_HM0360_M_REVB_EXTLDO_MCLK12M) || defined(CIS_HM0360_M_REVB_EXTLDO_MCLK24M)
	g_tflm_dp_cfg.dp_clk_mux = DP_CLK_SRC_XTAL_24M_POST;
	g_tflm_dp_cfg.clk_int_ext = DP_MCLK_SRC_INTERNAL;
	g_tflm_dp_cfg.clk_int_src = DP_MCLK_SRC_INT_SEL_XTAL;
	g_tflm_dp_cfg.mclk_div = SENSORCTRL_MCLK_DIV1;
#elif defined(CIS_HM0360_MONO_OSC_PCLK_12M) || defined(CIS_HM0360_MONO_OSC_PCLK_24M) || defined(CIS_HM0360_BAYER_OSC) || defined(CIS_HM0360_MONO_OSC_PCLK_12M_SENSORMD)
	g_tflm_dp_cfg.dp_clk_mux = DP_CLK_SRC_RC_36M;
	g_tflm_dp_cfg.clk_int_ext = DP_MCLK_SRC_INTERNAL;
	g_tflm_dp_cfg.clk_int_src = DP_MCLK_SRC_INT_SEL_XTAL;
	g_tflm_dp_cfg.mclk_div = SENSORCTRL_MCLK_NO;
/*#elif defined(CIS_HM01B0_MONO)
	g_tflm_dp_cfg.dp_clk_mux = DP_CLK_SRC_RC_36M;//WE1AppCfg_DP_CLK_Mux_RC36M;
	//g_tflm_dp_cfg.mclk_clk_mux = WE1AppCfg_MCLK_CLK_Mux_XTAL;
	g_tflm_dp_cfg.clk_int_ext = DP_MCLK_SRC_INTERNAL;
	g_tflm_dp_cfg.clk_int_src = DP_MCLK_SRC_INT_SEL_XTAL;
	g_tflm_dp_cfg.mclk_div = SENSORCTRL_MCLK_DIV2;*/
#elif defined(CIS_HM11B1_REVC_MCLK_24M_FPS60)
	g_tflm_dp_cfg.dp_clk_mux = DP_CLK_SRC_XTAL_24M_POST;
	g_tflm_dp_cfg.clk_int_ext = DP_MCLK_SRC_INTERNAL;
	g_tflm_dp_cfg.clk_int_src = DP_MCLK_SRC_INT_SEL_XTAL;
	g_tflm_dp_cfg.mclk_div = SENSORCTRL_MCLK_DIV1;
#else
	g_tflm_dp_cfg.dp_clk_mux = DP_CLK_SRC_XTAL_24M_POST;
	g_tflm_dp_cfg.clk_int_ext = DP_MCLK_SRC_INTERNAL;
	g_tflm_dp_cfg.clk_int_src = DP_MCLK_SRC_INT_SEL_XTAL;
	g_tflm_dp_cfg.mclk_div = SENSORCTRL_MCLK_DIV2;
#endif

	hx_drv_dp_set_dp_clk_src(g_tflm_dp_cfg.dp_clk_mux);
	hx_drv_dp_set_mclk_src(g_tflm_dp_cfg.clk_int_ext, g_tflm_dp_cfg.clk_int_src);

	return;
}

void tflm_set_sensor_por()
{
#ifdef CIS_XSHUT_SGPIO0
	g_tflm_dp_cfg.xshutdown_pin_sel = CIS_XHSUTDOWN_IOMUX_SGPIO0;
#else
	g_tflm_dp_cfg.xshutdown_pin_sel = CIS_XHSUTDOWN_IOMUX_SGPIO1;
#endif
	hx_drv_cis_init(g_tflm_dp_cfg.xshutdown_pin_sel, g_tflm_dp_cfg.mclk_div);
	return;
}

HX_DRV_ERROR_E tflm_set_initial_dp(hx_drv_sensor_image_config_t *image_cfg)
{
	uint32_t jpeg_enc_addr;
	uint8_t frame_no;
	uint8_t buffer_no = 0;
	uint32_t jpeg_enc_filesize = 0;

	sensordplib_stop_capture();
	sensordplib_start_swreset();
	sensordplib_stop_swreset_WoSensorCtrl();

	g_tflm_dp_cfg.cyclic_buffer_cnt = 1;
	//g_tflm_dp_cfg.wdma1_startaddr = 0x200E8C00;//CDM min require(reserve 161KB)164864
	//g_tflm_dp_cfg.wdma2_startaddr = 0x20111000;//81520(at least 77448)
	//g_tflm_dp_cfg.wdma3_startaddr = 0x20124E70;
	//g_tflm_dp_cfg.jpegsize_autofill_startaddr = 0x2016FE70;
	g_tflm_dp_cfg.wdma1_startaddr = 0x20124FF0; //CDM not use in current case, assign to somewhere
	g_tflm_dp_cfg.wdma2_startaddr = 0x20111FF0; //JPG 4x image, left 76KB
	g_tflm_dp_cfg.wdma3_startaddr = 0x20124FF0; //RAW image, left 300KB

	g_tflm_dp_cfg.jpegsize_autofill_startaddr = 0x2016FFF0; //left 16bytes, minmum 4 bytes

#if defined(CIS_HM0360_MONO_MCLK_12M) || defined(CIS_HM0360_MONO_OSC_PCLK_12M) || defined(CIS_HM0360_MONO_OSC_PCLK_24M) || defined(CIS_HM0360_BAYER_MCLK_12M) || defined(CIS_HM0360_BAYER_OSC) || defined(CIS_HM0360_MONO_CCM_EXTLDO_MCLK12M) || defined(CIS_HM0360_MONO_CCM_INTLDO_MCLK12M) || defined(CIS_HM0360_MONO_CCM_EXTLDO_MCLK24M) || defined(CIS_HM0360_MONO_CCM_INTLDO_MCLK24M) || defined(CIS_HM0360_MONO_OSC_PCLK_12M_SENSORMD) || defined(CIS_HM0360_MONO_MCLK_PCLK_12M_SENSORMD) || defined(CIS_HM0360_MONO_MCLK_24M)
	g_tflm_dp_cfg.sensor_id = SENSORDPLIB_SENSOR_HM0360_MODE1;
	g_tflm_dp_cfg.sensor_stream_type = SENSORDPLIB_STREAM_HM0360_CONT_MCLK;
	g_tflm_dp_cfg.sensor_width = 640;
	g_tflm_dp_cfg.sensor_height = 480;
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_process_mode = HW2x2_MODE_BINNING;/**< HW2x2 Subsample Mode*/
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_in_width = 640;     /**< HW2x2 ROI Width*/
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_in_height = 480;/**< HW2x2 ROI height*/
	g_tflm_dp_cfg.hw5x5_cfg.demos_color_mode = DEMOS_COLORMODE_YUV420;/**< HW5x5 Demosaic output Color Selection*/
	g_tflm_dp_cfg.hw5x5_cfg.demos_bndmode = DEMOS_BNDODE_INPUTEXTEND;/**< HW5x5 Demosaic Boundary process mode*/
		g_tflm_dp_cfg.hw5x5_cfg.hw55_crop_stx = 0;/**< HW5x5 ROI Start x-position*/
		g_tflm_dp_cfg.hw5x5_cfg.hw55_crop_sty = 0;/**< HW5x5 ROI Start y-position*/
		g_tflm_dp_cfg.hw5x5_cfg.hw55_in_width = 640;/**< HW5x5 ROI width*/
		g_tflm_dp_cfg.hw5x5_cfg.hw55_in_height = 480;/**< HW5x5 ROI height*/
		g_tflm_dp_cfg.jpeg_cfg.enc_width = 640; /**< JPEG encoding width(divide by 16)*/
		g_tflm_dp_cfg.jpeg_cfg.enc_height = 480; /**< JPEG encoding height(divide by 16)*/
	g_tflm_dp_cfg.jpeg_cfg.jpeg_enctype = JPEG_ENC_TYPE_YUV400;/**< JPEG Encoding Color format Selection*/
	g_tflm_dp_cfg.jpeg_cfg.dec_width = 640; /**< JPEG Decoding ROI width(divide by 16)*/
	g_tflm_dp_cfg.jpeg_cfg.dec_height = 480;

#elif defined(CIS_HM01B0_MONO)
	g_tflm_dp_cfg.sensor_id = SENSORDPLIB_SENSOR_HM01B0_8BITIO;
	g_tflm_dp_cfg.sensor_stream_type = SENSORDPLIB_STREAM_HM01B0_CONT;
	g_tflm_dp_cfg.sensor_width = 324;
	g_tflm_dp_cfg.sensor_height = 244;
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_process_mode  = HW2x2_MODE_UNITY;
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_in_width = 320;     /**< HW2x2 ROI Width*/
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_in_height = 240;/**< HW2x2 ROI height*/
	g_tflm_dp_cfg.hw5x5_cfg.demos_color_mode = DEMOS_COLORMODE_YUV400;/**< HW5x5 Demosaic output Color Selection*/
	g_tflm_dp_cfg.hw5x5_cfg.demos_bndmode = DEMOS_BNDODE_EXTEND0;/**< HW5x5 Demosaic Boundary process mode*/
	g_tflm_dp_cfg.hw5x5_cfg.hw55_crop_stx = 2;/**< HW5x5 ROI Start x-position*/
	g_tflm_dp_cfg.hw5x5_cfg.hw55_crop_sty = 2;/**< HW5x5 ROI Start y-position*/
	g_tflm_dp_cfg.hw5x5_cfg.hw55_in_width = 320;/**< HW5x5 ROI width*/
	g_tflm_dp_cfg.hw5x5_cfg.hw55_in_height = 240;/**< HW5x5 ROI height*/
	g_tflm_dp_cfg.jpeg_cfg.enc_width = 320; /**< JPEG encoding width(divide by 16)*/
	g_tflm_dp_cfg.jpeg_cfg.enc_height = 240; /**< JPEG encoding height(divide by 16)*/
	g_tflm_dp_cfg.jpeg_cfg.jpeg_enctype = JPEG_ENC_TYPE_YUV400;/**< JPEG Encoding Color format Selection*/
	g_tflm_dp_cfg.jpeg_cfg.dec_width = 320; /**< JPEG Decoding ROI width(divide by 16)*/
	g_tflm_dp_cfg.jpeg_cfg.dec_height = 240;
#elif defined(CIS_HM11B1_REVC_MCLK_24M_FPS60)
	g_tflm_dp_cfg.sensor_id = SENSORDPLIB_SENSOR_HM11B1_MSB;
	#ifdef CIS_AOS_MODE
	g_tflm_dp_cfg.sensor_stream_type = SENSORDPLIB_STREAM_HM11B1_LOWPOWER;
	#else
	g_tflm_dp_cfg.sensor_stream_type = SENSORDPLIB_STREAM_NONEAOS;
	#endif
	g_tflm_dp_cfg.sensor_width = 320;
	g_tflm_dp_cfg.sensor_height = 200;
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_process_mode  = HW2x2_MODE_UNITY;
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_in_width = 320;     /**< HW2x2 ROI Width*/
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_in_height = 200;/**< HW2x2 ROI height*/
	g_tflm_dp_cfg.hw5x5_cfg.demos_color_mode = DEMOS_COLORMODE_YUV400;/**< HW5x5 Demosaic output Color Selection*/
	g_tflm_dp_cfg.hw5x5_cfg.demos_bndmode = DEMOS_BNDODE_EXTEND0;/**< HW5x5 Demosaic Boundary process mode*/
	g_tflm_dp_cfg.hw5x5_cfg.hw55_crop_stx = 0;/**< HW5x5 ROI Start x-position*/
	g_tflm_dp_cfg.hw5x5_cfg.hw55_crop_sty = 0;/**< HW5x5 ROI Start y-position*/
	g_tflm_dp_cfg.hw5x5_cfg.hw55_in_width = 320;/**< HW5x5 ROI width*/
	g_tflm_dp_cfg.hw5x5_cfg.hw55_in_height = 192;/**< HW5x5 ROI height*/
	g_tflm_dp_cfg.jpeg_cfg.enc_width = 320; /**< JPEG encoding width(divide by 16)*/
	g_tflm_dp_cfg.jpeg_cfg.enc_height = 192; /**< JPEG encoding height(divide by 16)*/
	g_tflm_dp_cfg.jpeg_cfg.jpeg_enctype = JPEG_ENC_TYPE_YUV400;/**< JPEG Encoding Color format Selection*/
	g_tflm_dp_cfg.jpeg_cfg.dec_width = 320; /**< JPEG Decoding ROI width(divide by 16)*/
	g_tflm_dp_cfg.jpeg_cfg.dec_height = 192;
#endif


	g_tflm_dp_cfg.subsample = INP_SUBSAMPLE_DISABLE;
	g_tflm_dp_cfg.hw2x2_cfg.hw2x2_path = HW2x2_PATH_THROUGH;
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_mono_round_mode = HW2x2_ROUNDMODE_FLOOR;/**< HW2x2 Rounding Mode*/
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_crop_stx = 0;  /**< HW2x2 ROI Start X Position*/
	g_tflm_dp_cfg.hw2x2_cfg.hw_22_crop_sty = 0; /**< HW2x2 ROI Start Y Position*/

	g_tflm_dp_cfg.cdm_cfg.cdm_enable = CDM_ENABLE_ON;				/*!< CDM enable */
	g_tflm_dp_cfg.cdm_cfg.init_map_flag = CDM_INIMAP_FLAG_ON_ONEFRAME_ONLY;		/*!< CDM initial map flag */
	g_tflm_dp_cfg.cdm_cfg.cpu_activeflag = CDM_CPU_ACTFLAG_ACTIVE;		/*!< CDM cpu active flag */
	g_tflm_dp_cfg.cdm_cfg.meta_dump = CDM_ENABLE_MATA_DUMP_ON;		/*!< CDM meta data dump enable or disable */
	g_tflm_dp_cfg.cdm_cfg.ht_packing = CDM_ENABLE_HT_PACKING_ON;		/*!< CDM meta data dump packing or unpacking */
	g_tflm_dp_cfg.cdm_cfg.cdm_min_allow_dis = 3;				/*!< CDM algorithm minimum allowed distance between pixel and threshold setting*/
	g_tflm_dp_cfg.cdm_cfg.cdm_tolerance = 3;				/*!< CDM algorithm tolerance setting*/
	g_tflm_dp_cfg.cdm_cfg.cdm_reactance = 2;				/*!< CDM algorithm reactance setting*/
	g_tflm_dp_cfg.cdm_cfg.cdm_relaxation = 1;					/*!< CDM algorithm relaxation setting*/
	g_tflm_dp_cfg.cdm_cfg.cdm_eros_th = 3;				/*!< CDM algorithm erosion threshold setting*/
	g_tflm_dp_cfg.cdm_cfg.cdm_num_ht_th = 10;					/*!< CDM algorithm number of hot pixels threshold setting*/

	g_tflm_dp_cfg.cdm_cfg.cdm_num_ht_vect_th_x = 8;			/*!< CDM algorithm threshold for number of hot-pixels in each bin of the x-projection vector setting*/
	g_tflm_dp_cfg.cdm_cfg.cdm_num_ht_vect_th_y = 4;			/*!< CDM algorithm threshold for number of hot-pixels in each bin of the y-projection vector setting*/
	g_tflm_dp_cfg.cdm_cfg.cdm_num_cons_ht_bin_th_x = 1;		/*!< CDM algorithm threshold for number of consecutive hot bins of the x-projection vector setting*/
	g_tflm_dp_cfg.cdm_cfg.cdm_num_cons_ht_bin_th_y = 1;
	g_tflm_dp_cfg.cdm_cfg.cdm_crop_stx = 0;	/*!< CDM input ROI start x position*/
	g_tflm_dp_cfg.cdm_cfg.cdm_crop_sty = 0;	/*!< CDM input ROI start y position*/
	g_tflm_dp_cfg.cdm_cfg.cdm_in_width = 320;	/*!< CDM input ROI width*/
	g_tflm_dp_cfg.cdm_cfg.cdm_in_height = 240;	/*!< CDM input ROI height*/

	g_tflm_dp_cfg.hw5x5_cfg.fir_procmode = FIR_PROCMODE_LBP1;/**< HW5x5 FIR mode*/
	g_tflm_dp_cfg.hw5x5_cfg.firlpf_bndmode = FIRLPF_BNDODE_REPEAT;/**< HW5x5 FIR and LPF boundary extend mode*/
	g_tflm_dp_cfg.hw5x5_cfg.fir_lbp_th = 0x3;/**< HW5x5 FIR LBP Threshold*/
	g_tflm_dp_cfg.hw5x5_cfg.demos_pattern_mode = DEMOS_PATTENMODE_BGGR;/**< Bayer Sensor layout Selection for HW5x5*/
	g_tflm_dp_cfg.hw5x5_cfg.demoslpf_roundmode = DEMOSLPF_ROUNDMODE_FLOOR;/**< HW5x5 Demosaic and LPF Rounding mode*/
	g_tflm_dp_cfg.hw5x5_cfg.hw5x5_path = HW5x5_PATH_BYPASS_5X5;/**< HW5x5 Path Selection*/
	g_tflm_dp_cfg.hw5x5_cfg.demos_bndmode = DEMOS_BNDODE_INPUTEXTEND;/**< HW5x5 Demosaic Boundary process mode*/


	g_tflm_dp_cfg.jpeg_cfg.jpeg_path = JPEG_PATH_ENCODER_EN;/**< JPEG Path Selection*/
	g_tflm_dp_cfg.jpeg_cfg.jpeg_encqtable = JPEG_ENC_QTABLE_4X;/**< JPEG Encoding quantization table Selection*/
	g_tflm_dp_cfg.jpeg_cfg.dec_roi_stx = 0; /**< JPEG Decoding ROI Start x-position(divide by 16)*/
	g_tflm_dp_cfg.jpeg_cfg.dec_roi_sty = 0; /**< JPEG Decoding ROI Start y-position(divide by 16)*/

//#endif


	sensordplib_set_xDMA_baseaddrbyapp(g_tflm_dp_cfg.wdma1_startaddr, g_tflm_dp_cfg.wdma2_startaddr, g_tflm_dp_cfg.wdma3_startaddr);
	sensordplib_set_jpegfilesize_addrbyapp(g_tflm_dp_cfg.jpegsize_autofill_startaddr);

	if(sensordplib_set_sensorctrl_inp(g_tflm_dp_cfg.sensor_id
				, g_tflm_dp_cfg.sensor_stream_type
				, g_tflm_dp_cfg.sensor_width
				, g_tflm_dp_cfg.sensor_height
				, g_tflm_dp_cfg.subsample) !=0)
	{
		return HX_DRV_LIB_ERROR;
	}

	if(tflm_sensor_streamon() != HX_DRV_LIB_PASS)
	{
		return HX_DRV_LIB_ERROR;
	}

	sensordplib_set_mclkctrl_xsleepctrl_bySCMode();

	hx_drv_pmu_set_ctrl(PMU_SEN_INIT, 0);

	sensordplib_set_int_hw5x5_jpeg_wdma23(g_tflm_dp_cfg.hw5x5_cfg
			, g_tflm_dp_cfg.jpeg_cfg,
			g_tflm_dp_cfg.cyclic_buffer_cnt,
			capture_dplib_cb);

	sensordplib_set_sensorctrl_start();

	if(capture_frame_ready_check() != 0)
	{
		return HX_DRV_LIB_ERROR;
	}

    hx_drv_xdma_get_WDMA2_bufferNo(&buffer_no);
    hx_drv_xdma_get_WDMA2NextFrameIdx(&frame_no);
	if(frame_no == 0)
	{
		frame_no = buffer_no - 1;
	}else{
		frame_no = frame_no - 1;
	}
	hx_drv_jpeg_get_FillFileSizeToMem(frame_no, g_tflm_dp_cfg.jpegsize_autofill_startaddr, &jpeg_enc_filesize);
	hx_drv_jpeg_get_MemAddrByFrameNo(frame_no, g_tflm_dp_cfg.wdma2_startaddr, &jpeg_enc_addr);

	image_cfg->jpeg_address = (uint32_t) jpeg_enc_addr;
	image_cfg->jpeg_size = (uint32_t)jpeg_enc_filesize;
	image_cfg->raw_address = (uint32_t)g_tflm_dp_cfg.wdma3_startaddr;
	image_cfg->raw_size = (uint32_t)g_tflm_dp_cfg.jpeg_cfg.enc_width * g_tflm_dp_cfg.jpeg_cfg.enc_height;
	image_cfg->img_width = (uint32_t)g_tflm_dp_cfg.jpeg_cfg.enc_width;
	image_cfg->img_height = (uint32_t)g_tflm_dp_cfg.jpeg_cfg.enc_height;


	return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E tflm_recapture_frame(hx_drv_sensor_image_config_t *image_cfg)
{
	uint32_t jpeg_enc_addr;
	uint8_t frame_no;
	uint8_t buffer_no = 0;
	uint32_t jpeg_enc_filesize = 0;

	sensordplib_retrigger_capture();

	if(capture_frame_ready_check() != 0)
	{
		return HX_DRV_LIB_ERROR;
	}

    hx_drv_xdma_get_WDMA2_bufferNo(&buffer_no);
    hx_drv_xdma_get_WDMA2NextFrameIdx(&frame_no);
	if(frame_no == 0)
	{
		frame_no = buffer_no - 1;
	}else{
		frame_no = frame_no - 1;
	}
	hx_drv_jpeg_get_FillFileSizeToMem(frame_no, g_tflm_dp_cfg.jpegsize_autofill_startaddr, &jpeg_enc_filesize);
	hx_drv_jpeg_get_MemAddrByFrameNo(frame_no, g_tflm_dp_cfg.wdma2_startaddr, &jpeg_enc_addr);

	image_cfg->jpeg_address = (uint32_t) jpeg_enc_addr;
	image_cfg->jpeg_size = (uint32_t)jpeg_enc_filesize;
	image_cfg->raw_address = (uint32_t)g_tflm_dp_cfg.wdma3_startaddr;
	image_cfg->raw_size = (uint32_t)g_tflm_dp_cfg.jpeg_cfg.enc_width * g_tflm_dp_cfg.jpeg_cfg.enc_height;

	return HX_DRV_LIB_PASS;
}

HX_DRV_ERROR_E tflm_stop_capture()
{
	HX_DRV_ERROR_E ret = HX_DRV_LIB_PASS;
	sensordplib_stop_capture();
	if(tflm_sensor_streamoff() != HX_DRV_LIB_PASS)
	{
		ret = HX_DRV_LIB_ERROR;
	}
	sensordplib_start_swreset();
	sensordplib_stop_swreset_WoSensorCtrl();
	return ret;
}

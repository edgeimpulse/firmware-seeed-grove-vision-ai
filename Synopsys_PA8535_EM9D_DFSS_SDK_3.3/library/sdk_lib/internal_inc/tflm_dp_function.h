/*
 * tflm_dp_function.h
 *
 *  Created on: 2020¦~5¤ë18¤é
 *      Author: 902447
 */

#ifndef LIBRARY_TFLM_INTERNAL_INC_TFLM_DP_FUNCTION_H_
#define LIBRARY_TFLM_INTERNAL_INC_TFLM_DP_FUNCTION_H_

#include "sensor_dp_lib.h"
#include "hx_drv_tflm.h"
#include "tflm_cis_sensor_defcfg.h"


typedef struct
{
	SENSORDPLIB_SENSOR_E sensor_id;
	SENSORDPLIB_STREAM_E sensor_stream_type;
	uint16_t sensor_width;
	uint16_t sensor_height;
    INP_SUBSAMPLE_E subsample;
	DP_DP_CLK_SRC_E   dp_clk_mux;
	DP_MCLK_SRC_INT_EXT_E clk_int_ext;
	DP_MCLK_SRC_INT_SEL_E clk_int_src;
	SENSORCTRL_MCLK_E    mclk_div;
	CIS_XHSHUTDOWN_INDEX_E  xshutdown_pin_sel;
    uint8_t cyclic_buffer_cnt;
    uint32_t wdma1_startaddr;
    uint32_t wdma2_startaddr;
    uint32_t wdma3_startaddr;
    uint32_t jpegsize_autofill_startaddr;
	HW5x5_CFG_T hw5x5_cfg;
	JPEG_CFG_T jpeg_cfg;
	HW2x2_CFG_T hw2x2_cfg;
	CDM_CFG_T cdm_cfg;
}WE1TFLMCfg_WE1DPDriver_t;

void tflm_set_initial_dp_clk();
void tflm_set_sensor_por();
HX_DRV_ERROR_E tflm_set_initial_dp(hx_drv_sensor_image_config_t *image_cfg);
HX_DRV_ERROR_E tflm_recapture_frame(hx_drv_sensor_image_config_t *image_cfg);
HX_DRV_ERROR_E tflm_stop_capture();


#endif /* LIBRARY_TFLM_INTERNAL_INC_TFLM_DP_FUNCTION_H_ */

/*
 * vip_algo.h
 *
 *  Created on: 2020¦~12¤ë9¤é
 *      Author: 904091
 */

#ifndef APP_SCENARIO_APP_AIOT_BODYDETECT_ALLON_TFLITE_VIP_ALGO_H_
#define APP_SCENARIO_APP_AIOT_BODYDETECT_ALLON_TFLITE_VIP_ALGO_H_

#include "app_algo.h"

#if defined(HX_VIP_YOMO) && ( defined(TFLITE_MICRO_HIMAX_V15) || defined(TFLITE_MICRO_HIMAX_V24) )

#ifdef __cplusplus
extern "C" {
#endif
#ifdef USE_MODIFY_ROI_TOOL
void vip_algo_run( unsigned char *img, const int img_h, const int img_w, struct_algoResult *p_res , WR_ROI_SET wr_roi_set);
#else
void vip_algo_run( unsigned char *img, const int img_h, const int img_w, struct_algoResult *p_res);
#endif
#ifdef __cplusplus
}
#endif

#endif

#endif /* APP_SCENARIO_APP_AIOT_BODYDETECT_ALLON_TFLITE_VIP_ALGO_H_ */

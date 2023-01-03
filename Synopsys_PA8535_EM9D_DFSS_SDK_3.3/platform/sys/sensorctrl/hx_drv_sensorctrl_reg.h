/*
 * hx_drv_sensorctrl_reg.h
 *
 *  Created on: 2019¦~6¤ë19¤é
 *      Author: 902447
 */

#ifndef SYS_SENSORCTRL_HX_DRV_SENSORCTRL_REG_H_
#define SYS_SENSORCTRL_HX_DRV_SENSORCTRL_REG_H_

#include "embARC_toolchain.h"

/**
 * \brief	Sensor Control register structure
 * \details	Detailed struct description of Sensor Control
 *	block register information, implementation of Sensor Control
 */
typedef volatile struct sensorctrl_reg_s {
	uint32_t SENCTRL_MODE;		   /*!< (0x00) : sensorctrl address*/
	uint32_t SENCTRL_T_PRE_POST;   /*!< (0x04) : sensorctrl address*/
	uint32_t SENCTRL_NFRAME;		/*!< (0x08) : sensorctrl address*/
	uint32_t SENCTRL_FVLD_WDT;		/*!< (0x0C) : sensorctrl address*/
	uint32_t SENCTRL_TRIG_LOW_LINELENGTH;		/*!< (0x10) : sensorctrl address*/
	uint32_t SENCTRL_STATE;		/*!< (0x14) : sensorctrl address*/
} sensorctrl_REG, *sensorctrl_REG_PTR;

/*Register default value*/
#define DEFAULT_SENSORCTROL_OPMODE  			0
#define DEFAULT_SENSORCTROL_PRETIMING 			0
#define DEFAULT_SENSORCTROL_POSTTIMING  		0
#define DEFAULT_SENSORCTROL_NUMOFFRAME  		0
#define DEFAULT_SENSORCTROL_TRIGGERLOWLEN  		0
#define DEFAULT_SENSORCTROL_WDT	  				0


#endif /* SYS_SENSORCTRL_HX_DRV_SENSORCTRL_REG_H_ */

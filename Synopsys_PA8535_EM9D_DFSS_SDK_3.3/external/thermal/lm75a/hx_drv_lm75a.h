/*
 * hx_drv_LM75A.h
 *
 *  Created on: 2018/10/9
 *      Author: 902447
 */

#ifndef HX_DRV_LM75A_H_
#define HX_DRV_LM75A_H_

#include "board.h"
#include "hx_drv_iic_m.h"
/*
MSB
1    0    0   1   A2   A1   A0
A2, A1, A0 is ground
LM75A_SLAVE_ADDRESS = 0x48 << 1 = 0x90;
*/
//for EM9D no need shift slave ID, for CX3 need shift slave ID
#define LM75A_SLAVE_ADDRESS   0x48//0x90
#define IIC_M_ID_LM75A        USE_SS_IIC_1
#define LM75A_SYSTEM_SUPPORT_FLOATING

#define LM75A_TEMP_REG        0x00
#define LM75A_CONF_REG        0x01
#define LM75A_THYST_REG       0x02
#define LM75A_TOS_REG         0x03

#define LM75A_DEGREES_RESOLUTION   0.125
#define LM75A_TOS_THYST_RESOLUTION   0.5
#define LM75A_DEGREES_RESOLUTION_SHIFT     3
#define LM75A_TOS_THYST_RESOLUTION_SHIFT   1

#define INVALID_LM75A_TEMPERATURE 1000

/** LM75A Errors Type **/
typedef enum LM75A_ERROR_S
{
	LM75A_NO_ERROR                     = 0,	/**< No ERROR */
	LM75A_ERROR_INVALID_PARAMETERS     = 1,	/**< ERROR MSG: Invalid parameters */
	LM75A_ERROR_I2C                    = 2,	/**< ERROR MSG: I2C Fail */
	LM75A_ERROR_OVERFLOW     = 3,	/**< ERROR MSG: Over INVALID_LM75A_TEMPERATURE*/
	LM75A_UNKNOWN_ERROR      = 4,	/**< ERROR MSG: UNKNOWN ERROR*/
} LM75A_ERROR_E;

typedef enum LM75A_OS_MODE_S
{
	LM75A_OS_COMPARATOR      = 0,
	LM75A_OS_INT             = 1,
} LM75A_OS_MODE_E;

typedef enum LM75A_SHUTDOWN_MODE_S
{
	LM75A_SHUTDOWN_NORMAL      = 0,
	LM75A_SHUTDOWN_SHUTDOWN    = 1,
} LM75A_SHUTDOWN_MODE_E;

typedef enum LM75A_POLARITY_S
{
	LM75A_POLARITY_ACTIVELOW      = 0,
	LM75A_POLARITY_ACTIVEHIGH    = 1,
} LM75A_POLARITY_E;

typedef enum LM75A_OSFAULTQUEUE_S
{
	LM75A_OSFAULTQUEUE_1    = 0,
	LM75A_OSFAULTQUEUE_2    = 1,
	LM75A_OSFAULTQUEUE_4    = 2,
	LM75A_OSFAULTQUEUE_6    = 3,
} LM75A_OSFAULTQUEUE_E;

typedef enum LM75A_EVENT_S
{
	LM75A_EVENT_RESET     = 0,
	LM75A_EVENT_ACTIVE    = 1,
} LM75A_EVENT_E;


typedef void (*LM75A_SignalEvent_t) (LM75A_EVENT_E event);

/*!
 * \brief getTemperatureInDegrees Get temperature from LM75A sensor in degrees
 * \return (float) Sensor temperature in degrees (return INVALID_LM75A_TEMPERATURE if error happened)
 */
/*The resolution for register to degree is 0.125(LM75A_DEGREES_RESOLUTION)*/
#ifdef LM75A_SYSTEM_SUPPORT_FLOATING
LM75A_ERROR_E hx_drv_lm75a_getTemperatureInDegrees(float *real_value);
#else
LM75A_ERROR_E hx_drv_lm75a_getTemperatureInDegrees(int *real_value);
#endif
/*!
 * \brief getTemperatureInFahrenheit Get temperature from LM75A sensor in fahrenheit
 * \return (float) Sensor temperature in fahrenheit (return INVALID_LM75A_TEMPERATURE if error happened)
 */
#ifdef LM75A_SYSTEM_SUPPORT_FLOATING
LM75A_ERROR_E hx_drv_lm75a_getTemperatureInFahrenheit(float *temperature_in_degrees);
#endif
LM75A_ERROR_E hx_drv_lm75a_getTemperatureReg(uint16_t *temperature_in_reg);


/*The resolution for register to degree is 0.5(LM75A_TOS_THYST_RESOLUTION)*/
#ifdef LM75A_SYSTEM_SUPPORT_FLOATING
LM75A_ERROR_E hx_drv_lm75a_get_tosDegree(float *tos);
#else
LM75A_ERROR_E hx_drv_lm75a_get_tosDegree(int *tos);
#endif
/*The resolution for register to degree is 0.5(LM75A_TOS_THYST_RESOLUTION)*/
#ifdef LM75A_SYSTEM_SUPPORT_FLOATING
LM75A_ERROR_E hx_drv_lm75a_get_thysDegree(float *thys);
#else
LM75A_ERROR_E hx_drv_lm75a_get_thysDegree(int *thys);
#endif
/*The resolution for register to degree is 0.5(LM75A_TOS_THYST_RESOLUTION)*/
LM75A_ERROR_E hx_drv_lm75a_get_tosReg(uint16_t *tos);
/*The resolution for register to degree is 0.5(LM75A_TOS_THYST_RESOLUTION)*/
LM75A_ERROR_E hx_drv_lm75a_get_thysReg(uint16_t *thys);
/*The resolution for register to degree is 0.5(LM75A_TOS_THYST_RESOLUTION)*/
LM75A_ERROR_E hx_drv_lm75a_set_tosbyReg(uint16_t tos);
/*The resolution for register to degree is 0.5(LM75A_TOS_THYST_RESOLUTION)*/
LM75A_ERROR_E hx_drv_lm75a_set_thysbyReg(uint16_t thys);
/*The resolution for register to degree is 0.5(LM75A_TOS_THYST_RESOLUTION)*/
#ifdef LM75A_SYSTEM_SUPPORT_FLOATING
LM75A_ERROR_E hx_drv_lm75a_set_tosbyDegree(float tos);
#else
LM75A_ERROR_E hx_drv_lm75a_set_tosbyDegree(int tos);
#endif
/*The resolution for register to degree is 0.5(LM75A_TOS_THYST_RESOLUTION)*/
#ifdef LM75A_SYSTEM_SUPPORT_FLOATING
LM75A_ERROR_E hx_drv_lm75a_set_thysbyDegree(float thys);
#else
LM75A_ERROR_E hx_drv_lm75a_set_thysbyDegree(int thys);
#endif


LM75A_ERROR_E hx_drv_lm75a_set_OS_mode(LM75A_OS_MODE_E mode);
LM75A_ERROR_E hx_drv_lm75a_get_OS_mode(LM75A_OS_MODE_E *mode);
LM75A_ERROR_E hx_drv_lm75a_set_Shutdown_mode(LM75A_SHUTDOWN_MODE_E mode);
LM75A_ERROR_E hx_drv_lm75a_get_Shutdown_mode(LM75A_SHUTDOWN_MODE_E *mode);
LM75A_ERROR_E hx_drv_lm75a_set_Polarity(LM75A_POLARITY_E mode);
LM75A_ERROR_E hx_drv_lm75a_get_Polarity(LM75A_POLARITY_E *mode);
LM75A_ERROR_E hx_drv_lm75a_set_OSFaultQueue(LM75A_OSFAULTQUEUE_E mode);
LM75A_ERROR_E hx_drv_lm75a_get_OSFaultQueue(LM75A_OSFAULTQUEUE_E *mode);

LM75A_ERROR_E hx_drv_lm75a_getRegister(uint8_t regAddress, uint8_t *val);
LM75A_ERROR_E hx_drv_lm75a_setRegister(uint8_t regAddress, uint8_t newVal);
LM75A_ERROR_E hx_drv_lm75a_getTwoRegisters(uint8_t regAddress, uint16_t *val);
LM75A_ERROR_E hx_drv_lm75a_setTwoRegisters(uint8_t regAddress, uint16_t newVal);

LM75A_ERROR_E hx_drv_lm75a_register_cb(LM75A_SignalEvent_t  cb_event);


#endif /* HX_DRV_LM75A_H_ */

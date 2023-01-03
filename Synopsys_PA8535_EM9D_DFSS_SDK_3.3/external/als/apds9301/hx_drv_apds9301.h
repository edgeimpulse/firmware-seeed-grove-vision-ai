/*
 * hx_drv_alsAPDS9301.h
 *
 *  Created on: 2018¦~10¤ë4¤é
 *      Author: user
 */

#ifndef INC_HX_DRV_ALSAPDS9301_H_
#define INC_HX_DRV_ALSAPDS9301_H_

#include "board.h"
#include "hx_drv_iic_m.h"

/*
GND  0101001 = 0x29 << 1 = 0x52
Float  0111001 = 0x39 << 1 = 0x72
VDD 1001001 = 0x49 << 1 = 0x92
*/
//for EM9D no need shift slave ID, for CX3 need shift slave ID
#define APDS9301_SLAVE_ADDR    0x29//0x39//0x72
#define IIC_M_ID_APDS9301      USE_SS_IIC_1

#define APDS9301_SYSTEM_SUPPORT_FLOATING

#define APDS9301_CONTROL_REG        0x80
#define APDS9301_TIMING_REG         0x81
#define APDS9301_THRESHLOWLOW_REG   0x82
#define APDS9301_THRESHLOWHI_REG    0x83
#define APDS9301_THRESHHILOW_REG    0x84
#define APDS9301_THRESHHIHI_REG     0x85
#define APDS9301_INTERRUPT_REG      0x86
#define APDS9301_ID_REG             0x8A
#define APDS9301_DATA0LOW_REG       0x8C
#define APDS9301_DATA0HI_REG        0x8D
#define APDS9301_DATA1LOW_REG       0x8E
#define APDS9301_DATA1HI_REG        0x8F

/** APDS9301 Errors Type **/
typedef enum APDS9301_ERROR_S
{
	APDS9301_NO_ERROR                     = 0,	/**< No ERROR */
	APDS9301_ERROR_INVALID_PARAMETERS     = 1,	/**< ERROR MSG: Invalid parameters */
	APDS9301_ERROR_I2C                    = 2,	/**< ERROR MSG: I2C Fail */
	APDS9301_ERROR_OVERFLOW     = 3,	/**< ERROR MSG: ADC Overflow */
	APDS9301_UNKNOWN_ERROR      = 4,	/**< ERROR MSG: UNKNOWN ERROR*/
} APDS9301_ERROR_E;

typedef enum {
	APDS9301_LOW_GAIN,
	APDS9301_HIGH_GAIN
} APDS9301_gain;

typedef enum {
	APDS9301_INT_TIME_13_7_MS,
	APDS9301_INT_TIME_101_MS,
	APDS9301_INT_TIME_402_MS
} APDS9301_intTime;

typedef enum {
	APDS9301_INT_OFF,
	APDS9301_INT_ON
} APDS9301_interruptEnable;

typedef enum {
	APDS9301_POW_OFF,
	APDS9301_POW_ON
} APDS9301_powEnable;

typedef enum {
	APDS9301_INTSTATUS_NO,
	APDS9301_INTSTATUS_ON
} APDS9301_INTSTATUS;

typedef void (*APDS9301_SignalEvent_t) (APDS9301_INTSTATUS event);


  // powerEnable() enables/disables the power of the sensor. Normally
  //  this will be handled by the .begin() function, but it's possible
  //  a user may want to power the sensor off or on to save power
  //  outside of the normal begin()/end() methods.
APDS9301_ERROR_E hx_drv_apds9301_powerEnable(APDS9301_powEnable powEn);

APDS9301_ERROR_E hx_drv_apds9301_isPowerOn(int *ispwon);
  // set gain and integration time functions. By default the gain is
  //  set to low and integration time to its lowest setting; this is
  //  most suitable to high brightness environments. For lower
  //  brightness areas these probably ought to be turned up.
APDS9301_ERROR_E hx_drv_apds9301_setGain(APDS9301_gain gainLevel);
APDS9301_ERROR_E hx_drv_apds9301_setIntegrationTime(APDS9301_intTime integrationTime);

// Interrupt settings.
// Enable or disable interrupt.
APDS9301_ERROR_E hx_drv_apds9301_enableInterrupt(APDS9301_interruptEnable intMode);
APDS9301_ERROR_E hx_drv_apds9301_getInterruptReg(uint8_t *val);
// Clear the interrupt flag.
APDS9301_ERROR_E hx_drv_apds9301_clearIntFlag();

// Number of cycles outside of threshold range before interrupt is
//  asserted. 0 generates an interrupt on every ADC cycle, 1 will
//  generate an interrupt if the value of channel 0 (Vis + IR level)
//  is outside of the threshold region at all, 2-15 require that many
//  cycles out of the threshold region to trigger.
APDS9301_ERROR_E hx_drv_apds9301_setCyclesForInterrupt(uint8_t cycles);

// Thresholds for interrupt. Below low or above high will cause an
//  interrupt, depending on the interrupt cycles set by the prior
//  function.
APDS9301_ERROR_E hx_drv_apds9301_setLowThreshold(unsigned int threshold);
APDS9301_ERROR_E hx_drv_apds9301_setHighThreshold(unsigned int threshold);

// GET functions. Where applicable these return their typedef.

// getIDReg() returns the ID register value. Register will read
//  b0101xxxx where the lower four bits change with the silicon
//  revision of the chip.
APDS9301_ERROR_E hx_drv_apds9301_getIDReg(uint8_t *val);

// see above for more info about what these get functions do.
APDS9301_ERROR_E hx_drv_apds9301_getGain(APDS9301_gain *val);
APDS9301_ERROR_E hx_drv_apds9301_getIntegrationTime(APDS9301_intTime *val);
APDS9301_ERROR_E hx_drv_apds9301_getCyclesForInterrupt(uint8_t *val);
APDS9301_ERROR_E hx_drv_apds9301_getLowThreshold(unsigned int *val);
APDS9301_ERROR_E hx_drv_apds9301_getHighThreshold(unsigned int *val);

// Sensor read functions. These are the actual values the sensor
//  read at last conversion. Most often, this is going to be
//  ignored in favor of the calculated Lux level.
APDS9301_ERROR_E hx_drv_apds9301_readCH0Level(unsigned int *val);
APDS9301_ERROR_E hx_drv_apds9301_readCH1Level(unsigned int *val);

// Calculated Lux level. Accurate to within +/- 40%.
#ifdef APDS9301_SYSTEM_SUPPORT_FLOATING
APDS9301_ERROR_E hx_drv_apds9301_readLuxLevel(float *luxVal);
#else
APDS9301_ERROR_E hx_drv_apds9301_readLuxLevel_Integer(uint32_t *luxVal);
#endif

APDS9301_ERROR_E hx_drv_apds9301_getRegister(uint8_t regAddress, uint8_t *val);
APDS9301_ERROR_E hx_drv_apds9301_setRegister(uint8_t regAddress, uint8_t newVal);
APDS9301_ERROR_E hx_drv_apds9301_getTwoRegisters(uint8_t regAddress, uint16_t *val);
APDS9301_ERROR_E hx_drv_apds9301_setTwoRegisters(uint8_t regAddress, uint16_t newVal);

APDS9301_ERROR_E hx_drv_apds9301_register_cb(APDS9301_SignalEvent_t  cb_event);

#endif /* INC_HX_DRV_ALSAPDS9301_H_ */

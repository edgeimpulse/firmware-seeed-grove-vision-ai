/*
 * hx_drv_bme280.h
 *
 *  Created on: 2021/1/12
 *      Author: 904212
 */

#ifndef QWIIC_BEM280_HX_DRV_BEM280_H_
#define QWIIC_BEM280_HX_DRV_BEM280_H_

#include "board.h"
#include "hx_drv_iic_m.h"
#include "hx_drv_qwiic.h"

#define BME280_I2C_ADDRESS_0X77 0x77
#define BME280_I2C_ADDRESS_0X76 0x76

#define MODE_SLEEP 0b00
#define MODE_FORCED 0b01
#define MODE_NORMAL 0b11

//Register addresses
#define BME280_DIG_T1_LSB_REG 0x88
#define BME280_DIG_T1_MSB_REG 0x89
#define BME280_DIG_T2_LSB_REG 0x8A
#define BME280_DIG_T2_MSB_REG 0x8B
#define BME280_DIG_T3_LSB_REG 0x8C
#define BME280_DIG_T3_MSB_REG 0x8D
#define BME280_DIG_P1_LSB_REG 0x8E
#define BME280_DIG_P1_MSB_REG 0x8F
#define BME280_DIG_P2_LSB_REG 0x90
#define BME280_DIG_P2_MSB_REG 0x91
#define BME280_DIG_P3_LSB_REG 0x92
#define BME280_DIG_P3_MSB_REG 0x93
#define BME280_DIG_P4_LSB_REG 0x94
#define BME280_DIG_P4_MSB_REG 0x95
#define BME280_DIG_P5_LSB_REG 0x96
#define BME280_DIG_P5_MSB_REG 0x97
#define BME280_DIG_P6_LSB_REG 0x98
#define BME280_DIG_P6_MSB_REG 0x99
#define BME280_DIG_P7_LSB_REG 0x9A
#define BME280_DIG_P7_MSB_REG 0x9B
#define BME280_DIG_P8_LSB_REG 0x9C
#define BME280_DIG_P8_MSB_REG 0x9D
#define BME280_DIG_P9_LSB_REG 0x9E
#define BME280_DIG_P9_MSB_REG 0x9F
#define BME280_DIG_H1_REG 0xA1
#define BME280_CHIP_ID_REG 0xD0 //Chip ID
#define BME280_RST_REG 0xE0     //Softreset Reg
#define BME280_DIG_H2_LSB_REG 0xE1
#define BME280_DIG_H2_MSB_REG 0xE2
#define BME280_DIG_H3_REG 0xE3
#define BME280_DIG_H4_MSB_REG 0xE4
#define BME280_DIG_H4_LSB_REG 0xE5
#define BME280_DIG_H5_MSB_REG 0xE6
#define BME280_DIG_H6_REG 0xE7
#define BME280_CTRL_HUMIDITY_REG 0xF2    //Ctrl Humidity Reg
#define BME280_STAT_REG 0xF3             //Status Reg
#define BME280_CTRL_MEAS_REG 0xF4        //Ctrl Measure Reg
#define BME280_CONFIG_REG 0xF5           //Configuration Reg
#define BME280_MEASUREMENTS_REG 0xF7     //Measurements register start
#define BME280_PRESSURE_MSB_REG 0xF7     //Pressure MSB
#define BME280_PRESSURE_LSB_REG 0xF8     //Pressure LSB
#define BME280_PRESSURE_XLSB_REG 0xF9    //Pressure XLSB
#define BME280_TEMPERATURE_MSB_REG 0xFA  //Temperature MSB
#define BME280_TEMPERATURE_LSB_REG 0xFB  //Temperature LSB
#define BME280_TEMPERATURE_XLSB_REG 0xFC //Temperature XLSB
#define BME280_HUMIDITY_MSB_REG 0xFD     //Humidity MSB
#define BME280_HUMIDITY_LSB_REG 0xFE     //Humidity LSB

struct BME280_SensorCalibration
{
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;

    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;

    uint8_t dig_H1;
    int16_t dig_H2;
    uint8_t dig_H3;
    int16_t dig_H4;
    int16_t dig_H5;
    int8_t dig_H6;
};

uint8_t hx_drv_bme280_readRegister(uint8_t offset);

HX_DRV_QWIIC_ERROR_E hx_drv_bme280_initial(uint8_t);
HX_DRV_QWIIC_ERROR_E hx_drv_bme280_setMode(int8_t);
HX_DRV_QWIIC_ERROR_E hx_drv_bme280_receive_TempC(float *data);
HX_DRV_QWIIC_ERROR_E hx_drv_bme280_receive_FloatPressure(float *data);
HX_DRV_QWIIC_ERROR_E hx_drv_bme280_receive_IntPressure(uint32_t *data);
HX_DRV_QWIIC_ERROR_E hx_drv_bme280_receive_FloatHumidity(float *data);

#endif /* QWIIC_BEM280_HX_DRV_BEM280_H_ */

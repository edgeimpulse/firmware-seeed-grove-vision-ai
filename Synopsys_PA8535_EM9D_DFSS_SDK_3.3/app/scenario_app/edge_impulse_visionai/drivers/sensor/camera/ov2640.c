#include "ov2640.h"
#include "error_code.h"
#include "hx_drv_CIS_common.h"
#include "logger.h"

const HX_CIS_SensorSetting_t sensor_ov2640_setting[] = {
	{HX_CIS_I2C_Action_W, BANK_SEL, BANK_DSP},
	{HX_CIS_I2C_Action_W, 0x2c, 0xff},
	{HX_CIS_I2C_Action_W, 0x2e, 0xdf},
	{HX_CIS_I2C_Action_W, BANK_SEL, BANK_SENSOR},
	{HX_CIS_I2C_Action_W, 0x3c, 0x32},
	{HX_CIS_I2C_Action_W, CLKRC, 0x01},
	{HX_CIS_I2C_Action_W, COM2, COM2_OUT_DRIVE_3x},
	{HX_CIS_I2C_Action_W, REG04, REG04_DEFAULT},
	{HX_CIS_I2C_Action_W, COM8, COM8_DEFAULT | COM8_BNDF_EN | COM8_AGC_EN | COM8_AEC_EN},
	{HX_CIS_I2C_Action_W, COM9, COM9_AGC_SET(COM9_AGC_GAIN_8x)},
	{HX_CIS_I2C_Action_W, 0x2c, 0x0c},
	{HX_CIS_I2C_Action_W, 0x33, 0x78},
	{HX_CIS_I2C_Action_W, 0x3a, 0x33},
	{HX_CIS_I2C_Action_W, 0x3b, 0xfB},
	{HX_CIS_I2C_Action_W, 0x3e, 0x00},
	{HX_CIS_I2C_Action_W, 0x43, 0x11},
	{HX_CIS_I2C_Action_W, 0x16, 0x10},
	{HX_CIS_I2C_Action_W, 0x39, 0x92},
	{HX_CIS_I2C_Action_W, 0x35, 0xda},
	{HX_CIS_I2C_Action_W, 0x22, 0x1a},
	{HX_CIS_I2C_Action_W, 0x37, 0xc3},
	{HX_CIS_I2C_Action_W, 0x23, 0x00},
	{HX_CIS_I2C_Action_W, ARCOM2, 0xc0},
	{HX_CIS_I2C_Action_W, 0x06, 0x88},
	{HX_CIS_I2C_Action_W, 0x07, 0xc0},
	{HX_CIS_I2C_Action_W, COM4, 0x87},
	{HX_CIS_I2C_Action_W, 0x0e, 0x41},
	{HX_CIS_I2C_Action_W, 0x4c, 0x00},
	{HX_CIS_I2C_Action_W, 0x4a, 0x81},
	{HX_CIS_I2C_Action_W, 0x21, 0x99},
	{HX_CIS_I2C_Action_W, AEW, 0x40},
	{HX_CIS_I2C_Action_W, AEB, 0x38},
	{HX_CIS_I2C_Action_W, VV, VV_AGC_TH_SET(8, 2)},
	{HX_CIS_I2C_Action_W, 0x5c, 0x00},
	{HX_CIS_I2C_Action_W, 0x63, 0x00},
	{HX_CIS_I2C_Action_W, HISTO_LOW, 0x70},
	{HX_CIS_I2C_Action_W, HISTO_HIGH, 0x80},
	{HX_CIS_I2C_Action_W, 0x7c, 0x05},
	{HX_CIS_I2C_Action_W, 0x20, 0x80},
	{HX_CIS_I2C_Action_W, 0x28, 0x30},
	{HX_CIS_I2C_Action_W, 0x6c, 0x00},
	{HX_CIS_I2C_Action_W, 0x6d, 0x80},
	{HX_CIS_I2C_Action_W, 0x6e, 0x00},
	{HX_CIS_I2C_Action_W, 0x70, 0x02},
	{HX_CIS_I2C_Action_W, 0x71, 0x94},
	{HX_CIS_I2C_Action_W, 0x73, 0xc1},
	{HX_CIS_I2C_Action_W, 0x3d, 0x34},
	{HX_CIS_I2C_Action_W, 0x5a, 0x18},
	{HX_CIS_I2C_Action_W, BD50, 0xbb},
	{HX_CIS_I2C_Action_W, BD60, 0x9c},
	{HX_CIS_I2C_Action_W, COM7, COM7_RES_CIF},
	{HX_CIS_I2C_Action_W, HSTART, 0x11},
	{HX_CIS_I2C_Action_W, HSTOP, 0x43},
	{HX_CIS_I2C_Action_W, VSTART, 0x00},
	{HX_CIS_I2C_Action_W, VSTOP, 0x25},
	{HX_CIS_I2C_Action_W, REG32, 0x89},
	{HX_CIS_I2C_Action_W, 0x37, 0xc0},
	{HX_CIS_I2C_Action_W, BD50, 0xca},
	{HX_CIS_I2C_Action_W, BD60, 0xa8},
	{HX_CIS_I2C_Action_W, 0x6d, 0x00},
	{HX_CIS_I2C_Action_W, 0x3d, 0x38},
	{HX_CIS_I2C_Action_W, BANK_SEL, BANK_DSP},
	{HX_CIS_I2C_Action_W, 0xe5, 0x7f},
	{HX_CIS_I2C_Action_W, MC_BIST, MC_BIST_RESET | MC_BIST_BOOT_ROM_SEL},
	{HX_CIS_I2C_Action_W, 0x41, 0x24},
	{HX_CIS_I2C_Action_W, RESET, RESET_JPEG | RESET_DVP},
	{HX_CIS_I2C_Action_W, 0x76, 0xff},
	{HX_CIS_I2C_Action_W, 0x33, 0xa0},
	{HX_CIS_I2C_Action_W, 0x42, 0x20},
	{HX_CIS_I2C_Action_W, 0x43, 0x18},
	{HX_CIS_I2C_Action_W, 0x4c, 0x00},
	{HX_CIS_I2C_Action_W, CTRL3, CTRL3_WPC_EN | 0x10},
	{HX_CIS_I2C_Action_W, 0x88, 0x3f},
	{HX_CIS_I2C_Action_W, 0xd7, 0x03},
	{HX_CIS_I2C_Action_W, 0xd9, 0x10},
	{HX_CIS_I2C_Action_W, R_DVP_SP, R_DVP_SP_AUTO_MODE | 0x02},
	{HX_CIS_I2C_Action_W, 0xc8, 0x08},
	{HX_CIS_I2C_Action_W, 0xc9, 0x80},
	{HX_CIS_I2C_Action_W, BPADDR, 0x00},
	{HX_CIS_I2C_Action_W, BPDATA, 0x00},
	{HX_CIS_I2C_Action_W, BPADDR, 0x03},
	{HX_CIS_I2C_Action_W, BPDATA, 0x48},
	{HX_CIS_I2C_Action_W, BPDATA, 0x48},
	{HX_CIS_I2C_Action_W, BPADDR, 0x08},
	{HX_CIS_I2C_Action_W, BPDATA, 0x20},
	{HX_CIS_I2C_Action_W, BPDATA, 0x10},
	{HX_CIS_I2C_Action_W, BPDATA, 0x0e},
	{HX_CIS_I2C_Action_W, 0x90, 0x00},
	{HX_CIS_I2C_Action_W, 0x91, 0x0e},
	{HX_CIS_I2C_Action_W, 0x91, 0x1a},
	{HX_CIS_I2C_Action_W, 0x91, 0x31},
	{HX_CIS_I2C_Action_W, 0x91, 0x5a},
	{HX_CIS_I2C_Action_W, 0x91, 0x69},
	{HX_CIS_I2C_Action_W, 0x91, 0x75},
	{HX_CIS_I2C_Action_W, 0x91, 0x7e},
	{HX_CIS_I2C_Action_W, 0x91, 0x88},
	{HX_CIS_I2C_Action_W, 0x91, 0x8f},
	{HX_CIS_I2C_Action_W, 0x91, 0x96},
	{HX_CIS_I2C_Action_W, 0x91, 0xa3},
	{HX_CIS_I2C_Action_W, 0x91, 0xaf},
	{HX_CIS_I2C_Action_W, 0x91, 0xc4},
	{HX_CIS_I2C_Action_W, 0x91, 0xd7},
	{HX_CIS_I2C_Action_W, 0x91, 0xe8},
	{HX_CIS_I2C_Action_W, 0x91, 0x20},
	{HX_CIS_I2C_Action_W, 0x92, 0x00},
	{HX_CIS_I2C_Action_W, 0x93, 0x06},
	{HX_CIS_I2C_Action_W, 0x93, 0xe3},
	{HX_CIS_I2C_Action_W, 0x93, 0x05},
	{HX_CIS_I2C_Action_W, 0x93, 0x05},
	{HX_CIS_I2C_Action_W, 0x93, 0x00},
	{HX_CIS_I2C_Action_W, 0x93, 0x04},
	{HX_CIS_I2C_Action_W, 0x93, 0x00},
	{HX_CIS_I2C_Action_W, 0x93, 0x00},
	{HX_CIS_I2C_Action_W, 0x93, 0x00},
	{HX_CIS_I2C_Action_W, 0x93, 0x00},
	{HX_CIS_I2C_Action_W, 0x93, 0x00},
	{HX_CIS_I2C_Action_W, 0x93, 0x00},
	{HX_CIS_I2C_Action_W, 0x93, 0x00},
	{HX_CIS_I2C_Action_W, 0x96, 0x00},
	{HX_CIS_I2C_Action_W, 0x97, 0x08},
	{HX_CIS_I2C_Action_W, 0x97, 0x19},
	{HX_CIS_I2C_Action_W, 0x97, 0x02},
	{HX_CIS_I2C_Action_W, 0x97, 0x0c},
	{HX_CIS_I2C_Action_W, 0x97, 0x24},
	{HX_CIS_I2C_Action_W, 0x97, 0x30},
	{HX_CIS_I2C_Action_W, 0x97, 0x28},
	{HX_CIS_I2C_Action_W, 0x97, 0x26},
	{HX_CIS_I2C_Action_W, 0x97, 0x02},
	{HX_CIS_I2C_Action_W, 0x97, 0x98},
	{HX_CIS_I2C_Action_W, 0x97, 0x80},
	{HX_CIS_I2C_Action_W, 0x97, 0x00},
	{HX_CIS_I2C_Action_W, 0x97, 0x00},
	{HX_CIS_I2C_Action_W, 0xa4, 0x00},
	{HX_CIS_I2C_Action_W, 0xa8, 0x00},
	{HX_CIS_I2C_Action_W, 0xc5, 0x11},
	{HX_CIS_I2C_Action_W, 0xc6, 0x51},
	{HX_CIS_I2C_Action_W, 0xbf, 0x80},
	{HX_CIS_I2C_Action_W, 0xc7, 0x10},
	{HX_CIS_I2C_Action_W, 0xb6, 0x66},
	{HX_CIS_I2C_Action_W, 0xb8, 0xA5},
	{HX_CIS_I2C_Action_W, 0xb7, 0x64},
	{HX_CIS_I2C_Action_W, 0xb9, 0x7C},
	{HX_CIS_I2C_Action_W, 0xb3, 0xaf},
	{HX_CIS_I2C_Action_W, 0xb4, 0x97},
	{HX_CIS_I2C_Action_W, 0xb5, 0xFF},
	{HX_CIS_I2C_Action_W, 0xb0, 0xC5},
	{HX_CIS_I2C_Action_W, 0xb1, 0x94},
	{HX_CIS_I2C_Action_W, 0xb2, 0x0f},
	{HX_CIS_I2C_Action_W, 0xc4, 0x5c},
	{HX_CIS_I2C_Action_W, CTRL1, 0xfd},
	{HX_CIS_I2C_Action_W, 0x7f, 0x00},
	{HX_CIS_I2C_Action_W, 0xe5, 0x1f},
	{HX_CIS_I2C_Action_W, 0xe1, 0x67},
	{HX_CIS_I2C_Action_W, 0xdd, 0x7f},
	{HX_CIS_I2C_Action_W, IMAGE_MODE, 0x00},
	{HX_CIS_I2C_Action_W, RESET, 0x00},
	{HX_CIS_I2C_Action_W, R_BYPASS, R_BYPASS_DSP_EN},
	{HX_CIS_I2C_Action_W, 0, 0},

	// RAW10
	{HX_CIS_I2C_Action_W, BANK_SEL, BANK_DSP},
	{HX_CIS_I2C_Action_W, RESET, RESET_DVP},
	{HX_CIS_I2C_Action_W, IMAGE_MODE, IMAGE_MODE_RAW10},
	{HX_CIS_I2C_Action_W, 0xD7, 0x03},
	{HX_CIS_I2C_Action_W, 0xE1, 0x77},
	{HX_CIS_I2C_Action_W, RESET, 0x00},
	{HX_CIS_I2C_Action_W, 0, 0},
};
const HX_CIS_SensorSetting_t sensor_ov2640_uxga_setting[] = {
	// UXGA
	{HX_CIS_I2C_Action_W, BANK_SEL, BANK_SENSOR},
	{HX_CIS_I2C_Action_W, COM7, COM7_RES_UXGA},

	// Set the sensor output window
	{HX_CIS_I2C_Action_W, COM1, 0x0F},
	{HX_CIS_I2C_Action_W, REG32, REG32_UXGA},
	{HX_CIS_I2C_Action_W, HSTART, 0x11},
	{HX_CIS_I2C_Action_W, HSTOP, 0x75},
	{HX_CIS_I2C_Action_W, VSTART, 0x01},
	{HX_CIS_I2C_Action_W, VSTOP, 0x97},

	//{HX_CIS_I2C_Action_W,CLKRC, 0x00},
	{HX_CIS_I2C_Action_W, 0x3d, 0x34},
	{HX_CIS_I2C_Action_W, BD50, 0xbb},
	{HX_CIS_I2C_Action_W, BD60, 0x9c},
	{HX_CIS_I2C_Action_W, 0x5a, 0x18},
	{HX_CIS_I2C_Action_W, 0x6d, 0x80},
	{HX_CIS_I2C_Action_W, 0x39, 0x82},
	{HX_CIS_I2C_Action_W, 0x23, 0x00},
	{HX_CIS_I2C_Action_W, 0x07, 0xc0},
	{HX_CIS_I2C_Action_W, 0x4c, 0x00},
	{HX_CIS_I2C_Action_W, 0x35, 0x88},
	{HX_CIS_I2C_Action_W, 0x22, 0x0a},
	{HX_CIS_I2C_Action_W, 0x37, 0x40},
	{HX_CIS_I2C_Action_W, ARCOM2, 0xa0},
	{HX_CIS_I2C_Action_W, 0x06, 0x02},
	{HX_CIS_I2C_Action_W, COM4, 0xb7},
	{HX_CIS_I2C_Action_W, 0x0e, 0x01},
	{HX_CIS_I2C_Action_W, 0x42, 0x83},
	{HX_CIS_I2C_Action_W, BANK_SEL, BANK_DSP},
	{HX_CIS_I2C_Action_W, RESET, RESET_DVP},

	// Set the sensor resolution (UXGA, SVGA, CIF)
	{HX_CIS_I2C_Action_W, HSIZE8, 0xc8},
	{HX_CIS_I2C_Action_W, VSIZE8, 0x96},
	{HX_CIS_I2C_Action_W, SIZEL, 0x00},

	// Set the image window size >= output size
	{HX_CIS_I2C_Action_W, HSIZE, 0x90},
	{HX_CIS_I2C_Action_W, VSIZE, 0x2c},
	{HX_CIS_I2C_Action_W, XOFFL, 0x00},
	{HX_CIS_I2C_Action_W, YOFFL, 0x00},
	{HX_CIS_I2C_Action_W, VHYX, 0x88},
	{HX_CIS_I2C_Action_W, TEST, 0x00},

	{HX_CIS_I2C_Action_W, CTRL2, CTRL2_DCW_EN | 0x1d},
	{HX_CIS_I2C_Action_W, CTRLI, 0x00},
	//{HX_CIS_I2C_Action_W,R_DVP_SP, 0x06},
	{HX_CIS_I2C_Action_W, 0, 0},

};

const HX_CIS_SensorSetting_t sensor_ov2640_cif_setting[] = {

	// CIF
	{HX_CIS_I2C_Action_W, BANK_SEL, BANK_SENSOR},
	{HX_CIS_I2C_Action_W, COM7, COM7_RES_CIF},

	// Set the sensor output window
	{HX_CIS_I2C_Action_W, COM1, 0x0A},
	{HX_CIS_I2C_Action_W, REG32, REG32_CIF},
	{HX_CIS_I2C_Action_W, HSTART, 0x11},
	{HX_CIS_I2C_Action_W, HSTOP, 0x43},
	{HX_CIS_I2C_Action_W, VSTART, 0x00},
	{HX_CIS_I2C_Action_W, VSTOP, 0x25},

	//{HX_CIS_I2C_Action_W,CLKRC, 0x00},
	{HX_CIS_I2C_Action_W, BD50, 0xca},
	{HX_CIS_I2C_Action_W, BD60, 0xa8},
	{HX_CIS_I2C_Action_W, 0x5a, 0x18},
	{HX_CIS_I2C_Action_W, 0x6d, 0x00},
	{HX_CIS_I2C_Action_W, 0x3d, 0x38},
	{HX_CIS_I2C_Action_W, 0x39, 0x92},
	{HX_CIS_I2C_Action_W, 0x35, 0xda},
	{HX_CIS_I2C_Action_W, 0x22, 0x1a},
	{HX_CIS_I2C_Action_W, 0x37, 0xc3},
	{HX_CIS_I2C_Action_W, 0x23, 0x00},
	{HX_CIS_I2C_Action_W, ARCOM2, 0xc0},
	{HX_CIS_I2C_Action_W, 0x06, 0x88},
	{HX_CIS_I2C_Action_W, 0x07, 0xc0},
	{HX_CIS_I2C_Action_W, COM4, 0x87},
	{HX_CIS_I2C_Action_W, 0x0e, 0x41},
	{HX_CIS_I2C_Action_W, 0x4c, 0x00},
	{HX_CIS_I2C_Action_W, BANK_SEL, BANK_DSP},
	{HX_CIS_I2C_Action_W, RESET, RESET_DVP},

	// Set the sensor resolution (UXGA, SVGA, CIF)
	{HX_CIS_I2C_Action_W, HSIZE8, 0x32},
	{HX_CIS_I2C_Action_W, VSIZE8, 0x25},
	{HX_CIS_I2C_Action_W, SIZEL, 0x00},

	// Set the image window size >= output size
	{HX_CIS_I2C_Action_W, HSIZE, 0x64},
	{HX_CIS_I2C_Action_W, VSIZE, 0x4a},
	{HX_CIS_I2C_Action_W, XOFFL, 0x00},
	{HX_CIS_I2C_Action_W, YOFFL, 0x00},
	{HX_CIS_I2C_Action_W, VHYX, 0x00},
	{HX_CIS_I2C_Action_W, TEST, 0x00},

	{HX_CIS_I2C_Action_W, CTRL2, CTRL2_DCW_EN | 0x1D},
	{HX_CIS_I2C_Action_W, CTRLI, CTRLI_LP_DP | 0x00},
	//{HX_CIS_I2C_Action_W,R_DVP_SP, 0x08},
	{HX_CIS_I2C_Action_W, 0, 0}

};

const HX_CIS_SensorSetting_t sensor_ov2640_svga_setting[] = {

	// SVGA
	{HX_CIS_I2C_Action_W, BANK_SEL, BANK_SENSOR},
	{HX_CIS_I2C_Action_W, COM7, COM7_RES_SVGA},

	// Set the sensor output window
	{HX_CIS_I2C_Action_W, COM1, 0x0A},
	{HX_CIS_I2C_Action_W, REG32, REG32_SVGA},
	{HX_CIS_I2C_Action_W, HSTART, 0x11},
	{HX_CIS_I2C_Action_W, HSTOP, 0x43},
	{HX_CIS_I2C_Action_W, VSTART, 0x00},
	{HX_CIS_I2C_Action_W, VSTOP, 0x4b},

	//{HX_CIS_I2C_Action_W,CLKRC, 0x00},
	{HX_CIS_I2C_Action_W, 0x37, 0xc0},
	{HX_CIS_I2C_Action_W, BD50, 0xca},
	{HX_CIS_I2C_Action_W, BD60, 0xa8},
	{HX_CIS_I2C_Action_W, 0x5a, 0x23},
	{HX_CIS_I2C_Action_W, 0x6d, 0x00},
	{HX_CIS_I2C_Action_W, 0x3d, 0x38},
	{HX_CIS_I2C_Action_W, 0x39, 0x92},
	{HX_CIS_I2C_Action_W, 0x35, 0xda},
	{HX_CIS_I2C_Action_W, 0x22, 0x1a},
	{HX_CIS_I2C_Action_W, 0x37, 0xc3},
	{HX_CIS_I2C_Action_W, 0x23, 0x00},
	{HX_CIS_I2C_Action_W, ARCOM2, 0xc0},
	{HX_CIS_I2C_Action_W, 0x06, 0x88},
	{HX_CIS_I2C_Action_W, 0x07, 0xc0},
	{HX_CIS_I2C_Action_W, COM4, 0x87},
	{HX_CIS_I2C_Action_W, 0x0e, 0x41},
	{HX_CIS_I2C_Action_W, 0x42, 0x03},
	{HX_CIS_I2C_Action_W, 0x4c, 0x00},
	{HX_CIS_I2C_Action_W, BANK_SEL, BANK_DSP},
	{HX_CIS_I2C_Action_W, RESET, RESET_DVP},

	// Set the sensor resolution (UXGA, SVGA, CIF)
	{HX_CIS_I2C_Action_W, HSIZE8, 0x64},
	{HX_CIS_I2C_Action_W, VSIZE8, 0x4B},
	{HX_CIS_I2C_Action_W, SIZEL, 0x00},

	// Set the image window size >= output size
	{HX_CIS_I2C_Action_W, HSIZE, 0xC8},
	{HX_CIS_I2C_Action_W, VSIZE, 0x96},
	{HX_CIS_I2C_Action_W, XOFFL, 0x00},
	{HX_CIS_I2C_Action_W, YOFFL, 0x00},
	{HX_CIS_I2C_Action_W, VHYX, 0x00},
	{HX_CIS_I2C_Action_W, TEST, 0x00},

	{HX_CIS_I2C_Action_W, CTRL2, CTRL2_DCW_EN | 0x1D},
	{HX_CIS_I2C_Action_W, CTRLI, CTRLI_LP_DP | 0x00},
	//{HX_CIS_I2C_Action_W,R_DVP_SP, 0x08},
	{HX_CIS_I2C_Action_W, 0, 0}

};

static void ov2640_power_init(void)
{
#ifdef CAMERA_ENABLE_PIN
	hx_drv_iomux_set_pmux(OV2640_EN_GPIO, 3);
	hx_drv_iomux_set_outvalue(OV2640_EN_GPIO, OV2640_EN_STATE);
	board_delay_ms(1);
#endif
	return;
}

static void ov2640_power_off(void)
{
#ifdef CAMERA_ENABLE_PIN
	hx_drv_iomux_set_pmux(OV2640_EN_GPIO, 3);
	hx_drv_iomux_set_outvalue(OV2640_EN_GPIO, 1 - OV2640_EN_STATE);
#endif
	return;
}

static int8_t ov2640_get_sensor_id(uint32_t *sensor_id)
{
	uint8_t reg_addr = 0xff;
	uint8_t reg_value = 0x01;

	hx_drv_i2cm_write_data(SS_IIC_2_ID, OV2640_I2C_ADDR, &reg_addr, 1, &reg_value, 1);

	reg_addr = 0x0a;
	if (hx_drv_cis_get_reg(reg_addr, &reg_value) != HX_CIS_NO_ERROR)
	{
		LOGGER_WARNING("<%s><%d>get sensor id failed\n", __func__, __LINE__);
		return -EIO;
	}
	*sensor_id = reg_value << 8;

	reg_addr = 0x0b;
	if (hx_drv_cis_get_reg(reg_addr, &reg_value) != HX_CIS_NO_ERROR)
	{
		LOGGER_WARNING("<%s><%d>get sensor id failed\n", __func__, __LINE__);
		return -EIO;
	}
	*sensor_id = *sensor_id | reg_value;

	return 0;
}

static int8_t ov2640_set_output_size(uint16_t width, uint16_t height)
{
	uint16_t outw, outh, startx, starty;
	uint8_t temp;
	if (width % 4 || height % 4)
	{
		LOGGER_WARNING("camera size param error\n");
		return -EINVAL;
	}
	if (width > OV2640_MAX_WIDTH || height > OV2640_MAX_HEIGHT)
	{
		LOGGER_WARNING("camera size overflow error\n");
		return -EINVAL;
	}

	// if (width <= 64 && height <= 64)
	// {
	// 	// CIF
	// 	outh = 64;
	// 	outw = 64;

	// 	LOGGER_INFO("CIF: width = %d, height = %d, outw = %d, outh = %d\n", width, height, outw, outh);
	// 	hx_drv_cis_setRegTable(sensor_ov2640_cif_setting, sizeof(sensor_ov2640_cif_setting) / sizeof(sensor_ov2640_cif_setting[0]));
	// }else if (width <= 160 && height <= 123){
	// 	// CIF
	// 	outh = 120;
	// 	outw = 160;

	// 	LOGGER_INFO("CIF: width = %d, height = %d, outw = %d, outh = %d\n", width, height, outw, outh);
	// 	hx_drv_cis_setRegTable(sensor_ov2640_cif_setting, sizeof(sensor_ov2640_cif_setting) / sizeof(sensor_ov2640_cif_setting[0]));
	// }
	// else
	if (width <= 320 && height <= 240)
	{
		// CIF
		outh = 240;
		outw = 320;

		//LOGGER_INFO("CIF: width = %d, height = %d, outw = %d, outh = %d\n", width, height, outw, outh);
		hx_drv_cis_setRegTable(sensor_ov2640_cif_setting, sizeof(sensor_ov2640_cif_setting) / sizeof(sensor_ov2640_cif_setting[0]));
	}
	else if (width <= 640 && height <= 480)
	{
		// SVGA
		outh = 480;
		outw = 640;
		//LOGGER_INFO("SVGA: width = %d, height = %d, outw = %d, outh = %d\n", width, height, outw, outh);
		hx_drv_cis_setRegTable(sensor_ov2640_svga_setting, sizeof(sensor_ov2640_svga_setting) / sizeof(sensor_ov2640_svga_setting[0]));
		/* code */
	}
	else
	{
		// UXGA
		outh = height;
		outw = width;
		//LOGGER_INFO("UXGA: width = %d, height = %d, outw = %d, outh = %d\n", width, height, outw, outh);
		hx_drv_cis_setRegTable(sensor_ov2640_uxga_setting, sizeof(sensor_ov2640_uxga_setting) / sizeof(sensor_ov2640_uxga_setting[0]));
	}

	startx = (outw - width) / 2;
	starty = (outh - height) / 2;

	datapath_set_roi_start_position(startx, starty);

	outw /= 4;
	outh /= 4;

	hx_drv_cis_set_reg(0xff, 0x00, 1);
	hx_drv_cis_set_reg(0xe0, 0x04, 1);
	hx_drv_cis_set_reg(0x50, 0x00, 1);
	hx_drv_cis_set_reg(0x5a, outw & 0xff, 1);
	hx_drv_cis_set_reg(0x5b, outh & 0xff, 1);
	temp = (outw >> 8) & 0x03;
	temp |= (outh >> 6) & 0x04;
	hx_drv_cis_set_reg(0x5c, temp, 1);
	hx_drv_cis_set_reg(0xe0, 0X00, 1);

	return 0;
}

Camera_Hal_Struct ov2640_driver = {
	.power_init = ov2640_power_init,
	.power_off = ov2640_power_off,
	.get_sensor_id = ov2640_get_sensor_id,
	.camera_sensor_addr = OV2640_I2C_ADDR,
	.sensor_cfg = sensor_ov2640_setting,
	.sensor_cfg_len = HX_CIS_SIZE_N(sensor_ov2640_setting,
									HX_CIS_SensorSetting_t),
	.xshutdown_pin = CIS_XHSUTDOWN_IOMUX_NONE,
	.xsleep_ctl = SENSORCTRL_XSLEEP_BY_CPU,
	.set_output_size = ov2640_set_output_size,
};

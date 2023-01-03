/*
 * spi_protocol.h
 *
 *  Created on: 2020¦~5¤ë7¤é
 *      Author: 902449
 */

#ifndef INC_SPI_PROTOCOL_H_
#define INC_SPI_PROTOCOL_H_

typedef enum
{
	DATA_TYPE_NONE              = 0x00,
	DATA_TYPE_JPG               = 0x01,
	DATA_TYPE_BMP               = 0x02,
	DATA_TYPE_VO_CMD            = 0x03,
	DATA_TYPE_HUNN_PRESENT      = 0x04,
	DATA_TYPE_WKUP_METHOD       = 0x05,
	DATA_TYPE_HUMN_LV_TIMEOUT   = 0x06,
	DATA_TYPE_LANGUAGE          = 0x07,
#ifdef TV01
	DATA_TYPE_HUNN_LOCK_COUNT   = 0x08,
	DATA_TYPE_EYE_PROT_TIMEOUT  = 0x09,
#endif
    DATA_TYPE_VOICE_TIMEOUT     = 0x0A,
	DATA_TYPE_DBG_MSG           = 0x10,
	DATA_TYPE_WARN_MSG          = 0x11,
	DATA_TYPE_CTRL_MSG          = 0x12,
	DATA_TYPE_META_DATA         = 0x13,
	DATA_TYPE_JPG_L             = 0x14,
	DATA_TYPE_JPG_R             = 0x15,
	DATA_TYPE_RAW_IMG           = 0x16,
	DATA_TYPE_BIN_DATA          = 0x20,
	DATA_TYPE_INCORRECT_DATA    = 0x3F,
    DATA_TYPE_TV_STANDBY        = 0x40,

	DATA_TYPE_AREA_SUMMARY      = 0x5A,
	DATA_TYPE_AREA_DETAIL       = 0x5C,

	DATA_TYPE_QRCODE_RESULT     = 0x60,
	DATA_TYPE_WR_CONFIG         = 0x61,
	DATA_TYPE_SENSOR_REG    = 0x62,

	DATA_TYPE_PDM				= 0x90,
	DATA_TYPE_ALANGO			= 0x91,

}SPI_CMD_DATA_TYPE;

#endif /* INC_SPI_PROTOCOL_H_ */

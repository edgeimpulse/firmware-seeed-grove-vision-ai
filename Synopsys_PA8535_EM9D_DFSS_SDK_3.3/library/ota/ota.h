/**
 ********************************************************************************************
 *  @file      ota.h
 *  @details   This file contains all OTA related function
 *  @author    himax/903870
 *  @version   V1.0.0
 *  @date      25-July-2019
 *  @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 *******************************************************************************************/
#ifndef LIBRARY_OTA_H_
#define LIBRARY_OTA_H_

#include "hx_drv_basic_def.h"

/****************************************************
 * Constant Definition                              *
 ***************************************************/
//SEC
#define TRNG_SAMPLECYCLES_1M 11
#define system_mem	0x20000000
#define SYSTEM_DATA_LEN	(46*32*1024) //46*32K bytes


//memory layout in flash
#define WEI_2ND_BOOTLOAD_SIZE		0x10000 //65536 bytes, 64KB
#define WEI_1ST_BOOTLOAD_SIZE		0x10000 //65536 bytes, 64KB
#define WE1_MEMORY_DSP_SIZE			0x1000  //4096 byte, 4KB
#define WEI_BOOTLOAD_PATCH_SIZE		0x10000 //boot patch,only for Ver.A

#define WEI_2ND_BOOTLOAD_OFFSET		0x0
#define WEI_1ST_BOOTLOAD_OFFSET		(WEI_2ND_BOOTLOAD_OFFSET+ WEI_2ND_BOOTLOAD_SIZE)
#define WEI_MEMORY_DSP_OFFSET		(WEI_1ST_BOOTLOAD_OFFSET + WEI_1ST_BOOTLOAD_SIZE)
#define WEI_BOOTLOAD_PATCH_OFFSET	(WEI_MEMORY_DSP_OFFSET + WE1_MEMORY_DSP_SIZE) //boot patch,only for Ver.A

/* memory location */
#define WEI_SEC_LIB_DATA_SIZE		0x400
#define WEI_SEC_INFO_DATA_SIZE		0x400
#define WEI_SEC_DATA_SIZE			(WEI_SEC_LIB_DATA_SIZE + WEI_SEC_INFO_DATA_SIZE)// 1KB for sec lib, 1KB for sec info
#define WEI_ICCM1_BASE				(0x10000000)
#define WEI_SYSMEM_BASE				(0x20000000)
#define SYSMEM_TEMP_USE_OFFSET		0x50000
#define WEI_1ST_BOOTLOAD_BASE		WEI_SYSMEM_BASE
#define WEI_SEC_LIB_DATA_BASE		(WEI_1ST_BOOTLOAD_BASE + WEI_1ST_BOOTLOAD_SIZE)
#define WEI_SEC_INFO_DATA_BASE		(WEI_SEC_LIB_DATA_BASE + WEI_SEC_LIB_DATA_SIZE)
#define WEI_2ND_BOOTLOAD_BASE		(WEI_SEC_INFO_DATA_BASE + WEI_SEC_DATA_SIZE)


#define BASE_ADDR_FLASH 		(0x28000000)
#define BASE_ADDR_SPI_EXT		(0x30000000)

//Copy from BL Com_flash_boot.h
#define SB_HEADER_VERSION_NUM			0x01
#define SB_HEADER_PID					6

#define SB_HEADER_SECT_MAX				32
#define SB_HEADER_CRC_OFFSET			4
#define HW_PMU_CHIP_VER_ADDR				0xB00000FC
#define SYS_RST_CPU_PIN						14

#define INDICATION_FLAG_OFFSET		8
#define INDICATION_FLAG_SIZE		2
#define PMU_VERSION_WIDTH						24
#define PMU_VERSION_OFFSET						8

#define CHIP_VER_A	0x8535A0
#define CHIP_VER_B	0x8535A1

#define INDICATION_OTA				BIT_0
#define INDICATION_STR				BIT_1
#define INDICATION_XIP_BY_EIP		BIT_2



/****************************************************
 * ENUM Declaration                                 *
 ***************************************************/
typedef enum
{
	OTA_NO_ERROR						 = 0,	/**< No ERROR */
	OTA_ERROR_SEC_INIT						,
	OTA_ERROR_SEC_TRNG						,
	OTA_ERROR_CHECKSUM						,
	OTA_ERROR_I2C_DRV						,
	OTA_ERROR_SEC_VERIFY_ERROR				,
	OTA_ERROR_FLASH_CRC_CHECK_FAIL			,
	OTA_ERROR_UNKNOWN							
} OTA_ERROR_E;


typedef enum
{
	OTA_STATUS_APPLICATION_IDLE 			= 0 ,
	OTA_STATUS_OTA_LOADER_IDLE					,
	OTA_STATUS_OTA_EIP130_INIT					,	
	OTA_STATUS_OTA_DATA_VERIFY					,		
	OTA_STATUS_OTA_FLASH_CHECK					,	
	OTA_STATUS_OTA_DONE 											
} OTA_STATUS_E;




typedef enum
{
	OTA_ALL						=0x51,
	OTA_MEMDSP							=0x52,
	OTA_APPLICATION						=0x53,
	OTA_APP_CONFIG						=0x54,
	OTA_EZMA_CONFIG						=0x55,
	OTA_CNNLUT							=0x56,

}OTA_TYPE_E;

typedef enum WEI_IMAGE_TYPE_S{
	WEI_IMAGE_TYPE_BOOTLOADER		= 0,
	WEI_IMAGE_TYPE_SECOND_BOOTLOADER,
	WEI_IMAGE_TYPE_BOOTLOADER_PATCH, //only for Ver.A
	WEI_IMAGE_TYPE_LAYOUT_DESCRIPTOR,	
	WEI_IMAGE_TYPE_APPLICATION,
	WEI_IMAGE_TYPE_APPLICATION_CONFIG,
	WEI_IMAGE_TYPE_CUST_ALGO_CONFIG,
	WEI_IMAGE_TYPE_EMZA_CONFIG,
	WEI_IMAGE_TYPE_CNN_LUT,
	WEI_IMAGE_TYPE_LOGER,
	WEI_IMAGE_TYPE_AUDIO_DATA, // = 10.
	WEI_IMAGE_TYPE_FR_DATA, // = 11.
	WEI_IMAGE_TYPE_ALANGO_ALGO = 0x0f,   //ALANGO
	
	WEI_IMAGE_TYPE_WR_CONFIG = 0x10,  //WaterReader Config
	WEI_IMAGE_TYPE_ALGO_MODEL = 0x11,

	WEI_IMAGE_TYPE_COUNTS = 0xaa,
	WEI_IMAGE_MAX,
}WEI_IMAGE_TYPE_E;



/****************************************************
 * Type Definition                                 *
 ***************************************************/




/****************************************************
 * Structure Definition                             *
 ***************************************************/

typedef struct wei_memory_dsp_item_s{
	uint32_t pat_type;		
	uint32_t pat_att;			
	uint32_t pat_addr;			
	uint32_t pat_size;		
}wei_memory_dsp_item_t;

typedef struct wei_img_sec_item_s{
	uint32_t offset;		// offset address of secure boot image section #n start from flash_header_t
	uint32_t type;			// section image type
	uint32_t dst;			// destination address
	uint32_t payload;		// payload size for secure boot image section #n (SB Image Header + SB Image Section)
}wei_img_sec_item_t;

typedef struct wei_img_header_s{
	uint8_t type;			// indicate the secure image type (refer to SB_HEADER_TYPE_S)
	uint8_t version;		// Version of the SB header
	uint16_t crc;			// CRC value (CRC is calculated over the bytes from Size to ADDR_NEXT_SBH)

	uint8_t pid;			// Product ID (should be 35 for PA8535)
	uint8_t num_sbs;		// section count of secure boot image
	uint16_t size;			// the size of secure boot header (except Type/Version/CRC)

	uint16_t reserved0;
	uint16_t reserved1;

	uint32_t next_img_header;
}wei_img_header_t;

typedef struct flash_header_s{
	wei_img_header_t info;
	wei_img_sec_item_t item[SB_HEADER_SECT_MAX];
}flash_header_t;

typedef struct memory_dsp_s{
	wei_img_header_t info;
	wei_memory_dsp_item_t item[SB_HEADER_SECT_MAX];
}memory_dsp_t;


typedef struct wei_img_info_s{
	uint32_t rollback_id;
	uint32_t prj_id;
}wei_img_info_t;

typedef struct wei_security_info_s{
	wei_img_info_t img_info[WEI_IMAGE_MAX];
}wei_security_info_t;



/****************************************************
 * Function Declaration                             *
 ***************************************************/
uint32_t hx_board_get_ota_version(uint8_t type);
uint32_t hx_board_get_ota_projid(void);
void hx_boot_branch(int pc);

SEC_ERROR_E read_otp(uint32_t *output_otp, otp_ahb_wc_partition partition, uint32_t offset);
void i2c_read_otp_chip_id(uint8_t *wbuf, uint8_t *rbuf, int cmd);
void set_ota_result(OTA_STATUS_E status, OTA_ERROR_E error);
void HX_UNCACHE_BIT_SET(uint32_t REG, uint32_t SIZE, uint32_t POS, uint32_t VAL);
SEC_ERROR_E read_otp_init();
void dw_spi_eeprom_freq_div(int index, uint32_t div);



#endif /* LIBRARY_OTA_H_ */

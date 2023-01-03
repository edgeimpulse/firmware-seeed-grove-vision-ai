
#ifndef INC_SPI_M_PROTOCOL_H_
#define INC_SPI_M_PROTOCOL_H_

#include "dev_common.h"
#include "spi_protocol.h"

typedef void (*spi_mst_protocol_cb_t) (void );

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief	spi master 1 open device, speed with set to 1Mhz
 *
 * \retval	0					success
 * \retval	-1					fail
 */
extern int hx_drv_spi_mst_open();

/**
 * \brief	spi master 1 open device with target speed.
 *			Ex.
 *				//set spi master 1 speed to 50Mhz
 *				if(hx_drv_spi_mst_open_speed(50000000,400000000) != 0) //spi clock, cpu clock
 *					return ;
 *
 * \param[in]	spi_clk			spi clock speed value between 0 to 50000000Hz
 * \param[in]	cpu_clk			cpu clock speed value in hz
 * \retval		0				success
 * \retval		-1				fail
 */
extern int hx_drv_spi_mst_open_speed(uint32_t spi_clk, uint32_t cpu_clk);

/**
 * \brief	spi master 1 use protocol to send image out. data type in the header will be "JPG = 0x01".
 *
 * \param[in]	SRAM_addr	 	address of image data to transfer
 * \param[in]	img_size	 	image data size in bytes
 * \retval		0				success
 * \retval		-1				fail
 */
extern int hx_drv_spi_mst_protocol_write(uint32_t SRAM_addr, uint32_t img_size);

/**
 * \brief	spi master 1 use protocol to send image out. header_len should be described at upper layer.
 * 			This is a custom API for send data
 *
 * \param[in]	SRAM_addr		address of image data to transfer
 * \param[in]	img_size		image data size in bytes
 * \param[in]	header_len	 	packet header length
 * \retval		0				success
 * \retval		-1				fail
 */
extern int hx_drv_spi_mst_protocol_write_cus(uint32_t SRAM_addr, uint32_t img_size, uint32_t header_len);

/**
 * \brief	spi master 1 use protocol to send data out. data type should be specified.
 *
 * \param[in]	SRAM_addr	 	address of data to transfer
 * \param[in]	img_size	 	data size
 * \param[in]	data_type	 	data type
 * \retval		0				success
 * \retval		-1				fail
 */
extern int hx_drv_spi_mst_protocol_write_sp(uint32_t SRAM_addr, uint32_t img_size, SPI_CMD_DATA_TYPE data_type);

/**
 * \brief	spi master 1 force to stop current transmission.
 *
 * \retval		0				success
 * \retval		-1				fail
 */

extern int hx_drv_spi_mst_protocol_write_sp_capsule_02(uint32_t SRAM_addr, uint32_t img_size, SPI_CMD_DATA_TYPE data_type);

extern int hx_drv_spi_mst_protocol_write_halt();

/**
 * \brief	spi master 1 use protocol to read data. this is a blocking function which maximum wait 3 sec for spi slave ready and read data back.
 * 			during the transmission, spi master wait spi slave ready flag via GPIO handshake pin. spi master read header packet back, this should
 * 			includes data length information given by spi slave. spi master then read target size of data back.
 *
 * \param[in]	SRAM_addr		address of data to read back
 * \param[out]	img_size		read back data size
 * \retval		0				success
 * \retval		-1				fail
 */
extern int hx_drv_spi_mst_protocol_read(uint32_t SRAM_addr, uint32_t *img_size);

/**
 * \brief	spi master 1 register callback function for send data finish.
 *
 * \param[in]	aRWritecb	 	callback function set to driver, driver will trigger this callback function when send data finish.
 * \retval		0				success
 * \retval		-1				fail
 */
extern int hx_drv_spi_mst_protocol_register_tx_cb(spi_mst_protocol_cb_t aRWritecb);

/**
 * \brief	spi master 1 register callback function for read data finish.
 *
 * \param[in]	aRWritecb	 	callback function set to driver, driver will trigger this callback function when read data finish.
 * \retval		0				success
 * \retval		-1				fail
 */
extern int hx_drv_spi_mst_protocol_register_rx_cb(spi_mst_protocol_cb_t aReadcb);

/**
 * \brief	spi flash open device, speed with set to 1Mhz
 *
 * \param[in]	dev_no	 		0:SIP flash when 72pin& 128pin package / 1:external flash when 72pin& 128pin package
 * \retval		0				success
 * \retval		-1				fail
 */
extern int hx_drv_spi_flash_open(uint8_t dev_no);

/**
 * \brief	spi flash open device with target speed, this function set SIP flash to this speed.
 *			Ex.
 *				//set SIP spi flash speed to 50Mhz
 *				if(hx_drv_spi_flash_open_speed(50000000, 400000000) != 0) // spi_clk, cpu_clk
 *					return ;
 *
 * \param[in]	spi_clk			spi clock speed value between 0 to 50000000Hz
 * \param[in]	cpu_clk			cpu clock speed value in hz
 * \retval	0					success
 * \retval	-1					fail
 */
extern int hx_drv_spi_flash_open_speed(uint32_t spi_clk, uint32_t cpu_clk);

/**
 * \brief	spi flash device close function. Please call this function when spi flash is no more needed.
 *
 * \param[in] dev_no			0:SIP flash when 72pin& 128pin package / 1:external flash when 72pin& 128pin package
 * \retval	0					success
 * \retval	-1					fail
 */
extern int hx_drv_spi_flash_close(uint8_t dev_no);

/**
 * \brief	spi flash device erase all function. Please aware this function clear all data in the flash, includes bootloader/firmware...
 *			Ex.
 *				//set SIP spi flash speed to 50Mhz
*				if(hx_drv_spi_flash_open_speed(50000000, 400000000) != 0) // spi_clk, cpu_clk
 *					return ;
 *
 *				//erase all data in the Flash
 *				if(hx_drv_spi_flash_protocol_eraseall(0) != 0)
 *					return ;
 *
 *				if(hx_drv_spi_flash_close(0) != 0)
 *					return ;
 *
 *
 * \param[in] dev_no			0:SIP flash when 72pin& 128pin package / 1:external flash when 72pin& 128pin package
 * \retval	0					success
 * \retval	-1					fail
 */
extern int hx_drv_spi_flash_protocol_eraseall(uint8_t dev_no);

/**
 * \brief	spi flash device erase sector (4Kbytes) function. When erase sector, please image that all flash area is aligned by sector(4Kbyte) and
 * 	    	erase sector function will erase the sector specified.
 *			Ex.
 *				//set SIP spi flash speed to 50Mhz
*				if(hx_drv_spi_flash_open_speed(50000000, 400000000) != 0) // spi_clk, cpu_clk
 *					return ;
 *
 *				//erase sector at 1MByte position, this sector area (0x100000~0x100FFF) will be erased state of all 1s  (0xFF)
 *				int sector_pos = 0x100000;
 *				if(hx_drv_spi_flash_protocol_erase_sector(0, sector_pos) != 0)
 *					return ;
 *
 *				if(hx_drv_spi_flash_close(0) != 0)
 *					return ;
 *
 *
 * \param[in] dev_no			0:SIP flash when 72pin& 128pin package / 1:external flash when 72pin& 128pin package
 * \param[in] flash_addr		flash address related to the sector
 * \retval	0					success
 * \retval	-1					fail
 */
extern int hx_drv_spi_flash_protocol_erase_sector(uint8_t dev_no, uint32_t flash_addr);

/**
 * \brief	spi flash device write function, it wrote specified size of data with given source (SRAM address) to target (flash address).
 * 			Please notice that this area should be erase first.
 *			Ex.
 *				//set SIP spi flash speed to 50Mhz
*				if(hx_drv_spi_flash_open_speed(50000000, 400000000) != 0) // spi_clk, cpu_clk
 *					return ;
 *
 *				//erase 10 sectors (40 KBytes) start from 1MByte position
 *				int sector_pos = 0x100000;
 *				int sector_size = 0x1000;
 *				for(int i = 0;i<10;i++) {
 *					if(hx_drv_spi_flash_protocol_erase_sector(0, sector_pos+i*sector_size) != 0)
 *						return ;
 *				}
 *
 *				//write data to flash at flash position 1MBytes, data array is located at 0x20150000 with size 0x100 bytes.
 *				uint32_t meta_data_pos = 0x20150000;
 *				uint32_t meta_data_size = 0x100;
 *				hx_drv_spi_flash_protocol_write(0, sector_pos, meta_data_pos, meta_data_size, 4);
 *
 *				if(hx_drv_spi_flash_close(0) != 0)
 *					return ;
 *
 *
 * \param[in] dev_no			0:SIP flash when 72pin& 128pin package / 1:external flash when 72pin& 128pin package
 * \param[in] flash_addr		flash address
 * \param[in] SRAM_addr			SRAM address
 * \param[in] len				data array length in bytes
 * \param[in] mode				1:single mode/4:quad mode
 * \retval	0					success
 * \retval	-1					fail
 */
extern int hx_drv_spi_flash_protocol_write(uint8_t dev_no,uint32_t flash_addr, uint32_t SRAM_addr, uint32_t len, uint8_t mode);

/**
 * \brief	spi flash device read function, it read specified size of data with given source (flash address) to target (SRAM address).
 *			Ex.
 *				//set SIP spi flash speed to 50Mhz
*				if(hx_drv_spi_flash_open_speed(50000000, 400000000) != 0) // spi_clk, cpu_clk
 *					return ;
 *
 *				//erase 10 sectors (40 KBytes) start from 1MByte position
 *				int sector_pos = 0x100000;
 *				int sector_size = 0x1000;
 *				for(int i = 0;i<10;i++) {
 *					if(hx_drv_spi_flash_protocol_erase_sector(0, sector_pos+i*sector_size) != 0)
 *						return ;
 *				}
 *
 *				//write data to flash at flash position 1MBytes, data array is located at 0x20150000 with size 0x100 bytes.
 *				uint32_t meta_data_pos = 0x20150000;
 *				uint32_t meta_data_size = 0x100;
 *				hx_drv_spi_flash_protocol_write(0, sector_pos, meta_data_pos, meta_data_size, 4);
 *
 *				//read data from flash at position 1MBytes and put to SRAM 0x20160000 with size 0x100 bytes.
 *				uint32_t read_back_pos = 0x20160000;
 *				uint32_t read_back_size = 0x100;
 *				hx_drv_spi_flash_protocol_read(0, sector_pos, read_back_pos, read_back_size, 4);
 *
 *				if(hx_drv_spi_flash_close(0) != 0)
 *					return ;
 *
 *
 * \param[in] dev_no			0:SIP flash when 72pin& 128pin package / 1:external flash when 72pin& 128pin package
 * \param[in] flash_addr		flash address
 * \param[in] SRAM_addr			SRAM address
 * \param[in] len				data array length in bytes
 * \param[in] mode				1:single mode/2:dual mode/4:quad mode
 * \retval	0					success
 * \retval	-1					fail
 */
extern int hx_drv_spi_flash_protocol_read(uint8_t dev_no,uint32_t flash_addr, uint32_t SRAM_addr, uint32_t len, uint8_t mode);

#ifdef __cplusplus
}
#endif
#endif

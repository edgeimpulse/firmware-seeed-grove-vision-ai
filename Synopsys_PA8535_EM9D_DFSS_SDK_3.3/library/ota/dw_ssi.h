/*
 * spi_mst.h
 *
 *  Created on: 2019¦~3¤ë7¤é
 *      Author: 902452
 */

#ifndef SRC_SPI_MST_H_
#define SRC_SPI_MST_H_

void dw_ssi_xip_disable(int index);
void dw_ssi_xip_enable(int index);
void dw_ssi_erase_sector(int index, unsigned int start_addr, unsigned int end_addr);
void dw_ssi_eeprom_word_write (int index, unsigned int addr, unsigned int *data, unsigned int bytes_len);
#endif /* SRC_DW_SSI_H_ */

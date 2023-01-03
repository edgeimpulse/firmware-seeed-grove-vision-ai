/*
 * uart_protocol.h
 *
 *  Created on: 2020¦~4¤ë30¤é
 *      Author: 903935
 */

#ifndef PERIPHERAL_UART_UART_PROTOCOL_H_
#define PERIPHERAL_UART_UART_PROTOCOL_H_

void uart_callback_fun_tx(void);

/**
 * \brief	uart send data
 *
 * param[in]    SRAM_addr   we1 SRAM adddress
 * param[in]    img_size    transmission data size
 * param[in]    data_type   SPI/UART command data type
 * \retval	-1:transmission failed, 0:transmission succeed.
 */
int app_uart_send(uint32_t SRAM_addr, uint32_t img_size, SPI_CMD_DATA_TYPE data_type);

#endif /* PERIPHERAL_UART_UART_PROTOCOL_H_ */

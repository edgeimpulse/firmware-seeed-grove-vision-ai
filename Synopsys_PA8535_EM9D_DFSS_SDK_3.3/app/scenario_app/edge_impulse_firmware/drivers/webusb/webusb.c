#ifndef WEBUSB_H
#define WEBUSB_H

#include <stdint.h>
#include <stddef.h>

#include "grove_ai_config.h"
#include "hx_drv_timer.h"
#include "hx_drv_iomux.h"
#include "hx_drv_uart.h"
#include "console_io.h"
#include "debugger.h"

#define WEBUSB_PROTOCOL_JPEG_MAGIC 0x2B2D2B2D
#define WEBUSB_PROTOCOL_TEXT_MAGIC 0x0F100E12

static DEV_UART *console_uart;

void webusb_init(void)
{
    hx_drv_iomux_set_pmux(WEBUSB_SYNC_PIN, 3);
    hx_drv_iomux_set_outvalue(WEBUSB_SYNC_PIN, 1 - WEBUSB_SYNC_STATE);
    console_uart = hx_drv_uart_get_dev(CONSOLE_UART_ID);
}

void webusb_write_jpeg(uint8_t *jpeg, size_t jpeg_size)
{
    if (console_uart == NULL || jpeg == NULL)
    {
        return;
    }
    if (!debugger_available())
    {
        return;
    }
    board_delay_ms(1);
    hx_drv_iomux_set_outvalue(WEBUSB_SYNC_PIN, WEBUSB_SYNC_STATE);
    board_delay_ms(1);
    uint8_t header[8] = {0};
    header[0] = (WEBUSB_PROTOCOL_JPEG_MAGIC & 0xFF000000) >> 24;
    header[1] = (WEBUSB_PROTOCOL_JPEG_MAGIC & 0xFF0000) >> 16;
    header[2] = (WEBUSB_PROTOCOL_JPEG_MAGIC & 0xFF00) >> 8;
    header[3] = (WEBUSB_PROTOCOL_JPEG_MAGIC & 0xFF);
    header[4] = (jpeg_size & 0xFF000000) >> 24;
    header[5] = (jpeg_size & 0xFF0000) >> 16;
    header[6] = (jpeg_size & 0xFF00) >> 8;
    header[7] = (jpeg_size & 0xFF);

    console_uart->uart_write(header, 8);

    board_delay_ms(1);
    console_uart->uart_write(jpeg, jpeg_size);
    board_delay_ms(1);
    hx_drv_iomux_set_outvalue(WEBUSB_SYNC_PIN, 1 - WEBUSB_SYNC_STATE);
}

void webusb_write_text(char *text, size_t text_size)
{
    if (console_uart == NULL || text == NULL)
    {
        return;
    }
    if (!debugger_available())
    {
        return;
    }
    board_delay_ms(1);
    hx_drv_iomux_set_outvalue(WEBUSB_SYNC_PIN, WEBUSB_SYNC_STATE);
    board_delay_ms(1);
    uint8_t header[8] = {0};
    header[0] = (WEBUSB_PROTOCOL_TEXT_MAGIC & 0xFF000000) >> 24;
    header[1] = (WEBUSB_PROTOCOL_TEXT_MAGIC & 0xFF0000) >> 16;
    header[2] = (WEBUSB_PROTOCOL_TEXT_MAGIC & 0xFF00) >> 8;
    header[3] = (WEBUSB_PROTOCOL_TEXT_MAGIC & 0xFF);
    header[4] = (text_size & 0xFF000000) >> 24;
    header[5] = (text_size & 0xFF0000) >> 16;
    header[6] = (text_size & 0xFF00) >> 8;
    header[7] = (text_size & 0xFF);

    console_uart->uart_write(header, 8);

    board_delay_ms(1);
    console_uart->uart_write(text, text_size);
    board_delay_ms(1);
    hx_drv_iomux_set_outvalue(WEBUSB_SYNC_PIN, 1 - WEBUSB_SYNC_STATE);
}


#endif /* EI_I2C_HANDLERS_H */
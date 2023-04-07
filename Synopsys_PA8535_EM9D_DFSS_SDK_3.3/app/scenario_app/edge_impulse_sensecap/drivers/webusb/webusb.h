#ifndef WEBUSB_H
#define WEBUSB_H

#include <stdint.h>
#include <stddef.h>

#include "grove_ai_config.h"

#ifdef __cplusplus
extern "C"
{
#endif

void webusb_init(void);
void webusb_write_jpeg(uint8_t *jpeg, size_t jpeg_size);
void webusb_write_text(char *text, size_t text_size);

#ifdef __cplusplus
}
#endif

#endif /* WEBUSB */
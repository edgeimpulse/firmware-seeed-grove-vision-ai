#ifndef EI_ENCODE_JPEG
#define EI_ENCODE_JPEG
#include <stdint.h>
#include "edge-impulse-sdk/dsp/numpy_types.h"

/**
 * This module is a wrapper
 */

int encode_as_jpeg_send(ei::signal_t *signal, int width, int height);
int encode_as_jpeg_buf(uint8_t *framebuffer, size_t framebuffer_size, int width, int height, uint8_t *out_buffer, size_t out_buffer_size, size_t *out_size);

#endif /* EI_ENCODE_JPEG */
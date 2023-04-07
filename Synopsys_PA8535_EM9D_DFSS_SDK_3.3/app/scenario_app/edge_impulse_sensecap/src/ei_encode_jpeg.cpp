#include "firmware-sdk/jpeg/encode_as_jpg.h"
#include "ei_encode_jpeg.h"

using namespace ei;

int encode_as_jpeg_send(signal_t *signal, int width, int height)
{
    return encode_rgb888_signal_as_jpg_and_output_base64(signal, width, height);
}

int encode_as_jpeg_buf(uint8_t *framebuffer, size_t framebuffer_size, int width, int height, uint8_t *out_buffer, size_t out_buffer_size, size_t *out_size)
{
    return encode_as_jpg(framebuffer, framebuffer_size, width, height, out_buffer, out_buffer_size, out_size);
}

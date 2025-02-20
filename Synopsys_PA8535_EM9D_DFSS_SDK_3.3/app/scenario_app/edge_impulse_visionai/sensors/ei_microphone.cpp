/* The Clear BSD License
 *
 * Copyright (c) 2025 EdgeImpulse Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the disclaimer
 * below) provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *   this list of conditions and the following disclaimer.
 *
 *   * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 *   * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY
 * THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "ei_microphone.h"
#include "ei_device_vision_ai.h"
#include "firmware-sdk/sensor_aq.h"
#include "firmware-sdk/at_base64_lib.h"
#include "sensor_aq_mbedtls/sensor_aq_mbedtls_hs256.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
extern "C" {
    #include "aud_lib.h"
};

// max block size is 8kB (due to uDMA limitations)
// must be a multiply of 4 (we are collecting 2 channels * 2 bytes per channel)
#define AUDIO_SAMPLE_BLOCK_SIZE 4096
// make sure AUDIO_SAMPLE_BLOCKS_NUM is even, because half of blocks num is set
// as threshold to fire the callback
// total number of allocated on heap buffer is AUDIO_SAMPLE_BLOCKS_NUM * AUDIO_SAMPLE_BLOCK_SIZE
#define AUDIO_SAMPLE_BLOCKS_NUM (4)
#define SAMPLE_BUFFER_SIZE      (AUDIO_SAMPLE_BLOCKS_NUM * AUDIO_SAMPLE_BLOCK_SIZE)
#define CHANNEL_BUFFER_SIZE     (AUDIO_SAMPLE_BLOCKS_NUM * AUDIO_SAMPLE_BLOCK_SIZE / 4)
// due to DC removal algorithm in the PDM driver, we need to drop ~2048 samples
// after starting the sampling, otherwise the first samples are not correct
// 2048 samples * 2 channels * 2 bytes per channel = 8192 bytes
// 8192 bytes / 4096 bytes per block = 2 blocks
#define FIRST_BLOCKS_TO_DROP    (2)

/** Status and control struct for inferencing struct */
typedef struct {
    microphone_sample_t *buffers[2];
    uint8_t buf_select;
    uint8_t buf_ready;
    uint32_t buf_count;
    uint32_t n_samples;
} inference_t;

static size_t ei_write(const void *buffer, size_t size, size_t count, EI_SENSOR_AQ_STREAM *);
static int ei_seek(EI_SENSOR_AQ_STREAM *, long int offset, int origin);

static inference_t inference;
// number of bytes required to be collected for ingestion
static uint32_t required_bytes;
// number of bytes collected so far for ingestion
static uint32_t collected_bytes;
static uint32_t headerOffset = 0;
static uint8_t numDroppedBlocks = 0;
static microphone_sample_t sample_buffer[SAMPLE_BUFFER_SIZE];
microphone_sample_t *channel_buffer;

static unsigned char ei_mic_ctx_buffer[1024];
static sensor_aq_signing_ctx_t ei_mic_signing_ctx;
static sensor_aq_mbedtls_hs256_ctx_t ei_mic_hs_ctx;
static sensor_aq_ctx ei_mic_ctx = {
    { ei_mic_ctx_buffer, 1024 },
    &ei_mic_signing_ctx,
    &ei_write,
    &ei_seek,
    NULL,
};

/* Dummy functions for sensor_aq_ctx type */
static size_t ei_write(const void*, size_t size, size_t count, EI_SENSOR_AQ_STREAM*)
{
    return count;
}

static int ei_seek(EI_SENSOR_AQ_STREAM*, long int offset, int origin)
{
    return 0;
}

static int insert_ref(char *buffer, int hdrLength)
{
    #define EXTRA_BYTES(a)  ((a & 0x3) ? 4 - (a & 0x3) : (a & 0x03))
    const char *ref = "Ref-BINARY-i16";
    int addLength = 0;
    int padding = EXTRA_BYTES(hdrLength);

    buffer[addLength++] = 0x60 + 14 + padding;
    for(unsigned int i = 0; i < strlen(ref); i++) {
        buffer[addLength++] = *(ref + i);
    }
    for(int i = 0; i < padding; i++) {
        buffer[addLength++] = ' ';
    }

    buffer[addLength++] = 0xFF;

    return addLength;
}

static bool create_header(sensor_aq_payload_info *payload)
{
    int ret;
    EiDeviceVisionAI* dev = static_cast<EiDeviceVisionAI*>(EiDeviceVisionAI::get_device());
    EiDeviceMemory* mem = dev->get_memory();
    sensor_aq_init_mbedtls_hs256_context(&ei_mic_signing_ctx, &ei_mic_hs_ctx, dev->get_sample_hmac_key().c_str());

    ret = sensor_aq_init(&ei_mic_ctx, payload, NULL, true);

    if (ret != AQ_OK) {
        ei_printf("sensor_aq_init failed (%d)\n", ret);
        return false;
    }

    // then we're gonna find the last byte that is not 0x00 in the CBOR buffer.
    // That should give us the whole header
    size_t end_of_header_ix = 0;
    for (size_t ix = ei_mic_ctx.cbor_buffer.len - 1; ix != 0; ix--) {
        if (((uint8_t *)ei_mic_ctx.cbor_buffer.ptr)[ix] != 0x0) {
            end_of_header_ix = ix;
            break;
        }
    }

    if (end_of_header_ix == 0) {
        ei_printf("Failed to find end of header\n");
        return false;
    }

    int ref_size = insert_ref(((char*)ei_mic_ctx.cbor_buffer.ptr + end_of_header_ix), end_of_header_ix);
    // and update the signature
    ret = ei_mic_ctx.signature_ctx->update(ei_mic_ctx.signature_ctx, (uint8_t*)(ei_mic_ctx.cbor_buffer.ptr + end_of_header_ix), ref_size);
    if (ret != 0) {
        ei_printf("Failed to update signature from header (%d)\n", ret);
        return false;
    }
    end_of_header_ix += ref_size;

    // Write to blockdevice
    ret = mem->write_sample_data((uint8_t*)ei_mic_ctx.cbor_buffer.ptr, 0, end_of_header_ix);
    if ((size_t)ret != end_of_header_ix) {
        ei_printf("Failed to write to header blockdevice (%d)\n", ret);
        return false;
    }

    headerOffset = end_of_header_ix;

    return true;
}

static void ingestion_samples_callback(uint32_t status)
{
    EiDeviceVisionAI* dev = static_cast<EiDeviceVisionAI*>(EiDeviceInfo::get_device());
    EiDeviceMemory* mem = dev->get_memory();
    uint32_t audio_buf_addr;
    uint32_t available_blocks;

    // get number of available blocks
    hx_lib_audio_request_read(&audio_buf_addr, &available_blocks);
    for (int block = 0; block < available_blocks; block++) {
        if(numDroppedBlocks < FIRST_BLOCKS_TO_DROP) {
            numDroppedBlocks++;
            continue;
        }
        // one block has two channels, we need to extract only one channel, so maximum block_size / 2 bytes
        // but if we need to collect full block, then just collect as much as we need
        const int chunk_bytes = (required_bytes - collected_bytes) > (AUDIO_SAMPLE_BLOCK_SIZE / 2) ?
            (AUDIO_SAMPLE_BLOCK_SIZE / 2) :
            (required_bytes - collected_bytes);

        for(int byte = 0; byte < chunk_bytes; byte++) {
            channel_buffer[byte] = ((microphone_sample_t*)audio_buf_addr)[byte * 2];
        }

        // write to memory
        mem->write_sample_data((uint8_t*)channel_buffer, headerOffset + collected_bytes, chunk_bytes);

        // update data hash
        ei_mic_ctx.signature_ctx->update(ei_mic_ctx.signature_ctx, (uint8_t*)channel_buffer, chunk_bytes);

        collected_bytes += chunk_bytes;
        audio_buf_addr += chunk_bytes * 2;
    }

    hx_lib_audio_update_idx(&available_blocks);
}

bool ei_microphone_init(void)
{
    hx_lib_audio_set_if(AUDIO_IF_PDM);
    hx_lib_audio_init();

    return true;
}

bool ei_microphone_sample_start(void)
{
    EiDeviceVisionAI* dev = static_cast<EiDeviceVisionAI*>(EiDeviceInfo::get_device());
    EiDeviceMemory* mem = dev->get_memory();
    audio_config_t audio_cfg;

    uint8_t *page_buffer;
    int ret;
    uint32_t required_samples;

    sensor_aq_payload_info payload = {
        dev->get_device_id().c_str(),
        dev->get_device_type().c_str(),
        dev->get_sample_interval_ms(),
        { { "audio", "wav" } }
    };

    ei_printf("Sampling settings:\n");
    ei_printf("\tInterval: ");
    ei_printf_float(dev->get_sample_interval_ms());
    ei_printf(" ms.\n");
    ei_printf("\tLength: %lu ms.\n", dev->get_sample_length_ms());
    ei_printf("\tName: %s\n", dev->get_sample_label().c_str());
    ei_printf("\tHMAC Key: %s\n", dev->get_sample_hmac_key().c_str());
    ei_printf("\tFile name: %s\n", dev->get_sample_label().c_str());

    required_samples = (uint32_t)((dev->get_sample_length_ms()) / dev->get_sample_interval_ms());

    /* Round to even number of samples for word align flash write */
    if(required_samples & 1) {
        required_samples++;
    }

    required_bytes = required_samples * sizeof(microphone_sample_t);
    collected_bytes = 0;

    if(required_bytes > mem->get_available_sample_bytes()) {
        ei_printf("ERR: Sample length is too long. Maximum allowed is %lu ms at 16000 Hz.\r\n",
            ((mem->get_available_sample_bytes() / (16000 * sizeof(microphone_sample_t))) * 1000));
        return false;
    }

    dev->set_state(eiStateErasingFlash);

    // Minimum delay of 2000 ms for daemon
    uint32_t delay_time_ms = ((required_bytes / mem->block_size) + 1) * mem->block_erase_time;
    ei_printf("Starting in %lu ms... (or until all flash was erased)\n", delay_time_ms < 2000 ? 2000 : delay_time_ms);

    if(mem->erase_sample_data(0, required_bytes) != (required_bytes)) {
        return false;
    }

    // if erasing took less than 2 seconds, wait additional time
    if(delay_time_ms < 2000) {
        ei_sleep(2000 - delay_time_ms);
    }

    if (create_header(&payload) == false) {
        return false;
    }

    channel_buffer = (microphone_sample_t*)ei_malloc(CHANNEL_BUFFER_SIZE);
    if(channel_buffer == nullptr) {
        ei_printf("ERR: Failed to allocate channel buffer\n");
        return false;
    }

    ei_printf("Sampling...\n");

    audio_cfg.sample_rate = AUDIO_SR_16KHZ;
    audio_cfg.buffer_addr = (uint32_t*)sample_buffer;
    // block size in bytes
    audio_cfg.block_sz = AUDIO_SAMPLE_BLOCK_SIZE;
    // total number of blocks allocated in buffer
    audio_cfg.block_num = AUDIO_SAMPLE_BLOCKS_NUM;
    // numbers of blocks to fire an event
    audio_cfg.cb_evt_blk = 2;
    hx_lib_audio_register_evt_cb(ingestion_samples_callback);
    hx_lib_audio_start(&audio_cfg);

    dev->set_state(eiStateSampling);

    while (collected_bytes < required_bytes) {
        ei_sleep(10);
    }

    //TODO: return value
    hx_lib_audio_stop();
    numDroppedBlocks = 0;

    ei_free(channel_buffer);

    ret = ei_mic_ctx.signature_ctx->finish(ei_mic_ctx.signature_ctx, ei_mic_ctx.hash_buffer.buffer);
    if (ret != 0) {
        ei_printf("Failed to finish signature (%d)\n", ret);
        return false;
    }

    // load the first page in flash...
    page_buffer = (uint8_t*)ei_malloc(mem->block_size);
    if (!page_buffer) {
        ei_printf("Failed to allocate a page buffer to write the hash\n");
        return false;
    }

    ret = mem->read_sample_data(page_buffer, 0, mem->block_size);
    if ((uint32_t)ret != mem->block_size) {
        ei_printf("Failed to read first page (read %d, requersted %lu)\n", ret, mem->block_size);
        ei_free(page_buffer);
        return false;
    }

    // update the hash
    uint8_t *hash = ei_mic_ctx.hash_buffer.buffer;
    // we have allocated twice as much for this data (because we also want to be able to represent in hex)
    // thus only loop over the first half of the bytes as the signature_ctx has written to those
    for (size_t hash_ix = 0; hash_ix < ei_mic_ctx.hash_buffer.size / 2; hash_ix++) {
        // this might seem convoluted, but snprintf() with %02x is not always supported e.g. by newlib-nano
        // we encode as hex... first ASCII char encodes top 4 bytes
        uint8_t first = (hash[hash_ix] >> 4) & 0xf;
        // second encodes lower 4 bytes
        uint8_t second = hash[hash_ix] & 0xf;

        // if 0..9 -> '0' (48) + value, if >10, then use 'a' (97) - 10 + value
        char first_c = first >= 10 ? 87 + first : 48 + first;
        char second_c = second >= 10 ? 87 + second : 48 + second;

        page_buffer[ei_mic_ctx.signature_index + (hash_ix * 2) + 0] = first_c;
        page_buffer[ei_mic_ctx.signature_index + (hash_ix * 2) + 1] = second_c;
    }

    ret = mem->erase_sample_data(0, mem->block_size);
    if ((uint32_t)ret != mem->block_size) {
        ei_printf("Failed to erase first page (read %d, requested %lu)\n", ret, mem->block_size);
        ei_free(page_buffer);
        return false;
    }

    ret = mem->write_sample_data(page_buffer, 0, mem->block_size);
    ei_free(page_buffer);

    if ((uint32_t)ret != mem->block_size) {
        ei_printf("Failed to write first page with updated hash (read %d, requested %lu)\n", ret, mem->block_size);
        return false;
    }

    ei_printf("Done sampling, total bytes collected: %lu\n", required_bytes);
    ei_printf("[1/1] Uploading file to Edge Impulse...\n");
    ei_printf("Not uploading file, not connected to WiFi. Used buffer, from=0, to=%lu.\n", required_bytes + headerOffset);
    ei_printf("OK\n");

    return true;
}

static void inference_samples_callback(uint32_t status)
{
    uint32_t audio_buf_addr;
    uint32_t available_blocks;
    microphone_sample_t *buf;
    // get number of available blocks
    hx_lib_audio_request_read(&audio_buf_addr, &available_blocks);

    for (int block = 0; block < available_blocks; block++) {
        if(numDroppedBlocks < FIRST_BLOCKS_TO_DROP) {
            numDroppedBlocks++;
            continue;
        }
        // one block has two channels, we need to extract only one channel, so maximum block_size / 4 samples
        // but if we need to collect full block, then just collect as much as we need
        const int chunk_samples = ((inference.n_samples - inference.buf_count)) > (AUDIO_SAMPLE_BLOCK_SIZE / 4) ?
            (AUDIO_SAMPLE_BLOCK_SIZE / 4) :
            ((inference.n_samples - inference.buf_count));

        buf = &inference.buffers[inference.buf_select][inference.buf_count];
        for(int sample = 0; sample < chunk_samples; sample++) {
            buf[sample] = ((microphone_sample_t*)audio_buf_addr)[sample * 2];
        }

        inference.buf_count += chunk_samples;
        audio_buf_addr += chunk_samples * 2;

        if(inference.buf_count >= inference.n_samples) {
            inference.buf_select ^= 1;
            inference.buf_count = 0;
            inference.buf_ready = 1;
        }
    }

    hx_lib_audio_update_idx(&available_blocks);
}

int ei_microphone_inference_get_data(size_t offset, size_t length, float *out_ptr)
{
    size_t i;

    for(i = 0; i < length; i++) {
        *(out_ptr + i) = (float)inference.buffers[inference.buf_select ^ 1][offset + i]
        / ((float)(1 << 15));
    }

    return 0;
}

static microphone_sample_t buf[2][32768];

bool ei_microphone_inference_start(uint32_t n_samples, float interval_ms)
{
    audio_config_t audio_cfg;

    inference.buffers[0] = buf[0];
    if(inference.buffers[0] == NULL) {
        return false;
    }

    inference.buffers[1] = buf[1];
    if(inference.buffers[1] == NULL) {
        return false;
    }

    // double buffer because of double buffering
    if(sample_buffer == nullptr) {
        ei_printf("ERR: Failed to allocate audio buffer\n");
        return false;
    }

    inference.buf_select = 0;
    inference.buf_count  = 0;
    inference.n_samples  = n_samples;
    inference.buf_ready  = 0;

    audio_cfg.sample_rate = AUDIO_SR_16KHZ;
    audio_cfg.buffer_addr = (uint32_t*)sample_buffer;
    // block size in bytes
    audio_cfg.block_sz = AUDIO_SAMPLE_BLOCK_SIZE;
    // total number of blocks allocated in buffer
    audio_cfg.block_num = AUDIO_SAMPLE_BLOCKS_NUM;
    // numbers of blocks to fire an event
    audio_cfg.cb_evt_blk = 2;
    hx_lib_audio_register_evt_cb(inference_samples_callback);
    hx_lib_audio_start(&audio_cfg);

    return true;
}

bool ei_microphone_inference_is_recording(void)
{
    return inference.buf_ready == 0;
}

void ei_microphone_inference_reset_buffers(void)
{
    inference.buf_ready = 0;
    inference.buf_count = 0;
}

bool ei_microphone_inference_end(void)
{
    hx_lib_audio_stop();

    numDroppedBlocks = 0;

    return true;
}

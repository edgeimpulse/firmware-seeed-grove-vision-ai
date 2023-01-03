/*
 * tflm_audio_function.h
 *
 *  Created on: 2020/06/15
 *      Author: 903730
 */

#ifndef LIBRARY_TFLM_INTERNAL_INC_TFLM_AUDIO_FUNCTION_H_
#define LIBRARY_TFLM_INTERNAL_INC_TFLM_AUDIO_FUNCTION_H_

#include <stdint.h>

typedef struct {
    uint32_t  audio_data_address;
    uint32_t  audio_data_size;
} tflm_audio_samples_t;

typedef enum
{
	TFLM_AUDIO_NO_ERROR = 0,                 /**< No ERROR */
	TFLM_AUDIO_ERROR_NOT_INIT = 1,           /**< ERROR MSG: not init */
	TFLM_AUDIO_ERROR_DRIVER = 2,             /**< ERROR MSG: audio driver error */
	TFLM_AUDIO_ERROR_ALREADY_INIT = 3,       /**< ERROR MSG: already init */
	TFLM_AUDIO_ERROR_INVALID_PARAMETERS = 4, /**< ERROR MSG: Invalid parameters */
	TFLM_AUDIO_ERROR_NULL_POINTER = 5,       /**< ERROR MSG: NULL pointer */
	TFLM_AUDIO_UNKNOWN_ERROR = 6,            /**< ERROR MSG: UNKNOWN ERROR*/
} TFLM_AUDIO_ERROR_E;

TFLM_AUDIO_ERROR_E tflm_audio_init();
TFLM_AUDIO_ERROR_E tflm_audio_start();
TFLM_AUDIO_ERROR_E tflm_audio_stop();
void tflm_audio_samples_get(tflm_audio_samples_t *audio_samples);
int tflm_audio_data_get(uint32_t *aud_addr, uint32_t *size);
uint32_t tflm_audio_timestamp_get(void);

#endif /* LIBRARY_TFLM_INTERNAL_INC_TFLM_AUDIO_FUNCTION_H_ */

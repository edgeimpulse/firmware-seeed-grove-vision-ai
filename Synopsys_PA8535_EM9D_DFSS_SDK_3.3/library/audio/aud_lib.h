/**
 ********************************************************************************************
 *  @file      aud_lib.h
 *  @details   This file contains all I2S/PDM audio library related function
 *  @author    himax/902453
 *  @version   V1.0.0
 *  @date      21-Aug-2019
 *  @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 *******************************************************************************************/
/**
 * \defgroup	AUDIO_LIB	Audio Library
 * \ingroup	AUDIO_LIB
 * \brief	I2S/PDM Audio library Declaration
 */

#ifndef LIBRARY_AUDIO_LIB_H_
#define LIBRARY_AUDIO_LIB_H_

#include "hx_drv_pdm_rx.h"
#include "hx_drv_i2s.h"
/***************************************************
 * Macro Definition
 **************************************************/
#if 0   /* configuretions by hx_lib_audio_start() */
#if defined(AIOT_HUMANDETECT_TV) || defined(AIOT_HUMANDETECT_AIRCONDITION) || defined(AUDIO_RECOGNITION)
#define AUD_BUF_BLOCK_NUM       (23)//(32) 2sec, (64) 4sec //(20)   /* This constant defines the maximum number of Audio buffer */
#define AUD_BUF_BLOCK_SIZE 	    (4096)                              /* This constant defines the Audio buffer block size, max is 8KB. */
#define AUD_CB_EVT_BLK          (2)                                 /* This constant defines the Audio buffer block fill callback event */
/**
* 256KB : (0x200DD400) (HM0360 - 1 Frame)
* 128KB : (0x200FD400) (HM0360 - 1 Frame)
*         (0x20091000) (HM01B0 - 10 Frame)
*/
#define AUD_BUF_ADDR            (0x20000000+36*1024)                /* This constant defines the Audio buffer start address */
#else
#define AUD_BUF_BLOCK_NUM       (40)            /* This constant defines the maximum number of Audio buffer */
#define AUD_BUF_BLOCK_SIZE      (8192)          /* This constant defines the Audio buffer block size, max is 8KB. */
#define AUD_CB_EVT_BLK          (2)             /* This constant defines the Audio buffer block fill callback event */
#define AUD_BUF_ADDR            (0x200A0000)    /* This constant defines the Audio buffer start address */
#endif
#endif

typedef struct audio_config {
    uint32_t sample_rate;       /* This constant defines the Audio sample rate */
    uint32_t *buffer_addr;      /* This constant defines the Audio buffer start address */
    uint32_t block_num;         /* This constant defines the total number of Audio buffer block */
    uint32_t block_sz;          /* This constant defines audio block size, max is 8KB for uDMA single transfer */
    uint32_t cb_evt_blk;        /* This constant defines the Audio buffer block fill callback event */
} audio_config_t;

/**
 * \defgroup	AUDIO_LIB_ENUM	Audio Library Enumeration
 * \ingroup	AUDIO_LIB
 * \brief	Defines some enumeration of Audio Library need.
 * @{
 */
/****************************************************
 * ENUM Declaration                                 *
 ***************************************************/
/** AUDIO Errors Type **/
/**
 * \enum AUDIO_ERROR_E
 * \brief AUDIO API ERROR Code
 */
typedef enum AUDIO_ERROR_S
{
    AUDIO_NO_ERROR = 0,                 /**< No ERROR */
    AUDIO_ERROR_NOT_INIT = 1,           /**< ERROR MSG: not init */
    AUDIO_ERROR_DRIVER = 2,             /**< ERROR MSG: audio driver error */
    AUDIO_ERROR_ALREADY_INIT = 3,       /**< ERROR MSG: already init */
    AUDIO_ERROR_INVALID_PARAMETERS = 4, /**< ERROR MSG: Invalid parameters */
    AUDIO_ERROR_NULL_POINTER = 5,       /**< ERROR MSG: NULL pointer */
    AUDIO_UNKNOWN_ERROR = 6,            /**< ERROR MSG: UNKNOWN ERROR*/
} AUDIO_ERROR_E;

typedef enum AUDIO_IF_S
{
    AUDIO_IF_PDM,
    AUDIO_IF_I2S,
} AUDIO_IF_E;

typedef enum AUDIO_SR_S
{
    /* Compatible for I2S & PDM both sample rate enum */
    AUDIO_SR_16KHZ = 1,     
    AUDIO_SR_32KHZ = 2,
    AUDIO_SR_48KHZ = 4,
} AUDIO_SR_E;

/**
 * \enum AUDIO_CLK_SRC_E
 * \brief AUDIO CLK Source 0:rc_36m, 1:xtal_24m_post
 */
typedef enum
{
    AUDIO_CLK_SRC_RC_36M            = 0,    /**< AUDIO CLK Source from 0:rc_36m */
    AUDIO_CLK_SRC_XTAL_24M_POST     = 1,    /**< AUDIO CLK Source from 1:xtal_24m_post */
} AUDIO_CLK_SRC_E;

/**
 * \enum AUDIO_BCLK_E
 * \brief AUDIO BCLK 
 */
typedef enum
{
    AUDIO_BCLK_1M            = 1,
    AUDIO_BCLK_2M            = 2,
    AUDIO_BCLK_3M            = 3,
    AUDIO_BCLK_4M            = 4,
    AUDIO_BCLK_6M            = 6,
    AUDIO_BCLK_8M            = 8,
    AUDIO_BCLK_12M           = 12,
} AUDIO_BCLK_E;

typedef void (*AUD_ISR_CB)(uint32_t int_status);

/**
 * \brief	The function is used to set audio interface
 *
 */
void hx_lib_audio_set_if(uint32_t aud_if);
/** @} */

/**
 * \brief	The function is used to get audio interface
 *
 * \retval	AUDIO_IF_E	
 */
uint32_t hx_lib_audio_get_if(void);
/** @} */

/**
 * \brief	The function is used to get audio block size
 *
 * \retval	bytes	
 */

uint32_t hx_lib_audio_get_block_size(void);
/** @} */

/**
 * \brief	The function is used to init Audio RX
 *
 * \retval	AUDIO_ERROR_E	success
 * \retval	others			fail
 */
AUDIO_ERROR_E hx_lib_audio_init(void);
/** @} */

/**
 * \brief	The function is used to deinit Audio RX
 *
 * \retval	AUDIO_ERROR_E	success
 * \retval	others			fail
 */
AUDIO_ERROR_E hx_lib_audio_deinit(void);
/** @} */

/**
 * \brief	The function is used to register Audio RX evt cb
 *
 * \retval	AUDIO_ERROR_E	success
 * \retval	others			fail
 */
AUDIO_ERROR_E hx_lib_audio_register_evt_cb(AUD_ISR_CB aud_evt_cb);
/** @} */

/**
 * \brief	The function is used to start Audio RX
 *
 * \retval	AUDIO_ERROR_E	success
 * \retval	others			fail
 */
AUDIO_ERROR_E hx_lib_audio_start(audio_config_t *aud_cfg);
/** @} */

/**
 * \brief	The function is used to stop Audio RX
 *
 * \retval	AUDIO_ERROR_E	success
 * \retval	others			fail
 */
AUDIO_ERROR_E hx_lib_audio_stop(void);
/** @} */

/**
 * \brief	The function is used to request Audio RX read index
 *
 * \retval	AUDIO_ERROR_E	success
 * \retval	others			fail
 */
AUDIO_ERROR_E hx_lib_audio_request_read(uint32_t *address, uint32_t *block_num);
/** @} */

/**
 * \brief	The function is used to update Audio RX read index
 *
 * \retval	AUDIO_ERROR_E	success
 * \retval	others			fail
 */
AUDIO_ERROR_E hx_lib_audio_update_idx(uint32_t *block);
/** @} */


/**
 * \brief	set Audio CLK 
 *
 * \param[in]	clk_src Audio CLK Source from 0:rc_36m or 1:xtal_24m_post
 * \param[in]	bclk    Audio BCLK
 * 
 * \return	AUDIO_ERROR_E
 */
AUDIO_ERROR_E hx_lib_audio_set_clk(AUDIO_CLK_SRC_E clk_src, AUDIO_BCLK_E bclk);
/** @} */

#endif /* LIBRARY_AUDIO_LIB_H_ */

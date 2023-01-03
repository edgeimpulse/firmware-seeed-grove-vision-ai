/*
 * hx_drv_pdm_rx.h
 *
 *  Created on: 2019/03/08
 *      Author: 902453
 */

#ifndef INC_HX_DRV_PDM_RX_H_
#define INC_HX_DRV_PDM_RX_H_

#include "embARC_toolchain.h"
#include "hx_drv_ckgen.h"

/** PDM Errors Type **/
typedef enum PDM_ERROR_S
{
    PDM_NO_ERROR                    = 0,        /**< No ERROR */
    PDM_ERROR_NOT_INIT              = 1,        /**< ERROR MSG: not init */
    PDM_ERROR_ALREADY_INIT          = 2,        /**< ERROR MSG: already init */
    PDM_ERROR__INIT_FAIL            = 3,        /**< ERROR MSG: init fail */
    PDM_ERROR_INVALID_PARAMETERS    = 4,        /**< ERROR MSG: Invalid parameters */
    PDM_UNKNOWN_ERROR               = 5,        /**< ERROR MSG: UNKNOWN ERROR*/
} PDM_ERROR_E;

/** PDM PCM Freq **/
typedef enum PDM_PCM_FREQ_S
{
    PDM_PCM_FREQ_8K = 0,            
    PDM_PCM_FREQ_16K = 1,           
    PDM_PCM_FREQ_32K = 2,  
    /*PDM_PCM_FREQ_44_1K = 3,*/     /* PDM not support this, only compatible I2S enmu */          
    PDM_PCM_FREQ_48K = 4,          
} PDM_PCM_FREQ_E;

typedef struct PDM_CFG_S
{
    uint16_t rx_fifo_threshold;
    uint16_t oversampling_ratio;
    uint16_t cic_stages;
    uint16_t cic_delay;
    uint16_t dc_removal;
    uint16_t bit_range_shift;
} PDM_CFG_T;

typedef void (*PDM_ISR_CB)(uint32_t int_status);

typedef struct pdm_dev_info
{
    PDM_CFG_T pdm_cfg;
    PDM_ISR_CB pdm_rx_cb;
    PDM_ISR_CB pdm_err_cb;
    PDM_ISR_CB pdm_clip_cb;
} PDM_DEV_INFO, *PDM_DEV_INFO_PTR;

/* init PDM Driver */
PDM_ERROR_E hx_drv_pdm_init(PDM_DEV_INFO *pdm_dev_info);

/* Deinit PDM Driver */
PDM_ERROR_E hx_drv_pdm_deinit(PDM_DEV_INFO *pdm_dev_info);

/* Register PDM RX callback function */
PDM_ERROR_E hx_drv_pdm_register_cb(PDM_DEV_INFO *pdm_dev_info);

/* Start PDM Transfer */
PDM_ERROR_E hx_drv_pdm_init_transfer(uint32_t *data, uint32_t *size);

/* Stop PDM Transfer */
PDM_ERROR_E hx_drv_pdm_stop_transfer(void);

/* Set PCM Freq */
PDM_ERROR_E hx_drv_pdm_set_pcm_freq(uint32_t freq);
#endif /* INC_HX_DRV_PDM_RX_H_ */

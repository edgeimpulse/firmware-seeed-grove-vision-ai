/**
 * @file hx_drv_pwm.h
 * @author himax/902452
 * @brief 
 * @version V1.0.0
 * @date 2019-01-14
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef INC_HX_DRV_PWM_H_
#define INC_HX_DRV_PWM_H_

/***********************************************
 * CONSTANT DEFINITION
 **********************************************/
/**
 * \brief   contains definitions of PWM enable/disable
 * 
 */
#define PWM_EN                      1
#define PWM_DIS                     0


/**
 * \brief   PWM invertor
 * 
 */
#define PWM_INV_EN                  1
#define PWM_INV_DIS                 0

/**
 * \brief   PWM mode
 * 
 */
#define PWM_MODE_FIXED              0
#define PWM_MODE_CONTINUE           1
/***********************************************
 * EMULATOR DECLARATION
 **********************************************/
/**
 * \enum PWM_INDEX_E
 * \brief PWM INSTANCE
 */
typedef enum PWM_INDEX_S
{
    PWM0 = 0,
    PWM1,
    PWM2,
    PWM_MAX
} PWM_INDEX_E;


/**
 * \enum PWM_ERROR_E
 * \brief PWM Errors Type
 */
typedef enum PWM_ERROR_S
{
    PWM_NO_ERROR                        = 0,    /**< No ERROR */
    PWM_ERROR_NOT_INIT                  = 1,    /**< ERROR MSG: not init */
    PWM_ERROR_ALREADY_INIT              = 2,    /**< ERROR MSG: already init */
    PWM_ERROR_INVALID_PARAMETERS        = 3,    /**< ERROR MSG: Invalid parameters */
    PWM_ERROR_NULL_POINTER              = 4,    /**< ERROR MSG: NULL pointer */
    PWM_UNKNOWN_ERROR                   = 5,    /**< ERROR MSG: UNKNOWN ERROR*/
    PWM_ERROR_BUSY_STATUS               = 6,    /**< ERROR MSG: BUSY */
} PWM_ERROR_E;
/***********************************************
 * TYPEDEF DECLARATION
 **********************************************/
typedef void (*pwm_cb_t) (void* param);


/**
 * \struct pwm_ctrl
 * \brief the structure of PWM control
 */
typedef struct pwm_ctrl_s{
    uint8_t  continus;
    uint8_t  inverse;
    uint8_t  duty;          /**< Range : 1~100 */
    uint32_t freq;          /**< Programmed Frequency 0.045Hz~1.5MHz */
    uint32_t count;
}pwm_ctrl, *pwm_ctrl_ptr;

/***********************************************
 * FUNCTION DECLARATION
 **********************************************/
/**
 * \brief initialize PWM
 * 
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_init(void);


/**
 * \brief de-initialize PWM 
 * 
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_deinit(void);


/**
 * \brief register PWM callback function
 * 
 * \param[in] aIndex
 * \param[in] cb_fun
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_register_cb(PWM_INDEX_E aIndex, pwm_cb_t  cb_fun);


/**
 * \brief start PWM
 * 
 * \param[in] aIndex
 * \param[in] aCtrl
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_start(PWM_INDEX_E aIndex, pwm_ctrl_ptr aCtrl);


/**
 * \brief stop PWM
 * 
 * \param[in] aIndex
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_stop(PWM_INDEX_E aIndex);


/**
 * \brief enable PWM
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_set_en(PWM_INDEX_E aIndex, uint32_t aValue);


/**
 * \brief enable PWM output mode
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_set_cont(PWM_INDEX_E aIndex, uint32_t aValue);


/**
 * \brief reverse PWM phase 
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_set_inv(PWM_INDEX_E aIndex, uint32_t aValue);


/**
 * \brief set PWM cycle
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_set_cycle(PWM_INDEX_E aIndex, uint32_t aValue);


/**
 * \brief set PWM duty
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_set_duty(PWM_INDEX_E aIndex, uint32_t aValue);


/**
 * \brief set PWM pulse width
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_set_cnt(PWM_INDEX_E aIndex, uint32_t aValue);


/**
 * \brief set PWM debug selection
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_set_dbgsel(PWM_INDEX_E aIndex, uint32_t aValue);


/**
 * \brief clear PWM interrupt
 * 
 * \param[in] aIndex
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_set_intclr(PWM_INDEX_E aIndex);


/**
 * \brief get PWM cycle
 * 
 * \param[in] aIndex
 * \param[out] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_get_cycle(PWM_INDEX_E aIndex, uint32_t *aValue);


/**
 * \brief get PWM high level beats
 * 
 * \param[in] aIndex
 * \param[out] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_get_hlbeat(PWM_INDEX_E aIndex, uint32_t *aValue);


/**
 * \brief  get PWM period
 * 
 * \param[in] aIndex
 * \param[out] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_get_period(PWM_INDEX_E aIndex, uint32_t *aValue);


/**
 * \brief get PWM working status
 * 
 * \param[in] aIndex
 * \param[out] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_get_busy(PWM_INDEX_E aIndex, uint32_t *aValue);


/**
 * \brief get PWM output mode
 * 
 * \param[in] aIndex
 * \param[out] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_get_keep(PWM_INDEX_E aIndex, uint32_t *aValue);


/**
 * \brief get PWM count
 * 
 * \param[in] aIndex
 * \param[out] aValue
 * \return PWM_ERROR_E
 */
PWM_ERROR_E hx_drv_pwm_get_cnt(PWM_INDEX_E aIndex, uint32_t *aValue);

#endif /* INC_HX_DRV_PWM_H_ */

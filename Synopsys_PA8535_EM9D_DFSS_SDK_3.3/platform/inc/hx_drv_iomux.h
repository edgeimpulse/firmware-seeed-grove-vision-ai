/**
 * @file hx_drv_iomux.h
 * @author himax/902452
 * @brief 
 * @version V1.0.0
 * @date 2018-12-06
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef PLATFORM_INC_HX_DRV_IOMUX_H_
#define PLATFORM_INC_HX_DRV_IOMUX_H_

#include "embARC_toolchain.h"


/***********************************************
 * CONSTANT DEFINITION
 **********************************************/
/**
 * \brief   contains definitions of IO enable/disable
 * 
 */
#define IO_EN                       1
#define IO_DIS                      0


/**
 * \brief   GPIO MUX Selection
 * 
 */
#define IO_MUX_SEL_0                0
#define IO_MUX_SEL_1                1
#define IO_MUX_SEL_2                2
#define IO_MUX_SEL_3                3


/**
 * \brief   GPIO Output Value
 * 
 */
#define IO_OUT_HIGH                 1
#define IO_OUT_LOW                  0
/***********************************************
 * EMULATOR DECLARATION
 **********************************************/
/**
 * \enum IOMUX_ERROR_E
 * \brief IOMUX Errors Type
 */
typedef enum IOMUX_ERROR_S
{
    IOMUX_NO_ERROR                          = 0,    /**< No ERROR */
    IOMUX_ERROR_NOT_INIT                    = 1,    /**< ERROR MSG: not init */
    IOMUX_ERROR_ALREADY_INIT                = 2,    /**< ERROR MSG: already init */
    IOMUX_ERROR_INVALID_PARAMETERS          = 3,    /**< ERROR MSG: Invalid parameters */
    IOMUX_ERROR_NULL_POINTER                = 4,    /**< ERROR MSG: NULL pointer */
    IOMUX_UNKNOWN_ERROR                     = 5,    /**< ERROR MSG: UNKNOWN ERROR*/
} IOMUX_ERROR_E;


/**
 * \enum IOMUX_INDEX_E
 * \brief IOMUX GPIO
 */ 
typedef enum IOMUX_INDEX_S
{
    IOMUX_PGPIO0 = 0,
    IOMUX_PGPIO1,
    IOMUX_PGPIO2,
    IOMUX_PGPIO3,
    IOMUX_PGPIO4,
    IOMUX_PGPIO5,
    IOMUX_PGPIO6,
    IOMUX_PGPIO7,
    IOMUX_PGPIO8,
    IOMUX_PGPIO9,
    IOMUX_PGPIO10,
    IOMUX_PGPIO11,
    IOMUX_PGPIO12,
    IOMUX_PGPIO13,
    IOMUX_PGPIO14,
    IOMUX_RESERVED,  // reserved
    IOMUX_SGPIO0 = 16,
    IOMUX_SGPIO1
}__attribute__((packed)) IOMUX_INDEX_E;

/**
 * \enum IOMUX_DIRECTION_S
 * \brief IO Direction 
 */ 
typedef enum IOMUX_DIRECTION_S
{
    IOMUX_DIR_RES0 = 0,     /* Reserved */
    IOMUX_DIR_RES1,         /* Reserved */
    IOMUX_DIR_INPUT,        /* Input */
    IOMUX_DIR_OUTPUT,       /* Output */
}IOMUX_DIRECTION_E;


/**
 * \enum PERI_INDEX_E
 * \brief Peripheral 
 */ 
typedef enum PERI_INDEX_S
{
    PERI_ORIGNAL = 0,
    PERI_SPI_M1,
    PERI_I2C_M1,
    PERI_SPI_SLV,
    PERI_UART1_SGPIO1,
    PERI_PDM,
    PERI_BOOT_OPT,
    PERI_UART1_TX,
    PERI_SSI0_CS1,
    PERI_UART1_RX,
    PERI_PGPIO1,
}PERI_INDEX_E;

/***********************************************
 * TYPEDEF DECLARATION
 **********************************************/
typedef void (*iomux_cb_t) (void* event);


/***********************************************
 * FUNCTION DECLARATION
 **********************************************/
/**
 * \brief initialize I/O 
 * 
 * \return IOMUX_ERROR_E
 */

IOMUX_ERROR_E hx_drv_iomux_init(void);


/**
 * \brief de-initialize I/O 
 * 
 * \return IOMUX_ERROR_E
 */
IOMUX_ERROR_E hx_drv_iomux_deinit(void);


/**
 * \brief set I/O configuration
 * 
 * \param[in] aIndex
 * \param[in] aConfig              assign IO direction, refer to  IOMUX_DIRECTION_E
 * \return IOMUX_ERROR_E
 */
IOMUX_ERROR_E hx_drv_iomux_set_pmux(IOMUX_INDEX_E aIndex, uint8_t aConfig);


/**
 * \brief set output value
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return IOMUX_ERROR_E
 */
IOMUX_ERROR_E hx_drv_iomux_set_outvalue(IOMUX_INDEX_E aIndex, uint8_t aValue);


/**
 * \brief get input value
 * 
 * \param[in] aIndex
 * \param[out] aValue
 * \return IOMUX_ERROR_E
 */
IOMUX_ERROR_E hx_drv_iomux_get_invalue(IOMUX_INDEX_E aIndex, uint8_t * aValue);


/**
 * \brief register I/O callback function
 * 
 * \param[in] aIndex
 * \param[in] cb_fun
 * \return IOMUX_ERROR_E
 */
IOMUX_ERROR_E hx_drv_iomux_cb_register(IOMUX_INDEX_E aIndex, iomux_cb_t  cb_fun);


/**
 * \brief  mask I/O interrupt
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return IOMUX_ERROR_E
 */
IOMUX_ERROR_E hx_drv_iomux_set_intmask(IOMUX_INDEX_E aIndex, uint8_t aValue);


/**
 * \brief  set the polarity of I/O interrupt 
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return IOMUX_ERROR_E
 */
IOMUX_ERROR_E hx_drv_iomux_set_intpol(IOMUX_INDEX_E aIndex, uint8_t aValue);


/**
 * \brief  enable/disable I/O interrupt
 * 
 * \param[in] aIndex
 * \param[in] aValue
 * \return IOMUX_ERROR_E
 */
IOMUX_ERROR_E hx_drv_iomux_set_intenable(IOMUX_INDEX_E aIndex, uint8_t aValue);

/**
 * \brief  peripheral pin mux
 *  WE-I has 3 packages: LQFP128, QFN72, WLCSP38
 *  LQFP128: full pin assignment
 *  QFN72: 
 *         w/o I2C-M1 pin, I2C-M1 signal can mux to SPI-M1 pin        (peri = PERI_I2C_M1, PERI_SPI_M1)
 *         w/o SPI-S pin
 *             choice 1: SPI-S signal can mux to UART1 + SGPIO1 pin   (peri = PERI_SPI_SLV, PERI_UART1_SGPIO1)
 *             choice 2: SPI-S signal can mux to SPI-M1 pin           (peri = PERI_SPI_SLV, PERI_SPI_M1)
 *         w/o PDM pin, PDM signal can mux to BOOT_OPT pin            (peri = PERI_PDM, PERI_BOOT_OPT)
 * 
 *  WLCSP38:
 *         w/o I2C-M1 pin, can't mux to any pin
 *         w/o SPI-S pin
 *             choice 1: SPI-S signal can mux to UART1 + SGPIO1 pin   (peri = PERI_SPI_SLV, PERI_UART1_SGPIO1)
 *         w/o PDM pin, PDM signal can mux to BOOT_OPT pin            (peri = PERI_PDM, PERI_BOOT_OPT)
 *         w/o SSI0-CS1, that can mux to UART1_TX                     (peri = PERI_SSI0_CS1, PERI_UART1_TX)
 *         w/o PGPIO1, that can mux to UART1_RX                       (peri = PERI_PGPIO1, PERI_UART1_RX)
 * 
 * \param[in] peri
 * \param[in] mux_pin_out
 * \return IOMUX_ERROR_E
 */
IOMUX_ERROR_E hx_drv_iomux_set_func_pin_out(uint8_t peri, uint8_t mux_pin_out);

#endif /* PLATFORM_INC_HX_DRV_IOMUX_H_ */

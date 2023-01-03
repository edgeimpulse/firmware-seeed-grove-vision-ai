/**
 * @file hx_drv_iomux.c
 * @author himax/902452
 * @brief 
 * @version V1.0.0
 * @date 2018-12-06
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

/**************************************************************************************************/
/*	History
 * 	1. Initial Version (2018.12.07)
 * 	2. GPIO interrupt trigger type : edge(rising) (2019.01.21)
 * 	3. Sync GPIO register from reg_table_grp_aon_190530.xls (2019.06.06)
 **************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "arc_builtin.h"
#include "arc.h"
#include "embARC_debug.h"
#include "arc_exception.h"
#include "embARC_toolchain.h"
#include "embARC_error.h"

#include "io_config.h"
#include "io_config_ext.h"
#include "hardware_config.h"
#include "apexextensions.h"
#include "BITOPS.h"
#include "hx_drv_iomux.h"

#ifdef IO_GPIO_HMX_PRESENT
/***********************************************
 * CONSTANT DEFINITION
 **********************************************/
/** Register BIT Offset **/
#define SGPIO0_EN_OFFSET                24
#define SGPIO1_EN_OFFSET                25

#define ALL_IOPAD_CONTROL_POS           0
#define ALL_IOPAD_CONTROL_SIZE          16
#define DEFAULT_IO_DRIVING_STREN        0x02
#define DEFAULT_IO_PU_PD_CONTROL        0x00
#define DEFAULT_IO_PAD_CONTROL          (DEFAULT_IO_PU_PD_CONTROL << 8) | (DEFAULT_IO_DRIVING_STREN)

/** Maximum GPIO Number **/
#define MAX_PIO_NUM             16
#define MAX_SIO_NUM             2

#define IO_EN_WIDTH             1
#define IO_MUX_WIDTH            2

#define IO_EN_MASK              0x01
#define IO_MUX_MASK             0x03

/** IO DEFAULT SETTING **/
#define PIO0_EN_DEF         IO_EN
#define PIO1_EN_DEF         IO_EN
#define PIO2_EN_DEF         IO_EN
#define PIO3_EN_DEF         IO_EN
#define PIO4_EN_DEF         IO_EN
#define PIO5_EN_DEF         IO_EN
#define PIO6_EN_DEF         IO_EN
#define PIO7_EN_DEF         IO_EN
#define PIO8_EN_DEF         IO_EN
#define PIO9_EN_DEF         IO_EN
#define PIO10_EN_DEF        IO_EN
#define PIO11_EN_DEF        IO_EN
#define PIO12_EN_DEF        IO_EN
#define PIO13_EN_DEF        IO_EN
#define PIO14_EN_DEF        IO_EN
#define PIO15_EN_DEF        IO_EN
#define SIO0_EN_DEF         IO_EN
#define SIO1_EN_DEF         IO_EN

#define PIO0_MUX_DEF        IO_MUX_SEL_0
#define PIO1_MUX_DEF        IO_MUX_SEL_0
#define PIO2_MUX_DEF        IO_MUX_SEL_0
#define PIO3_MUX_DEF        IO_MUX_SEL_0
#define PIO4_MUX_DEF        IO_MUX_SEL_0
#define PIO5_MUX_DEF        IO_MUX_SEL_0
#define PIO6_MUX_DEF        IO_MUX_SEL_0
#define PIO7_MUX_DEF        IO_MUX_SEL_0
#define PIO8_MUX_DEF        IO_MUX_SEL_0
#define PIO9_MUX_DEF        IO_MUX_SEL_0
#define PIO10_MUX_DEF       IO_MUX_SEL_0
#define PIO11_MUX_DEF       IO_MUX_SEL_0
#define PIO12_MUX_DEF       IO_MUX_SEL_0
#define PIO13_MUX_DEF       IO_MUX_SEL_0
#define PIO14_MUX_DEF       IO_MUX_SEL_0
#define PIO15_MUX_DEF       IO_MUX_SEL_0
#define SIO0_MUX_DEF        IO_MUX_SEL_0
#define SIO1_MUX_DEF        IO_MUX_SEL_0

#define PIO0_MUX_OFFSET     0
#define PIO1_MUX_OFFSET     2
#define PIO2_MUX_OFFSET     4
#define PIO3_MUX_OFFSET     6
#define PIO4_MUX_OFFSET     8
#define PIO5_MUX_OFFSET     10
#define PIO6_MUX_OFFSET     12
#define PIO7_MUX_OFFSET     14
#define PIO8_MUX_OFFSET     16
#define PIO9_MUX_OFFSET     18
#define PIO10_MUX_OFFSET    20
#define PIO11_MUX_OFFSET    22
#define PIO12_MUX_OFFSET    24
#define PIO13_MUX_OFFSET    26
#define PIO14_MUX_OFFSET    28
#define PIO15_MUX_OFFSET    30
#define SIO0_MUX_OFFSET     16
#define SIO1_MUX_OFFSET     18

#define PIO0_OUT_DEF        IO_OUT_LOW
#define PIO1_OUT_DEF        IO_OUT_LOW
#define PIO2_OUT_DEF        IO_OUT_LOW
#define PIO3_OUT_DEF        IO_OUT_LOW
#define PIO4_OUT_DEF        IO_OUT_LOW
#define PIO5_OUT_DEF        IO_OUT_LOW
#define PIO6_OUT_DEF        IO_OUT_LOW
#define PIO7_OUT_DEF        IO_OUT_LOW
#define PIO8_OUT_DEF        IO_OUT_LOW
#define PIO9_OUT_DEF        IO_OUT_LOW
#define PIO10_OUT_DEF       IO_OUT_LOW
#define PIO11_OUT_DEF       IO_OUT_LOW
#define PIO12_OUT_DEF       IO_OUT_LOW
#define PIO13_OUT_DEF       IO_OUT_LOW
#define PIO14_OUT_DEF       IO_OUT_LOW
#define PIO15_OUT_DEF       IO_OUT_LOW
#define SIO0_OUT_DEF        IO_OUT_LOW
#define SIO1_OUT_DEF        IO_OUT_LOW

/** GPIO Default Regsiter Setting **/
#define DEFAULT_IOMUX_MUX ((PIO15_MUX_DEF << PIO15_MUX_OFFSET) | (PIO14_MUX_DEF << PIO14_MUX_OFFSET) | \
                           (PIO13_MUX_DEF << PIO13_MUX_OFFSET) | (PIO12_MUX_DEF << PIO12_MUX_OFFSET) | \
                           (PIO11_MUX_DEF << PIO11_MUX_OFFSET) | (PIO10_MUX_DEF << PIO10_MUX_OFFSET) | \
                           (PIO9_MUX_DEF << PIO9_MUX_OFFSET) | (PIO8_MUX_DEF << PIO8_MUX_OFFSET) |     \
                           (PIO7_MUX_DEF << PIO7_MUX_OFFSET) | (PIO6_MUX_DEF << PIO6_MUX_OFFSET) |     \
                           (PIO5_MUX_DEF << PIO5_MUX_OFFSET) | (PIO4_MUX_DEF << PIO4_MUX_OFFSET) |     \
                           (PIO3_MUX_DEF << PIO3_MUX_OFFSET) | (PIO2_MUX_DEF << PIO2_MUX_OFFSET) |     \
                           (PIO1_MUX_DEF << PIO1_MUX_OFFSET) | (PIO0_MUX_DEF << PIO0_MUX_OFFSET))

#define DEFAULT_IOMUX_OUT ((SIO1_OUT_DEF << IOMUX_SGPIO1) | (SIO0_OUT_DEF << IOMUX_SGPIO0) |     \
                           (PIO15_OUT_DEF << IOMUX_RESERVED) | (PIO14_OUT_DEF << IOMUX_PGPIO14) | \
                           (PIO13_OUT_DEF << IOMUX_PGPIO13) | (PIO12_OUT_DEF << IOMUX_PGPIO12) | \
                           (PIO11_OUT_DEF << IOMUX_PGPIO11) | (PIO10_OUT_DEF << IOMUX_PGPIO10) | \
                           (PIO9_OUT_DEF << IOMUX_PGPIO9) | (PIO8_OUT_DEF << IOMUX_PGPIO8) |     \
                           (PIO7_OUT_DEF << IOMUX_PGPIO7) | (PIO6_OUT_DEF << IOMUX_PGPIO6) |     \
                           (PIO5_OUT_DEF << IOMUX_PGPIO5) | (PIO4_OUT_DEF << IOMUX_PGPIO4) |     \
                           (PIO3_OUT_DEF << IOMUX_PGPIO3) | (PIO2_OUT_DEF << IOMUX_PGPIO2) |     \
                           (PIO1_OUT_DEF << IOMUX_PGPIO1) | (PIO0_OUT_DEF << IOMUX_PGPIO0))

/***********************************************
 * MACRO/INLINE DECLARATION
 **********************************************/
/**
 * \brief	IOMUX register structure
 * \details	Detailed structure description of IOMUX
 *	block   register information, implementation of IOMUX
 */
typedef volatile struct iomux_reg_s
{
    uint32_t io_pad_ctrl; /*!< (0x00) : io pad ctrl address*/
    uint32_t io_mux;      /*!< (0x04) : io mux setting address*/
    uint32_t out_value;   /*!< (0x08) : io output value  address*/
    uint32_t in_sataus;   /*!< (0x0C) : io input status address*/
    uint32_t reserved;    /*!< (0x10) : reserved address*/
    uint32_t io_mux1;     /*!< (0x14) : io mux setting address*/
} IOMUX_REG, *IOMUX_REG_PTR;

typedef volatile struct iomux_reg1_s
{
    uint32_t gpi_pol;      /*!< (0x00) : io input polarity (0: default; 1: inverse)*/
    uint32_t gpi_int_mask; /*!< (0x04) : io interrupt mask (0: non-mask, 1: mask)*/
} IOMUX_REG1, *IOMUX_REG1_PTR;

/** GPIO configuration **/
typedef struct io_cfg_s
{
    uint8_t en;
    uint8_t mux;
    uint8_t ovalue;
    uint8_t reserved;
    iomux_cb_t cb;
} io_cfg_t;

/***********************************************
 * GLOBAL VARIABLE
 **********************************************/
static uint8_t g_iomux_init = false;

/** Store all of PIF GPIO configuration **/
io_cfg_t iomux_cfg[MAX_PIO_NUM + MAX_SIO_NUM] = {
    {PIO0_EN_DEF, PIO0_MUX_DEF, PIO0_OUT_DEF, 0, NULL},    // PGPIO0
    {PIO1_EN_DEF, PIO1_MUX_DEF, PIO1_OUT_DEF, 0, NULL},    // PGPIO1
    {PIO2_EN_DEF, PIO2_MUX_DEF, PIO2_OUT_DEF, 0, NULL},    // PGPIO2
    {PIO3_EN_DEF, PIO3_MUX_DEF, PIO3_OUT_DEF, 0, NULL},    // PGPIO3
    {PIO4_EN_DEF, PIO4_MUX_DEF, PIO4_OUT_DEF, 0, NULL},    // PGPIO4
    {PIO5_EN_DEF, PIO5_MUX_DEF, PIO5_OUT_DEF, 0, NULL},    // PGPIO5
    {PIO6_EN_DEF, PIO6_MUX_DEF, PIO6_OUT_DEF, 0, NULL},    // PGPIO6
    {PIO7_EN_DEF, PIO7_MUX_DEF, PIO7_OUT_DEF, 0, NULL},    // PGPIO7
    {PIO8_EN_DEF, PIO8_MUX_DEF, PIO8_OUT_DEF, 0, NULL},    // PGPIO8
    {PIO9_EN_DEF, PIO9_MUX_DEF, PIO9_OUT_DEF, 0, NULL},    // PGPIO9
    {PIO10_EN_DEF, PIO10_MUX_DEF, PIO10_OUT_DEF, 0, NULL}, // PGPIO10
    {PIO11_EN_DEF, PIO11_MUX_DEF, PIO11_OUT_DEF, 0, NULL}, // PGPIO11
    {PIO12_EN_DEF, PIO12_MUX_DEF, PIO12_OUT_DEF, 0, NULL}, // PGPIO12
    {PIO13_EN_DEF, PIO13_MUX_DEF, PIO13_OUT_DEF, 0, NULL}, // PGPIO13
    {PIO14_EN_DEF, PIO14_MUX_DEF, PIO14_OUT_DEF, 0, NULL}, // PGPIO14
    {PIO15_EN_DEF, PIO15_MUX_DEF, PIO15_OUT_DEF, 0, NULL}, // IOMUX_RESERVED
    {SIO0_EN_DEF, SIO0_MUX_DEF, SIO0_OUT_DEF, 0, NULL},    // SGPIO1
    {SIO1_EN_DEF, SIO1_MUX_DEF, SIO1_OUT_DEF, 0, NULL}     // SGPIO2
};

/***********************************************
 * GLOBAL/EXTERN VARIABLE DECLARATION
 **********************************************/
/** IOMUX Base Address Pointer **/
IOMUX_REG *iomux_reg_ptr = (IOMUX_REG *)(HW_GPIO_BASE_ADDR);
IOMUX_REG1 *iomux_reg1_ptr = (IOMUX_REG1 *)(HW_GPIO_BASE_ADDR1);

/***********************************************
 * FUNCTION IMPLEMENTATION
 **********************************************/
#ifdef IO_GPIO_HMX_PGPIO00
static void iomux_isr_pgpio0(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO0].cb)
        iomux_cfg[IOMUX_PGPIO0].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO01
static void iomux_isr_pgpio1(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO1].cb)
        iomux_cfg[IOMUX_PGPIO1].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO02
static void iomux_isr_pgpio2(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO2].cb)
        iomux_cfg[IOMUX_PGPIO2].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO03
static void iomux_isr_pgpio3(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO3].cb)
        iomux_cfg[IOMUX_PGPIO3].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO04
static void iomux_isr_pgpio4(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO4].cb)
        iomux_cfg[IOMUX_PGPIO4].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO05
static void iomux_isr_pgpio5(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO5].cb)
        iomux_cfg[IOMUX_PGPIO5].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO06
static void iomux_isr_pgpio6(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO6].cb)
        iomux_cfg[IOMUX_PGPIO6].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO07
static void iomux_isr_pgpio7(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO7].cb)
        iomux_cfg[IOMUX_PGPIO7].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO08
static void iomux_isr_pgpio8(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO8].cb)
        iomux_cfg[IOMUX_PGPIO8].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO09
static void iomux_isr_pgpio9(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO9].cb)
        iomux_cfg[IOMUX_PGPIO9].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO10
static void iomux_isr_pgpio10(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO10].cb)
        iomux_cfg[IOMUX_PGPIO10].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO11
static void iomux_isr_pgpio11(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO11].cb)
        iomux_cfg[IOMUX_PGPIO11].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO12
static void iomux_isr_pgpio12(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO12].cb)
        iomux_cfg[IOMUX_PGPIO12].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO13
static void iomux_isr_pgpio13(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO13].cb)
        iomux_cfg[IOMUX_PGPIO13].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_PGPIO14
static void iomux_isr_pgpio14(void *ptr)
{
    if (iomux_cfg[IOMUX_PGPIO14].cb)
        iomux_cfg[IOMUX_PGPIO14].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_SGPIO00
static void iomux_isr_sgpio0(void *ptr)
{
    if (iomux_cfg[IOMUX_SGPIO0].cb)
        iomux_cfg[IOMUX_SGPIO0].cb(ptr);
}
#endif
#ifdef IO_GPIO_HMX_SGPIO01
static void iomux_isr_sgpio1(void *ptr)
{
    if (iomux_cfg[IOMUX_SGPIO1].cb)
        iomux_cfg[IOMUX_SGPIO1].cb(ptr);
}
#endif
IOMUX_ERROR_E hx_drv_iomux_cb_register(IOMUX_INDEX_E aIndex, iomux_cb_t cb_fun)
{
    if (cb_fun == NULL)
        return IOMUX_ERROR_NULL_POINTER;

    iomux_cfg[aIndex].cb = cb_fun;

    return IOMUX_NO_ERROR;
}

IOMUX_ERROR_E hx_drv_iomux_init(void)
{
    if (g_iomux_init == false)
    {
        /** Configure IOMUX with default setting */
        //HX_BIT_SET(iomux_reg_ptr->io_pad_ctrl, ALL_IOPAD_CONTROL_SIZE, ALL_IOPAD_CONTROL_POS, DEFAULT_IO_PAD_CONTROL);
        //iomux_reg_ptr->io_mux = DEFAULT_IOMUX_MUX;
       // iomux_reg_ptr->out_value = DEFAULT_IOMUX_OUT;

        /* enable all of interrupt **/
#ifdef IO_GPIO_HMX_PGPIO00
        int_disable(IO_GPIO_HMX_PGPIO00); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO00, iomux_isr_pgpio0);
        int_level_config(IO_GPIO_HMX_PGPIO00, 1);
        //int_enable(IO_GPIO_HMX_PGPIO00);
#endif

#ifdef IO_GPIO_HMX_PGPIO01
        int_disable(IO_GPIO_HMX_PGPIO01); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO01, iomux_isr_pgpio1);
        int_level_config(IO_GPIO_HMX_PGPIO01, 1);
        //int_enable(IO_GPIO_HMX_PGPIO01);
#endif

#ifdef IO_GPIO_HMX_PGPIO02
        int_disable(IO_GPIO_HMX_PGPIO02); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO02, iomux_isr_pgpio2);
        int_level_config(IO_GPIO_HMX_PGPIO02, 1);
        //int_enable(IO_GPIO_HMX_PGPIO02);
#endif

#ifdef IO_GPIO_HMX_PGPIO03
        int_disable(IO_GPIO_HMX_PGPIO03); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO03, iomux_isr_pgpio3);
        int_level_config(IO_GPIO_HMX_PGPIO03, 1);
        //int_enable(IO_GPIO_HMX_PGPIO03);
#endif

#ifdef IO_GPIO_HMX_PGPIO04
        int_disable(IO_GPIO_HMX_PGPIO04); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO04, iomux_isr_pgpio4);
        int_level_config(IO_GPIO_HMX_PGPIO04, 1);
        //int_enable(IO_GPIO_HMX_PGPIO04);
#endif
#ifdef IO_GPIO_HMX_PGPIO05
        int_disable(IO_GPIO_HMX_PGPIO05); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO05, iomux_isr_pgpio5);
        int_level_config(IO_GPIO_HMX_PGPIO05, 1);
        //int_enable(IO_GPIO_HMX_PGPIO05);
#endif
#ifdef IO_GPIO_HMX_PGPIO06
        int_disable(IO_GPIO_HMX_PGPIO06); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO06, iomux_isr_pgpio6);
        int_level_config(IO_GPIO_HMX_PGPIO06, 1);
        //int_enable(IO_GPIO_HMX_PGPIO06);
#endif
#ifdef IO_GPIO_HMX_PGPIO07
        int_disable(IO_GPIO_HMX_PGPIO07); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO07, iomux_isr_pgpio7);
        int_level_config(IO_GPIO_HMX_PGPIO07, 1);
        //int_enable(IO_GPIO_HMX_PGPIO07);
#endif
#ifdef IO_GPIO_HMX_PGPIO08
        int_disable(IO_GPIO_HMX_PGPIO08); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO08, iomux_isr_pgpio8);
        int_level_config(IO_GPIO_HMX_PGPIO08, 1);
        //int_enable(IO_GPIO_HMX_PGPIO08);
#endif
#ifdef IO_GPIO_HMX_PGPIO09
        int_disable(IO_GPIO_HMX_PGPIO09); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO09, iomux_isr_pgpio9);
        int_level_config(IO_GPIO_HMX_PGPIO09, 1);
        //int_enable(IO_GPIO_HMX_PGPIO09);
#endif
#ifdef IO_GPIO_HMX_PGPIO10
        int_disable(IO_GPIO_HMX_PGPIO10); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO10, iomux_isr_pgpio10);
        int_level_config(IO_GPIO_HMX_PGPIO10, 1);
        //int_enable(IO_GPIO_HMX_PGPIO10);
#endif
#ifdef IO_GPIO_HMX_PGPIO11
        int_disable(IO_GPIO_HMX_PGPIO11); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO11, iomux_isr_pgpio11);
        int_level_config(IO_GPIO_HMX_PGPIO11, 1);
        //int_enable(IO_GPIO_HMX_PGPIO11);
#endif
#ifdef IO_GPIO_HMX_PGPIO12
        int_disable(IO_GPIO_HMX_PGPIO12); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO12, iomux_isr_pgpio12);
        int_level_config(IO_GPIO_HMX_PGPIO12, 1);
        //int_enable(IO_GPIO_HMX_PGPIO3);
#endif
#ifdef IO_GPIO_HMX_PGPIO13
        int_disable(IO_GPIO_HMX_PGPIO13); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO13, iomux_isr_pgpio13);
        int_level_config(IO_GPIO_HMX_PGPIO13, 1);
        //int_enable(IO_GPIO_HMX_PGPIO13);
#endif
#ifdef IO_GPIO_HMX_PGPIO14
        int_disable(IO_GPIO_HMX_PGPIO14); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_PGPIO14, iomux_isr_pgpio14);
        int_level_config(IO_GPIO_HMX_PGPIO14, 1);
        //int_enable(IO_GPIO_HMX_PGPIO14);
#endif
#ifdef IO_GPIO_HMX_SGPIO00
        int_disable(IO_GPIO_HMX_SGPIO00); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_SGPIO00, iomux_isr_sgpio0);
        int_level_config(IO_GPIO_HMX_SGPIO00, 1);
        //int_enable(IO_GPIO_HMX_SGPIO00);
#endif
#ifdef IO_GPIO_HMX_SGPIO01
        int_disable(IO_GPIO_HMX_SGPIO01); /* disable first then enable */
        int_handler_install(IO_GPIO_HMX_SGPIO01, iomux_isr_sgpio1);
        int_level_config(IO_GPIO_HMX_SGPIO01, 1);
        //int_enable(IO_GPIO_HMX_SGPIO01);
#endif
        g_iomux_init = true;
    }
    else
    {
        return IOMUX_ERROR_ALREADY_INIT;
    }

    return IOMUX_NO_ERROR;
}

IOMUX_ERROR_E hx_drv_iomux_deinit(void)
{
    g_iomux_init = false;
#if 0
    HX_BIT_SET(iomux_reg_ptr->io_pad_ctrl, ALL_IOPAD_CONTROL_SIZE, ALL_IOPAD_CONTROL_POS, DEFAULT_IO_PAD_CONTROL);
    iomux_reg_ptr->io_mux = DEFAULT_IOMUX_MUX;
    iomux_reg_ptr->out_value = DEFAULT_IOMUX_OUT;

    /*disable INTC and clear isr*/
#ifdef IO_GPIO_HMX_PGPIO00
    int_disable(IO_GPIO_HMX_PGPIO00); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO01
    int_disable(IO_GPIO_HMX_PGPIO01); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO02
    int_disable(IO_GPIO_HMX_PGPIO02); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO03
    int_disable(IO_GPIO_HMX_PGPIO03); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO04
    int_disable(IO_GPIO_HMX_PGPIO04); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO05
    int_disable(IO_GPIO_HMX_PGPIO05); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO06
    int_disable(IO_GPIO_HMX_PGPIO06); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO07
    int_disable(IO_GPIO_HMX_PGPIO07); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO08
    int_disable(IO_GPIO_HMX_PGPIO08); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO09
    int_disable(IO_GPIO_HMX_PGPIO09); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO10
    int_disable(IO_GPIO_HMX_PGPIO10); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO11
    int_disable(IO_GPIO_HMX_PGPIO11); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO12
    int_disable(IO_GPIO_HMX_PGPIO12); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO13
    int_disable(IO_GPIO_HMX_PGPIO13); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_PGPIO14
    int_disable(IO_GPIO_HMX_PGPIO14); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_SGPIO00
    int_disable(IO_GPIO_HMX_SGPIO00); /* disable first then enable */
#endif
#ifdef IO_GPIO_HMX_SGPIO01
    int_disable(IO_GPIO_HMX_SGPIO01); /* disable first then enable */
#endif
#endif
    return IOMUX_NO_ERROR;
}

IOMUX_ERROR_E hx_drv_iomux_set_pmux(IOMUX_INDEX_E aIndex, uint8_t aConfig)
{
    uint32_t pos = 0;

    if (g_iomux_init == false)
        return IOMUX_ERROR_NOT_INIT;

    if (aIndex < IOMUX_RESERVED)
    {
        pos = aIndex << 1;
        HX_BIT_SET(iomux_reg_ptr->io_mux, 2, pos, aConfig);
    }
    else if(aIndex == IOMUX_RESERVED)
    {
       /*TODO*/
    }
    else
    {
        pos = (aIndex - IOMUX_SGPIO0) << 1;
        HX_BIT_SET(iomux_reg_ptr->io_mux1, 2, pos, aConfig);
    }

    return IOMUX_NO_ERROR;
}

IOMUX_ERROR_E hx_drv_iomux_set_outvalue(IOMUX_INDEX_E aIndex, uint8_t aValue)
{
    if (g_iomux_init == false)
        return IOMUX_ERROR_NOT_INIT;

    if (aIndex <= IOMUX_SGPIO1)
        HX_BIT_SET(iomux_reg_ptr->out_value, 1, aIndex, aValue);
    else
        return IOMUX_ERROR_INVALID_PARAMETERS;

    return IOMUX_NO_ERROR;
}

IOMUX_ERROR_E hx_drv_iomux_get_invalue(IOMUX_INDEX_E aIndex, uint8_t *aValue)
{
    if (g_iomux_init == false)
        return IOMUX_ERROR_NOT_INIT;

    if (aValue == NULL)
        return IOMUX_ERROR_NULL_POINTER;

    if (aIndex <= IOMUX_SGPIO1)
        *aValue = HX_BIT_GET(iomux_reg_ptr->in_sataus, 1, aIndex);
    else
        return IOMUX_ERROR_INVALID_PARAMETERS;

    return IOMUX_NO_ERROR;
}

IOMUX_ERROR_E hx_drv_iomux_set_intmask(IOMUX_INDEX_E aIndex, uint8_t aValue)
{
    if (g_iomux_init == false)
        return IOMUX_ERROR_NOT_INIT;

    if (aIndex <= IOMUX_SGPIO1)
        HX_BIT_SET(iomux_reg1_ptr->gpi_int_mask, 1, aIndex, aValue);
    else
        return IOMUX_ERROR_INVALID_PARAMETERS;

    return IOMUX_NO_ERROR;
}

IOMUX_ERROR_E hx_drv_iomux_set_intpol(IOMUX_INDEX_E aIndex, uint8_t aValue)
{
    if (g_iomux_init == false)
        return IOMUX_ERROR_NOT_INIT;

    if (aIndex <= IOMUX_SGPIO1)
        HX_BIT_SET(iomux_reg1_ptr->gpi_pol, 1, aIndex, aValue);
    else
        return IOMUX_ERROR_INVALID_PARAMETERS;

    return IOMUX_NO_ERROR;
}

IOMUX_ERROR_E hx_drv_iomux_set_intenable(IOMUX_INDEX_E aIndex, uint8_t aValue)
{
    uint32_t irq_no = -1;

    if (g_iomux_init == false)
        return IOMUX_ERROR_NOT_INIT;

    switch (aIndex)
    {
    case IOMUX_PGPIO0:
        irq_no = WEI_IRQ_ID_PGPIO00;
        break;
    case IOMUX_PGPIO1:
        irq_no = WEI_IRQ_ID_PGPIO01;
        break;
    case IOMUX_PGPIO2:
        irq_no = WEI_IRQ_ID_PGPIO02;
        break;
    case IOMUX_PGPIO3:
        irq_no = WEI_IRQ_ID_PGPIO03;
        break;
    case IOMUX_PGPIO4:
        irq_no = WEI_IRQ_ID_PGPIO04;
        break;
    case IOMUX_PGPIO5:
        irq_no = WEI_IRQ_ID_PGPIO05;
        break;
    case IOMUX_PGPIO6:
        irq_no = WEI_IRQ_ID_PGPIO06;
        break;
    case IOMUX_PGPIO7:
        irq_no = WEI_IRQ_ID_PGPIO07;
        break;
    case IOMUX_PGPIO8:
        irq_no = WEI_IRQ_ID_PGPIO08;
        break;
    case IOMUX_PGPIO9:
        irq_no = WEI_IRQ_ID_PGPIO09;
        break;
    case IOMUX_PGPIO10:
        irq_no = WEI_IRQ_ID_PGPIO10;
        break;
    case IOMUX_PGPIO11:
        irq_no = WEI_IRQ_ID_PGPIO11;
        break;
    case IOMUX_PGPIO12:
        irq_no = WEI_IRQ_ID_PGPIO12;
        break;
    case IOMUX_PGPIO13:
        irq_no = WEI_IRQ_ID_PGPIO13;
        break;
    case IOMUX_PGPIO14:
        irq_no = WEI_IRQ_ID_PGPIO14;
        break;
    case IOMUX_SGPIO0:
        irq_no = WEI_IRQ_ID_SGPIO00;
        break;
    case IOMUX_SGPIO1:
        irq_no = WEI_IRQ_ID_SGPIO01;
        break;
    default:
            irq_no = -1;
            break;
    }

    if(irq_no == -1)
    {
        return IOMUX_ERROR_INVALID_PARAMETERS;
    }
    else
    {
        if (aValue)
        {
            int_enable(irq_no);
        }
        else
        {
            int_disable(irq_no);
        }
        return IOMUX_NO_ERROR;
    }
}
#endif

IOMUX_ERROR_E hx_drv_iomux_set_func_pin_out(uint8_t peri, uint8_t mux_pin_out)
{
    #define SHARE_PIN_MUX1_ADDR         0xB0000044
        /* 
            0: mux to PDM
            1: mux to PAD_BOOT_OPT
        */
        #define PDM_MUX_BIT_POS         7
        #define PDM_MUX_BIT_SIZE        1

        /*
            0: mux to UART1
            1: mux to JTAG
        */         
        #define UART1_MUX_BIT_POS       8
        #define UART1_MUX_BIT_SIZE      1

        /*
            0: mux to SPI_M1
            1: mux to debug bus
            2: mux to SPI_SLV + I2C_M1
        */        
        #define SPI_M1_MUX_BIT_POS      9
        #define SPI_M1_MUX_BIT_SIZE     2

        /*
            0: mux to SPI_SLV
            1: 
            SPI_SLV_CSN mux to SGPIO1
            SPI_SLV_CLK mux to UART1_RX
            SPI_SLV_SDO mux to UART1_TX
        */
        #define SPI_SLV_MUX_BIT_POS    11
        #define SPI_SLV_MUX_BIT_SIZE    1
    
    #define SHARE_PGPIO_MUX_ADDR      0xB0000034
        /* 
            0: disable mux
            1: UART1_TX mux to SSI0_CS1
               UART1_RX mux to PGPIO1
        */
        #define UART1_TX_RX_MUX_BIT_POS       30
        #define UART1_TX_RX_MUX_BIT_SIZE      1


    uint32_t pin_mux_addr = SHARE_PIN_MUX1_ADDR;
    uint32_t pin_mux_val = 0;
    uint32_t ret = IOMUX_NO_ERROR;

    pin_mux_val = _arc_read_uncached_32((void*) pin_mux_addr);

    if(peri == PERI_PDM)
    {
        if(mux_pin_out == PERI_ORIGNAL)
        {
            HX_BIT_SET(pin_mux_val, PDM_MUX_BIT_SIZE, PDM_MUX_BIT_POS, 0);
        }
        else if(mux_pin_out == PERI_BOOT_OPT)
        {
            HX_BIT_SET(pin_mux_val, PDM_MUX_BIT_SIZE, PDM_MUX_BIT_POS, 1);
        }
        else
        {
            ret = IOMUX_ERROR_INVALID_PARAMETERS;
        }
    }
    else if(peri == PERI_I2C_M1)
    {
        if(mux_pin_out == PERI_ORIGNAL)
        {
            /* Notice: Maybe SPI_SLV mux to SPI_M1 is used */
            HX_BIT_SET(pin_mux_val, SPI_M1_MUX_BIT_SIZE, SPI_M1_MUX_BIT_POS, 0);
        }
        else if(mux_pin_out == PERI_SPI_M1)
        {
            HX_BIT_SET(pin_mux_val, SPI_M1_MUX_BIT_SIZE, SPI_M1_MUX_BIT_POS, 2);
        }
        else
        {
            ret = IOMUX_ERROR_INVALID_PARAMETERS;
        }
    }
    else if(peri == PERI_SPI_SLV)
    {
        if(mux_pin_out == PERI_ORIGNAL)
        {
            HX_BIT_SET(pin_mux_val, SPI_SLV_MUX_BIT_SIZE, SPI_SLV_MUX_BIT_POS, 0);

            /* Notice: Maybe I2C_M1 mux to SPI_M1 is used */
            HX_BIT_SET(pin_mux_val, SPI_M1_MUX_BIT_SIZE, SPI_M1_MUX_BIT_POS, 0);
        }    
        else if(mux_pin_out == PERI_SPI_M1)
        {
            HX_BIT_SET(pin_mux_val, SPI_M1_MUX_BIT_SIZE, SPI_M1_MUX_BIT_POS, 2);
            HX_BIT_SET(pin_mux_val, SPI_SLV_MUX_BIT_SIZE, SPI_SLV_MUX_BIT_POS, 0);
        }
        else if(mux_pin_out == PERI_UART1_SGPIO1)
        {
            /* set SGPIO1 input mode */
            #if 0
            /* need read register then set bit11 high */
            hx_drv_iomux_set_pmux(IOMUX_SGPIO1, 2);
            #else
            HX_BIT_SET(pin_mux_val, 2, 2, 2);
            #endif

            HX_BIT_SET(pin_mux_val, SPI_SLV_MUX_BIT_SIZE, SPI_SLV_MUX_BIT_POS, 1);

            /* maybe I2C_M1 mux to SPI_M1 is used */
            // HX_BIT_SET(pin_mux_val, SPI_M1_MUX_BIT_SIZE, SPI_M1_MUX_BIT_POS, 0);
        }
        else
        {
            ret = IOMUX_ERROR_INVALID_PARAMETERS;
        }
    }    
    else if(peri == PERI_SPI_M1)
    {
        if(mux_pin_out == PERI_ORIGNAL)
        {
            HX_BIT_SET(pin_mux_val, SPI_M1_MUX_BIT_SIZE, SPI_M1_MUX_BIT_POS, 0);
        }
        else
        {
            ret = IOMUX_ERROR_INVALID_PARAMETERS;
        }
    }
    else if(peri == PERI_SSI0_CS1)
    {
        pin_mux_addr = SHARE_PGPIO_MUX_ADDR;
        pin_mux_val = _arc_read_uncached_32((void*) pin_mux_addr);

        if(mux_pin_out == PERI_ORIGNAL)
        {
            HX_BIT_SET(pin_mux_val, UART1_TX_RX_MUX_BIT_SIZE, UART1_TX_RX_MUX_BIT_POS, 0);
        }
        else if(mux_pin_out == PERI_UART1_TX)
        {
            HX_BIT_SET(pin_mux_val, UART1_TX_RX_MUX_BIT_SIZE, UART1_TX_RX_MUX_BIT_POS, 1);
        }
        else
        {
            ret = IOMUX_ERROR_INVALID_PARAMETERS;
        }
    }
    else if(peri == PERI_PGPIO1)
    {
        pin_mux_addr = SHARE_PGPIO_MUX_ADDR;
        pin_mux_val = _arc_read_uncached_32((void*) pin_mux_addr);

        if(mux_pin_out == PERI_ORIGNAL)
        {
            HX_BIT_SET(pin_mux_val, UART1_TX_RX_MUX_BIT_SIZE, UART1_TX_RX_MUX_BIT_POS, 0);
        }
        else if(mux_pin_out == PERI_UART1_RX)
        {
            HX_BIT_SET(pin_mux_val, UART1_TX_RX_MUX_BIT_SIZE, UART1_TX_RX_MUX_BIT_POS, 1);
        }
        else
        {
            ret = IOMUX_ERROR_INVALID_PARAMETERS;
        }
    }    
    else
    {
        ret = IOMUX_ERROR_INVALID_PARAMETERS;
    }

    _arc_write_uncached_32((void *)pin_mux_addr, pin_mux_val);
    return ret;
}    


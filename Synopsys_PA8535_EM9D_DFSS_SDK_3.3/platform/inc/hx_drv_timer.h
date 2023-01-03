/**
 * @file hx_drv_timer.h
 * @author himax/902452
 * @brief 
 * @version V1.0.0
 * @date 2018-10-24
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef PLATFORM_SYS_TIMER_HX_DRV_TIMER_H_
#define PLATFORM_SYS_TIMER_HX_DRV_TIMER_H_

#include "embARC_toolchain.h"

#ifdef __cplusplus
extern "C" {
#endif


extern volatile uint64_t gl_sys_hz_cnt;
extern volatile uint32_t gl_sys_ms_cnt;

/***********************************************
 * STRUNCTURE/EMULATOR DECLARATION
 **********************************************/
/**
 * \struct TIMER_T
 * \brief Timer configuration 
 */
typedef struct TIMER_S
{
    void (*function)(void *);   /**< callback function */
    unsigned int timeout;       /**< unit: 100 ms */
    void *data;
    bool one_shot;              /**< one shot or no */
} TIMER_T;

typedef void(*timer_func_t)(void *data);


/***********************************************
 * FUNCTION DECLARATION
 **********************************************/
/**
 * \brief timer initialization
 * 
 */
extern void hx_drv_timer_init(void);


/**
 * \brief timer de-initialization
 * 
 */
extern void hx_drv_timer_deinit(void);


/**
 * \brief start one system timer to monitor by user define's TIMER_T
 * 
 * \param[in] mytimer - a pointer which point to TIMER_T structure
 * \return int  0 - success to allocate one system timer slot
 *             -1 - fail to allocate one system timer slot
 */
extern int hx_drv_timer_start(TIMER_T *mytimer);

/**
 * \brief stop specific system timer to monitor by user define's TIMER_T
 * 
 * \param[in] mytimer - a pointer which point to TIMER_T structure
 * \return int  0 - success to stop the system timer slot
 *             -1 - fail to stop one system timer slot
 */
extern int hx_drv_timer_stop(TIMER_T *mytimer);

/**
 * \brief Function get max tick count which use SYS_TIMER
 * 
 * \param[out] max_tick - max tick count value
 */
extern void hx_drv_timer_sys_maxtick(uint32_t *max_tick);


/**
 * \brief Function get current tick count value which use SYS_TIMER
 * 
 * \return uint64_t - current tick count value
 */
extern uint64_t board_get_hwticks(void);


/**
 * \brief Function get current us value which use SYS_TIMER
 * 
 * \return uint64_t current us value
 */
extern uint64_t board_get_cur_us(void);


/**
 * \brief Function busy loop to wait for us delay time which use STD_TIMER
 *        (Note : function use interrupt to count. So, should not be call in ISR)
 * 
 * \param[in] us - us to delay
 */
extern void board_delay_us(uint32_t us);


/**
 * \brief Function busy loop to wait for ms delay time which use STD_TIMER
 *        (Note : function use interrupt to count. So, should not be call in ISR)
 * 
 * \param[in] ms - ms to delay
 */
extern void board_delay_ms(uint32_t ms);


/**
 * \brief Function busy loop to wait for tich count delay time which use STD_TIMER
 * 
 * \param[in] tick - cpu tick count
 */
extern void board_delay_cycle(uint32_t tick);


/**
 * \brief Function watchdog enable
 * 
 * \param[in] sec - time unit
 */
extern void hx_drv_wdt_enable(uint32_t sec);


/**
 * \brief Function watchdog disable
 * 
 */
extern void hx_drv_wdt_disable(void);


/**
 * \brief Function reset watchdog counter
 * 
 */
extern void hx_drv_wdt_reset(void);

/**
 * \brief  calibrate delay
 *
 * \param[in] board cpu clock
 * \return loops_per_jiffy
 */
extern uint64_t timer_calibrate_delay(uint32_t cpu_clock);

/**
 * \brief  delay us function type
 *
 * \param[in] int_or_poll  - 0: polling, 1: interrupt
 */
extern void set_delay_us_by(bool int_or_poll);

#ifdef __cplusplus
}
#endif

#endif /* PLATFORM_SYS_TIMER_HX_DRV_TIMER_H_ */

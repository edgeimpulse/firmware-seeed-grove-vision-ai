/**************************************************************************************************
    (C) COPYRIGHT, Himax Technologies, Inc. ALL RIGHTS RESERVED
    ------------------------------------------------------------------------
    File        : board.c
    Project     : WEI
    DATE        : 2018/10/01
    AUTHOR      : 902452
    BRIFE       : main function
    HISTORY     : Initial version - 2018/10/01 created by Will
**************************************************************************************************/
#include "embARC.h"
#include "embARC_debug.h"
#ifdef EVENT_HANDLER_LIB
#include "event.h"
#endif
#include "board.h"
uint32_t g_bsp_version = 0;
//extern uint32_t g_pad_dir_78;
//extern uint32_t g_pad_dir_7c;

typedef struct main_args {
	int argc;
	char *argv[];
} MAIN_ARGS;

/** Change this to pass your own arguments to main functions */
MAIN_ARGS s_main_args = {1, {"main"}};

#ifdef DISPLAY_SVN_VERSION
FORMAL_VERSION formal_version   __attribute__((section(".ver"), aligned(16))) =
{
	.svn_version 		= REPO_REV,
	.customer_name 		= CUSTOMER_NAME,
	.customer_version 	= CUSTOMER_VERSION
};

void print_formal_version()
{
	char buf[64];

	sprintf(buf, "%d.%s.%d",
				formal_version.svn_version,
				formal_version.customer_name,
				formal_version.customer_version);
	printf("\033[31mFW version: %s\033[0m\n", buf);
}
#endif

#if defined(EMBARC_USE_BOARD_MAIN)
/*--- When new embARC Startup process is used----*/
#define MIN_CALC(x, y)		(((x)<(y))?(x):(y))
#define MAX_CALC(x, y)		(((x)>(y))?(x):(y))

#ifdef OS_FREERTOS
/* Note: Task size in unit of StackType_t */
/* Note: Stack size should be small than 65536, since the stack size unit is uint16_t */
#define MIN_STACKSZ(size)	(MIN_CALC(size, configTOTAL_HEAP_SIZE) / sizeof(StackType_t))

#ifndef TASK_PRI_MAIN
#define TASK_PRI_MAIN		1	/* Main task priority */
#endif
static TaskHandle_t task_handle_main;

#endif /* OS_FREERTOS */

static void task_main(void *par)
{
	int ercd;

	if ((par == NULL) || (((int)par) & 0x3)) {
	/* null or aligned not to 4 bytes */
		ercd = _arc_goto_main(0, NULL);
	} else {
		MAIN_ARGS *main_arg = (MAIN_ARGS *)par;
		ercd = _arc_goto_main(main_arg->argc, main_arg->argv);
	}

#if defined(OS_FREERTOS)
	EMBARC_PRINTF("Exit from main function, error code:%d....\r\n", ercd);
	while (1) {
		vTaskSuspend(NULL);
	}
#else
	while (1);
#endif
}

void board_main(void)
{
/* board level hardware init */
	board_init();
/* board level middlware init */
	unsigned long long total_us;
	if(is_ref_cpu_clk_by_var()){
		total_us = ((unsigned long long)total_us * BOARD_SYS_TIMER_US_HZ) / get_ref_cpu_clk();
		timer_calibrate_delay(get_ref_cpu_clk());
	}else{
		timer_calibrate_delay(BOARD_CPU_CLOCK);
	}

#ifdef LIB_COMMON
	xprintf_setup();
#endif

    infra_evts_init();//need to erase later

#ifdef DISPLAY_SVN_VERSION
    print_formal_version();
#endif
#ifdef ENABLE_OS
	os_hal_exc_init();
#endif

#ifdef OS_FREERTOS
	xTaskCreate((TaskFunction_t)task_main, "main", TASK_STACK_SIZE_MAIN,
			(void *)(&s_main_args), TASK_PRI_MAIN, &task_handle_main);
#else /* No os and ntshell */
	cpu_unlock();	/* unlock cpu to let interrupt work */
	task_main((void *)(&s_main_args));
#endif

#ifdef OS_FREERTOS
	vTaskStartScheduler();
#endif

/* board level exit */
}
uint32_t hx_board_get_version(void)
{
	return g_bsp_version;
}
/*ifdef (EMBARC_USE_BOARD_MAIN) end*/
#elif defined(OS_TX)

#include "tx_api.h"

#define TASK_MAIN_STACK_SIZE         3072
#define TASK_MAIN_BYTE_POOL_SIZE     4096

static TX_THREAD               thread_task_main;
static TX_BYTE_POOL            byte_pool_task_main;

static UCHAR                   task_main_memory_area[TASK_MAIN_BYTE_POOL_SIZE];

static void task_main(void *par)
{
	int ercd;

	if ((par == NULL) || (((int)par) & 0x3)) {
	/* null or aligned not to 4 bytes */
		ercd = _arc_goto_main(0, NULL);
	} else {
		MAIN_ARGS *main_arg = (MAIN_ARGS *)par;
		ercd = _arc_goto_main(main_arg->argc, main_arg->argv);
	}
#ifdef OS_TX
	EMBARC_PRINTF("Exit from main function, error code:%d....\r\n", ercd);
	while (1) {
		tx_thread_suspend(&thread_task_main);
	}
#else
	while (1);
#endif

}
static void    thread_task_main_entry(ULONG thread_input)
{
	xprintf("thread_main_entry\n");
	task_main((void *)(&s_main_args));

}
void    tx_application_define(void *first_unused_memory)
{

	CHAR    *pointer = TX_NULL;
	UINT ret;
	xprintf("tx_application_define\n");
	/* Create a byte memory pool from which to allocate the thread stacks.  */
	ret = tx_byte_pool_create(&byte_pool_task_main, "byte_pool_task_main", task_main_memory_area, TASK_MAIN_BYTE_POOL_SIZE);
	if(ret != TX_SUCCESS){
		xprintf("byte_pool_task_main create fail err= 0x%x\n",ret);
	}
	/* Put system definition stuff in here, e.g. thread creates and other assorted
	   create information.  */

	/* Allocate the stack for thread 0.  */
	ret = tx_byte_allocate(&byte_pool_task_main, (VOID **) &pointer, TASK_MAIN_STACK_SIZE, TX_NO_WAIT);
	if(ret != TX_SUCCESS){
		xprintf("byte_pool_task_main allocate fail err= 0x%x\n",ret);
	}
	/* Create the main thread.  */
	ret = tx_thread_create(&thread_task_main, "thread_task_main", thread_task_main_entry, 0,
			pointer, TASK_MAIN_STACK_SIZE, 1, 1, TX_NO_TIME_SLICE, TX_AUTO_START);
	if(ret != TX_SUCCESS){
		xprintf("thread_task_main create fail err= 0x%x\n",ret);
	}
}

void board_main(void)
{
	/* board level hardware init */
	board_init();

	/* Library Support List */
#ifdef LIB_COMMON
	xprintf_setup();
#endif

#ifdef EVENT_HANDLER_LIB
	infra_evts_init();
#endif


#ifdef OS_TX
	tx_kernel_enter();
#else
	task_main((void *)(&s_main_args));
#endif
}

/* board level exit */
uint32_t hx_board_get_version(void)
{
	return g_bsp_version;
}
/*elif defined(OS_TX) end*/
#else /*-- Old embARC Startup process */

static void enter_to_main(MAIN_ARGS *main_arg)
{
	if (main_arg == NULL) {
	/* null or aligned not to 4 bytes */
		_arc_goto_main(0, NULL);
	} else {
		_arc_goto_main(main_arg->argc, main_arg->argv);
	}
}


void board_main(void)
{

#ifndef PURE_BOARD_INIT
#if HW_VERSION == 23
	uint32_t reg_val = 0;
	// ahb clk source select
	reg_val = _arc_read_uncached_32((void *)0xb0000010);
	reg_val = reg_val | 0x04;
	_arc_write_uncached_32((void *)0xb0000010, reg_val);

#if 0 // disable this - RD update default setting : select dfss uart
	reg_val = _arc_read_uncached_32((void *)0xb0010110);
	reg_val = reg_val | 0x80000000;
	_arc_write_uncached_32((void *)0xb0010110, reg_val);
#endif
#endif
	/* board level hardware init */
	board_init();

	/* Library Support List */
#ifdef LIB_COMMON
	xprintf_setup();
#endif
//	xprintf("BSP Version: 0x%08x\r\n", g_bsp_version);
//	xprintf("g_pad_dir_78=0x%08x\r\n", g_pad_dir_78);
//	xprintf("g_pad_dir_7c=0x%08x\r\n", g_pad_dir_7c);
#ifdef EVENT_HANDLER_LIB
	infra_evts_init();
#endif
#else

#ifndef FPGA_PLATFORM
	specific_board_init(BOARD_INIT_SPEC_PERI_I2CM | BOARD_INIT_SPEC_PERI_UART | BOARD_INIT_SPEC_PERI_SPIM |
			BOARD_INIT_SPEC_PERI_GPIO | BOARD_INIT_SPEC_PWM | BOARD_INIT_SPEC_DP );
#endif

#endif
#ifdef DISPLAY_SVN_VERSION
	print_formal_version();
#endif
	enter_to_main(&s_main_args);
}

uint32_t hx_board_get_version(void)
{
	return g_bsp_version;
}
#endif /* EMBARC_USE_BOARD_MAIN */

void hx_get_formal_version(unsigned char *pBuf)
{
#ifdef DISPLAY_SVN_VERSION
	unsigned char *p = (unsigned char *)&formal_version;
	int i;

	print_formal_version();

	for(i=0; i<sizeof(FORMAL_VERSION); i++)
	{
		pBuf[i] = p[i];
	}
#endif
}

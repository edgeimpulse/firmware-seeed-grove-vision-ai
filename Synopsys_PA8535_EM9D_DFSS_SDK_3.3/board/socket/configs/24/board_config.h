/*
* board_config.h
*
*  Created on: 2018/10/25
*      Author: 902452
*/

#ifndef SOCKET_CONFIGS_24_BOARD_CONFIG_H_
#define SOCKET_CONFIGS_24_BOARD_CONFIG_H_

#include "../24/hardware_config.h"
#include "arc_em.h"
#include "arc_builtin.h"

#include "sysconf.h"
#include "hx_drv_uart.h"
#include "hx_drv_iic_m.h"
#include "hx_drv_iic_s.h"
#include "hx_drv_timer.h"
#include "arc_timer.h"

#ifdef ARC_FEATURE_DMP_PERIPHERAL
#define PERIPHERAL_BASE     ARC_FEATURE_DMP_PERIPHERAL
#else
#define PERIPHERAL_BASE     _arc_aux_read(AUX_DMP_PERIPHERAL)
#endif

/*-----------------------------------------------------------------------------*/

#define BOARD_SYS_TIMER_ID          TIMER_0
#define BOARD_SYS_TIMER_INTNO       INTNO_TIMER0
#define BOARD_SYS_TIMER_HZ          (1000)
#define BOARD_SYS_TIMER_HZ_100MS    (10)
#define BOARD_SYS_TIMER_HZ_1S       (1)

#define BOARD_STD_TIMER_ID          TIMER_1
#define BOARD_STD_TIMER_INTNO       INTNO_TIMER1
#define BOARD_STD_TIMER_HZ          (1000)
#define BOARD_STD_TIMER_HZ_100MS    (10)

#define BOARD_RTC_TIMER_ID          TIMER_RTC
#define BOARD_RTC_TIMER_HZ          (1000)

/** board timer count frequency (HZ) */
#define BOARD_SYS_TIMER_MS_HZ       (1000)
/** board timer count frequency convention based on the global timer counter */
#define BOARD_SYS_TIMER_MS_CONV     (BOARD_CPU_CLOCK/BOARD_SYS_TIMER_HZ)
/** board timer count frequency (HZ) */
#define BOARD_SYS_TIMER_US_HZ       (1000000)
/** board timer count frequency convention based on the global timer counter */
#define BOARD_SYS_TIMER_US_CONV     (BOARD_CPU_CLOCK/BOARD_SYS_TIMER_US_HZ)


#define BOARD_OS_TIMER_ID                   TIMER_0
#define BOARD_OS_TIMER_INTNO                INTNO_TIMER0

#define BOARD_CPU_CLOCK                     CLK_CPU
#define BOARD_DEV_CLOCK                     CLK_BUS_APB

#define OSP_DELAY_OS_COMPAT_ENABLE          (1)
#define OSP_DELAY_OS_COMPAT_DISABLE         (0)

#define OSP_GET_CUR_SYSHZ()                 (gl_sys_hz_cnt)
#define OSP_GET_CUR_MS()                    (gl_sys_ms_cnt)
#define OSP_GET_CUR_US()                    board_get_cur_us()
#define OSP_GET_CUR_HWTICKS()               board_get_hwticks()

/*-----------------------------------------------------------------------------*/

/* common macros must be defined by socket boards */
#define BOARD_TEMP_SENSOR_IIC_ID        USE_SS_IIC_1
#define BOARD_TEMP_IIC_SLVADDR          TEMP_I2C_SLAVE_ADDRESS

#define BOARD_CIS_SENSOR_IIC_ID         USE_SS_IIC_2
#define BOARD_CIS_IIC_SLVADDR           (0x24)

#define BOARD_CONSOLE_DEBUG             1

#if defined(IC_PACKAGE_WLCSP38) || defined(IC_PACKAGE_QFP100) || defined(IC_PACKAGE_QFN72) || defined(NB_IOT_BOARD)
	#ifdef UART_PROTOCOL
		#define BOARD_CONSOLE_UART_ID           DFSS_UART_0_ID
		#define BOARD_COMMAND_UART_ID           DFSS_UART_1_ID
	#else
		#define BOARD_CONSOLE_UART_ID           DFSS_UART_1_ID
		#define BOARD_COMMAND_UART_ID           DFSS_UART_0_ID
	#endif
#else
	#if defined(HX6539_WIFI_ESP12F_V10)
		#define BOARD_CONSOLE_UART_ID           DFSS_UART_1_ID
		#define BOARD_COMMAND_UART_ID           DFSS_UART_0_ID
	#else
		#define BOARD_CONSOLE_UART_ID           DFSS_UART_0_ID
		#define BOARD_COMMAND_UART_ID           DFSS_UART_1_ID
	#endif
#endif

/*TODO: override in project.mk */
#define BOARD_CONSOLE_UART_BAUD         UART_BAUDRATE_921600
#define BOARD_COMMAND_UART_BAUD         UART_BAUDRATE_921600

#if defined(HX6539_WIFI_ESP12F_V10)
#define BOARD_WIFI_UART_ID              DFSS_UART_0_ID
#define BOARD_WIFI_UART_BAUD            UART_BAUDRATE_115200
#else
#define BOARD_WIFI_UART_ID              DFSS_UART_1_ID
#define BOARD_WIFI_UART_BAUD            UART_BAUDRATE_115200
#endif

#define BOARD_ONBOARD_NTSHELL_ID        (SOCKET_NTSHELL_0_ID)

#define BOARD_DFSS_IICS_ID              (USE_SS_IIC_S_0)
#define BOARD_DFSS_IICS_SLVADDR         (0x62)
#if defined(CIS_OV2640_BAYER) || defined(CIS_OV_SENSOR)
#define SCCB_ID   			(0X30)  			//OV2640µÄID
#endif


/* socket DFSS SPI configuration */
#ifndef BOARD_SPI_FREQ
#define BOARD_SPI_FREQ              (1000000)
#endif

#ifndef BOARD_SPI_CLKMODE
#define BOARD_SPI_CLKMODE           (SPI_CLK_MODE_0)
#endif

#define WF_IPADDR_1                 (192)
#define WF_IPADDR_2                 (168)
#define WF_IPADDR_3                 (43)
#define WF_IPADDR_4                 (102)

#define WF_NETMASK_1                (255)
#define WF_NETMASK_2                (255)
#define WF_NETMASK_3                (255)
#define WF_NETMASK_4                (0)

#define WF_GATEWAY_1                (192)
#define WF_GATEWAY_2                (168)
#define WF_GATEWAY_3                (43)
#define WF_GATEWAY_4                (1)

#define WF_HOTSPOT_IS_OPEN          (0)
#define WF_IPADDR_DHCP              (1)

#define WF_HOTSPOT_NAME             "embARC"
#define WF_HOTSPOT_PASSWD           "qazwsxedc"

#define WF_ENABLE_MANUAL_SET_MAC	(0)

#define WF_MAC_ADDR0                (SOCKET_PMWIFI_0_MAC_ADDR0)
#define WF_MAC_ADDR1                (SOCKET_PMWIFI_0_MAC_ADDR1)
#define WF_MAC_ADDR2                (SOCKET_PMWIFI_0_MAC_ADDR2)
#define WF_MAC_ADDR3                (SOCKET_PMWIFI_0_MAC_ADDR3)
#define WF_MAC_ADDR4                (SOCKET_PMWIFI_0_MAC_ADDR4)
#define WF_MAC_ADDR5                (SOCKET_PMWIFI_0_MAC_ADDR5)

/** Possible Pmod WiFi choices */
#define PMWIFI_MRF24G               0
#define PMWIFI_RW009                1


#define BOARD_PMWIFI_0_ID           SOCKET_PMWIFI_0_ID
#define BOARD_WIFI_SPI_LINE         0
#define BOARD_WIFI_0_INT            4
#define BOARD_WIFI_0_RST            5

#define TASK_STACK_SIZE_MAIN        2048

// Un-implemented LED/Switch/Button functions and macros
#define BOARD_LED_MASK          (0x0)
#define BOARD_LED_CNT           (0)
#define BOARD_BTN_MASK          (0x0)
#define BOARD_BTN_CNT           (0)
#define BOARD_SWT_MASK          (0x0)
#define BOARD_SWT_CNT           (0)

#define button_read(x)          1
#define led_write(x, y)         EMBARC_PRINTF("led out: %x, %x\r\n", x, y)

typedef enum {
    BOARD_INIT_SPEC_PERI_I2CM =	0x1<<0,
	BOARD_INIT_SPEC_PERI_I2CS =	0x1<<1,
	BOARD_INIT_SPEC_PERI_UART =	0x1<<2,
	BOARD_INIT_SPEC_PERI_SPIM =	0x1<<3,
	BOARD_INIT_SPEC_PERI_SPIS =	0x1<<4,
	BOARD_INIT_SPEC_PERI_GPIO =	0x1<<5,
	BOARD_INIT_SPEC_PWM = 		0x1<<6,
	BOARD_INIT_SPEC_DP = 		0x1<<7,
	BOARD_INIT_SPEC_AUDIO = 	0x1<<8,
	BOARD_INIT_SPEC_EVT = 		0x1<<9,
	BOARD_INIT_SPEC_SECURITY = 	0x1<<10,
} BOARD_INIT_SPEC_E;

/* socket DFSS GPIO configuration */
// #define BOARD_GPIO_PORT_A        DFSS_GPIO_PORT_A
// #define BOARD_GPIO_PORT_B        DFSS_GPIO_PORT_B
// #define BOARD_GPIO_PORT_C        DFSS_GPIO_PORT_C
// #define BOARD_GPIO_PORT_D        DFSS_GPIO_PORT_D

#ifdef __cplusplus
extern "C" {
#endif

extern void specific_board_init(BOARD_INIT_SPEC_E INIT_ITEM);
extern void board_init(void);
extern void board_timer_update(uint32_t precision);
extern void board_delay_ms(uint32_t ms);

#ifdef __cplusplus
}
#endif

#endif /* SOCKET_CONFIGS_24_BOARD_CONFIG_H_ */

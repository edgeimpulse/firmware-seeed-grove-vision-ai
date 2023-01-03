#ifndef INC_HX_DRV_UART_SW_H_
#define INC_HX_DRV_UART_SW_H_

#include "dev_common.h"
#include "hx_drv_iomux.h"
#include "hx_drv_uart.h"

/**
 * \brief  defines DFSS SWUART Object Number
 * 
 */
#define DFSS_UART_NUM	(2)	/*!< datafusion UART valid number */

/**
 * \brief  defines DFSS SWUART Object ID Macros
 * 
 */
#define DFSS_UART_SW_0_ID	0	/*!< uart 0 id macro */
#define DFSS_UART_SW_1_ID	1	/*!< uart 1 id macro */
#define DFSS_UART_SW_all_ID	DFSS_UART_NUM	/*!< uart All id macro */

/**
 * \enum UART TX/RX STATES 
 * \brief uart tx/rx states
*/
typedef enum
{
    HX_SWUART_START_BIT = 0,
    HX_SWUART_DATA_1,
    HX_SWUART_DATA_2,
    HX_SWUART_DATA_3,
    HX_SWUART_DATA_4,
    HX_SWUART_DATA_5,
    HX_SWUART_DATA_6,
    HX_SWUART_DATA_7,
    HX_SWUART_DATA_8,
    HX_SWUART_DATA_9,
    HX_SWUART_STOP_1,
    HX_SWUART_STOP_2,
} UART_TXRX_STATES;

typedef struct dev_uart_sw_cbs {
	DEV_CALLBACK tx_cb;	/*!< uart data transmit success required bytes callback (no support)*/
	DEV_CALLBACK rx_cb;	/*!< uart data receive success required bytes callback (no support)*/
	DEV_CALLBACK rxnb_cb;	/*!< uart data receive success required bytes callback(non-blocking) */
} DEV_UART_SW_CBS, *DEV_UART_SW_CBS_PTR;

/**
 * \enum USE_SS_UART_E_SW
 * \brief DFSS SW-UART Object ID
 */
typedef enum USE_SS_UART_SW_S
{
	USE_SS_UART_SW_0 = DFSS_UART_SW_0_ID,         /*!< enable use datafusion subsystem uart 0 */
	USE_SS_UART_SW_1 = DFSS_UART_SW_1_ID,         /*!< enable use datafusion subsystem uart 1 */
	USE_SS_UART_SW_ALL = DFSS_UART_SW_all_ID,     /*!< enable use datafusion subsystem uart all */
	USE_SS_UART_SW_MAX
} USE_SS_UART_SW_E;

/**
 * Set SW-UART Transfer Mode
 * - Param type : uint32_t
 * - Param usage :
 * - Return value explanation :
 */
#define SWUART_CMD_SET_TRANSMITDATA_MODE			DEV_SET_SYSCMD(25)

/**
 * Set SW-UART Receive Mode
 * - Param type : uint32_t
 * - Param usage :
 * - Return value explanation :
 */
#define SWUART_CMD_SET_RECEIVEDATA_MODE			DEV_SET_SYSCMD(26)

#define SWUART_CMD_CLOSE_RECEIVEDATA_MODE			DEV_SET_SYSCMD(27)

/** Default UART DPS format */
static const UART_DPS_FORMAT dps_format_default_sw = {UART_DATABITS_DEFAULT, UART_PARITY_NONE, UART_STPBITS_ONE};
/** @} */


/**
 * \brief	UART information struct definition
 * \details	informations about SW-uart tx GPIO, rx GPIO,
 *     baudrate, uart dps format
 */
typedef struct dev_uart_sw_info{
    uint8_t dev_id;         
    IOMUX_INDEX_E tx_pin;               /*!<software uart TX GPIO */ 
    IOMUX_INDEX_E rx_pin;               /*!<software uart RX GPIO */ 
    
    uint32_t baudrate;                 /*!< uart baud rate, this should be the value of baud passing by uart_open if first successfully opened */
    UART_DPS_FORMAT dps_format;       /*!< D/P/S format settings for uart device, here is \ref dps_format_default "default settings for first open" */
    UART_TRANSFER_MODE transfer_mode;

    DEV_BUFFER tx_buf;                  /*!< transmit buffer via interrupt, this should be all zero for first open */
    DEV_BUFFER rx_buf;                  /*!< receive buffer via interrupt, this should be all zero for first open */

    DEV_UART_SW_CBS uart_cbs;

    volatile uint16_t 	flags;
} DEV_UART_SW_INFO, * DEV_UART_SW_INFO_PTR;


/**
 * \brief	UART device interface definition
 * \details	Define uart device interface, like uart information structure,
 * 	provide functions to open/close/control uart, send/receive data by uart
 * \note	All this details are implemented by user in user porting code
 */
typedef struct dev_uart_sw {
	DEV_UART_SW_INFO info;				/*!< UART device information */
	int32_t (*uart_sw_open) (uint32_t baud, IOMUX_INDEX_E tx, IOMUX_INDEX_E rx);			/*!< Open uart device */
	int32_t (*uart_sw_close) (void);				/*!< Close uart device */
	int32_t (*uart_sw_control) (uint32_t ctrl_cmd, void *param);	/*!< Control uart device */
	int32_t (*uart_sw_write) (const void *data, uint32_t len);	/*!< Send data by uart device(blocked) */
	uint32_t (*uart_sw_read) (void *data, uint32_t len);	/*!< Read data from uart device(blocked) */
} DEV_UART_SW, * DEV_UART_SW_PTR;

typedef struct ss_uart_sw_dev_context
{
    uint32_t reg_base;
    uint8_t dev_id; 
    DEV_UART_SW_INFO *info;
    volatile uint32_t bit_length;
    volatile uint16_t 	flags;

    uint8_t poll_read;
    uint8_t poll_write;
} SS_UART_SW_DEV_CONTEXT;


/**
 * \brief	get an \ref dev_uart "uart device" by uart device id.
 * 	For how to use uart device hal refer to \ref DEVICE_HAL_UART_DEVSTRUCT "Functions in uart device structure"
 * \param[in]	uart_id	id of uart, defined by user
 * \retval	!NULL	pointer to an \ref dev_uart "uart device structure"
 * \retval	NULL	failed to find the uart device by \ref uart_id
 * \note	need to implemented by user in user code
 */
extern DEV_UART_SW_PTR hx_drv_uart_sw_get_dev(USE_SS_UART_SW_E uart_id);

/**
 * \brief init SW-UART 
 * 
 * \param[in] uart_id
 * \param[in] TX_GPIO
 * \param[in] RX_GPIO
 * \return int32_t
 */
extern int32_t hx_drv_uart_sw_init(USE_SS_UART_SW_E uart_id);

/**
 * \brief deinit SW-UART 
 * 
 * \param[in] uart_id
 * \return int32_t
 */
extern int32_t hx_drv_uart_sw_deinit(uint8_t uart_id);
#endif /* INC_HX_DRV_UART_SW_H_ */

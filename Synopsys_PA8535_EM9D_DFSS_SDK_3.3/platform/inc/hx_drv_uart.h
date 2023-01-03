/**
 * @file hx_drv_uart.h
 * @author himax/902452
 * @brief 
 * @version V1.0.0
 * @date 2018-10-08
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef INC_HX_DRV_UART_H_
#define INC_HX_DRV_UART_H_

#include <platform/inc/dev_common.h>

/**
 * \defgroup	DEVICE_HAL_UART_OBJ	UART Device Object Instance
 * \ingroup	DEVICE_HAL_UART
 * \brief	Macros for uart instance.
 * \details	Definitions for uart instance.
 * @{
 */


/**
 * \brief  defines DFSS UART Object Number
 * 
 */
#define DFSS_UART_NUM	(2)	/*!< datafusion UART valid number */


/**
 * \brief  defines DFSS UART Object ID Macros
 * 
 */
#define DFSS_UART_0_ID	0	/*!< uart 0 id macro */
#define DFSS_UART_1_ID	1	/*!< uart 1 id macro */
#define DFSS_UART_all_ID	DFSS_UART_NUM	/*!< uart All id macro */


/**
 * \enum USE_SS_UART_E
 * \brief DFSS UART Object ID
 */
typedef enum USE_SS_UART_S
{
	USE_SS_UART_0 = DFSS_UART_0_ID,         /*!< enable use datafusion subsystem uart 0 */
	USE_SS_UART_1 = DFSS_UART_1_ID,         /*!< enable use datafusion subsystem uart 1 */
	USE_SS_UART_ALL = DFSS_UART_all_ID,     /*!< enable use datafusion subsystem uart all */
	USE_SS_UART_MAX
}USE_SS_UART_E;

/** @} */


/**
 * \defgroup	DEVICE_HAL_UART_BAUD	UART Device Baudrate Definitions
 * \ingroup	DEVICE_HAL_UART
 * \brief	Macros for uart baudrate.
 * \details	Definitions for baudrate from 4800 to 115200bps.
 * @{
 */
/**
 * \brief  defines for uart baudrates
 * 
 */
#define UART_BAUDRATE_110           (110)       /*!< uart baudrate 110bps */
#define UART_BAUDRATE_300           (300)       /*!< uart baudrate 300bps */
#define UART_BAUDRATE_600           (600)       /*!< uart baudrate 600bps */
#define UART_BAUDRATE_1200          (1200)      /*!< uart baudrate 1200bps */
#define UART_BAUDRATE_2400          (2400)      /*!< uart baudrate 2400bps */
#define UART_BAUDRATE_4800          (4800)      /*!< uart baudrate 4800bps */
#define UART_BAUDRATE_9600          (9600)      /*!< uart baudrate 9600bps */
#define UART_BAUDRATE_14400         (14400)     /*!< uart baudrate 14400bps */
#define UART_BAUDRATE_19200         (19200)     /*!< uart baudrate 19200bps */
#define UART_BAUDRATE_38400         (38400)     /*!< uart baudrate 38400bps */
#define UART_BAUDRATE_57600         (57600)     /*!< uart baudrate 57600bps */
#define UART_BAUDRATE_115200        (115200)    /*!< uart baudrate 115200bps */
#define UART_BAUDRATE_230400        (230400)    /*!< uart baudrate 230400bps */
#define UART_BAUDRATE_460800        (460800)    /*!< uart baudrate 460800bps */
#define UART_BAUDRATE_921600        (921600)    /*!< uart baudrate 921600bps */
#define UART_BAUDRATE_12500000      (12500000)  /*!< uart baudrate 12500000bps */
#define UART_BAUDRATE_25000000      (25000000)  /*!< uart baudrate 25000000bps */
/** @} */

/**
 * \defgroup	DEVICE_HAL_UART_FORMAT	UART Device Format Definitions
 * \ingroup	DEVICE_HAL_UART
 * \brief	Macros for uart format.
 * \details	Definitions for uart format like databits, parity, stopbits.
 * @{
 */
/**
 * \enum UART_PARITY
 * \brief UART Device Parity Types Enum
 */
typedef enum {
	UART_PARITY_NONE  = 0,	/*!< no parity bit */
	UART_PARITY_ODD   = 1,	/*!< odd parity bit */
	UART_PARITY_EVEN  = 2,	/*!< even parity bit */
	UART_PARITY_MARK  = 3,	/*!< mark parity bit, always logical 1 */
	UART_PARITY_SPACE = 4	/*!< space parity bit, always logical 0 */
} UART_PARITY;


/**
 * \enum UART_STOPBITS
 * \brief UART Device Stop Bits Enum
 */
typedef enum {
	UART_STPBITS_ONE     = 0,	/*!< 1 stop bit */
	UART_STPBITS_ONEHALF = 1,	/*!< 1.5 stop bits */
	UART_STPBITS_TWO     = 2	/*!< 2 stop bits */
} UART_STOPBITS;


/**
 * \enum UART_TRANSFER_MODE
 * \brief UART Transfer Mode
 */
typedef enum uart_transfer_mode {
	UART_TRANSFER_INT  = 0,     /*!< Use DMA mode */
	UART_TRANSFER_DMA  = 1      /*!< Use INTERRUPT mode */
} UART_TRANSFER_MODE;


/**
 * \struct UART_DPS_FORMAT
 * \brief UART DPS Format: databits/parity/stopbits
 */
typedef struct uart_dps_format {
	uint32_t databits;          /*!< data bits */
	UART_PARITY parity;         /*!< parity bit type */
	UART_STOPBITS stopbits;     /*!< stop bits */
} UART_DPS_FORMAT;


/**
 * \struct UART_LINE_CTRL
 * \brief UART LINE Control: dls, stop, pen, eps, sp, bc
 */
typedef struct uart_line_ctrl {
	uint8_t databits;           /*!< data bits */
	UART_PARITY parity;         /*!< parity bit type */
	UART_STOPBITS stopbits;     /*!< stop bits */
} UART_LINE_CTRL;


#define UART_DATABITS_DEFAULT	8	/*!< default data bits */

/** Default UART DPS format */
static const UART_DPS_FORMAT dps_format_default = {UART_DATABITS_DEFAULT, UART_PARITY_NONE, UART_STPBITS_ONE};
/** @} */


/**
 * \enum UART_HW_FLOW_CONTROL
 * \brief UART Device Hardware Flow Control Types Enum
 */
typedef enum {
	UART_FC_NONE = 0,	/*!< Non hardware flow control */
	UART_FC_RTS  = 1,	/*!< Request To Send */
	UART_FC_CTS  = 2,	/*!< Clear To Send */
	UART_FC_BOTH = 3	/*!< Both hardware flow control methods */
} UART_HW_FLOW_CONTROL;

/** Default hardware flow control method */
static const UART_HW_FLOW_CONTROL hwfc_default = UART_FC_NONE;

/**
 * \defgroup	DEVICE_HAL_UART_CTRLCMD		UART Device Control Commands
 * \ingroup	DEVICE_HAL_UART
 * \brief	Definitions for uart control command, used in \ref dev_uart::uart_control "UART IO Control"
 * \details	These commands defined here can be used in user code directly.
 * - Parameters Usage
 *   - For passing parameters like integer, just use uint32_t/int32_t to directly pass values
 *   - For passing parameters for a structure, please use pointer to pass values
 *   - For getting some data, please use pointer to store the return data
 * - Common Return Values
 *   - \ref E_OK,	Control device successfully
 *   - \ref E_CLSED,	Device is not opened
 *   - \ref E_OBJ,	Device object is not valid or not exists
 *   - \ref E_PAR,	Parameter is not valid for current control command
 *   - \ref E_SYS,	Control device failed, due to hardware issues such as device is disabled
 *   - \ref E_CTX,	Control device failed, due to different reasons like in transfer state
 *   - \ref E_NOSPT,	Control command is not supported or not valid
 * @{
 */
/**
 * Set \ref dev_uart_info::baudrate "uart baudrate".
 * - Param type : uint32_t
 * - Param usage : uart baudrate, must above zero. Here is a list of \ref DEVICE_HAL_UART_BAUD "possible baudrates"
 * - Return value explanation :
 */
#define UART_CMD_SET_BAUD			DEV_SET_SYSCMD(0)
/**
 * Get \ref dev_uart_info::status "current device status"
 * - Param type : uint32_t *
 * - Param usage : store result of current status
 * - Return value explanation :
 */
#define UART_CMD_GET_STATUS			DEV_SET_SYSCMD(1)
/**
 * Enable uart device
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define UART_CMD_ENA_DEV			DEV_SET_SYSCMD(2)
/**
 * Disable uart device, when device is disabled,
 * only \ref UART_CMD_ENA_DEV, \ref UART_CMD_DIS_DEV and
 * \ref UART_CMD_GET_STATUS commands can be executed,
 * other commands will return \ref E_SYS
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define UART_CMD_DIS_DEV			DEV_SET_SYSCMD(3)
/**
 * Flush uart device output
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define UART_CMD_FLUSH_OUTPUT			DEV_SET_SYSCMD(4)
/**
 * Get how many bytes space in uart are available to transmit,
 * this can be used in interrupt callback functions,
 * cooperate with \ref dev_uart::uart_write "uart_write" API to realize non-blocked write
 * - Param type : int32_t *
 * - Param usage : store the write available bytes, > 0 for available bytes, 0 for not available
 * - Return value explanation :
 */
#define UART_CMD_GET_TXAVAIL			DEV_SET_SYSCMD(5)
/**
 * Get how many bytes in uart are available to receive,
 * this can be used in interrupt callback functions,
 * cooperate with \ref dev_uart::uart_read "uart_read" API to realize non-blocked read
 * - Param type : int32_t *
 * - Param usage : store the read available bytes, > 0 for available bytes, 0 for not available
 * - Return value explanation :
 */
#define UART_CMD_GET_RXAVAIL			DEV_SET_SYSCMD(6)
/**
 * Cause a break condition to be transmitted to the receiving device
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define UART_CMD_BREAK_SET			DEV_SET_SYSCMD(7)
/**
 * Clear break condition and return to normal
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define UART_CMD_BREAK_CLR			DEV_SET_SYSCMD(8)
/**
 * Change uart \ref dev_uart_info::dps_format "D/P/S(Data/Parity/Stop) format"
 * - Param type : \ref UART_DPS_FORMAT *
 * - Param usage : uart dps format including databits, parity and stopbits
 * - Return value explanation :
 */
#define UART_CMD_SET_DPS_FORMAT			DEV_SET_SYSCMD(9)
/**
 * Set uart device \ref dev_uart_info::hwfc "hardware flow control"
 * - Param type : \ref UART_HW_FLOW_CONTROL
 * - Param usage : uart dps format including databits, parity and stopbits
 * - Return value explanation :
 */
#define UART_CMD_SET_HWFC			DEV_SET_SYSCMD(10)
/**
 * Set \ref dev_uart_cbs::tx_cb "uart transmit success callback" function
 * when all required bytes are transmitted for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transmit success callback function for uart
 * - Return value explanation :
 */
#define UART_CMD_SET_TXCB			DEV_SET_SYSCMD(11)
/**
 * Set \ref dev_uart_cbs::rx_cb "uart receive success callback" function
 * when all required bytes are received for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : receive success callback function for uart
 * - Return value explanation :
 */
#define UART_CMD_SET_RXCB			DEV_SET_SYSCMD(12)
/**
 * Set \ref dev_uart_cbs::err_cb "uart transfer error callback" function
 * when something error happened for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transfer error callback function for uart
 * - Return value explanation :
 */
#define UART_CMD_SET_ERRCB			DEV_SET_SYSCMD(13)
/**
 * Set transmit buffer via interrupt, and it will set \ref dev_uart_info::tx_buf "tx_buf"
 * - Param type : DEV_BUFFER * or NULL
 * - Param usage : buffer structure pointer, if param is NULL, then it will set tx_buf to NULL
 * - Return value explanation :
 */
#define UART_CMD_SET_TXINT_BUF			DEV_SET_SYSCMD(14)
/**
 * Set receive buffer via interrupt, and it will set \ref dev_uart_info::rx_buf "rx_buf"
 * - Param type : DEV_BUFFER * or NULL
 * - Param usage : buffer structure pointer, if param is NULL, then it will set rx_buf to NULL
 * - Return value explanation :
 */
#define UART_CMD_SET_RXINT_BUF			DEV_SET_SYSCMD(15)
/**
 * Enable or disable transmit interrupt
 * - Param type : uint32_t
 * - Param usage : enable(none-zero) or disable(zero) flag
 * - Return value explanation :
 */
#define UART_CMD_SET_TXINT			DEV_SET_SYSCMD(16)
/**
 * Enable or disable receive interrupt
 * - Param type : uint32_t
 * - Param usage : enable(none-zero) or disable(zero) flag
 * - Return value explanation :
 */
#define UART_CMD_SET_RXINT			DEV_SET_SYSCMD(17)
/**
 * Abort current interrupt transmit operation if tx interrupt enabled,
 * it will disable transmit interrupt, and set \ref DEV_IN_TX_ABRT
 * in \ref dev_uart_info::status "status" variable,
 * and call the transmit callback function, when tx callback is finished,
 * it will clear \ref DEV_IN_TX_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define UART_CMD_ABORT_TX			DEV_SET_SYSCMD(18)
/**
 * Abort current interrupt receive operation if rx interrupt enabled,
 * it will disable receive interrupt, and set \ref DEV_IN_TX_ABRT
 * in \ref dev_uart_info::status "status" variable,
 * and call the receive callback function, when rx callback is finished,
 * it will clear \ref DEV_IN_TX_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define UART_CMD_ABORT_RX			DEV_SET_SYSCMD(19)
/**
 * Configure the transmit FIFO trigger level.
 * it will enable transmit FIFOs.
 * (can only be call if fifo depth not equal to zero)
 * - Param type : uint32_t
 * - Param usage :
 * - Return value explanation :
 */
#define UART_CMD_TX_FIFO_TRI			DEV_SET_SYSCMD(20)
/**
 * Configure the receive FIFO trigger level.
 * it will enable receive FIFOs.
 * (can only be call if fifo depth not equal to zero)
 * - Param type : uint32_t
 * - Param usage :
 * - Return value explanation :
 */
#define UART_CMD_RX_FIFO_TRI			DEV_SET_SYSCMD(21)
/**
 * Configure the UART HW Flow Control.
 * - Param type : uint32_t
 * - Param usage :
 * - Return value explanation :
 */
#define UART_CMD_SET_TRANSFER_MODE			DEV_SET_SYSCMD(22)

#define UART_CMD_POLL_READ			DEV_SET_SYSCMD(23)
#define UART_CMD_POLL_WRITE			DEV_SET_SYSCMD(24)
/** @} */

/**
 * \defgroup	DEVICE_HAL_UART_CALLBACK	UART Interrupt callback functions
 * \ingroup	DEVICE_HAL_UART
 * \brief	callback function structure for UART device
 * @{
 */
typedef struct dev_uart_cbs {
	DEV_CALLBACK tx_cb;	/*!< uart data transmit success required bytes callback */
	DEV_CALLBACK rx_cb;	/*!< uart data receive success required bytes callback */
	DEV_CALLBACK err_cb;	/*!< uart error callback */
} DEV_UART_CBS, *DEV_UART_CBS_PTR;
/** @} */

/**
 * \defgroup	DEVICE_HAL_UART_DEVSTRUCT	UART Device Interface Definition
 * \ingroup	DEVICE_HAL_UART
 * \brief	Contains definitions of uart device interface structure.
 * \details	This structure will be used in user implemented code, which was called
 *     \ref DEVICE_IMPL "Device Driver Implement Layer" for uart to use in implementation code.
 *     Application developer should use the UART API provided here to access to UART devices.
 *     BSP developer should follow the API definition to implement UART device drivers.
 * @{
 */
/**
 * \brief	UART information struct definition
 * \details	informations about uart open count, working status,
 *     baudrate, uart registers and ctrl structure, uart dps format
 */
typedef struct dev_uart_info {
	void *uart_ctrl;	/*!< uart control related pointer, implemented by bsp developer, and this should be set during uart object implementation */
	uint32_t opn_cnt;	/*!< uart open count, open it will increase 1, close it will decrease 1, 0 for close, >0 for open */
	uint32_t status;	/*!< current working status, refer to \ref DEVICE_HAL_COMMON_DEVSTATUS, this should be \ref DEV_ENABLED for first open */
	uint32_t baudrate;	/*!< uart baud rate, this should be the value of baud passing by uart_open if first successfully opened */
	UART_TRANSFER_MODE transfer_mode; /*!< current transfer \ref UART_TRANSFER_MODE "uart transfer mode" */
	UART_DPS_FORMAT dps_format;	/*!< D/P/S format settings for uart device, here is \ref dps_format_default "default settings for first open" */
	UART_HW_FLOW_CONTROL hwfc;	/*!< UART hardware flow control, here is \ref hwfc_default "default hardware flow control settings for first open" */
	DEV_BUFFER tx_buf;	/*!< transmit buffer via interrupt, this should be all zero for first open */
	DEV_BUFFER rx_buf;	/*!< receive buffer via interrupt, this should be all zero for first open */
	DEV_UART_CBS uart_cbs;	/*!< uart callbacks, callback arguments should be \ref DEV_UART * or NULL, this should be all NULL for first open */
	void *extra;		/*!< a extra pointer to get hook to applications which should not used by bsp developer,
					this should be NULL for first open and you can \ref DEV_UART_INFO_SET_EXTRA_OBJECT "set"
					or \ref DEV_UART_INFO_GET_EXTRA_OBJECT "get" the extra information pointer */
} DEV_UART_INFO, * DEV_UART_INFO_PTR;

/** Set extra information pointer of uart info */
#define DEV_UART_INFO_SET_EXTRA_OBJECT(uart_info_ptr, extra_info)	(uart_info_ptr)->extra = (void *)(extra_info)
/** Get extra information pointer of uart info */
#define DEV_UART_INFO_GET_EXTRA_OBJECT(uart_info_ptr)			((uart_info_ptr)->extra)

/**
 * \brief	UART device interface definition
 * \details	Define uart device interface, like uart information structure,
 * 	provide functions to open/close/control uart, send/receive data by uart
 * \note	All this details are implemented by user in user porting code
 */
typedef struct dev_uart {
	DEV_UART_INFO uart_info;				/*!< UART device information */
	int32_t (*uart_open) (uint32_t baud);			/*!< Open uart device */
	int32_t (*uart_close) (void);				/*!< Close uart device */
	int32_t (*uart_control) (uint32_t ctrl_cmd, void *param);	/*!< Control uart device */
	int32_t (*uart_write) (const void *data, uint32_t len);	/*!< Send data by uart device(blocked) */
	int32_t (*uart_read) (void *data, uint32_t len);	/*!< Read data from uart device(blocked) */
	int32_t (*uart_read_nonblock) (void *data, uint32_t len);	/*!< Read data from uart device(blocked) */
} DEV_UART, * DEV_UART_PTR;

/**
 * \fn		int32_t (* dev_uart::uart_open) (uint32_t baud)
 * \details	open an uart device with defined baudrate
 * \param[in]	baud	\ref DEVICE_HAL_UART_BAUD "initial baudrate of uart", must > 0
 * \retval	E_OK	Open successfully without any issues
 * \retval	E_OPNED	If device was opened before with different parameters,
 *			then just increase the \ref dev_uart_info::opn_cnt "opn_cnt" and return \ref E_OPNED
 * \retval	E_OBJ	Device object is not valid
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_NOSPT	Open settings are not supported
 */

/**
 * \fn		int32_t (* dev_uart::uart_close) (void)
 * \details	close an uart device, just decrease the \ref dev_uart_info::opn_cnt "opn_cnt",
 *      if \ref dev_uart_info::opn_cnt "opn_cnt" equals 0, then close the device
 * \retval	E_OK	Close successfully without any issues(including scenario that device is already closed)
 * \retval	E_OPNED	Device is still opened, the device \ref dev_uart_info::opn_cnt "opn_cnt" decreased by 1
 * \retval	E_OBJ	Device object is not valid
 */

/**
 * \fn		int32_t (* dev_uart::uart_control) (uint32_t ctrl_cmd, void *param)
 * \details	control an uart device by \ref ctrl_cmd, with passed \ref param.
 * 	you can control uart device using predefined uart control commands defined using \ref DEV_SET_SYSCMD
 * 	(which must be implemented by bsp developer), such as \ref UART_CMD_SET_BAUD "change baudrate",
 * 	\ref UART_CMD_FLUSH_OUTPUT "flush output" and \ref DEVICE_HAL_UART_CTRLCMD "more".
 * 	And you can also control uart device using your own specified commands defined using \ref DEV_SET_USRCMD,
 * 	but these specified commands should be defined in your own uart device driver implementation.
 * \param[in]		ctrl_cmd	\ref DEVICE_HAL_UART_CTRLCMD "control command", to change or get some thing related to uart
 * \param[in,out]	param		parameters that maybe argument of the command, or return values of the command
 * \retval	E_OK	Control device successfully
 * \retval	E_CLSED	Device is not opened
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid for current control command
 * \retval	E_SYS	Control device failed, due to hardware issues, such as device is disabled
 * \retval	E_CTX	Control device failed, due to different reasons like in transfer state
 * \retval	E_NOSPT	Control command is not supported or not valid
 */

/**
 * \fn		int32_t (* dev_uart::uart_write) (const void *data, uint32_t len)
 * \details	send \ref data through uart with defined \ref len(blocked).
 * \param[in]	data	pointer to data need to send by uart, must not be NULL
 * \param[in]	len	length of data to be sent, must > 0
 * \retval	>0	Byte count that was successfully sent for poll method
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_SYS	Can't write data to hardware due to hardware issues, such as device is disabled
 */

/**
 * \fn		int32_t (* dev_uart::uart_read) (void *data, uint32_t len)
 * \details	receive \ref data of defined \ref len through uart(blocked).
 * \param[out]	data	pointer to data need to received by uart, must not be NULL
 * \param[in]	len	length of data to be received, must > 0
 * \retval	>0	Byte count that was successfully received for poll method
 * \retval	E_OBJ	Device object is not valid or not exists
 * \retval	E_PAR	Parameter is not valid
 * \retval	E_SYS	Can't receive data from hardware due to hardware issues, such as device is disabled
 */
/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief	get an \ref dev_uart "uart device" by uart device id.
 * 	For how to use uart device hal refer to \ref DEVICE_HAL_UART_DEVSTRUCT "Functions in uart device structure"
 * \param[in]	uart_id	id of uart, defined by user
 * \retval	!NULL	pointer to an \ref dev_uart "uart device structure"
 * \retval	NULL	failed to find the uart device by \ref uart_id
 * \note	need to implemented by user in user code
 */
extern DEV_UART_PTR hx_drv_uart_get_dev(USE_SS_UART_E);

extern int hx_drv_uart_init(USE_SS_UART_E uart_id);

extern int hx_drv_uart_deinit(USE_SS_UART_E uart_id);

#ifdef __cplusplus
}
#endif


#endif /* INC_HX_DRV_UART_H_ */

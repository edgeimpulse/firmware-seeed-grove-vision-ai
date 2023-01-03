/**
 * @file hx_drv_iic_s.h
 * @author himax/902452
 * @brief 
 * @version V1.0.0
 * @date 2018-11-21
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef INC_HX_DRV_IIC_S_H_
#define INC_HX_DRV_IIC_S_H_

#include "dev_common.h"


/**
 * \brief  contains definition DFSS IIC Object ID Macros
 * 
 */
#define SS_IIC_S_NUM		(1)	     /*!< DFSS IIC valid number */
#define SS_IIC_S_0_ID		 0	     /*!< IIC 0 ID macro : slave 0*/

/** 7bit IIC address mask */
#define IIC_S_7BIT_ADDRESS_MASK	    (0x7F)
/** 10bit IIC address mask */
#define IIC_S_10BIT_ADDRESS_MASK    (0x3FF)


/**
 * \enum    USE_SS_IIC_S_E
 * \brief   IIC USED ID
 */
typedef enum USE_SS_IIC_S_S
{
	USE_SS_IIC_S_0   = SS_IIC_S_0_ID,    	/*!< enable use datafusion subsystem uart 0 */
	USE_SS_IIC_S_ALL = SS_IIC_S_NUM	        /*!< enable use datafusion subsystem uart all */
}USE_SS_IIC_S_E;


/**
 * \struct  IIC_S_ERROR_STATE
 * \brief   IIC Error State
 */
typedef enum iic_s_error_state {
	IIC_S_ERR_NONE       = 0,	/*!< Currently in iic device free state */
	IIC_S_ERR_LOST_BUS   = 1,	/*!< Master or slave lost bus during operation */
	IIC_S_ERR_ADDR_NOACK = 2,	/*!< Slave address is sent but not addressed by any slave devices */
	IIC_S_ERR_DATA_NOACK = 3,	/*!< Data in transfer is not acked when it should be acked */
	IIC_S_ERR_TIMEOUT    = 4,	/*!< Transfer timeout, no more data is received or sent */
	IIC_S_ERR_MSTSTOP    = 5,	/*!< Slave received a STOP condition from master device */
	IIC_S_ERR_UNDEF      = 6	/*!< Undefined error cases */
} IIC_S_ERROR_STATE;


/**
 * \enum    IIC_S_WORKING_STATE
 * \brief   IIC Working State
 */
typedef enum iic_s_working_state {
	IIC_S_FREE  = 0,	/*!< Currently in iic device free state */
	IIC_S_IN_TX = 1,	/*!< Currently in iic master transmit state */
	IIC_S_IN_RX = 2	    /*!< Currently in iic master receive state */
} IIC_S_WORKING_STATE;


/**
 * \enum    IIC_S_ADDRESS_MODE
 * \brief   IIC Addressing Mode
 */
typedef enum iic_s_address_mode {
	IIC_S_7BIT_ADDRESS  = 0,	/*!< Use 7bit address mode */
	IIC_S_10BIT_ADDRESS = 1	    /*!< Use 10bit address mode */
} IIC_S_ADDRESS_MODE;


/**
 * \enum    IIC_S_TRANSFER_MODE
 * \brief   IIC Transfer Mode
 */
typedef enum iic_s_transfer_mode {
	IIC_S_TRANSFER_INT  = 0,	/*!< Use DMA mode */
	IIC_S_TRANSFER_DMA  = 1	    /*!< Use INTERRUPT mode */
} IIC_S_TRANSFER_MODE;


/**
 * \enum    IIC_S_SLAVE_STATE
 * \brief   IIC Slave State
 */
typedef enum iic_s_slave_state {
	IIC_S_SLAVE_STATE_FREE     = 0,		    /*!< None state, in free */
	IIC_S_SLAVE_STATE_START    = (1<<1),	/*!< Start or Restart condition, clear it when read */
	IIC_S_SLAVE_STATE_STOP     = (1<<2),	/*!< Stop condition, clear it when read */
	IIC_S_SLAVE_STATE_RD_REQ   = (1<<3),	/*!< Read request from master, this will trigger the slave transmit callback */
	IIC_S_SLAVE_STATE_RD_DONE  = (1<<4),	/*!< Read request done from master, clear it when read */
	IIC_S_SLAVE_STATE_WR_REQ   = (1<<5),	/*!< Write request from master, this will trigger the slave receive callback */
	IIC_S_SLAVE_STATE_GC_REQ   = (1<<6),	/*!< General call request from master */
	IIC_S_SLAVE_STATE_ERROR    = (1<<7)	    /*!< Error, clear it when read */
} IIC_S_SLAVE_STATE;


/**
 * \defgroup	DEVICE_HAL_IIC_S_CTRLCMD		IIC Device Control Commands
 * \ingroup	DEVICE_HAL_IIC
 * \brief	Definitions for iic control command, used in \ref dev_iic::iic_s_control "IIC IO Control"
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
 */

/** Define IIC control commands for common usage */
#define DEV_SET_IIC_S_SYSCMD(cmd)		DEV_SET_SYSCMD((cmd))
/** Define IIC control commands for master usage */
#define DEV_SET_IIC_S_MST_SYSCMD(cmd)	DEV_SET_SYSCMD(0x00004000|(cmd))
/** Define IIC control commands for slave usage */
#define DEV_SET_IIC_S_SLV_SYSCMD(cmd)	DEV_SET_SYSCMD(0x00008000|(cmd))


/* ++++ Common commands for IIC Device ++++ */
/**
 * Get \ref dev_iic_s_info::status "current device status"
 * - Param type : uint32_t *
 * - Param usage : store result of current status
 * - Return value explanation :
 */
#define IIC_S_CMD_GET_STATUS			DEV_SET_IIC_S_SYSCMD(0)
/**
 * Set \ref dev_iic_s_info::addr_mode "iic addressing mode".
 * - Param type : uint32_t
 * - Param usage : iic addressing mode, possible values can be found \ref IIC_S_ADDRESS_MODE "here"
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_ADDR_MODE			DEV_SET_IIC_S_SYSCMD(1)
/**
 * Set \ref dev_iic_s_cbs::tx_cb "iic transmit success callback" function
 * when all required bytes are transmitted for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transmit success callback function for iic
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_TXCB			DEV_SET_IIC_S_SYSCMD(2)
/**
 * Set \ref dev_iic_s_cbs::rx_cb "iic receive success callback" function
 * when all required bytes are received for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : receive success callback function for iic
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_RXCB			DEV_SET_IIC_S_SYSCMD(3)
/**
 * Set \ref dev_iic_s_cbs::err_cb "iic transfer error callback" function
 * when something error happened for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transfer error callback function for iic
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_ERRCB			DEV_SET_IIC_S_SYSCMD(4)
/**
 * Set buffer for interrupt transmit, and it will set \ref dev_iic_s_info::tx_buf "tx_buf".
 * - IIC master mode use case  \n
 *    For master mode, if you set tx buffer to NULL, when tx interrupt is enabled and entered into tx interrupt,
 * it will automatically disable the tx interrupt, so when you want to transfer something, you need to set the
 * tx buffer to Non-NULL and enable tx interrupt, when the tx buffer is sent, it will disable the tx interrupt
 * and call tx callback function if available.
 * - IIC slave mode use case   \n
 *    For slave mode, the tx buffer is not used, only tx callback function is used, and if tx callback is not set,
 * then it will automatically disable the tx interrupt, if tx callback is set, it will call the tx callback function
 * and you need to write or read in the tx callback function, to avoid meaningless waiting, you can use control command
 * \ref IIC_S_CMD_GET_TXAVAIL to get how many bytes space existing in transmit fifo, and use iic_s_write to send the available
 * bytes.
 * - Param type : DEV_BUFFER * or NULL
 * - Param usage : buffer structure pointer, if param is NULL, then it will set tx_buf to NULL
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_TXINT_BUF			DEV_SET_IIC_S_SYSCMD(5)
/**
 * Set buffer for interrupt receive, and it will set \ref dev_iic_s_info::rx_buf "rx_buf"
 * - IIC master mode use case  \n
 *   Similar to \ref IIC_S_CMD_SET_TXINT_BUF
 * - IIC slave mode use case   \n
 *   Similiar to \ref IIC_S_CMD_SET_TXINT_BUF
 * - Param type : DEV_BUFFER * or NULL
 * - Param usage : buffer structure pointer, if param is NULL, then it will set rx_buf to NULL
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_RXINT_BUF			DEV_SET_IIC_S_SYSCMD(6)
/**
 * Enable or disable transmit interrupt,
 * for master mode, only one of tx and rx interrupt can be enabled,
 * if tx interrupt is enabled, then rx interrupt can't be changed.
 * - Param type : uint32_t
 * - Param usage : enable(none-zero) or disable(zero) flag
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_TXINT			DEV_SET_IIC_S_SYSCMD(7)
/**
 * Enable or disable receive interrupt,
 * for master mode, only one of tx and rx interrupt can be enabled,
 * if rx interrupt is enabled, then tx interrupt can't be changed.
 * - Param type : uint32_t
 * - Param usage : enable(none-zero) or disable(zero) flag
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_RXINT			DEV_SET_IIC_S_SYSCMD(8)
/**
 * Abort current interrupt transmit operation if tx interrupt enabled,
 * it will disable transmit interrupt, and set \ref DEV_IN_TX_ABRT
 * in \ref dev_iic_s_info::status "status" variable,
 * and call the transmit callback function, when tx callback is finished,
 * it will clear \ref DEV_IN_TX_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define IIC_S_CMD_ABORT_TX			DEV_SET_IIC_S_SYSCMD(9)
/**
 * Abort current interrupt receive operation if rx interrupt enabled,
 * it will disable receive interrupt, and set \ref DEV_IN_TX_ABRT
 * in \ref dev_iic_s_info::status "status" variable,
 * and call the receive callback function, when rx callback is finished,
 * it will clear \ref DEV_IN_TX_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define IIC_S_CMD_ABORT_RX			DEV_SET_IIC_S_SYSCMD(10)
/**
 * Do a software reset for IIC device, it will stop current transfer,
 * and clear error state and bring device to normal state, set next condition to STOP
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define IIC_S_CMD_RESET				DEV_SET_IIC_S_SYSCMD(11)
/**
 * Flush iic device transmit buffer or fifo
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define IIC_S_CMD_FLUSH_TX			DEV_SET_IIC_S_SYSCMD(12)
/**
 * Flush iic device receive buffer or fifo
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define IIC_S_CMD_FLUSH_RX			DEV_SET_IIC_S_SYSCMD(13)
/**
 * Enable iic device
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define IIC_S_CMD_ENA_DEV				DEV_SET_IIC_S_SYSCMD(14)
/**
 * Disable iic device, when device is disabled,
 * only \ref IIC_S_CMD_ENA_DEV, \ref IIC_S_CMD_DIS_DEV,
 * \ref IIC_S_CMD_GET_STATUS and \ref IIC_S_CMD_RESET
 * commands can be executed, other commands will return \ref E_SYS
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define IIC_S_CMD_DIS_DEV				DEV_SET_IIC_S_SYSCMD(15)
/**
 * Get how many bytes space in iic are available to transmit,
 * this can be used in interrupt callback functions,
 * cooperate with \ref dev_iic::iic_s_write "iic_s_write" API to realize non-blocked write
 * - Param type : int32_t *
 * - Param usage : store the write available bytes, > 0 for available bytes, 0 for not available
 * - Return value explaination :
 */
#define IIC_S_CMD_GET_TXAVAIL			DEV_SET_IIC_S_SYSCMD(16)
/**
 * Get how many bytes in iic are available to receive,
 * this can be used in interrupt callback functions,
 * cooperate with \ref dev_iic::iic_s_read "iic_s_read" API to realize non-blocked read
 * - Param type : int32_t *
 * - Param usage : store the read available bytes, > 0 for available bytes, 0 for not available
 * - Return value explanation :
 */
#define IIC_S_CMD_GET_RXAVAIL			DEV_SET_IIC_S_SYSCMD(17)
/**
 * Set \ref dev_iic_s_cbs::dev_cb "iic transfer callback" function
 * when i2c transfer done for interrupt method (option for application)
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transfer driver callback function for iic
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_DEVCB			DEV_SET_IIC_S_SYSCMD(18)
/**
 * Set \ref dev_iic_s_cbs::rdreq_cb "iic transfer callback" function
 * when i2c transfer done for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transfer driver callback function for iic
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_RDREQ_CB		DEV_SET_IIC_S_SYSCMD(19)
/**
 * Set \ref dev_iic_s_cbs::dev_cb "iic transfer callback" function
 * when i2c transfer done for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transfer driver callback function for iic
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_RESTART_CB	DEV_SET_IIC_S_SYSCMD(20)
/**
 * Set transmit(TX) FIFO threshold function
 * - Param type : uint32_t
 * - Param usage : iic transmit fifo threshold
 * - Return value explanation :
 */
#define IIC_S_CMD_SET_TXFIFO			DEV_SET_IIC_S_SYSCMD(21)
/**
 * Set receive(RX) FIFO threshold function
 * - Param type : uint32_t
 * - Param usage : control the threshold level for generation "TX EMPTY" interrupt
 * - Return value explanation
 */
#define IIC_S_CMD_SET_RXFIFO			DEV_SET_IIC_S_SYSCMD(22)
/**
 * Set I2C Transfer Mode
 * - Param type  : uint32_t
 * - Param usage : control the transfer mode \ref IIC_S_TRANSFER_MODE
 *                 - IIC_S_TRANSFER_INT : read/write function using interrupt to process data transfer
 *                 - IIC_S_TRANSFER_DMA : read/write function using interrupt to process data transfer
 * - Return value explanation
 */
#define IIC_S_CMD_SET_TRANSFER_MODE	DEV_SET_IIC_S_SYSCMD(23)

/* ++++ Slave only commands for IIC Device ++++ */
/**
 * Set slave address when working as slave iic device
 * - Param type : uint32_t
 * - Param usage : slave address value
 * - Return value explanation :
 */
#define IIC_S_CMD_SLV_SET_SLV_ADDR		DEV_SET_IIC_S_SLV_SYSCMD(0)
/**
 * Get \ref iic_s_slave_state "slave state" when working as slave iic device
 * - Param type : uint32_t *
 * - Param usage : slave state
 * - Return value explanation :
 */
#define IIC_S_CMD_SLV_GET_SLV_STATE		DEV_SET_IIC_S_SLV_SYSCMD(1)

/**
 * Get \ref 
 * - Param type : uint8_t
 * - Param usage : slave status
 * - Return value explanation :
 */
#define IIC_S_CMD_SLV_GET_SLV_STATUS	DEV_SET_IIC_S_SLV_SYSCMD(2)

typedef struct dev_iic_s_cbs {
	DEV_CALLBACK tx_cb;	        /*!< iic data transmit success required bytes callback */
	DEV_CALLBACK rx_cb;	        /*!< iic data receive success required bytes callback */
	DEV_CALLBACK err_cb;	    /*!< iic error callback */
	DEV_CALLBACK stop_cb;
	DEV_CALLBACK rdreq_cb;
	DEV_CALLBACK restart_cb;
} DEV_IIC_S_CBS, *DEV_IIC_S_CBS_PTR;



typedef struct dev_iic_s_info {
	void *iic_s_ctrl;		/*!< iic control related pointer, implemented by bsp developer, and this should be set during iic object implementation */
	uint32_t opn_cnt;	/*!< iic open count, open it will increase 1, close it will decrease 1, 0 for close, >0 for open */
	uint32_t status;	/*!< current working status, refer to \ref DEVICE_HAL_COMMON_DEVSTATUS, this should be \ref DEV_ENABLED for first open */
	uint32_t mode;		/*!< current working mode, which can be \ref DEV_MASTER_MODE "master mode" or \ref DEV_SLAVE_MODE "slave mode" */
	uint32_t speed_mode;	/*!< current working \ref IIC_S_SPEED_MODE "iic speed mode" */
	uint32_t transfer_mode; /*!< current transfer \ref IIC_S_TRANSFER_MODE "iic transfer mode" */
	uint32_t cur_state;	/*!< \ref IIC_S_WORKING_STATE "current working state for iic device", this should be \ref IIC_S_FREE for first open */
	uint32_t err_state;	/*!< \ref IIC_S_ERROR_STATE "current error state for iic device", this should be \ref IIC_S_ERR_NONE for first open */
	uint32_t addr_mode;	/*!< \ref IIC_S_ADDRESS_MODE "current addressing mode", this should be \ref IIC_S_7BIT_ADDRESS for first open */
	uint32_t slv_addr;	/*!< slave address when working as slave iic device, this should be 0 for first open */
	uint32_t tar_addr;	/*!< target slave device address when addressing that slave device, this should be 0 for first open */
	uint32_t next_cond;	/*!< \ref IIC_S_NEXT_CONDTION "next condition for master transmit or receive", \
					possible values are STOP or RESTART, it should be STOP for first open */
	DEV_BUFFER tx_buf;	/*!< transmit buffer via interrupt, this should be all zero for first open */
	DEV_BUFFER rx_buf;	/*!< receive buffer via interrupt, this should be all zero for first open */
	DEV_IIC_S_CBS iic_s_cbs;	/*!< iic callbacks, for both master and slave mode, this should be all NULL for first open */
	void *extra;		/*!< a extra pointer to get hook to applications which should not used by bsp developer,
					this should be NULL for first open and you can \ref DEV_IIC_S_INFO_SET_EXTRA_OBJECT "set"
					or \ref DEV_IIC_S_INFO_GET_EXTRA_OBJECT "get" the extra information pointer */
} DEV_IIC_S_INFO, * DEV_IIC_S_INFO_PTR;


typedef struct dev_iic_s {
	DEV_IIC_S_INFO iic_s_info;					/*!< iic device information */
	int32_t (*iic_s_open) (uint32_t mode, uint32_t param);	/*!< open iic device in master/slave mode, \
									when in master mode, param stands for speed mode, \
									when in slave mode, param stands for slave address */
	int32_t (*iic_s_close) (void);				/*!< close iic device */
	int32_t (*iic_s_control) (uint32_t ctrl_cmd, void *param);/*!< control iic device */
	int32_t (*iic_s_write) (const void *data, uint32_t len);	/*!< send data by iic device (blocking method) */
	int32_t (*iic_s_read) (void *data, uint32_t len);		/*!< read data from iic device (blocking method) */
} DEV_IIC_S, * DEV_IIC_S_PTR;


/** Set extra information pointer of iic info */
#define DEV_IIC_S_INFO_SET_EXTRA_OBJECT(iic_s_info_ptr, extra_info)		(iic_s_info_ptr)->extra = (void *)(extra_info)
/** Get extra information pointer of iic info */
#define DEV_IIC_S_INFO_GET_EXTRA_OBJECT(iic_s_info_ptr)			((iic_s_info_ptr)->extra)


/**
 * \brief init I2C slave 
 * 
 * \return int32_t
 */
int32_t hx_drv_i2cs_init(void);


/**
 * \brief de-init I2C slave
 * 
 * \return int32_t
 */
int32_t hx_drv_i2cs_deinit(void);


/**
 * \brief get I2C slave configuration
 * 
 * \return DEV_IIC_S_PTR
 */
DEV_IIC_S_PTR hx_drv_i2cs_get_dev(void);

#endif /* INC_HX_DRV_IIC_S_S_H_ */

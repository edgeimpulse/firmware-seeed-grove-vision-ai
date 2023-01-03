/**
 * @file hx_drv_spi_m.h
 * @author himax/902449
 * @brief 
 * @version V1.0.2
 * @date 2020-03-25
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef INC_HX_DRV_SPI_M_H_
#define INC_HX_DRV_SPI_M_H_

#include "dev_common.h"

/**
 * \name	DesignWare SPI Object Number
 * @{
 */
#define DW_SPI_NUM		(2)	/*!< DesignWare SPI valid number */
/** @} end of name */

/**
 * \name	Designware SPI Object ID Macros
 * @{
 */
#define DW_SPI_0_ID		0	/*!< SPI 0 id macro (master node) */
#define DW_SPI_1_ID		1	/*!< SPI 1 id macro (slave node) */
#define DW_SPI_MST_NUM	2   /*!< DW SPI master valid number */
/** @} end of name */

/**
 * \name	Designware SPI Object Control Macros
 * @{
 */
#define USE_DW_SPI_0		1	/*!< enable use designware SPI 0 */
#define USE_DW_SPI_1		1	/*!< enable use designware SPI 1 */
/** @} end of name */



#define spi_plt_hdr_default USE_DW_SPI_PLT_HDR

/**
 * \enum USE_DW_SPI_MST_E
 * \brief SPI Master ID enum
 */
typedef enum USE_DW_SPI_MST_S
{
	USE_DW_SPI_MST_0 = DW_SPI_0_ID,    		/*!< enable use dw spi master 0 */
	USE_DW_SPI_MST_1 = DW_SPI_1_ID,    		/*!< enable use dw spi master 1 */
	USE_DW_SPI_MST_ALL = DW_SPI_MST_NUM,	/*!< enable use dw spi master all */
	USE_DW_SPI_MST_MAX
}USE_DW_SPI_MST_E;

/** Define SPI control commands for common usage */
#define DEV_SET_SPI_SYSCMD(cmd)		DEV_SET_SYSCMD((cmd))
/** Define SPI control commands for master usage */
#define DEV_SET_SPI_MST_SYSCMD(cmd)	DEV_SET_SYSCMD(0x00001000|(cmd))
/** Define SPI control commands for slave usage */
#define DEV_SET_SPI_SLV_SYSCMD(cmd)	DEV_SET_SYSCMD(0x00002000|(cmd))


/* ++++ Common commands for SPI Device ++++ */
/**
 * Get \ref dev_spi_info::status "current device status"
 * - Param type : uint32_t *
 * - Param usage : store result of current status
 * - Return value explanation :
 */
#define SPI_CMD_GET_STATUS			DEV_SET_SPI_SYSCMD(0)
/**
 * set the \ref dev_spi_info::clk_mode "clock mode" of spi transfer
 * - Param type : uint32_t
 * - Param usage : spi clock mode to choose clock phase and clock polarity
 * - Return value explanation :
 */
#define SPI_CMD_SET_CLK_MODE			DEV_SET_SPI_SYSCMD(1)
/**
 * set spi \ref dev_spi_info::dfs "data frame size"
 * - Param type : uint32_t
 * - Param usage : should > 0
 * - Return value explanation : If dfs is not supported, then return \ref E_SYS
 */
#define SPI_CMD_SET_DFS				DEV_SET_SPI_SYSCMD(2)
/**
 * set the \ref dev_spi_info::dummy "dummy data" during spi transfer
 * - Param type : uint32_t
 * - Param usage : dummy data to transfer
 * - Return value explanation :
 */
#define SPI_CMD_SET_DUMMY_DATA			DEV_SET_SPI_SYSCMD(3)
/**
 * Set \ref dev_spi_cbs::tx_cb "spi transmit success callback" function
 * when all required bytes are transmitted for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transmit success callback function for spi
 * - Return value explanation :
 */
#define SPI_CMD_SET_TXCB			DEV_SET_SPI_SYSCMD(4)
/**
 * Set \ref dev_spi_cbs::rx_cb "spi receive success callback" function
 * when all required bytes are received for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : receive success callback function for spi
 * - Return value explanation :
 */
#define SPI_CMD_SET_RXCB			DEV_SET_SPI_SYSCMD(5)
/**
 * Set \ref dev_spi_cbs::xfer_cb "spi transfer success callback" function
 * when all required transfer are done for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transfer success callback function for spi
 * - Return value explanation :
 */
#define SPI_CMD_SET_XFERCB			DEV_SET_SPI_SYSCMD(6)
/**
 * Set \ref dev_spi_cbs::err_cb "spi transfer error callback" function
 * when something error happened for interrupt method
 * - Param type : \ref DEV_CALLBACK * or NULL
 * - Param usage : transfer error callback function for spi
 * - Return value explanation :
 */
#define SPI_CMD_SET_ERRCB			DEV_SET_SPI_SYSCMD(7)
/**
 * Set buffer in interrupt transmit, and it will set \ref dev_spi_info::xfer "spi tranfer".
 * - SPI master and slave mode use case  \n
 *    For both master and slave mode, if you set tx buffer to NULL, when tx interrupt is enabled and entered into tx interrupt,
 * it will automatically disable the tx interrupt, so when you want to transfer something, you need to set the
 * tx buffer to Non-NULL and enable tx interrupt, when the tx buffer is sent, it will disable the tx interrupt
 * and call tx callback function if available.
 * - Param type : DEV_BUFFER * or NULL
 * - Param usage : buffer structure pointer, if param is NULL, then it will set xfer to empty
 * - Return value explanation :
 */
#define SPI_CMD_SET_TXINT_BUF			DEV_SET_SPI_SYSCMD(8)
/**
 * Set buffer in interrupt receive, and it will set \ref dev_spi_info::xfer "spi tranfer".
 * - SPI master mode use case  \n
 *   Similar to \ref SPI_CMD_SET_TXINT_BUF
 * - SPI slave mode use case   \n
 *   Similiar to \ref SPI_CMD_SET_TXINT_BUF
 * - Param type : DEV_BUFFER * or NULL
 * - Param usage : buffer structure pointer, if param is NULL, then it will set xfer to empty
 * - Return value explanation :
 */
#define SPI_CMD_SET_RXINT_BUF			DEV_SET_SPI_SYSCMD(9)
/**
 * Enable or disable transmit interrupt,
 * for master mode, only one of tx and rx interrupt can be enabled,
 * if tx interrupt is enabled, then rx interrupt can't be enabled.
 * - Param type : uint32_t
 * - Param usage : enable(none-zero) or disable(zero) flag
 * - Return value explanation :
 */
#define SPI_CMD_SET_TXINT			DEV_SET_SPI_SYSCMD(10)
/**
 * Enable or disable receive interrupt,
 * for master mode, only one of tx and rx interrupt can be enabled,
 * if rx interrupt is enabled, then tx interrupt can't be enabled.
 * - Param type : uint32_t
 * - Param usage : enable(none-zero) or disable(zero) flag
 * - Return value explanation :
 */
#define SPI_CMD_SET_RXINT			DEV_SET_SPI_SYSCMD(11)
/**
 * start the transfer by polling
 * - Param type : \ref DEV_SPI_TRANSFER *
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_TRANSFER_POLLING		DEV_SET_SPI_SYSCMD(12)
/**
 * start the transfer by interrupt
 * - Param type : \ref DEV_SPI_TRANSFER * or NULL
 * - Param usage : If NULL, it will disable transfer interrupt, if not NULL, it will enable transfer interrupt
 * - Return value explanation :
 */
#define SPI_CMD_TRANSFER_INT			DEV_SET_SPI_SYSCMD(13)
/**
 * Abort current interrupt transmit operation if tx interrupt enabled,
 * it will disable transmit interrupt, and set \ref DEV_IN_TX_ABRT
 * in \ref dev_spi_info::status "status" variable,
 * and call the transmit callback function, when tx callback is finished,
 * it will clear \ref DEV_IN_TX_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_ABORT_TX			DEV_SET_SPI_SYSCMD(14)
/**
 * Abort current interrupt receive operation if rx interrupt enabled,
 * it will disable receive interrupt, and set \ref DEV_IN_TX_ABRT
 * in \ref dev_spi_info::status "status" variable,
 * and call the receive callback function, when rx callback is finished,
 * it will clear \ref DEV_IN_TX_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_ABORT_RX			DEV_SET_SPI_SYSCMD(15)
/**
 * Abort current interrupt transfer operation if transfer is issued,
 * it will disable transfer interrupt, and set \ref DEV_IN_XFER_ABRT
 * in \ref dev_spi_info::status "status" variable,
 * and call the transfer callback function, when xfer callback is finished,
 * it will clear \ref DEV_IN_XFER_ABRT and return
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_ABORT_XFER			DEV_SET_SPI_SYSCMD(16)
/**
 * Do a software reset for SPI device, it will stop current transfer,
 * and clear error state and bring device to normal state, set next condition to STOP
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_RESET				DEV_SET_SPI_SYSCMD(17)
/**
 * Flush spi tx fifo, this will clear the data in tx fifo
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_FLUSH_TX			DEV_SET_SPI_SYSCMD(18)
/**
 * Flush spi rx fifo, this will clear the data in rx fifo
 * - Param type : NULL
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_FLUSH_RX			DEV_SET_SPI_SYSCMD(19)
/**
 * Enable spi device
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define SPI_CMD_ENA_DEV				DEV_SET_SPI_SYSCMD(20)
/**
 * Disable spi device, when device is disabled,
 * only \ref SPI_CMD_ENA_DEV, \ref SPI_CMD_DIS_DEV,
 * \ref SPI_CMD_GET_STATUS and \ref SPI_CMD_RESET
 * commands can be executed, other commands will return \ref E_SYS
 * - Param type : NULL
 * - Param usage : param is not required
 * - Return value explanation :
 */
#define SPI_CMD_DIS_DEV				DEV_SET_SPI_SYSCMD(21)
/**
 * Get how many bytes space in spi are available to transmit,
 * this can be used in interrupt callback functions,
 * cooperate with \ref dev_spi::spi_write "spi_write" API to realize non-blocked write
 * - Param type : int32_t *
 * - Param usage : store the write available bytes, > 0 for available bytes, 0 for not available
 * - Return value explanation :
 */
#define SPI_CMD_GET_TXAVAIL			DEV_SET_SPI_SYSCMD(22)
/**
 * Get how many bytes in spi are available to receive,
 * this can be used in interrupt callback functions,
 * cooperate with \ref dev_spi::spi_read "spi_read" API to realize non-blocked read
 * - Param type : int32_t *
 * - Param usage : store the read available bytes, > 0 for available bytes, 0 for not available
 * - Return value explanation :
 */
#define SPI_CMD_GET_RXAVAIL			DEV_SET_SPI_SYSCMD(23)
/**
 * - Param type : int32_t *
 * - Param usage :
 * - Return value explanation :
 */
#define SPI_CMD_SET_TRANSMODE		DEV_SET_SPI_SYSCMD(24)

/* ++++ Master only commands for SPI Device ++++ */
/**
 *  select spi slave device
 * - Param type : uint32_t
 * - Param usage : the number of spi slave device to select
 * - Return value explanation : return \ref E_SYS when selection can't be done, return \ref E_CTX during transfer
 */
#define SPI_CMD_MST_SEL_DEV			DEV_SET_SPI_MST_SYSCMD(0)
/**
 *  de-select spi slave device
 * - Param type : uint32_t
 * - Param usage : the number of spi slave device to de-select
 * - Return value explanation : return \ref E_SYS when selection can't be done, return \ref E_CTX during transfer
 */
#define SPI_CMD_MST_DSEL_DEV			DEV_SET_SPI_MST_SYSCMD(1)
 /**
 * Set \ref dev_spi_info::freq "spi frequency".
 * - Param type : uint32_t
 * - Param usage : spi freq
 * - Return value explanation : no return
 */
#define SPI_CMD_MST_SET_FREQ			DEV_SET_SPI_MST_SYSCMD(2)
/**
*   set rx delay value
* - Param type : uint32_t
* - Param usage : value is the delay tick number of spi clock, spi master read data after wait these spi tick clock count
* - Return value explanation : no return
*/
#define SPI_CMD_MST_SET_RX_DLY			DEV_SET_SPI_MST_SYSCMD(3)
/**
 * \defgroup	DEVICE_HAL_SPI_CALLBACK	SPI Interrupt callback functions
 * \ingroup	DEVICE_HAL_SPI
 * \brief	callback function structure for SPI device
 * @{
 */
typedef struct dev_spi_cbs {
	DEV_CALLBACK tx_cb;	/*!< spi data transmit success required bytes callback */
	DEV_CALLBACK rx_cb;	/*!< spi data receive success required bytes callback */
	DEV_CALLBACK err_cb;	/*!< spi error callback */
	DEV_CALLBACK xfer_cb;	/*!< transfer callback */
} DEV_SPI_CBS, *DEV_SPI_CBS_PTR;
/** @} */

/**
 * \defgroup	DEVICE_HAL_SPI_CLK_MODE	SPI Clock Mode
 * \ingroup	DEVICE_HAL_SPI
 * \brief	spi clock mode settings
 * @{
 */
/** SPI Clock Mode */
typedef enum spi_clk_mode {
	SPI_CPOL_0_CPHA_0 = 0,	/*!< Inactive state of serial clock is low, serial clock toggles in middle of first data bit */
	SPI_CPOL_0_CPHA_1 = 1,	/*!< Inactive state of serial clock is low, serial clock toggles at start of first data bit  */
	SPI_CPOL_1_CPHA_0 = 2,	/*!< Inactive state of serial clock is high, serial clock toggles in middle of first data bit */
	SPI_CPOL_1_CPHA_1 = 3,	/*!< Inactive state of serial clock is high, serial clock toggles at start of first data bit */

	SPI_CLK_MODE_0    = SPI_CPOL_0_CPHA_0,	/*!< Equal to \ref SPI_CPOL_0_CPHA_0 */
	SPI_CLK_MODE_1    = SPI_CPOL_0_CPHA_1,	/*!< Equal to \ref SPI_CPOL_0_CPHA_1 */
	SPI_CLK_MODE_2    = SPI_CPOL_1_CPHA_0,	/*!< Equal to \ref SPI_CPOL_1_CPHA_0 */
	SPI_CLK_MODE_3    = SPI_CPOL_1_CPHA_1	/*!< Equal to \ref SPI_CPOL_1_CPHA_1 */
} SPI_CLK_MODE;

typedef SPI_CLK_MODE			DEV_SPI_CLK_MODE;

/*!< Default SPI device clock mode */
#define SPI_CLK_MODE_DEFAULT		SPI_CPOL_0_CPHA_0
/** @} */

/**
 * \defgroup	DEVICE_HAL_SPI_SLAVE_SELECT	SPI Slave Select Line
 * \ingroup	DEVICE_HAL_SPI
 * \brief	spi slave select line definition
 * @{
 */
/** SPI Slave Select Line, start from 0 */
#define DEV_SPI_CS_LINE_DEF(line)		(line)
typedef enum dev_spi_cs_line {
	DEV_SPI_CS_LINE_0 = 0,		/*!< SPI slave select line 0  */
	DEV_SPI_CS_LINE_1,		/*!< SPI slave select line 1  */
	DEV_SPI_CS_LINE_2,		/*!< SPI slave select line 2  */
	DEV_SPI_CS_LINE_3,		/*!< SPI slave select line 3  */
} DEV_SPI_CS_LINE;
/** @} */

/**
 * \defgroup	DEVICE_HAL_SPI_DEVSTRUCT	SPI Device Structure
 * \ingroup	DEVICE_HAL_SPI
 * \brief	contains definitions of spi device structure.
 * \details	this structure will be used in user implemented code, which was called
 * 	Device Driver Implement Layer for spi to realize in user code.
 * @{
 */
typedef struct dev_spi_transfer DEV_SPI_TRANSFER, *DEV_SPI_TRANSFER_PTR;
/**
 * \brief	spi read and write data structure used by \ref SPI_CMD_TRANSFER
 * 	spi write then read data
 *
 */
struct dev_spi_transfer {
	DEV_SPI_TRANSFER *next;
	/* Calc by software */
	/** tot_len = (tx_totlen>rx_totlen)?tx_totlen:rx_totlen */
	uint32_t tot_len;
	/* Set by user */
	uint8_t *tx_buf;
	uint32_t tx_ofs;
	uint32_t tx_len;
	uint8_t *rx_buf;
	uint32_t rx_ofs;
	uint32_t rx_len;
	/* Should auto set to proper value during set buffer value */
	uint32_t tx_idx;
	uint32_t tx_totlen;	/** tx_totlen = tx_len + tx_ofs */
	uint32_t rx_idx;
	uint32_t rx_totlen;	/** rx_totlen = rx_len + rx_ofs */
};

/** Set tx buffer of device spi transfer */
#define DEV_SPI_XFER_SET_TXBUF(xfer, buf, ofs, len)		{		\
					(xfer)->tx_buf = (uint8_t *)(buf);	\
					(xfer)->tx_len = (uint32_t)(len);	\
					(xfer)->tx_ofs = (uint32_t)(ofs);	\
					(xfer)->tx_idx = 0;			\
					(xfer)->tx_totlen = ( (uint32_t)(len) 	\
							+ (uint32_t)(ofs) ) ;	\
				}

/** Set rx buffer of device spi transfer */
#define DEV_SPI_XFER_SET_RXBUF(xfer, buf, ofs, len)		{		\
					(xfer)->rx_buf = (uint8_t *)(buf);	\
					(xfer)->rx_len = (uint32_t)(len);	\
					(xfer)->rx_ofs = (uint32_t)(ofs);	\
					(xfer)->rx_idx = 0;			\
					(xfer)->rx_totlen = ( (uint32_t)(len) 	\
							+ (uint32_t)(ofs) ) ;	\
				}

/** Calculate total length of current transfer without next transfer */
#define DEV_SPI_XFER_CALC_TOTLEN(xfer)		(xfer)->tot_len =	\
				((xfer)->tx_totlen > (xfer)->rx_totlen) ? (xfer)->tx_totlen : (xfer)->rx_totlen ;

/** Set next SPI transfer */
#define DEV_SPI_XFER_SET_NEXT(xfer, next_xfer)	(xfer)->next = (next_xfer);

/** Init spi transfer */
#define DEV_SPI_XFER_INIT(xfer)					{		\
					(xfer)->tx_idx = 0;			\
					(xfer)->rx_idx = 0;			\
					(xfer)->tx_totlen = ((xfer)->tx_len  	\
							+ (xfer)->tx_ofs) ;	\
					(xfer)->rx_totlen = ((xfer)->rx_len  	\
							+ (xfer)->rx_ofs) ;	\
					DEV_SPI_XFER_CALC_TOTLEN(xfer);		\
				}
/** Flash Access Mode */
typedef enum {
	SPI_M_MODE_SINGLE = 1,	/*!< Single mode  */
	SPI_M_MODE_DUAL = 2,	/*!< Dual mode  */
	SPI_M_MODE_QUAD = 4,	/*!< Quad mode */
} SPI_M_ACCESS_MODE_E;


/**
 * \brief	spi information struct definition
 * \details	informations about spi open state, working state,
 * 	frequency, spi registers, working method, interrupt number
 */
typedef struct dev_spi_info {
	void *spi_ctrl;		/*!< spi control related */
	uint32_t status;	/*!< current working status, refer to \ref DEVICE_HAL_COMMON_DEVSTATUS, this should be \ref DEV_ENABLED for first open */
	uint32_t freq;		/*!< spi working baudrate */
	uint8_t mode;		/*!< spi working mode (master/slave) */
	uint8_t clk_mode;	/*!< spi clock phase and polarity, this should be \ref SPI_CLK_MODE_DEFAULT for first open */
	uint8_t opn_cnt;	/*!< spi open count, open it will increase 1, close it will decrease 1, 0 for close, >0 for open */
	uint8_t slave;		/*!< current selected slave device no, start from 0, this should be \ref SPI_SLAVE_NOT_SELECTED for first open */
	uint8_t dfs;		/*!< data frame size, this should be \ref SPI_DFS_DEFAULT for first open */

	DEV_SPI_TRANSFER xfer;	/*!< spi transfer, this should be set to all zero for first open */
	DEV_SPI_CBS spi_cbs;	/*!< spi callbacks,  this should be all NULL for first open */
	uint32_t dummy;		/*!< dummy write data when send and receive, this should be \ref SPI_DUMMY_DEFAULT for first open */
} DEV_SPI_INFO, * DEV_SPI_INFO_PTR;


#define SPI_DFS_DEFAULT				8		/*!< Default spi data frame size */
#define SPI_SLAVE_NOT_SELECTED			(0xFF)		/*!< Slave is not selected */
#define SPI_DUMMY_DEFAULT			(0xFF)		/*!< default dummy value for first open */

typedef void (*spimcomm_cb_t) (void );

/**
 * \brief	spi device interface definition
 * \details	define spi device interface, like spi information structure,
 * 	fuctions to get spi info, open/close/control spi, send/receive data by spi
 * \note	all this details are implemented by user in user porting code
 */
typedef struct dev_spi {
	DEV_SPI_INFO spi_info;						/*!< spi device information */
	int32_t (*spi_open) (uint32_t mode, uint32_t param, uint32_t cpu_freq);		/*!< open spi master device with mode select to default (SPI_CPOL_0_CPHA_0), param stands for spi frequency.
	  	  	  	  	  	  	  	  cpu frequency is needed for driver to calculate correct divider */
	int32_t (*spi_close) (void);					/*!< close spi device */
	int32_t (*spi_control) (uint32_t ctrl_cmd, void *param);	/*!< control spi device */
	int32_t (*spi_write) (const void *data, uint32_t len);		/*!< send data to spi device (interrupt method) */
	int32_t (*spi_read) (void *data, uint32_t len);			/*!< read data from spi device (interrupt method) */
	int32_t (*spi_write_dma) (const void *data, uint32_t len);		/*!< send data to spi device (dma method) */
	int32_t (*spi_read_dma) (void *data, uint32_t len);			/*!< read data from spi device (dma method) */
	int32_t (*spi_read_dma_status)(void); /*!< check if read done (dma method) */
	int32_t (*spi_write_ptl) (SPI_M_ACCESS_MODE_E mode, const void *data_packet, uint32_t data_len, uint8_t data_type);		/*!< send data to spi device ( method with protocol) */
	int32_t (*spi_write_ptl_cus) (const void *header_buf, uint32_t header_len, const void *data_packet, uint32_t data_len);	/*!< send data to spi device ( method with user-defined protocol) */
	int32_t (*spi_write_ptl_halt) (void);		/*!<halt all writing data */
	int32_t (*spi_read_ptl) (const void *data_packet, uint32_t *data_len);		/*!< read data from spi device ( method with protocol) */

	int32_t (*flash_id) (unsigned char *data); /*!< read eeprom id information */
	int32_t (*flash_read) (SPI_M_ACCESS_MODE_E mode, uint32_t flash_addr, unsigned char *data, uint32_t len); /*!< read eeprom with address, length information */
	int32_t (*flash_word_read) (SPI_M_ACCESS_MODE_E mode, uint32_t flash_addr, uint32_t *data, uint32_t len); /*!< word read eeprom with address, length information */
	int32_t (*flash_write) (SPI_M_ACCESS_MODE_E mode, uint32_t flash_addr, unsigned char *data, uint32_t len, bool word_switch); /*!< write eeprom with address, length information. word_switch-when storage data in waord type, change word_switch to true for little endian/big endian switch */
	int32_t (*flash_word_write) (SPI_M_ACCESS_MODE_E mode, uint32_t flash_addr, uint32_t *data, uint32_t len); /*!< word write eeprom with address, length information */
	int32_t (*flash_erase_all) (void); /*!< chip erase select eeprom */
	int32_t (*flash_erase_sector) (uint32_t flash_addr); /*!< sector erase by given flash address */
	int32_t (*flash_set_xip) ( bool xip_enable, SPI_M_ACCESS_MODE_E xip_mode); /*!< set select eeprom to specific XIP mode. xip_enable- set enable/disable XIP mode. xip_mode- set XIP mode, support dual mode pr quad mode*/
	int32_t (*flash_Send_Op_code) (uint8_t *data, uint32_t len); /*!< send op command to select eeprom */

} DEV_SPI, * DEV_SPI_PTR;



#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief	get current spi master handle, initial device if needed
 *
 * \param[in]	spi_id	 send id as input to get handle
 * \return	handler of select spi master.
 */
extern DEV_SPI_PTR hx_drv_spi_mst_get_dev(USE_DW_SPI_MST_E spi_id);

/**
 * \brief	initial select spi master
 *
 * \param[in]	spi_id	 select spi master
 * \return	error id.
 */
extern int hx_drv_spi_mst_init(USE_DW_SPI_MST_E spi_id);

/**
 * \brief	de-initial select spi master
 *
 * \param[in]	spi_id	 select spi master
 * \return	error id.
 */
extern int hx_drv_spi_mst_deinit(USE_DW_SPI_MST_E spi_id);

/**
 * \brief	callback register function, it register tx done callback
 *
 * \param[in]	aWritecb   callback function pointer
 * \return	error id.
 */
extern int hx_spimcomm_register_tx_cb(spimcomm_cb_t aWritecb);

/**
 * \brief	callback register function, it register rx done callback
 *
 * \param[in]	aReadcb   callback function pointer
 * \return	error id.
 */
extern int hx_spimcomm_register_rx_cb(spimcomm_cb_t aReadcb);
#ifdef __cplusplus
}
#endif

/** @} */
#endif /* INC_HX_DRV_SPI_M_H_ */

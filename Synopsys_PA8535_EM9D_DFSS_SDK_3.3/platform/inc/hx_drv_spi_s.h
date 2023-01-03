/**
 * @file hx_drv_spi_s.h
 * @author himax/902452
 * @brief 
 * @version V1.0.0
 * @date 2018-10-05
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef INC_HX_DRV_SPI_S_H_
#define INC_HX_DRV_SPI_S_H_

#include "dev_common.h"

/**
 * \defgroup	DEVICE_HAL_SPI_SLV_OBJ	SPI Slave Device Object Instance
 * \ingroup	DEVICE_HAL_SPI_SLV
 * \brief	Macros for spi slave instance.
 * \details	Definitions for spi slave instance.
 * @{
 */
#define DFSS_SPI_SLV_NUM		(1)	/*!< Datafusion SPI slave valid number */

#define DFSS_SPI_SLV_0_ID		0	/*!< SPI 0 id macro (slave node) */
#define DFSS_SPI_SLV_ALL_ID	DFSS_SPI_SLV_NUM

typedef enum USE_DFSS_SPI_SLV_S
{
	USE_DFSS_SPI_SLV_0 = DFSS_SPI_SLV_0_ID,    		/*!< enable use datafusion subsystem spi slave 0 */
	USE_DFSS_SPI_SLV_ALL = DFSS_SPI_SLV_ALL_ID,		/*!< enable use datafusion subsystem spi slave all */
	USE_DFSS_SPI_SLV_MAX
}USE_DFSS_SPI_SLV_E;

/** @} */


/**
 * \defgroup	DEVICE_HAL_SPI_SLV_CTRLCMD		SPI Slave Device Control Commands
 * \ingroup	DEVICE_HAL_SPI_SLV
 * \brief	Definitions for spi slave control command, used in \ref dev_spi::spi_control "SPI IO Control"
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
 * - Usage Comment
 *     If there is a operation is running, any other operation will return \ref E_CTX
 * @{
 */

/** Define SPI control commands for common usage */
#define DEV_SET_SPI_SYSCMD(cmd)		DEV_SET_SYSCMD((cmd))
/** Define SPI control commands for master usage */
//#define DEV_SET_SPI_MST_SYSCMD(cmd)	DEV_SET_SYSCMD(0x00001000|(cmd))
/** Define SPI control commands for slave usage */
#define DEV_SET_SPI_SLV_SYSCMD(cmd)	DEV_SET_SYSCMD(0x00002000|(cmd))


/* ++++ Common commands for SPI Device ++++ */

/**
 * set the \ref dev_spi_info::clk_mode "clock mode" of spi slave transfer
 * - Param type : uint32_t
 * - Param usage : spi slave clock mode to choose clock phase and clock polarity
 * - Return value explanation :
 */
#define SPI_CMD_SET_CLK_MODE			DEV_SET_SPI_SYSCMD(1)
/**
 * set spi slave \ref dev_spi_info::dfs "data frame size"
 * - Param type : uint32_t
 * - Param usage : should > 0, currently support 8 and 32 bits
 * - Return value explanation : If dfs is not supported, then return \ref E_SYS
 */
#define SPI_CMD_SET_DFS				DEV_SET_SPI_SYSCMD(2)

/* ++++ end of Common commands for SPI Device ++++ */

/** @} */

/**
 * \defgroup	DEVICE_HAL_SPI_CALLBACK	SPI Interrupt callback functions
 * \ingroup	DEVICE_HAL_SPI
 * \brief	callback function structure for SPI device
 * @{
 */
typedef struct dev_spi_slv_cbs {
	DEV_CALLBACK tx_cb;	/*!< spi slave data transmit success required bytes callback */
	DEV_CALLBACK rx_cb;	/*!< spi slave data receive success required bytes callback */
	DEV_CALLBACK err_cb;	/*!< spi slave error callback */
	DEV_CALLBACK xfer_cb;	/*!< transfer callback */
} DEV_SPI_SLV_CBS, *DEV_SPI_SLV_CBS_PTR;
/** @} */

/**
 * \defgroup	DEVICE_HAL_SPI_CLK_MODE	SPI Clock Mode
 * \ingroup	DEVICE_HAL_SPI
 * \brief	spi slave clock mode settings
 * @{
 */
/** SPI Clock Mode */
typedef enum spi_slv_clk_mode {
	SPI_S_CPOL_0_CPHA_0 = 0,	/*!< Inactive state of serial clock is low, serial clock toggles in middle of first data bit */
	SPI_S_CPOL_0_CPHA_1 = 1,	/*!< Inactive state of serial clock is low, serial clock toggles at start of first data bit  */
	SPI_S_CPOL_1_CPHA_0 = 2,	/*!< Inactive state of serial clock is high, serial clock toggles in middle of first data bit */
	SPI_S_CPOL_1_CPHA_1 = 3,	/*!< Inactive state of serial clock is high, serial clock toggles at start of first data bit */

	SPI_S_CLK_MODE_0    = SPI_S_CPOL_0_CPHA_0,	/*!< Equal to \ref SPI_CPOL_0_CPHA_0 */
	SPI_S_CLK_MODE_1    = SPI_S_CPOL_0_CPHA_1,	/*!< Equal to \ref SPI_CPOL_0_CPHA_1 */
	SPI_S_CLK_MODE_2    = SPI_S_CPOL_1_CPHA_0,	/*!< Equal to \ref SPI_CPOL_1_CPHA_0 */
	SPI_S_CLK_MODE_3    = SPI_S_CPOL_1_CPHA_1	/*!< Equal to \ref SPI_CPOL_1_CPHA_1 */
} SPI_SLV_CLK_MODE;

//typedef SPI_SLV_CLK_MODE				DEV_SPI_SLV_CLK_MODE;

/*!< Default SPI device clock mode */
#define SPI_SLV_CLK_MODE_DEFAULT		SPI_S_CPOL_0_CPHA_0
/** @} */


/**
 * \defgroup	DEVICE_HAL_SPI_DEVSTRUCT	SPI Device Structure
 * \ingroup	DEVICE_HAL_SPI
 * \brief	contains definitions of spi slave device structure.
 * \details	this structure will be used in user implemented code, which was called
 * 	Device Driver Implement Layer for spi slave to realize in user code.
 * @{
 */
typedef struct dev_spi_slv_transfer DEV_SPI_SLV_TRANSFER, *DEV_SPI_SLV_TRANSFER_PTR;
/**
 * \brief	spi slave read and write data structure used by \ref SPI_CMD_TRANSFER
 * 	spi slave write then read data
 *
 */
struct dev_spi_slv_transfer {
	DEV_SPI_SLV_TRANSFER *next;
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

/**
 * \brief	spi slave information structure definition
 * \details	informations about spi slave open state, working state,
 * 	frequency, spi slave registers, working method, interrupt number
 */
typedef struct dev_spi_slv_info {
	void *spi_ctrl;		/*!< spi slave control related */
	uint32_t status;	/*!< current working status, refer to \ref DEVICE_HAL_COMMON_DEVSTATUS, this should be \ref DEV_ENABLED for first open */
	uint32_t freq;		/*!< spi slave working baudrate */
	uint8_t mode;		/*!< spi slave working mode (master/slave) */
	uint8_t clk_mode;	/*!< spi slave clock phase and polarity, this should be \ref SPI_CLK_MODE_DEFAULT for first open */
	uint8_t opn_cnt;	/*!< spi slave open count, open it will increase 1, close it will decrease 1, 0 for close, >0 for open */
	uint8_t slave;		/*!< current selected slave device no, start from 0, this should be \ref SPI_SLAVE_NOT_SELECTED for first open */
	uint8_t dfs;		/*!< data frame size, this should be \ref SPI_DFS_DEFAULT for first open */

	DEV_SPI_SLV_TRANSFER xfer;	/*!< spi slave transfer, this should be set to all zero for first open */
	DEV_SPI_SLV_CBS spi_cbs;	/*!< spi slave callbacks, for both master and slave mode, this should be all NULL for first open */
	void *extra;		/*!< a extra pointer to get hook to applications which should not used by bsp developer,
					this should be NULL for first open and you can \ref DEV_SPI_INFO_SET_EXTRA_OBJECT "set"
					or \ref DEV_SPI_INFO_GET_EXTRA_OBJECT "get" the extra information pointer */
	uint32_t dummy;		/*!< dummy write data when send and receive, this should be \ref SPI_DUMMY_DEFAULT for first open */
} DEV_SPI_SLV_INFO, * DEV_SPI_SLV_INFO_PTR;

/** Set extra information pointer of spi slave info */
//#define DEV_SPI_SLV_INFO_SET_EXTRA_OBJECT(spi_info_ptr, extra_info)		(spi_info_ptr)->extra = (void *)(extra_info)
/** Get extra information pointer of spi slave info */
//#define DEV_SPI_SLV_INFO_GET_EXTRA_OBJECT(spi_info_ptr)			((spi_info_ptr)->extra)



/**
 * \brief	spi slave device interface definition
 * \details	define spi slave device interface, like spi slave information structure,
 * 	fuctions to get spi slave info, open/close/control spi, send/receive data by spi
 * \note	all this details are implemented by user in user porting code
 */
typedef struct dev_spi_slv {
	DEV_SPI_SLV_INFO spi_info;						/*!< spi slave device information */
	int32_t (*spi_open) (uint32_t mode, uint32_t param);		/*!< open spi slave device,  \
									when in slave mode, param stands for clock mode and default data frame size is 8 bits */
	int32_t (*spi_close) (void);					/*!< close spi slave device */
	int32_t (*spi_control) (uint32_t ctrl_cmd, void *param);	/*!< control spi slave device */
	int32_t (*spi_write) (const void *data, uint32_t len);		/*!< send data to spi master device (dma method) */
	int32_t (*spi_write_ptl) (const void *data, uint32_t len, uint8_t data_type);		/*!< send data to spi master device with protocol (dma method) */
	int32_t (*spi_write_ptl_cus) (const void *header_buf, uint32_t header_len,  /*!< send data to spi master device (method with user-defined protocol) */
								 const void *data, uint32_t len); 
	int32_t (*spi_write_halt) ();		/*!< it stops the spi_write operation, any data in the buffer will not write out and will be ignored  */
	int32_t (*spi_read) (void *data, uint32_t len);			/*!< read data from spi master device (dma method) */
	int32_t (*spi_read_halt) ();			/*!< halt read data function, un-read data will be ignored  */
	int32_t (*spi_read_pp) (void *data1, void *data2, uint32_t len);			/*!< read data from spi master device (recursive ping pong method) len should be smaller than 256KB */
	int32_t (*spi_read_pp_halt) ();			/*!< read data ping pong mode halt  */


} DEV_SPI_SLV, * DEV_SPI_SLV_PTR;


/** @} */

typedef void (*hx_drv_spi_s_cb_t) (void );

#ifdef __cplusplus
extern "C" {
#endif

extern DEV_SPI_SLV_PTR hx_drv_spi_slv_get_dev(USE_DFSS_SPI_SLV_E spi_id);

extern int hx_drv_spi_slv_init(USE_DFSS_SPI_SLV_E spi_id);

extern int hx_drv_spi_slv_deinit(USE_DFSS_SPI_SLV_E spi_id);

extern int hx_drv_spi_slv_register_tx_cb(hx_drv_spi_s_cb_t aWritecb);

extern int hx_drv_spi_slv_register_rx_cb(hx_drv_spi_s_cb_t aReadcb);

extern int hx_drv_spi_slv_register_rx_evt_cb(hx_drv_spi_s_cb_t aEvtReadcb);

#ifdef __cplusplus
}
#endif
#endif /* INC_HX_DRV_SPI_S_H_ */

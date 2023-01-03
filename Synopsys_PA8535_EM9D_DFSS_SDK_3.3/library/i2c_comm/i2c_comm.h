/**
 ********************************************************************************************
 *  @file      i2c_comm.h
 *  @details   This file contains all i2c communication protocol related function
 *  @author    himax/902452
 *  @version   V1.0.0
 *  @date      14-July-2019
 *  @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 *******************************************************************************************/
#ifndef LIBRARY_I2C_COMM_I2C_COMM_H_
#define LIBRARY_I2C_COMM_I2C_COMM_H_
/**
 * \defgroup	I2C_COMM	I2C Communication Library
 * \ingroup	I2C_COMM
 * \brief	I2C communication library declaration
 */

#include "i2c_comm_cfg.h"

/****************************************************
 * Support Feature List                             *
 ***************************************************/

/****************************************************
 * Constant Definition                              *
 ***************************************************/

/* I2C Communication Protocol : Format / Field Definition
 * [Feature] [CMD] [Payload Len] [Payload] [checksum]
 * [Feature] - one byte
 * [CMD]     - one byte
 * [PL_LEN ] - two bytes
 * [Payload] - 256bytes (MAX)
 * [checksum]- two bytes (ccitt-crc16)
 */
#define I2CCOMM_HEADER_SIZE     4
#define I2CCOMM_PAYLOAD_SIZE    256
#define I2CCOMM_CHECKSUM_SIZE   2
#define I2CCOMM_MAX_WBUF_SIZE   (I2CCOMM_HEADER_SIZE + I2CCOMM_PAYLOAD_SIZE + I2CCOMM_CHECKSUM_SIZE)
#define I2CCOMM_MAX_RBUF_SIZE   (I2CCOMM_HEADER_SIZE + I2CCOMM_PAYLOAD_SIZE + I2CCOMM_CHECKSUM_SIZE)

// Feature Code
#define I2CFMT_FEATURE_OFFSET   0
#define I2CFMT_FEATURE_SIZE     1

// Command Code
#define I2CFMT_COMMAND_OFFSET   1
#define I2CFMT_COMMAND_SIZE     1

// Payload Length
#define I2CFMT_PAYLOADLEN_LSB_OFFSET    2
#define I2CFMT_PAYLOADLEN_MSB_OFFSET    3
#define I2CFMT_PAYLOADLEN_SIZE          2

// Payload buffer
#define I2CFMT_PAYLOAD_OFFSET           4
#define I2CFMT_PAYLOAD_SIZE             I2CCOMM_PAYLOAD_SIZE

/* I2CCOMM_FEATURE_SYS : Payload Length Definition of RX buffer
 * I2CCOMM_SYS_CMD_E Command Payload Size for i2c master read
 */
#define I2CCOMM_SYS_CMD_PAYLOAD_VER_BSP     4 // I2CCOMM_CMD_SYS_GET_VER_BSP
#define I2CCOMM_SYS_CMD_PAYLOAD_VER_I2C     4 // I2CCOMM_CMD_SYS_GET_VER_I2C

/* I2CCOMM_FEATURE_REG : Payload Length Definition of RX buffer
 * I2CCOMM_REG_CMD_E Command Payload Size for i2c master read
 */
#define I2CCOMM_REG_CMD_PAYLOAD_AHB_REG     4 // I2CCOMM_CMD_AHB_REG_GET
#define I2CCOMM_REG_CMD_PAYLOAD_AUX_REG     4 // I2CCOMM_CMD_AUX_REG_GET

/* I2CCOMM_FEATURE_QUANTA_ISH : Payload Length Definition of RX buffer
 * I2CCOMM_QUANDA_CMD_E Command Payload Size for i2c master read
 */
#define I2CCOMM_QUANTA_CMD_PAYLOAD_STATE    1   // I2CCOMM_CMD_QUANDA_FD_GET_STATE

#ifdef EMZA_ALGO_FACE_V2
#define I2CCOMM_QUANTA_CMD_PAYLOAD_RESULT   34 // I2CCOMM_CMD_QUANDA_FD_GET_RESULT
#else
#define I2CCOMM_QUANTA_CMD_PAYLOAD_RESULT   18 // I2CCOMM_CMD_QUANDA_FD_GET_RESULT
#endif

#define I2CCOMM_GPIO_CMD_PAYLOAD_GET_VAL    1
#define I2CCOMM_SENSOR_CMD_PAYLOAD_GET_VAL  1
/****************************************************
 * ENUM Declaration                                 *
 ***************************************************/
/**
 * \defgroup	I2C_COMM_ENUM	I2C Communication Library Enumeration
 * \ingroup	I2C_COMM
 * \brief	Defines the required enumeration of I2C communication library.
 * @{
 */

/**
 * \enum I2C_COMM_ERROR_E
 * \brief this enumeration use in i2c communication process, define return code of the provided function
 */
typedef enum
{
    I2CCOMM_NO_ERROR = 0,             /**< No ERROR */
    I2CCOMM_ERROR_DRIVER_FAIL,        /**< ERROR MSG: i2c driver fail */
    I2CCOMM_ERROR_NOT_INIT,           /**< ERROR MSG: not init */
    I2CCOMM_ERROR_ALREADY_INIT,       /**< ERROR MSG: already init */
    I2CCOMM_ERROR_INVALID_PARAMETERS, /**< ERROR MSG: Invalid parameters */
    I2CCOMM_ERROR_BUFFER_NOT_ASSIGN,  /**< ERROR MSG: Without assign read/write buffer */
    I2CCOMM_ERROR_DRVIER_WRITE_FAIL,  /**< ERROR MSG: I2C Slave Fail to execute i2c write */
    I2CCOMM_ERROR_DRVIER_READ_FAIL,   /**< ERROR MSG: I2C Slave Fail to execute i2c read */
    I2CCOMM_ERROR_CHECKSUM,           /**< ERROR MSG: I2C Read/Write checksum error */
    I2CCOMM_ERROR_UNKNOWN             /**< ERROR MSG: UNKNOWN ERROR*/
} I2CCOMM_ERROR_E;

/**
 * \enum I2C_COMM_STATUS_E
 * \brief this enumeration use in i2c communication library, define the status of i2c communication process.
 */
typedef enum
{
    I2CCOMM_STATUS_CLOSE = 0, /**< STATUS: Close state - the process is closed (disconnect to i2c driver)*/
    I2CCOMM_STATUS_OPEN,      /**< STATUS: Open state - the library is opened (connect to i2c driver) */
    I2CCOMM_STATUS_INIT,      /**< STATUS: Init state - the library is initialized */
#if 0                         // [Option] - Currently, not support
	I2CCOMM_STTAUS_IDLE		                	,	/**< STATUS: Idle state - wait i2c write command to process */
	I2CCOMM_STATUS_BUSY				     		,	/**< STATUS: Busy state - library is processing write or read command */
	I2CCOMM_STATUS_SUSPEND     					,	/**< STATUS: Suspend state - process is been suspend*/
	I2CCOMM_STATUS_WAIT							,   /**< STATUS: Wait state - the process is waiting for read command due to previous W/R cmd */
#endif
    I2CCOMM_STATUS_UNKNOWN /**< STATUS: Unknown status - abnormal state */
} I2CCOMM_STATUS_E;

/**
 * \enum I2CCOMM_FEATURE_E
 * \brief this enumeration use in i2c communication library, define the supported feature.
 */
typedef enum
{
    I2CCOMM_FEATURE_SYS                 = 0x00, /**< SUPPORT FEATURE: system information*/
    I2CCOMM_WEI_REG_ACCESS              = 0x10, /**< SUPPORT FEATURE: WE-I Register read/write*/
    I2CCOMM_WEI_GPIO_CTRL               = 0x11,
    I2CCOMM_SENSOR_REG_ACCESS           = 0x20,
    I2CCOMM_FEATURE_QUANTA_ISH          = 0x30, /**< SUPPORT FEATURE: Quanta NB Product - ISH communication*/
    I2CCOMM_FEATURE_SPI                 = 0x40,
    I2CCOMM_FEATURE_OTA_RESERVED        = 0x50,
    I2CCOMM_FEATURE_OTA_ALL             = 0x51,
    I2CCOMM_FEATURE_OTA_MEM_DSP         = 0x52,
    I2CCOMM_FEATURE_OTA_APP             = 0x53,
    I2CCOMM_FEATURE_OTA_APP_CONFIG      = 0x54,
    I2CCOMM_FEATURE_OTA_EMZA_CONFIG     = 0x55,
    I2CCOMM_FEATURE_OTA_CNNLUT          = 0x56,
    I2CCOMM_FEATURE_CSTM_SECURE_DGB 	= 0x70,
    I2CCOMM_FEATURE_AUDIO_TEST			= 0x57,

    I2CCOMM_FEATURE_CUSTOMER_MIN        = 0x80,
    I2CCOMM_FEATURE_CUSTOMER_MAX        = 0x8F,
    I2CCOMM_FEATURE_MAX
} I2CCOMM_FEATURE_E;

/**
 * \enum I2CCOMM_SYS_CMD_E
 * \brief this enumeration use in i2c communication library, define the supported system command.
 */
typedef enum
{
    I2CCOMM_CMD_SYS_GET_VER_BSP = 0, /**< System CMD : get version number of BSP */
    I2CCOMM_CMD_SYS_GET_VER_I2C,     /**< System CMD : get version number of I2C communication protocol */
    I2CCOMM_CMD_SYS_GET_VER_FORMAL,  /**< System CMD : get formal version number of BSP */
    I2CCOMM_CMD_SYS_MAX
} I2CCOMM_SYS_CMD_E;

/**
 * \enum I2CCOMM_REG_CMD_E
 * \brief this enumeration use in i2c communication library, define the supported WE-I register read/write command.
 */
typedef enum
{
    I2CCOMM_CMD_AHB_REG_GET = 0, /**< Register CMD : get AHB register */
    I2CCOMM_CMD_AHB_REG_SET,     /**< Register CMD : set AHB register */
    I2CCOMM_CMD_AUX_REG_GET,     /**< Register CMD : get AUX register */
    I2CCOMM_CMD_AUX_REG_SET,     /**< Register CMD : set AUX register */
    I2CCOMM_CMD_REG_MAX
} I2CCOMM_REG_CMD_E;

/**
 * \enum I2CCOMM_GPIO_CMD_E
 * \brief this enumeration use in i2c communication library, define the supported GPIO control command.
 */
typedef enum
{
    I2CCOMM_CMD_GPIO_MUX = 0, /**< GPIO CMD : set io mux */
    I2CCOMM_CMD_GPIO_SET,     /**< GPIO CMD : set value */
    I2CCOMM_CMD_GPIO_GET,     /**< GPIO CMD : get value */
    I2CCOMM_CMD_IO_MAX
} I2CCOMM_GPIO_CMD_E;

/**
 * \enum I2CCOMM_SENSOR_CMD_E
 * \brief this enumeration use in i2c communication library, define the supported sensor register r/w command.
 */
typedef enum
{
    I2CCOMM_CMD_SENSOR_REG_SET = 0, /**< Sensor Register CMD: set register */
    I2CCOMM_CMD_SENSOR_REG_GET,     /**< Sensor Register CMD: get value */
    I2CCOMM_CMD_SENSOR_MAX
} I2CCOMM_SENSOR_CMD_E;

/**
 * \enum I2CCOMM_QUANTA_CMD_E
 * \brief this enumeration use in i2c communication library, define the supported quanta ish command.
 */
typedef enum
{
    I2CCOMM_CMD_QUANDA_FD_SET_START = 0, /**< Quanta CMD : control WEI to start face detection */
    I2CCOMM_CMD_QUANDA_FD_SET_STOP,      /**< Quanta CMD : control WEI to stop face detection */
    I2CCOMM_CMD_QUANDA_FD_GET_STATE,     /**< Quanta CMD : control WEI to get state */
    I2CCOMM_CMD_QUANDA_FD_GET_RESULT,    /**< Quanta CMD : control WEI to get algorithm result */
    I2CCOMM_CMD_QUANDA_FD_SET_STANDBY0,  /**< Quanta CMD : control WEI to enter CDM and SLEEP1 mode*/
    I2CCOMM_CMD_QUANDA_FD_SET_STANDBY1,  /**< Quanta CMD : control WEI to enter CDM and ALL ON mode */
    I2CCOMM_CMD_QUANDA_MAX
} I2CCOMM_QUANDA_CMD_E;

/**
 * \enum I2CCOMM_OTA_CMD_E
 * \brief this enumeration use in i2c communication library, define the supported OTA command.
 */
typedef enum
{
    I2CCOMM_CMD_OTA_GET_VER=0x0,
    I2CCOMM_CMD_OTA_GET_PROJID=0x1,
    I2CCOMM_CMD_OTA_START=0x2,
    I2CCOMM_CMD_OTA_DATA=0x3,
    I2CCOMM_CMD_OTA_END=0x4,
    I2CCOMM_CMD_OTA_SENT_RESULT=0x5,
    I2CCOMM_CMD_OTA_ABORT=0x6,
    I2CCOMM_CMD_OTA_JUMP2UPG=0x7,
    I2CCOMM_CMD_OTA_SEND_CHIP_ID=0x8,
    I2CCOMM_CMD_OTA_TURN_ON_ECI=0x9,
    I2CCOMM_CMD_OTA_TURN_OFF_ECI=0xA,
    I2CCOMM_CMD_OTA_TURN_OFF_PDM=0xB,
    I2CCOMM_CMD_OTA_AUDIO_RECOGNITION_INIT=0xC,
    I2CCOMM_CMD_OTA_AUDIO_RECOGNITION_RECV_DATA=0xD,
    I2CCOMM_CMD_OTA_AUDIO_RECOGNITION=0xE,
    I2CCOMM_CMD_OTA_GET_AUDIO_RESULT=0xF,
    I2CCOMM_CMD_OTA_GET_ALGO_ID=0x14,
    I2CCOMM_CMD_OTA_MAX
} I2CCOMM_OTA_CMD_E;
/**
 * \enum I2CCOMM_AUDIO_TEST_CMD_E
 * \brief this enumeration use in i2c communication library, define the supported OTA command.
 */
typedef enum
{
	I2CCOMM_CMD_AUDIO_INIT_PDM,
	I2CCOMM_CMD_AUDIO_TURN_OFF_PDM,
	I2CCOMM_CMD_AUDIO_PDM_RECORD,
	I2CCOMM_CMD_AUDIO_PDM_GETBUF,
	I2CCOMM_CMD_AUDIO_TEST_RECV_DATA_SIZE,
	I2CCOMM_CMD_AUDIO_TEST_RECV_DATA,
	I2CCOMM_CMD_AUDIO_TEST_RECOGNITION,
	I2CCOMM_CMD_AUDIO_GET_RESULT,
	I2CCOMM_CMD_AUDIO_ALANGO_PROCESS,
	I2CCOMM_CMD_AUDIO_ALANGO_DATA,
	I2CCOMM_CMD_AUDIO_SEND_DATA,
	I2CCOMM_CMD_AUDIO_OPEN_Measure,
	I2CCOMM_CMD_AUDIO_OFF_Measure,
	I2CCOMM_CMD_AUDIO_Reset,
} I2CCOMM_AUDIO_CMD_E;


/**
 * \brief this enumeration use in i2c communication library, define the supported SPI feature.
 */
#define SPI_DISABLE_ALGO     (1<<7)

#define SPI_ENABLE_PDM       (1<<5)
#define SPI_ENABLE_RAWIMG    (1<<4)
#define SPI_ALL_ON           (1<<3)
#define SPI_ENABLE_JPEG      (1<<2)
#define SPI_ENABLE_METADATA  (1<<1)
#define SPI_ENABLE_VOICE     (1<<0)
#define SPI_ENABLE_ALL       (SPI_ALL_ON | SPI_ENABLE_JPEG | SPI_ENABLE_METADATA | SPI_ENABLE_VOICE | SPI_ENABLE_RAWIMG | SPI_ENABLE_PDM)

/** @} */

/****************************************************
 * Type Definition                                 *
 ***************************************************/
/**
 * \brief I2C Communication callback function type definition
 *
 * \param[in] void * pointer to read/write header
 * \param[in] void * pointer to read/write buffer
 * \param[in] uint8_t feature code
 * \param[in] uint8_t command type
 * \param[in] uint8_t checksum value
 * \retval void.
 */
//typedef void (*i2ccomm_write_cb_t) (I2CCOMM_HEADER_T *, uint8_t*, uint8_t);
typedef void (*i2ccomm_cb_t)(void *);

/****************************************************
 * Structure Definition                             *
 ***************************************************/
/**
 * \defgroup	I2C_COMM_STRUCT		I2C Communication Library Structure
 * \ingroup	I2C_COMM
 * \brief	Defines the required structure of I2C Communication library.
 * @{
 */

/**
 * \struct I2CCOMM_HEADER_T
 * \brief I2C Command Header
 */
typedef struct
{
    uint8_t fcode;       /*!< I2CCOMM Format : feature code */
    uint8_t cmd_type;    /*!< I2CCOMM Format : command type */
    uint8_t payload_len; /*!< I2CCOMM Format : payload length */
} I2CCOMM_HEADER_T;

/**
 * \struct I2CCOMM_FMT_T
 * \brief I2C Command Format
 */
typedef struct
{
    uint8_t fcode;       /*!< I2CCOMM Format : feature code */
    uint8_t cmd_type;    /*!< I2CCOMM Format : command type */
    uint8_t payload_len; /*!< I2CCOMM Format : payload length */
    uint8_t *payload;    /*!< I2CCOMM Format : payload buffer */
    uint8_t checksum;    /*!< I2CCOMM Format : checksum value */
} I2CCOMM_FMT_T;

/**
 * \struct I2CCOMM_CFG_T
 * \brief I2C Communication Configuration
 */
typedef struct
{
    unsigned int slv_addr; /*!< I2CCOMM Format : feature code */
    i2ccomm_cb_t write_cb;
    i2ccomm_cb_t read_cb;
    i2ccomm_cb_t err_cb;
} I2CCOMM_CFG_T;

/** @} */ //I2C_COMM_STRUCT

/****************************************************
 * Function Declaration                             *
 ***************************************************/
/**
 * \defgroup	I2C_COMM_FUNCDLR	I2C Communication library Function Declaration
 * \ingroup	I2C_COMM
 * \brief	Contains declarations of I2C Communication library functions.
 * @{
 */

/**
 * \brief	The function use to open the i2c communication library
 *
 * Close the i2c communication library to connect i2c slave driver.
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_open(void);

/**
 * \brief	The function use to close the i2c communication library
 *
 * Open the i2c communication library to disconnect i2c slave driver.
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_close(void);

/**
 * \brief	The function use to initial the i2c communication protocol
 *
 * Initialize the i2c communication library.
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_init(I2CCOMM_CFG_T aCfg);

/**
 * \brief	The function use to deinitialize the i2c communication protocol
 *
 * Deinitialize the i2c communication library.
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_deinit(void);

/**
 * \brief	The function use to register callback function of IIC communication process.
 *
 * Register callback function.
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_register_cb(i2ccomm_cb_t aReadcb, i2ccomm_cb_t aRWritecb);

/**
 * \brief	The function use to enable i2c slave read process to monitor the i2c master's write command
 *
 * Start to execute the i2c communication read process : enable to monitor the i2c write command from i2c master.
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_enable_read(unsigned char *rbuf, uint32_t size);

/**
 * \brief	The function use to enable i2c slave write process to monitor the i2c master's read command
 *
 * Start to execute the i2c communication write process : enable to monitor the i2c read command from i2c master.
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_enable_write(unsigned char *wbuf);

/**
 * \brief	The function use to start the i2c communication process
 *
 * Stop the i2c communication process : start to monitor the i2c write command on i2c bus.
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_start(unsigned char *rbuf, uint32_t size);

/**
 * \brief	The function use to stop the i2c communication process
 *
 * Stop the i2c communication process : suspend to monitor the i2c command on i2c bus.
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_stop(void);

/**
 * \brief	The function use to get the status of i2c communication process
 *
 * Get the status of i2c communication process
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_status(I2CCOMM_STATUS_E *aStatus);

/**
 * \brief	The function use to get the version of i2c communication process
 *
 * Get the version of i2c communication process
 * \retval	uint32_t version number
 */
uint32_t hx_lib_i2ccomm_version(void);

/**
 * \brief	The function use to validate that whether the checksum is correct or not.
 *
 * Process validate checksum field is correct or not
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_validate_checksum(unsigned char *aBuf);

/**
 * \brief	The function use to generate checksum with the associated buffer data.
 *
 * Process generate checksum value using ccitt_crc16
 * \retval	I2CCOMM_NO_ERROR	no error
 * \retval	others	error
 */
I2CCOMM_ERROR_E hx_lib_i2ccomm_generate_checksum(unsigned char *aBuf, unsigned int aSize, unsigned short *aCRC);

/** @} */ //I2C_COMM_FUNCDLR

#endif /* LIBRARY_I2C_COMM_I2C_COMM_H_ */

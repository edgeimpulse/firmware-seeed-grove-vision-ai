/**
 ********************************************************************************************
 *  @file      isp_comm.h
 *  @details   This file contains all isp communication protocol related function
 *  @author    himax/902453
 *  @version   V1.0.0
 *  @date      14-July-2019
 *  @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 *******************************************************************************************/
#ifndef LIBRARY_ISP_COMM_ISP_COMM_H_
#define LIBRARY_ISP_COMM_ISP_COMM_H_
/**
 * \defgroup	ISP_COMM	ISP Communication Library
 * \ingroup	ISP_COMM
 * \brief	ISP communication library declaration
 */

#include "isp_comm_cfg.h"
#include "hx_drv_iomux.h"

/****************************************************
 * Constant Definition                              *
 ***************************************************/


/****************************************************
 * ENUM Declaration                                 *
 ***************************************************/
/**
 * \defgroup	ISP_COMM_ENUM	ISP Communication Library Enumeration
 * \ingroup	ISP_COMM
 * \brief	Defines the required enumeration of ISP communication library.
 * @{
 */

/**
 * \enum ISP_COMM_ERROR_E
 * \brief this enumeration use in isp communication process, define return code of the provided function
 */
typedef enum
{
	ISPCOMM_NO_ERROR                     	 = 0,	/**< No ERROR */
	ISPCOMM_ERROR_DRIVER_FAIL					,   /**< ERROR MSG: isp driver fail */
	ISPCOMM_ERROR_NOT_INIT              	    ,	/**< ERROR MSG: not init */
	ISPCOMM_ERROR_ALREADY_INIT                	,	/**< ERROR MSG: already init */
	ISPCOMM_ERROR_INVALID_PARAMETERS     		,	/**< ERROR MSG: Invalid parameters */
	ISPCOMM_ERROR_BUFFER_NOT_ASSIGN				,   /**< ERROR MSG: Without assign read/write buffer */
	ISPCOMM_ERROR_DRVIER_WRITE_FAIL				,   /**< ERROR MSG: ISP Slave Fail to execute isp write */
	ISPCOMM_ERROR_DRVIER_READ_FAIL				,   /**< ERROR MSG: ISP Slave Fail to execute isp read */
	ISPCOMM_ERROR_CHECKSUM						,   /**< ERROR MSG: ISP Read/Write checksum error */
	ISPCOMM_ERROR_UNKNOWN      						/**< ERROR MSG: UNKNOWN ERROR*/
} ISPCOMM_ERROR_E;


/**
 * \enum ISP_COMM_STATUS_E
 * \brief this enumeration use in isp communication library, define the status of isp communication process.
 */
typedef enum
{
	ISPCOMM_STATUS_UNINIT	             	= 0,	/**< STATUS: Close state - the process is closed*/
	ISPCOMM_STATUS_INIT		             	   ,	/**< STATUS: Init state - the library is initialized */
	ISPCOMM_STATUS_UNKNOWN							/**< STATUS: Unknown status - abnormal state */
} ISPCOMM_STATUS_E;

/** @} */


/****************************************************
 * Type Definition                                 *
 ***************************************************/
/**
 * \brief ISP Communication callback function type definition
 *
 * \param[in] void *
 * \retval void.
 */
typedef void (*ispcomm_cb_t) (void *);


/****************************************************
 * Structure Definition                             *
 ***************************************************/
/**
 * \defgroup	ISP_COMM_STRUCT		ISP Communication Library Structure
 * \ingroup	ISP_COMM
 * \brief	Defines the required structure of ISP Communication library.
 * @{
 */


/**
 * \struct ISPCOMM_CFG_T
 * \brief ISP Communication Configuration
 */
typedef struct
{
	ISPCOMM_STATUS_E ispcomm_state;	/*!< ISPCOMM state */
	IOMUX_INDEX_E isp_gpio0;
	IOMUX_INDEX_E isp_gpio1;
	IOMUX_INDEX_E i2c_mux_gpio;
	ispcomm_cb_t ispcomm_cb;
} ISPCOMM_CFG_T;


/** @} */	//ISP_COMM_STRUCT



/****************************************************
 * Function Declaration                             *
 ***************************************************/
/**
 * \defgroup	ISP_COMM_FUNCDLR	ISP Communication library Function Declaration
 * \ingroup	ISP_COMM
 * \brief	Contains declarations of ISP Communication library functions.
 * @{
 */

/**
 * \brief	The function use to initial the isp communication protocol
 *
 * Initialize the isp communication library.
 * \retval	ISPCOMM_NO_ERROR	no error
 * \retval	others	error
 */
ISPCOMM_ERROR_E hx_lib_ispcomm_init(ISPCOMM_CFG_T *aCfg);


/**
 * \brief	The function use to deinitialize the isp communication protocol
 *
 * Deinitialize the isp communication library.
 * \retval	ISPCOMM_NO_ERROR	no error
 * \retval	others	error
 */
ISPCOMM_ERROR_E hx_lib_ispcomm_deinit(ISPCOMM_CFG_T *aCfg);


/**
 * \brief	The function use to start the isp communication process
 *
 * Stop the isp communication process : start to monitor the isp write command on isp bus.
 * \retval	ISPCOMM_NO_ERROR	no error
 * \retval	others	error
 */
ISPCOMM_ERROR_E hx_lib_ispcomm_start(void);


/**
 * \brief	The function use to stop the isp communication process
 *
 * Stop the isp communication process : suspend to monitor the isp command on isp bus.
 * \retval	ISPCOMM_NO_ERROR	no error
 * \retval	others	error
 */
ISPCOMM_ERROR_E hx_lib_ispcomm_stop(void);


/**
 * \brief	The function use to get the status of isp communication process
 *
 * Get the status of isp communication process
 * \retval	ISPCOMM_NO_ERROR	no error
 * \retval	others	error
 */
ISPCOMM_ERROR_E hx_lib_ispcomm_status(ISPCOMM_STATUS_E *aStatus);


/**
 * \brief	The function use to process isp command for feature:sysinfo.
 *
 * Process isp command for feature:sysinfo
 * \retval	ISPCOMM_NO_ERROR	no error
 * \retval	others	error
 */
ISPCOMM_ERROR_E hx_lib_ispcomm_process(ISPCOMM_CFG_T *aCfg);

/** @} */	//ISP_COMM_FUNCDLR


#endif /* LIBRARY_ISP_COMM_ISP_COMM_H_ */

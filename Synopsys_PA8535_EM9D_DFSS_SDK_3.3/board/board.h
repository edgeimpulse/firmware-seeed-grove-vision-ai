/**
 ********************************************************************************************
 *  @file      board.h
 *  @details   This file contains all board related function
 *  @author    himax/902452
 *  @version   V1.0.0
 *  @date      14-May-2019
 *  @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 *******************************************************************************************/

/**
 * \defgroup	BOARD	WEI supported board version
 * \ingroup	BOARD
 * \brief	The board header file that contain common configuration.
 * \details
 * - This header file will contain board related common settings for all of supported boards.
 * - The specific board's configuration is located in their own folder.
 */


/**
 * \addtogroup BOARD
 * @{
 */
#ifndef _EMBARC_BOARD_H_
#define _EMBARC_BOARD_H_


#include "board_config.h"
#include "fw_version.h"

/****************************************************
 * ENUM Declaration                                 *
 ***************************************************/
/**
 * \defgroup	BOARD_ENUM	Board Enumeration
 * \ingroup	BOARD
 * \brief	Defines some enumeration of Boaard need.
 * @{
 */

/****************************************************
 * Structure Definition                             *
 ***************************************************/
/**
 * \defgroup	BOARD_STRUCT		Board Structure
 * \ingroup	BOARD
 * \brief	contains definitions of board structure.
 * @{
 */

/**
 * \enum APP_TYPE_E
 * \brief this enumeration use in board information api
 */
typedef enum APP_TYPE_S
{
	APP_TYPE_DEV = 0,		/* Application type for internal development */
	APP_TYPE_QUANTANB,		/* Application type for QUANTANB product */
	APP_TYPE_AIOT_DEMO,  	/* Application type for AIOT Demo program */
	APP_TYPE_INVALID
}APP_TYPE_E;

/**
 * \defgroup	BOARD_FUNCDLR	Board Function Declaration
 * \ingroup	BOARD
 * \brief	Contains declarations of Board functions.
 * @{
 */


/**
 * \brief	get board support package(BSP) version number
 *
 * get bsp version number
 * \retval	uint32_t return the bsp verion number
 */
uint32_t hx_board_get_version(void);

#pragma pack(1)
typedef struct _FORMAL_VERSION
{
    int svn_version;
    char customer_name[5];
    int customer_version;
}FORMAL_VERSION;
#pragma pack()

void hx_get_formal_version(unsigned char *pBuf);

#endif /* _EMBARC_BOARD_H_ */

/** @} end of group BOARD */

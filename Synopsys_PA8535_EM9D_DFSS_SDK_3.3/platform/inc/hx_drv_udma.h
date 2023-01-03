/**
 * @file hx_drv_udma.h
 * @author himax/903730
 * @brief 
 * @version V1.0.0
 * @date 2020-01-21
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#ifndef INC_HX_DRV_UDMA_H_
#define INC_HX_DRV_UDMA_H_


#ifdef __Xdmac
/**
 * \brief	copy data from dst_addr to src_addr
 *
 * \param[in]	src_addr	data source address
 * \param[in]	dst_addr	data destination address
 * \param[in]	length	    copy data size
 * \return	1: success.
 */
bool hx_drv_udma_memcpy(uint32_t src_addr, uint32_t dst_addr, uint32_t length);
#endif


#endif





/*
 * hx_drv_RSDMA.h
 *
 *  Created on: 2018¦~11¤ë7¤é
 *      Author: 902447
 */

#ifndef INC_HX_DRV_RSDMA_H_
#define INC_HX_DRV_RSDMA_H_

#include "embARC_toolchain.h"

/**
 * \defgroup	RSDMAC_DRV	Resampler DMAC Driver
 * \ingroup		RSDMAC_DRV
 * \brief	Resampler DMAC Driver Declaration
 */
/**
 * \defgroup	RSDMAC_DRV_ENUM	Resampler DMAC Driver Enumeration
 * \ingroup	RSDMAC_DRV
 * \brief	Defines some enumeration of RS DMAC Driver need.
 * @{
 */
/**
 * \enum RSDMA_ERROR_E
 * \brief RSDMA Errors Type
 */
typedef enum
{
	RSDMA_NO_ERROR                     		= 0,	/**< No ERROR */
	RSDMA_ERROR_NOT_INIT              	    = 1,	/**< ERROR MSG: not init */
	RSDMA_ERROR_ALREADY_INIT                = 2,	/**< ERROR MSG: already init */
	RSDMA_ERROR_INVALID_PARAMETERS     		= 3,	/**< ERROR MSG: Invalid parameters */
	RSDMA_UNKNOWN_ERROR      				= 4,	/**< ERROR MSG: UNKNOWN ERROR*/
} RSDMA_ERROR_E;

/**
 * \enum RSDMA_INTTYPE_E
 * \brief RSDMA Interrupt Type
 */
typedef enum
{
	RSDMA_INTTYPE_NORMAL_FINISH           = 0,	/**< [0]: Normal finish.*/
	RSDMA_INTTYPE_RDMA_FIFO_ERROR     = 5,	/**< [5]: RDMA FIFO errors (abnormal).*/
	RSDMA_INTTYPE_WDMA_FIFO_ERROR     = 6,	/**< [6]: WDMA FIFO overflow errors (abnormal).*/
} RSDMA_INTTYPE_E;

/**
 * \enum RSDMA_INTMASK_E
 * \brief RSDMA Interrupt Mask
 */
typedef enum
{
	RSDMA_INTMASK_OFF       = 0,	/**< Not Mask Interrupt*/
	RSDMA_INTMASK_ON        = 1,	/**< Mask Interrupt*/
} RSDMA_INTMASK_E;

/**
 * \enum RSDMA_INTSTATUS_E
 * \brief RSDMA Interrupt Status
 */
typedef enum
{
	RSDMA_INTSTATUS_NO	           		= 0,	/**< No */
	RSDMA_INTSTATUS_NORMAL_FINISH       = 0x1F,	/**< [0-4]: Normal finish.*/
	RSDMA_INTSTATUS_NOGETFE_FINISH      = 0x1E,	/**< [0-4]: abNormal finish.*/
	RSDMA_INTSTATUS_NOSENDFE_FINISH     = 0x1D,	/**< [0-4]: abNormal finish.*/
	RSDMA_INTSTATUS_NOBOTHFE_FINISH     = 0x1C,	/**< [0-4]: abNormal finish.*/
	RSDMA_INTSTATUS_RDMA_FIFO_ERROR     = 0x20,	/**< [5]: RDMA FIFO errors (abnormal).*/
	RSDMA_INTSTATUS_WDMA_FIFO_ERROR 	= 0x40,	/**< [6]: WDMA FIFO overflow errors (abnormal).*/
} RSDMA_INTSTATUS_E;
/** @} */

/**
 * \defgroup	RSDMAC_DRV_REGSTRUCT	Resampler DMAC Driver Structure
 * \ingroup	RSDMAC_DRV
 * \brief	contains definitions of Resampler DMAC Driver structure.
 * @{
 */
/**
 * \struct RSDMA_CFG_T
 * \brief RS DMAC configuration by RS DMAC Driver
 */
typedef struct
{
	uint8_t rs_dma_en;			/**< RS DMAC Enable */
	uint32_t rs_RDMA_startaddr;	/**< RS DMAC RDMA Start address */
	uint32_t rs_RDMA_size;		/**< RS DMAC RDMA Size */
	uint32_t rs_WDMA_startaddr; /**< RS DMAC WDMA Start address */
	uint32_t rs_WDMA_size;		/**< RS DMAC WDMA Start size */
	uint16_t rs_hsize;			/**< RS DMAC DMA HSize */
	uint16_t rs_vsize;			/**< RS DMAC DMA VSize */
	uint32_t rs_intmask;		/**< RS DMAC DMA Interrupt Mask */
} RSDMA_CFG_T;
/** @} */

/**
 * \defgroup	RSDMAC_DRV_FUNCDLR	RS DMAC Driver Function Declaration
 * \ingroup	RSDMAC_DRV
 * \brief	Contains declarations of RS DMAC Driver functions.
 * @{
 */
/**
 * \brief	RS DMAC interrupt callback function
 *
 * \param[in]	event	 RS DMAC interrupt callback event
 * \return	void.
 */
typedef void (*RSDMA_ISREvent_t) (RSDMA_INTSTATUS_E event);

/**
 * \brief	init RSDMA Driver
 *
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_init();

/**
 * \brief	set all RSDMA related Setting
 *
 * \param[in]	rsdma_cfg	 RS DMAC configuration
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_set_allCfg(RSDMA_CFG_T rsdma_cfg);

/**
 * \brief	get default RSDMA related Setting
 *
 * \param[out]	rsdma_cfg	 RS DMAC configuration
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_get_defCfg(RSDMA_CFG_T *rsdma_cfg);

/**
 * \brief	set RS DMAC enable Setting
 *
 * \param[in]	enable	 RS DMAC enable
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_set_enable(uint8_t enable);

/**
 * \brief	get RS DMAC enable Setting
 *
 * \param[out]	enable	 RS DMAC enable
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_get_enable(uint8_t *enable);

/**
 * \brief	set RS DMAC RDMA Start Address and Size Setting
 *
 * \param[in]	startaddr	 RS DMAC RDMA start address
 * \param[in]	size	 RS DMAC RDMA size
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_set_RDMAAddrSize(uint32_t startaddr, uint32_t size);

/**
 * \brief	get RS DMAC RDMA Start Address and Size Setting
 *
 * \param[out]	*startaddr	 RS DMAC RDMA start address
 * \param[out]	*size	 RS DMAC RDMA size
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_get_RDMAAddrSize(uint32_t *startaddr, uint32_t *size);

/**
 * \brief	set RS DMAC WDMA Start Address and Size Setting
 *
 * \param[in]	startaddr	 RS DMAC WDMA start address
 * \param[in]	size	 RS DMAC WDMA size
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_set_WDMAAddrSize(uint32_t startaddr, uint32_t size);

/**
 * \brief	get RS DMAC WDMA Start Address and Size Setting
 *
 * \param[out]	startaddr	 RS DMAC WDMA start address
 * \param[out]	size	 RS DMAC WDMA size
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_get_WDMAAddrSize(uint32_t *startaddr, uint32_t *size);

/**
 * \brief	set RS DMAC Clear Interrupt
 *
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_clear_interrupt();

/**
 * \brief	set RS DMAC Interrupt Mask
 *
 * \param[in]	mask	 RS DMAC Interrupt Mask
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_set_INTMask(uint32_t mask);

/**
 * \brief	get RS DMAC Interrupt Mask
 *
 * \param[out]	mask	 RS DMAC Interrupt Mask
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_get_INTMask(uint32_t *mask);

/**
 * \brief	set RS DMAC Timing Generator HSize and VSize
 *
 * \param[in]	hsize	 timing generator width
 * \param[in]	vsize	 timing generator height
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_set_timing(uint16_t hsize, uint16_t vsize);

/**
 * \brief	get RS DMAC Timing Generator HSize and VSize
 *
 * \param[out]	hsize	 timing generator width
 * \param[out]	vsize	 timing generator height
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_get_timing(uint16_t *hsize, uint16_t *vsize);

/**
 * \brief	set RS DMAC Register interrupt callback function
 *
 * \param[in]	cb_event	 RS DMAC interrupt callback function
 * \return	RSDMA_ERROR_E.
 */
RSDMA_ERROR_E hx_drv_rsdma_register_cb(RSDMA_ISREvent_t  cb_event);
/** @} */

#endif /* INC_HX_DRV_RSDMA_ */

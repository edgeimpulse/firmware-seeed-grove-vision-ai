/*
 * hx_drv_HOGDMA.h
 *
 *  Created on: 2018¦~11¤ë8¤é
 *      Author: 902447
 */

#ifndef INC_HX_DRV_HOGDMA_H_
#define INC_HX_DRV_HOGDMA_H_

#include "embARC_toolchain.h"
/**
 * \defgroup	HOGDMAC_DRV	HOG DMAC Driver
 * \ingroup		HOGDMAC_DRV
 * \brief	 HOG DMAC Driver Declaration
 */
/**
 * \defgroup	HOGDMAC_DRV_ENUM	HOG DMAC Driver Enumeration
 * \ingroup	HOGDMAC_DRV
 * \brief	Defines some enumeration of HOG DMAC Driver need.
 * @{
 */
/**
 * \enum HOGDMA_ERROR_E
 * \brief HOGDMA Errors Type
 */
typedef enum
{
	HOGDMA_NO_ERROR                     	= 0,	/**< No ERROR */
	HOGDMA_ERROR_NOT_INIT              	    = 1,	/**< ERROR MSG: not init */
	HOGDMA_ERROR_ALREADY_INIT               = 2,	/**< ERROR MSG: already init */
	HOGDMA_ERROR_INVALID_PARAMETERS     	= 3,	/**< ERROR MSG: Invalid parameters */
	HOGDMA_UNKNOWN_ERROR      				= 4,	/**< ERROR MSG: UNKNOWN ERROR*/
} HOGDMA_ERROR_E;

/**
 * \enum HOGDMA_MODE_E
 * \brief HOGDMA Full Frame or ROI mode
 */
typedef enum
{
	HOGDMA_MODE_NORMAL      = 0,	/**< HOGDMA Full Frame */
	HOGDMA_MODE_ROI	        = 1,	/**< HOGDMA ROI Mode */
}HOGDMA_MODE_E;

/**
 * \enum HOGDMA_TGMODE_E
 * \brief HOGDMA Timing Generator Mono or YUV420
 */
typedef enum
{
	HOGDMA_TGMODE_MONO      = 0,	/**< HOGDMA Timing Generator Mono Mode */
	HOGDMA_TGMODE_YUV420	= 1,	/**< HOGDMA Timing Generator YUV420 Mode */
}HOGDMA_TGMODE_E;

/**
 * \enum HOGDMA_INTTYPE_E
 * \brief HOGDMA Interrupt Type
 */
typedef enum
{
	HOGDMA_INTTYPE_NORMAL_FINISH           = 0,	/**< [0]: Normal finish. */
	HOGDMA_INTTYPE_CH4_WDMA_FIFO_ERR  	   = 7,/**< [7]: channel 4 WDMA FIFO overflow errors (abnormal).*/
	HOGDMA_INTTYPE_CH1_RDMA_FIFO_ERR  	   = 8,/**< [8]: channel 1 RDMA FIFO errors (abnormal).*/
	HOGDMA_INTTYPE_CH2_RDMA_FIFO_ERR  	   = 9,/**< [9]: channel 2 RDMA FIFO errors (abnormal).*/
	HOGDMA_INTTYPE_CH3_RDMA_FIFO_ERR  	   = 10,/**< [10]: channel 3 RDMA FIFO errors (abnormal).*/
} HOGDMA_INTTYPE_E;

/**
 * \enum HOGDMA_INTMASK_E
 * \brief HOGDMA Interrupt Mask
 */
typedef enum
{
	HOGDMA_INTMASK_OFF       = 0,	/**< Not Mask Interrupt*/
	HOGDMA_INTMASK_ON        = 1,	/**< Mask Interrupt*/
} HOGDMA_INTMASK_E;

/**
 * \enum HOGDMA_INTSTATUS_E
 * \brief HOGDMA Interrupt Status
 */
typedef enum
{
	HOGDMA_INTSTATUS_NO			           	 = 0,	/**< NO */
	HOGDMA_INTSTATUS_NORMAL_FINISH_STATUS    = 0x7F,	/**< [0~6]: Normal finish. with status */
	HOGDMA_INTSTATUS_NOGETFE_FINISH		     = 0x7E,	/**< [0~6]: Normal finish. with status */
	HOGDMA_INTSTATUS_NOSENDFE_FINISH	     = 0x7D,	/**< [0~6]: Normal finish. with status */
	HOGDMA_INTSTATUS_NOBOTHFE_FINISH	     = 0x7C,	/**< [0~6]: Normal finish. with status */
	HOGDMA_INTSTATUS_CH1_RDMA_FIFO_ERR  	 = 0x80,/**< [7]: channel 4 WDMA FIFO overflow errors (abnormal).*/
	HOGDMA_INTSTATUS_CH2_RDMA_FIFO_ERR  	 = 0x100,/**< [8]: channel 1 RDMA FIFO errors (abnormal).*/
	HOGDMA_INTSTATUS_CH3_RDMA_FIFO_ERR  	 = 0x200,/**< [9]: channel 2 RDMA FIFO errors (abnormal).*/
	HOGDMA_INTSTATUS_CH4_WDMA_FIFO_ERR  	 = 0x400,/**< [10]: channel 3 RDMA FIFO errors (abnormal).*/
} HOGDMA_INTSTATUS_E;
/** @} */

/**
 * \defgroup	HOGDMAC_DRV_REGSTRUCT	HOG DMAC Driver Structure
 * \ingroup	HOGDMAC_DRV
 * \brief	contains definitions of HOG DMAC Driver structure.
 * @{
 */
/**
 * \struct HOGDMA_CFG_T
 * \brief HOG DMAC configuration by HOGDMA Driver
 */
typedef struct
{
	uint8_t hog_dma_en;			/**< HOG DMAC enable */
	uint8_t hog_dma_ch_en;		/**< HOG DMAC channel enable */
	HOGDMA_MODE_E mode;			/**< HOGDMA Full Frame or ROI mode */
	uint32_t hog_RDMA1_startaddr;	/**< HOGDMA RDMA channel 1 start address */
	uint32_t hog_RDMA1_size;		/**< HOGDMA RDMA channel 1 size */
	uint32_t hog_RDMA1_ROIOffset;	/**< HOGDMA RDMA channel 1 ROI offset */
	uint16_t hog_RDMA1_ROIlinecnt;	/**< HOGDMA RDMA channel 1 ROI line count */

	uint32_t hog_RDMA2_startaddr;	/**< HOGDMA RDMA channel 2 start address */
	uint32_t hog_RDMA2_size;		/**< HOGDMA RDMA channel 2 size */
	uint32_t hog_RDMA2_ROIOffset;	/**< HOGDMA RDMA channel 2 ROI offset */
	uint16_t hog_RDMA2_ROIlinecnt;	/**< HOGDMA RDMA channel 2 ROI line count */

	uint32_t hog_RDMA3_startaddr;	/**< HOGDMA RDMA channel 3 start address */
	uint32_t hog_RDMA3_size;		/**< HOGDMA RDMA channel 3 size */
	uint32_t hog_RDMA3_ROIOffset;	/**< HOGDMA RDMA channel 3 ROI offset */
	uint16_t hog_RDMA3_ROIlinecnt;	/**< HOGDMA RDMA channel 3 ROI line count */

	uint32_t hog_WDMA_startaddr;	/**< HOGDMA WDMA start address */
	uint32_t hog_WDMA_size;			/**< HOGDMA WDMA size */

	HOGDMA_TGMODE_E tgmode;		/**< HOGDMA Timing Generator Mono or YUV420 */
	uint16_t hog_hsize;			/**< HOGDMA Timing Generator width */
	uint16_t hog_vsize;			/**< HOGDMA Timing Generator height */
	uint16_t hog_intmask;		/**< HOGDMA Interrupt Mask */
} HOGDMA_CFG_T;
/** @} */

/**
 * \defgroup	HOGDMAC_DRV_FUNCDLR	HOG DMAC Driver Function Declaration
 * \ingroup	HOGDMAC_DRV
 * \brief	Contains declarations of HOG DMAC Driver functions.
 * @{
 */
/**
 * \brief	HOG DMAC interrupt callback function
 *
  * \param[in]	event	 HOG DMAC interrupt callback event
 * \return	HOG_ERROR_E.
 */
typedef void (*HOGDMA_ISREvent_t) (HOGDMA_INTSTATUS_E event);

/**
 * \brief	initial HOGDMA Driver
 *
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_init();

/**
 * \brief	set all HOGDMA related Setting
 *
 * \param[in]	hogdma_cfg	 HOG DMAC configuration
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_allCfg(HOGDMA_CFG_T hogdma_cfg);

/**
 * \brief	get default HOGDMA related Setting
 *
 * \param[out]	hogdma_cfg	 HOG DMAC configuration
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_defCfg(HOGDMA_CFG_T *hogdma_cfg);

/**
 * \brief	set HOGDMA enable Setting
 *
 * \param[in]	enable	 HOG DMAC enable
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_enable(uint8_t enable);
/**
 * \brief	get HOGDMA enable Setting
 *
 * \param[out]	enable	 HOG DMAC enable
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_enable(uint8_t *enable);

/**
 * \brief	set HOGDMA Channel enable Setting
 *
 * \param[in]	ch_enable	 HOG DMAC channel enable (channel 1:1, channel 2:2, channel 2:4, all channel:7 )
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_ch_enable(uint8_t ch_enable);
/**
 * \brief	get HOGDMA Channel enable Setting
 *
 * \param[out]	ch_enable	 HOG DMAC channel enable (channel 1:1, channel 2:2, channel 2:4, all channel:7 )
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_ch_enable(uint8_t *ch_enable);

/**
 * \brief	set HOGDMA Normal or ROI Setting
 *
 * \param[in]	mode	HOGDMA Full Frame or ROI mode
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_NormalROI(HOGDMA_MODE_E mode);

/**
 * \brief	get HOGDMA Normal or ROI Setting
 *
 * \param[out]	mode	HOGDMA Full Frame or ROI mode
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_NormalROI(HOGDMA_MODE_E *mode);

/**
 * \brief	set HOGDMA RDMA channel 1 Start Addr, Size and ROI Setting
 *
 * \param[in]	startaddr	HOGDMA RDMA channel 1 Address
 * \param[in]	size	HOGDMA RDMA channel 1 size
 * \param[in]	offset	HOGDMA RDMA channel 1 ROI offset
 * \param[in]	linecnt	HOGDMA RDMA channel 1 ROI linecnt
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_RDMA1AddrSizeROI(uint32_t startaddr, uint32_t size, uint32_t offset, uint16_t linecnt);

/**
 * \brief	get HOGDMA RDMA channel 1 Start Addr, Size and ROI Setting
 *
 * \param[out]	startaddr	HOGDMA RDMA channel 1 Address
 * \param[out]	size	HOGDMA RDMA channel 1 size
 * \param[out]	offset	HOGDMA RDMA channel 1 ROI offset
 * \param[out]	linecnt	HOGDMA RDMA channel 1 ROI linecnt
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_RDMA1AddrSizeROI(uint32_t *startaddr, uint32_t *size, uint32_t *offset, uint16_t *linecnt);

/**
 * \brief	set HOGDMA RDMA channel 2 Start Addr, Size and ROI Setting
 *
 * \param[in]	startaddr	HOGDMA RDMA channel 2 Address
 * \param[in]	size	HOGDMA RDMA channel 2 size
 * \param[in]	offset	HOGDMA RDMA channel 2 ROI offset
 * \param[in]	linecnt	HOGDMA RDMA channel 2 ROI linecnt
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_RDMA2AddrSizeROI(uint32_t startaddr, uint32_t size, uint32_t offset, uint16_t linecnt);

/**
 * \brief	get HOGDMA RDMA channel 2 Start Addr, Size and ROI Setting
 *
 * \param[out]	startaddr	HOGDMA RDMA channel 2 Address
 * \param[out]	size	HOGDMA RDMA channel 2 size
 * \param[out]	offset	HOGDMA RDMA channel 2 ROI offset
 * \param[out]	linecnt	HOGDMA RDMA channel 2 ROI linecnt
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_RDMA2AddrSizeROI(uint32_t *startaddr, uint32_t *size, uint32_t *offset, uint16_t *linecnt);

/**
 * \brief	set HOGDMA RDMA channel 3 Start Addr, Size and ROI Setting
 *
 * \param[in]	startaddr	HOGDMA RDMA channel 3 Address
 * \param[in]	size	HOGDMA RDMA channel 3 size
 * \param[in]	offset	HOGDMA RDMA channel 3 ROI offset
 * \param[in]	linecnt	HOGDMA RDMA channel 3 ROI linecnt
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_RDMA3AddrSizeROI(uint32_t startaddr, uint32_t size, uint32_t offset, uint16_t linecnt);

/**
 * \brief	get HOGDMA RDMA channel 3 Start Addr, Size and ROI Setting
 *
 * \param[out]	startaddr	HOGDMA RDMA channel 3 Address
 * \param[out]	size	HOGDMA RDMA channel 3 size
 * \param[out]	offset	HOGDMA RDMA channel 3 ROI offset
 * \param[out]	linecnt	HOGDMA RDMA channel 3 ROI linecnt
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_RDMA3AddrSizeROI(uint32_t *startaddr, uint32_t *size, uint32_t *offset, uint16_t *linecnt);


/**
 * \brief	set HOGDMA WDMA Start Addr. and Size Setting
 *
 * \param[in]	startaddr	HOGDMA WDMA Address
 * \param[in]	size	HOGDMA WDMA size
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_WDMAAddrSize(uint32_t startaddr, uint32_t size);

/**
 * \brief	get HOGDMA WDMA Start Addr. and Size Setting
 *
 * \param[out]	startaddr	HOGDMA WDMA Address
 * \param[out]	size	HOGDMA WDMA size
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_WDMAAddrSize(uint32_t *startaddr, uint32_t *size);

/**
 * \brief	set HOGDMA DMAC Clear Interrupt
 *
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_clear_interrupt();

/**
 * \brief	set HOG DMAC Interrupt Mask
 *
 * \param[in]	mask	HOGDMA_INTTYPE_E interrupt type
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_INTMask(uint16_t mask);

/**
 * \brief	get HOG DMAC Interrupt Mask
 *
 * \param[out]	mask	HOGDMA_INTTYPE_E interrupt type
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_INTMask(uint16_t *mask);

/**
 * \brief	set HOG DMAC Timing Generator Mode
 *
 * \param[in]	tgmode	Timing Generator type Mono or YUV420
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_TGMode(HOGDMA_TGMODE_E tgmode);

/**
 * \brief	get HOG DMAC Timing Generator Mode
 *
 * \param[out]	tgmode	Timing Generator type Mono or YUV420
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_TGMode(HOGDMA_TGMODE_E *tgmode);

/**
 * \brief	set HOG DMAC Timing Generator Hsize and Vsize
 *
 * \param[in]	hsize	HOG DMAC Timing Generator Hsize
 * \param[in]	vsize	HOG DMAC Timing Generator Vsize
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_set_timing(uint16_t hsize, uint16_t vsize);

/**
 * \brief	get HOG DMAC Timing Generator Hsize and Vsize
 *
 * \param[out]	hsize	HOG DMAC Timing Generator Hsize
 * \param[out]	vsize	HOG DMAC Timing Generator Vsize
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_get_timing(uint16_t *hsize, uint16_t *vsize);

/**
 * \brief	set HOG DMAC register interrupt callback function
 *
 * \param[in]	cb_event	Interrupt callback function from upper layer
 * \return	HOGDMA_ERROR_E.
 */
HOGDMA_ERROR_E hx_drv_hogdma_register_cb(HOGDMA_ISREvent_t  cb_event);
/** @} */

#endif /* INC_HX_DRV_HOGDMA_H_ */

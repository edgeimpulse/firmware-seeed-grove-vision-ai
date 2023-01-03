/*
 * hx_drv_HOG.h
 *
 *  Created on: 2018¦~11¤ë7¤é
 *      Author: 902447
 */

#ifndef INC_HX_DRV_HOG_H_
#define INC_HX_DRV_HOG_H_

#include "embARC_toolchain.h"
/**
 * \defgroup	HWACC_HOG_DRV	HOG Hardware accelerator Driver
 * \ingroup		HWACC_HOG_DRV
 * \brief		HOG Hardware accelerator Driver Declaration
 * \details Application can use HOG_CFG_T, SENSORDPLIB_HOGDMA_CFG_T Structure and Datapath Library to Control HOG and HOGDMA\n
 * <pre>
 * For Example
 * Ex1: All HOG IP configurations are in structure HOG_CFG_T, HOG DMA configuration in SENSORDPLIB_HOGDMA_CFG_T
 * 		a. sensordplib_set_HOG_HWACC_Crop(HOG_CFG_T hog_cfg, SENSORDPLIB_HOGDMA_CFG_T dma_cfg, sensordplib_CBEvent_t dplib_cb);
 * 		b. sensordplib_set_HOG_DMACropNoExtraBND(HOG_CFG_T hog_cfg, SENSORDPLIB_HOGDMA_CFG_T dma_cfg, sensordplib_CBEvent_t dplib_cb);
 * 		c. sensordplib_set_HOG_DMACropExtraBND(HOG_CFG_T hog_cfg, SENSORDPLIB_HOGDMA_CFG_T dma_cfg, sensordplib_CBEvent_t dplib_cb);
 * 		Those functions are non-blocking function so you should use callback function to check if HOG processing is done or not.
 * </pre>
 */
/**
 * \defgroup	HWACC_HOG_DRV_ENUM	HOG Hardware accelerator Driver Enumeration
 * \ingroup	HWACC_HOG_DRV
 * \brief	Defines some enumeration of HOG Hardware accelerator Driver need.
 * @{
 */
/**
 * \enum HOG_ERROR_E
 * \brief HOG Errors Type
 */
typedef enum
{
	HOG_NO_ERROR                     		= 0,	/**< No ERROR */
	HOG_ERROR_NOT_INIT              	    = 1,	/**< ERROR MSG: not init */
	HOG_ERROR_ALREADY_INIT                	= 2,	/**< ERROR MSG: already init */
	HOG_ERROR_INVALID_PARAMETERS     		= 3,	/**< ERROR MSG: Invalid parameters */
	HOG_ERROR_INVALID_TIMING_RANGE     		= 4,	/**< ERROR MSG: Invalid TIMING Range */
	HOG_ERROR_INVALID_TIMING_DIVISIBLE 	    = 5,	/**< ERROR MSG: Invalid TIMING Divisble */
	HOG_UNKNOWN_ERROR      					= 6,	/**< ERROR MSG: UNKNOWN ERROR*/
} HOG_ERROR_E;

/**
 * \enum HOG_INPUT_TYPE_E
 * \brief HOG Input format
 */
typedef enum
{
	HOG_INPUT_TYPE_MONO		= 0,	/**< HOG Input format Mono */
	HOG_INPUT_TYPE_YUV420 	= 1,	/**< HOG Input format YUV420 */
}HOG_INPUT_TYPE_E;

/**
 * \enum HOG_CELL_SIZE_E
 * \brief HOG Cell Size
 */
typedef enum
{
	HOG_CELL_SIZE_4X4		= 0,	/**< HOG Cell Size 4x4 */
	HOG_CELL_SIZE_6X6 		= 1,	/**< HOG Cell Size 6x6 */
	HOG_CELL_SIZE_8X8 		= 2,	/**< HOG Cell Size 8x8 */
}HOG_CELL_SIZE_E;

/**
 * \enum HOG_NORMALIZATION_EN_E
 * \brief HOG Normalization enable/disable
 */
typedef enum
{
	HOG_NORMALIZATION_EN_OFF		= 0,	/**< HOG Normalization Disable */
	HOG_NORMALIZATION_EN_ON 		= 1,	/**< HOG Normalization Enable */
}HOG_NORMALIZATION_EN_E;
/** @} */

/**
 * \defgroup	HWACC_HOG_DRV_REGSTRUCT	HOG Hardware accelerator Driver Structure
 * \ingroup	HWACC_HOG_DRV
 * \brief	contains definitions of HOG Hardware accelerator Driver structure.
 * @{
 */
/**
 * \struct HOG_CFG_T
 * \brief HOG configuration by HOG Driver
 */
typedef struct
{
	HOG_INPUT_TYPE_E input_type;	/**< HOG Input format */
	HOG_CELL_SIZE_E cell_size;		/**< HOG Cell Size */
	HOG_NORMALIZATION_EN_E normalization_en;	/**< HOG Normalization enable/disable */
	uint8_t hog_normal_const;		/**< HOG Normalization constant */
	uint16_t hog_in_width;			/**< HOG input width */
	uint16_t hog_in_height;			/**< HOG input height */
	uint16_t hog_roi_stx;			/**< HOG ROI start x position */
	uint16_t hog_roi_sty;			/**< HOG ROI start y position */
	uint16_t hog_roi_width;			/**< HOG ROI width */
	uint16_t hog_roi_height;		/**< HOG ROI height */
} HOG_CFG_T;
/** @} */

/**
 * \defgroup	HWACC_HOG_DRV_MACRO	HOG Hardware accelerator Driver MACRO
 * \ingroup	HWACC_HOG_DRV
 * \brief	contains definitions of HOG Hardware accelerator Driver MACRO.
 * @{
 */
#define MAX_HOG_CROP_WIDTH_CONSTRAINT 	640	/*!< Timing Constraint of max ROI width*/
#define MAX_HOG_CROP_HEIGHT_CONSTRAINT 	480 /*!< Timing Constraint of max ROI height*/
#define HOG_WIDTH_DIVISIBLE  			2	/*!< Timing Constraint of width multiple*/
#define HOG_HEIGHT_DIVISIBLE  			2	/*!< Timing Constraint of height multiple*/
#define MIN_HOG_CROP_WIDTH_CONSTRAINT 	8	/*!< Timing Constraint of min ROI width*/
#define MIN_HOG_CROP_HEIGHT_CONSTRAINT 	8	/*!< Timing Constraint of min ROI height*/
/** @} */

/**
 * \defgroup	HWACC_HOG_DRV_FUNCDLR	Hardware accelerator HOG Driver Function Declaration
 * \ingroup	HWACC_HOG_DRV
 * \brief	Contains declarations of Hardware accelerator HOG Driver functions.
 * @{
 */
/**
 * \brief	initial HOG Driver
 *
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_init();

/**
 * \brief	set all HOG related Setting
 *
 * \param[in]	hog_cfg	 HOG configuration
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_set_allCfg(HOG_CFG_T hog_cfg);

/**
 * \brief	get default HOG related Setting
 *
 * \param[out]	hog_cfg	 HOG default configuration
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_get_defCfg(HOG_CFG_T *hog_cfg);

/**
 * \brief	get HOG available Width and Height to avoid HW Constraint
 *
 * \param[in]	in_width	 HOG input width
 * \param[in]	in_height	 HOG input height
 * \param[out]	crop_width	 HOG suggest crop width
 * \param[out]	crop_height	 HOG suggest crop height
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_get_available_HV(uint16_t in_width,uint16_t in_height,uint16_t *crop_width,uint16_t *crop_height);

/**
 * \brief	set HOG input_type
 *
 * \param[in]	input_type	 HOG input format
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_set_input_type(HOG_INPUT_TYPE_E input_type);
/**
 * \brief	get HOG input_type
 *
 * \param[out]	input_type	 HOG input format
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_get_input_type(HOG_INPUT_TYPE_E *input_type);

/**
 * \brief	set HOG cell size
 *
 * \param[in]	cell_size	 HOG cell size
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_set_cellsizeMode(HOG_CELL_SIZE_E cell_size);

/**
 * \brief	get HOG cell size
 *
 * \param[out]	cell_size	 HOG cell size
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_get_cellsizeMode(HOG_CELL_SIZE_E *cell_size);

/**
 * \brief	set HOG enable block normalization and additional constant for block normalization factor
 *
 * \param[in]	enable	 HOG normalization enable/disable
 * \param[in]	hog_normal_const	 HOG normalization constant
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_set_normalize(HOG_NORMALIZATION_EN_E enable, uint8_t hog_normal_const);

/**
 * \brief	get HOG enable block normalization and additional constant for block normalization factor
 *
 * \param[out]	enable	 HOG normalization enable/disable
 * \param[out]	hog_normal_const	 HOG normalization constant
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_get_normalize(HOG_NORMALIZATION_EN_E *enable, uint8_t *hog_normal_const);

/**
 * \brief	set HOG cell size HV count that HW require. It will be automatically set when set ROI or cell size
 *
 * \param[in]	cell_size_h	 Cell_size_h = ceil(roi_width/cell_size) -1
 * \param[in]	cell_size_v	 Cell_size_v = ceil(roi_ height /cell_size) -1
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_set_HVCellCnt(uint8_t cell_size_h, uint8_t cell_size_v);

/**
 * \brief	get HOG cell size HV count that HW require. It will be automatically set when set ROI or cell size
 *
 * \param[out]	cell_size_h	 Cell_size_h = ceil(roi_width/cell_size) -1
 * \param[out]	cell_size_v	 Cell_size_v = ceil(roi_ height /cell_size) -1
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_get_HVCellCnt(uint8_t *cell_size_h, uint8_t *cell_size_v);


/**
 * \brief	set HOG Video timing and croping related setting
 *
 * \param[in]	in_width	 HOG input width
 * \param[in]	in_height	 HOG input height
 * \param[in]	roi_stx	 HOG ROI start x position
 * \param[in]	roi_sty	 HOG ROI start y position
 * \param[in]	roi_width	 HOG ROI width
 * \param[in]	roi_height	 HOG ROI height
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_set_Videotiming(uint16_t in_width, uint16_t in_height, uint16_t roi_stx,uint16_t roi_sty, uint16_t roi_width, uint16_t roi_height);

/**
 * \brief	get HOG Video timing and croping related setting
 *
 * \param[out]	in_width	 HOG input width
 * \param[out]	in_height	 HOG input height
 * \param[out]	roi_stx	 HOG ROI start x position
 * \param[out]	roi_sty	 HOG ROI start y position
 * \param[out]	roi_width	 HOG ROI width
 * \param[out]	roi_height	 HOG ROI height
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_get_Videotiming(uint16_t *in_width, uint16_t *in_height,uint16_t *roi_stx,uint16_t *roi_sty, uint16_t *roi_width, uint16_t *roi_height);

/**
 * \brief	get HOG output Memory Size for DMAC
 *
 * \param[in]	hog_cfg	 HOG Configuration
 * \param[out]	mem_size	 HOG output data memory size
 * \return	HOG_ERROR_E.
 */
HOG_ERROR_E hx_drv_hog_get_OutMEMSize(HOG_CFG_T hog_cfg, uint32_t *mem_size);
/** @} */

#endif /* INC_hx_drv_hog_H_ */

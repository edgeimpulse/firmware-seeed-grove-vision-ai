#ifndef _HX_DRV_RESAMPLER_H_
#define _HX_DRV_RESAMPLER_H_
#include "embARC_toolchain.h"

/**
 * \defgroup	HWACC_RS_DRV	RS Hardware accelerator Driver
 * \ingroup		HWACC_RS_DRV
 * \brief	Hardware accelerator RS Driver Declaration
 */
/**
 * \defgroup	HWACC_RS_DRV_ENUM	RS Driver Enumeration
 * \ingroup	HWACC_RS_DRV
 * \brief	Defines some enumeration of RS Driver need.
 * \details Application can use Resampler driver enumeration and Datapath Library to Control Resampler and Resampler DMA\n
 * <pre>
 * For Example
 * Ex1: Use Resampler driver enumeration and datapath library to control Resampler and Resampler DMA
 *	sensordplib_set_RS(uint16_t in_width, uint16_t in_height,
 *		uint16_t st_x, uint16_t st_y,
 *		uint16_t crop_width, uint16_t crop_height
 *		,RS_SCALEMODE_E mode, RS_SCALERATIO_E ratio
 *		,RS_ROUNDMODE_E rs_round_mode
 *		,uint32_t rs_rdma_startaddr
 *		,uint32_t rs_wdma_startaddr
 *		,sensordplib_CBEvent_t dplib_cb);
 * 		Those functions are non-blocking function so you should use callback function to check if Resampler processing is done or not.
 * </pre>
 * @{
 */
/**
 * \enum RS_ERROR_E
 * \brief RS Errors Type
 */
typedef enum
{
	RS_NO_ERROR                     	= 0,	/**< No ERROR */
	RS_ERROR_NOT_INIT              	    = 1,	/**< ERROR MSG: not init */
	RS_ERROR_ALREADY_INIT               = 2,	/**< ERROR MSG: already init */
	RS_ERROR_INVALID_PARAMETERS     	= 3,	/**< ERROR MSG: Invalid parameters */
    RS_ERROR_INVALID_TIMING_RANGE     	= 4,	/**< ERROR MSG: Invalid TIMING Range */
    RS_ERROR_INVALID_TIMING_DIVISIBLE   = 5,	/**< ERROR MSG: Invalid TIMING Divisble */
	RS_UNKNOWN_ERROR      				= 6,	/**< ERROR MSG: UNKNOWN ERROR*/
} RS_ERROR_E;
/**
 * \enum RS_ROUNDMODE_E
 * \brief Resampler rounding mode
 */
typedef enum
{
	RS_ROUNDMODE_FLOOR 	= 0,	/**< Resampler rounding mode floor */
	RS_ROUNDMODE_ROUNDING 	= 1,/**< Resampler rounding mode rounding */
} RS_ROUNDMODE_E;
/**
 * \enum RS_SCALEMODE_E
 * \brief Resampler Scaling method
 */
typedef enum
{
	RS_SCALEMODE_NONE 			= 0,/**< No Scaling */
	RS_BILINEAR_WITH_SHIFT 		= 1,/**< bilinear with shift interpolation */
	RS_BILINEAR_WITHOUT_SHIFT 	= 2,/**< bilinear without shift interpolation */
	RS_NEAREST_WITHOUT_SHIFT 	= 3,/**< nearest without shift interpolation */
	RS_AVG_WITH_SHIFT 			= 4,/**< average with shift interpolation */
	RS_AVG_WITHOUT_SHIFT 		= 5,/**< average without shift interpolation */
} RS_SCALEMODE_E;
/**
 * \enum RS_SCALERATIO_E
 * \brief Resampler Scaling Ratio
 */
typedef enum
{
	RS_SCALERATIO_NONE 				= 0,/**< Resampler Scaling Ratio None */
	RS_SCALERATIO_ONE_EIGHTHS 		= 1,/**< Resampler Scaling Ratio 1/8 */
	RS_SCALERATIO_TWO_EIGHTHS 		= 2,/**< Resampler Scaling Ratio 2/8 */
	RS_SCALERATIO_THREE_EIGHTHS 	= 3,/**< Resampler Scaling Ratio 3/8 */
	RS_SCALERATIO_FOUR_EIGHTHS 		= 4,/**< Resampler Scaling Ratio 4/8 */
	RS_SCALERATIO_FIVE_EIGHTHS 		= 5,/**< Resampler Scaling Ratio 5/8 */
	RS_SCALERATIO_SIX_EIGHTHS 		= 6,/**< Resampler Scaling Ratio 6/8 */
	RS_SCALERATIO_SEVEN_EIGHTHS 	= 7,/**< Resampler Scaling Ratio 7/8 */
} RS_SCALERATIO_E;
/** @} */

/**
 * \defgroup	HWACC_RS_DRV_REGSTRUCT	RS Hardware accelerator Driver Structure
 * \ingroup	HWACC_RS_DRV
 * \brief	contains definitions of RS Hardware accelerator Driver structure.
 * @{
 */
/**
 * \struct Resampler_CFG_T
 * \brief RS configuration by RS Driver
 */
typedef struct
{
	RS_ROUNDMODE_E rs_round_mode;/**< Resampler rounding mode */
	uint16_t rs_crop_stx; /**< Resampler ROI start x-position */
	uint16_t rs_crop_sty; /**< Resampler ROI start y-position */
	uint16_t rs_crop_width; /**< Resampler ROI width */
	uint16_t rs_crop_height;   /**< Resampler ROI height */
    RS_SCALEMODE_E rs_scale_mode;/**< Resampler Scaling method */
    RS_SCALERATIO_E rs_scale_ratio;/**< Resampler Scaling Ratio */
} Resampler_CFG_T;
/** @} */

/**
 * \defgroup	HWACC_RS_DRV_MACRO	RS Hardware accelerator Driver MACRO
 * \ingroup	HWACC_RS_DRV
 * \brief	contains definitions of RS Hardware accelerator Driver MACRO.
 * @{
 */
#define MAX_RS_CROP_WIDTH_CONSTRAINT 	640 /**< Resampler Timing constraint of max width */
#define MAX_RS_CROP_HEIGHT_CONSTRAINT 	480 /**< Resampler Timing constraint of max height */
#define RS_CROP_WIDTH_DIVISIBLE  		8	/**< Resampler Timing constraint of width multiple */
#define RS_CROP_HEIGHT_DIVISIBLE  		8	/**< Resampler Timing constraint of height multiple */
#define MIN_RS_CROP_WIDTH_CONSTRAINT 	8	/**< Resampler Timing constraint of min width */
#define MIN_RS_CROP_HEIGHT_CONSTRAINT 	8	/**< Resampler Timing constraint of min height */
/** @} */


/**
 * \defgroup	HWACC_RS_DRV_FUNCDLR	Hardware accelerator RS Driver Function Declaration
 * \ingroup	HWACC_RS_DRV
 * \brief	Contains declarations of Hardware accelerator RS Driver functions.
 * @{
 */
/**
 * \brief	initial RS Driver
 *
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_init();

/**
 * \brief	set all Resampler related Setting
 *
 * \param[in]	rs_cfg	 RS configuration
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_set_allCfg(Resampler_CFG_T rs_cfg);

/**
 * \brief	get default Resampler related Setting
 *
 * \param[out]	rs_cfg	 RS default configuration
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_get_defCfg(Resampler_CFG_T *rs_cfg);

/**
 * \brief	get RS available Width and Height to avoid HW Constraint
 *
 * \param[in]	in_width	 RS input width
 * \param[in]	in_height	 RS input height
 * \param[out]	crop_width	 RS ROI width according to timing constraint of RS
 * \param[out]	crop_height	 RS ROI height according to timing constraint of RS
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_get_available_HV(uint16_t in_width,uint16_t in_height,uint16_t *crop_width,uint16_t *crop_height);

/**
 * \brief	set Resampler interpolation rounding mode
 *
 * \param[in]	m_mode	 Resampler rounding mode
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_set_round(RS_ROUNDMODE_E m_mode);

/**
 * \brief	get Resampler interpolation rounding mode
 *
 * \param[out]	m_mode	 Resampler rounding mode
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_get_round(RS_ROUNDMODE_E *m_mode);

/**
 * \brief	set Resampler scale mode and ratio
 *
 * \param[in]	scale_mode	 Resampler Scaling method
 * \param[in]	ratio	 Resampler Scaling Ratio
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_set_scale(RS_SCALEMODE_E scale_mode, RS_SCALERATIO_E ratio);

/**
 * \brief	get Resampler scale mode and ratio
 *
 * \param[out]	scale_mode	 Resampler Scaling method
 * \param[out]	ratio	 Resampler Scaling Ratio
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_get_scale(RS_SCALEMODE_E *scale_mode, RS_SCALERATIO_E *ratio);

/**
 * \brief	set Resampler crop setting
 *
 * \param[in]	crop_stx	 Resampler ROI start x-position
 * \param[in]	crop_sty	 Resampler ROI start y-position
 * \param[out]	crop_width	 Resampler ROI width
 * \param[out]	crop_height	 Resampler ROI height
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_set_crop(uint16_t crop_stx,uint16_t crop_sty, uint16_t crop_width, uint16_t crop_height);

/**
 * \brief	get Resampler crop setting
 *
 * \param[out]	crop_stx	 Resampler ROI start x-position
 * \param[out]	crop_sty	 Resampler ROI start y-position
 * \param[out]	crop_width	 Resampler ROI width
 * \param[out]	crop_height	 Resampler ROI height
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_get_crop(uint16_t *crop_stx,uint16_t *crop_sty, uint16_t *crop_width, uint16_t *crop_height);

/**
 * \brief	get RS output Memory Size for DMAC
 *
 * \param[in]	rs_cfg	 Resampler configuration
 * \param[out]	mem_size	 Resampler output memory size according to configuration
 * \return	RS_ERROR_E.
 */
RS_ERROR_E hx_drv_rs_get_OutMEMSize(Resampler_CFG_T rs_cfg, uint32_t *mem_size);
/** @} */

#endif

#ifndef _HX_DRV_DATAPATH_H_
#define _HX_DRV_DATAPATH_H_

#include "embARC_toolchain.h"
/**
 * \defgroup	DATAPATH_DRV	Data path Driver
 * \ingroup		DATAPATH_DRV
 * \brief		Data path Driver Declaration
 * \details Application can use DP driver API to control DP Mux and CLK Source by application\n
 * <pre>
 * For Example
 * Ex1: Set Datapath Clock Source RC36M or XTAL24M
 * 		hx_drv_dp_set_dp_clk_src(DP_DP_CLK_SRC_E clk_src);
 * Ex2: Set MCLK Source is from RC36M or XTAL24M
 * 		hx_drv_dp_set_mclk_src(DP_MCLK_SRC_INT_EXT_E clk_int_ext, DP_MCLK_SRC_INT_SEL_E clk_int_src);
 * Ex3: DP Mux already handle in Datapath library so you may not need use DP driver Mux API
 * </pre>
 */


/**
 * \defgroup	DATAPATH_DRV_ENUM	Datapath Driver Enumeration
 * \ingroup	DATAPATH_DRV
 * \brief	Defines some enumeration of Datapath Driver need.
 * @{
 */
/**
 * \enum DP_ERROR_E
 * \brief DP Errors Type
 */
typedef enum
{
	DP_NO_ERROR                     	= 0,	/**< No ERROR */
	DP_ERROR_NOT_INIT              	    = 1,	/**< ERROR MSG: not init */
	DP_ERROR_ALREADY_INIT               = 2,	/**< ERROR MSG: already init */
	DP_ERROR_INVALID_PARAMETERS     	= 3,	/**< ERROR MSG: Invalid parameters */
	DP_UNKNOWN_ERROR      				= 4,	/**< ERROR MSG: UNKNOWN ERROR*/
} DP_ERROR_E;


/**
 * \enum DP_MUX_INP_E
 * \brief INP input mux
 */
typedef enum{
	DP_MUX_INP_DISABLE,		/**< mask data input */
	DP_MUX_INP_SENSOR,		/**< INP input from sensor */
	DP_MUX_INP_TPG			/**< INP input from TPG */
}DP_MUX_INP_E;


/**
 * \enum DP_MUX_FILTER_E
 * \brief INP or TPG output to 2x2/5x5 filter input mux
 */
typedef enum
{
	DP_MUX_FILTER_DISABLE			= 0,	/**< mask data input */
	DP_MUX_FILTER_INP_TO_XX			= 1,	/**< INP to 2x2/5x5 filter */
	DP_MUX_FILTER_TPG_TO_XX			= 2,	/**< TPG to 2x2/5x5 filter */
} DP_MUX_FILTER_E;
        

/**
 * \enum DP_MUX_CDM_E
 * \brief 2x2 or mux_filter output to CDM input mux
 */
typedef enum
{
	DP_MUX_CDM_DISABLE   		   = 0,	/**< mask data input */
	DP_MUX_CDM_2X2_TO_CDM		   = 1,	/**< 2x2 filter output to CDM */
	DP_MUX_CDM_MUXFILTER_TO_CDM	   = 2,	/**< mux_filter output to CDM */
} DP_MUX_CDM_E;


/**
 * \enum DP_MUX_JPEG_E
 * \brief 5x5 filter or TPG output to JPEG input mux:
 */
typedef enum
{
	DP_MUX_JPEG_DISABLE				= 0,	/**< mask data input */
	DP_MUX_JPEG_5X5_TO_JPEGENC		= 1,	/**< 5x5 filter to JPEG(encoder) */
	DP_MUX_JPEG_TPG_TO_JPEG			= 2,	/**< TPG to JPEG */
} DP_MUX_JPEG_E;

/**
 * \enum DP_MUX_WDMA1_E
 * \brief CDM/mux_cdm output to WDMA1 input mux
 */
typedef enum
{
	DP_MUX_WDMA1_DISABLE			= 0,	/**< mask data input */
	DP_MUX_WDMA1_CDM_TO_WDMA1		= 1,	/**< CDM to WDMA1 */
	DP_MUX_WDMA1_MUXCDM_TO_WDMA1	= 2,	/**< mux_cdm to WDMA1 */
} DP_MUX_WDMA1_E;

/**
 * \enum DP_MUX_WDMA2_E
 * \brief mux_filter/JPEG output to WDMA2 input mux
 */
typedef enum
{
	DP_MUX_WDMA2_DISABLE				= 0,	/**< mask data input */
	DP_MUX_WDMA2_MUXFILTER_TO_WDMA2		= 1,	/**< mux_filter output to WDMA2 */
	DP_MUX_WDMA2_JPEGENC_TO_WDMA2		= 2,	/**< JPEG(encode) to WDMA2 */
} DP_MUX_WDMA2_E;

/**
 * \enum DP_MUX_WDMA3_E
 * \brief 5x5 filter/JPEG output to WDMA3 input mux
 */
typedef enum
{
	DP_MUX_WDMA3_DISABLE        	 = 0,	/**< mask data input */
	DP_MUX_WDMA3_JPEGDEC_TO_WDMA3    = 1,	/**< JPEG(decoder) to WDMA3 */
	DP_MUX_WDMA3_5X5_TO_WDMA3    	 = 2,	/**< 5x5 filter output to WDMA3 */
} DP_MUX_WDMA3_E;


/**
 * \enum DP_INT_CDM_MOTION_MASK_E
 * \brief DATAPATH Motion Interrupt Mask
 */
typedef enum
{
	DP_INT_MASK_CDM_MOTION_DISABLE       = 0,	/**< Disable Interrupt Mask */
	DP_INT_MASK_CDM_MOTION_ENABLE        = 1,	/**< Enable Interrupt Mask */
} DP_INT_CDM_MOTION_MASK_E;

/**
 * \enum DP_INT_CDM_HL_OVERFLOW_MASK_E
 * \brief CDM HL Overflow Interrupt Mask
 */
typedef enum
{
	DP_INT_MASK_CDM_HL_OVERFLOW_DISABLE       = 0,	/**< Disable Interrupt Mask */
	DP_INT_MASK_CDM_HL_OVERFLOW_ENABLE        = 1,	/**< Enable Interrupt Mask */
} DP_INT_CDM_HL_OVERFLOW_MASK_E;

/**
 * \enum DP_INT_CDM_HL_UNDERFLOW_MASK_E
 * \brief CDM HL Underflow Interrupt Mask
 */
typedef enum
{
	DP_INT_MASK_CDM_HL_UNDERFLOW_DISABLE       = 0,	/**< Disable Interrupt Mask */
	DP_INT_MASK_CDM_HL_UNDERFLOW_ENABLE        = 1,	/**< Enable Interrupt Mask */
} DP_INT_CDM_HL_UNDERFLOW_MASK_E;

/**
 * \enum DP_INT_STATUS_E
 * \brief Datapath Interrupt status
 */
typedef enum
{
	DP_INT_STATUS_NO				       = 0,	/**< No Interrupt Status */
	DP_INT_STATUS_CDM_MOTION_ON		  	   = 1,	/**< CDM Motion Interrupt Status */
	DP_INT_STATUS_CDM_HL_OVERFLOW_ON       = 2,	/**< CDM HL Overflow Interrupt Status */
	DP_INT_STATUS_CDM_HL_UNDERFLOW_ON      = 4,	/**< CDM HL Underflow Interrupt Status */
} DP_INT_STATUS_E;

/**
 * \enum DP_INP_RX_CLK_SRC_E
 * \brief Datapath INP RX CLK Source
 */
typedef enum
{
	DP_INP_RX_CLK_SRC_SENSOR		   = 0,	/**< RX CLK Source from Sensor */
	DP_INP_RX_CLK_SRC_DP		  	   = 1,	/**< RX CLK Source from DP */
} DP_INP_RX_CLK_SRC_E;

/**
 * \enum DP_MCLK_SRC_INT_EXT_E
 * \brief Sensor MCLK Source Internal or External
 */
typedef enum
{
	DP_MCLK_SRC_INTERNAL		   = 0,	/**< MCLK Source from 0:internal(xtal_24m/rc_36m) */
	DP_MCLK_SRC_EXTERNAL		   = 1,	/**< MCLK CLK Source from 1:external (test_clk6) */
} DP_MCLK_SRC_INT_EXT_E;

/**
 * \enum DP_MCLK_SRC_INT_EXT_E
 * \brief Sensor MCLK Source Internal from RC36M or XTAL
 */
typedef enum
{
	DP_MCLK_SRC_INT_SEL_RC36M	  = 0,	/**< MCLK Internal Source from 0:rc_36m */
	DP_MCLK_SRC_INT_SEL_XTAL	  = 1,	/**< MCLK Internal Source from 1:xtal_24m */
} DP_MCLK_SRC_INT_SEL_E;

/**
 * \enum DP_DP_CLK_SRC_E
 * \brief Datapath CLK Source 0:rc_36m, 1:xtal_24m_post
 */
typedef enum
{
	DP_CLK_SRC_RC_36M		   = 0,	/**< DP CLK Source from 0:rc_36m */
	DP_CLK_SRC_XTAL_24M_POST	= 1,	/**< DP CLK Source from 1:xtal_24m_post */
} DP_DP_CLK_SRC_E;

/**
 * \enum DP_DP_CLK_GATED_SEL_E
 * \brief Datapath CLK Gated 0: by CPU, 1: by PMU and CPU
 */
typedef enum
{
	DP_CLK_GATED_SEL_CPU		   = 0,	/**< DP CLK GATED SEL CPU */
	DP_CLK_GATED_SEL_CPU_PMU	   = 1,	/**< DP CLK GATED SEL CPU and PMU */
} DP_DP_CLK_GATED_SEL_E;
/** @} */

/**
 * \defgroup	DATAPATH_DRV_REGSTRUCT	Datapath Driver Structure
 * \ingroup	DATAPATH_DRV
 * \brief	contains definitions of Datapath Driver structure.
 * @{
 */
/**
 * \struct DP_CFG_MUX_T
 * \brief Datapath Mux configuration by datapath Driver
 */
typedef struct
{
	DP_MUX_INP_E usINPMux;			/**< INP input mux */
	DP_MUX_FILTER_E usDPFilterMux;	/**< INP or TPG output to 2x2/5x5 filter input mux */
	DP_MUX_CDM_E usDPCDMMux;		/**< 2x2 or mux_filter output to CDM input mux */
	DP_MUX_JPEG_E usDPJPEGMux;		/**< 5x5 filter or TPG output to JPEG input mux */
	DP_MUX_WDMA1_E usDPWDMA1Mux;	/**< CDM/mux_cdm output to WDMA1 input mux */
	DP_MUX_WDMA2_E usDPWDMA2Mux;	/**< mux_filter/JPEG output to WDMA2 input mux */
	DP_MUX_WDMA3_E usDPWDMA3Mux;	/**< 5x5 filter/JPEG output to WDMA3 input mux */
}DP_CFG_MUX_T;

/**
 * \struct DP_CFG_T
 * \brief Datapath configuration by datapath Driver
 */
typedef struct
{
	DP_CFG_MUX_T  mux;			/**< Datapath Mux configuration */
	DP_INT_CDM_MOTION_MASK_E  cdm_motion_mask;	/**< Datapath CDM Motion Interrupt configuration */
	DP_INT_CDM_HL_OVERFLOW_MASK_E  cdm_overflow_mask;	/**< Datapath CDM HL Overflow Interrupt configuration */
	DP_INT_CDM_HL_UNDERFLOW_MASK_E cdm_underflow_mask;	/**< Datapath CDM HL Underflow Interrupt configuration */
} DP_CFG_T;
/** @} */

/**
 * \defgroup	DATAPATH_DRV_FUNCDLR	DataPath Driver Function Declaration
 * \ingroup	DATAPATH_DRV
 * \brief	Contains declarations of DataPath Driver functions.
 * @{
 */
/**
 * \brief	Datapth Interrupt callback function
 *
 * \return	void
 */
typedef void (*DP_ISREvent_t) (DP_INT_STATUS_E event);

/**
 * \brief	init datapath Driver
 *
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_init();

/**
 * \brief	set all DP Driver related Setting
 *
 * \param[in]	all_cfg	 Datapath configuration
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_set_allCfg(DP_CFG_T all_cfg);

/**
 * \brief	get default DP related Setting
 *
 * \param[out]	dp_cfg	 Datapath configuration
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_get_defCfg(DP_CFG_T *dp_cfg);

/**
 * \brief	set all DP MUX related Setting
 *
 * \param[in]	mux_cfg	 Datapath Mux configuration
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_set_MuxCfg(DP_CFG_MUX_T mux_cfg);

/**
 * \brief	get all DP MUX related Setting
 *
 * \param[out]	mux_cfg	 Datapath Mux configuration
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_get_MuxCfg(DP_CFG_MUX_T *mux_cfg);

/**
 * \brief	set DP CDM interrupt Motion Mask enable or disable
 *
 * \param[in]	mask	 CDM Motion Interrupt Mask Setting
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_set_INTMotionMask(DP_INT_CDM_MOTION_MASK_E mask);

/**
 * \brief	get DP CDM interrupt Motion Mask enable or disable
 *
 * \param[out]	mask	 CDM Motion Interrupt Mask Setting
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_get_INTMotionMask(DP_INT_CDM_MOTION_MASK_E *mask);

/**
 * \brief	set DP CDM interrupt FIFO Overflow Mask enable or disable
 *
 * \param[in]	mask	 CDM HL Overflow Interrupt Mask Setting
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_set_INTOverflowMask(DP_INT_CDM_HL_OVERFLOW_MASK_E mask);

/**
 * \brief	get DP CDM interrupt FIFO Overflow Mask enable or disable
 *
 * \param[out]	mask	 CDM HL Overflow Interrupt Mask Setting
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_get_INTOverflowMask(DP_INT_CDM_HL_OVERFLOW_MASK_E *mask);

/**
 * \brief	set DP CDM interrupt FIFO Underflow Mask enable or disable
 *
 * \param[in]	mask	 CDM HL Underflow Interrupt Mask Setting
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_set_INTUnderflowMask(DP_INT_CDM_HL_UNDERFLOW_MASK_E mask);

/**
 * \brief	get DP CDM interrupt FIFO Underflow Mask enable or disable
 *
 * \param[out]	mask	 CDM HL Underflow Interrupt Mask Setting
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_get_INTUnderflowMask(DP_INT_CDM_HL_UNDERFLOW_MASK_E *mask);

/**
 * \brief	get DP CDM interrupt Status
 *
 * \param[out]	status	 CDM Interrupt Status
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_get_INTStatus(DP_INT_STATUS_E *status);

/**
 * \brief	register DP CDM interrupt status callback
 *
 * \param[in]	cb_event	 CDM interrupt event callback function
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_register_cb(DP_ISREvent_t  cb_event);

/**
 * \brief	start Software reset DP related block INP, SensorCtrl, HW-ACC, xDMA1*
 *
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_dp_start_swreset();

/**
 * \brief	stop Software reset(return to normal) DP related block INP, SensorCtrl, HW-ACC, xDMA1
 *
 * \param[in]	with_sensorctrl	 0 : not stop sensor control swreset, 1 : stop sensor control swreset
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_dp_stop_swreset(int with_sensorctrl);

/**
 * \brief	start Software reset DP related block RS & RSDMA
 *
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_rs_start_swreset();

/**
 * \brief	stop Software reset(return to normal) DP related block RS & RSDMA
 *
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_rs_stop_swreset();

/**
 * \brief	start Software reset(return to normal) DP related block HOG & HOGDMA
 *
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_hog_start_swreset();

/**
 * \brief	stop Software reset DP related block HOG & HOGDMA
 *
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_hog_stop_swreset();

/**
 * \brief	get INP RX CLK source
 *
 * \param[out]	clk_src INP RX CLK Source from Sensor or DP
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_get_rx_clk_src(DP_INP_RX_CLK_SRC_E *clk_src);

/**
 * \brief	set INP RX CLK source
 *
 * \param[in]	clk_src INP RX CLK Source from Sensor or DP
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_set_rx_clk_src(DP_INP_RX_CLK_SRC_E clk_src);

/**
 * \brief	get Sensor MCLK source
 *
 * \param[out]	clk_int_ext MCLK Source from Internal or External
 * \param[out]	clk_int_src MCLK Source from RC36 or XTAL24M
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_get_mclk_src(DP_MCLK_SRC_INT_EXT_E *clk_int_ext, DP_MCLK_SRC_INT_SEL_E *clk_int_src);

/**
 * \brief	set Sensor MCLK source
 *
 * \param[in]	clk_int_ext MCLK Source from Internal or External
 * \param[in]	clk_int_src MCLK Source from RC36 or XTAL24M
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_set_mclk_src(DP_MCLK_SRC_INT_EXT_E clk_int_ext, DP_MCLK_SRC_INT_SEL_E clk_int_src);

/**
 * \brief	get DP CLK source
 *
 * \param[out]	clk_src DP CLK Source from 0:rc_36m or 1:xtal_24m_post
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_get_dp_clk_src(DP_DP_CLK_SRC_E *clk_src);

/**
 * \brief	set DP CLK source
 *
 * \param[in]	clk_src DP CLK Source from 0:rc_36m or 1:xtal_24m_post
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_set_dp_clk_src(DP_DP_CLK_SRC_E clk_src);

/**
 * \brief	get DP CLK Gated Selection
 *
 * \param[out]	clk_src DP CLK Gated from CPU or (PMU+CPU)
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_get_dp_gatedclk(DP_DP_CLK_GATED_SEL_E *clk_src);

/**
 * \brief	set DP CLK Gated Selection
 *
 * \param[in]	clk_src DP CLK Source from CPU or (PMU+CPU)
 * \return	DP_ERROR_E
 */
DP_ERROR_E hx_drv_dp_set_dp_gatedclk(DP_DP_CLK_GATED_SEL_E clk_src);

/** @} */
#endif

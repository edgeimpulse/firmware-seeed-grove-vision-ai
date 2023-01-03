/**
 * @file hx_drv_CIS_common.c
 * @author himax/902447
 * @brief 
 * @version V1.0.0
 * @date 2019-06-24
 * 
 * @copyright (C) COPYRIGHT, Himax, Inc. ALL RIGHTS RESERVED
 * 
 */

#include <stdio.h>
#include <string.h>
#include "embARC.h"
#include "embARC_debug.h"
#include "hx_drv_sensorctrl.h"
#include "apexextensions.h"
#include "arc_exception.h"
#include "embARC_toolchain.h"
#include "embARC_error.h"
#include "board_config.h"
#include "io_config.h"
#include "io_config_ext.h"
#include "hardware_config.h"
#include "hx_drv_ckgen.h"
#include "board.h"
#include "board_config.h"
#include "hx_drv_iic_m.h"
#include "hx_drv_iomux.h"
#include "hx_drv_CIS_common.h"

static uint8_t g_slave_id = HX_CIS_SLAVE_ID;

HX_CIS_ERROR_E hx_drv_cis_init(CIS_XHSHUTDOWN_INDEX_E xshutdown_pin, SENSORCTRL_MCLK_E mclk_div)
{
    SENSORCTRL_MCLKCTRL_E mclkctrl;
    IOMUX_INDEX_E iomux_idx;
    if(mclk_div == SENSORCTRL_MCLK_NO)
    {
    	hx_drv_sensorctrl_set_MCLK(0, 1);
    }else{
    	hx_drv_sensorctrl_set_MCLK(1, mclk_div);
    }

	hx_drv_sensorctrl_get_MCLKCtrl(&mclkctrl);
	if(mclkctrl != SENSORCTRL_MCLKCTRL_NONAOS)
	{
		hx_drv_sensorctrl_set_MCLKCtrl(SENSORCTRL_MCLKCTRL_NONAOS);
	}

	hx_drv_sensorctrl_set_xSleepCtrl(SENSORCTRL_XSLEEP_BY_CPU);
	hx_drv_sensorctrl_set_xSleep(0);
	if(xshutdown_pin != CIS_XHSUTDOWN_IOMUX_NONE)
	{
		iomux_idx = (IOMUX_INDEX_E)xshutdown_pin;
		hx_drv_sensorctrl_set_xShutdown(iomux_idx, 0);

		if(is_ref_cpu_clk_by_var()){
			board_delay_cycle(1* (get_ref_cpu_clk()/BOARD_SYS_TIMER_HZ));
		}else{
			board_delay_cycle(1* BOARD_SYS_TIMER_MS_CONV);
		}

		hx_drv_sensorctrl_set_xShutdown(iomux_idx, 1);
		
		if(is_ref_cpu_clk_by_var()){
			board_delay_cycle(50* (get_ref_cpu_clk()/BOARD_SYS_TIMER_US_HZ));
		}else{
			board_delay_cycle(50* BOARD_SYS_TIMER_US_CONV);
		}			
	}

	hx_drv_sensorctrl_set_xSleepCtrl(SENSORCTRL_XSLEEP_BY_CPU);
#ifdef HM0435
    hx_drv_sensorctrl_set_xSleep(0);
#else
	hx_drv_sensorctrl_set_xSleep(1);
#endif

	return HX_CIS_NO_ERROR;
}

HX_CIS_ERROR_E hx_drv_cis_set_slaveID(uint8_t slave_id)
{
	g_slave_id = slave_id;
	return HX_CIS_NO_ERROR;
}
HX_CIS_ERROR_E hx_drv_cis_get_slaveID(uint8_t *slave_id)
{
	*slave_id = g_slave_id;
	return HX_CIS_NO_ERROR;
}


/* write by reg table */
HX_CIS_ERROR_E
hx_drv_cis_setRegTable (
	   HX_CIS_SensorSetting_t *pSensorSetting, uint16_t Length) {
	   HX_CIS_ERROR_E status = HX_CIS_NO_ERROR;
	   uint32_t i = 0;
	   uint8_t val;
	   uint16_t regAddr;

	   if (Length == 0)
	   {
           EMBARC_PRINTF("setRegTable fail: no item\r\n");
	       return HX_CIS_ERROR_NOT_SUPPORT;
	   }

	#ifdef SUPPROT_CIS_DEBUG_PRINT
	   EMBARC_PRINTF("\n");
	   EMBARC_PRINTF("hx_drv_cis_setRegTable_Sz=%d\r\n",Length);
	#endif

	   for (i=0; i < Length; i++) {
	       status = HX_CIS_NO_ERROR;
	       if (HX_CIS_I2C_Action_W == pSensorSetting[i].I2C_ActionType) {
	    	   val = pSensorSetting[i].Value;
	    	   regAddr = pSensorSetting[i].RegAddree;
	    	   for(uint8_t idx = 0; idx < HX_CIS_I2C_RETRY_TIME; idx++)
	    	   {
	#ifdef SUPPROT_CIS_DEBUG_PRINT
	               EMBARC_PRINTF("hx_drv_cis_set_reg(0x%04x, 0x%02x) \n", regAddr, val);
	#endif
	    		   if(hx_drv_cis_set_reg(regAddr, val, 0) != HX_CIS_NO_ERROR)
	    		   {
	    			   EMBARC_PRINTF("    retry=%d, (regAddr=0x%04x, val=0x%02x) Fail\r\n",idx,regAddr, val);
	    			   if(idx >= (HX_CIS_I2C_RETRY_TIME - 1))
	    				   return HX_CIS_ERROR_I2C;
	    		   }else{
	    			   if(idx > 0)
	    				   EMBARC_PRINTF("    retry=%d, (regAddr=0x%04x, val=0x%02x)  Success\r\n",idx,regAddr, val);
	    			   break;
	    		   }
	    	   }
	       }
	       else if (HX_CIS_I2C_Action_R == pSensorSetting[i].I2C_ActionType) {
	    	   val = 0xFF; //default
	    	   regAddr = pSensorSetting[i].RegAddree;
	    	   if(hx_drv_cis_get_reg(regAddr, &val) != HX_CIS_NO_ERROR)
	    	   {
	    			return HX_CIS_ERROR_I2C;
	    	   }
	    	   pSensorSetting[i].Value = val;
	       }
	       else if (HX_CIS_I2C_Action_S == pSensorSetting[i].I2C_ActionType) {
				if(is_ref_cpu_clk_by_var()){
					board_delay_cycle(pSensorSetting[i].RegAddree * (get_ref_cpu_clk()/BOARD_SYS_TIMER_HZ));
				}else{
					board_delay_cycle(pSensorSetting[i].RegAddree * BOARD_SYS_TIMER_MS_CONV);
				}

	           status = HX_CIS_NO_ERROR;
	       }
	       else {
	           EMBARC_PRINTF("\n\rsetting index = %d, unknow action=%d ", i ,pSensorSetting[i].I2C_ActionType);
	           status = HX_CIS_ERROR_INVALID_PARAMETERS;
	           return status;
	       }
	   }

	#ifdef SUPPROT_CIS_DEBUG_PRINT
	   EMBARC_PRINTF("\n");
	#endif

	   return status;
}

/**
 * \brief Get Configuration to CIS Sensor by I2C Master.
 *
 * \param[in] pSensorSetting Configuration table for CIS Sensor
 * \param[in] Length Configuration table Length for CIS Sensor
 * \return HX_CIS_ERROR_E.
 * */
HX_CIS_ERROR_E hx_drv_cis_getRegTable(HX_CIS_SensorSetting_t *pSensorSetting, uint16_t Length)
{
	   HX_CIS_ERROR_E status = HX_CIS_NO_ERROR;
	   uint32_t i = 0;
	   uint8_t val;
	   uint16_t regAddr;

	#ifdef SUPPROT_CIS_DEBUG_PRINT
	   EMBARC_PRINTF("\n");
	   EMBARC_PRINTF("hx_drv_cis_setRegTable_Sz=%d\r\n",Length);
	#endif

	   for (i=0; i < Length; i++) {
	       status = HX_CIS_NO_ERROR;
	       if ((HX_CIS_I2C_Action_R == pSensorSetting[i].I2C_ActionType) ||
	    		   (HX_CIS_I2C_Action_W == pSensorSetting[i].I2C_ActionType)) {
	    	   val = 0xFF; //default
	    	   regAddr = pSensorSetting[i].RegAddree;
	    	   if(hx_drv_cis_get_reg(regAddr, &val) != HX_CIS_NO_ERROR)
	    	   {
	    			return HX_CIS_ERROR_I2C;
	    	   }
	    	   pSensorSetting[i].Value = val;
	    	   EMBARC_PRINTF("0x%04x=0x%02x\r\n",regAddr, val);
	       }
	       else if (HX_CIS_I2C_Action_S == pSensorSetting[i].I2C_ActionType) {
	           status = HX_CIS_NO_ERROR;
	       }
	   }

	#ifdef SUPPROT_CIS_DEBUG_PRINT
	   EMBARC_PRINTF("\n");
	#endif

	   return status;
}

HX_CIS_ERROR_E hx_drv_cis_set_reg(uint16_t addr, uint8_t val, uint8_t cmu_update)
{
    uint8_t rwBuffer[HX_CIS_I2C_DATA_BYTE]={0x00};
    uint8_t regLen = HX_CIS_I2C_ADDR_BYTE;
    uint8_t regAddr[HX_CIS_I2C_ADDR_BYTE];
    int32_t retI2C = 0;

    SENSORCTRL_MCLKCTRL_E mclkctrl;
	hx_drv_sensorctrl_get_MCLKCtrl(&mclkctrl);
	if(mclkctrl != SENSORCTRL_MCLKCTRL_NONAOS)
	{
		hx_drv_sensorctrl_set_MCLKCtrl(SENSORCTRL_MCLKCTRL_NONAOS);
	}
#ifdef CIS_OV2640_BAYER
    regAddr[0]= addr & 0xFF;
#else
    regAddr[0]= (addr >> 8) & 0xFF;
    regAddr[1]= addr & 0xFF;
#endif

    rwBuffer[0] = val;
   	retI2C = hx_drv_i2cm_write_data(HX_CIS_IIC_M_ID, g_slave_id, regAddr, regLen, rwBuffer, HX_CIS_I2C_DATA_BYTE);
   	if(retI2C < E_OK)
   	{
   #ifdef SUPPROT_CIS_DEBUG_PRINT
   	    EMBARC_PRINTF("hm01B0_set_reg I2C fail\r\n");
   #endif
   		return HX_CIS_ERROR_I2C;
   	}


	if(cmu_update)
	{
	  	if(hx_drv_cis_CMU_Update() != HX_CIS_NO_ERROR)
	  	{
#ifdef SUPPROT_CIS_DEBUG_PRINT
	  	        EMBARC_PRINTF("hx_drv_cis_CMU_Update fail\r\n");
#endif
	  			return HX_CIS_ERROR_I2C;
	  	}
	}
	return HX_CIS_NO_ERROR;
}

HX_CIS_ERROR_E hx_drv_cis_get_reg(uint16_t addr, uint8_t *val)
{
#ifdef CIS_OV2640_BAYER
    uint8_t  RegByteCount = 1;//...2;
#else
    uint8_t  RegByteCount = 2;
#endif
    HX_CIS_ERROR_E status = HX_CIS_NO_ERROR;
    uint8_t rwBuffer[HX_CIS_I2C_DATA_BYTE]={0x00};
    uint8_t regAddr[HX_CIS_I2C_ADDR_BYTE];
    int32_t retI2C = 0;

    SENSORCTRL_MCLKCTRL_E mclkctrl;
	hx_drv_sensorctrl_get_MCLKCtrl(&mclkctrl);
	if(mclkctrl != SENSORCTRL_MCLKCTRL_NONAOS)
	{
		hx_drv_sensorctrl_set_MCLKCtrl(SENSORCTRL_MCLKCTRL_NONAOS);
	}

    *val = 0;
#ifdef CIS_OV2640_BAYER
    regAddr[0]= addr & 0xFF;
#else
    regAddr[0]= (addr >> 8) & 0xFF;
    regAddr[1]= addr & 0xFF;
#endif

    retI2C = hx_drv_i2cm_writeread(HX_CIS_IIC_M_ID, g_slave_id, regAddr, RegByteCount, rwBuffer, HX_CIS_I2C_DATA_BYTE);
    if(retI2C < E_OK)
    {
  #ifdef SUPPROT_HM01B0_DEBUG_PRINT
  	   EMBARC_PRINTF("HX CIS getRegister I2C fail\r\n");
  #endif
  	  return HX_CIS_ERROR_I2C;
    }else{
    	status = HX_CIS_NO_ERROR;
    }

    if (HX_CIS_NO_ERROR == status) {
    	*val = rwBuffer[0];
    }else{
#ifdef SUPPROT_HM01B0_DEBUG_PRINT
	    EMBARC_PRINTF("hx_drv_cis_get_reg fail 0x%x\r\n", regAddr);
#endif
    }

	return HX_CIS_NO_ERROR;
}
/**
 * \brief Set Register value to CIS Sensor by I2C Master.
 *
 * \param[in] addr Register Address for CIS Sensor(8bit address mode)
 * \param[in] val Register value for CIS Sensor
 * \param[in] cmu_update After register setting, it need CMU update to Sensor or not
 * \return HX_CIS_ERROR_E.
 * */
HX_CIS_ERROR_E hx_drv_cis_8bit_addr_set_reg(uint8_t addr, uint8_t val, uint8_t cmu_update)
{
    uint8_t rwBuffer[HX_CIS_I2C_DATA_BYTE]={0x00};
    int32_t retI2C = 0;

    SENSORCTRL_MCLKCTRL_E mclkctrl;
	hx_drv_sensorctrl_get_MCLKCtrl(&mclkctrl);
	if(mclkctrl != SENSORCTRL_MCLKCTRL_NONAOS)
	{
		hx_drv_sensorctrl_set_MCLKCtrl(SENSORCTRL_MCLKCTRL_NONAOS);
	}

    rwBuffer[0] = val;
   	retI2C = hx_drv_i2cm_write_data(HX_CIS_IIC_M_ID, g_slave_id, &addr, 1, rwBuffer, HX_CIS_I2C_DATA_BYTE);
   	if(retI2C < E_OK)
   	{
   #ifdef SUPPROT_CIS_DEBUG_PRINT
   	    EMBARC_PRINTF("hm01B0_set_reg I2C fail\r\n");
   #endif
   		return HX_CIS_ERROR_I2C;
   	}


	if(cmu_update)
	{
	  	if(hx_drv_cis_CMU_Update() != HX_CIS_NO_ERROR)
	  	{
#ifdef SUPPROT_CIS_DEBUG_PRINT
	  	        EMBARC_PRINTF("hx_drv_cis_CMU_Update fail\r\n");
#endif
	  			return HX_CIS_ERROR_I2C;
	  	}
	}
	return HX_CIS_NO_ERROR;
}

/**
 * \brief Get Current Register value from CIS Sensor by I2C Master.
 *
 * \param[in] addr Register Address for CIS Sensor(8bit address mode)
 * \param[out] val Current Register value from CIS Sensor
 * \return HX_CIS_ERROR_E.
 * */
HX_CIS_ERROR_E hx_drv_cis_8bit_addr_get_reg(uint8_t addr, uint8_t *val)
{
    uint8_t  RegByteCount = 1;//2
    HX_CIS_ERROR_E status = HX_CIS_NO_ERROR;
    uint8_t rwBuffer[HX_CIS_I2C_DATA_BYTE]={0x00};
    int32_t retI2C = 0;

    SENSORCTRL_MCLKCTRL_E mclkctrl;
	hx_drv_sensorctrl_get_MCLKCtrl(&mclkctrl);
	if(mclkctrl != SENSORCTRL_MCLKCTRL_NONAOS)
	{
		hx_drv_sensorctrl_set_MCLKCtrl(SENSORCTRL_MCLKCTRL_NONAOS);
	}

    *val = 0;

    retI2C = hx_drv_i2cm_writeread(HX_CIS_IIC_M_ID, g_slave_id, &addr, RegByteCount, rwBuffer, HX_CIS_I2C_DATA_BYTE);
    if(retI2C < E_OK)
    {
  #ifdef SUPPROT_HM01B0_DEBUG_PRINT
  	   EMBARC_PRINTF("HX CIS getRegister I2C fail\r\n");
  #endif
  	  return HX_CIS_ERROR_I2C;
    }else{
    	status = HX_CIS_NO_ERROR;
    }

    if (HX_CIS_NO_ERROR == status) {
    	*val = rwBuffer[0];
    }else{
#ifdef SUPPROT_HM01B0_DEBUG_PRINT
	    EMBARC_PRINTF("hx_drv_cis_get_reg fail 0x%x\r\n", regAddr);
#endif
    }

	return HX_CIS_NO_ERROR;
}

HX_CIS_ERROR_E hx_drv_cis_CMU_Update(void) {
	HX_CIS_ERROR_E status = HX_CIS_NO_ERROR;
    uint8_t rwBuffer[HX_CIS_I2C_DATA_BYTE]={0x00};
    uint8_t regLen = HX_CIS_I2C_ADDR_BYTE;
    uint8_t regAddr[HX_CIS_I2C_ADDR_BYTE];
    int32_t retI2C = 0;

    SENSORCTRL_MCLKCTRL_E mclkctrl;
	hx_drv_sensorctrl_get_MCLKCtrl(&mclkctrl);
	if(mclkctrl != SENSORCTRL_MCLKCTRL_NONAOS)
	{
		hx_drv_sensorctrl_set_MCLKCtrl(SENSORCTRL_MCLKCTRL_NONAOS);
	}

    regAddr[0]= (HX_CIS_CMU_REG_ADDR >> 8) & 0xFF;
    regAddr[1]= HX_CIS_CMU_REG_ADDR & 0xFF;

    rwBuffer[0] = 1;
   	retI2C = hx_drv_i2cm_write_data(HX_CIS_IIC_M_ID, g_slave_id, regAddr, regLen, rwBuffer, HX_CIS_I2C_DATA_BYTE);
   	if(retI2C < E_OK)
   	{
   #ifdef SUPPROT_HM01B0_DEBUG_PRINT
   	    EMBARC_PRINTF("HX CIS CMU_Update I2C fail\r\n");
   #endif
   		return HX_CIS_ERROR_I2C;
   	}

     return status;
}

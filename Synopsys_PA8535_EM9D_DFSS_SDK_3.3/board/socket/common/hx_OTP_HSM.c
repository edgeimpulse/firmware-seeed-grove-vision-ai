/*
 * ssi.c
 *
 *  Created on: 2019¦~3¤ë7¤é
 *      Author: 902452
 */

#include "arc_timer.h"
#include "hx_OTP_HSM.h"

#include "hx_drv_timer.h"
uint32_t reg_val_PDSTB_PTRIM_tv=0,reg_val_PCE_tv=0;

void HX_OTP_HSM_initial(void)
{
	uint32_t reg_val = 0;
	uint32_t delay_time=0;
	
	reg_val_PDSTB_PTRIM_tv = _arc_read_uncached_32((void *)0xB0030004);
	reg_val_PCE_tv = _arc_read_uncached_32((void *)0xB0030008);
	
	//Delay time(us) = (1000/otp_clk) * STBD_tv
	reg_val = _arc_read_uncached_32((void *)0xB0030014);
	delay_time = (reg_val*1000)/CLK_OTP;
	#ifdef OS_FREERTOS
	board_delay_ms(1);
	#else
	if(delay_time<25)
		board_delay_us(25);
	else
		board_delay_us(delay_time);
	#endif
	//Write PDSTB [9:0]   Tsas time value = 1,Write PTRIM [25:16] Ttas time value = 1
	reg_val = _arc_read_uncached_32((void *)0xB0030004);
	reg_val &= 0xFC00FE00;
	reg_val |= 0x10001;
	_arc_write_uncached_32((void *)0xB0030004, reg_val);

	//Write PCE   [9:0]   Tcs  time value = 1
	reg_val = _arc_read_uncached_32((void *)0xB0030008);
	reg_val &= 0xFFFFFE00;
	reg_val |= 0x1;
	_arc_write_uncached_32((void *)0xB0030008, reg_val);

	//OTP register update,0xB0030018[0]=1
	reg_val = _arc_read_uncached_32((void *)0xB0030018);
	reg_val |= 0x1;
	_arc_write_uncached_32((void *)0xB0030018, reg_val);

	//Switch OTP control signal mux to Register control,0xB0010110[0]=1
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val |= 0x1;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);

	//PDSTB enable,0xB0010110[1]=1
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val |= 0x2;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);
	#ifdef OS_FREERTOS
	board_delay_ms(1);
	#else
	board_delay_us(2);
	#endif
	//PTRIM enable,0xB0010110[2]=1
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val |= 0x4;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);
	#ifdef OS_FREERTOS
	board_delay_ms(1);
	#else
	board_delay_us(50);
	#endif
	//PCE enable,0xB0010110[3]=1
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val |= 0x8;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);
	#ifdef OS_FREERTOS
	board_delay_ms(1);
	#else
	board_delay_us(10);
	#endif
	return;
}

void HX_OTP_HSM_normal_to_standby(void)
{
	uint32_t reg_val = 0;

	//PCE disable,0xB0010110[3]=0
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val &= 0xFFFFFFF7;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);

	//PTRIM disable,0xB0010110[2]=0
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val &= 0xFFFFFFFB;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);

	//PDSTB disable,0xB0010110[1]=0
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val &= 0xFFFFFFFD;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);

	return;
}
void HX_OTP_HSM_standby_to_normal(void)
{
	uint32_t reg_val = 0;
	
	//PDSTB enable,0xB0010110[1]=1
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val |= 0x2;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);
	#ifdef OS_FREERTOS
	board_delay_ms(1);
	#else
	board_delay_us(2);
	#endif
	//PTRIM enable,0xB0010110[2]=1
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val |= 0x4;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);
	#ifdef OS_FREERTOS
	board_delay_ms(1);
	#else
	board_delay_us(50);
	#endif
	//PCE enable,0xB0010110[3]=1
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val |= 0x8;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);
	#ifdef OS_FREERTOS
	board_delay_ms(1);
	#else
	board_delay_us(10);
	#endif
	return;
}

/* OTP HSM must be standby mode*/
void HX_OTP_HSM_close(void)
{
	uint32_t reg_val = 0;

	HX_OTP_HSM_normal_to_standby();
		
	_arc_write_uncached_32((void *)0xB0030004, reg_val_PDSTB_PTRIM_tv);
	_arc_write_uncached_32((void *)0xB0030008, reg_val_PCE_tv);

	//OTP register update,0xB0030018[0]=1
	reg_val = _arc_read_uncached_32((void *)0xB0030018);
	reg_val |= 0x1;
	_arc_write_uncached_32((void *)0xB0030018, reg_val);

	//Switch OTP control signal mux to OTP top,0xB0010110[0]=0
	reg_val = _arc_read_uncached_32((void *)0xB0010110);
	reg_val &= 0xFFFFFFFE;
	_arc_write_uncached_32((void *)0xB0010110, reg_val);

	return;
}


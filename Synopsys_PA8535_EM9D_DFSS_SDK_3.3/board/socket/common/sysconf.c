/* ------------------------------------------
 * Copyright (c) 2017, Synopsys, Inc. All rights reserved.

 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:

 * 1) Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * 2) Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.

 * 3) Neither the name of the Synopsys, Inc., nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
--------------------------------------------- */

#include "embARC_toolchain.h"
#include "sysconf.h"
#include "../configs/24/hardware_config.h"


#define PLL_CLK_IN	(BOARD_REF_CLK / 1000000)  /* PLL clock in */

static SYSCONF_REG_PTR sysconf_reg_ptr = (SYSCONF_REG_PTR)(BASE_ADDR_SYSCONFIG);


typedef struct pll_conf {
	uint32_t fout;
	uint32_t pll;
} PLL_CONF;

/* why m + 4 is required? from provided source code */
#define PLL_CONF_VAL(n, m, od) \
	(((n) << PLLCON_BIT_OFFSET_N) | \
	((m + 4) << (PLLCON_BIT_OFFSET_M)) | \
	((od) << PLLCON_BIT_OFFSET_OD)) \


/* the following configuration is based on Fin = 16 Mhz */
static const PLL_CONF pll_configuration[] = {
	{200, PLL_CONF_VAL(1, 25, 1)}, /* 200 Mhz */
	{100, PLL_CONF_VAL(1, 25, 2)}, /* 100 Mhz */
	{50,  PLL_CONF_VAL(1, 25, 3)},  /* 50 Mhz */
	{400, PLL_CONF_VAL(1, 25, 0)}, /* 400 Mhz */
	{150, PLL_CONF_VAL(4, 75, 1)}, /* 150 Mhz */
	{75,  PLL_CONF_VAL(4, 75, 2)},  /* 75 Mhz */
	{300, PLL_CONF_VAL(4, 75, 0)}, /* 300 Mhz */
	{25,  PLL_CONF_VAL(2, 25, 3)},  /* 25 Mhz */
	{72,  PLL_CONF_VAL(8, 144, 2)}, /* 72 Mhz */
	{144, PLL_CONF_VAL(8, 144, 1)}, /* 144 Mhz */
	{180, PLL_CONF_VAL(8, 180, 1)}, /* 180 Mhz */
};


/**
 * PLL Fout = Fin * M/ (N *n NO)
 *
 * Fref = Fin / N; Fvco = Fref * M Fout = Fvco / NO
 *
 *  N = input divider value (1, 2, 3 �� 15)
 *  M = feedback divider value (4, 5, 6 �� 16383)
 *  NO = output divider value (1, 2, 4, or 8)
 *
 *  1 Mhz <= Fref <= 50 Mhz
 *  200 Mhz <= Fvco <= 400 Mhz
 *
 */

void pll_conf_reg(uint32_t val)
{

	sysconf_reg_ptr->CLKSEL = CLKSEL_EXT_16M;
	/* 0x52000000 is not described in spec. */
	sysconf_reg_ptr->PLLCON = val | (0x52000000);

	sysconf_reg_ptr->PLLCON = val | (1 << PLLCON_BIT_OFFSET_PLLRST);
	sysconf_reg_ptr->PLLCON = val & (~(1 << PLLCON_BIT_OFFSET_PLLRST));

	while (!(sysconf_reg_ptr->PLLSTAT
		& (1 << PLLSTAT_BIT_OFFSET_PLLSTB)));

	sysconf_reg_ptr->CLKSEL = CLKSEL_PLL;
	/* from AHB_CLK_DIVIDER, not from DVFSS&PMC */
	sysconf_reg_ptr->AHBCLKDIV_SEL |= 1;
	/* AHB clk divisor = 1 */
	sysconf_reg_ptr->AHBCLKDIV = 0x1;
}

int32_t pll_fout_config(uint32_t freq)
{
	uint32_t i;

	if (freq == PLL_CLK_IN) {
		sysconf_reg_ptr->CLKSEL = CLKSEL_EXT_16M;
	}

	for (i = 0; i < EMBARC_ARRAY_COUNT(pll_configuration); i++) {
		if (pll_configuration[i].fout == freq) {
			break;
		}
	}

	if (i >= EMBARC_ARRAY_COUNT(pll_configuration)) {
		return -1;
	}

	pll_conf_reg(pll_configuration[i].pll);


	/* config eflash clk, must be < 100 Mhz */
	if (freq > 100) {
		eflash_clk_div(2);
	} else {
		eflash_clk_div(1);
	}

	return 0;
}

void ahb_clk_divisor(uint8_t div)
{
	sysconf_reg_ptr->AHBCLKDIV = div;
}

/**
 * \brief       enable the clk of ahb device
 *
 * \param[in]   dev ahb device number
 *
 * \retval      none
 */
void ahb_clk_enable(uint8_t dev)
{
	if (dev > AHBCLKEN_BIT_SDIO) {
		return;
	}

	sysconf_reg_ptr->AHBCLKEN |= (1 << dev);
}

/**
 * \brief       disable the clk of ahb device
 *
 * \param[in]   dev ahb device number
 *
 * \retval      none
 */
void ahb_clk_disable(uint8_t dev)
{
	if (dev > AHBCLKEN_BIT_SDIO) {
		return;
	}

	sysconf_reg_ptr->AHBCLKEN &= (~(1 << dev));
}

void apb_clk_divisor(uint8_t div)
{
	sysconf_reg_ptr->APBCLKDIV = div;
}

void apb_clk_enable(uint8_t dev)
{
	if (dev > APBCLKEN_BIT_I3C) {
		return;
	}

	sysconf_reg_ptr->APBCLKEN |= (1 << dev);
}

void apb_clk_disable(uint8_t dev)
{
	if (dev > APBCLKEN_BIT_I3C) {
		return;
	}

	sysconf_reg_ptr->APBCLKEN &= (~(1 << dev));
}

/**
 * \brief       configure the sdio clk divisor
 * 		sdio is in ahb bus
 *
 * \param[in]   div divisor
 *
 * \retval      none
 */
void sdio_clk_divisor(uint8_t div)
{
	sysconf_reg_ptr->SDIO_REFCLK_DIV;
}


/**
 * \brief       configure the spi master's clk divisor
 *
 * \param[in]   id  spi master id
 * \param[in]   div divisor
 *
 * \retval      none
 */
void spi_master_clk_divisor(uint8_t id, uint8_t div)
{
	if (id == SPI_MASTER_0) {
		sysconf_reg_ptr->SPI_MST_CLKDIV =
			(sysconf_reg_ptr->SPI_MST_CLKDIV & 0xffffff00) | div;
	} else if (id == SPI_MASTER_1) {
		sysconf_reg_ptr->SPI_MST_CLKDIV =
			(sysconf_reg_ptr->SPI_MST_CLKDIV & 0xffff00ff) | (div << 8);
	} else if (id == SPI_MASTER_2) {
		sysconf_reg_ptr->SPI_MST_CLKDIV =
			(sysconf_reg_ptr->SPI_MST_CLKDIV & 0xff00ffff) | (div << 16);
	}
}

/**
 * \brief     configure the debounce clk divisor of gpio8b
 *
 * \param[in]   bank bank number
 * \param[in]   div  debounce clk divisor
 *
 * \retval      none
 */
void gpio8b_dbclk_div(uint8_t bank, uint8_t div)
{
	if (bank == GPIO8B_BANK0) {
		sysconf_reg_ptr->GPIO8B_DBCLK_DIV =
			(sysconf_reg_ptr->GPIO8B_DBCLK_DIV & 0xffffff00) | div;
	} else if (bank == GPIO8B_BANK1) {
		sysconf_reg_ptr->GPIO8B_DBCLK_DIV =
		(sysconf_reg_ptr->GPIO8B_DBCLK_DIV & 0xffff00ff) | (div << 8);
	} else if (bank == GPIO8B_BANK2) {
		sysconf_reg_ptr->GPIO8B_DBCLK_DIV =
		(sysconf_reg_ptr->GPIO8B_DBCLK_DIV & 0xff00ffff) | (div << 16);
	} else if (bank == GPIO8B_BANK3) {
		sysconf_reg_ptr->GPIO8B_DBCLK_DIV =
		(sysconf_reg_ptr->GPIO8B_DBCLK_DIV & 0x00ffffff) | (div << 24);
	}
}

/**
 * \brief     configure the debounce clk divisor of gpio4b
 *
 * \param[in]   bank bank number
 * \param[in]   div  debounce clk divisor
 *
 * \retval      none
 */
void gpio4b_dbclk_div(uint8_t bank, uint8_t div)
{
	if (bank == GPIO4B_BANK0) {
		sysconf_reg_ptr->GPIO4B_DBCLK_DIV =
			(sysconf_reg_ptr->GPIO4B_DBCLK_DIV & 0xffffff00) | div;
	} else if (bank == GPIO4B_BANK1) {
		sysconf_reg_ptr->GPIO4B_DBCLK_DIV =
		(sysconf_reg_ptr->GPIO4B_DBCLK_DIV & 0xffff00ff) | (div << 8);
	} else if (bank == GPIO4B_BANK2) {
		sysconf_reg_ptr->GPIO4B_DBCLK_DIV =
		(sysconf_reg_ptr->GPIO4B_DBCLK_DIV & 0xff00ffff) | (div << 16);
	}
}

void i2s_tx_clk_div(uint8_t div)
{
	sysconf_reg_ptr->I2S_TX_SCLKDIV = div;
}

void i2s_rx_clk_div(uint8_t div)
{
	sysconf_reg_ptr->I2S_RX_SCLKDIV = div;
}

void i2s_rx_clk_sel(uint8_t sel)
{
	sysconf_reg_ptr->I2S_RX_SCLKSEL = sel;
}

void syscon_reset(void)
{
	sysconf_reg_ptr->RSTCON = 0x55AA6699;
}

uint32_t is_poweron_rst(void)
{
	if (sysconf_reg_ptr->RSTSTAT & SYS_RST_SOFTWARE_ON) {
		return 0;
	} else {
		return 1;
	}
}

void dvfs_clk_divisor(uint8_t level, uint8_t div)
{
	if (level == DVFS_PERF_LEVEL0) {
		sysconf_reg_ptr->DVFS_CLKDIV =
			(sysconf_reg_ptr->DVFS_CLKDIV & 0xffffff00) | div;
	} else if (level == DVFS_PERF_LEVEL1) {
		sysconf_reg_ptr->DVFS_CLKDIV =
			(sysconf_reg_ptr->DVFS_CLKDIV & 0xffff00ff) | (div << 8);
	} else if (level == DVFS_PERF_LEVEL2) {
		sysconf_reg_ptr->DVFS_CLKDIV =
			(sysconf_reg_ptr->DVFS_CLKDIV & 0xff00ffff) | (div << 16);
	} else if (level == DVFS_PERF_LEVEL3) {
		sysconf_reg_ptr->DVFS_CLKDIV =
			(sysconf_reg_ptr->DVFS_CLKDIV & 0x00ffffff) | (div << 24);
	}
}

void dvfs_vdd_config(uint8_t level, uint8_t val)
{
	val &= 0xf;

	if (level == DVFS_PERF_LEVEL0) {
		sysconf_reg_ptr->DVFS_VDDSET =
			(sysconf_reg_ptr->DVFS_VDDSET & 0xfffffff0) | val;
	} else if (level == DVFS_PERF_LEVEL1) {
		sysconf_reg_ptr->DVFS_VDDSET =
			(sysconf_reg_ptr->DVFS_VDDSET & 0xffffff0f) | (val << 4);
	} else if (level == DVFS_PERF_LEVEL2) {
		sysconf_reg_ptr->DVFS_VDDSET =
			(sysconf_reg_ptr->DVFS_VDDSET & 0xfffff0ff) | (val << 8);
	} else if (level == DVFS_PERF_LEVEL3) {
		sysconf_reg_ptr->DVFS_CLKDIV =
			(sysconf_reg_ptr->DVFS_CLKDIV & 0xffff0fff) | (val << 12);
	}
}

void dvfs_vwtime_config(uint8_t time)
{
	sysconf_reg_ptr->DVFS_VWTIME = time;
}

void pmc_pwwtime_config(uint8_t time)
{
	sysconf_reg_ptr->PMC_PUWTIME= time;
}

void pmode_mux_config(uint8_t val)
{
	sysconf_reg_ptr->PMOD_MUX = val;
}

void uart3_clk_divisor(uint8_t div)
{
	sysconf_reg_ptr->UART3SCLK_DIV = div;
}

void arduino_pin_mux(uint8_t pin, uint8_t function)
{
	volatile uint32_t val;
	if (pin > ARDUINO_A5 || function > ARDUINO_FUNC_3RD) {
		return;
	}

	if (pin == ARDUINO_RESERVED || pin == ARDUINO_SPI_MASK ||
	   pin == ARDUINO_IIC_MASK) {
		return;
	}

	val = sysconf_reg_ptr->ARDUINO_MUX;

	if (pin == ARDUINO_D10 || pin == ARDUINO_D11) {
		if (function == ARDUINO_FUNC_2ND) {//SPI function
			val |= (1 << ARDUINO_SPI_MASK);
		} else {
			val &= (~(1 << ARDUINO_SPI_MASK));
		}
	} else if (pin == ARDUINO_A4 || pin == ARDUINO_A5) {
		if (function == ARDUINO_FUNC_2ND) {//IIC function
			val |= (1 << ARDUINO_IIC_MASK);
		} else {
			val &= (~(1 << ARDUINO_IIC_MASK));
		}
	}

	if (function == ARDUINO_FUNC_GPIO) {
		val &= (~(1 << pin));
	} else if (function == ARDUINO_FUNC_2ND || function == ARDUINO_FUNC_3RD) {
		val |= (1 << pin);
	}

	sysconf_reg_ptr->ARDUINO_MUX = val;
}

void reset_powerdown_vector(uint32_t addr)
{
	sysconf_reg_ptr->RESET_PD_VECTOR = addr;
}

void pwm_timer_pause(uint32_t id, uint32_t pause)
{
	uint32_t val = sysconf_reg_ptr->TIMER_PAUSE;

	if (id > PWM_TIMER5) {
		return;
	}

	if (pause) {
		val |= (1 << id);
	} else {
		val &= (~(1 << id));
	}

	sysconf_reg_ptr->TIMER_PAUSE = val;
}

void eflash_clk_div(uint8_t div)
{
	sysconf_reg_ptr->AHBCLKDIV |= (div << 8);
}

static bool ref_cpu_clk_by_var = 0;	// 0: refer to pre-define BOARD_DFSS_CORE_CLK, 1: ref_cpu_clk_hz
static uint32_t ref_cpu_clk_hz = 400000000; 

void set_ref_cpu_clk_from(bool define_or_var)
{
	ref_cpu_clk_by_var = define_or_var;
}

bool is_ref_cpu_clk_by_var()
{
	return ref_cpu_clk_by_var;
}

void set_ref_cpu_clk(uint32_t clk_hz)
{
	ref_cpu_clk_hz = clk_hz;
}

uint32_t get_ref_cpu_clk(void)
{
	return ref_cpu_clk_hz;
}
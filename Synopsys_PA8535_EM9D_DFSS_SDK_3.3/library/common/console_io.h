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

/**
 * \file
 * \brief  common io implementation
 */
#ifndef _CONSOLE_IO_H_
#define _CONSOLE_IO_H_
#include "embARC_toolchain.h"
#include "board.h"

typedef enum {
	CONSOLE_BAUDRATE_9600 = 0,
	CONSOLE_BAUDRATE_14400 = 1,
	CONSOLE_BAUDRATE_19200 = 2,
	CONSOLE_BAUDRATE_38400 = 3,
	CONSOLE_BAUDRATE_57600 = 4,
	CONSOLE_BAUDRATE_115200 = 5,
	CONSOLE_BAUDRATE_230400 = 6,
	CONSOLE_BAUDRATE_460800 = 7,
	CONSOLE_BAUDRATE_921600 = 8,
}CONSOLE_BAUDRATE_E;

#define CONSOLE_UART_ID		BOARD_CONSOLE_UART_ID	/*!< console uart id */

#ifdef ENABLE_UART_BLOCKING_TASK
#undef BOARD_CONSOLE_UART_BAUD
#define BOARD_CONSOLE_UART_BAUD UART_BAUDRATE_9600
#endif


#ifdef __cplusplus
extern "C" {
#endif

extern int console_putchar(unsigned char chr);
extern int console_putstr(const char *str, unsigned int len);
extern int console_getchar(void);
extern int console_getchar_nonblock(void);
extern int console_getstr(char *str, unsigned int len);
extern void xprintf_setup(void);
extern void xprintf_desetup(void);
extern int xprintf_setup_br(CONSOLE_BAUDRATE_E baud_rate);
#ifdef __cplusplus
}
#endif

#endif /* _CONSOLE_IO_H_ */

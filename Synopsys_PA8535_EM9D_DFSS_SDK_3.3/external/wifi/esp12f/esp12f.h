/*
 * esp12f.h
 *
 *  Created on: 2018¦~9¤ë26¤é
 *      Author: 902452
 */

#ifndef DEVICE_PERIPHERAL_WIFI_ESP8266_ESP8266_H_
#define DEVICE_PERIPHERAL_WIFI_ESP8266_ESP8266_H_


/***********************************************
 * FEATURE SUPPORT FLAG
 **********************************************/
#define AT_CMD_SUPPORT_BASIC	1
#define AT_CMD_SUPPORT_WIFI		1
#define AT_CMD_SUPPORT_TCPIP	1


/***********************************************
 * CONSTANT DEFINITION
 **********************************************/
#define DFSS_UART_NUM		(2)	/*!< DFSS UART valid number */

#define DFSS_UART_0_ID		0	/*!< UART 0 ID macro */
#define DFSS_UART_1_ID		1	/*!< UART 1 ID macro */

#define ESP8266_DEFAULT_BAUD_RATE   115200
#define ESP8266_ALL_SOCKET_IDS 		-1

#define MAX_READ_CNT		20

/***********************************************
 * STRUNCTURE/EMULATOR DECLARATION
 **********************************************/
typedef enum AT_CMD_TYPE_S{
	AT_CMD_TYPE_TEST = 0,	// AT+CMD=?
	AT_CMD_TYPE_QUERY,		// AT+CMD?
	AT_CMD_TYPE_SETUP,		// AT+CMD=parameter1,parameter2,
	AT_CMD_TYPE_EXE,		// AT+CMD
	AT_CMD_TYPE_MAX
}AT_CMD_TYPE_T;



void hx_drv_esp_Initialize(void);
void hx_drv_esp_DeInitialize(void);
bool hx_drv_esp_SendATcmd(char* aCmd,  AT_CMD_TYPE_T aType, char* aParam);
void hx_drv_esp_ProMsg();
void hx_drv_esp_ProIPDMsg();

bool hx_drv_wifi_ATConnect(const char *type, int id, const char* addr, int port);
bool hx_drv_wifi_ATSend(char* aMsg);


#endif /* DEVICE_PERIPHERAL_WIFI_ESP8266_ESP8266_H_ */

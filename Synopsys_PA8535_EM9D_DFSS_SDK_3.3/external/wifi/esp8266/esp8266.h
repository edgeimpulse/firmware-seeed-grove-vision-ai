/* ------------------------------------------
 * Copyright (c) 2018, Synopsys, Inc. All rights reserved.

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

#ifndef _ESP8266_H_
#define _ESP8266_H_

#include "at_parser.h"
#include "board.h"


/** uart id which HM-10 BLE uses */
#if defined(BOARD_EMSK)
#define ESP8266_UART_ID		DW_UART_0_ID
#else
#if 1 //aaronlin: for wifi board
#define ESP8266_UART_ID		BOARD_WIFI_UART_ID
#else
#define ESP8266_UART_ID		DFSS_UART_1_ID
#endif
#endif

typedef enum{
	ESP8266_STA=1,
	ESP8266_AP,
	ESP8266_AP_STA
}ESP8266_WIFI_MODE;

typedef enum{
	ESP8266_NORMALSEND=0,
	ESP8266_PASSTHR
}ESP8266_TRANS_MODE;

typedef enum{
	ESP8266_RECV_ACTIVE=0,
	ESP8266_RECV_PASSIVE,
	ESP8266_RECV_MAX
}ESP8266_TCP_RECV_MODE;

typedef enum{
	ESP8266_MQTT_SCHM_TCP=1,
	ESP8266_MQTT_SCHM_TLS_NO_CERT,
	ESP8266_MQTT_SCHM_TLS_SERVER_CERT,
	ESP8266_MQTT_SCHM_TLS_CLIENT_CERT,
	ESP8266_MQTT_SCHM_TLS_SERVER_CLIENT_CERT,
	ESP8266_MQTT_SCHM_MAX
}ESP8266_MQTT_SCHEME;

typedef struct{
	AT_PARSER_DEF_PTR p_at;
	//add other members here if needed
	bool wifi_connected;
	ESP8266_TRANS_MODE trans_mode;
}ESP8266_DEF, *ESP8266_DEF_PTR;

#define ESP8266_DEFINE(NAME) \
	ESP8266_DEF __ ## NAME = { \
			.p_at = NULL, \
	}; \
	ESP8266_DEF_PTR NAME = &__ ## NAME

int32_t esp8266_init(ESP8266_DEF_PTR obj, uint32_t baudrate);
void esp8266_deinit(ESP8266_DEF_PTR obj);
int32_t esp8266_test(ESP8266_DEF_PTR obj);

int32_t esp8266_mac_get(ESP8266_DEF_PTR obj, char *mac_result);
int32_t esp8266_wifi_mode_get(ESP8266_DEF_PTR obj, bool flash);
int32_t esp8266_wifi_mode_set(ESP8266_DEF_PTR obj, ESP8266_WIFI_MODE, bool flash);
int32_t esp8266_wifi_scan(ESP8266_DEF_PTR obj, char * rcv_buf, uint32_t buf_size);
int32_t esp8266_wifi_connect(ESP8266_DEF_PTR obj, AT_STRING ssid, AT_STRING pwd, bool flash);
int32_t esp8266_wifi_disconnect(ESP8266_DEF_PTR obj);
int32_t esp8266_address_get(ESP8266_DEF_PTR obj,char *ip, char *mac);
int32_t esp8266_conn_status(ESP8266_DEF_PTR obj);
int32_t esp8266_multi_conn_status(ESP8266_DEF_PTR obj,uint32_t link_id);

int32_t esp8266_dns_lookup(ESP8266_DEF_PTR obj, char * domain_ip, AT_STRING domain_name);
int32_t esp8266_set_baudrate(ESP8266_DEF_PTR obj, uint32_t baudrate);
int32_t esp8266_tcp_multi(ESP8266_DEF_PTR obj, bool enable);
int32_t esp8266_tcp_recv_mode_set(ESP8266_DEF_PTR obj, ESP8266_TCP_RECV_MODE mode);
int32_t esp8266_tcp_passive_recv_get_len(ESP8266_DEF_PTR obj, int32_t *link_0_len, int32_t *link_1_len, int32_t *link_2_len, int32_t *link_3_len, int32_t *link_4_len);
uint32_t esp8266_tcp_multi_passive_read(ESP8266_DEF_PTR obj, uint32_t link_id, char *buf, int32_t buf_len, int32_t *p_read_len);
int32_t esp8266_tcp_multi_connect(ESP8266_DEF_PTR obj, uint32_t link_id, AT_STRING server_IP, uint32_t port);
int32_t esp8266_tcp_multi_disconnect(ESP8266_DEF_PTR obj, uint32_t link_id);
uint32_t esp8266_tcp_multi_write(ESP8266_DEF_PTR obj, uint32_t link_id, char *buf, uint32_t cnt);
int32_t esp8266_tcp_connect(ESP8266_DEF_PTR obj, AT_STRING server_IP, uint32_t port);
int32_t esp8266_tcp_server_open(ESP8266_DEF_PTR obj, uint32_t port);
int32_t esp8266_tcp_server_close(ESP8266_DEF_PTR obj, uint32_t port);

int32_t esp8266_transmission_mode(ESP8266_DEF_PTR obj, ESP8266_TRANS_MODE mode);
int32_t esp8266_passthr_start(ESP8266_DEF_PTR obj);
int32_t esp8266_passthr_end(ESP8266_DEF_PTR obj);
int32_t esp8266_passthr_write(ESP8266_DEF_PTR obj, char *buf, uint32_t cnt);
uint32_t esp8266_normal_write(ESP8266_DEF_PTR obj, char *buf, uint32_t cnt);
uint32_t esp8266_connect_write(ESP8266_DEF_PTR obj, char *buf, char* connect, uint32_t cnt);
int32_t esp8266_read(ESP8266_DEF_PTR obj, char *buf, uint32_t timeout);
uint32_t esp8266_nread(ESP8266_DEF_PTR obj, char *buf, uint32_t n);

int32_t esp8266_CIPCLOSE(ESP8266_DEF_PTR obj, char * conn_buf);

/////////////// MQTT AT ///////////////////
int32_t esp8266_mqtt_init();
int32_t esp8266_mqtt_deinit();
int32_t esp8266_mqtt_set_user_cfg(ESP8266_DEF_PTR obj, ESP8266_MQTT_SCHEME scheme, char *client_id, char *username, char *password);
int32_t esp8266_mqtt_conn(ESP8266_DEF_PTR obj, char *host, uint32_t port, bool reconnect);
int32_t esp8266_mqtt_publish(ESP8266_DEF_PTR obj, char *topic, char *data, uint8_t qos, bool retain);
int32_t esp8266_mqtt_publish_raw(ESP8266_DEF_PTR obj, char *topic, char *data, uint32_t data_len, uint8_t qos, bool retain);
int32_t esp8266_mqtt_subscribe(ESP8266_DEF_PTR obj, char *topic, uint8_t qos);
int32_t esp8266_mqtt_clean(ESP8266_DEF_PTR obj);

#endif
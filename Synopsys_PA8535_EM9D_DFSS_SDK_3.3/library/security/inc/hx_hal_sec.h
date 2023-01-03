#ifndef INCLUDE_HX_HAL_SEC_H
#define INCLUDE_HX_HAL_SEC_H

#include "hx_drv_basic_def.h"

typedef enum 
{
	CMD_TYPE_NOP,
	CMD_TYPE_CRYPTO,
	CMD_TYPE_ASYM_CRYPTO,
	CMD_TYPE_CRYPTO_AE,//for AES-GCM,AES-CCM,ARIA-CCM,ARIA-GCM,AEAD-ChaCha20-Poly1305
	CMD_TYPE_KEY_WRAP,
	CMD_TYPE_HASH,
	CMD_TYPE_MAC_UPDATE,
	CMD_TYPE_MAC_GENERATE,
	CMD_TYPE_MAC_VERIFY,
	CMD_TYPE_ASSET_SEARCH,
	CMD_TYPE_ASSET_CREATE,
	CMD_TYPE_ASSET_LOAD_IMPORT,
	CMD_TYPE_ASSET_LOAD_DERIVE,
	CMD_TYPE_ASSET_LOAD_PLAINTEXT,
	CMD_TYPE_ASSET_LOAD_RANDOM,
	CMD_TYPE_ASSET_LOAD_AESUNWRAP,
	CMD_TYPE_ASSET_PUBLIC_DATA_READ,
	CMD_TYPE_ASSET_DEL,
	CMD_TYPE_SIGN_VERIFY_NO_ASSET,
	CMD_TYPE_SIGN_WITH_ASSET,
	CMD_TYPE_VERIFY_WITH_ASSET,
	CMD_TYPE_GEN_PUBKEY,
	CMD_TYPE_GEN_KEYPAIR,
	CMD_TYPE_ECDHE_GEN_SHAREKEY,
	CMD_TYPE_OTP_READ,
	CMD_TYPE_OTP_WRITE,
	CMD_TYPE_OTP_WC_READ,
	CMD_TYPE_OTP_WC_WRITE,
	CMD_TYPE_OTP_MONOTONIC_READ,
	CMD_TYPE_OTP_MONOTONIC_INCR,
	CMD_TYPE_OTP_RANDOMHUK,
	CMD_TYPE_TRNG_CONFIG,
	CMD_TYPE_TRNG_RANDOM,
	CMD_TYPE_AUTH_UNLOCK_START,
	CMD_TYPE_AUTH_UNLOCK_VERIFY,
	CMD_TYPE_SECURE_DEBUG,
	CMD_TYPE_SYSTEM_RESET,
	CMD_TYPE_SYSTEM_INFOR,
}SEC_CMD_TYPE;

typedef enum 
{
	KEY_TYPE_HUK,
	KEY_TYPE_ProdComKey,	
}SEC_KEY_TYPE;

typedef struct
{
	uint8_t *input;
	uint32_t length;
	uint8_t *hmac;
}HMAC_PARA_t;

typedef struct
{
	uint32_t algorithm;
	uint32_t mode;	
	uint8_t *input;
	uint32_t length;
	uint8_t *aad;
	uint32_t aad_length;
	uint8_t *iv;
	uint32_t iv_length;
	bool f_encrypt;
	uint8_t *tag;
	uint8_t *output;
}CRYPTO_PARA_t;

SEC_ERROR_E himax_sec_nop(SEC_CMD_TYPE type, uint32_t param);
SEC_ERROR_E himax_sec_crypto(SEC_CMD_TYPE type, uint32_t param, uint8_t *output);
SEC_ERROR_E himax_sec_hash(SEC_CMD_TYPE type, uint32_t param, uint8_t *output);
SEC_ERROR_E himax_sec_mac(SEC_CMD_TYPE type, uint32_t param, uint8_t *output);
SEC_ERROR_E himax_sec_asset_manag(SEC_CMD_TYPE type, uint32_t param, uint32_t *output);
SEC_ERROR_E himax_sec_sign_verify(SEC_CMD_TYPE type, uint32_t param, uint32_t *state_asset_Id);
SEC_ERROR_E himax_sec_gen_keypair(SEC_CMD_TYPE type, uint32_t param);
SEC_ERROR_E himax_sec_otp(SEC_CMD_TYPE type, uint32_t param, uint32_t *len);
SEC_ERROR_E himax_sec_trng(SEC_CMD_TYPE type, uint32_t param);
SEC_ERROR_E himax_sec_secure_debug(SEC_CMD_TYPE type, uint32_t param, uint8_t *NonceData);
SEC_ERROR_E himax_sec_init(Hx_System_Info *system_info);
SEC_ERROR_E himax_sec_deinit(void);
void himax_sec_get_version(char *version);
SEC_ERROR_E himax_sec_read_public_data(SEC_ASSET_NUMBER index, uint8_t *output_data, uint32_t *length);								 
SEC_ERROR_E himax_sec_system(SEC_CMD_TYPE type, uint32_t param);
SEC_ERROR_E himax_sec_HMAC_key_from_otp(HMAC_PARA_t HMAC_para, SEC_KEY_TYPE key_type);
SEC_ERROR_E himax_sec_crypto_key_from_otp(CRYPTO_PARA_t CRYPTO_para, SEC_KEY_TYPE key_type);

#ifdef SEC_DRIVER_BOOT
SEC_BOOT_ERROR himax_sec_SB_image_process(
                                 SEC_FW_TYPE fw_type,
                                 bool header_export,
                                 uint8_t *Input_p,
                                 uint8_t *Output_p
                                 );
SEC_BOOT_ERROR himax_sec_SB_image_process_EX(
                                 bool header_export,
                                 uint8_t *Input_p,
                                 uint8_t *Output_p,
                                 uint32_t temp_header_addr
                                 );
#endif

#endif


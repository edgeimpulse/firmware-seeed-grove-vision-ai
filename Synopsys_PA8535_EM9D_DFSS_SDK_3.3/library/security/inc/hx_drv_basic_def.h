#ifndef INCLUDE_HX_DRV_BASIC_DEF_H
#define INCLUDE_HX_DRV_BASIC_DEF_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef BOARD_HIMAXANDES
#include "uart.h"
#define EIP130_REGISTEROFFSET_OTP_AHB_BASE		0x60008000
#ifdef HIMAX_SEC_DEBUG
#define HX_SEC_DBG_INFO HX_DBG_INFO
#else
#define HX_SEC_DBG_INFO(...) do{}while(0)
#endif
#define HX_SEC_get_ms() (gettimer()/1000)
#define HX_SEC_delay_ms himax_delay_ms
#elif defined BOARD_HIMAXEM9D
#include "embARC_debug.h"
#include "arc_timer.h"
#define EIP130_REGISTEROFFSET_OTP_AHB_BASE		0xB0038000
#ifdef HIMAX_SEC_DEBUG
#define HX_SEC_DBG_INFO EMBARC_PRINTF
#else
#define HX_SEC_DBG_INFO(...) do{}while(0)
#endif
#define HX_SEC_timer_start timer_start
#define HX_SEC_timer_read timer_current
#define HX_SEC_timer_stop timer_stop
#endif

#define EIP130_waiting_time 3000 //ms
#define TRNG_SAMPLECYCLES_1M 11
#define MAX_Mailbox_Number 4
#define SEC_ECC_CURVE_BITS 256 
#define SEC_ASYM_DATA_VHEADER       (4)
#define SEC_ECC_KEY_SIZE (32+SEC_ASYM_DATA_VHEADER)

/** - Converts a size in bits to a size in bytes aligned on a word boundary */
#define SEC_ASYM_DATA_SIZE_B2WB(x)  (4*((x+31)/32))
/** - The size of a HW asymmetric crypto element in bytes based on a bits size.*/
#define SEC_ASYM_DATA_SIZE_VWB(x)   (SEC_ASYM_DATA_VHEADER + SEC_ASYM_DATA_SIZE_B2WB(x))

#define SEC_ENCRYPT 1
#define SEC_DECRYPT 0
#define SEC_AES_WRAP 1
#define SEC_AES_UNWRAP 0

/** SEC Errors Type **/
typedef enum SEC_ERROR_S
{
	//SEC_ERROR_HX_INTERNAL = -1,
	SEC_NO_ERROR = 0,	/**< No ERROR */
	SEC_ERROR_INVALID_PARA,	
	SEC_ERROR_SIZE_NOT_ALIGN,
	SEC_ERROR_MAILBOX_IN_USE,
	SEC_ERROR_MAILBOX_HANDOVER,			
	SEC_ERROR_MAILBOX_LINK,			
	SEC_ERROR_MAILBOX_UNLINK,				
	SEC_ERROR_REPONSE_TIMEOUT,			
	SEC_ERROR_NOT_SUPPORT,		
	SEC_ERROR_INTERNAL,				
	SEC_ERROR_ECDSA_LOAD_CURVE,				
	SEC_ERROR_ECDSA_DEL_CURVE,
	SEC_ERROR_WC_OTP,
	SEC_ERROR_EIP130_NOT_READY,
	SEC_ERROR_NOT_INITIAL,
}SEC_ERROR_E;

typedef enum
{
	SEC_BOOT_VERIFY_SUCCESS = 0,	/**< No ERROR */
	SEC_BOOT_NEED_WRITE_FLASH,
	SEC_BOOT_SECURE_DISABLE,
	SEC_BOOT_ERROR_INVALID_PARA,
	SEC_BOOT_ERROR_PUBKEY_VERIFY,
	SEC_BOOT_ERROR_KEY_DERIVE,
	SEC_BOOT_ERROR_IMAGE_DECRYPT,
	SEC_BOOT_ERROR_IMAGE_VERIFY,
	SEC_BOOT_ERROR_IMAGE_REENCRYT,
	SEC_BOOT_ERROR_CERTI_VERIFY,
	SEC_BOOT_ERROR_ASSET_DEL,
	SEC_BOOT_ERROR_INTERNAL,
	SEC_BOOT_ERROR_NOT_INITIAL,
}SEC_BOOT_ERROR;

typedef enum
{
	SEC_ASSET_NUM_HUK=1,
	SEC_ASSET_NUM_PRODCOMKEY,
	SEC_ASSET_NUM_AUTHKEY,
	SEC_ASSET_NUM_PUBKEYHASH,
	SEC_ASSET_NUM_MONOTONIC_ODM,
	SEC_ASSET_NUM_ALGO_ID,
	SEC_ASSET_NUM_PROJECT_ID,
	SEC_ASSET_NUM_MONOTONIC_LOADER=32,
	SEC_ASSET_NUM_MONOTONIC_HIMAX=33,
}SEC_ASSET_NUMBER;

typedef enum
{
	SEC_FW_TYPE_LOADER=1,
	SEC_FW_TYPE_HIMAX,
	SEC_FW_TYPE_ODM,
	SEC_FW_TYPE_OTHERS,
	SEC_FW_TYPE_MAX,
}SEC_FW_TYPE;

typedef struct
{
    uint8_t * Data_p;                   // Data part
    uint32_t ByteDataSize;              // Data size in bytes
} SEC_DATA_INFO;

#define SB_NUM_ATTRIBUTES 8
#define SB_RSA_BYTES 256
#define SB_RSA_BITS (8*SB_RSA_BYTES)
#define SB_ENCRYPTIONKEY256_LEN ((256 / 32) + 2)
#define SB_ENCRYPTIONIV_LEN (128 / 32)
#define SB_ATTRIBUTE_TYPE_PROJECT_ID 0x80504944 /* Version field for project ID. */
#define SB_ATTRIBUTE_TYPE_FW_TYPE 0x80545950 /* Version field for fw type. */

typedef struct
{
    uint8_t signature[SB_RSA_BYTES];
}
SB_Signature_t;

typedef struct
{
    uint8_t pubkeyExp[4];
    uint8_t modulus[SB_RSA_BYTES];
}
SB_PublicKey_t;

typedef struct
{
    SB_PublicKey_t PublicKey;    /** Public key. */
    SB_Signature_t Signature;    /** Signature. */
    /* Notice: add padding to get the size which is multiple of 8 */
    uint8_t          Pad[4];
}
SB_Certificate_t;

/** Attribute data (incl. version id). */
typedef struct
{
    uint32_t ElementType;
    uint32_t ElementValue;
}
SB_AttributeElement_t;

typedef struct SB_Attributes
{
    /** Attribute data element. */
    SB_AttributeElement_t AttributeElements[SB_NUM_ATTRIBUTES];
}
SB_Attributes_t;

/**
    Signing header for the images.
 */
typedef struct
{
    uint32_t               Type;                /** Type. */
    uint32_t               PubKeyType;          /** Type of public key */
    SB_Signature_t       Signature;           /** Signature. */
    SB_PublicKey_t       PublicKey;           /** Public key (if included in image). */
    uint32_t               EncryptionKey[SB_ENCRYPTIONKEY256_LEN]; /** Key. */
    uint32_t               EncryptionIV[SB_ENCRYPTIONIV_LEN]; /** IV. */
    uint32_t               ImageLen;            /** Image length. */
    SB_Attributes_t      ImageAttributes;     /** Image attributes. */
    uint32_t               CertificateCount;    /** Certificate count. */
} SB_Header_t;

typedef enum
{
    SEC_CIPHER_ALGO_AES = 0,
    SEC_CIPHER_ALGO_DES,
    SEC_CIPHER_ALGO_3DES,
    SEC_CIPHER_ALGO_CHACHA20 = 7,
    SEC_CIPHER_ALGO_SM4,
    SEC_CIPHER_ALGO_ARIA,
} SEC_CIPHER_ALGO;

typedef enum
{
    SEC_CIPHER_MODE_ECB = 0,
    SEC_CIPHER_MODE_CBC,
    SEC_CIPHER_MODE_CTR,
    SEC_CIPHER_MODE_ICM,
    SEC_CIPHER_MODE_F8,
    SEC_CIPHER_MODE_CCM,
    SEC_CIPHER_MODE_XTS,
    SEC_CIPHER_MODE_GCM,
    SEC_CIPHER_MODE_CHACHA20_ENC = 0,
    SEC_CIPHER_MODE_CHACHA20_AEAD,
} SEC_CIPHER_MODE;

typedef enum
{
    SEC_ALGO_HASH_SHA1 = 1,
    SEC_ALGO_HASH_SHA224,
    SEC_ALGO_HASH_SHA256,
    SEC_ALGO_HASH_SHA384,
    SEC_ALGO_HASH_SHA512,
} SEC_HASH_ALGO;

typedef enum
{
    SEC_ALGO_MAC_HMAC_SHA1 = 1,
    SEC_ALGO_MAC_HMAC_SHA224,
    SEC_ALGO_MAC_HMAC_SHA256,
    SEC_ALGO_MAC_HMAC_SHA384,
    SEC_ALGO_MAC_HMAC_SHA512,
    SEC_ALGO_MAC_AES_CMAC = 8,
    SEC_ALGO_MAC_AES_CBC_MAC,
    SEC_ALGO_MAC_ARIA_CMAC,
    SEC_ALGO_MAC_ARIA_CBC_MAC,
    SEC_ALGO_MAC_POLY1305 = 14,
} SEC_HASH_MAC_ALGO;

typedef enum
{
    SEC_HASH_MAC_MODE_INIT2FINAL = 0,
    SEC_HASH_MAC_MODE_CONT2FINAL,
    SEC_HASH_MAC_MODE_INIT2CONT,
    SEC_HASH_MAC_MODE_CONT2CONT,
} SEC_HASH_MAC_MODE;

typedef enum
{
    SEC_PKASSET_ECDH_ECDSA_KEYCHK = 0x01,
    SEC_PKASSET_DH_DSA_KEYCHK,
    SEC_PKASSET_DSA_SIGN = 0x04,
    SEC_PKASSET_DSA_VERIFY,
    SEC_PKASSET_ECDSA_SIGN = 0x06,
    SEC_PKASSET_ECDSA_VERIFY,
    SEC_PKASSET_RSA_PKCS1V1_5_SIGN = 0x08,
    SEC_PKASSET_RSA_PKCS1V1_5_VERIFY,
    SEC_PKASSET_RSA_PKCS1V1_5_SIGN_CRT,
    SEC_PKASSET_RSA_PSS_SIGN = 0x0C,
    SEC_PKASSET_RSA_PSS_VERIFY,
    SEC_PKASSET_RSA_PSS_SIGN_CRT,
    SEC_PKASSET_DH_GEN_PUBKEY = 0x10,
    SEC_PKASSET_DH_GEN_KEYPAIR,
    SEC_PKASSET_DH_GEN_SHARED_SECRET_SKEYPAIR,
    SEC_PKASSET_DH_GEN_SHARED_SECRET_DKEYPAIR,
    SEC_PKASSET_ECDH_ECDSA_GEN_PUBKEY,
    SEC_PKASSET_ECDH_ECDSA_GEN_KEYPAIR,
    SEC_PKASSET_ECDH_GEN_SHARED_SECRET_SKEYPAIR,
    SEC_PKASSET_ECDH_GEN_SHARED_SECRET_DKEYPAIR,
    SEC_PKASSET_RSA_OAEP_WRAP_STRING = 0x18,
    SEC_PKASSET_RSA_OAEP_WRAP_HASH,
    SEC_PKASSET_RSA_OAEP_UNWRAP_STRING,
    SEC_PKASSET_RSA_OAEP_UNWRAP_HASH,
    SEC_PKASSET_RSA_PKCS1V15_UNWRAP = 0x21, 
    SEC_PKASSET_RSA_PKCS1V15_WRAP,    
    SEC_PKASSET_ECC_ELGAMAL_ENCRYPT = 0x24,
    SEC_PKASSET_ECC_ELGAMAL_DECRYPT,
    SEC_PKASSET_CURVE25519_GEN_PUBKEY = 0x28,
    SEC_PKASSET_CURVE25519_GEN_KEYPAIR,
    SEC_PKASSET_CURVE25519_GEN_SHARED_SECRET,
    SEC_PKASSET_EDDSA_GEN_PUBKEY,
    SEC_PKASSET_EDDSA_GEN_KEYPAIR,
    SEC_PKASSET_EDDSA_SIGN_INITIAL,
    SEC_PKASSET_EDDSA_SIGN_UPDATE,
    SEC_PKASSET_EDDSA_SIGN_FINAL,
    SEC_PKASSET_EDDSA_VERIFY_INITIAL,
    SEC_PKASSET_EDDSA_VERIFY_FINAL,
}SEC_PKASSET_MODE;

typedef enum
{
    SEC_PK_OP_NUMLOAD = 0x01,
    SEC_PK_OP_NUMSETN = 0x03,
    SEC_PK_OP_MODEXPE = 0x04,
    SEC_PK_OP_MODEXPD,
    SEC_PK_OP_MODEXPCRT,
    SEC_PK_OP_ECMONTMUL = 0x0A,
    SEC_PK_OP_ECCMUL,
    SEC_PK_OP_ECCADD,
    SEC_PK_OP_DSASIGN,
    SEC_PK_OP_DSAVERIFY,
    SEC_PK_OP_ECDSASIGN,
    SEC_PK_OP_ECDSAVERIFY,
} SEC_PK_OP_MODE;

typedef enum
{
    SEC_ASSET_LIFETIME_INFINITE = 0,        /* Not used */
    SEC_ASSET_LIFETIME_SECONDS,
    SEC_ASSET_LIFETIME_MILLISECONDS,
    SEC_ASSET_LIFETIME_COUNTER,
} ValAssetLifetimeUse_t;

typedef enum otp_ahb_wc_partition
{
	OTP_AHB_PARTITION_SW_HW = 0,				
	OTP_AHB_PARTITION_MAGIC,
	OTP_AHB_PARTITION_COMMON,
	OTP_AHB_PARTITION_CHIP_ID,
}otp_ahb_wc_partition;

//OTP area base address: IS-B0, IS-B1, WC-B0, WH-B1, WC-COMMON
#define OTP_AHB_IS_B0_BASE (EIP130_REGISTEROFFSET_OTP_AHB_BASE) 
#define OTP_AHB_IS_B1_BASE (EIP130_REGISTEROFFSET_OTP_AHB_BASE + 0x100)
#define OTP_AHB_WC_B0_BASE (EIP130_REGISTEROFFSET_OTP_AHB_BASE + 0x200)
#define OTP_AHB_WC_B1_BASE (EIP130_REGISTEROFFSET_OTP_AHB_BASE + 0x200 + 20)
#define OTP_AHB_WC_COMMON_BASE (EIP130_REGISTEROFFSET_OTP_AHB_BASE + 0x200 + 40)
//OTP size in byte
#define OTP_SIZE_IN_BYTE 1024 //8k bits
//OTP WC partition offset
#define OTP_AHB_OFFSET_SW		0
#define OTP_AHB_OFFSET_HW		8
#define OTP_AHB_OFFSET_MAGIC	16
#define OTP_AHB_OFFSET_COMMON	40

//OTP WC SW define  bit offset
#define OTP_AHB_SW_SIGNATYRE_EN				0x00000001ULL
#define OTP_AHB_SW_LOADER_BLP_DIS			0x00000002ULL
#define OTP_AHB_SW_HIMAX_FW_BLP_DIS			0x00000004ULL
#define OTP_AHB_SW_CODE_PROTECT_EN			0x00000008ULL
#define OTP_AHB_SW_SB_EIP130_DIS			0x00000010ULL
#define OTP_AHB_SW_PRJ_ID_EN				0x00000020ULL

//OTP WC HW define  bit offset
#define OTP_AHB_HW_PIF_I2C_S_0x79_DIS	0x00000001ULL
#define OTP_AHB_HW_PIF_PMU_I2C_S_DIS	0x00000002ULL
#define OTP_AHB_HW_JTAG_DIS				0x00000004ULL
#define OTP_AHB_HW_SIF_SPI_M_DIS		0x00000008ULL
#define OTP_AHB_HW_PIF_SPI_M_DIS		0x00000010ULL
#define OTP_AHB_HW_PIF_SPI_S_DIS		0x00000020ULL
#define OTP_AHB_HW_SIF_I2C_M_DIS		0x00000040ULL
#define OTP_AHB_HW_PIF_I2C_M1_DIS		0x00000080ULL
#define OTP_AHB_HW_PIF_I2C_M2_DIS		0x00000100ULL
#define OTP_AHB_HW_PIF_I2C_S_DIS		0x00000200ULL
#define OTP_AHB_HW_UART_1_DIS			0x00000400ULL
#define OTP_AHB_HW_UART_2_DIS			0x00000800ULL
#define OTP_AHB_HW_OTP_OBF_EN			0x00001000ULL
#define OTP_AHB_HW_IS_AHB_RW_DIS		0x00002000ULL
#define OTP_AHB_HW_WC_B0_W_DIS			0x00004000ULL
#define OTP_AHB_HW_I2S_DIS				0x00008000ULL
#define OTP_AHB_HW_PDM_DIS				0x00010000ULL
#define OTP_AHB_HW_SGPIO_0_DIS			0x00020000ULL
#define OTP_AHB_HW_SGPIO_1_DIS			0x00040000ULL
#define OTP_AHB_HW_PGPIO_0_DIS			0x00080000ULL
#define OTP_AHB_HW_PGPIO_1_DIS			0x00100000ULL
#define OTP_AHB_HW_PGPIO_2_DIS			0x00200000ULL
#define OTP_AHB_HW_PGPIO_3_DIS			0x00400000ULL
#define OTP_AHB_HW_PGPIO_4_DIS			0x00800000ULL
#define OTP_AHB_HW_PGPIO_5_DIS			0x01000000ULL
#define OTP_AHB_HW_PGPIO_6_DIS			0x02000000ULL
#define OTP_AHB_HW_PGPIO_7_DIS			0x04000000ULL
#define OTP_AHB_HW_PGPIO_8_DIS			0x08000000ULL
#define OTP_AHB_HW_PGPIO_9_DIS			0x10000000ULL
#define OTP_AHB_HW_PGPIO_10_DIS			0x20000000ULL
#define OTP_AHB_HW_PGPIO_11_DIS			0x40000000ULL
#define OTP_AHB_HW_PGPIO_12_DIS			0x80000000ULL
#define OTP_AHB_HW_PGPIO_13_DIS			0x00000001ULL
#define OTP_AHB_HW_PGPIO_14_DIS			0x00000002ULL
#define OTP_AHB_HW_BOOT_OP_SCAN_DIS		0x00000004ULL
#define OTP_AHB_HW_BOOT_OP_MBIIST_DIS	0x00000008ULL
#define OTP_AHB_HW_BOOT_OP_IC_DBG_DIS	0x00000010ULL
#define OTP_AHB_HW_SIP_FLASH_PROG_DIS	0x00000020ULL
#define OTP_AHB_HW_SELF_TEST_EN			0x00000040ULL
#define OTP_AHB_HW_AESTX_BYPASS_DIS		0x00000080ULL
#define OTP_AHB_HW_ACCESS_AESTX_KEY_DIS	0x00000100ULL

/* ============ BIT_n ============ */

// using postfix "U" to be compatible with uint32
// ("UL" is not needed and gives lint warning)
#define BIT_0   0x00000001U
#define BIT_1   0x00000002U
#define BIT_2   0x00000004U
#define BIT_3   0x00000008U
#define BIT_4   0x00000010U
#define BIT_5   0x00000020U
#define BIT_6   0x00000040U
#define BIT_7   0x00000080U
#define BIT_8   0x00000100U
#define BIT_9   0x00000200U
#define BIT_10  0x00000400U
#define BIT_11  0x00000800U
#define BIT_12  0x00001000U
#define BIT_13  0x00002000U
#define BIT_14  0x00004000U
#define BIT_15  0x00008000U
#define BIT_16  0x00010000U
#define BIT_17  0x00020000U
#define BIT_18  0x00040000U
#define BIT_19  0x00080000U
#define BIT_20  0x00100000U
#define BIT_21  0x00200000U
#define BIT_22  0x00400000U
#define BIT_23  0x00800000U
#define BIT_24  0x01000000U
#define BIT_25  0x02000000U
#define BIT_26  0x04000000U
#define BIT_27  0x08000000U
#define BIT_28  0x10000000U
#define BIT_29  0x20000000U
#define BIT_30  0x40000000U
#define BIT_31  0x80000000U

/* ============ MASK_n_BITS ============ */

#define MASK_1_BIT      (BIT_1 - 1)
#define MASK_2_BITS     (BIT_2 - 1)
#define MASK_3_BITS     (BIT_3 - 1)
#define MASK_4_BITS     (BIT_4 - 1)
#define MASK_5_BITS     (BIT_5 - 1)
#define MASK_6_BITS     (BIT_6 - 1)
#define MASK_7_BITS     (BIT_7 - 1)
#define MASK_8_BITS     (BIT_8 - 1)
#define MASK_9_BITS     (BIT_9 - 1)
#define MASK_10_BITS    (BIT_10 - 1)
#define MASK_11_BITS    (BIT_11 - 1)
#define MASK_12_BITS    (BIT_12 - 1)
#define MASK_13_BITS    (BIT_13 - 1)
#define MASK_14_BITS    (BIT_14 - 1)
#define MASK_15_BITS    (BIT_15 - 1)
#define MASK_16_BITS    (BIT_16 - 1)
#define MASK_17_BITS    (BIT_17 - 1)
#define MASK_18_BITS    (BIT_18 - 1)
#define MASK_19_BITS    (BIT_19 - 1)
#define MASK_20_BITS    (BIT_20 - 1)
#define MASK_21_BITS    (BIT_21 - 1)
#define MASK_22_BITS    (BIT_22 - 1)
#define MASK_23_BITS    (BIT_23 - 1)
#define MASK_24_BITS    (BIT_24 - 1)
#define MASK_25_BITS    (BIT_25 - 1)
#define MASK_26_BITS    (BIT_26 - 1)
#define MASK_27_BITS    (BIT_27 - 1)
#define MASK_28_BITS    (BIT_28 - 1)
#define MASK_29_BITS    (BIT_29 - 1)
#define MASK_30_BITS    (BIT_30 - 1)
#define MASK_31_BITS    (BIT_31 - 1)

/** Asset policies related to hash/HMAC and CMAC algorithms */
#define SEC_POLICY_SHA1                       0x0000000000000001ULL
#define SEC_POLICY_SHA224                     0x0000000000000002ULL
#define SEC_POLICY_SHA256                     0x0000000000000004ULL
#define SEC_POLICY_SHA384                     0x0000000000000008ULL
#define SEC_POLICY_SHA512                     0x0000000000000010ULL
#define SEC_POLICY_CMAC                       0x0000000000000020ULL
#define SEC_POLICY_POLY1305                   0x0000000000000040ULL

/** Asset policies related to symmetric cipher algorithms */
#define SEC_POLICY_ALGO_CIPHER_MASK           0x0000000000000300ULL
#define SEC_POLICY_ALGO_CIPHER_AES            0x0000000000000100ULL
#define SEC_POLICY_ALGO_CIPHER_TRIPLE_DES     0x0000000000000200ULL
#define SEC_POLICY_ALGO_CIPHER_CHACHA20       0x0000000000002000ULL
#define SEC_POLICY_ALGO_CIPHER_SM4            0x0000000000004000ULL
#define SEC_POLICY_ALGO_CIPHER_ARIA           0x0000000000008000ULL

/** Asset policies related to symmetric cipher modes */
#define SEC_POLICY_MODE1                      0x0000000000010000ULL
#define SEC_POLICY_MODE2                      0x0000000000020000ULL
#define SEC_POLICY_MODE3                      0x0000000000040000ULL
#define SEC_POLICY_MODE4                      0x0000000000080000ULL
#define SEC_POLICY_MODE5                      0x0000000000100000ULL
#define SEC_POLICY_MODE6                      0x0000000000200000ULL
#define SEC_POLICY_MODE7                      0x0000000000400000ULL
#define SEC_POLICY_MODE8                      0x0000000000800000ULL
#define SEC_POLICY_MODE9                      0x0000000001000000ULL
#define SEC_POLICY_MODE10                     0x0000000002000000ULL

/** Asset policies specialized per symmetric cipher algorithm */
#define SEC_POLICY_AES_MODE_ECB               (SEC_POLICY_ALGO_CIPHER_AES|SEC_POLICY_MODE1)
#define SEC_POLICY_AES_MODE_CBC               (SEC_POLICY_ALGO_CIPHER_AES|SEC_POLICY_MODE2)
#define SEC_POLICY_AES_MODE_CTR               (SEC_POLICY_ALGO_CIPHER_AES|SEC_POLICY_MODE4)
#define SEC_POLICY_AES_MODE_CTR32             (SEC_POLICY_ALGO_CIPHER_AES|SEC_POLICY_MODE4)
#define SEC_POLICY_AES_MODE_ICM               (SEC_POLICY_ALGO_CIPHER_AES|SEC_POLICY_MODE5)
#define SEC_POLICY_AES_MODE_CCM               (SEC_POLICY_ALGO_CIPHER_AES|SEC_POLICY_MODE7|SEC_POLICY_CMAC)
#define SEC_POLICY_AES_MODE_F8                (SEC_POLICY_ALGO_CIPHER_AES|SEC_POLICY_MODE8)
#define SEC_POLICY_AES_MODE_XTS               (SEC_POLICY_ALGO_CIPHER_AES|SEC_POLICY_MODE9)
#define SEC_POLICY_AES_MODE_GCM               (SEC_POLICY_ALGO_CIPHER_AES|SEC_POLICY_MODE10)

#define SEC_POLICY_3DES_MODE_ECB              (SEC_POLICY_ALGO_CIPHER_TRIPLE_DES|SEC_POLICY_MODE1)
#define SEC_POLICY_3DES_MODE_CBC              (SEC_POLICY_ALGO_CIPHER_TRIPLE_DES|SEC_POLICY_MODE2)

#define SEC_POLICY_CHACHA20_ENCRYPT           (SEC_POLICY_ALGO_CIPHER_CHACHA20)
#define SEC_POLICY_CHACHA20_AEAD              (SEC_POLICY_ALGO_CIPHER_CHACHA20|SEC_POLICY_POLY1305)

#define SEC_POLICY_SM4_MODE_ECB               (SEC_POLICY_ALGO_CIPHER_SM4|SEC_POLICY_MODE1)
#define SEC_POLICY_SM4_MODE_CBC               (SEC_POLICY_ALGO_CIPHER_SM4|SEC_POLICY_MODE2)
#define SEC_POLICY_SM4_MODE_CTR               (SEC_POLICY_ALGO_CIPHER_SM4|SEC_POLICY_MODE4)

#define SEC_POLICY_ARIA_MODE_ECB              (SEC_POLICY_ALGO_CIPHER_ARIA|SEC_POLICY_MODE1)
#define SEC_POLICY_ARIA_MODE_CBC              (SEC_POLICY_ALGO_CIPHER_ARIA|SEC_POLICY_MODE2)
#define SEC_POLICY_ARIA_MODE_CTR              (SEC_POLICY_ALGO_CIPHER_ARIA|SEC_POLICY_MODE4)
#define SEC_POLICY_ARIA_MODE_CTR32            (SEC_POLICY_ALGO_CIPHER_ARIA|SEC_POLICY_MODE4)
#define SEC_POLICY_ARIA_MODE_ICM              (SEC_POLICY_ALGO_CIPHER_ARIA|SEC_POLICY_MODE5)
#define SEC_POLICY_ARIA_MODE_CCM              (SEC_POLICY_ALGO_CIPHER_ARIA|SEC_POLICY_MODE7|SEC_POLICY_CMAC)
#define SEC_POLICY_ARIA_MODE_GCM              (SEC_POLICY_ALGO_CIPHER_ARIA|SEC_POLICY_MODE10)

/** Asset policies related to Algorithm/cipher/MAC operations */
#define SEC_POLICY_MAC_GENERATE               0x0000000004000000ULL
#define SEC_POLICY_MAC_VERIFY                 0x0000000008000000ULL
#define SEC_POLICY_ENCRYPT                    0x0000000010000000ULL
#define SEC_POLICY_DECRYPT                    0x0000000020000000ULL

/** Asset policy related to coprocessor */
#define SEC_POLICY_CPIF                  0x0000000040000000ULL

/** Asset policies related to temporary values
 *  Note that the SEC_POLICY_TEMP_MAC should be used for intermediate
 *  hash digest as well. */
#define SEC_POLICY_TEMP_IV                    0x0001000000000000ULL
#define SEC_POLICY_TEMP_COUNTER               0x0002000000000000ULL
#define SEC_POLICY_TEMP_MAC                   0x0004000000000000ULL
#define SEC_POLICY_TEMP_AUTH_STATE            0x0010000000000000ULL

/** Asset policy related to monotonic counter */
#define SEC_POLICY_MONOTONIC                  0x0000000100000000ULL

/** Asset policies related to key derive functionality */
#define SEC_POLICY_TRUSTED_ROOT_KEY           0x0000000200000000ULL
#define SEC_POLICY_TRUSTED_KEY_DERIVE         0x0000000400000000ULL
#define SEC_POLICY_KEY_DERIVE                 0x0000000800000000ULL

/** Asset policies related to AES key wrap functionality\n
 *  Note: Must be combined with operations bits */
#define SEC_POLICY_TRUSTED_WRAP               0x0000001000000000ULL
#define SEC_POLICY_AES_WRAP                   0x0000002000000000ULL

/** Asset policies related to PK operations */
#define SEC_POLICY_PUBLIC_KEY                 0x0000000080000000ULL
#define SEC_POLICY_PK_RSA_OAEP_WRAP           0x0000004000000000ULL
#define SEC_POLICY_PK_RSA_PKCS1_WRAP          0x0000010000000000ULL	
#define SEC_POLICY_PK_RSA_PKCS1_SIGN          0x0000020000000000ULL
#define SEC_POLICY_PK_RSA_PSS_SIGN            0x0000040000000000ULL
#define SEC_POLICY_PK_DSA_SIGN                0x0000080000000000ULL
#define SEC_POLICY_PK_ECC_ECDSA_SIGN          0x0000100000000000ULL
#define SEC_POLICY_PK_DH_KEY                  0x0000200000000000ULL
#define SEC_POLICY_PK_ECDH_KEY                0x0000400000000000ULL
#define SEC_POLICY_PUBLIC_KEY_PARAM           0x0000800000000000ULL

#define SEC_POLICY_PK_ECC_ELGAMAL_ENC         (SEC_POLICY_PK_ECC_ECDSA_SIGN|SEC_POLICY_PK_ECDH_KEY)

/** Asset policies related to Authentication */
#define SEC_POLICY_EMMC_AUTH_KEY              0x0400000000000000ULL
#define SEC_POLICY_AUTH_KEY                   0x8000000000000000ULL

/** Asset policies related to the domain */
#define SEC_POLICY_SOURCE_NON_SECURE          0x0100000000000000ULL
#define SEC_POLICY_CROSS_DOMAIN               0x0200000000000000ULL

/** Asset policies related to general purpose data that can or must be used
 *  in an operation */
#define SEC_POLICY_PRIVATE_DATA               0x0800000000000000ULL
#define SEC_POLICY_PUBLIC_DATA                0x1000000000000000ULL

/** Asset policies related to export functionality */
#define SEC_POLICY_EXPORT                     0x2000000000000000ULL
#define SEC_POLICY_TRUSTED_EXPORT             0x4000000000000000ULL

typedef struct
{
	const uint8_t * In_p;
	uint8_t * Out_p;
	uint32_t Size;
} Nop;

typedef struct
{
	const uint8_t * SrcData_p;
	uint8_t * DstData_p;
	uint32_t Algorithm;			// reference SEC_CIPHER_ALGO
	uint32_t Mode;				// reference SEC_CIPHER_MODE
	uint32_t TempAssetId;		// IV from asset
	uint32_t KeyAssetId;		// 0 -> from token, others -> from asset
	uint32_t DataSize;
	uint32_t KeySize;			// key length in bytes
	uint8_t Key[64];            // AES-XTS requires 512bit (2 * 256bit)
	uint8_t IV[16];				//IV from token
	uint8_t Parameter[16];      // System parameter
	uint8_t f8_IV[16];          // IV for AES f8 mode
	uint8_t f8_SaltKey[16];     // Salt key for AES f8 mode
	uint8_t f8_SaltKeySize;     // Salt key size for AES f8 mode
	uint8_t NonceLength;        // Nonce length for ChaCha20
	uint8_t fEncrypt;			// 0->decrypt, 1->encrypt
	uint8_t fParameter;         // Write system parameter
} Cipher;

/*
for AES-GCM,AES-CCM,ARIA-CCM,ARIA-GCM,AEAD-ChaCha20-Poly1305
*/
typedef struct
{
	const uint8_t * AAD_p;
	const uint8_t * SrcData_p;
	uint8_t * DstData_p;
	uint32_t Algorithm;
	uint32_t Mode;
	uint32_t KeyAssetId;
	uint32_t AADSize;
	uint32_t input_DataSize;
	uint32_t real_DataSize; 
	uint32_t KeySize;
	uint8_t Key[32];
	uint8_t NonceHashKey[16];
	uint8_t IV[16];
	uint8_t Tag[16];
	uint8_t fEncrypt;
	uint8_t NonceHashKeySize;  // Actual Nonce/HashKey size
	uint8_t GCMMode; 		  // GCMMode
	uint8_t TagSize; 		  // Tag size
} CipherAE;

typedef struct
{
	const uint8_t * SrcData_p;
	uint8_t * DstData_p;
	uint32_t KeyAssetId;
	uint32_t SrcDataSize;
	uint32_t DstDataSize;
	uint32_t KeySize;
	uint8_t Key[32];
	uint8_t fWrap;
} KeyWrap;

typedef struct
{
	const uint8_t * Data_p;
	uint64_t TotalMessageLength;
	uint32_t Algorithm;
	uint32_t Mode;
	uint32_t DataSize;
	uint32_t TempAssetId;
	uint8_t Digest[64];
} Hash;

typedef struct
{
	const uint8_t * Data_p;
	uint64_t TotalMessageLength;
	uint32_t Algorithm;
	uint32_t Mode;
	uint32_t TempAssetId;
	uint32_t KeyAssetId;
	uint32_t MacAssetId;
	uint32_t DataSize;
	uint32_t KeySize;
	uint32_t MacSize;
	uint8_t Key[128];
	uint8_t Mac[64];
	uint8_t TempMac[64];
} Mac;

typedef struct
{
	uint64_t Policy;
	uint32_t Size;
	uint32_t Lifetime;
	uint8_t LifetimeUse;
	uint8_t fLifetimeRelative;
	uint8_t fLifetimeNoLoad;
} AssetCreate;

typedef struct
{
	const uint8_t * KeyBlob_p;
	uint32_t AssetId;
	uint32_t KekAssetId;
	uint32_t KeyBlobSize;
	uint32_t AssociatedDataSize;
	uint8_t AssociatedData[224];
} AssetLoadImport;

typedef struct
{
	const uint8_t * Salt_p;
	const uint8_t * IV_p;
	uint32_t AssetId;
	uint32_t KdkAssetId;
	uint32_t AssociatedDataSize;// must larger than 53 bytes
	uint32_t SaltSize;
	uint32_t IVSize;
	uint8_t AssociatedData[224];
	uint8_t fCounter;
	uint8_t fRFC5869;
} AssetLoadDerive;

typedef struct
{
	const uint8_t * Data_p;
	uint8_t * KeyBlob_p;
	uint32_t AssetId;
	uint32_t KekAssetId; //load key from other asset
	uint32_t DataSize;
	uint32_t AssociatedDataSize;
	uint32_t KeyBlobSize;
	uint8_t AssociatedData[224];
} AssetLoadPlaintext;

typedef struct
{
	uint8_t * KeyBlob_p;
	uint32_t AssetId;
	uint32_t KekAssetId;
	uint32_t AssociatedDataSize;
	uint32_t KeyBlobSize;
	uint8_t AssociatedData[224];
} AssetLoadRandom;

typedef struct
{
	const uint8_t * KeyBlob_p;
	uint32_t AssetId;
	uint32_t KekAssetId;
	uint32_t KeyBlobSize;
} AssetLoadAesunwrap;

typedef struct
{
	uint32_t Method;
	const uint8_t * HashData_p;	//input address
	uint8_t * Sign_p;			//output address
	uint64_t TotalMessageSize;
	uint32_t ModulusSizeInBits;
	uint32_t KeyAssetId;		//private key asset for sign,public key asset for verify
	//uint32_t DomainAssetId;		//domain asset
	uint32_t DigestAssetId;
	uint32_t HashDataSize;		//input data size
	uint32_t SaltSize;          // RSA-PSS only
	uint32_t SignSize;			//output data size
} PkAssetSignVerify;

typedef struct
{
	uint32_t Method;
	const  uint8_t * SrcData_p;
	const uint8_t * DstData_p;
	uint32_t ModulusSizeInBits;
	uint32_t KeyAssetId;
	uint32_t DomainAssetId;
	uint32_t SrcDataSize;
	uint32_t DstDataSize;
} PkAssetEncrypt;

typedef struct
{
	uint32_t Method;
	const uint8_t * KeyBlob_p;
	uint8_t * PubKey_p;
	//uint32_t ModulusSizeInBits;
	//uint32_t DivisorSizeInBits;
	uint32_t PubKeyAssetId;
	uint32_t PrivKeyAssetId;
	//uint32_t DomainAssetId;
	uint32_t KekAssetId;
	uint32_t AssociatedDataSize;
	uint32_t KeyBlobSize;
	uint32_t PubKeySize;
	uint8_t AssociatedData[224];
} PkAssetGenKey;

typedef struct
{
	uint32_t Method;
	uint32_t ModulusSizeInBits;
	uint32_t DivisorSizeInBits;
	uint32_t PubKeyAssetId;
	uint32_t PrivKeyAssetId;
	uint32_t DomainAssetId;
} PkAssetKeyCheck;

typedef struct
{
	uint32_t Method;
	const uint8_t * OtherInfo_p;
	const uint32_t * AssetIdList_p;
	uint32_t ModulusSizeInBits;
	uint32_t DivisorSizeInBits;
	uint32_t PubKeyAssetId;
	uint32_t PrivKeyAssetId;
	uint32_t DomainAssetId;
	uint32_t PubKey2AssetId;
	uint32_t PrivKey2AssetId;
	uint32_t OtherInfoSize;
	uint32_t AssetIdListSize;
	uint8_t fSaveSharedSecret;
} PkAssetGenSharedSecret;

typedef struct
{
	uint32_t Method;
	const uint8_t * Data_p;
	uint32_t ModulusSizeInBits;
	uint32_t KeyAssetId;
	uint32_t AssetId;
	uint32_t DataSize;
	uint32_t AdditionalInputSize;
	uint8_t AdditionalInput[208];
} PkAssetWrap;

typedef struct
{
	const uint8_t * InData_p;
	const uint8_t * OutData_p;
	uint32_t Operation;
	uint32_t PublicExponent;
	uint32_t InDataSize;
	uint32_t OutDataSize;
	uint8_t Nwords;
	uint8_t Mwords;
	uint8_t Mmask;
	uint8_t Index;
} PkOperation;

typedef struct
{
	const uint8_t * KeyBlob_p;
	uint32_t KeyBlobSize;
	uint32_t AssociatedDataSize;
	uint16_t AssetNumber;
	uint16_t PolicyNumber;
	uint8_t AssociatedData[224];
	bool fAddCRC;
} OTPDataWrite;

typedef struct
{
	const uint8_t * Data_p;
	uint32_t AssetId;
	uint32_t DataSize;
} PublicData;

typedef struct
{
	otp_ahb_wc_partition otp_partition;
	uint32_t offset;
	uint32_t *Data_p;
} otp_wc_read;

typedef struct
{
	otp_ahb_wc_partition otp_partition;
	uint32_t offset;
	uint32_t otp_ctl_bit;
} otp_wc_write;

typedef struct
{
	const uint8_t * Data_p;
	uint32_t AssetId;
	uint32_t DataSize;
} MonotonicCounter;

typedef struct
{
	const uint8_t * KeyBlob_p;
	uint32_t Identity; //COID
	uint32_t KeyBlobSize;
	uint32_t AssociatedDataSize;
	uint16_t AssetNumber;
	uint16_t SampleCycles;
	uint8_t AssociatedData[224];
	uint8_t NoiseBlocks;
	uint8_t SampleDiv;
	uint8_t AutoSeed;
	uint8_t f128bit;
	uint8_t fAddCRC;
} ProvisionRandomHUK;

typedef struct
{
	uint16_t FroBlockKey;
	uint16_t SampleCycles;
	uint8_t SampleDiv;
	uint8_t NoiseBlocks;
	uint8_t AutoSeed;
	uint8_t fLoadStart;
	uint8_t fReseed;
} TrngConfig;

typedef struct
{
	uint8_t * Data_p;
	uint16_t Size;
} Random;

typedef struct
{
	const uint8_t * Sign_p;
	uint32_t AuthStateAssetId;
	uint32_t AuthKeyAssetId;
	uint32_t SignSize;
	uint8_t Nonce[16];
} AuthUnlock;

typedef struct
{
	uint32_t AuthStateAssetId;
	uint32_t fSet;
} SecureDebug;

typedef struct
{
	uint32_t AssetId;
	uint32_t Size;
} Result_AssetSearch;

typedef struct
{
    struct
    {
        uint8_t Major, Minor, Patch;    // 0..9 each
        uint16_t MemorySizeInBytes;
    } Hardware;

    struct
    {
        uint8_t Major, Minor, Patch;    // 0..9 each
        bool fIsTestFW;
    } Firmware;

    struct
    {
        uint8_t HostID;
        uint32_t Identity;
    } SelfIdentity;

    struct
    {
        uint8_t ErrorCode;
        uint16_t ErrorLocation;
    } OTP;

} Eip130Token_SystemInfo_t;

typedef struct
{
	uint32_t cpu_clk; //cpu frequency
	uint32_t sec_system_mem; //memory address for secure driver internal use
} Hx_System_Info;

static inline uint32_t SB_Load_BE32(const void * const Value_p)
{
    const uint8_t * const p = (const uint8_t *)Value_p;

    return (p[0] << 24 | p[1] << 16 | p[2] << 8  | p[3]);
}

#endif


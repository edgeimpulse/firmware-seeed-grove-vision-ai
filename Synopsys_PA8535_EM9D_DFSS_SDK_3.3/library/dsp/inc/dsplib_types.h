/*
//
//CONFIDENTIAL AND PROPRIETARY INFORMATION
//
//Copyright (c) 2015 Synopsys, Inc. All rights reserved.
//This software and documentation contain confidential and
//proprietary information that is the property of
//Synopsys, Inc. The software and documentation are
//furnished under a license agreement and may be used
//or copied only in accordance with the terms of the license
//agreement. No part of the software and documentation
//may be reproduced, transmitted, or translated, in any
//form or by any means, electronic, mechanical, manual,
//optical, or otherwise, without prior written permission
//of Synopsys, Inc., or as expressly provided by the license agreement.
//Reverse engineering is prohibited, and reproduction,
//disclosure or use without specific written authorization
//of Synopsys Inc. is strictly forbidden.
//
//
*/

#ifndef _DSPLIB_TYPES
#define _DSPLIB_TYPES
#include <stdint.h>

// DSP library version
#define ARC_DSPLIB_MAJOR_VERSION (1)
#define ARC_DSPLIB_MINOR_VERSION (0)
#define ARC_DSPLIB_REVISION (1)

#if !defined(_ARC) && !defined(_Inline)
#define _Inline __inline
#endif

#if defined(_MSC_VER) && !defined(_ARCVER)
#define _ARCVER 0x21
#endif

// DSP Library HW architecture configuration
#if ((_ARCVER >= 0x21) && (_ARCVER <= 0x26))
#define _ARCVER_ARC600
#endif

#if ((_ARCVER >= 0x31) && (_ARCVER <= 0x35))
#define _ARCVER_ARC700
#endif

#if ((_ARCVER >= 0x40) && (_ARCVER < 0x50))
#define _ARCVER_ARCv2EM
#endif

#if ((_ARCVER >= 0x50) && (_ARCVER < 0x60))
#define _ARCVER_ARCv2HS
#endif

#if defined(_ARCVER_ARCv2HS) && defined(__Xdsp)
#define _ARCVER_ARCv2HS_DSP
#endif

#if (defined _ARCVER_ARC600) && defined __Xxy
#define _ARC600_XY
#endif

#if defined(_ARC600_XY) && defined(__Xea) && defined(__Xmul32x16) && defined(__Xxmac_d16)
#define _ARC_AS210
#endif

#if defined(_ARC600_XY) && defined(__Xea) && defined(__Xmul32x16)
#define _ARC_AS210_mac32
#endif

#if defined(_ARC600_XY) && defined(__Xea) && defined(__Xxmac_d16)
#define _ARC_AS210_mac16
#endif

#if defined(_ARC600_XY) && defined(__Xea)
#define _ARC_AS210_nomac
#endif

#if defined _ARCVER_ARCv2EM && defined __Xxy && defined __Xagu
#define _ARCv2EM_XY

#if   defined __Xagu_small
#define _ARCv2EM_XY_AGU_SMALL

#elif defined __Xagu_medium
#define _ARCv2EM_XY_AGU_SMALL
#define _ARCv2EM_XY_AGU_MEDIUM

#elif defined __Xagu_large
#define _ARCv2EM_XY_AGU_SMALL
#define _ARCv2EM_XY_AGU_MEDIUM
#define _ARCv2EM_XY_AGU_LARGE
#endif

#endif

#if defined _ARCv2EM_XY && core_config_dcache_present==1
#define _ARCv2EM_XY_11D
#endif

#if defined _ARCVER_ARCv2HS && defined __Xagu
#define _ARCVER_ARCv2HS_AGU
#endif

#ifdef _ARC600_XY
#ifndef XY_REGION_SIZE
#ifndef DSPRAM_BUILD
#define DSPRAM_BUILD    0x79
#endif
#define XY_REGION_SIZE ((int32_t)(1 << (((_lr(DSPRAM_BUILD)>>8) & 0xf) + 9)))
#endif
#endif

#ifndef I_CACHE_LINE_SIZE
#define I_CACHE_LINE_SIZE 128
#endif

//COMMON DEFINITIONS
#ifndef __FXAPI__
typedef int8_t  q7_t ;                                 /* fixed point < q.7  */
typedef int16_t q15_t;                                 /* fixed point < q.15 */
typedef int32_t q31_t;                                 /* fixed point < q.31 */
typedef int64_t q63_t;                                 /* fixed point < q.63 */
#else // purpose of this branch is to avoid intersections of type definitions when -Hfxapi is switched on.
#include "fxarc.h"
#endif

typedef float   f32_t;                                 /* floating point */

//DSP ERROR CODES
typedef enum
{
	DSP_ERR_OK = 0,                      /* No error */
	DSP_ERR_MAT_DIMENSIONS = -1,         /* Dimensions of matrices mismatch */
	DSP_ERR_SINGULAR = -2,               /* Matrix is singular*/
	DSP_ERR_NULL = -3,                   /* No-initialized instance is used */
	DSP_ERR_LENGTH_NOT_SUPPORTED = -4,
	DSP_ERR_LENGTH_TOO_BIG = -6,
	DSP_ERR_LENGTH_TOO_SMALL = -7,
	DSP_ERR_LENGTH_NOT_POWER2 = -8,
	DSP_ERR_LENGTH_NO_TABLE = -9,
	DSP_ERR_WRONG_ARGUMENT = -5
} dsp_status;

/* Fix for STAR: 9000961341- Replace enum types with int32 types in DSP library
   dsp_status is leaved as "enum" because it does not presenet as field of structures
   and it only used as return status value. */

typedef int32_t dsp_transform_scaling;
#define DSP_TRANSFORM_SCALING_UNSCALED 0   /* Scaling factor is 1 */
#define DSP_TRANSFORM_SCALING_SCALED 1     /* Scaling factor is 1/N */


typedef int32_t dsp_spectrum_format;
#define DSP_TRANSFORM_FULL_SPECTRUM 0                /* Requires N spectral samples (default) */
#define DSP_TRANSFORM_HALF_SPECTRUM 1                /* Requires N/2+1 spectral samples */
#define DSP_TRANSFORM_HALF_SPECTRUM_PACKED 2         /* Requires N/2 spectral samples */

#define MAX_TRANSFORM_ORDER 16

#define FRACT_BITS_Q31 31
#define FRACT_BITS_Q15 15
#define FRACT_BITS_Q7  7

#define M_PI 3.141592653589793
#define M_1_PI 0.318309886183791

#define M_2PI (2.0*M_PI)
#define M_1_2PI (M_1_PI/2.0)


#ifdef _MSC_VER
#pragma warning( disable : 4307 )
#endif

#define MAX_VAL(BITS) ((long long)((1ull<< (BITS)) - 1))     // BITS can be at range 1..62
#define MIN_VAL(BITS) (-MAX_VAL(BITS) - 1)     //

#define MAX_VAL_Q63 0x7fffffffffffffffll
#define MIN_VAL_Q63 0x8000000000000000ll

#define MAX_VAL_Q31 (q31_t)MAX_VAL(FRACT_BITS_Q31)
#define MIN_VAL_Q31 (q31_t)MIN_VAL(FRACT_BITS_Q31)

#define MAX_VAL_Q15 (q15_t)MAX_VAL(FRACT_BITS_Q15)
#define MIN_VAL_Q15 (q15_t)MIN_VAL(FRACT_BITS_Q15)

#define MAX_VAL_Q7  (q7_t)MAX_VAL(FRACT_BITS_Q7)
#define MIN_VAL_Q7  (q7_t)MIN_VAL(FRACT_BITS_Q7)

#if !defined __DSPLIB_FAST_MACROS && !defined __DSPLIB_DUMMY_MACROS
// this is the set of accurate macros for conversion to interger formats from float
#define PRE_CNVP(a, N, type) ((((a) * (double)(type)MAX_VAL(N)) + (a)) > (((double)(type)MAX_VAL(sizeof(type)*8-1))) ? (((double) (type)MAX_VAL(sizeof(type)*8-1))) : (((a) * (double)(type)MAX_VAL(N)) + (a)))
#define PRE_CNVN(a, N, type) ((((a) * (double)(type)MAX_VAL(N)) + (a)) < (((double)(type)MIN_VAL(sizeof(type)*8-1))) ? (((double) (type)MIN_VAL(sizeof(type)*8-1))) : (((a) * (double)(type)MAX_VAL(N)) + (a)))
#define FLT_2_INT(type, a, N) (type)(((a) < 0.0) ? (PRE_CNVN(a,N,type) - 0.5) : (PRE_CNVP(a,N,type) + 0.5))
#define dsp_q31_cast_rnd_f32(a) FLT_2_INT(q31_t, a, FRACT_BITS_Q31)
#define dsp_q15_cast_rnd_f32(a) FLT_2_INT(q15_t, a, FRACT_BITS_Q15)
#define dsp_q7_cast_rnd_f32(a)  FLT_2_INT(q7_t, a,  FRACT_BITS_Q7)
#endif

#ifdef __DSPLIB_FAST_MACROS
// this set of conversion macros should be used to decrease compilation time of large data amounts
#define FLT_2_INT(type, a, N) (type)((a)*((double)(type)MAX_VAL(N)))
#define dsp_q31_cast_rnd_f32(a) (q31_t)((a)*0x7fffffff)
#define dsp_q15_cast_rnd_f32(a) (q15_t)((a)*0x7fff)
#define dsp_q7_cast_rnd_f32(a)  (q7_t) ((a)*0x7f)
#endif

#ifdef __DSPLIB_DUMMY_MACROS
// this set of conversion macros should be used to compile just table prototypes and when data does not required in link_script
#define FLT_2_INT(type, a, N) (0)
#define dsp_q31_cast_rnd_f32(a) (q31_t)(0)
#define dsp_q15_cast_rnd_f32(a) (q15_t)(0)
#define dsp_q7_cast_rnd_f32(a)  (q7_t) (0)
#endif

// Deprecated names
#define FLT_2_Q31 dsp_q31_cast_rnd_f32
#define FLT_2_Q15 dsp_q15_cast_rnd_f32
#define FLT_2_Q7  dsp_q7_cast_rnd_f32

_Inline static q31_t dsp_q31_cast_q7(q7_t in){
	return (q31_t)in << 24;
}
_Inline static q31_t dsp_q31_cast_q15(q15_t in){
	return (q31_t)in << 16;
}
_Inline static q31_t dsp_q31_cast_f32(f32_t in){
	if (in >  1.0) return (q31_t)0x7fffffff;
	if (in <= -1.0) return (q31_t)0x80000000;
	return (q31_t)(2147483648.0*in);
}

_Inline static q15_t dsp_q15_cast_q7(q7_t in){
	return (q15_t)in << 8;
}
_Inline static q15_t dsp_q15_cast_q31(q31_t in){
	return (q15_t)(in >> 16);
}
_Inline static q15_t dsp_q15_cast_f32(f32_t in){
	if (in >  1.0) return (q15_t)0x7fff;
    if (in <= -1.0) return (q15_t)0x8000;
	return (q15_t)(32768.0*in);
}

_Inline static q7_t dsp_q7_cast_q15(q15_t in){
	return (q7_t)(in >> 8);
}
_Inline static q7_t dsp_q7_cast_q31(q31_t in){
	return (q7_t)(in >> 24);
}
_Inline static q7_t dsp_q7_cast_f32(f32_t in){
	if (in >  1.0) return (q7_t)0x7f;
	if (in <= -1.0) return (q7_t)0x80;
	return (q7_t)(128.0*in);
}

_Inline static f32_t dsp_f32_cast_q7(q7_t in){
	return (f32_t)in*(1/128.0);
}
_Inline static f32_t dsp_f32_cast_q15(q15_t in){
	return (f32_t)in*(1/32768.0);
}
_Inline static f32_t dsp_f32_cast_q31(q31_t in){
	return (f32_t)in*(1/2147483648.0);
}




#define COMPLEX_RE(data, i) (data)[(i)*2]
#define COMPLEX_IM(data, i) (data)[(i)*2+1]


#define COMPLEX_MATRIX_ELEMENT_RE(mtx, row, col) (mtx)->pData[(mtx)->colCnt*(row)*2 + (col)*2]
#define COMPLEX_MATRIX_ELEMENT_IM(mtx, row, col) (mtx)->pData[(mtx)->colCnt*(row)*2 + (col)*2+1]


#if defined(_ARC600_XY)

#define XADDR_Q31(x) ((int32_t*)((int8_t*)_get_xbase() + (x)*sizeof(q31_t)))
#define YADDR_Q31(x) ((int32_t*)((int8_t*)_get_ybase() + (x)*sizeof(q31_t)))
#define XADDR_Q15(x) ((int32_t*)((int8_t*)_get_xbase() + (x)*sizeof(q15_t)))
#define YADDR_Q15(x) ((int32_t*)((int8_t*)_get_ybase() + (x)*sizeof(q15_t)))

typedef struct { uint16_t numTaps; uint16_t shift; uint32_t xyptr_states; uint32_t xyptr_coeffs; } fir_q31_xy_t;
typedef struct { uint16_t numTaps; uint16_t shift; uint32_t xyptr_states; uint32_t xyptr_coeffs; } fir_q15_xy_t;

typedef struct { uint32_t postShift; fir_q31_xy_t filter; } iir_biquad_q31_xy_t;
typedef struct { uint32_t postShift; fir_q15_xy_t filter; } iir_biquad_q15_xy_t;

typedef struct { uint32_t length; int32_t shiftBits; dsp_transform_scaling scaling; } cfft_rad2_q31_xy_t;
typedef struct { uint32_t length; uint32_t xyptr_twd; int32_t shiftBits; dsp_transform_scaling scaling; } cfft_rad2_q15_xy_t;
typedef struct { uint32_t length; int32_t shiftBits; dsp_transform_scaling scaling; } cfft_rad2_f32_xy_t;

typedef struct { uint32_t length; uint32_t offs_twiddle; int32_t shiftBits; dsp_transform_scaling scaling; } cfft_srad_q31_xy_t;

typedef struct { uint32_t length; uint32_t xyptr_twd; dsp_spectrum_format spectrum_format; } rfft_f32_xy_t;
typedef struct { uint32_t length; uint32_t xyptr_twd; dsp_spectrum_format spectrum_format; } rfft_q31_xy_t;
typedef struct { uint32_t length; uint32_t xyptr_twd; dsp_spectrum_format spectrum_format; } rfft_q15_xy_t;

typedef struct { uint32_t length; uint32_t xyptr_twd; uint32_t xyptr_twd4; } dct2_q31_xy_t;
typedef struct { uint32_t length; uint32_t xyptr_twd; uint32_t xyptr_twd4; } dct2_q15_xy_t;

typedef struct { uint32_t length; uint32_t xyptr_twd; uint32_t xyptr_twd4; } dct3_q31_xy_t;
typedef struct { uint32_t length; uint32_t xyptr_twd; uint32_t xyptr_twd4; } dct3_q15_xy_t;

typedef struct { int32_t length; int32_t xyptr_prerot; int32_t xyptr_postrot; } dct4_q31_xy_t;
typedef struct { int32_t length; int32_t xyptr_prerot; int32_t xyptr_postrot; } dct4_q15_xy_t;

typedef struct { int32_t length; int32_t xyptr_twf; } fct4_q31_xy_t;
typedef struct { int32_t length; int32_t xyptr_twf; } fct4_q15_xy_t;

typedef struct { uint16_t order; uint32_t xyptr_states; uint32_t xyptr_pkcoeffs; uint32_t xyptr_pvcoeffs; } iir_lattice_q31_xy_t;
typedef struct { uint16_t order; uint32_t xyptr_states; uint32_t xyptr_pkcoeffs; uint32_t xyptr_pvcoeffs; } iir_lattice_q15_xy_t;

typedef struct {fir_q15_xy_t filter; uint8_t factor; uint16_t dly_line_size; } fir_intdec_q15_xy_t;
typedef struct {fir_q31_xy_t filter; uint8_t factor; uint16_t dly_line_size; } fir_intdec_q31_xy_t;

typedef struct { uint16_t numTaps; uint32_t xyptr_states; uint32_t xyptr_coeffs; q31_t mu; uint16_t shift; uint32_t postshift;} lms_q31_xy_t;
typedef struct { uint16_t numTaps; uint32_t xyptr_states; uint32_t xyptr_coeffs; q31_t mu; uint16_t shift; uint32_t postshift;} lms_q15_xy_t;

#define XYDEP(str) str
#else
#define XYDEP(str)
#endif

// Matrices Types

typedef struct { uint16_t rowCnt, colCnt; uint32_t size; q7_t  *pData; } matrix_q7_t;
typedef struct { uint16_t rowCnt, colCnt; uint32_t size; q15_t *pData; } matrix_q15_t;
typedef struct { uint16_t rowCnt, colCnt; uint32_t size; q31_t *pData; } matrix_q31_t;
typedef struct { uint16_t rowCnt, colCnt; uint32_t size; f32_t *pData; } matrix_f32_t;


// FIR-like filter types

typedef struct { uint16_t numTaps; uint16_t shift; q7_t *pData; const q7_t *pCoeffs; } fir_q7_t;
typedef struct { uint16_t numTaps; uint16_t shift; q15_t *pData; const q15_t *pCoeffs;  XYDEP(fir_q15_xy_t fir_q15_ll;)} fir_q15_t;
typedef struct { uint16_t numTaps; uint16_t shift; q31_t *pData; const q31_t *pCoeffs;  XYDEP(fir_q31_xy_t fir_q31_ll;)} fir_q31_t;
typedef struct { uint16_t numTaps; uint16_t shift; f32_t *pData; const f32_t *pCoeffs; } fir_f32_t;

typedef struct { uint8_t factor; fir_q15_t filter; uint8_t index; int32_t dly_line_size; XYDEP(fir_intdec_q15_xy_t fir_intdec_q15_xy;) } fir_intdec_q15_t;
typedef struct { uint8_t factor; fir_q31_t filter; uint8_t index; int32_t dly_line_size; XYDEP(fir_intdec_q31_xy_t fir_intdec_q31_xy;) } fir_intdec_q31_t;
typedef struct { uint8_t factor; fir_f32_t filter; uint8_t index; int32_t dly_line_size; } fir_intdec_f32_t;

typedef struct { uint16_t numTaps; q31_t *pState; q31_t *pCoeffs; q31_t mu; uint16_t shift; uint32_t postshift; XYDEP(lms_q31_xy_t lms_q31_ll;)} lms_q31_t;
typedef struct { uint16_t numTaps; q15_t *pState; q15_t *pCoeffs; q15_t mu; uint16_t shift; uint32_t postshift; XYDEP(lms_q15_xy_t lms_q15_ll;)} lms_q15_t;
typedef struct { uint16_t numTaps; f32_t *pState; f32_t *pCoeffs; f32_t mu; uint16_t shift;} lms_f32_t;

// IIR-like filter types


typedef struct { uint32_t postShift; fir_q15_t filter; XYDEP( iir_biquad_q15_xy_t iir_biquad_xy;) } iir_biquad_q15_t;
typedef struct { uint32_t postShift; fir_q31_t filter; XYDEP( iir_biquad_q31_xy_t iir_biquad_xy;) } iir_biquad_q31_t;
typedef struct { fir_f32_t filter; } iir_biquad_f32_t;

typedef struct { uint16_t order; q15_t *pData; const q15_t *pkCoeffs; const q15_t *pvCoeffs; XYDEP(iir_lattice_q15_xy_t iir_lattice_xy;) } iir_lattice_q15_t;
typedef struct { uint16_t order; q31_t *pData; const q31_t *pkCoeffs; const q31_t *pvCoeffs; XYDEP(iir_lattice_q31_xy_t iir_lattice_xy;) } iir_lattice_q31_t;
typedef struct { uint16_t order; f32_t *pData; const f32_t *pkCoeffs; const f32_t *pvCoeffs; } iir_lattice_f32_t;

// Transforms Types

typedef struct { uint32_t length; uint16_t invFlag; q15_t* temp_buffer; uint16_t bitReverse_flag; int16_t* tab_bit_rev; q15_t* ptwd; int32_t shiftBits; dsp_transform_scaling scaling; XYDEP(cfft_rad2_q15_xy_t fft_rad2_xy;) } cfft_q15_t;
typedef struct { uint32_t length; uint16_t invFlag; q31_t* temp_buffer; uint16_t bitReverse_flag; int16_t* tab_bit_rev; q31_t* ptwd; q31_t* ptwd3; int32_t shiftBits; dsp_transform_scaling scaling; XYDEP(cfft_rad2_q31_xy_t fft_rad2_xy;) } cfft_q31_t;
typedef struct { uint32_t length; uint16_t invFlag; f32_t* temp_buffer; uint16_t bitReverse_flag; int16_t* tab_bit_rev; f32_t* ptwd; f32_t* ptwd3; dsp_transform_scaling scaling; XYDEP(cfft_rad2_f32_xy_t fft_rad2_xy;) } cfft_f32_t;

typedef struct { cfft_f32_t hfft; uint32_t length; f32_t* temp_buffer; f32_t* ptwd; dsp_spectrum_format spectrum_format; dsp_transform_scaling scaling; XYDEP(rfft_f32_xy_t rfft_xy;) } rfft_f32_t;
typedef struct { cfft_q31_t hfft; uint32_t length; q31_t* temp_buffer; q31_t* ptwd; dsp_spectrum_format spectrum_format; dsp_transform_scaling scaling; XYDEP(rfft_q31_xy_t rfft_xy;) } rfft_q31_t;
typedef struct { cfft_q15_t hfft; uint32_t length; q15_t* temp_buffer; q15_t* ptwd; dsp_spectrum_format spectrum_format; dsp_transform_scaling scaling; XYDEP(rfft_q15_xy_t rfft_xy;) } rfft_q15_t;

typedef struct { cfft_q15_t hfft; uint32_t length; q15_t* temp_buffer; q15_t* ptwd; q15_t* ptwd4; XYDEP( dct2_q15_xy_t dct2_xy;) } dct2_q15_t;
typedef struct { cfft_q31_t hfft; uint32_t length; q31_t* temp_buffer; q31_t* ptwd; q31_t* ptwd4; XYDEP( dct2_q31_xy_t dct2_xy;) } dct2_q31_t;

typedef struct { cfft_q31_t hfft; uint32_t length; q31_t* temp_buffer; q31_t* ptwd; q31_t* ptwd4; XYDEP( dct3_q31_xy_t dct3_xy;) } dct3_q31_t;
typedef struct { cfft_q15_t hfft; uint32_t length; q15_t* temp_buffer; q15_t* ptwd; q15_t* ptwd4; XYDEP( dct3_q15_xy_t dct3_xy;) } dct3_q15_t;

typedef struct { cfft_q31_t hfft; uint32_t length; q31_t* temp_buffer; q31_t* prerot; q31_t* postrot; q31_t normalize; XYDEP(cfft_srad_q31_xy_t xy_fft; dct4_q31_xy_t xy_dct4;) } dct4_q31_t;
typedef struct { cfft_q15_t hfft; uint32_t length; q15_t* temp_buffer; q15_t* prerot; q15_t* postrot; q31_t normalize; XYDEP(cfft_rad2_q15_xy_t xy_fft; dct4_q15_xy_t xy_dct4;) } dct4_q15_t;

typedef struct { cfft_q31_t hfft; uint32_t length; q31_t* temp_buffer; q31_t* prerot; q31_t* postrot; XYDEP(cfft_srad_q31_xy_t xy_fft; dct4_q31_xy_t xy_dct4;) } mdct_q31_t;
typedef struct { cfft_q15_t hfft; uint32_t length; q15_t* temp_buffer; q15_t* prerot; q15_t* postrot; XYDEP(cfft_rad2_q15_xy_t xy_fft; dct4_q15_xy_t xy_dct4;) } mdct_q15_t;

// Interpolation functions types

typedef struct { uint16_t order; const  q7_t *pCoeffs; int32_t shift; } pol_q7_t;
typedef struct { uint16_t order; const q15_t *pCoeffs; int32_t shift; } pol_q15_t;
typedef struct { uint16_t order; const q31_t *pCoeffs; int32_t shift; } pol_q31_t;
typedef struct { uint16_t order; const f32_t *pCoeffs; } pol_f32_t;

typedef struct {
    uint32_t nValues; // grid(table) length
    f32_t x1;         // first element linking
    f32_t spacing;    // spacing between 2 elements
    f32_t *pData;     // pointer to the grid
} dsp_linear_interp_instance_f32;


// set default calling conventions for dsplib to __xyfast for Shanghai versions
#ifndef DSPLIB_CC_NO_XYFAST
#define DSPLIB_CC_XYFAST
#endif

#if defined (DSPLIB_CC_XYFAST) && defined(_ARCv2EM_XY)
// "__xyfast" predicator is removed in functions description due to it is set as default in MWDT 2015.12
#define _DSPLIB_XYCC
#else
// placeholder for alternative calling convention
#define _DSPLIB_XYCC
#endif

#if defined _ARCv2EM_XY
// define calling convention to functions which does not use XY memory internally. It is required to minimize context store/restore overheads.
#define _DSPLIB_NOXYCC __xypreserve
#else
#define _DSPLIB_NOXYCC
#endif

#ifdef _ARC
#if defined _ARCv2EM_XY && defined __Xagu
#define __AGU __agu
#else
#define __AGU
#endif
#else
#define __AGU
#define __xy
#define __agu
#endif

#endif

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

#ifndef _DSPLIB_API_HEADER_ARC
#define _DSPLIB_API_HEADER_ARC

#include "dsplib_types.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

    //*** VECTOR MATH BLOCK ***
    //different data types cast
void _DSPLIB_XYCC dsp_q15_cast_vect_f32(__AGU f32_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_q7_cast_vect_f32 (__AGU f32_t * __restrict pSrc, __AGU q7_t *  __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_q31_cast_vect_f32(__AGU f32_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);

void _DSPLIB_XYCC dsp_q15_cast_vect_q31(__AGU q31_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_q7_cast_vect_q31 (__AGU q31_t * __restrict pSrc, __AGU q7_t *  __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_f32_cast_vect_q31(__AGU q31_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);

void _DSPLIB_XYCC dsp_q31_cast_vect_q15(__AGU q15_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_q7_cast_vect_q15 (__AGU q15_t * __restrict pSrc, __AGU q7_t *  __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_f32_cast_vect_q15(__AGU q15_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);

void _DSPLIB_XYCC dsp_q15_cast_vect_q7 (__AGU q7_t *  __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_q31_cast_vect_q7 (__AGU q7_t *  __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_f32_cast_vect_q7 (__AGU q7_t *  __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);

    //calculates absolute value of vector
void _DSPLIB_XYCC dsp_abs_f32(const __AGU f32_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_abs_q31(const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_abs_q15(const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_abs_q7(const __AGU q7_t * __restrict pSrc, __AGU q7_t * __restrict pDst, uint32_t nSamples);

    //negate vector
void _DSPLIB_XYCC dsp_negate_f32(const __AGU f32_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_negate_q31(const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_negate_q15(const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_negate_q7(const __AGU q7_t * __restrict pSrc, __AGU q7_t * __restrict pDst, uint32_t nSamples);

    //addition of 2 vectors
void _DSPLIB_XYCC dsp_add_f32(const __AGU f32_t * __restrict pSrcA, const __AGU f32_t * __restrict pSrcB, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_add_q31(const __AGU q31_t * __restrict pSrcA, const __AGU q31_t * __restrict pSrcB, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_add_q15(const __AGU q15_t * __restrict pSrcA, const __AGU q15_t * __restrict pSrcB, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_add_q7(const __AGU q7_t * __restrict pSrcA, const __AGU q7_t * __restrict pSrcB, __AGU q7_t * __restrict pDst, uint32_t nSamples);

    //substraction of 2 vectors
void _DSPLIB_XYCC dsp_sub_f32(const __AGU f32_t * __restrict pSrcA, const __AGU f32_t * __restrict pSrcB, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_sub_q31(const __AGU q31_t * __restrict pSrcA, const __AGU q31_t * __restrict pSrcB, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_sub_q15(const __AGU q15_t * __restrict pSrcA, const __AGU q15_t * __restrict pSrcB, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_sub_q7(const __AGU q7_t * __restrict pSrcA, const __AGU q7_t * __restrict pSrcB, __AGU q7_t * __restrict pDst, uint32_t nSamples);

    //addition of constant to vector
void _DSPLIB_XYCC dsp_offset_f32(const __AGU f32_t * __restrict pSrc, f32_t offset, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_offset_q31(const __AGU q31_t * __restrict pSrc, q31_t offset, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_offset_q15(const __AGU q15_t * __restrict pSrc, q15_t offset, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_offset_q7(const __AGU q7_t * __restrict pSrc, q7_t offset, __AGU q7_t * __restrict pDst, uint32_t nSamples);

    //per element multiplication of 2 vectors
void _DSPLIB_XYCC dsp_mult_f32(const __AGU f32_t * __restrict pSrcA, const __AGU f32_t * __restrict pSrcB, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_mult_q31(const __AGU q31_t * __restrict pSrcA, const __AGU q31_t * __restrict pSrcB, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_mult_q15(const __AGU q15_t * __restrict pSrcA, const __AGU q15_t * __restrict pSrcB, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_mult_q7(const __AGU q7_t * __restrict pSrcA, const __AGU q7_t * __restrict pSrcB, __AGU q7_t * __restrict pDst, uint32_t nSamples);

    //multiplication of float point vector and const

    /*multiplication of vector and const witch is represented by fractional part q.(n) value and shift value*/
void _DSPLIB_XYCC dsp_scale_q31(const __AGU q31_t * __restrict pSrc, q31_t   scaleFract, int8_t  shift, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_scale_q15(const __AGU q15_t * __restrict pSrc, q15_t   scaleFract, int8_t  shift, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_scale_q7(const __AGU q7_t * __restrict pSrc, q7_t   scaleFract, int8_t  shift, __AGU q7_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_scale_f32(const __AGU f32_t * __restrict pSrc, f32_t   scale, __AGU f32_t * __restrict pDst,  uint32_t nSamples);

    /*shift vector by N bits*/
void _DSPLIB_XYCC dsp_shift_q31(const __AGU q31_t * __restrict pSrc, int8_t  shiftBits, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_shift_q15(const __AGU q15_t * __restrict pSrc, int8_t  shiftBits, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_shift_q7(const __AGU q7_t * __restrict pSrc, int8_t  shiftBits, __AGU q7_t * __restrict pDst, uint32_t nSamples);

    //vector dot product
void _DSPLIB_XYCC dsp_dot_prod_f32(const __AGU f32_t * __restrict pSrcA, const __AGU f32_t * __restrict pSrcB, uint32_t nSamples, f32_t *result);
void _DSPLIB_XYCC dsp_dot_prod_q31(const __AGU q31_t * __restrict pSrcA, const __AGU q31_t * __restrict pSrcB, uint32_t nSamples, q63_t *result);
void _DSPLIB_XYCC dsp_dot_prod_q15(const __AGU q15_t * __restrict pSrcA, const __AGU q15_t * __restrict pSrcB, uint32_t nSamples, q63_t *result);
void _DSPLIB_XYCC dsp_dot_prod_q7(const __AGU q7_t * __restrict pSrcA, const __AGU q7_t * __restrict pSrcB, uint32_t nSamples, q31_t *result);


    //get maximum vector value
void _DSPLIB_XYCC dsp_min_f32(const __AGU f32_t * __restrict pSrc, uint32_t nSamples, f32_t *pResult, uint32_t *pIndex);
void _DSPLIB_XYCC dsp_min_q31(const __AGU q31_t * __restrict pSrc, uint32_t nSamples, q31_t *pResult, uint32_t *pIndex);
void _DSPLIB_XYCC dsp_min_q15(const __AGU q15_t * __restrict pSrc, uint32_t nSamples, q15_t *pResult, uint32_t *pIndex);
void _DSPLIB_XYCC dsp_min_q7(const __AGU q7_t * __restrict pSrc, uint32_t nSamples, q7_t *pResult, uint32_t *pIndex);

    //get minimum vector value
void _DSPLIB_XYCC dsp_max_f32(const __AGU f32_t * __restrict pSrc, uint32_t nSamples, f32_t *pResult, uint32_t *pIndex);
void _DSPLIB_XYCC dsp_max_q31(const __AGU q31_t * __restrict  pSrc, uint32_t nSamples, q31_t *pResult, uint32_t *pIndex);
void _DSPLIB_XYCC dsp_max_q15(const __AGU q15_t * __restrict  pSrc, uint32_t nSamples, q15_t *pResult, uint32_t *pIndex);
void _DSPLIB_XYCC dsp_max_q7(const __AGU q7_t * __restrict pSrc, uint32_t nSamples, q7_t *pResult, uint32_t *pIndex);

    //conjugate operates on input *sequence* (re,im)
void _DSPLIB_XYCC dsp_cmpl_conj_f32(const __AGU f32_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_cmpl_conj_q31(const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_cmpl_conj_q15(const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);

    //complex dot product
void _DSPLIB_XYCC dsp_cmpl_dot_prod_q15(const __AGU q15_t * __restrict pSrcA, const __AGU q15_t * __restrict pSrcB, uint32_t nSamples, q31_t *realResult, q31_t *imagResult);
void _DSPLIB_XYCC dsp_cmpl_dot_prod_q31(const __AGU q31_t * __restrict pSrcA, const __AGU q31_t * __restrict pSrcB, uint32_t nSamples, q63_t *realResult, q63_t *imagResult);
void _DSPLIB_XYCC dsp_cmpl_dot_prod_f32(const __AGU f32_t * __restrict pSrcA, const __AGU f32_t * __restrict pSrcB, uint32_t nSamples, f32_t *realResult, f32_t *imagResult);

    //magnitude
void _DSPLIB_XYCC dsp_cmpl_mag_f32(const __AGU f32_t * __restrict pSrc,  __AGU f32_t * __restrict pDst,  uint32_t nSamples);
void _DSPLIB_XYCC dsp_cmpl_mag_q31(const __AGU q31_t * __restrict pSrc,  __AGU q31_t * __restrict pDst,  uint32_t nSamples);
void _DSPLIB_XYCC dsp_cmpl_mag_q15(const __AGU q15_t * __restrict pSrc,  __AGU q15_t * __restrict pDst,  uint32_t nSamples);

    //magnitude squared 
void _DSPLIB_XYCC dsp_cmpl_mag_squared_f32(const __AGU f32_t * __restrict pSrc,  __AGU f32_t * __restrict pDst,  uint32_t nSamples);
void _DSPLIB_XYCC dsp_cmpl_mag_squared_q31(const __AGU q31_t * __restrict pSrc,  __AGU q31_t * __restrict pDst,  uint32_t nSamples);
void _DSPLIB_XYCC dsp_cmpl_mag_squared_q15(const __AGU q15_t * __restrict pSrc,  __AGU q15_t * __restrict pDst,  uint32_t nSamples);

    //complex multiply with complex
void _DSPLIB_XYCC dsp_cmpl_mult_cmpl_f32(const __AGU f32_t *  __restrict pSrcA, const __AGU f32_t *  __restrict pSrcB, __AGU f32_t *  __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_cmpl_mult_cmpl_q31(const __AGU q31_t * __restrict pSrcA, const __AGU q31_t * __restrict pSrcB, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_cmpl_mult_cmpl_q15(const __AGU q15_t * __restrict pSrcA, const __AGU q15_t * __restrict pSrcB, __AGU q15_t * __restrict pDst, uint32_t nSamples);

    //complex multiply with real
void _DSPLIB_XYCC dsp_cmpl_mult_real_f32(const __AGU f32_t *  __restrict pSrcCmplx, const __AGU f32_t *  __restrict pSrcReal, __AGU f32_t *  __restrict pCmplxDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_cmpl_mult_real_q31(const __AGU q31_t * __restrict pSrcCmplx, const __AGU q31_t * __restrict pSrcReal, __AGU q31_t * __restrict pCmplxDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_cmpl_mult_real_q15(const __AGU q15_t * __restrict pSrcCmplx, const __AGU q15_t * __restrict pSrcReal, __AGU q15_t * __restrict pCmplxDst, uint32_t nSamples);

    //*** SCALAR MATH BLOCK ***

    //"calculates sine. q.31 value [-1; 1) is mapped to [-pi;pi)"
f32_t _DSPLIB_NOXYCC dsp_sin_f32(f32_t in);
q31_t _DSPLIB_NOXYCC dsp_sin_q31(q31_t in);
q15_t _DSPLIB_NOXYCC dsp_sin_q15(q15_t in);

    //"calculates cosine. q.31 value [-1; 1) is mapped to [-pi;pi)"
f32_t _DSPLIB_NOXYCC dsp_cos_f32(f32_t in);
q31_t _DSPLIB_NOXYCC dsp_cos_q31(q31_t in);
q15_t _DSPLIB_NOXYCC dsp_cos_q15(q15_t in);

// calculates tangent
q31_t _DSPLIB_NOXYCC dsp_tan_q31(q31_t in);
q15_t _DSPLIB_NOXYCC dsp_tan_q15(q15_t in);

    //"converts Cartesian coordinate value to angle value output: [-1; 1) is mapped to [-pi;pi)"
q31_t _DSPLIB_NOXYCC dsp_atan2_q31(q31_t y, q31_t x);
q15_t _DSPLIB_NOXYCC dsp_atan2_q15(q15_t y, q15_t x);

// calculates arctangent
q31_t _DSPLIB_NOXYCC dsp_atan_q31(q31_t in);
q15_t _DSPLIB_NOXYCC dsp_atan_q15(q15_t in);

// calculates arcsine
q31_t _DSPLIB_NOXYCC dsp_asin_q31(q31_t in);
q15_t _DSPLIB_NOXYCC dsp_asin_q15(q15_t in);

// calculates arccosine
q31_t _DSPLIB_NOXYCC dsp_acos_q31(q31_t in);
q15_t _DSPLIB_NOXYCC dsp_acos_q15(q15_t in);

    //calculates square root
f32_t _DSPLIB_NOXYCC dsp_sqrt_f32(f32_t op);
q31_t _DSPLIB_NOXYCC dsp_sqrt_q31(q31_t op);
q15_t _DSPLIB_NOXYCC dsp_sqrt_q15(q15_t op);

    //calculates 1/sqrt(x) value
q31_t _DSPLIB_NOXYCC dsp_reciprt_q31(q31_t x);

    //fractional division, input condition: den > num
q31_t _DSPLIB_NOXYCC dsp_div_q31(q31_t num, q31_t den);
q31_t _DSPLIB_NOXYCC dsp_div_q31_q15(q31_t num, q15_t den);
q15_t _DSPLIB_NOXYCC dsp_div_q15(q15_t num, q15_t den);

    //reciprocal function 1/(x) calculation
q31_t _DSPLIB_NOXYCC dsp_recip_q31(int32_t x);
q15_t _DSPLIB_NOXYCC dsp_recip_q15(int16_t x);

    //"logarithm base 2 calculation in ragne: input - (0.5;1) output - (-1; 0)"
q31_t _DSPLIB_NOXYCC dsp_log2_q31(q31_t x);
q15_t _DSPLIB_NOXYCC dsp_log2_q15(q15_t x);

    //"power function calculates y=2^(x) in range: input - [-1;0] output - [1;0.5]"
q31_t _DSPLIB_NOXYCC dsp_pow2x_q31(q31_t x);
q15_t _DSPLIB_NOXYCC dsp_pow2x_q15(q15_t x);

    //*** MATRIX BLOCK ***

    //do initialization of matrix structure
void _DSPLIB_XYCC dsp_mat_init_f32(matrix_f32_t *matrix, uint16_t nRows, uint16_t nColumns, __AGU f32_t * pData);
void _DSPLIB_XYCC dsp_mat_init_q31(matrix_q31_t *matrix, uint16_t nRows, uint16_t nColumns, __AGU q31_t * pData);
void _DSPLIB_XYCC dsp_mat_init_q15(matrix_q15_t *matrix, uint16_t nRows, uint16_t nColumns, __AGU q15_t * pData);
void _DSPLIB_XYCC dsp_mat_init_q7(matrix_q7_t *matrix, uint16_t nRows, uint16_t nColumns, __AGU q7_t * pData);

    //addition of 2 matrices [M x N] = [M x N] + [M x N]
dsp_status _DSPLIB_XYCC dsp_mat_add_f32(const matrix_f32_t *pSrcA, const matrix_f32_t *pSrcB, matrix_f32_t *pDst);
dsp_status _DSPLIB_XYCC dsp_mat_add_q31(const matrix_q31_t *pSrcA, const matrix_q31_t *pSrcB, matrix_q31_t *pDst);
dsp_status _DSPLIB_XYCC dsp_mat_add_q15(const matrix_q15_t *pSrcA, const matrix_q15_t *pSrcB, matrix_q15_t *pDst);

    //subtraction of 2 matrices [M x N] = [M x N] - [M x N]
dsp_status _DSPLIB_XYCC dsp_mat_sub_f32(const matrix_f32_t *pSrcA, const matrix_f32_t *pSrcB, matrix_f32_t *pDst);
dsp_status _DSPLIB_XYCC dsp_mat_sub_q31(const matrix_q31_t *pSrcA, const matrix_q31_t *pSrcB, matrix_q31_t *pDst);
dsp_status _DSPLIB_XYCC dsp_mat_sub_q15(const matrix_q15_t *pSrcA, const matrix_q15_t *pSrcB, matrix_q15_t *pDst);

    //multiplication of 2 matrices [M x K] = [M x N] * [N x K]
dsp_status _DSPLIB_XYCC dsp_mat_mult_f32(const matrix_f32_t *pSrcA, const matrix_f32_t *pSrcB, matrix_f32_t *pDst);
dsp_status _DSPLIB_XYCC dsp_mat_mult_q31(const matrix_q31_t *pSrcA, const matrix_q31_t *pSrcB, matrix_q31_t *pDst);
dsp_status _DSPLIB_XYCC dsp_mat_mult_q15(const matrix_q15_t *pSrcA, const matrix_q15_t *pSrcB, matrix_q15_t *pDst);

    //multiplication of matrix and const [M x N] = [M x N] * const
dsp_status _DSPLIB_XYCC dsp_mat_scale_f32(const matrix_f32_t *pSrc, f32_t factor, matrix_f32_t *pDst);
dsp_status _DSPLIB_XYCC dsp_mat_scale_q31(const matrix_q31_t *pSrc, q31_t factor, int32_t shift, matrix_q31_t *pDst);
dsp_status _DSPLIB_XYCC dsp_mat_scale_q15(const matrix_q15_t *pSrc, q15_t factor, int32_t shift, matrix_q15_t *pDst);

    //transpose of matrix [N x M] = [M x N]
dsp_status _DSPLIB_XYCC dsp_mat_trans_f32(const matrix_f32_t *pSrc, matrix_f32_t *pDst);
dsp_status _DSPLIB_XYCC dsp_mat_trans_q31(const matrix_q31_t *pSrc, matrix_q31_t *pDst);
dsp_status _DSPLIB_XYCC dsp_mat_trans_q15(const matrix_q15_t *pSrc, matrix_q15_t *pDst);

    //inverse of square matrix [M x M] = [M x M]
dsp_status _DSPLIB_XYCC dsp_mat_inverse_f32(const matrix_f32_t  *pSrc, matrix_f32_t  *pDst);

    //*** COMPLEX MARIX BLOCK ***

    //addition of 2 complex matrices [M x N] = [M x N] + [M x N]
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_add_f32(const matrix_f32_t *pSrcA, const matrix_f32_t *pSrcB, matrix_f32_t *pDst);
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_add_q31(const matrix_q31_t *pSrcA, const matrix_q31_t *pSrcB, matrix_q31_t *pDst);
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_add_q15(const matrix_q15_t *pSrcA, const matrix_q15_t *pSrcB, matrix_q15_t *pDst);

    //subtraction of 2 complex matrices [M x N] = [M x N] - [M x N]
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_sub_f32(const matrix_f32_t *pSrcA, const matrix_f32_t *pSrcB, matrix_f32_t *pDst);
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_sub_q31(const matrix_q31_t *pSrcA, const matrix_q31_t *pSrcB, matrix_q31_t *pDst);
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_sub_q15(const matrix_q15_t *pSrcA, const matrix_q15_t *pSrcB, matrix_q15_t *pDst);

    //multiplication of 2 complex matrices [M x K] = [M x N] * [N x K]
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_mult_f32(const matrix_f32_t *pSrcA, const matrix_f32_t *pSrcB, matrix_f32_t *pDst);
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_mult_q31(const matrix_q31_t *pSrcA, const matrix_q31_t *pSrcB, matrix_q31_t *pDst);
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_mult_q15(const matrix_q15_t *pSrcA, const matrix_q15_t *pSrcB, matrix_q15_t *pDst);

    //multiplication of complex matrix and const [M x N] = [M x N] * const
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_scale_f32(const matrix_f32_t *pSrc, f32_t factor, matrix_f32_t *pDst);
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_scale_q31(const matrix_q31_t *pSrc, q31_t factor, int32_t shift, matrix_q31_t *pDst);
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_scale_q15(const matrix_q15_t *pSrc, q15_t factor, int32_t shift, matrix_q15_t *pDst);

    //transpose of complex matrix [N x M] = [M x N]
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_trans_f32(const matrix_f32_t *pSrc, matrix_f32_t *pDst);
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_trans_q31(const matrix_q31_t *pSrc, matrix_q31_t *pDst);
dsp_status _DSPLIB_XYCC dsp_cmpl_mat_trans_q15(const matrix_q15_t *pSrc, matrix_q15_t *pDst);

    //*** FILTERING BLOCK ***

    //Real value FIR filter
#define dsp_fir_getsize_f32(nTaps) (nTaps * sizeof(f32_t))
#define dsp_fir_getsize_q31(nTaps) (nTaps * sizeof(q31_t))
#define dsp_fir_getsize_q15(nTaps) ((nTaps*3+4) * sizeof(q15_t))
#define dsp_fir_getsize_q7(nTaps) (0)
dsp_status _DSPLIB_XYCC dsp_fir_init_f32(fir_f32_t *inst, uint16_t nTaps, const __AGU f32_t * pCoeffs, __AGU f32_t * pState);
dsp_status _DSPLIB_XYCC dsp_fir_init_q31(fir_q31_t *inst, uint16_t nTaps, const __AGU q31_t * pCoeffs, __AGU q31_t * pState);
dsp_status _DSPLIB_XYCC dsp_fir_init_q15(fir_q15_t *inst, uint16_t nTaps, const __AGU q15_t * pCoeffs, __AGU q15_t * pState);
dsp_status _DSPLIB_XYCC dsp_fir_init_q7(fir_q7_t *inst, uint16_t nTaps, const __AGU q7_t * pCoeffs, __AGU q7_t * pState);
void dsp_fir_delete_f32(fir_f32_t *inst);
void dsp_fir_delete_q31(fir_q31_t *inst);
void dsp_fir_delete_q15(fir_q15_t *inst);
void dsp_fir_delete_q7(fir_q7_t *inst);
void _DSPLIB_XYCC dsp_fir_f32(fir_f32_t *inst, const __AGU f32_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_q31(fir_q31_t *inst, const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_q15(fir_q15_t *inst, const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_q7(fir_q7_t *inst, const __AGU q7_t * __restrict pSrc, __AGU q7_t * __restrict pDst, uint32_t nSamples);

    //Complex FIR filter
#define dsp_fir_complex_getsize_q31(nTaps) (nTaps * sizeof(q31_t) * 2)
#define dsp_fir_complex_getsize_q15(nTaps) (nTaps * sizeof(q15_t) * 2)
dsp_status _DSPLIB_XYCC dsp_fir_complex_init_q31(fir_q31_t *inst, uint16_t nTaps, const __AGU q31_t * pCoeffs, __AGU q31_t * pState);
dsp_status _DSPLIB_XYCC dsp_fir_complex_init_q15(fir_q15_t *inst, uint16_t nTaps, const __AGU q15_t * pCoeffs, __AGU q15_t * pState);
void dsp_fir_complex_delete_q31(fir_q31_t *inst);
void dsp_fir_complex_delete_q15(fir_q15_t *inst);
void _DSPLIB_XYCC dsp_fir_complex_q31(fir_q31_t *inst, const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_complex_q15(fir_q15_t *inst, const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);

   // Deprecated function names. Please avoid use these names in current and future projects
#define dsp_fir_getsize_q31_complex dsp_fir_complex_getsize_q31
#define dsp_fir_getsize_q15_complex dsp_fir_complex_getsize_q15
#define dsp_fir_init_q31_complex dsp_fir_complex_init_q31
#define dsp_fir_init_q15_complex dsp_fir_complex_init_q15
#define dsp_fir_q31_complex dsp_fir_complex_q31
#define dsp_fir_q15_complex dsp_fir_complex_q15
#define dsp_fir_delete_q31_complex dsp_fir_complex_delete_q31
#define dsp_fir_delete_q15_complex dsp_fir_complex_delete_q15

    //Decimation FIR filter
#define dsp_fir_decimate_getsize_f32(nTaps, decFactor) (0)
#define dsp_fir_decimate_getsize_q31(nTaps, decFactor) (nTaps * sizeof(q31_t))
#define dsp_fir_decimate_getsize_q15(nTaps, decFactor) ((nTaps + 1) * sizeof(q15_t))
dsp_status _DSPLIB_XYCC dsp_fir_decimate_init_f32(fir_intdec_f32_t *inst, uint16_t nTaps, uint8_t decFactor, const __AGU f32_t * pCoeffs, __AGU f32_t * pState);
dsp_status _DSPLIB_XYCC dsp_fir_decimate_init_q31(fir_intdec_q31_t *inst, uint16_t nTaps, uint8_t decFactor, const __AGU q31_t * pCoeffs, __AGU q31_t * pState);
dsp_status _DSPLIB_XYCC dsp_fir_decimate_init_q15(fir_intdec_q15_t *inst, uint16_t nTaps, uint8_t decFactor, const __AGU q15_t * pCoeffs, __AGU q15_t * pState);
void dsp_fir_decimate_delete_f32(fir_intdec_f32_t *inst);
void dsp_fir_decimate_delete_q31(fir_intdec_q31_t *inst);
void dsp_fir_decimate_delete_q15(fir_intdec_q15_t *inst);
void _DSPLIB_XYCC dsp_fir_decimate_f32(fir_intdec_f32_t *inst, const __AGU f32_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_decimate_q31(fir_intdec_q31_t *inst, const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_decimate_q15(fir_intdec_q15_t *inst, const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);

    //Interpolation FIR filter
#define dsp_fir_interpolate_getsize_f32(nTaps, intFactor) (nTaps * sizeof(f32_t))
#define dsp_fir_interpolate_getsize_q31(nTaps, intFactor) (nTaps * sizeof(q31_t))
#define dsp_fir_interpolate_getsize_q15(nTaps, intFactor) (nTaps * sizeof(q15_t))
dsp_status _DSPLIB_XYCC dsp_fir_interpolate_init_f32(fir_intdec_f32_t *inst, uint16_t nTaps, uint8_t intFactor, const __AGU f32_t * pCoeffs, __AGU f32_t * pState);
dsp_status _DSPLIB_XYCC dsp_fir_interpolate_init_q31(fir_intdec_q31_t *inst, uint16_t nTaps, uint8_t intFactor, const __AGU q31_t * pCoeffs, __AGU q31_t * pState);
dsp_status _DSPLIB_XYCC dsp_fir_interpolate_init_q15(fir_intdec_q15_t *inst, uint16_t nTaps, uint8_t intFactor, const __AGU q15_t * pCoeffs, __AGU q15_t * pState);
void dsp_fir_interpolate_delete_f32(fir_intdec_f32_t *inst);
void dsp_fir_interpolate_delete_q31(fir_intdec_q31_t *inst);
void dsp_fir_interpolate_delete_q15(fir_intdec_q15_t *inst);
void _DSPLIB_XYCC dsp_fir_interpolate_f32(fir_intdec_f32_t *inst, const __AGU f32_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_interpolate_q31(fir_intdec_q31_t *inst, const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_interpolate_q15(fir_intdec_q15_t *inst, const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);

    //LMS filter
#define dsp_lms_getsize_f32(numTaps) (sizeof(f32_t) * (numTaps))
#define dsp_lms_getsize_q31(numTaps) (sizeof(q31_t) * (numTaps))
#define dsp_lms_getsize_q15(numTaps) (sizeof(q15_t) * (numTaps))
dsp_status _DSPLIB_XYCC dsp_lms_init_f32(lms_f32_t  *inst,  uint16_t numTaps,  __AGU f32_t * pCoeffs,  __AGU f32_t * pState,  f32_t mu);
dsp_status _DSPLIB_XYCC dsp_lms_init_q31(lms_q31_t  *inst,  uint16_t numTaps,  __AGU q31_t * pCoeffs,  __AGU q31_t * pState,  q31_t mu);
dsp_status _DSPLIB_XYCC dsp_lms_init_q15(lms_q15_t  *inst,  uint16_t numTaps,  __AGU q15_t * pCoeffs,  __AGU q15_t * pState,  q15_t mu);
void dsp_lms_delete_f32(lms_f32_t  *inst);
void dsp_lms_delete_q31(lms_q31_t  *inst);
void dsp_lms_delete_q15(lms_q15_t  *inst);
void _DSPLIB_XYCC dsp_lms_f32(lms_f32_t  *inst,  const __AGU f32_t * __restrict pSrc,  const __AGU f32_t * __restrict pRef,  __AGU f32_t * __restrict pOut,  __AGU f32_t * __restrict pErr,  uint32_t nSamples);
void _DSPLIB_XYCC dsp_lms_q31(lms_q31_t  *inst,  const __AGU q31_t * __restrict pSrc,  const __AGU q31_t * __restrict pRef,  __AGU q31_t * __restrict pOut,  __AGU q31_t * __restrict pErr,  uint32_t nSamples);
void _DSPLIB_XYCC dsp_lms_q15(lms_q15_t  *inst,  const __AGU q15_t * __restrict pSrc,  const __AGU q15_t * __restrict pRef,  __AGU q15_t * __restrict pOut,  __AGU q15_t * __restrict pErr,  uint32_t nSamples);

    //Bi-quad IIR filter
#if defined (_ARCv2EM_XY)
#define dsp_biquad_cascade_df1_getsize_q31(numStages) ((numStages * 4 + 1) * sizeof(q31_t))
#define dsp_biquad_cascade_df1_getsize_q15(numStages) ((numStages * 4 + 1) * sizeof(q15_t))
#define dsp_biquad_cascade_df1_getsize_f32(numStages) ((numStages * 4 + 1) * sizeof(f32_t))
#else
#define dsp_biquad_cascade_df1_getsize_q31(numStages) (numStages * 4 * sizeof(q31_t))
#define dsp_biquad_cascade_df1_getsize_q15(numStages) (numStages * 4 * sizeof(q15_t))
#define dsp_biquad_cascade_df1_getsize_f32(numStages) (numStages * 4 * sizeof(f32_t))
#endif

dsp_status _DSPLIB_XYCC dsp_biquad_cascade_df1_init_q31(iir_biquad_q31_t *inst, uint8_t numStages, const __AGU q31_t * pCoeffs, __AGU q31_t * pState, int8_t postShift);
dsp_status _DSPLIB_XYCC dsp_biquad_cascade_df1_init_q15(iir_biquad_q15_t *inst, uint8_t numStages, const __AGU q15_t * pCoeffs, __AGU q15_t * pState, int8_t postShift);
dsp_status _DSPLIB_XYCC dsp_biquad_cascade_df1_init_f32(iir_biquad_f32_t *inst, uint8_t numStages, const __AGU f32_t * pCoeffs, __AGU f32_t * pState);
void dsp_biquad_cascade_df1_delete_q31(iir_biquad_q31_t *inst);
void dsp_biquad_cascade_df1_delete_q15(iir_biquad_q15_t *inst);
void dsp_biquad_cascade_df1_delete_f32(iir_biquad_f32_t *inst);
void _DSPLIB_XYCC dsp_biquad_cascade_df1_q31(const iir_biquad_q31_t *inst, const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_biquad_cascade_df1_q15(const iir_biquad_q15_t *inst, const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_biquad_cascade_df1_f32(const iir_biquad_f32_t *inst, const __AGU f32_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);

    //Bi-quad IIR filter with DF2T biquad section
#define dsp_biquad_cascade_df2T_getsize_f32(numStages) (numStages * 2 * sizeof(f32_t))
dsp_status _DSPLIB_XYCC dsp_biquad_cascade_df2T_init_f32(iir_biquad_f32_t *inst, uint8_t numStages, const __AGU f32_t * pCoeffs, __AGU f32_t * pState);
void dsp_biquad_cascade_df2T_delete_f32(iir_biquad_f32_t *inst);
void _DSPLIB_XYCC dsp_biquad_cascade_df2T_f32(const iir_biquad_f32_t *inst, const __AGU f32_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);

    //Lattice IIR filter
#define dsp_iir_lattice_getsize_f32(nStages) ((nStages + 1) * sizeof(f32_t))
#define dsp_iir_lattice_getsize_q31(nStages) ((nStages + 1) * sizeof(q31_t))
#define dsp_iir_lattice_getsize_q15(nStages) ((nStages + 1) * sizeof(q15_t))
dsp_status _DSPLIB_XYCC dsp_iir_lattice_init_f32(iir_lattice_f32_t *inst, uint16_t nStages, const __AGU f32_t * pkCoeffs, const __AGU f32_t * pvCoeffs, __AGU f32_t * pState);
dsp_status _DSPLIB_XYCC dsp_iir_lattice_init_q31(iir_lattice_q31_t *inst, uint16_t nStages, const __AGU q31_t * pkCoeffs, const __AGU q31_t * pvCoeffs, __AGU q31_t * pState);
dsp_status _DSPLIB_XYCC dsp_iir_lattice_init_q15(iir_lattice_q15_t *inst, uint16_t nStages, const __AGU q15_t * pkCoeffs, const __AGU q15_t * pvCoeffs, __AGU q15_t * pState);
void dsp_iir_lattice_delete_f32(iir_lattice_f32_t *inst);
void dsp_iir_lattice_delete_q31(iir_lattice_q31_t *inst);
void dsp_iir_lattice_delete_q15(iir_lattice_q15_t *inst);
void _DSPLIB_XYCC dsp_iir_lattice_f32(const iir_lattice_f32_t *inst, const __AGU f32_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_iir_lattice_q31(const iir_lattice_q31_t *inst, const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_iir_lattice_q15(const iir_lattice_q15_t *inst, const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);

    //Convolution of 2 vectors
void _DSPLIB_XYCC dsp_conv_f32(const __AGU f32_t * __restrict pSrcA, uint32_t nLenA, const __AGU f32_t * __restrict pSrcB, uint32_t nLenB, __AGU f32_t * __restrict pDst);
void _DSPLIB_XYCC dsp_conv_q31(const __AGU q31_t * __restrict pSrcA, uint32_t nLenA, const __AGU q31_t * __restrict pSrcB, uint32_t nLenB, __AGU q31_t * __restrict pDst);
void _DSPLIB_XYCC dsp_conv_q15(const __AGU q15_t * __restrict pSrcA, uint32_t nLenA, const __AGU q15_t * __restrict pSrcB, uint32_t nLenB, __AGU q15_t * __restrict pDst);
void _DSPLIB_XYCC dsp_conv_q7(const __AGU q7_t * __restrict pSrcA, uint32_t nLenA, const __AGU q7_t * __restrict pSrcB, uint32_t nLenB, __AGU q7_t * __restrict pDst);

    //Correlation of 2 vectors
void _DSPLIB_XYCC dsp_correlate_f32(const __AGU f32_t * __restrict pSrcA, uint32_t nLenA, const __AGU f32_t * __restrict pSrcB, uint32_t nLenB, __AGU f32_t * __restrict pDst);
void _DSPLIB_XYCC dsp_correlate_q31(const __AGU q31_t * __restrict pSrcA, uint32_t nLenA, const __AGU q31_t * __restrict pSrcB, uint32_t nLenB, __AGU q31_t * __restrict pDst);
void _DSPLIB_XYCC dsp_correlate_q15(const __AGU q15_t * __restrict pSrcA, uint32_t nLenA, const __AGU q15_t * __restrict pSrcB, uint32_t nLenB, __AGU q15_t * __restrict pDst);
void _DSPLIB_XYCC dsp_correlate_q7(const __AGU q7_t * __restrict pSrcA, uint32_t nLenA, const __AGU q7_t * __restrict pSrcB, uint32_t nLenB, __AGU q7_t * __restrict pDst);

    //*** TRANSFORMS BLOCK ***

    //Complex FFT Radix 2
#if defined _ARCv2EM_XY_11D
#define dsp_cfft_getsize_f32(length) ((length)*sizeof(f32_t))
#define dsp_cfft_getsize_q31(length) ((length)*sizeof(q31_t))
#define dsp_cfft_getsize_q15(length) ((length)*sizeof(q15_t))
#else
#define dsp_cfft_getsize_f32(length) (0)
#define dsp_cfft_getsize_q31(length) (0)
#define dsp_cfft_getsize_q15(length) (0)
#endif
dsp_status _DSPLIB_XYCC dsp_cfft_init_f32(cfft_f32_t *handle, uint32_t length, __AGU f32_t * pState);
dsp_status _DSPLIB_XYCC dsp_cfft_init_q31(cfft_q31_t *handle, uint32_t length, __AGU uint32_t * pState);
dsp_status _DSPLIB_XYCC dsp_cfft_init_q15(cfft_q15_t *handle, uint32_t length, __AGU uint32_t * pState);
void dsp_cfft_delete_f32(cfft_f32_t *handle);
void dsp_cfft_delete_q31(cfft_q31_t *handle);
void dsp_cfft_delete_q15(cfft_q15_t *handle);
void _DSPLIB_XYCC dsp_cfft_f32(const cfft_f32_t *handle, const __AGU f32_t * input, __AGU f32_t * output);
void _DSPLIB_XYCC dsp_cfft_q31(const cfft_q31_t *handle, const __AGU q31_t * input, __AGU q31_t * output);
void _DSPLIB_XYCC dsp_cfft_q15(const cfft_q15_t *handle, const __AGU q15_t * input, __AGU q15_t * output);
void dsp_cfft_scaling_control_q15(cfft_q15_t* handle, dsp_transform_scaling scaling);

    //Complex Inverse FFT Radix 2
#if defined _ARCv2EM_XY_11D
#define dsp_cifft_getsize_f32(length) ((length)*sizeof(f32_t))
#define dsp_cifft_getsize_q31(length) ((length)*sizeof(q31_t))
#define dsp_cifft_getsize_q15(length) ((length)*sizeof(q15_t))
#else
#define dsp_cifft_getsize_f32(length) (0)
#define dsp_cifft_getsize_q31(length) (0)
#define dsp_cifft_getsize_q15(length) (0)
#endif
dsp_status _DSPLIB_XYCC dsp_cifft_init_f32(cfft_f32_t *handle, uint32_t length, __AGU f32_t * pState);
dsp_status _DSPLIB_XYCC dsp_cifft_init_q31(cfft_q31_t *handle, uint32_t length, __AGU uint32_t * pState);
dsp_status _DSPLIB_XYCC dsp_cifft_init_q15(cfft_q15_t *handle, uint32_t length, __AGU uint32_t * pState);
void dsp_cifft_delete_f32(cfft_f32_t *handle);
void dsp_cifft_delete_q31(cfft_q31_t *handle);
void dsp_cifft_delete_q15(cfft_q15_t *handle);
void _DSPLIB_XYCC dsp_cifft_f32(const cfft_f32_t *handle, const __AGU f32_t * input, __AGU f32_t * output);
void _DSPLIB_XYCC dsp_cifft_q31(const cfft_q31_t *handle, const __AGU q31_t * input, __AGU q31_t * output);
void _DSPLIB_XYCC dsp_cifft_q15(const cfft_q15_t *handle, const __AGU q15_t * input, __AGU q15_t * output);
void dsp_cifft_scaling_control_q15(cfft_q15_t* handle, dsp_transform_scaling scaling);

    //Real input + Complex output FFT
#ifdef _ARCv2EM_XY_11D
#define dsp_rfft_getsize_f32(length) (1*(length)*sizeof(f32_t) + dsp_cfft_getsize_f32((length)/2))
#define dsp_rfft_getsize_q31(length) (1*(length)*sizeof(q31_t) + dsp_cfft_getsize_q31((length)/2))
#define dsp_rfft_getsize_q15(length) (2*(length)*sizeof(q15_t) + dsp_cfft_getsize_q15((length)/2))
#else
#define dsp_rfft_getsize_f32(length) (dsp_cfft_getsize_f32((length)/2))
#define dsp_rfft_getsize_q31(length) (dsp_cfft_getsize_q31((length)/2))
#define dsp_rfft_getsize_q15(length) (dsp_cfft_getsize_q15((length)/2))
#endif
dsp_status _DSPLIB_XYCC dsp_rfft_init_f32(rfft_f32_t *handle, uint32_t length, __AGU f32_t * pState);
dsp_status _DSPLIB_XYCC dsp_rfft_init_q31(rfft_q31_t *handle, uint32_t length, __AGU uint32_t * pState);
dsp_status _DSPLIB_XYCC dsp_rfft_init_q15(rfft_q15_t *handle, uint32_t length, __AGU uint32_t * pState);
void dsp_rfft_delete_f32(rfft_f32_t *handle);
void dsp_rfft_delete_q31(rfft_q31_t *handle);
void dsp_rfft_delete_q15(rfft_q15_t *handle);
void _DSPLIB_XYCC dsp_rfft_f32(const rfft_f32_t *handle, const __AGU f32_t * input, __AGU f32_t * output);
void _DSPLIB_XYCC dsp_rfft_q31(const rfft_q31_t *handle, const __AGU q31_t * input, __AGU q31_t * output);
void _DSPLIB_XYCC dsp_rfft_q15(const rfft_q15_t *handle, const __AGU q15_t * input, __AGU q15_t * output);

    //Complex input + Real output Inverse FFT
#ifdef _ARCv2EM_XY_11D
#define dsp_rifft_getsize_f32(length) (2*(length)*sizeof(f32_t) + dsp_cifft_getsize_f32((length)/2))
#define dsp_rifft_getsize_q31(length) (2*(length)*sizeof(q31_t) + dsp_cifft_getsize_q31((length)/2))
#define dsp_rifft_getsize_q15(length) (3*(length)*sizeof(q15_t) + dsp_cifft_getsize_q15((length)/2))
#else
#define dsp_rifft_getsize_f32(length) ((length)*sizeof(f32_t) + dsp_cifft_getsize_f32((length)/2))
#define dsp_rifft_getsize_q31(length) ((length)*sizeof(q31_t) + dsp_cifft_getsize_q31((length)/2))
#define dsp_rifft_getsize_q15(length) ((length)*sizeof(q15_t) + dsp_cifft_getsize_q15((length)/2))
#endif
dsp_status _DSPLIB_XYCC dsp_rifft_init_f32(rfft_f32_t *handle, uint32_t length, __AGU f32_t * pState);
dsp_status _DSPLIB_XYCC dsp_rifft_init_q31(rfft_q31_t *handle, uint32_t length, __AGU uint32_t * pState);
dsp_status _DSPLIB_XYCC dsp_rifft_init_q15(rfft_q15_t *handle, uint32_t length, __AGU uint32_t * pState);
void dsp_rifft_delete_f32(rfft_f32_t *handle);
void dsp_rifft_delete_q31(rfft_q31_t *handle);
void dsp_rifft_delete_q15(rfft_q15_t *handle);
void _DSPLIB_XYCC dsp_rifft_f32(const rfft_f32_t *handle, const __AGU f32_t * input, __AGU f32_t * output);
void _DSPLIB_XYCC dsp_rifft_q31(const rfft_q31_t *handle, const __AGU q31_t * input, __AGU q31_t * output);
void _DSPLIB_XYCC dsp_rifft_q15(const rfft_q15_t *handle, const __AGU q15_t * input, __AGU q15_t * output);

    //DCT2 transform
#if defined _ARCv2EM_XY_11D
#define dsp_dct2_getsize_q31(length) (5*(length) * sizeof(q31_t)/2 + dsp_cfft_getsize_q31((length)/2))
#define dsp_dct2_getsize_q15(length) (5*(length) * sizeof(q15_t)/2 + dsp_cfft_getsize_q15((length)/2))
#else
#define dsp_dct2_getsize_q31(length) ((length) * sizeof(q31_t) + dsp_cfft_getsize_q31((length)/2))
#define dsp_dct2_getsize_q15(length) ((length) * sizeof(q15_t) + dsp_cfft_getsize_q15((length)/2))
#endif
dsp_status _DSPLIB_XYCC dsp_dct2_init_q31(dct2_q31_t *handle, uint32_t length, __AGU uint32_t * pState);
dsp_status _DSPLIB_XYCC dsp_dct2_init_q15(dct2_q15_t *handle, uint32_t length, __AGU uint32_t * pState);
void dsp_dct2_delete_q31(dct2_q31_t *handle);
void dsp_dct2_delete_q15(dct2_q15_t *handle);
void _DSPLIB_XYCC dsp_dct2_q31(const dct2_q31_t *handle, const __AGU q31_t * input, __AGU q31_t * output);
void _DSPLIB_XYCC dsp_dct2_q15(const dct2_q15_t *handle, const __AGU q15_t * input, __AGU q15_t * output);

    //DCT3 transform
#if defined _ARCv2EM_XY_11D
#define dsp_dct3_getsize_q31(length) (5*(length) * sizeof(q31_t)/2 + dsp_cfft_getsize_q31((length)/2))
#define dsp_dct3_getsize_q15(length) (5*(length) * sizeof(q15_t)/2 + dsp_cfft_getsize_q15((length)/2))
#else
#define dsp_dct3_getsize_q31(length) ((length) * sizeof(q31_t) + dsp_cfft_getsize_q31((length)/2))
#define dsp_dct3_getsize_q15(length) ((length) * sizeof(q15_t) + dsp_cfft_getsize_q15((length)/2))
#endif
dsp_status _DSPLIB_XYCC dsp_dct3_init_q31(dct3_q31_t *handle, uint32_t length, __AGU uint32_t * pState);
dsp_status _DSPLIB_XYCC dsp_dct3_init_q15(dct3_q15_t *handle, uint32_t length, __AGU uint32_t * pState);
void dsp_dct3_delete_q31(dct3_q31_t *handle);
void dsp_dct3_delete_q15(dct3_q15_t *handle);
void _DSPLIB_XYCC dsp_dct3_q31(const dct3_q31_t *handle, const __AGU q31_t * input, __AGU q31_t * output);
void _DSPLIB_XYCC dsp_dct3_q15(const dct3_q15_t *handle, const __AGU q15_t * input, __AGU q15_t * output);

    //DCT4 transform
#if defined(_ARC_AS210_mac32)
#define XY_DCT4_Q31_THRESHOLD ((XY_REGION_SIZE)/sizeof(q31_t))
#define dsp_dct4_getsize_q31(length) (((length) > XY_DCT4_Q31_THRESHOLD) ? dsp_cfft_getsize_q31((length)/2) : 0)
#elif defined(_ARCv2EM_XY_11D)
#define dsp_dct4_getsize_q31(length) (5*(length)*sizeof(q31_t)/2 + dsp_cfft_getsize_q31((length)/2))
#else
#define dsp_dct4_getsize_q31(length) ((length)*sizeof(q31_t) + dsp_cfft_getsize_q31((length)/2))
#endif

#if defined(_ARC_AS210_mac16)
#define XY_DCT4_Q15_THRESHOLD (((XY_REGION_SIZE))/sizeof(q15_t))
#define dsp_dct4_getsize_q15(length) (((length) > XY_DCT4_Q15_THRESHOLD) ? dsp_cfft_getsize_q15((length)/2) : 0)
#elif defined(_ARCv2EM_XY_11D)
#define dsp_dct4_getsize_q15(length) (5*(length)*sizeof(q15_t)/2 + dsp_cfft_getsize_q15((length)/2))
#else
#define dsp_dct4_getsize_q15(length) ((length)*sizeof(q15_t) + dsp_cfft_getsize_q15((length)/2))
#endif

dsp_status _DSPLIB_XYCC dsp_dct4_init_q31(dct4_q31_t *handle, uint32_t length, __AGU uint32_t * pState);
dsp_status _DSPLIB_XYCC dsp_dct4_init_q15(dct4_q15_t *handle, uint32_t length, __AGU uint32_t * pState);
void dsp_dct4_delete_q31(dct4_q31_t *handle);
void dsp_dct4_delete_q15(dct4_q15_t *handle);
void _DSPLIB_XYCC dsp_dct4_q31(const dct4_q31_t *handle, const __AGU q31_t * input, __AGU q31_t * output);
void _DSPLIB_XYCC dsp_dct4_q15(const dct4_q15_t *handle, const __AGU q15_t * input, __AGU q15_t * output);

    //MDCT transform
#if defined(_ARC_AS210_mac32)
#define XY_MDCT_Q31_THRESHOLD (((XY_REGION_SIZE))/sizeof(q31_t))
#define dsp_mdct_getsize_q31(length) (((length) > XY_MDCT_Q31_THRESHOLD) ? dsp_cfft_getsize_q31((length)/4) : 0)
#elif defined(_ARCv2EM_XY_11D)
#define dsp_mdct_getsize_q31(length) (5*(length)*sizeof(q31_t)/4 + dsp_cfft_getsize_q31((length)/4))
#else
#define dsp_mdct_getsize_q31(length) ((length)*sizeof(q31_t)/2 + dsp_cfft_getsize_q31((length)/4))
#endif

#if defined(_ARC_AS210_mac16)
#define XY_MDCT_Q15_THRESHOLD (((XY_REGION_SIZE))/sizeof(q15_t))
#define dsp_mdct_getsize_q15(length) (((length) > XY_MDCT_Q15_THRESHOLD) ? dsp_cfft_getsize_q15((length)/4) : 0)
#elif defined(_ARCv2EM_XY_11D)
#define dsp_mdct_getsize_q15(length) (5*(length)*sizeof(q15_t)/4 + dsp_cfft_getsize_q15((length)/4))
#else
#define dsp_mdct_getsize_q15(length) ((length)*sizeof(q15_t)/2 + dsp_cfft_getsize_q15((length)/4))
#endif

dsp_status _DSPLIB_XYCC dsp_mdct_init_q31(mdct_q31_t *handle, uint32_t length, __AGU uint32_t * pState);
dsp_status _DSPLIB_XYCC dsp_mdct_init_q15(mdct_q15_t *handle, uint32_t length, __AGU uint32_t * pState);
void dsp_mdct_delete_q31(mdct_q31_t *handle);
void dsp_mdct_delete_q15(mdct_q15_t *handle);
void _DSPLIB_XYCC dsp_mdct_q31(const mdct_q31_t *handle, const __AGU q31_t * input, __AGU q31_t * output);
void _DSPLIB_XYCC dsp_mdct_q15(const mdct_q15_t *handle, const __AGU q15_t * input, __AGU q15_t * output);

    //iMDCT transform
#if defined(_ARC_AS210_mac32)
#define XY_IMDCT_Q31_THRESHOLD (((XY_REGION_SIZE/2))/sizeof(q31_t))
#define dsp_imdct_getsize_q31(length) ((length > XY_IMDCT_Q31_THRESHOLD) ? dsp_cfft_getsize_q31((length)/2) : 0)
#elif defined(_ARCv2EM_XY_11D)
#define dsp_imdct_getsize_q31(length) (5*(length)*sizeof(q31_t)/2 + dsp_cfft_getsize_q31((length)/2))
#else
#define dsp_imdct_getsize_q31(length) ((length)*sizeof(q31_t) + dsp_cfft_getsize_q31((length)/2))
#endif

#if defined(_ARC_AS210_mac16)
#define XY_IMDCT_Q15_THRESHOLD (((XY_REGION_SIZE/2))/sizeof(q15_t))
#define dsp_imdct_getsize_q15(length) ((length > XY_IMDCT_Q15_THRESHOLD) ? dsp_cfft_getsize_q15((length)/2) : 0)
#elif defined(_ARCv2EM_XY_11D)
#define dsp_imdct_getsize_q15(length) (5*(length)*sizeof(q15_t)/2 + dsp_cfft_getsize_q15((length)/2))
#else
#define dsp_imdct_getsize_q15(length) ((length)*sizeof(q15_t) + dsp_cfft_getsize_q15((length)/2))
#endif

dsp_status _DSPLIB_XYCC dsp_imdct_init_q31(mdct_q31_t *handle, uint32_t length, __AGU uint32_t * pState);
dsp_status _DSPLIB_XYCC dsp_imdct_init_q15(mdct_q15_t *handle, uint32_t length, __AGU uint32_t * pState);
void dsp_imdct_delete_q31(mdct_q31_t *handle);
void dsp_imdct_delete_q15(mdct_q15_t *handle);
void _DSPLIB_XYCC dsp_imdct_q31(const mdct_q31_t *handle, const __AGU q31_t * input, __AGU q31_t * output);
void _DSPLIB_XYCC dsp_imdct_q15(const mdct_q15_t *handle, const __AGU q15_t * input, __AGU q15_t * output);

    //*** INTERPOLATION BLOCK ***

    //linear interpolation
q31_t dsp_linear_interp_q31(const q31_t  *pYTable,  int32_t x,  uint32_t tableSize);
q15_t dsp_linear_interp_q15(const q15_t  *pYTable,  int32_t x,  uint32_t tableSize);
q7_t dsp_linear_interp_q7(const q7_t  *pYTable,  int32_t x,  uint32_t tableSize);
f32_t dsp_linear_interp_f32(const f32_t  *pYTable,  f32_t x,  uint32_t tableSize);

    //bilinear interpolation
q31_t dsp_bilinear_interp_q31(const matrix_q31_t *pGrid, q31_t x, q31_t y);
q15_t dsp_bilinear_interp_q15(const matrix_q15_t *pGrid, q31_t x, q31_t y);
q7_t dsp_bilinear_interp_q7(const matrix_q7_t *pGrid, q31_t x, q31_t y);
f32_t dsp_bilinear_interp_f32(const matrix_f32_t *pGrid, f32_t x, f32_t y);

    //
#define dsp_pol_eval_getsize_f32(nOrder) (0)
#define dsp_pol_eval_getsize_q31(nOrder) (0)
#define dsp_pol_eval_getsize_q15(nOrder) (0)
#define dsp_pol_eval_getsize_q7(nOrder) (0)
dsp_status _DSPLIB_XYCC dsp_pol_eval_init_f32(pol_f32_t *pInst, uint16_t nCoeffs, const __AGU f32_t * pCoeffs);
dsp_status _DSPLIB_XYCC dsp_pol_eval_init_q31(pol_q31_t *pInst, uint16_t nCoeffs, const __AGU q31_t * pCoeffs, int32_t shift);
dsp_status _DSPLIB_XYCC dsp_pol_eval_init_q15(pol_q15_t *pInst, uint16_t nCoeffs, const __AGU q15_t * pCoeffs, int32_t shift);
dsp_status _DSPLIB_XYCC dsp_pol_eval_init_q7(pol_q7_t *pInst, uint16_t nCoeffs, const __AGU q7_t * pCoeffs, int32_t shift);
void dsp_pol_eval_delete_f32(pol_f32_t *pInst);
void dsp_pol_eval_delete_q31(pol_q31_t *pInst);
void dsp_pol_eval_delete_q15(pol_q15_t *pInst);
void dsp_pol_eval_delete_q7(pol_q7_t *pInst);
void _DSPLIB_XYCC dsp_pol_eval_f32(const pol_f32_t *pInst ,const __AGU f32_t * __restrict pSrc, __AGU f32_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_pol_eval_q31(const pol_q31_t *pInst ,const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_pol_eval_q15(const pol_q15_t *pInst ,const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_pol_eval_q7(const pol_q7_t *pInst ,const __AGU q7_t * __restrict pSrc, __AGU q7_t * __restrict pDst, uint32_t nSamples);

/////////////////////////////
// Additional wrappers 
////////////////////////////

//radix2 cFFT/ciFFT
//invFlag=0|1 - forward/inverse cFFT
dsp_status 	dsp_cfft_radix2_init_q15 (cfft_q15_t* handle, uint16_t length, uint8_t invFlag, uint8_t bitReverse_flag); 
void _DSPLIB_XYCC		dsp_cfft_radix2_q15( const cfft_q15_t *handle,  __AGU q15_t *  pInOut);

dsp_status 	dsp_cfft_radix2_init_q31 (cfft_q31_t* handle, uint16_t length, uint8_t invFlag, uint8_t bitReverse_flag);
void _DSPLIB_XYCC		dsp_cfft_radix2_q31( const cfft_q31_t *handle,  __AGU q31_t *  pInOut);

dsp_status dsp_rfft_init_q31_ext(rfft_q31_t *handle, void *temp0,  uint32_t length,  uint32_t invFlag,  uint32_t bitReverse_flag);
void _DSPLIB_XYCC       dsp_rfft_q31_ext(const rfft_q31_t* handle, const __AGU q31_t *  input, __AGU q31_t *  output);

dsp_status dsp_dct4_init_q31_ext(dct4_q31_t *inst,  void *temp0,  void *temp1,  uint16_t length,  uint16_t temp2,  q31_t normalize);
void _DSPLIB_XYCC       dsp_dct4_q31_ext(const dct4_q31_t *inst,  void *temp0,  __AGU q31_t *  pInPut);

dsp_status dsp_rfft_init_q15_ext(rfft_q15_t *handle, void *temp0,  uint32_t length,  uint32_t invFlag,  uint32_t bitReverse_flag);
void _DSPLIB_XYCC       dsp_rfft_q15_ext(const rfft_q15_t* handle, const __AGU q15_t *  input, __AGU q15_t *  output);

dsp_status dsp_dct4_init_q15_ext(dct4_q15_t *inst,  void *temp0,  void *temp1,  uint16_t length,  uint16_t temp2,  q15_t normalize);
void _DSPLIB_XYCC       dsp_dct4_q15_ext(const dct4_q15_t *inst,  void *temp0,  __AGU q15_t *  pInPut);

//sqrt
dsp_status _DSPLIB_NOXYCC dsp_sqrt_f32_ext(f32_t op, f32_t * pOut);
dsp_status _DSPLIB_NOXYCC dsp_sqrt_q31_ext(q31_t op, q31_t * pOut);
dsp_status _DSPLIB_NOXYCC dsp_sqrt_q15_ext(q15_t op, q15_t * pOut);

//"calculates sine. q.31 value [0; 1) is mapped to [-pi;pi)"
static _Inline q31_t _DSPLIB_NOXYCC dsp_sin_q31_ext(q31_t in) { return dsp_sin_q31((uint32_t)in << 1); };
static _Inline q15_t _DSPLIB_NOXYCC dsp_sin_q15_ext(q15_t in) { return dsp_sin_q15((uint16_t)in << 1); };

//"calculates cosine. q.31 value [0; 1) is mapped to [-pi;pi)"
static _Inline q31_t _DSPLIB_NOXYCC dsp_cos_q31_ext(q31_t in) { return dsp_cos_q31((uint32_t)in << 1); };
static _Inline q15_t _DSPLIB_NOXYCC dsp_cos_q15_ext(q15_t in) { return dsp_cos_q15((uint16_t)in << 1); };

//mat mult
dsp_status dsp_mat_mult_q15_ext(  const matrix_q15_t * pSrcA,  const matrix_q15_t * pSrcB,  matrix_q15_t * pDst,  q15_t * pState);

//filters
void _DSPLIB_XYCC dsp_fir_init_f32_ext(  fir_f32_t *inst,  uint16_t nTaps,  __AGU f32_t *  pCoeffs,  __AGU f32_t * pState,  uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_init_q7_ext(  fir_q7_t  *inst,  uint16_t nTaps,  __AGU q7_t *  pCoeffs,  __AGU q7_t * pState,  uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_init_q31_ext(  fir_q31_t *inst,  uint16_t nTaps,  __AGU q31_t *  pCoeffs,  __AGU q31_t * pState,  uint32_t nSamples);
dsp_status _DSPLIB_XYCC dsp_fir_init_q15_ext(  fir_q15_t *inst,  uint16_t nTaps,  __AGU q15_t *  pCoeffs,  __AGU q15_t * pState,  uint32_t nSamples);

dsp_status _DSPLIB_XYCC dsp_fir_decimate_init_f32_ext(fir_intdec_f32_t *inst, uint16_t nTaps, uint8_t decFactor, __AGU f32_t * pCoeffs, __AGU f32_t * pState, uint32_t nSamples);
dsp_status _DSPLIB_XYCC dsp_fir_decimate_init_q31_ext(fir_intdec_q31_t *inst, uint16_t nTaps, uint8_t decFactor, __AGU q31_t * pCoeffs, __AGU q31_t * pState, uint32_t nSamples);
dsp_status _DSPLIB_XYCC dsp_fir_decimate_init_q15_ext(fir_intdec_q15_t *inst, uint16_t nTaps, uint8_t decFactor, __AGU q15_t * pCoeffs, __AGU q15_t * pState, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_decimate_f32_ext(fir_intdec_f32_t *inst, const __AGU f32_t * pSrc, __AGU f32_t * pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_decimate_q31_ext(fir_intdec_q31_t *inst, const __AGU q31_t * __restrict pSrc, __AGU q31_t * __restrict pDst, uint32_t nSamples);
void _DSPLIB_XYCC dsp_fir_decimate_q15_ext(fir_intdec_q15_t *inst, const __AGU q15_t * __restrict pSrc, __AGU q15_t * __restrict pDst, uint32_t nSamples);

dsp_status _DSPLIB_XYCC dsp_fir_interpolate_init_f32_ext(fir_intdec_f32_t *inst, uint8_t intFactor, uint16_t nTaps, __AGU f32_t * pCoeffs, __AGU f32_t * pState, uint32_t nSamples);
dsp_status _DSPLIB_XYCC dsp_fir_interpolate_init_q31_ext(fir_intdec_q31_t *inst, uint8_t intFactor, uint16_t nTaps, __AGU q31_t * pCoeffs, __AGU q31_t * pState, uint32_t nSamples);
dsp_status _DSPLIB_XYCC dsp_fir_interpolate_init_q15_ext(fir_intdec_q15_t *inst, uint8_t intFactor, uint16_t nTaps, __AGU q15_t * pCoeffs, __AGU q15_t * pState, uint32_t nSamples);

void _DSPLIB_XYCC dsp_lms_init_f32_ext(lms_f32_t *inst, uint16_t numTaps, __AGU f32_t * pCoeffs, __AGU f32_t * pState, f32_t mu, uint32_t nSamples);
void _DSPLIB_XYCC dsp_lms_init_q31_ext(lms_q31_t *inst, uint16_t numTaps, __AGU q31_t * pCoeffs, __AGU q31_t * pState, q31_t mu, uint32_t nSamples, uint32_t postShift);
void _DSPLIB_XYCC dsp_lms_init_q15_ext(lms_q15_t *inst, uint16_t numTaps, __AGU q15_t * pCoeffs, __AGU q15_t * pState, q15_t mu, uint32_t nSamples, uint32_t postShift);

void _DSPLIB_XYCC dsp_iir_lattice_init_f32_ext(iir_lattice_f32_t *inst, uint16_t nStages, __AGU f32_t * pkCoeffs, __AGU f32_t * pvCoeffs, __AGU f32_t * pState, uint32_t nSamples);
void _DSPLIB_XYCC dsp_iir_lattice_init_q15_ext(iir_lattice_q15_t *inst, uint16_t nStages, __AGU q15_t * pkCoeffs, __AGU q15_t * pvCoeffs, __AGU q15_t * pState, uint32_t nSamples);
void _DSPLIB_XYCC dsp_iir_lattice_init_q31_ext(iir_lattice_q31_t *inst, uint16_t nStages, __AGU q31_t * pkCoeffs, __AGU q31_t * pvCoeffs, __AGU q31_t * pState, uint32_t nSamples);

//linear interpolation
f32_t dsp_linear_interp_f32_ext( dsp_linear_interp_instance_f32 *inst,  f32_t xx);

#if defined(DSPLIB_HEADER_EXTENSION)
#include "dsplib_extension.h"
#endif 

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif

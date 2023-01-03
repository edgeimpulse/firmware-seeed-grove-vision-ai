/*
 * lib_mem_desp.h
 *
 *  Created on: 2020/5/5
 *      Author: 903787
 */

#ifndef LIB_MEM_DSP_H_
#define LIB_MEM_DSP_H_

#include <ota.h>

typedef enum{
    LD_FALIED = -1,
    LD_SUCCESS = 0,
}LD_MEM_DSTOR_ERR;


typedef struct{
    uint32_t addr;
    uint32_t size;
}MEM_DESP_DATA_t;

static int lib_mem_desp_read(uint32_t *dest_addr);
int lib_mem_desp_parse(MEM_DESP_DATA_t mem_dsp_infor[], WEI_IMAGE_TYPE_E pat_type, uint32_t pat_count);
#endif


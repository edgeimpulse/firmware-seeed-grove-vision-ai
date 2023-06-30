#ifndef EI_ACCELETROMETER_H
#define EI_ACCELETROMETER_H

#include "firmware-sdk/ei_config_types.h"

/** Number of axis used and sample data format */
typedef float sample_format_t;
#define N_AXIS_SAMPLED			3
#define SIZEOF_N_AXIS_SAMPLED	(sizeof(sample_format_t) * N_AXIS_SAMPLED)

bool ei_accel_init(void);
void ei_accel_read_data(void);
bool ei_accel_sample_start(sampler_callback callback, float sample_interval_ms);
bool ei_accel_setup_data_sampling(void);

#endif /* EI_ACCELETROMETER_H */
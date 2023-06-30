#include "ei_accelerometer.h"
#include "ei_device_vision_ai.h"
#include "ei_sampler.h"
#include "edge-impulse-sdk/porting/ei_classifier_porting.h"
extern "C" {
#include "hx_drv_lsm6ds3.h"
};

static DEV_LSM6DS3_PTR lsm6ds3 = NULL;
sampler_callback inertial_cb_sampler;
static uint32_t sampling_interval;
static float accel_data[N_AXIS_SAMPLED];

#define CONVERT_G_TO_MS2    (9.80665f)
// measured on the device (see ei_accel_read_data)
#define ACC_SAMPLE_TIME_MS  (8)

static float convert_g_to_ms2(float axis)
{
    return((float)axis * CONVERT_G_TO_MS2);
}

bool ei_accel_init(void)
{
    lsm6ds3 = hx_drv_lsm6ds3_init((USE_SS_IIC_E)SS_IIC_0_ID);
    if(!lsm6ds3) {
        ei_printf("ERR: Failed to init LSM6DS3\n");
        return false;
    }

    lsm6ds3->settings.accel_range = 4;

    if (!hx_drv_lsm6ds3_begin(lsm6ds3))
    {
        free(lsm6ds3);
        lsm6ds3 = NULL;
        ei_printf("ERR: Failed to begin LSM6DS3\n");
        return false;
    }
    return true;
}

bool ei_accel_setup_data_sampling(void)
{
    EiDeviceInfo *dev = EiDeviceInfo::get_device();

    sensor_aq_payload_info payload = {
        // Unique device ID (optional), set this to e.g. MAC address or device EUI **if** your device has one
        dev->get_device_id().c_str(),
        // Device type (required), use the same device type for similar devices
        dev->get_device_type().c_str(),
        // How often new data is sampled in ms. (100Hz = every 10 ms.)
        dev->get_sample_interval_ms(),
        // The axes which you'll use. The units field needs to comply to SenML units (see https://www.iana.org/assignments/senml/senml.xhtml)
        { { "accX", "m/s2" }, { "accY", "m/s2" }, { "accZ", "m/s2" }, },
    };

    dev->set_state(eiStateErasingFlash);
    ei_sampler_start_sampling(&payload, &ei_accel_sample_start, SIZEOF_N_AXIS_SAMPLED);
    dev->set_state(eiStateIdle);

    return true;
}

void ei_accel_read_data(void)
{
    ei_sleep(sampling_interval - ACC_SAMPLE_TIME_MS);

    // Measurement procedure for tesiing purposes
    // uint64_t start = ei_read_timer_us();

    // wait for data to be available
    while(hx_drv_lsm6ds3_acc_available(lsm6ds3) == 0);

    accel_data[0] = convert_g_to_ms2(hx_drv_lsm6ds3_read_acc_x(lsm6ds3));
    accel_data[1] = convert_g_to_ms2(hx_drv_lsm6ds3_read_acc_y(lsm6ds3));
    accel_data[2] = convert_g_to_ms2(hx_drv_lsm6ds3_read_acc_z(lsm6ds3));

    inertial_cb_sampler((const void *)&accel_data[0], SIZEOF_N_AXIS_SAMPLED);
    // uint64_t end = ei_read_timer_us();
    // ei_printf("Took: %lu us\n", end - start);
}

bool ei_accel_sample_start(sampler_callback callsampler, float sample_interval_ms)
{
    EiDeviceInfo *dev = EiDeviceInfo::get_device();
    inertial_cb_sampler = callsampler;

    dev->set_sample_interval_ms(sample_interval_ms);
    sampling_interval = sample_interval_ms;

    dev->set_state(eiStateSampling);

    return true;
}

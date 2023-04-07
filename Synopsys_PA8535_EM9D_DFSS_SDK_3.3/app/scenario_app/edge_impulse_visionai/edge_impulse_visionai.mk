SCENARIO_APP_SUPPORT_LIST += $(APP_TYPE)

APPL_DEFINES += -DEDGE_IMPULSE_VISIONAI -DEI_PORTING_SEEED_VISION_AI

# Edge Impulse specific defines
APPL_DEFINES += -DEI_CLASSIFIER_ALLOCATION_STATIC_HIMAX_GNU
APPL_DEFINES += -DEI_DSP_IMAGE_BUFFER_STATIC_SIZE=1024
APPL_DEFINES += -DEIDSP_QUANTIZE_FILTERBANK=0

#boards
APPL_DEFINES += -DGROVE_VISION_AI

#if you don't use the OV camera, pls comment this code
APPL_DEFINES += -DCIS_OV_SENSOR -DCIS_OV2640_BAYER

LIB_SEL += arc_mli
LIB_SEL += sensordp pwrmgmt
LIB_SEL += i2c_comm

STACKSZ = 102400
HEAPSZ = 262144

USER_LINKER_SCRIPT_FILE = $(SCENARIO_APP_ROOT)/edge_impulse_visionai/edge_impulse_visionai.ld

SCENARIO_APP_SUPPORT_LIST +=	edge_impulse_visionai/configs \
								edge_impulse_visionai/debugger \
								edge_impulse_visionai/datapath \
								edge_impulse_visionai/drivers \
								edge_impulse_visionai/drivers/flash \
								edge_impulse_visionai/drivers/webusb \
								edge_impulse_visionai/drivers/sensor \
								edge_impulse_visionai/drivers/sensor/camera \
								edge_impulse_visionai/firmware-sdk \
								edge_impulse_visionai/firmware-sdk/at-server \
								edge_impulse_visionai/firmware-sdk/i2c-server \
								edge_impulse_visionai/firmware-sdk/jpeg \
								edge_impulse_visionai/ei-model/tflite-model \
								edge_impulse_visionai/ei-model \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/anomaly \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/classifier \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/porting \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/porting/seeed-vision-ai \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/dsp/kissfft \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/dsp/dct \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/dsp/image \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/tensorflow/lite/micro \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/tensorflow/lite/micro/memory_planner \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/tensorflow/lite/micro/kernels \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/tensorflow/lite/core/api \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/tensorflow/lite/ \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/tensorflow/lite/c \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/tensorflow/lite/kernels/internal \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/tensorflow/lite/kernels \
								edge_impulse_visionai/ei-model/edge-impulse-sdk/tensorflow/lite/micro/kernels/arc_mli \
								edge_impulse_visionai/inference \
								edge_impulse_visionai/src \


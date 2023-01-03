# directory declaration
LIB_CV_DIR = $(LIBRARIES_ROOT)/cv/tflitemicro_24

LIB_CV_ASMSRCDIR	= $(LIB_CV_DIR)
LIB_CV_INCDIR	= $(LIB_CV_DIR)
LIB_CV_INCDIR += $(LIB_CV_DIR)/third_party/gemmlowp
LIB_CV_INCDIR += $(LIB_CV_DIR)/third_party
LIB_CV_INCDIR += $(LIB_CV_DIR)/third_party/flatbuffers/include
LIB_CV_INCDIR += $(LIB_CV_DIR)/third_party/arc_mli_package/include
LIB_CV_INCDIR += $(LIB_CV_DIR)/third_party/arc_mli_package/include/api
LIB_CV_INCDIR += $(LIB_CV_DIR)/third_party/kissfft
LIB_CV_INCDIR += $(LIB_CV_DIR)/third_party/ruy
LIB_CV_INCDIR += $(LIB_CV_DIR)/tensorflow/lite/micro/kernels/arc_mli


LIB_CV_CSRCDIR = $(LIB_CV_DIR)/tensorflow/lite/c
LIB_CV_CCSRCSDIR =  \
$(LIB_CV_DIR)/tensorflow/lite/micro \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels \
$(LIB_CV_DIR)/tensorflow/lite/micro/memory_planner \
$(LIB_CV_DIR)/tensorflow/lite/core/api \
$(LIB_CV_DIR)/tensorflow/lite/kernels/internal \
$(LIB_CV_DIR)/tensorflow/lite/kernels \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/arc

# find all the source files in the target directories
LIB_CV_CSRCS = $(call get_csrcs, $(LIB_CV_CSRCDIR))
LIB_CV_CXXSRCS = $(call get_cxxsrcs, $(LIB_CV_CXXSRCSDIR))
LIB_CV_ASMSRCS = $(call get_asmsrcs, $(LIB_CV_ASMSRCDIR))

#tensorflow/lite/micro/kernels/conv.cc \
#tensorflow/lite/micro/kernels/fully_connected.cc \
#tensorflow/lite/micro/kernels/depthwise_conv.cc\
#tensorflow/lite/micro/kernels/pooling.cc \

LIB_CV_CCSRCS := \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/arc_mli/scratch_buf_mgr.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/arc_mli/scratch_buffers.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/arc_mli/conv.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/arc_mli/pooling.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/arc_mli/fully_connected.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/arc_mli/depthwise_conv.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/arc_mli/mli_slicers.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/micro_interpreter.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/micro_optional_debug_tools.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/micro_utils.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/micro_allocator.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/debug_log.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/micro_error_reporter.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/micro_string.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/test_helpers.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/memory_helpers.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/simple_memory_allocator.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/round.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/strided_slice.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/elementwise.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/maximum_minimum.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/all_ops_resolver.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/neg.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/unpack.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/concatenation.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/svdf.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/logistic.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/softmax.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/floor.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/pad.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/add.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/mul.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/quantize.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/dequantize.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/split.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/arg_min_max.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/ceil.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/activations.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/prelu.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/reshape.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/comparisons.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/logical.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/pack.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/circular_buffer.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/l2norm.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/reduce.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/resize_nearest_neighbor.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/sub.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/memory_planner/greedy_memory_planner.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/memory_planner/linear_memory_planner.cc \
$(LIB_CV_DIR)/tensorflow/lite/core/api/error_reporter.cc \
$(LIB_CV_DIR)/tensorflow/lite/core/api/flatbuffer_conversions.cc \
$(LIB_CV_DIR)/tensorflow/lite/core/api/op_resolver.cc \
$(LIB_CV_DIR)/tensorflow/lite/core/api/tensor_utils.cc \
$(LIB_CV_DIR)/tensorflow/lite/kernels/internal/quantization_util.cc \
$(LIB_CV_DIR)/tensorflow/lite/kernels/kernel_util.cc \
$(LIB_CV_DIR)/tensorflow/lite/micro/kernels/kernel_util.cc

ifeq ($(ALGO_TYPE), TFLITE_MICRO_GOOGLE_PERSON)
LIB_CV_CCSRCS += $(LIB_CV_DIR)/examples/person_detection_experimental/person_detect_model_data.cc
APPL_DEFINES += -DTFLITE_MICRO_GOOGLE_PERSON
endif
ifeq ($(ALGO_TYPE), TFLITE_MICRO_HIMAX_PERSON)
		ifeq (YOLO, $(findstring YOLO, $(APPL_DEFINES)))
			LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/yolo_PTQ_int8.cc
		endif
		ifeq (HX_VIP_YOMO, $(findstring HX_VIP_YOMO, $(APPL_DEFINES)))
			ifeq (HX_VIP_YOMO_20210115_E_PANA, $(findstring HX_VIP_YOMO_20210115_E_PANA, $(APPL_DEFINES)))
				LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/YOMO_E_PANA_20210115.cc
			else ifeq (HX_VIP_YOMO_20210121_PBR_PANA, $(findstring HX_VIP_YOMO_20210121_PBR_PANA, $(APPL_DEFINES)))
				LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/YOMO_PBR_AoS96_PANA_20210121.cc
			else ifeq (HX_VIP_YOMO_DOOR_DETECT, $(findstring HX_VIP_YOMO_DOOR_DETECT, $(APPL_DEFINES)))
				LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/YOMO_DOOR_DETECT.cc
				
			# static hand gesture
			else ifeq (HX_VIP_STATIC_GESTURE_320x240, $(findstring HX_VIP_STATIC_GESTURE_320x240, $(APPL_DEFINES)))
				LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/HGR_tiny_hands_3_mix_44_L.cc
			else ifeq (HX_VIP_STATIC_GESTURE_04_V2_320x200, $(findstring HX_VIP_STATIC_GESTURE_04_V2_320x200, $(APPL_DEFINES)))
				LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/tiny_hands_3_mix_04_MobileNetV2.cc
			else ifeq (HX_VIP_STATIC_GESTURE_06_V2_320x200, $(findstring HX_VIP_STATIC_GESTURE_06_V2_320x200, $(APPL_DEFINES)))
				LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/tiny_hands_3_mix_06_MobileNetV2.cc
			else ifeq (HX_VIP_STATIC_GESTURE_07_V3_320x200, $(findstring HX_VIP_STATIC_GESTURE_07_V3_320x200, $(APPL_DEFINES)))
				LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/tiny_hands_3_mix_07_MobileNetV3_S.cc
			else ifeq (HX_VIP_STATIC_GESTURE_91_320x240, $(findstring HX_VIP_STATIC_GESTURE_91_320x240, $(APPL_DEFINES)))
				LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/vip_gesture_mix_91_MobileNetV2.cc
				
				
				
				
			else ifeq (HX_VIP_YOMO_AMR_ROI, $(findstring HX_VIP_YOMO_AMR_ROI, $(APPL_DEFINES)))
				ifneq (LOAD_FROM_BIN_FILE, $(findstring LOAD_FROM_BIN_FILE, $(APPL_DEFINES)))
					ifeq (AMR_DEMO_DATASET, $(findstring AMR_DEMO_DATASET, $(APPL_DEFINES)))
						LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/AMR_ROI_DEMO_DATASET_10CM.cc
						LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/AMR_CR_DEMO_DATASET_10CM.cc
					else ifeq (AMR_ORIG_DATASET, $(findstring AMR_ORIG_DATASET, $(APPL_DEFINES)))
						LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/AMR_ROI_ORIG_DATASET.cc
						LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/AMR_CR_ORIG_DATASET.cc
					else ifeq (AMR_CR_DEMO_FIX_LAYOUT_5CM_DATASET, $(findstring AMR_CR_DEMO_FIX_LAYOUT_5CM_DATASET, $(APPL_DEFINES)))
						LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/AMR_CR_DEMO_FIX_LAYOUT_5CM.cc
					else ifeq (AMR_CR_FIX_LAYOUT_MID_DATASET, $(findstring AMR_CR_FIX_LAYOUT_MID_DATASET, $(APPL_DEFINES)))
						ifeq (AMR_CR_FIX_LAYOUT_MID_SWITCH_SECK_MODEL, $(findstring AMR_CR_FIX_LAYOUT_MID_SWITCH_SECK_MODEL, $(APPL_DEFINES)))
							LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/AMR_CR_FIX_LAYOUT_MID_CUSTOMER.cc
						else ifeq (AMR_CR_FIX_LAYOUT_MID_WATERFOG_SWITCH_SECK_MODEL, $(findstring AMR_CR_FIX_LAYOUT_MID_WATERFOG_SWITCH_SECK_MODEL, $(APPL_DEFINES)))
							LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/AMR_CR_FIX_LAYOUT_MID_SECK_WATERFOG.cc
						else ifeq (AMR_CR_LUODING_MODEL, $(findstring AMR_CR_LUODING_MODEL, $(APPL_DEFINES)))
							LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/AMR_CR_LUODING_WATERFOG.cc
						else ifeq (AMR_CR_HIMAX_MODEL, $(findstring AMR_CR_HIMAX_MODEL, $(APPL_DEFINES)))
							LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/AMR_CR_FIX_LAYOUT_MID.cc
						endif
					endif
				endif
			endif
		else
			LIB_CV_CCSRCS += $(LIBRARIES_ROOT)/cv/himax/model/yolo_PTQ_int8.cc
		endif
	
APPL_DEFINES += -DTFLITE_MICRO_HIMAX_PERSON
endif

# get object files
LIB_CV_COBJS = $(call get_relobjs, $(LIB_CV_CSRCS))
LIB_CV_CXXOBJS = $(call get_relobjs, $(LIB_CV_CXXSRCS))
LIB_CV_CCOBJS = $(call get_relobjs, $(LIB_CV_CCSRCS))
LIB_CV_ASMOBJS = $(call get_relobjs, $(LIB_CV_ASMSRCS))
LIB_CV_OBJS = $(LIB_CV_COBJS) $(LIB_CV_ASMOBJS) $(LIB_CV_CXXOBJS) $(LIB_CV_CCOBJS)

#CV_CXXFLAGS += -O3 -DNDEBUG -g -DTF_LITE_STATIC_MEMORY -DEMBARC_TCF_GENERATED -fno-rtti -Hnocopyr -O3 -Hpurge -Hcl -fslp-vectorize-aggressive -ffunction-sections -fdata-sections
#CV_CCFLAGS +=  -DNDEBUG -g -DTF_LITE_STATIC_MEMORY -DEMBARC_TCF_GENERATED -Hnocopyr -O3 -Hpurge -Hcl -fslp-vectorize-aggressive -ffunction-sections -fdata-sections
#CV_CXXFLAGS += -DSCRATCH_MEM_Z_SIZE=0x10000

APPL_DEFINES += -O3 -DNDEBUG -g -DTF_LITE_STATIC_MEMORY -DEMBARC_TCF_GENERATED -O3 -ffunction-sections -fdata-sections
APPL_DEFINES +=  -DNDEBUG -g -DTF_LITE_STATIC_MEMORY -DEMBARC_TCF_GENERATED -O3 -ffunction-sections -fdata-sections
ifeq ($(TOOLCHAIN), mw)
APPL_DEFINES += -fno-rtti -Hnocopyr -Hpurge -Hcl -fslp-vectorize-aggressive
APPL_DEFINES += -Hnocopyr -Hpurge -Hcl -fslp-vectorize-aggressive
endif

APPL_DEFINES += -DSCRATCH_MEM_Z_SIZE=0x10000

# extra macros to be defined
LIB_CV_DEFINES = -DLIB_TFLITEMICRO

# genearte library
CV_LIB = $(OUT_DIR)/libtflitemicro_24.a

LIB_INCDIR += $(LIB_CV_INCDIR)

ifeq ($(TOOLCHAIN), mw)
	ifeq ($(ALGO_TYPE), TFLITE_MICRO_HIMAX_PERSON)
		override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_wo_audio.ld
		ifeq (OS_FREERTOS, $(findstring OS_FREERTOS, $(OS_DEFINES)))
			ifeq ($(ALGO_TYPE_AUDIO), CYBERON)
				ifeq (HX_VIP_YOMO, $(findstring HX_VIP_YOMO, $(APPL_DEFINES)))
					ifeq (HX_VIP_CDM_GRAD, $(findstring HX_VIP_CDM_GRAD, $(APPL_DEFINES)))
						override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_w_audio_cdm.ld
					else ifeq (HX_VIP_CDM_PIX, $(findstring HX_VIP_CDM_PIX, $(APPL_DEFINES)))
						override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_w_audio_cdm.ld
					else
						override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_w_audio.ld
					endif
				else
					override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_w_audio.ld
				endif
			else
				ifeq (HX_VIP_YOMO, $(findstring HX_VIP_YOMO, $(APPL_DEFINES)))
					ifeq (HX_VIP_CDM_GRAD, $(findstring HX_VIP_CDM_GRAD, $(APPL_DEFINES)))
						override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_wo_audio_cdm.ld
					else ifeq (HX_VIP_CDM_PIX, $(findstring HX_VIP_CDM_PIX, $(APPL_DEFINES)))
						override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_wo_audio_cdm.ld
					else
						override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_wo_audio.ld
					endif
				else
					override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_wo_audio.ld
				endif
			endif
		else
			override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_wo_audio.ld
			ifeq (AIOT_HGR_VIP, $(findstring AIOT_HGR_VIP, $(APPL_DEFINES)))
			    override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_wo_audio_HGR.ld
			endif
		endif
	else
		ifeq ($(ALGO_TYPE_AUDIO), CYBERON)
			override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_w_audio.ld
		else
			override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_rtos_wo_audio.ld
		endif
	endif
else
	override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_gnu_tflitemicro_wo_audio.ld
endif
#APPL_DEFINES += -DTWO_BSS

ifeq ($(TOOLCHAIN), mw)
	ifeq (SAMPLE_CODE_WATER_METER, $(findstring SAMPLE_CODE_WATER_METER, $(APPL_DEFINES)))
		override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_mw_tflitemicro_sample_code_water_meter.ld
	endif
endif	

ifeq "$(HOST_OS)" "Windows"
MLI_LIB = $(BOARD_OUT_DIR)\$(BUILD_INFO)\libmli.a
PREBUILT_MLI_LIB = .\library\cv\tflitemicro_24\third_party\arc_mli_package\bin\himax_arcem9d_r16\release\libmli.a
else
MLI_LIB = $(BOARD_OUT_DIR)/$(BUILD_INFO)/libmli.a
PREBUILT_MLI_LIB = ./library/cv/tflitemicro_24/third_party/arc_mli_package/bin/himax_arcem9d_r16/release/libmli.a
endif

$(MLI_LIB) :
	$(CP) $(PREBUILT_MLI_LIB) $(MLI_LIB)

# library generation rule
ifeq ($(LIB_CV_PREBUILT), 1)
ifeq "$(HOST_OS)" "Windows"
CV_LIB = $(BOARD_OUT_DIR)\$(BUILD_INFO)\libtflitemicro_24.a
else
CV_LIB = $(BOARD_OUT_DIR)/$(BUILD_INFO)/libtflitemicro_24.a
endif
#
ifeq "$(HOST_OS)" "Windows"
ifeq ($(ALGO_TYPE), TFLITE_MICRO_GOOGLE_PERSON)
CV_PREBUILT_LIB = .\library\cv\tflitemicro_24\prebuilt_lib\libtflitemicro_google_person.a
endif
ifeq ($(ALGO_TYPE), TFLITE_MICRO_HIMAX_PERSON)
CV_PREBUILT_LIB = .\library\cv\himax\prebuilt_lib\libtflitemicro_24_himax_person.a
endif
else
ifeq ($(ALGO_TYPE), TFLITE_MICRO_GOOGLE_PERSON)
	ifeq ($(TOOLCHAIN), mw)
		CV_PREBUILT_LIB = ./library/cv/tflitemicro_24/prebuilt_lib/libtflitemicro_google_person.a
	else
		CV_PREBUILT_LIB = ./library/cv/tflitemicro_24/prebuilt_lib/libtflitemicro_google_person_gnu.a
	endif
endif
ifeq ($(ALGO_TYPE), TFLITE_MICRO_HIMAX_PERSON)
	ifeq ($(TOOLCHAIN), mw)
		CV_PREBUILT_LIB = ./library/cv/himax/prebuilt_lib/libtflitemicro_24_himax_person.a
	else
		CV_PREBUILT_LIB = ./library/cv/himax/prebuilt_lib/libtflitemicro_24_himax_person_gnu.a
	endif
endif
endif

$(CV_LIB) :
	$(CP) $(CV_PREBUILT_LIB) $(CV_LIB)
else
# specific compile rules
# user can add rules to compile this middleware
# if not rules specified to this middleware, it will use default compiling rules

# Middleware Definitions
CV_LIB_CSRCDIR += $(LIB_CV_CSRCDIR)
CV_LIB_CXXSRCDIR += $(LIB_CV_CXXSRCDIR)
CV_LIB_CCSRCDIR += $(LIB_CV_CCSRCDIR)
CV_LIB_ASMSRCDIR += $(LIB_CV_ASMSRCDIR)

CV_LIB_CSRCS += $(LIB_CV_CSRCS)
CV_LIB_CXXSRCS += $(LIB_CV_CXXSRCS)
CV_LIB_CCSRCS += $(LIB_CV_CCSRCS)
CV_LIB_ASMSRCS += $(LIB_CV_ASMSRCS)
CV_LIB_ALLSRCS += $(LIB_CV_CSRCS) $(LIB_CV_ASMSRCS) $(CV_LIB_CXXSRCS) $(CV_LIB_CCSRCS)

CV_LIB_COBJS += $(LIB_CV_COBJS)
CV_LIB_CXXOBJS += $(LIB_CV_CXXOBJS)
CV_LIB_CCOBJS += $(LIB_CV_CCOBJS)
CV_LIB_ASMOBJS += $(LIB_CV_ASMOBJS)
CV_LIB_ALLOBJS += $(LIB_CV_OBJS)

CV_LIB_DEFINES += $(LIB_CV_DEFINES)
CV_LIB_DEPS += $(LIB_CV_DEPS)
CV_LIB_LIBS += $(LIB_LIB_CV)

$(CV_LIB): $(LIB_CV_OBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(LIB_CV_OBJS)
endif

override LIB_BSS_DIR = $(LIB_CV_DIR)/bss

override LIB_BSS_ASMSRCDIR	= $(LIB_BSS_DIR)
override LIB_BSS_CSRCDIR	= $(LIB_BSS_DIR)
override LIB_BSS_CXXSRCSDIR    = $(LIB_BSS_DIR)
override LIB_BSS_INCDIR	= $(LIB_BSS_DIR)

# find all the source files in the target directories
override LIB_BSS_CSRCS = $(call get_csrcs, $(LIB_BSS_CSRCDIR))
override LIB_BSS_CXXSRCS = $(call get_cxxsrcs, $(LIB_BSS_CXXSRCSDIR))
override LIB_BSS_ASMSRCS = $(call get_asmsrcs, $(LIB_BSS_ASMSRCDIR))

# get object files
override LIB_BSS_COBJS = $(call get_relobjs, $(LIB_BSS_CSRCS))
override LIB_BSS_CXXOBJS = $(call get_relobjs, $(LIB_BSS_CXXSRCS))
override LIB_BSS_ASMOBJS = $(call get_relobjs, $(LIB_BSS_ASMSRCS))
override LIB_BSS_OBJS = $(LIB_BSS_COBJS) $(LIB_BSS_ASMOBJS) $(LIB_BSS_CXXOBJS)

# get dependency files
override LIB_BSS_DEPS = $(call get_deps, $(LIB_BSS_OBJS))

# extra macros to be defined
override LIB_BSS_DEFINES = -DLIB_BSS_HANDLE

# genearte library
override BSS_LIB = $(OUT_DIR)/libbss.a

LIB_INCDIR += $(LIB_BSS_INCDIR)

override BSS_LIB_CSRCDIR = $(LIB_BSS_CSRCDIR)
override BSS_LIB_CXXSRCDIR = $(LIB_BSS_CXXSRCDIR)
override BSS_LIB_ASMSRCDIR = $(LIB_BSS_ASMSRCDIR)

override BSS_LIB_CSRCS = $(LIB_BSS_CSRCS)
override BSS_LIB_CXXSRCS = $(LIB_BSS_CXXSRCS)
override BSS_LIB_ASMSRCS = $(LIB_BSS_ASMSRCS)
override BSS_LIB_ALLSRCS = $(LIB_BSS_CSRCS) $(LIB_BSS_ASMSRCS)

override BSS_LIB_COBJS = $(LIB_BSS_COBJS)
override BSS_LIB_CXXOBJS = $(LIB_BSS_CXXOBJS)
override BSS_LIB_ASMOBJS = $(LIB_BSS_ASMOBJS)
override BSS_LIB_ALLOBJS = $(LIB_BSS_OBJS)

override BSS_LIB_DEFINES = $(LIB_BSS_DEFINES)
override BSS_LIB_DEPS = $(LIB_BSS_DEPS)
override BSS_LIB_LIBS = $(LIB_LIB_BSS)

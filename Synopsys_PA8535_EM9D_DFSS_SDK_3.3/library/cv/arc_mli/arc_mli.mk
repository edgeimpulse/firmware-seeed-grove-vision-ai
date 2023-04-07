# directory declaration
LIB_ARC_MLI_DIR = $(LIBRARIES_ROOT)/cv/arc_mli

LIB_ARC_MLI_INCDIR	= $(LIB_ARC_MLI_DIR)
LIB_ARC_MLI_INCDIR += $(LIB_ARC_MLI_DIR)/arc_mli_package/include
LIB_ARC_MLI_INCDIR += $(LIB_ARC_MLI_DIR)/arc_mli_package/include/api

APPL_DEFINES += -DNDEBUG -g -DTF_LITE_STATIC_MEMORY -DEMBARC_TCF_GENERATED -Os -ffunction-sections -fdata-sections
APPL_DEFINES += -DSCRATCH_MEM_Z_SIZE=0

LIB_INCDIR += $(LIB_ARC_MLI_INCDIR)

# override LINKER_SCRIPT_FILE := $(LIBRARIES_ROOT)/cv/himax/linker_script/linker_template_gnu_tflitemicro_wo_audio.ld

ifeq "$(HOST_OS)" "Windows"
MLI_LIB = $(BOARD_OUT_DIR)\$(BUILD_INFO)\libmli.a
PREBUILT_MLI_LIB = .\library\cv\arc_mli\arc_mli_package\bin\himax_arcem9d_r16\release\libmli.a
else
MLI_LIB = $(BOARD_OUT_DIR)/$(BUILD_INFO)/libmli.a
PREBUILT_MLI_LIB = ./library/cv/arc_mli/arc_mli_package/bin/himax_arcem9d_r16/release/libmli.a
endif

$(MLI_LIB) :
	$(CP) $(PREBUILT_MLI_LIB) $(MLI_LIB)

# override LIB_BSS_DIR = $(LIB_CV_DIR)/bss

# override LIB_BSS_ASMSRCDIR	= $(LIB_BSS_DIR)
# override LIB_BSS_CSRCDIR	= $(LIB_BSS_DIR)
# override LIB_BSS_CXXSRCSDIR    = $(LIB_BSS_DIR)
# override LIB_BSS_INCDIR	= $(LIB_BSS_DIR)

# # find all the source files in the target directories
# override LIB_BSS_CSRCS = $(call get_csrcs, $(LIB_BSS_CSRCDIR))
# override LIB_BSS_CXXSRCS = $(call get_cxxsrcs, $(LIB_BSS_CXXSRCSDIR))
# override LIB_BSS_ASMSRCS = $(call get_asmsrcs, $(LIB_BSS_ASMSRCDIR))

# # get object files
# override LIB_BSS_COBJS = $(call get_relobjs, $(LIB_BSS_CSRCS))
# override LIB_BSS_CXXOBJS = $(call get_relobjs, $(LIB_BSS_CXXSRCS))
# override LIB_BSS_ASMOBJS = $(call get_relobjs, $(LIB_BSS_ASMSRCS))
# override LIB_BSS_OBJS = $(LIB_BSS_COBJS) $(LIB_BSS_ASMOBJS) $(LIB_BSS_CXXOBJS)

# # get dependency files
# override LIB_BSS_DEPS = $(call get_deps, $(LIB_BSS_OBJS))

# extra macros to be defined
# override LIB_BSS_DEFINES = -DLIB_BSS_HANDLE

# genearte library
# override BSS_LIB = $(OUT_DIR)/libbss.a

# LIB_INCDIR += $(LIB_BSS_INCDIR)

# override BSS_LIB_CSRCDIR = $(LIB_BSS_CSRCDIR)
# override BSS_LIB_CXXSRCDIR = $(LIB_BSS_CXXSRCDIR)
# override BSS_LIB_ASMSRCDIR = $(LIB_BSS_ASMSRCDIR)

# override BSS_LIB_CSRCS = $(LIB_BSS_CSRCS)
# override BSS_LIB_CXXSRCS = $(LIB_BSS_CXXSRCS)
# override BSS_LIB_ASMSRCS = $(LIB_BSS_ASMSRCS)
# override BSS_LIB_ALLSRCS = $(LIB_BSS_CSRCS) $(LIB_BSS_ASMSRCS)

# override BSS_LIB_COBJS = $(LIB_BSS_COBJS)
# override BSS_LIB_CXXOBJS = $(LIB_BSS_CXXOBJS)
# override BSS_LIB_ASMOBJS = $(LIB_BSS_ASMOBJS)
# override BSS_LIB_ALLOBJS = $(LIB_BSS_OBJS)

# override BSS_LIB_DEFINES = $(LIB_BSS_DEFINES)
# override BSS_LIB_DEPS = $(LIB_BSS_DEPS)
# override BSS_LIB_LIBS = $(LIB_LIB_BSS)

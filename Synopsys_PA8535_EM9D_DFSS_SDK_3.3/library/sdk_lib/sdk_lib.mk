# directory declaration
LIB_TFLM_SDK_DIR = $(LIBRARIES_ROOT)/sdk_lib
LIB_TFLM_SDK_OTADIR = $(LIBRARIES_ROOT)/ota
$(warning build sdk lib) 
LIB_TFLM_SDK_ASMSRCDIR	= $(LIB_TFLM_SDK_DIR)
LIB_TFLM_SDK_CSRCDIR	= $(LIB_TFLM_SDK_DIR)
LIB_TFLM_SDK_CXXSRCSDIR    = $(LIB_TFLM_SDK_DIR)
LIB_TFLM_SDK_INCDIR	= $(LIB_TFLM_SDK_DIR) 
LIB_TFLM_SDK_INCDIR	+= $(LIB_TFLM_SDK_DIR)/internal_inc
LIB_TFLM_SDK_INCDIR += $(LIB_TFLM_SDK_OTADIR)
# find all the source files in the target directories
LIB_TFLM_SDK_CSRCS = $(call get_csrcs, $(LIB_TFLM_SDK_CSRCDIR))
LIB_TFLM_SDK_CXXSRCS = $(call get_cxxsrcs, $(LIB_TFLM_SDK_CXXSRCSDIR))
LIB_TFLM_SDK_ASMSRCS = $(call get_asmsrcs, $(LIB_TFLM_SDK_ASMSRCDIR))

# get object files
LIB_TFLM_SDK_COBJS = $(call get_relobjs, $(LIB_TFLM_SDK_CSRCS))
LIB_TFLM_SDK_CXXOBJS = $(call get_relobjs, $(LIB_TFLM_SDK_CXXSRCS))
LIB_TFLM_SDK_ASMOBJS = $(call get_relobjs, $(LIB_TFLM_SDK_ASMSRCS))
LIB_TFLM_SDK_OBJS = $(LIB_TFLM_SDK_COBJS) $(LIB_TFLM_SDK_ASMOBJS) $(LIB_TFLM_SDK_CXXOBJS)

# get dependency files
LIB_TFLM_SDK_DEPS = $(call get_deps, $(LIB_TFLM_SDK_OBJS))

# extra macros to be defined
LIB_TFLM_SDK_DEFINES = -DLIB_TFLM_SDK

# genearte library
LIB_LIB_TFLM_SDK = $(OUT_DIR)/liblibtflm.a


# library generation rule
$(LIB_LIB_TFLM_SDK): $(LIB_TFLM_SDK_OBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(LIB_TFLM_SDK_OBJS)

# specific compile rules
# user can add rules to compile this middleware
# if not rules specified to this middleware, it will use default compiling rules

# Middleware Definitions
LIB_INCDIR += $(LIB_TFLM_SDK_INCDIR)
LIB_CSRCDIR += $(LIB_TFLM_SDK_CSRCDIR)
LIB_CXXSRCDIR += $(LIB_TFLM_SDK_CXXSRCDIR)
LIB_ASMSRCDIR += $(LIB_TFLM_SDK_ASMSRCDIR)

LIB_CSRCS += $(LIB_TFLM_SDK_CSRCS)
LIB_CXXSRCS += $(LIB_TFLM_SDK_CXXSRCS)
LIB_ASMSRCS += $(LIB_TFLM_SDK_ASMSRCS)
LIB_ALLSRCS += $(LIB_TFLM_SDK_CSRCS) $(LIB_TFLM_SDK_ASMSRCS)

LIB_COBJS += $(LIB_TFLM_SDK_COBJS)
LIB_CXXOBJS += $(LIB_TFLM_SDK_CXXOBJS)
LIB_ASMOBJS += $(LIB_TFLM_SDK_ASMOBJS)

# Comment code below to exclude this libray from 'libembarc.a'.
#LIB_ALLOBJS += $(LIB_TFLM_SDK_OBJS)

LIB_DEFINES += $(LIB_TFLM_SDK_DEFINES)
LIB_DEPS += $(LIB_TFLM_SDK_DEPS)

# Comment code below to exclude this libray from 'libembarc.a'.
#LIB_LIBS += $(LIB_LIB_TFLM_SDK)

# Add 'OPEN_LIBS' as dependency of creating *.elf rather than adding it to 'libembacr.a'
OPEN_LIBS += $(LIB_LIB_TFLM_SDK)
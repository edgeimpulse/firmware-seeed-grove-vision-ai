# directory declaration
LIB_DSP_DIR = $(LIBRARIES_ROOT)/dsp

LIB_DSP_ASMSRCDIR	= $(LIB_DSP_DIR) $(LIB_DSP_DIR)/math
LIB_DSP_CSRCDIR	= $(LIB_DSP_DIR) $(LIB_DSP_DIR)/math
LIB_DSP_INCDIR	= $(LIB_DSP_DIR) $(LIB_DSP_DIR)/math

# find all the source files in the target directories
LIB_DSP_CSRCS = $(call get_csrcs, $(LIB_DSP_CSRCDIR))
LIB_DSP_ASMSRCS = $(call get_asmsrcs, $(LIB_DSP_ASMSRCDIR))

# get object files
LIB_DSP_COBJS = $(call get_relobjs, $(LIB_DSP_CSRCS))
LIB_DSP_ASMOBJS = $(call get_relobjs, $(LIB_DSP_ASMSRCS))
LIB_DSP_OBJS = $(LIB_DSP_COBJS) $(LIB_DSP_ASMOBJS)

# get dependency files
LIB_DSP_DEPS = $(call get_deps, $(LIB_DSP_OBJS))

# extra macros to be defined
LIB_DSP_DEFINES = -DLIB_DSP

# genearte library
LIB_LIB_DSP = $(OUT_DIR)/liblibdsp.a


# library generation rule
$(LIB_LIB_DSP): $(LIB_DSP_OBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(LIB_DSP_OBJS)

# specific compile rules
# user can add rules to compile this middleware
# if not rules specified to this middleware, it will use default compiling rules

# Middleware Definitions
LIB_INCDIR += $(LIB_DSP_INCDIR)
LIB_CSRCDIR += $(LIB_DSP_CSRCDIR)
LIB_ASMSRCDIR += $(LIB_DSP_ASMSRCDIR)

LIB_CSRCS += $(LIB_DSP_CSRCS)
LIB_CXXSRCS +=
LIB_ASMSRCS += $(LIB_DSP_ASMSRCS)
LIB_ALLSRCS += $(LIB_DSP_CSRCS) $(LIB_DSP_ASMSRCS)

LIB_COBJS += $(LIB_DSP_COBJS)
LIB_CXXOBJS +=
LIB_ASMOBJS += $(LIB_DSP_ASMOBJS)
LIB_ALLOBJS += $(LIB_DSP_OBJS)

LIB_DEFINES += $(LIB_DSP_DEFINES)
LIB_DEPS += $(LIB_DSP_DEPS)
LIB_LIBS += $(LIB_LIB_DSP)
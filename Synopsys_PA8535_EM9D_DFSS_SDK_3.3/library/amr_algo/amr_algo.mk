# directory declaration
LIB_AMR_ALGO_DIR = $(LIBRARIES_ROOT)/amr_algo

LIB_AMR_ALGO_ASMSRCDIR	= $(LIB_AMR_ALGO_DIR)
LIB_AMR_ALGO_CSRCDIR	= $(LIB_AMR_ALGO_DIR)
LIB_AMR_ALGO_CXXSRCSDIR    = $(LIB_AMR_ALGO_DIR)
LIB_AMR_ALGO_INCDIR	= $(LIB_AMR_ALGO_DIR)

# find all the source files in the target directories
LIB_AMR_ALGO_CSRCS = $(call get_csrcs, $(LIB_AMR_ALGO_CSRCDIR))
LIB_AMR_ALGO_CXXSRCS = $(call get_cxxsrcs, $(LIB_AMR_ALGO_CXXSRCSDIR))
LIB_AMR_ALGO_ASMSRCS = $(call get_asmsrcs, $(LIB_AMR_ALGO_ASMSRCDIR))

LIB_AMR_ALGO_CCSRCS := \
$(LIB_AMR_ALGO_DIR)/AMR_bboxs_postprocessing.cc \
$(LIB_AMR_ALGO_DIR)/hx_vip_algo.cc \
$(LIB_AMR_ALGO_DIR)/hx_vip_yomo.cc


# get object files
LIB_AMR_ALGO_COBJS = $(call get_relobjs, $(LIB_AMR_ALGO_CSRCS))
LIB_AMR_ALGO_CXXOBJS = $(call get_relobjs, $(LIB_AMR_ALGO_CXXSRCS))
LIB_AMR_ALGO_CCOBJS = $(call get_relobjs, $(LIB_AMR_ALGO_CCSRCS))
LIB_AMR_ALGO_ASMOBJS = $(call get_relobjs, $(LIB_AMR_ALGO_ASMSRCS))
LIB_AMR_ALGO_OBJS = $(LIB_AMR_ALGO_COBJS) $(LIB_AMR_ALGO_ASMOBJS) $(LIB_AMR_ALGO_CXXOBJS) $(LIB_AMR_ALGO_CCOBJS)

# get dependency files
LIB_AMR_ALGO_DEPS = $(call get_deps, $(LIB_AMR_ALGO_OBJS))

# extra macros to be defined
LIB_AMR_ALGO_DEFINES = -DLIB_AMR_ALGO

# genearte library
LIB_LIB_AMR_ALGO = $(OUT_DIR)/liblibamr_algo.a


# library generation rule
$(LIB_LIB_AMR_ALGO): $(LIB_AMR_ALGO_OBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(LIB_AMR_ALGO_OBJS)

# specific compile rules
# user can add rules to compile this middleware
# if not rules specified to this middleware, it will use default compiling rules

# Middleware Definitions
LIB_INCDIR += $(LIB_AMR_ALGO_INCDIR)
LIB_CSRCDIR += $(LIB_AMR_ALGO_CSRCDIR)
LIB_CXXSRCDIR += $(LIB_AMR_ALGO_CXXSRCDIR)
LIB_ASMSRCDIR += $(LIB_AMR_ALGO_ASMSRCDIR)

LIB_CSRCS += $(LIB_AMR_ALGO_CSRCS)
LIB_CXXSRCS += $(LIB_AMR_ALGO_CXXSRCS)
LIB_CCSRCS += $(LIB_AMR_ALGO_CCSRCS)
LIB_ASMSRCS += $(LIB_AMR_ALGO_ASMSRCS)
LIB_ALLSRCS += $(LIB_AMR_ALGO_CSRCS) $(LIB_AMR_ALGO_ASMSRCS)

LIB_COBJS += $(LIB_AMR_ALGO_COBJS)
LIB_CXXOBJS += $(LIB_AMR_ALGO_CXXOBJS)
LIB_CCOBJS += $(LIB_AMR_ALGO_CCOBJS)
LIB_ASMOBJS += $(LIB_AMR_ALGO_ASMOBJS)
LIB_ALLOBJS += $(LIB_AMR_ALGO_OBJS)

LIB_DEFINES += $(LIB_AMR_ALGO_DEFINES)
LIB_DEPS += $(LIB_AMR_ALGO_DEPS)
LIB_LIBS += $(LIB_LIB_AMR_ALGO)
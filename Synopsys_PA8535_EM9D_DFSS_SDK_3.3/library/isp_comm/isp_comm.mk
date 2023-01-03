# directory declaration
LIB_ISP_COMM_DIR = $(LIBRARIES_ROOT)/isp_comm

LIB_ISP_COMM_ASMSRCDIR	= $(LIB_ISP_COMM_DIR)
LIB_ISP_COMM_CSRCDIR	= $(LIB_ISP_COMM_DIR)
LIB_ISP_COMM_CXXSRCSDIR    = $(LIB_ISP_COMM_DIR)
LIB_ISP_COMM_INCDIR	= $(LIB_ISP_COMM_DIR)

# find all the source files in the target directories
LIB_ISP_COMM_CSRCS = $(call get_csrcs, $(LIB_ISP_COMM_CSRCDIR))
LIB_ISP_COMM_CXXSRCS = $(call get_cxxsrcs, $(LIB_ISP_COMM_CXXSRCSDIR))
LIB_ISP_COMM_ASMSRCS = $(call get_asmsrcs, $(LIB_ISP_COMM_ASMSRCDIR))

# get object files
LIB_ISP_COMM_COBJS = $(call get_relobjs, $(LIB_ISP_COMM_CSRCS))
LIB_ISP_COMM_CXXOBJS = $(call get_relobjs, $(LIB_ISP_COMM_CXXSRCS))
LIB_ISP_COMM_ASMOBJS = $(call get_relobjs, $(LIB_ISP_COMM_ASMSRCS))
LIB_ISP_COMM_OBJS = $(LIB_ISP_COMM_COBJS) $(LIB_ISP_COMM_ASMOBJS) $(LIB_ISP_COMM_CXXOBJS)

# get dependency files
LIB_ISP_COMM_DEPS = $(call get_deps, $(LIB_ISP_COMM_OBJS))

# extra macros to be defined
LIB_ISP_COMM_DEFINES = -DLIB_ISP_COMM

# genearte library
LIB_LIB_ISP_COMM = $(OUT_DIR)/liblibisp_comm.a


# library generation rule
$(LIB_LIB_ISP_COMM): $(LIB_ISP_COMM_OBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(LIB_ISP_COMM_OBJS)

# specific compile rules
# user can add rules to compile this middleware
# if not rules specified to this middleware, it will use default compiling rules

# Middleware Definitions
LIB_INCDIR += $(LIB_ISP_COMM_INCDIR)
LIB_CSRCDIR += $(LIB_ISP_COMM_CSRCDIR)
LIB_CXXSRCDIR += $(LIB_ISP_COMM_CXXSRCDIR)
LIB_ASMSRCDIR += $(LIB_ISP_COMM_ASMSRCDIR)

LIB_CSRCS += $(LIB_ISP_COMM_CSRCS)
LIB_CXXSRCS += $(LIB_ISP_COMM_CXXSRCS)
LIB_ASMSRCS += $(LIB_ISP_COMM_ASMSRCS)
LIB_ALLSRCS += $(LIB_ISP_COMM_CSRCS) $(LIB_ISP_COMM_ASMSRCS)

LIB_COBJS += $(LIB_ISP_COMM_COBJS)
LIB_CXXOBJS += $(LIB_ISP_COMM_CXXOBJS)
LIB_ASMOBJS += $(LIB_ISP_COMM_ASMOBJS)
LIB_ALLOBJS += $(LIB_ISP_COMM_OBJS)

LIB_DEFINES += $(LIB_ISP_COMM_DEFINES)
LIB_DEPS += $(LIB_ISP_COMM_DEPS)
LIB_LIBS += $(LIB_LIB_ISP_COMM)
# directory declaration
LIB_MEMDESP_DIR = $(LIBRARIES_ROOT)/memdesp

LIB_MEMDESP_ASMSRCDIR	= $(LIB_MEMDESP_DIR)
LIB_MEMDESP_CSRCDIR	= $(LIB_MEMDESP_DIR)
LIB_MEMDESP_CXXSRCSDIR    = $(LIB_MEMDESP_DIR)
LIB_MEMDESP_INCDIR	= $(LIB_MEMDESP_DIR)

# find all the source files in the target directories
LIB_MEMDESP_CSRCS = $(call get_csrcs, $(LIB_MEMDESP_CSRCDIR))
LIB_MEMDESP_CXXSRCS = $(call get_cxxsrcs, $(LIB_MEMDESP_CXXSRCSDIR))
LIB_MEMDESP_ASMSRCS = $(call get_asmsrcs, $(LIB_MEMDESP_ASMSRCDIR))

# get object files
LIB_MEMDESP_COBJS = $(call get_relobjs, $(LIB_MEMDESP_CSRCS))
LIB_MEMDESP_CXXOBJS = $(call get_relobjs, $(LIB_MEMDESP_CXXSRCS))
LIB_MEMDESP_ASMOBJS = $(call get_relobjs, $(LIB_MEMDESP_ASMSRCS))
LIB_MEMDESP_OBJS = $(LIB_MEMDESP_COBJS) $(LIB_MEMDESP_ASMOBJS) $(LIB_MEMDESP_CXXOBJS)

# get dependency files
LIB_MEMDESP_DEPS = $(call get_deps, $(LIB_MEMDESP_OBJS))

# extra macros to be defined
LIB_MEMDESP_DEFINES = -DLIB_MEMDESP

# genearte library
LIB_LIB_MEMDESP = $(OUT_DIR)/liblibmemdesp.a


# library generation rule
$(LIB_LIB_MEMDESP): $(LIB_MEMDESP_OBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(LIB_MEMDESP_OBJS)

# specific compile rules
# user can add rules to compile this middleware
# if not rules specified to this middleware, it will use default compiling rules

# Middleware Definitions
LIB_INCDIR += $(LIB_MEMDESP_INCDIR)
LIB_CSRCDIR += $(LIB_MEMDESP_CSRCDIR)
LIB_CXXSRCDIR += $(LIB_MEMDESP_CXXSRCDIR)
LIB_ASMSRCDIR += $(LIB_MEMDESP_ASMSRCDIR)

LIB_CSRCS += $(LIB_MEMDESP_CSRCS)
LIB_CXXSRCS += $(LIB_MEMDESP_CXXSRCS)
LIB_ASMSRCS += $(LIB_MEMDESP_ASMSRCS)
LIB_ALLSRCS += $(LIB_MEMDESP_CSRCS) $(LIB_MEMDESP_ASMSRCS)

LIB_COBJS += $(LIB_MEMDESP_COBJS)
LIB_CXXOBJS += $(LIB_MEMDESP_CXXOBJS)
LIB_ASMOBJS += $(LIB_MEMDESP_ASMOBJS)
LIB_ALLOBJS += $(LIB_MEMDESP_OBJS)

LIB_DEFINES += $(LIB_MEMDESP_DEFINES)
LIB_DEPS += $(LIB_MEMDESP_DEPS)
LIB_LIBS += $(LIB_LIB_MEMDESP)
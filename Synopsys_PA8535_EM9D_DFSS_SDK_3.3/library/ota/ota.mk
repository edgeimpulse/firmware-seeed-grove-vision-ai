# directory declaration
LIB_OTA_DIR = $(LIBRARIES_ROOT)/ota

LIB_OTA_ASMSRCDIR	= $(LIB_OTA_DIR)
LIB_OTA_CSRCDIR	= $(LIB_OTA_DIR)
LIB_OTA_CXXSRCSDIR    = $(LIB_OTA_DIR)
LIB_OTA_INCDIR	= $(LIB_OTA_DIR)

# find all the source files in the target directories
LIB_OTA_CSRCS = $(call get_csrcs, $(LIB_OTA_CSRCDIR))
LIB_OTA_CXXSRCS = $(call get_cxxsrcs, $(LIB_OTA_CXXSRCSDIR))
LIB_OTA_ASMSRCS = $(call get_asmsrcs, $(LIB_OTA_ASMSRCDIR))

# get object files
LIB_OTA_COBJS = $(call get_relobjs, $(LIB_OTA_CSRCS))
LIB_OTA_CXXOBJS = $(call get_relobjs, $(LIB_OTA_CXXSRCS))
LIB_OTA_ASMOBJS = $(call get_relobjs, $(LIB_OTA_ASMSRCS))
LIB_OTA_OBJS = $(LIB_OTA_COBJS) $(LIB_OTA_ASMOBJS) $(LIB_OTA_CXXOBJS)

# get dependency files
LIB_OTA_DEPS = $(call get_deps, $(LIB_OTA_OBJS))

# extra macros to be defined
LIB_OTA_DEFINES = -DLIB_OTA

# genearte library
LIB_LIB_OTA = $(OUT_DIR)/liblibota.a


# library generation rule
$(LIB_LIB_OTA): $(LIB_OTA_OBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(LIB_OTA_OBJS)

# specific compile rules
# user can add rules to compile this middleware
# if not rules specified to this middleware, it will use default compiling rules

# Middleware Definitions
LIB_INCDIR += $(LIB_OTA_INCDIR)
LIB_CSRCDIR += $(LIB_OTA_CSRCDIR)
LIB_CXXSRCDIR += $(LIB_OTA_CXXSRCDIR)
LIB_ASMSRCDIR += $(LIB_OTA_ASMSRCDIR)

LIB_CSRCS += $(LIB_OTA_CSRCS)
LIB_CXXSRCS += $(LIB_OTA_CXXSRCS)
LIB_ASMSRCS += $(LIB_OTA_ASMSRCS)
LIB_ALLSRCS += $(LIB_OTA_CSRCS) $(LIB_OTA_ASMSRCS)

LIB_COBJS += $(LIB_OTA_COBJS)
LIB_CXXOBJS += $(LIB_OTA_CXXOBJS)
LIB_ASMOBJS += $(LIB_OTA_ASMOBJS)
LIB_ALLOBJS += $(LIB_OTA_OBJS)

LIB_DEFINES += $(LIB_OTA_DEFINES)
LIB_DEPS += $(LIB_OTA_DEPS)
LIB_LIBS += $(LIB_LIB_OTA)
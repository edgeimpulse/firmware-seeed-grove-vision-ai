# directory declaration
LIB_SECURITY_DIR = $(LIBRARIES_ROOT)/security

LIB_SECURITY_ASMSRCDIR	= 
LIB_SECURITY_CSRCDIR	= 
LIB_SECURITY_CXXSRCSDIR    = 
LIB_SECURITY_INCDIR	= $(LIB_SECURITY_DIR)/inc/

# find all the source files in the target directories
LIB_SECURITY_CSRCS = $(call get_csrcs, $(LIB_SECURITY_CSRCDIR))
LIB_SECURITY_CXXSRCS = $(call get_cxxsrcs, $(LIB_SECURITY_CXXSRCSDIR))
LIB_SECURITY_ASMSRCS = $(call get_asmsrcs, $(LIB_SECURITY_ASMSRCDIR))

# get object files
LIB_SECURITY_COBJS = $(call get_relobjs, $(LIB_SECURITY_CSRCS))
LIB_SECURITY_CXXOBJS = $(call get_relobjs, $(LIB_SECURITY_CXXSRCS))
LIB_SECURITY_ASMOBJS = $(call get_relobjs, $(LIB_SECURITY_ASMSRCS))
LIB_SECURITY_OBJS = $(LIB_SECURITY_COBJS) $(LIB_SECURITY_ASMOBJS)

# get dependency files
LIB_SECURITY_DEPS = $(call get_deps, $(LIB_SECURITY_OBJS))

# extra macros to be defined
LIB_SECURITY_DEFINES = -DLIB_SECURITY

# genearte library
LIB_LIB_SECURITY =


# library generation rule
$(LIB_LIB_SECURITY): $(LIB_SECURITY_OBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(LIB_SECURITY_OBJS)

# specific compile rules
# user can add rules to compile this middleware
# if not rules specified to this middleware, it will use default compiling rules

# Middleware Definitions
LIB_INCDIR += $(LIB_SECURITY_INCDIR)
LIB_CSRCDIR += $(LIB_SECURITY_CSRCDIR)
LIB_CXXSRCDIR += $(LIB_SECURITY_CXXSRCDIR)
LIB_ASMSRCDIR += $(LIB_SECURITY_ASMSRCDIR)

LIB_CSRCS += $(LIB_SECURITY_CSRCS)
LIB_CXXSRCS +=
LIB_ASMSRCS += $(LIB_SECURITY_ASMSRCS)
LIB_ALLSRCS += $(LIB_SECURITY_CSRCS) $(LIB_SECURITY_ASMSRCS)

LIB_COBJS += $(LIB_SECURITY_COBJS)
LIB_CXXOBJS += $(LIB_SECURITY_CXXOBJS)
LIB_ASMOBJS += $(LIB_SECURITY_ASMOBJS)
LIB_ALLOBJS += $(LIB_SECURITY_OBJS)

LIB_DEFINES += $(LIB_SECURITY_DEFINES)
LIB_DEPS += $(LIB_SECURITY_DEPS)
LIB_LIBS += $(LIB_LIB_SECURITY)

APPL_DEFINES += -DBOARD_HIMAXEM9D
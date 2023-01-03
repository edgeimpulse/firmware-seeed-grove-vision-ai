##
# \defgroup 	MK_BOARD_SOCKET	SOCKET Board Related Makefile Configurations
# \ingroup	MK_BOARD
# \brief	makefile related to SOCKET board configurations
##

##
# \brief	current board directory definition
##
BOARD_SOCKET_DIR = $(BOARDS_ROOT)/socket
##
# board version definition
# 10 stands for v1.0
# When you don't special BD_VER
# in any other place or through make options
# it will select a proper BD_VER according to your cur_core
# v10 : initial version - cpu only + dfss + dmac
##
SUPPORTED_BD_VERS = 24

## Select Board Version
BD_VER ?= 24

override BD_VER := $(strip $(BD_VER))

## Set Valid Board Version
VALID_BD_VER = $(call check_item_exist, $(BD_VER), $(SUPPORTED_BD_VERS))

## Check TCF file existence
ifneq ($(TCF),)
ifeq ($(wildcard $(TCF)),)
$(error Tool Configuration File(TCF) - $(TCF) doesn't exist, please check it!)
else
TCFFILE_IS_VALID = 1
TCFFILE_NAME = $(firstword $(basename $(notdir $(TCF))))
endif
endif

## If CUR_CORE is not in SUPPORTED_BD_VERS list, then force BD_VER and VALID_BD_VER to be 10
ifeq ($(TCFFILE_IS_VALID),1)
ifeq ($(VALID_BD_VER),)
override BD_VER := 24
override VALID_BD_VER := 24
endif
endif

## Try to include different board version makefiles
ifneq ($(TCFFILE_IS_VALID),1)
ifeq ($(VALID_BD_VER),)
$(info BOARD $(BOARD) Version - $(SUPPORTED_BD_VERS) are supported)
$(error $(BOARD) Version $(BD_VER) is not supported, please check it!)
endif
endif

## Compiler Options
BOARD_CORE_DIR = $(BOARD_SOCKET_DIR)/configs/$(VALID_BD_VER)
COMMON_COMPILE_PREREQUISITES += $(BOARD_SOCKET_DIR)/configs/core_configs.mk
include $(BOARD_SOCKET_DIR)/configs/core_configs.mk

COMMON_COMPILE_PREREQUISITES += $(BOARD_SOCKET_DIR)/configs/core_compiler.mk
include $(BOARD_SOCKET_DIR)/configs/core_compiler.mk

## Board Related Settings, GNU is not supported
OPENOCD_CFG_FILE ?= $(BOARD_SOCKET_DIR)/configs/openocd/snps_socket.cfg

OPENOCD_OPTIONS ?= -s $(OPENOCD_SCRIPT_ROOT) -f $(OPENOCD_CFG_FILE)


##
# \brief	socket board related source and header
# HIMAX@WILL<make>, update BOARD_SOCKET_DEV_CSRCDIR if add drivers/wrapper for 1)platform and 2)external 
##
# onchip ip object rules
#ifdef ONCHIP_IP_LIST
#	BOARD_SOCKET_DEV_CSRCDIR += $(foreach ONCHIP_IP_OBJ, $(ONCHIP_IP_LIST), $(addprefix $(BOARD_SOCKET_DIR)/drivers/ip/, $(ONCHIP_IP_OBJ)))
#endif


include $(EMBARC_ROOT)/platform/platform.mk
include $(EMBARC_ROOT)/external/external.mk

##
# \brief	socket platform driver related
##
BOARD_SOCKET_DEV_CSRCDIR		+= $(DEV_CSRCDIR)
BOARD_SOCKET_DEV_ASMSRCDIR	+= $(DEV_ASMSRCDIR)
BOARD_SOCKET_DEV_INCDIR		+= $(DEV_INCDIR)

##
# \brief	socket board related source and header
##
BOARD_SOCKET_CSRCDIR		+= $(BOARD_SOCKET_DEV_CSRCDIR) $(BOARD_CORE_DIR) $(BOARD_SOCKET_DIR)/common
BOARD_SOCKET_ASMSRCDIR	+= $(BOARD_SOCKET_DEV_ASMSRCDIR) $(BOARD_CORE_DIR) $(BOARD_SOCKET_DIR)/common
BOARD_SOCKET_INCDIR 		+= $(BOARD_SOCKET_DEV_INCDIR) $(BOARD_CORE_DIR) $(BOARD_SOCKET_DIR)/common

# find all the source files in the target directories
BOARD_SOCKET_CSRCS = $(call get_csrcs, $(BOARD_SOCKET_CSRCDIR))
BOARD_SOCKET_ASMSRCS = $(call get_asmsrcs, $(BOARD_SOCKET_ASMSRCDIR))

# remove opened protocol source files
BOARD_SOCKET_CSRCS := $(filter-out $(DEV_OPEN_CSRC),$(BOARD_SOCKET_CSRCS))

# get object files
BOARD_SOCKET_COBJS = $(call get_relobjs, $(BOARD_SOCKET_CSRCS))
BOARD_SOCKET_ASMOBJS = $(call get_relobjs, $(BOARD_SOCKET_ASMSRCS))
BOARD_SOCKET_OBJS = $(BOARD_SOCKET_COBJS) $(BOARD_SOCKET_ASMOBJS)

# get dependency files
BOARD_SOCKET_DEPS = $(call get_deps, $(BOARD_SOCKET_OBJS))

# extra macros to be defined
BOARD_SOCKET_DEFINES += $(CORE_DEFINES) $(DEV_DEFINES)

# genearte library
BOARD_LIB_SOCKET = $(OUT_DIR)/libboard_socket.a


# specific compile rules
# user can add rules to compile this middleware
# if not rules specified to this middleware, it will use default compiling rules
BOARD_ROOT_CSRCS += $(call get_csrcs, $(BOARDS_ROOT))
BOARD_ROOT_ASMSRCS += $(call get_asmsrcs, $(BOARDS_ROOT))

# get object files
BOARD_ROOT_COBJS += $(call get_relobjs, $(BOARD_ROOT_CSRCS))
BOARD_ROOT_ASMOBJS += $(call get_relobjs, $(BOARD_ROOT_ASMSRCS))
BOARD_ROOT_OBJS += $(BOARD_ROOT_COBJS) $(BOARD_ROOT_ASMOBJS)


# Middleware Definitions
BOARD_INCDIR += $(BOARD_SOCKET_INCDIR)
BOARD_CSRCDIR += $(BOARD_SOCKET_CSRCDIR)
BOARD_ASMSRCDIR += $(BOARD_SOCKET_ASMSRCDIR)

BOARD_CSRCS += $(BOARD_SOCKET_CSRCS) $(BOARD_ROOT_CSRCS)
BOARD_CXXSRCS +=
BOARD_ASMSRCS += $(BOARD_SOCKET_ASMSRCS) $(BOARD_ROOT_ASMSRCS)
BOARD_ALLSRCS += $(BOARD_SOCKET_CSRCS) $(BOARD_SOCKET_ASMSRCS)

BOARD_COBJS += $(BOARD_SOCKET_COBJS) $(BOARD_ROOT_COBJS)
BOARD_CXXOBJS +=
BOARD_ASMOBJS += $(BOARD_SOCKET_ASMOBJS) $(BOARD_ROOT_ASMOBJS)
BOARD_ALLOBJS += $(BOARD_SOCKET_OBJS) $(BOARD_ROOT_OBJS)

BOARD_DEFINES += $(BOARD_SOCKET_DEFINES)
BOARD_DEPS += $(BOARD_SOCKET_DEPS)
BOARD_LIB = $(BOARD_LIB_SOCKET)

# library generation rule
$(BOARD_LIB_SOCKET): $(BOARD_ALLOBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(BOARD_ALLOBJS)

# for open protocol source files
BOARD_SOCKET_OPEN_CSRCS = $(DEV_OPEN_CSRC)
BOARD_SOCKET_OPEN_OBJS = $(call get_relobjs, $(BOARD_SOCKET_OPEN_CSRCS))
BOARD_OPEN_LIB_SOCKET = $(OUT_DIR)/libboard_open_socket.a
$(BOARD_OPEN_LIB_SOCKET): $(BOARD_SOCKET_OPEN_OBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(BOARD_SOCKET_OPEN_OBJS)
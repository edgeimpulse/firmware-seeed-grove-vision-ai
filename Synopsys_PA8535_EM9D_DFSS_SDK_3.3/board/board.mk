##
# \defgroup	MK_BOARD	Board Makefile Configurations
# \brief	makefile related to board configurations
##

# boards root declaration
BOARDS_ROOT = $(EMBARC_ROOT)/board

##
# BOARD
# select the target board
# scan the sub-dirs of board to get the supported boards
SUPPORTED_BOARDS = $(basename $(notdir $(wildcard $(BOARDS_ROOT)/*/*.mk)))
BOARD ?= fpga
ifeq ($(OS_TYPE), RTOS)
USE_BOARD_MAIN ?= 1
else
USE_BOARD_MAIN ?=
endif


override BOARD := $(strip $(BOARD))
override USE_BOARD_MAIN := $(strip $(USE_BOARD_MAIN))

BOARD_CSRCDIR	+= $(BOARDS_ROOT)
BOARD_ASMSRCDIR	+= $(BOARDS_ROOT)
BOARD_INCDIR	+= $(BOARDS_ROOT)

ifeq ($(USE_BOARD_MAIN), 1)
BOARD_MAIN_DEFINES = -DEMBARC_USE_BOARD_MAIN
else
BOARD_MAIN_DEFINES =
endif

ifeq ($(PURE_BOARD_INIT), 1)
BOARD_MAIN_DEFINES += -DPURE_BOARD_INIT
endif


EXTRA_BOARD_DEFINES += $(BOARD_MAIN_DEFINES)

include $(EMBARC_ROOT)/def_linker_script/def_linker_script.mk

ifeq ($(BOARD), fpga)
APPL_DEFINES += -DFPGA_PLATFORM
APPL_DEFINES += -DSPI_SLAVE_HANDSHAKE_FPGA
else
APPL_DEFINES += -DSPI_SLAVE_HANDSHAKE_IC
APPL_DEFINES += -DCHANG_PLL_BEFORE_PMU
endif
## CPU_FREQ & DEV_FREQ defined in each board support file ##

## Set Valid Board
VALID_BOARD = $(call check_item_exist, $(BOARD), $(SUPPORTED_BOARDS))

## Try Check BOARD is valid
ifeq ($(VALID_BOARD), )
$(info BOARD - $(SUPPORTED_BOARDS) are supported)
$(error BOARD $(BOARD) is not supported, please check it!)
endif

#board definition
BOARD_ID = $(call uc,BOARD_$(VALID_BOARD))
#device usage settings
#must be before include
COMMON_COMPILE_PREREQUISITES += $(BOARDS_ROOT)/$(VALID_BOARD)/$(VALID_BOARD).mk
include $(BOARDS_ROOT)/$(VALID_BOARD)/$(VALID_BOARD).mk

##
# \brief	add defines for board
##
BOARD_DEFINES += $(EXTRA_BOARD_DEFINES) -D$(BOARD_ID) -DHW_VERSION=$(BD_VER)
ifneq ($(CPU_FREQ), )
BOARD_DEFINES += -DBOARD_CPU_FREQ=$(CPU_FREQ)
endif
ifneq ($(DEV_FREQ), )
BOARD_DEFINES += -DBOARD_DEV_FREQ=$(DEV_FREQ)
endif

##
# \brief	add svn version for board
##
# _REPO_REV := $(shell svnversion -n)
ifeq ($(LIB_BSP_PREBUILT), 0)
_REPO_REV = $(shell svn info --show-item=revision)

ifeq (M, $(findstring M, $(_REPO_REV)))
	REPO_REV = $(_REPO_REV:%M=%)
else ifeq (P, $(findstring P, $(_REPO_REV)))
	REPO_REV = $(_REPO_REV:%P=%)
else ifeq (S, $(findstring S, $(_REPO_REV)))
	REPO_REV = $(_REPO_REV:%S=%)
else ifeq (:, $(findstring :, $(_REPO_REV)))
	REPO_REV = $(word 1, $(subst :, ,$(_REPO_REV)))
else ifeq (Unversioned directory, $(findstring Unversioned directory, $(_REPO_REV)))
	REPO_REV = 0
else ifeq (not a working copy, $(findstring not a working copy, $(_REPO_REV)))
	REPO_REV = 0
else ifeq (Command not found, $(findstring Command not found, $(_REPO_REV)))
	REPO_REV = 0
else ifeq ($(_REPO_REV), )
	REPO_REV = 0
else
	REPO_REV = $(_REPO_REV)
endif
endif

REPO_REV = 162765

BOARD_DEFINES += -DREPO_REV=$(REPO_REV)

$(warning "------------------------------------------")
$(warning $(_REPO_REV))
$(warning $(REPO_REV))
$(warning "------------------------------------------")

# include dependency files
ifneq ($(MAKECMDGOALS),clean)
-include $(BOARD_DEPS)
endif
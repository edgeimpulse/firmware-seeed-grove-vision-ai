LINKER_SCRIPT_ROOT = $(EMBARC_ROOT)/def_linker_script

ifeq ($(VALID_TOOLCHAIN), mw)
	ifeq ("$(LINKER_SCRIPT_FILE)","")
	override LINKER_SCRIPT_FILE := $(LINKER_SCRIPT_ROOT)/linker_template_mw.ld
	endif
	ifeq ($(ALGO_TYPE), DATA_BSS_SRAM)
	override LINKER_SCRIPT_FILE := $(LINKER_SCRIPT_ROOT)/linker_template_mw_sram.ld
	endif
	ifeq ($(OS_TYPE), RTOS)
	override LINKER_SCRIPT_FILE := $(LINKER_SCRIPT_ROOT)/linker_template_mw_rtos.ld
		ifeq (aiot_humandetect_aircondition, $(findstring aiot_humandetect_aircondition, $(APP_TYPE)))
			override LINKER_SCRIPT_FILE := $(LINKER_SCRIPT_ROOT)/linker_template_mw_rtos_2.ld
		else ifeq ($(APP_TYPE), sample_code_rtos)
			override LINKER_SCRIPT_FILE := $(LINKER_SCRIPT_ROOT)/linker_template_mw_rtos_2.ld
		endif
	endif
ifeq ($(OS_TYPE), TX)
override LINKER_SCRIPT_FILE := $(LINKER_SCRIPT_ROOT)/linker_template_mw_tx.ld
$(warning "OS_TYPE TX")
endif
else
ifdef USER_LINKER_SCRIPT_FILE
	override LINKER_SCRIPT_FILE := $(USER_LINKER_SCRIPT_FILE)
else
	override LINKER_SCRIPT_FILE := $(LINKER_SCRIPT_ROOT)/linker_template_gnu_M.ld
endif
endif


override LIB_BSS_DIR = $(EMBARC_ROOT)/def_linker_script/bss

override LIB_BSS_ASMSRCDIR	= $(LIB_BSS_DIR)
override LIB_BSS_CSRCDIR	= $(LIB_BSS_DIR)
override LIB_BSS_CXXSRCSDIR    = $(LIB_BSS_DIR)
override LIB_BSS_INCDIR	= $(LIB_BSS_DIR)

# find all the source files in the target directories
override LIB_BSS_CSRCS = $(call get_csrcs, $(LIB_BSS_CSRCDIR))
override LIB_BSS_CXXSRCS = $(call get_cxxsrcs, $(LIB_BSS_CXXSRCSDIR))
override LIB_BSS_ASMSRCS = $(call get_asmsrcs, $(LIB_BSS_ASMSRCDIR))

# get object files
override LIB_BSS_COBJS = $(call get_relobjs, $(LIB_BSS_CSRCS))
override LIB_BSS_CXXOBJS = $(call get_relobjs, $(LIB_BSS_CXXSRCS))
override LIB_BSS_ASMOBJS = $(call get_relobjs, $(LIB_BSS_ASMSRCS))
override LIB_BSS_OBJS = $(LIB_BSS_COBJS) $(LIB_BSS_ASMOBJS) $(LIB_BSS_CXXOBJS)

# get dependency files
override LIB_BSS_DEPS = $(call get_deps, $(LIB_BSS_OBJS))

# extra macros to be defined
override LIB_BSS_DEFINES = -DLIB_BSS_HANDLE

# genearte library
override BSS_LIB = $(OUT_DIR)/libbss.a

LIB_INCDIR += $(LIB_BSS_INCDIR)

override BSS_LIB_CSRCDIR = $(LIB_BSS_CSRCDIR)
override BSS_LIB_CXXSRCDIR = $(LIB_BSS_CXXSRCDIR)
override BSS_LIB_ASMSRCDIR = $(LIB_BSS_ASMSRCDIR)

override BSS_LIB_CSRCS = $(LIB_BSS_CSRCS)
override BSS_LIB_CXXSRCS = $(LIB_BSS_CXXSRCS)
override BSS_LIB_ASMSRCS = $(LIB_BSS_ASMSRCS)
override BSS_LIB_ALLSRCS = $(LIB_BSS_CSRCS) $(LIB_BSS_ASMSRCS)

override BSS_LIB_COBJS = $(LIB_BSS_COBJS)
override BSS_LIB_CXXOBJS = $(LIB_BSS_CXXOBJS)
override BSS_LIB_ASMOBJS = $(LIB_BSS_ASMOBJS)
override BSS_LIB_ALLOBJS = $(LIB_BSS_OBJS)

override BSS_LIB_DEFINES = $(LIB_BSS_DEFINES)
override BSS_LIB_DEPS = $(LIB_BSS_DEPS)
override BSS_LIB_LIBS = $(LIB_LIB_BSS)

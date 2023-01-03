SHELL:=/bin/bash
## TCF Processing ##
VALID_TCF = $(wildcard $(TCF))

ifeq ($(VALID_TCF),)
CORE_ARG_FILES =
else
CORE_ARG_FILES_LIST = $(GENE_FILE_LIST)
CORE_ARG_FILES = $(addprefix $(EMBARC_GENERATED_DIR)/, $(CORE_ARG_FILES_LIST))
COMMON_COMPILE_PREREQUISITES += $(CORE_ARG_FILES)
EXTRA_DEFINES += -DEMBARC_TCF_GENERATED
endif


## All defines ##
ALL_DEFINES += -DPLATFORM_EMBARC $(CPU_DEFINES) $(BOARD_DEFINES) \
		$(MID_DEFINES) $(LIB_DEFINES) $(CV_LIB_DEFINES) $(LIB_BSS_DEFINES) $(OS_DEFINES) \
		$(AZ_SDK_LIB_DEFINES) $(NETXDUO_LIB_DEFINES) \
		$(TOOLCHAIN_DEFINES) $(EXTRA_DEFINES) $(APPL_DEFINES)
ifeq ($(TOOLCHAIN), mw)
	ALL_DEFINES += -tcf_core_config
endif		
## all includes conversion  ##
ALL_INCLUDES = $(foreach dir,$(ALL_INC_DIRS),-I$(dir))

##
# All object sub-directories need to be created
##
ALL_OBJDIRS = $(sort $(dir $(ALL_ALLOBJS)))

##
# Generated directories required to build this applications
##
ALL_GENERATED_DIRS += $(ALL_OBJDIRS) $(EMBARC_GENERATED_DIR)/
ALL_GENERATED_DIRS_TMPFILES = $(sort $(call get_mkdir_tmps, $(ALL_GENERATED_DIRS)))

##
# Collect all libraries
##
ALL_LIBS = $(BOARD_LIB) $(MID_LIBS) $(OS_LIBS) $(CPU_LIBS) $(LIB_LIBS)
ALL_OBJS = $(BOARD_ALLOBJS) $(MID_ALLOBJS) $(OS_ALLOBJS) $(CPU_ALLOBJS) $(LIB_ALLOBJS)
EMBARC_LIB = $(OUT_DIR)/libembarc.a

SECURE_LIB = $(OUT_DIR)/liblibsecurity.a	


##
# Collect Dependency Files
##
APPL_DEPS = $(call get_deps, $(APPL_OBJS))
EXTRA_DEPS = $(call get_deps, $(EXTRA_OBJS))
ALL_DEPS = $(call get_deps, $(ALL_ALLOBJS))

# include dependency files of application
ifneq ($(MAKECMDGOALS),clean)
 -include $(APPL_DEPS)
 -include $(EXTRA_DEPS)
endif


##
# Clean Related
##
OUT_DIR_PREFIX_WILDCARD = $(subst \,/,$(OUT_DIR_PREFIX))
OUT_DIRS_WILDCARD = $(sort $(wildcard $(OUT_DIR_PREFIX_WILDCARD)*))
OUT_DIRS = $(subst /,$(PS), $(strip $(OUT_DIRS_WILDCARD)))

ifeq ($(strip $(OUT_DIRS)), )
DIST_DIR_CLEAN =
else
DIST_DIR_CLEAN = $(RMD) $(OUT_DIRS)
endif

TEMP_FILES2CLEAN = $(sort $(wildcard *.o *.out *.bin *.dis *.elf *.a *.hex *.map *.bak *.dump *.d *.img *.dasm *.log))
ifeq ($(strip $(TEMP_FILES2CLEAN)), )
TEMPFILES_CLEAN =
else
TEMPFILES_CLEAN = $(RM) $(TEMP_FILES2CLEAN)
endif

##
# Overwrite some variables
##
override ALL_DEFINES := $(sort $(ALL_DEFINES))
override ALL_INCLUDES := $(sort $(ALL_INCLUDES))
ifeq ($(TOOLCHAIN), mw)
	TCF_FLAGS = -tcf=$(TCF)
else
	TCF_FLAGS = -include $(BOARD_CORE_DIR)/core_config.h
endif
#
#  the definition of source file directory
#
vpath %.C $(ALL_CSRC_DIRS)
vpath %.c $(ALL_CSRC_DIRS)
vpath %.cpp $(ALL_CXXSRC_DIRS)
vpath %.cc $(ALL_CCSRC_DIRS)
vpath %.CC $(ALL_CCSRC_DIRS)
vpath %.S $(ALL_ASMSRC_DIRS)
vpath %.s $(ALL_ASMSRC_DIRS)

ifeq ($(TOOLCHAIN), gnu)
CUR_PATH = $(shell pwd)
GEN_TOOL_PATH = $(patsubst $/,%, $(dir $(shell pwd))) 
GEN_TOOL_DIR = image_gen_linux
GEN_TOOL_NAME = image_gen_gnu
endif

.PHONY : all build dump dasm bin hex size clean boardclean distclean run gui cfg opt info spopt infodirs infosrcs infoobjs help

all : $(APPL_FULL_NAME).elf

build : clean all

dump : $(APPL_FULL_NAME).dump

dasm : $(APPL_FULL_NAME).dasm

bin : $(APPL_FULL_NAME).bin

hex : $(APPL_FULL_NAME).hex

help :
	@$(ECHO) 'Build Targets for selected configuration:'
	@$(ECHO) '  all         - Build example'
	@$(ECHO) '  bin         - Build and Generate binary for example'
	@$(ECHO) '  hex         - Build and Generate Intel Hex File for example'
	@$(ECHO) '  build       - Clean first then compile example'
	@$(ECHO) '  dump        - Generate dump information for example'
	@$(ECHO) '  dasm        - Disassemble object file'
	@$(ECHO) '  size        - Display size information of object file'
	@$(ECHO) 'Clean Targets:'
	@$(ECHO) '  clean       - Remove object files of selected configuration'
	@$(ECHO) '  boardclean  - Remove object files of selected board'
	@$(ECHO) '  distclean   - Remove object files of all boards'
	@$(ECHO) 'Debug & Run Targets for selected configuration:'
	@$(ECHO) '  run         - Use MDB & JTAG to download and run object elf file'
	@$(ECHO) '  gui         - Use MDB & JTAG to download and debug object elf file'
	@$(ECHO) 'Other Targets:'
	@$(ECHO) '  cfg         - Display build target configuration'
	@$(ECHO) '  opt         - Display Current MAKE options'
	@$(ECHO) '  spopt       - Display Supported MAKE options'
	@$(ECHO) '  flash       - Generate image'
	@$(ECHO) '  ota         - Copy elf and map file to ota img folder'
	@$(ECHO) '  menuconfig  - Set parameters of image generation tool'
	@$(ECHO) 'Available Configurations:'
	@$(ECHO) '  BOARD=emsk|nsim|axs                         - Build for which board(EMSK, NSIM, AXS)'
	@$(ECHO) '  BD_VER=11|22|23|10|1506|103                 - Board Version of development board'
	@$(ECHO) '  OLEVEL=Os|O0|O1|O2|O3                       - Optimization Level of examples to be built'
	@$(ECHO) '  CUR_CORE=arcem4|arcem4cr16|arcem6|arcem6gp|arcem7d|arcem9d|arcem11d|arcem|archs|arcemfull|arcsem|archs36|...'
	@$(ECHO) '                                              - Current core configuration'
	@$(ECHO) '  TCF=path/to/yourtcf                         - Select your own tcf file to replace current used one'
	@$(ECHO) '  TOOLCHAIN=mw|gnu                            - Current selected compiling toolchain'
	@$(ECHO) '  JTAG=usb|opella                             - Current debug jtag(Digilent JTAG or Ashling Opella-XD JTAG)'
	@$(ECHO) '  OUT_DIR_ROOT=.|xxx                          - Specify where to generate object files default current example makefile folder'
	@$(ECHO) '  SILENT=0|1                                  - Disable or enable message output'
	@$(ECHO) '  V=0|1                                       - Disable or enable verbose compiling information'
	@$(ECHO) '  DIG_NAME=xxx                                - Specify Digilent JTAG which to be used, most useful when more than one Digilent USB-JTAG plugged in'
	@$(ECHO) '  HEAPSZ=xxx                                  - Specify heap size for program, xxx stands for size in bytes'
	@$(ECHO) '  STACKSZ=xxx                                 - Specify stack size for program, xxx stands for size in bytes'
	@$(ECHO) 'Example Usage:'
	@$(ECHO) '  make all                                                                - build example in current directory using default configuration'
	@$(ECHO) '  make BOARD=emsk BD_VER=22 CUR_CORE=arcem7d OLEVEL=O2 TOOLCHAIN=gnu all  - build example using configuration (emsk, 22, arcem7d, O2, gnu)'
	@$(ECHO) '  make BOARD=emsk BD_VER=22 CUR_CORE=arcem7d TCF=mytcfpath all            - build example using configuration (emsk, 22, arcem7d) using the tcf defined in TCF option'

cfg :
	@$(ECHO) '=======Current Configuration======='
	@$(ECHO) 'Host OS            : $(HOST_OS)'
	@$(ECHO) 'Board              : $(BOARD)'
	@$(ECHO) 'Hardware Version   : $(BD_VER)'
	@$(ECHO) 'Core Configuration : $(CUR_CORE)'
	@$(ECHO) 'CPU Clock HZ       : $(CPU_FREQ)'
	@$(ECHO) 'Peripheral Clock HZ: $(DEV_FREQ)'
	@$(ECHO) 'Build Toolchain    : $(TOOLCHAIN)'
	@$(ECHO) 'Optimization Level : $(OLEVEL)'
	@$(ECHO) 'Debug Jtag         : $(JTAG)'
	@$(ECHO) '======Supported Configurations of $(BOARD)-$(BD_VER)======'
	@$(ECHO) 'Boards (BOARD)                 : $(SUPPORTED_BOARDS)'
	@$(ECHO) 'Core Configurations (CUR_CORE) : $(SUPPORTED_CORES)'
	@$(ECHO) 'Build Toolchains (TOOLCHAIN)   : $(SUPPORTED_TOOLCHAINS)'
	@$(ECHO) 'Debug Jtags (JTAG)             : $(SUPPORTED_JTAGS)'

opt :
	@$(ECHO) ======CURRENT CONFIGURATION=====
	@$(ECHO) BOARD : $(BOARD)
	@$(ECHO) BD_VER : $(BD_VER)
	@$(ECHO) CUR_CORE : $(CUR_CORE)
	@$(ECHO) TOOLCHAIN : $(TOOLCHAIN)
	@$(ECHO) OLEVEL : $(OLEVEL)
	@$(ECHO) JTAG : $(JTAG)
	@$(ECHO) EMBARC_ROOT : $(EMBARC_ROOT)
	@$(ECHO) OUT_DIR_ROOT : $(OUT_DIR_ROOT)
	@$(ECHO) COMPILE_OPT : $(subst $(MKDEP_OPT), , $(COMPILE_OPT))
	@$(ECHO) CXX_COMPILE_OPT: $(subst $(MKDEP_OPT), , $(CXX_COMPILE_OPT))
	@$(ECHO) ASM_OPT : $(subst $(MKDEP_OPT), , $(ASM_OPT))
	@$(ECHO) AR_OPT : $(AR_OPT)
	@$(ECHO) LINK_OPT : $(LINK_OPT)
	@$(ECHO) DEBUGGER : $(DBG)
	@$(ECHO) DBG_HW_FLAGS : $(DBG_HW_FLAGS)
	@$(ECHO) MDB_NSIM_OPT : $(MDB_NSIM_OPT)

info:
	@$(ECHO) ======CURRENT BUILD INFORMATION=====
	@$(ECHO) EMBARC_ROOT : $(realpath $(EMBARC_ROOT))
	@$(ECHO) OUT_DIR_ROOT : $(realpath $(OUT_DIR_ROOT))
	@$(ECHO) BUILD_OPTION : BOARD=$(BOARD) BD_VER=$(BD_VER) CUR_CORE=$(CUR_CORE) TOOLCHAIN=$(TOOLCHAIN) OLEVEL=$(OLEVEL) V=$(V) DEBUG=$(DEBUG) SILENT=$(SILENT)
	@$(ECHO) APPLICATION_NAME : $(APPL_NAME)
	@$(ECHO) APPLICATION_LINKSCRIPT : $(APPL_LINK_FILE)
	@$(ECHO) APPLICATION_ELF : $(APPL_FULL_NAME).elf
	@$(ECHO) APPLICATION_BIN : $(APPL_FULL_NAME).bin
	@$(ECHO) APPLICATION_HEX : $(APPL_FULL_NAME).hex
	@$(ECHO) APPLICATION_MAP : $(APPL_FULL_NAME).map
	@$(ECHO) APPLICATION_DUMP : $(APPL_FULL_NAME).dump
	@$(ECHO) APPLICATION_DASM : $(APPL_FULL_NAME).dasm
	@$(ECHO) MIDDLEWARE : $(sort $(MID_SEL))
	@$(ECHO) PERIPHERAL : $(sort $(EXT_DEV_LIST))

spopt :
	@$(ECHO) ======SUPPORTED CONFIGURATIONS=====
	@$(ECHO) SUPPORTED_BOARDS : $(SUPPORTED_BOARDS)
	@$(ECHO) SUPPORTED_BD_VERS : $(SUPPORTED_BD_VERS)
	@$(ECHO) SUPPORTED_CORES : $(SUPPORTED_CORES)
	@$(ECHO) SUPPORTED_OLEVELS : $(SUPPORTED_OLEVELS)
	@$(ECHO) SUPPORTED_TOOLCHAINS : $(SUPPORTED_TOOLCHAINS)
	@$(ECHO) SUPPORTED_JTAGS : $(SUPPORTED_JTAGS)

infodirs :
	@$(ECHO) ======ALL Directories Information=====
	@$(ECHO) ALL_INC_DIRS : $(ALL_INC_DIRS)
	@$(ECHO) ALL_CSRC_DIRS : $(ALL_CSRC_DIRS)
	@$(ECHO) ALL_ASMSRC_DIRS : $(ALL_ASMSRC_DIRS)
	@$(ECHO) ALL_CXXSRC_DIRS : $(ALL_CXXSRC_DIRS)

infosrcs :
	@$(ECHO) ======ALL Sources Information=====
	@$(ECHO) ALL_CSRCS : $(ALL_CSRCS)
	@$(ECHO) ALL_ASMSRCS : $(ALL_ASMSRCS)
	@$(ECHO) ALL_CXXSRCS : $(ALL_CXXSRCS)
	@$(ECHO) ALL_CCSRCS : $(ALL_CCSRCS)

infoobjs :
	@$(ECHO) ======ALL Sources Information=====
	@$(ECHO) ALL_COBJS : $(ALL_COBJS)
	@$(ECHO) ALL_ASMOBJS : $(ALL_ASMOBJS)
	@$(ECHO) ALL_CXXOBJS : $(ALL_CXXOBJS)


size : $(APPL_FULL_NAME).elf
	@$(ECHO) "Print Application Program Size"
	$(Q)$(SIZE) $(SIZE_OPT) $<

clean :
	@$(ECHO) "Clean Workspace For Selected Configuration : $(SELECTED_CONFIG)"
	-$(IFEXISTDIR) $(subst /,$(PS),$(OUT_DIR)) $(ENDIFEXISTDIR) $(RMD) $(subst /,$(PS),$(OUT_DIR))
	-$(IFEXISTDIR) .sc.project $(ENDIFEXISTDIR) $(RMD) .sc.project
	-$(TEMPFILES_CLEAN)

boardclean :
	@$(ECHO) "Clean Workspace For Selected Board : $(BOARD_INFO)"
	-$(IFEXISTDIR) $(subst /,$(PS),$(BOARD_OUT_DIR)) $(ENDIFEXISTDIR) $(RMD) $(subst /,$(PS),$(BOARD_OUT_DIR))
	-$(IFEXISTDIR) .sc.project $(ENDIFEXISTDIR) $(RMD) .sc.project
	-$(TEMPFILES_CLEAN)

distclean :
	@$(ECHO) "Clean All"
	-$(IFEXISTDIR) .sc.project $(ENDIFEXISTDIR) $(RMD) .sc.project
	-$(DIST_DIR_CLEAN)
	-$(TEMPFILES_CLEAN)

run : $(APPL_FULL_NAME).elf
	@$(ECHO) "Download & Run $<"
	$(DBG) $(DBG_HW_FLAGS) $< $(CMD_LINE)

gui : $(APPL_FULL_NAME).elf
	@$(ECHO) "Download & Debug $<"
	$(DBG) $(DBG_HW_FLAGS) $< $(CMD_LINE)

flash :
ifeq ($(TOOLCHAIN), gnu)	 
	@$(ECHO) "===== GNU Generate CSTM Image Process ====="
	$(CP) $(APPL_FULL_NAME).elf $(IMAGE_GEN_TOOL_INPUT_DIR)
	@$(ECHO) "execute image_gen_cstm_gnu"
	cd $(IMAGE_GEN_TOOL_DIR) &&\
	chmod 777 image_gen_cstm_gnu &&\
	chmod 777 sign_tool &&\
	./image_gen_cstm_gnu ic config

	@$(ECHO) "===== Image for OTA ====="
	$(CP) $(IMAGE_GEN_TOOL_OUTPUT_DIR)/output.img $(OTA_IMG_DIR)/output.img
	$(CP) $(IMAGE_GEN_TOOL_OUTPUT_DIR)/layout.bin $(OTA_IMG_DIR)/layout.bin
	@$(ECHO) "Image path:" $(IMAGE_GEN_TOOL_OUTPUT_DIR)/output.img
else
	@$(ECHO) "===== Windows Generate CSTM Image Process ====="
	$(CP) $(APPL_FULL_NAME).elf $(IMAGE_GEN_TOOL_INPUT_DIR)
	$(CP) $(APPL_FULL_NAME).map $(IMAGE_GEN_TOOL_INPUT_DIR)
	@$(ECHO) "execute image_gen_cstm.exe"
ifeq ($(HOST_OS), Windows)
	@cd $(IMAGE_GEN_TOOL_DIR) &&\
	image_gen_cstm.exe
else
	cd $(IMAGE_GEN_TOOL_DIR) &&\
	./image_gen_cstm.exe
endif

	@$(ECHO) "===== Image for OTA ====="
	$(CP) $(IMAGE_GEN_TOOL_OUTPUT_DIR)\output.img $(OTA_IMG_DIR)\output.img
	$(CP) $(IMAGE_GEN_TOOL_OUTPUT_DIR)\layout.bin $(OTA_IMG_DIR)\layout.bin
	@$(ECHO) "OTA Image path:" $(IMAGE_GEN_TOOL_OUTPUT_DIR)\output.img
endif
	

ota :
	@$(ECHO) "===== OTA Process ====="
ifeq ($(TOOLCHAIN), gnu)	 
	$(CP) $(IMAGE_GEN_TOOL_OUTPUT_DIR)/output.img $(OTA_IMG_DIR)/output.img
	$(CP) $(IMAGE_GEN_TOOL_OUTPUT_DIR)/layout.bin $(OTA_IMG_DIR)/layout.bin
else
	$(CP) $(IMAGE_GEN_TOOL_OUTPUT_DIR)\output.img $(OTA_IMG_DIR)\output.img
	$(CP) $(IMAGE_GEN_TOOL_OUTPUT_DIR)\layout.bin $(OTA_IMG_DIR)\layout.bin
endif
	@$(ECHO) "Please execute ota tool"

menuconfig :
	@$(ECHO) "Set parameters of image generation tool"
ifeq ($(TOOLCHAIN), mw)
ifeq ($(HOST_OS), Windows)
	@cd $(IMAGE_GEN_TOOL_DIR) &&\
	menuconfig_mw_v1.0.bat
else
	@./$(IMAGE_GEN_TOOL_DIR)/menuconfig_mw_v1.0.sh
endif
else
	@chmod 777 $(IMAGE_GEN_TOOL_DIR)/menuconfig_gnu_v1.0.sh
	@./$(IMAGE_GEN_TOOL_DIR)/menuconfig_gnu_v1.0.sh
endif

ifeq ($(BOARD), nsim)
ifeq ($(DBG), arc-elf32-gdb)
ifeq ($(VALID_TCF),)
nsim :
else
nsim : $(EMBARC_GENERATED_DIR)/$(GENE_NSIM_PROPS)
endif
	@$(ECHO) "Start nSim Standalone"
	$(NSIMDRV) -gdb -port 1234 -p nsim_emt=1 $(NSIMDRV_OPT)
endif
endif

#####RULES FOR GENERATING ARGUMENT FILE USING TCF#####
$(EMBARC_GENERATED_DIR)/$(GENE_TCF): $(VALID_TCF) $(EMBARC_GENERATED_DIR)/.mkdir_done
ifeq ($(UPGRADE_TCF), 1)
## Upgrade TCF file needed.
	@$(ECHO) "Upgrade to latest TCF file $@"
	$(Q)$(TCFGEN) -q -i $< -o $@ -ob $(dir $@)/$(GENE_BCR_CONTENTS_TXT)
else
## No need to upgrade TCF file
	@$(ECHO) "Copy TCF file $< to $@"
#	$(Q)-$(IFEXISTFILE) $(subst /,$(PS),$@) $(ENDIFEXISTFILE) $(RM) $(subst /,$(PS),$@)
#	$(Q)$(CP) $(subst /,$(PS),$<) $(subst /,$(PS),$@)
	$(Q)$(TCFTOOL) -q -d IDE -o $@ $<
endif

$(EMBARC_GENERATED_DIR)/$(GENE_CCAC_ARG): $(EMBARC_GENERATED_DIR)/$(GENE_TCF)
	@$(ECHO) "Generate Metaware compiler argument file $@"
	$(Q)$(TCFTOOL) -q -x mw_compiler,$@ $<

$(EMBARC_GENERATED_DIR)/$(GENE_GCC_ARG): $(EMBARC_GENERATED_DIR)/$(GENE_TCF)
	@$(ECHO) "Generate ARC GNU compiler argument file $@"
	$(Q)$(TCFTOOL) -q -x gcc_compiler,$@ $<

$(EMBARC_GENERATED_DIR)/$(GENE_NSIM_PROPS): $(EMBARC_GENERATED_DIR)/$(GENE_TCF)
	@$(ECHO) "Generate nSIM properties file $@"
	$(Q)$(TCFTOOL) -q -x nSIM,$@ $<

$(EMBARC_GENERATED_DIR)/$(GENE_MDB_ARG): $(EMBARC_GENERATED_DIR)/$(GENE_TCF)
	@$(ECHO) "Generate Metaware Debugger argument file $@"
	$(Q)$(TCFTOOL) -q -x mw_debugger,$@ $<

$(EMBARC_GENERATED_DIR)/$(GENE_CORE_CONFIG_H): $(EMBARC_GENERATED_DIR)/$(GENE_TCF)
	@$(ECHO) "Generate ARC core config header file $@"
	$(Q)$(TCFTOOL) -q -x C_defines,$@ $<

$(EMBARC_GENERATED_DIR)/$(GENE_CORE_CONFIG_S): $(EMBARC_GENERATED_DIR)/$(GENE_TCF)
	@$(ECHO) "Generate ARC core config assembler file $@"
	$(Q)$(TCFTOOL) -q -x assembler_defines,$@ $<

$(EMBARC_GENERATED_DIR)/$(GENE_APEXEXTENSIONS_H): $(EMBARC_GENERATED_DIR)/$(GENE_TCF)
	@$(ECHO) "Generate ARC APEX externsion header file $@"
	-$(Q)$(TCFTOOL) -q -x apex_header,$@ $<

$(EMBARC_GENERATED_DIR)/$(GENE_APEXEXTENSIONS_S): $(EMBARC_GENERATED_DIR)/$(GENE_TCF)
	@$(ECHO) "Generate ARC APEX externsion assembler file $@"
	-$(Q)$(TCFTOOL) -q -x apex_assembly,$@ $<

$(EMBARC_GENERATED_DIR)/$(GENE_LINK_CMD_TXT): $(EMBARC_GENERATED_DIR)/$(GENE_TCF)
	@$(ECHO) "Generate Metaware Linker file from TCF $@"
	$(Q)$(TCFTOOL) -q -x linker_command_file,$@ $<

$(EMBARC_GENERATED_DIR)/$(GENE_MEMORY_X): $(EMBARC_GENERATED_DIR)/$(GENE_TCF)
	@$(ECHO) "Generate ARC GNU Linker file from TCF $@"
	$(Q)$(TCFTOOL) -q -x gnu_linker_command_file,$@ $<


#####RULES FOR GENERATING LINK FILE FROM TEMPLATE#####
.SECONDEXPANSION:
$(APPL_LINK_FILE): $(LINKER_SCRIPT_FILE) $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_GEN_LINKFILE)
	$(Q)$(CC) -c $(TCF_FLAGS) $(ALL_DEFINES) $(LINK_FILE_OPT) $< -o $@

#####RULES FOR GENERATING ELF FILE#####
.SECONDEXPANSION:
$(APPL_FULL_NAME).elf : $(ALL_GENERATED_DIRS_TMPFILES) $(CORE_ARG_FILES) $(APPL_LINK_FILE) $(APPL_OBJS) $(EXTRA_OBJS) $(INTEGRATE_OBJS) $(HWACCAUTOTEST_OBJS) $(SCENARIO_APP_OBJS) $(EVENTHANDLER_OBJS) $(EMBARC_LIB) $(OKAO_LIB) $(BOARD_OPEN_LIB_SOCKET) $(CV_LIB) $(LIB_LIB_DSP) $(BSS_LIB) $(MLI_LIB) $(SECURE_LIB) $(AUDIO_ALGO_LIB) $(ALANGO_ALGO_LIB) $(GNU_DEP_LIB) $(OPEN_LIBS) $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_LINK)
	$(Q)$(LD) $(LINK_OPT) $(APPL_OBJS) $(EXTRA_OBJS) $(INTEGRATE_OBJS) $(HWACCAUTOTEST_OBJS) $(SCENARIO_APP_OBJS) $(EVENTHANDLER_OBJS) $(LD_START_GROUPLIB) $(EMBARC_LIB) $(OKAO_LIB) $(BOARD_OPEN_LIB_SOCKET) $(CV_LIB) $(LIB_LIB_DSP) $(BSS_LIB) $(MLI_LIB) $(SECURE_LIB) $(AUDIO_ALGO_LIB) $(ALANGO_ALGO_LIB) $(GNU_DEP_LIB) $(APPL_LIBS) $(OPEN_LIBS) $(LD_SYSTEMLIBS) $(LD_END_GROUPLIB)  -o $@

#####RULES FOR ACHIEVING PRE-BUILT BSP LIBRARY#####
ifeq ($(LIB_BSP_PREBUILT), 1)
$(EMBARC_LIB) : 
ifeq "$(HOST_OS)" "Windows"
ifeq ($(IC_PACKAGE_SEL), LQFP128)
ifeq ($(OS_TYPE), )
	$(CP) .\library\prebuilt_lib\libembarc_128pin_mw.a $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a
else
	$(CP) .\library\prebuilt_lib\libembarc_128pin_mw_os.a $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a
endif
endif
ifeq ($(IC_PACKAGE_SEL), WLCSP38)
ifeq ($(OS_TYPE), )	
	$(CP) .\library\prebuilt_lib\libembarc_38pin_mw.a $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a
else
	$(CP) .\library\prebuilt_lib\libembarc_38pin_mw_os.a $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a
endif
endif
ifeq ($(IC_PACKAGE_SEL), QFP100)
	$(CP) .\library\prebuilt_lib\libembarc_100pin.a $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a
endif	
ifeq ($(IC_PACKAGE_SEL), QFN72)
ifeq ($(OS_TYPE), )	
	$(CP) .\library\prebuilt_lib\libembarc_72pin_mw.a $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a
else
	$(CP) .\library\prebuilt_lib\libembarc_72pin_mw_os.a $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a
endif	
endif
else
ifeq ($(IC_PACKAGE_SEL), LQFP128)
ifeq ($(TOOLCHAIN), mw)
ifeq ($(OS_TYPE), )
	$(CP) ./library/prebuilt_lib/libembarc_128pin_mw.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
else
	$(CP) ./library/prebuilt_lib/libembarc_128pin_mw_os.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
endif
else	
ifeq ($(OS_TYPE), )
	$(CP) ./library/prebuilt_lib/libembarc_128pin_gnu.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
else
	$(CP) ./library/prebuilt_lib/libembarc_128pin_gnu_os.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
endif	
endif	
endif
ifeq ($(IC_PACKAGE_SEL), WLCSP38)
ifeq ($(TOOLCHAIN), mw)
ifeq ($(OS_TYPE), )	
	$(CP) ./library/prebuilt_lib/libembarc_38pin_mw.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
else
	$(CP) ./library/prebuilt_lib/libembarc_38pin_mw_os.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
endif
else	
ifeq ($(OS_TYPE), )
	$(CP) ./library/prebuilt_lib/libembarc_38pin_gnu.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
else
	$(CP) ./library/prebuilt_lib/libembarc_38pin_gnu_os.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
endif
endif
endif
ifeq ($(IC_PACKAGE_SEL), QFP100)
	$(CP) ./library/prebuilt_lib/libembarc_100pin.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
endif	
ifeq ($(IC_PACKAGE_SEL), QFN72)
ifeq ($(TOOLCHAIN), mw)
ifeq ($(OS_TYPE), )	
	$(CP) ./library/prebuilt_lib/libembarc_72pin_mw.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
else
	$(CP) ./library/prebuilt_lib/libembarc_72pin_mw_os.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
endif
else	
ifeq ($(OS_TYPE), )
	$(CP) ./library/prebuilt_lib/libembarc_72pin_gnu.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
else
	$(CP) ./library/prebuilt_lib/libembarc_72pin_gnu_os.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a
endif	
endif		
endif
endif		
else
$(EMBARC_LIB) : $(ALL_GENERATED_DIRS_TMPFILES) $(CORE_ARG_FILES) $(ALL_LIBS) $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_ARCHIVE)
	$(Q)-$(IFEXISTFILE) $(subst /,$(PS),$(EMBARC_LIB)) $(ENDIFEXISTFILE) $(RM) $(subst /,$(PS),$(EMBARC_LIB))
ifeq ($(TOOLCHAIN), mw)	
	$(Q)$(AR) $(AR_OPT) $@ $(ALL_LIBS)
else
	echo "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
	echo $(ALL_OBJS)
	$(Q)$(AR) $(AR_OPT) $@ $(ALL_OBJS)
endif	
ifeq "$(HOST_OS)" "Windows"
ifeq ($(IC_PACKAGE_SEL), LQFP128)
ifeq ($(OS_TYPE), )		
	$(CP) $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a .\library\prebuilt_lib\libembarc_128pin_mw.a
else
	$(CP) $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a .\library\prebuilt_lib\libembarc_128pin_mw_os.a
endif
endif
ifeq ($(IC_PACKAGE_SEL), WLCSP38)
ifeq ($(OS_TYPE), )	
	$(CP) $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a .\library\prebuilt_lib\libembarc_38pin_mw.a
else
	$(CP) $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a .\library\prebuilt_lib\libembarc_38pin_mw_os.a
endif
endif
ifeq ($(IC_PACKAGE_SEL), QFP100)
	$(CP) $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a .\library\prebuilt_lib\libembarc_100pin.a
endif	
ifeq ($(IC_PACKAGE_SEL), QFN72)
ifeq ($(OS_TYPE), )	
	$(CP) $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a .\library\prebuilt_lib\libembarc_72pin_mw.a
else
	$(CP) $(BOARD_OUT_DIR)\$(BUILD_INFO)\libembarc.a .\library\prebuilt_lib\libembarc_72pin_mw_os.a
endif
endif
else
ifeq ($(IC_PACKAGE_SEL), LQFP128)
ifeq ($(TOOLCHAIN), mw)
ifeq ($(OS_TYPE), )		
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_128pin_mw.a
else
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_128pin_mw_os.a
endif
else	
ifeq ($(OS_TYPE), )
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_128pin_gnu.a
else
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_128pin_gnu_os.a
endif	
endif	
endif
ifeq ($(IC_PACKAGE_SEL), WLCSP38)
ifeq ($(TOOLCHAIN), mw)	
ifeq ($(OS_TYPE), )	
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_38pin_mw.a
else
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_38pin_mw_os.a
endif
else
ifeq ($(OS_TYPE), )
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_38pin_gnu.a
else
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_38pin_gnu_os.a
endif	
endif
endif
ifeq ($(IC_PACKAGE_SEL), QFP100)
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_100pin.a
endif	
ifeq ($(IC_PACKAGE_SEL), QFN72)
ifeq ($(TOOLCHAIN), mw)	
ifeq ($(OS_TYPE), )	
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_72pin_mw.a
else
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_72pin_mw_os.a
endif
else
ifeq ($(OS_TYPE), )
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_72pin_gnu.a
else
	$(CP) $(BOARD_OUT_DIR)/$(BUILD_INFO)/libembarc.a ./library/prebuilt_lib/libembarc_72pin_gnu_os.a
endif	
endif	
endif
endif
endif

$(SECURE_LIB) :
ifeq "$(HOST_OS)" "Windows"
	$(CP) .\library\prebuilt_lib\liblibsecurity_r16.a $(BOARD_OUT_DIR)\$(BUILD_INFO)\liblibsecurity.a
else
	$(CP) ./library/prebuilt_lib/liblibsecurity_r16.a $(BOARD_OUT_DIR)/$(BUILD_INFO)/liblibsecurity.a
endif

#####APPLICATION C/ASM/CPP SOURCE FILE COMPILING RULES#####
.SECONDEXPANSION:
$(APPL_COBJS) :$(APPL_OUT_DIR)/%.o: %.c $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_COMPILE)
	$(Q)$(CC) -c $(TCF_FLAGS) $(ALL_DEFINES) $(COMPILE_OPT) $< -o $@

.SECONDEXPANSION:
$(APPL_CXXOBJS) : $(APPL_OUT_DIR)/%.o: %.cpp $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_COMPILE)
	$(Q)$(CXX) -c $(TCF_FLAGS) $(ALL_DEFINES) $(CXX_COMPILE_OPT) $< -o $@

.SECONDEXPANSION:
$(APPL_CCOBJS) : $(APPL_OUT_DIR)/%.o: %.cc $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_COMPILE)
	$(Q)$(CXX) -c $(TCF_FLAGS) $(ALL_DEFINES) $(CXX_COMPILE_OPT) $< -o $@

.SECONDEXPANSION:
$(APPL_ASMOBJS): $(APPL_OUT_DIR)/%.o: %.s $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_ASSEMBLE)
	$(Q)$(CC) -c $(TCF_FLAGS) $(ALL_DEFINES) $(ASM_OPT) $< -o $@

#####DEFAULT C/ASM/CPP SOURCE FILE COMPILING RULES FOR CPU/BOARD/LIBRARY/MIDDLEWARE/OS/EXTRA#####
.SECONDEXPANSION:
$(OUT_DIR)/%.o :$(EMBARC_ROOT)/%.c $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_COMPILE)
	$(Q)$(CC) -c $(TCF_FLAGS) $(ALL_DEFINES) $(COMPILE_OPT) $< -o $@

.SECONDEXPANSION:
$(OUT_DIR)/%.o :$(EMBARC_ROOT)/%.cpp $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_COMPILE)
	$(Q)$(CC) -c $(TCF_FLAGS) $(ALL_DEFINES) $(CXX_COMPILE_OPT) $< -o $@

.SECONDEXPANSION:
$(OUT_DIR)/%.o :$(EMBARC_ROOT)/%.cc $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_COMPILE)
	$(Q)$(CXX) -c $(TCF_FLAGS) $(ALL_DEFINES) $(CXX_COMPILE_OPT) $< -o $@

.SECONDEXPANSION:
$(OUT_DIR)/%.o :$(EMBARC_ROOT)/%.s $$(COMMON_COMPILE_PREREQUISITES)
	$(TRACE_ASSEMBLE)
	$(Q)$(CC) -c $(TCF_FLAGS) $(ALL_DEFINES) $(ASM_OPT) $< -o $@

#####RULES FOR CREATING REQUIRED DIRECTORIES#####
%/.mkdir_done:
	$(TRACE_CREATE_DIR)
	$(TRY_MK_OBJDIR)
	@$(ECHO) $(@D) > $@

#####RULES FOR GENERATING DUMP/DASM/BIN/HEX FILE#####
$(APPL_FULL_NAME).dump : $(APPL_FULL_NAME).elf
	@$(ECHO) "Dumping $<"
	$(Q)$(DMP) $(DMP_OPT) $<  > $@

$(APPL_FULL_NAME).dasm : $(APPL_FULL_NAME).elf
	@$(ECHO) "Disassembling $<"
	$(Q)$(DMP) $(DASM_OPT) $<  > $@

$(APPL_FULL_NAME).bin : $(APPL_FULL_NAME).elf
	@$(ECHO) "Generating Binary $@"
	$(Q)$(OBJCOPY) $(ELF2BIN_OPT) $< $@

$(APPL_FULL_NAME).hex : $(APPL_FULL_NAME).elf
	@$(ECHO) "Generating Intel Hex File $@"
	$(Q)$(ELF2HEX) $(ELF2HEX_INOPT) $< $(ELF2HEX_OUTOPT) $@

$(BSS_LIB): $(LIB_BSS_OBJS)
	$(TRACE_ARCHIVE)
	$(Q)$(AR) $(AR_OPT) $@ $(LIB_BSS_OBJS)
#####RULES FOR WORKAROUNDS#####
<built-in> :
	@$(ECHO) "Rules to fix built-in missing caused by metaware compiler 2014.12"

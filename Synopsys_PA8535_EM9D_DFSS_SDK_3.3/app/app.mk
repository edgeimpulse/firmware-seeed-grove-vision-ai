##
# application source dirs
##
override ALGO_TYPE := $(strip $(ALGO_TYPE))
override LINKER_SCRIPT_FILE := $(strip $(LINKER_SCRIPT_FILE))

APPL_CSRC_DIR = . $(EMBARC_ROOT)/app
APPL_ASMSRC_DIR = . $(EMBARC_ROOT)/app
APPL_INC_DIR = . $(EMBARC_ROOT)/app 

### Himax Internal Use #####
ifneq ("$(findstring CLI,$(strip $(APP_TYPE)))", "")
include $(EMBARC_ROOT)/app/integrate/integrate.mk
endif
ifneq ("$(findstring HWACCBYTPG,$(strip $(APP_TYPE)))", "")
include $(EMBARC_ROOT)/app/hwaccautotest/hwaccautotest.mk
endif

### For Product application ####
include $(EMBARC_ROOT)/app/scenario_app/scenario_app.mk


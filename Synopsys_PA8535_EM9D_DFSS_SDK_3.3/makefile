## embARC application makefile template ##
### You can copy this file to your application folder
### and rename it to makefile.
##

##
# Selected OS
#freertos
#tx
##
#OS_SEL ?= tx

# Application name
APPL ?= WEI_FW

# Optimization Level
# Please Refer to toolchain_xxx.mk for this option
OLEVEL ?= O2

##
# Current Board And Core
##
BOARD ?= socket
BD_VER ?= 24
CUR_CORE ?= arcem9d_wei_r16
##
# select debugging jtag
##
JTAG ?= usb

##
# IC package select : LQFP128/WLCSP38/QFP100/QFN72
##

IC_PACKAGE_SEL = QFN72

##
# Set toolchain
## gnu or mw
TOOLCHAIN ?= gnu

##
# Set OS type
#RTOS
#TX
##
#OS_TYPE ?= TX

##
# Uncomment following options
# if you want to set your own heap and stack size
# Default settings see options.mk
##
#HEAPSZ ?= 29000
HEAPSZ ?= 32768
#HEAPSZ ?= 131072
#STACKSZ ?= 8192


##
# support TLS function?
##
#TLS_ENABLE ?= 1

##
# Uncomment following options
# if you want to add your own library into link process
# For example:
# If you want link math lib for gnu toolchain,
# you need to set the option to -lm
##
#APPL_LIBS ?=

##
# root dir of embARC
##
EMBARC_ROOT = .

##
# library support feature
# Add new library here
# The source code should be loacted in ~\library\{lib_name}\
# sensordp : for hwacc datapath
# security : for security library
##
LIB_SEL = security

##
# middleware support feature
# Add new middleware here
# The source code should be loacted in ~\middleware\{mid_name}\
##
MID_SEL =

##
# CIS_SENSOR support feature HM_COMMON, HM1245, HM2140, HM01B0_MONO, HM01B0_BAYER
# HM0360_MONO, HM0360_MONO_OSC, HM0360_BAYER, HM0360_BAYER_OSC, HM11B1, HM11B1_REVC
# HM0360_MONO_REVB, HM0360_MONO_OSC_REVB, HM0360_BAYER_REVB, HM0360_BAYER_OSC_REVB
##
CIS_SEL = HM_COMMON
##
# CIS_XSHUTDOWN_PIN_SEL XSHUTDOWN_SGPIO0(FPGA board), XSHUTDOWN_SGPIO1(Socket board, AIOT board)
##
CIS_XSHUTDOWN_PIN_SEL = XSHUTDOWN_SGPIO1

##
# application defines
# Add any definition to enable/disable any feature of application
# EX: -DCLI_ENABLE - Support CLI command for System/IP verification
#     -DEVENT_PROCESS - Support Event Create/Handler for System Usage
##
APPL_DEFINES =

# USING Pre-built BSP library
# 1 for enable
# other for disable
##
LIB_BSP_PREBUILT = 1

# USING Pre-built CV library
# 1 for enable
# other for disable
##
LIB_CV_PREBUILT = 0

# USING Pre-built AUDIO library
# 1 for enable
# other for disable
##
LIB_AUDIO_ALGO_PREBUILT = 1

# USING latest AUDIO library
# 1 for using latest AUDIO library
# other for old AUDIO library
##
USE_LATEST_LIB_AUDIO_ALGO = 0

# USING TONE AUDIO library
# 1 for enable
# other for disable
##
USE_TONE_LIB_AUDIO_ALGO = 0

# USING Pre-built ALANGO library
# 1 for enable
# other for disable
##
LIB_AUDIO_ALANGO_PREBUILT = 1

# USING Pre-built AZ_SDK library
# 1 for enable
# other for disable
##
LIB_AZ_SDK_PREBUILT = 1

# USING Pre-built NETXDUO library
# 1 for enable
# other for disable
##
LIB_NETXDUO_PREBUILT = 1


# Flag for pure board initial(no peripheral initial)
# 1 for enable
# other for disable
##
#PURE_BOARD_INIT = 1


APP_TYPE ?= unknown

##
#  TFLITE_MICRO_GOOGLE_PERSON
#  TFLITE_MICRO_YOLO_FASTEST
##
ALGO_TYPE = TFLITE_MICRO_GOOGLE_PERSON


LINKER_SCRIPT_FILE =
##
# Add new external device here
# The source code should be located in ~\external\{device_name}\
##
EXT_DEV_LIST = 

# application makefile
include $(EMBARC_ROOT)/app/app.mk

# include current project makefile
COMMON_COMPILE_PREREQUISITES += makefile

### Options above must be added before include options.mk ###
# include key embARC build system makefile
override EMBARC_ROOT := $(strip $(subst \,/,$(EMBARC_ROOT)))
include $(EMBARC_ROOT)/options/options.mk

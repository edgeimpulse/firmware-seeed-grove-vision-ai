##
#  IC_PACKAGE_SEL
##
ifeq ($(IC_PACKAGE_SEL), LQFP128)
APPL_DEFINES += -DIC_PACKAGE_LQFP128
endif
ifeq ($(IC_PACKAGE_SEL), WLCSP38)
APPL_DEFINES += -DIC_PACKAGE_WLCSP38
endif
ifeq ($(IC_PACKAGE_SEL), QFP100)
APPL_DEFINES += -DIC_PACKAGE_QFP100
endif
ifeq ($(IC_PACKAGE_SEL), QFN72)
APPL_DEFINES += -DIC_PACKAGE_QFN72
endif
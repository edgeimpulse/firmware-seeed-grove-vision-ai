# devices root declaration
EXTERNAL_ROOT = $(EMBARC_ROOT)/external
EXT_INCDIR += $(EXTERNAL_ROOT)/inc $(EXTERNAL_ROOT)

EXT_DEV_LIST += cis/hm_common
ifeq ($(CIS_SEL), HM1245)
EXT_DEV_LIST += cis/hm1245
endif
ifeq ($(CIS_SEL), HM01B0_MONO) 
EXT_DEV_LIST += cis/hm01b0
endif
ifeq ($(CIS_SEL), HM01B0_BAYER) 
EXT_DEV_LIST += cis/hm01b0
endif
ifeq ($(CIS_SEL), HM2140)
EXT_DEV_LIST += cis/hm2140
endif
#HM0360_MONO
ifeq ($(CIS_SEL), HM0360_MONO)
EXT_DEV_LIST += cis/hm0360
endif
#HM0360_MONO_OSC
ifeq ($(CIS_SEL), HM0360_MONO_OSC)
EXT_DEV_LIST += cis/hm0360
endif
#HM0360_BAYER
ifeq ($(CIS_SEL), HM0360_BAYER)
EXT_DEV_LIST += cis/hm0360
endif
#HM0360_BAYER_OSC
ifeq ($(CIS_SEL), HM0360_BAYER_OSC)
EXT_DEV_LIST += cis/hm0360
endif
#HM11B1
ifeq ($(CIS_SEL), HM11B1)
EXT_DEV_LIST += cis/hm11b1
endif
#HM11B1_REVC
ifeq ($(CIS_SEL), HM11B1_REVC)
EXT_DEV_LIST += cis/hm11b1_revc
endif
#HM0360_MONO_REVB
ifeq ($(CIS_SEL), HM0360_MONO_REVB)
EXT_DEV_LIST += cis/hm0360_revb
endif
#HM0360_MONO_OSC
ifeq ($(CIS_SEL), HM0360_MONO_OSC_REVB)
EXT_DEV_LIST += cis/hm0360_revb
endif
#HM0360_BAYER
ifeq ($(CIS_SEL), HM0360_BAYER_REVB)
EXT_DEV_LIST += cis/hm0360_revb
endif
#HM0360_BAYER_OSC
ifeq ($(CIS_SEL), HM0360_BAYER_OSC_REVB)
EXT_DEV_LIST += cis/hm0360_revb
endif

# external device rules
ifdef EXT_DEV_LIST
	override EXT_DEV_LIST := $(sort $(strip $(EXT_DEV_LIST)))
	EXT_DEV_MKS = $(foreach EXT_DEV, $(EXT_DEV_LIST), $(join $(EXTERNAL_ROOT)/$(EXT_DEV)/, $(notdir $(EXT_DEV)).mk))
	include $(EXT_DEV_MKS)
endif


# platform root declaration
DEVICES_ROOT = $(EMBARC_ROOT)/platform

##
# HIMAX@WILL<make> : update platform tree
# ~\platform\
# 		~\hwacc\
#		~\peripheral\
#		~\sys\
#		~\inc\
##
DEV_INCDIR += $(DEVICES_ROOT)/inc $(DEVICES_ROOT)

##
# platform (onchip ip) support feature
# Add all of supported ip list here
# The source code should be located in ~\platform\{[peripheral|hwacc|sys]}\{ip_name}\
##
ONCHIP_IP_LIST		?= peripheral/i2s \
			peripheral/iic \
			peripheral/spi_m \
			peripheral/spi_s \
			peripheral/uart \
			peripheral/iomux \
			peripheral/pdm \
			sys/rtc \
			sys/timer \
			sys/clkgen \
			sys/pwm \
			sys/pmu \
			sys/inp \
			sys/sensorctrl \
			sys/tpg \
			sys/edm \
			sys/adcc \
			sys/inp1bitparser \
			sys/trim \
			hwacc/DP \
			hwacc/2x2 \
			hwacc/5x5 \
			hwacc/CDM \
			hwacc/JPEG \
			hwacc/xDMA \
			hwacc/RS \
			hwacc/RSDMA \
			hwacc/HOG \
			hwacc/HOGDMA \
			hwacc/uDMA 

# onchip ip rules
ifdef ONCHIP_IP_LIST
	override ONCHIP_IP_LIST  := $(sort $(strip $(ONCHIP_IP_LIST)))
	DEV_CSRCDIR += $(foreach ONCHIP_IP, $(ONCHIP_IP_LIST), $(addprefix $(DEVICES_ROOT)/, $(ONCHIP_IP)))
	DEV_INCDIR += $(foreach ONCHIP_IP, $(ONCHIP_IP_LIST), $(addprefix $(DEVICES_ROOT)/, $(ONCHIP_IP)))
endif

# opened source files
DEV_OPEN_CSRC += $(DEVICES_ROOT)/peripheral/spi_m/spi_master_protocol.c \
				$(DEVICES_ROOT)/peripheral/spi_s/spi_slave_protocol.c \
				$(DEVICES_ROOT)/peripheral/uart/uart_protocol.c \
				$(EMBARC_ROOT)/library/common/console_io.c \
				$(EMBARC_ROOT)/external/cis/hm_common/hx_drv_CIS_common.c


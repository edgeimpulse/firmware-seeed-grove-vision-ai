#ifndef HX_DRV_P021_H_
#define HX_DRV_P021_H_

#include <stdint.h>
/****************************************************
 * ENUM Declaration                                 *
 ***************************************************/
/**
 * \enum HX_DRV_ERROR_E
 * \brief Himax driver error code
 */
typedef enum __attribute__((packed)) {
    HX_DRV_LIB_PASS = 0,  /**< Error code - PASS */
    HX_DRV_LIB_ERROR = -1, /**< Error code - FAIL */
	HX_DRV_LIB_NODATA = -2, /**< Error code - no DATA feedback */
} HX_DRV_ERROR_E;

/**
 * \enum HX_DRV_GPIO_E
 * \brief Himax driver GPIO selection
 */
typedef enum __attribute__((packed)) {
    HX_DRV_PGPIO_0 = 0,  /**< Select GPIO number 0  */
    HX_DRV_PGPIO_1 = 1,  /**< Select GPIO number 1 */
    HX_DRV_PGPIO_2 = 2,  /**< Select GPIO number 2 */
} HX_DRV_GPIO_E;

/**
 * \enum HX_DRV_GPIO_DIRCTION_E
 * \brief Himax driver GPIO direction, including input and output direction
 */
typedef enum __attribute__((packed)) {
    HX_DRV_GPIO_INPUT = 2,    /**< Select GPIO as input direction  */
    HX_DRV_GPIO_OUTPUT = 3,   /**< Select GPIO as output direction  */
} HX_DRV_GPIO_DIRCTION_E;

/**
 * \enum HX_DRV_LED_SELECT_E
 * \brief Himax driver LED selection
 */
typedef enum __attribute__((packed)) {
    HX_DRV_LED_RED = 6,    /**< Select Red LED  */
    HX_DRV_LED_GREEN = 8,  /**< Select Green LED  */
} HX_DRV_LED_SELECT_E;

/**
 * \enum HX_DRV_LED_ONOFF_E
 * \brief Himax driver LED on off operation
 */
typedef enum __attribute__((packed)) {
    HX_DRV_LED_OFF = 0,    /**< LED on operation  */
    HX_DRV_LED_ON = 1,     /**< LED off operation  */
} HX_DRV_LED_ONOFF_E;

/**
 * \enum HX_DRV_SPI_TYPE
 * \brief Himax driver SPI transfer data type
 */
typedef enum __attribute__((packed)) {
	SPI_TYPE_JPG               = 0x01,    /**< transfer data type is JPEG image */
	SPI_TYPE_RAW               = 0x02,    /**< transfer data type is RAW image  */
	SPI_TYPE_META_DATA         = 0x03,    /**< transfer data type is meta-data  */
	SPI_TYPE_PDM     	 	   = 0x04,    /**< transfer data type is audio PDM data  */
}HX_DRV_SPI_TYPE;

/**
 * \enum HX_DRV_SHARE_MODE_E
 * \brief Himax driver share pin switch
 */
typedef enum __attribute__((packed)) {
	SHARE_MODE_SPIM            = 0x01,    /**< switch share pin to spi master mode */
	SHARE_MODE_I2CM            = 0x02,    /**< switch share pin to i2c master mode */
}HX_DRV_SHARE_MODE_E;

/**
 * \enum HX_DRV_UART_BAUDRATE_E
 * \brief Himax driver UART baud rate selection
 */
typedef enum __attribute__((packed)) {
	UART_BR_9600 = 0,		/**< UART bard rate 9600bps */
	UART_BR_14400 = 1,		/**< UART bard rate 14400bps */
	UART_BR_19200 = 2,		/**< UART bard rate 19200bps */
	UART_BR_38400 = 3,		/**< UART bard rate 38400bps */
	UART_BR_57600 = 4,		/**< UART bard rate 57600bps */
	UART_BR_115200 = 5,		/**< UART bard rate 115200bps */
	UART_BR_230400 = 6,		/**< UART bard rate 230400bps */
	UART_BR_460800 = 7,		/**< UART bard rate 460800bps */
	UART_BR_921600 = 8,		/**< UART bard rate 921600bps */
}HX_DRV_UART_BAUDRATE_E;

/**
 * \enum HX_DRV_QWIIC_CCS811_I2C_ADDR_E
 * \brief Himax driver CCS811 I2C address selection
 */
typedef enum __attribute__((packed)) {
    HX_DRV_QWIIC_CCS811_I2C_0X5A = 0,    /**< Select 0x5A */
    HX_DRV_QWIIC_CCS811_I2C_0X5B = 1,    /**< Select 0x5B */
} HX_DRV_QWIIC_CCS811_I2C_ADDR_E;


/**
 * \enum HX_DRV_QWIIC_BME280_I2C_ADDR_E
 * \brief  Himax driver BME280 I2C address selection
 */
typedef enum __attribute__((packed)) {
    HX_DRV_QWIIC_BME280_I2C_0X76 = 0,    /**< Select 0x76 */
    HX_DRV_QWIIC_BME280_I2C_0X77 = 1,    /**< Select 0x77 */
} HX_DRV_QWIIC_BME280_I2C_ADDR_E;


/****************************************************
 * Structure Definition                             *
 ***************************************************/

/**
 * \struct hx_drv_sensor_image_config_t
 * \brief Himax driver image sensor configuration
 */
typedef struct {
	uint32_t img_width;    /**< image width, assigned by Himax driver */
	uint32_t img_height;   /**< image height, assigned by Himax driver */
    uint32_t jpeg_address; /**< JPEG image address, assigned by Himax driver */
    uint32_t jpeg_size;    /**< JPEG image size, assigned by Himax driver */
    uint32_t raw_address;  /**< RAW image address, assigned by Himax driver */
    uint32_t raw_size;     /**< RAW image size, assigned by Himax driver */

} hx_drv_sensor_image_config_t;

/**
 * \struct hx_drv_mic_data_config_t
 * \brief Himax driver microphone configuration
 */
typedef struct {
    uint32_t data_address;	/**< microphone data array address, assigned by Himax driver */
    uint32_t data_size;		/**< microphone data size in bytes about samples, assigned by Himax driver */

} hx_drv_mic_data_config_t;

/**
 * \struct hx_drv_gpio_config_t
 * \brief Himax driver GPIO configuration
 */
typedef struct {
	HX_DRV_GPIO_E gpio_pin;                 /**< GPIO pin, assigned by user */
    uint8_t gpio_data;                      /**< GPIO data. Assigned by user when as output direction. Assigned by Himax driver when as input direction */
    HX_DRV_GPIO_DIRCTION_E gpio_direction;  /**< GPIO direction, assigned by user */

} __attribute__((packed)) hx_drv_gpio_config_t;


/****************************************************
 * Function Declaration                             *
 ***************************************************/

#ifdef __cplusplus
extern "C" {
#endif
/**
 * \brief	Check current himax driver version.
 *
 * \param[out] major_ver		Major version of the driver
 * \param[out] minor_ver		Minor version of the driver
 * \retval	HX_DRV_LIB_PASS		Success
 */
extern HX_DRV_ERROR_E hx_drv_lib_version(uint32_t *major_ver, uint32_t *minor_ver);

/**
 * \brief	Check current platfrom ID.
 *
 * \param[out] id		return id of current platform
 * \retval	HX_DRV_LIB_PASS		Success
 */
extern HX_DRV_ERROR_E hx_drv_id_get(uint32_t *id);

/**
 * \brief	Image sensor initialization, it try to initial sensor and query one JPEG frame + one RAW frame to target address.
 *          Current image sensor use for himax_we1_evb is HM0360, image resolution is 640x480.
 *			If initial step is PASS, one JPEG and one RAW frame will be captured in the memory address and sensor back to standby mode.
 *			Ex.
 * 				hx_drv_sensor_image_config_t pimg_config;
 *
 *				//sensor start capture and start streaming
 * 				if(hx_drv_sensor_initial(&pimg_config) != HX_DRV_LIB_PASS)
 * 					return ;
 *
 * 				//image information will be provided in "pimg_config"
 * 				//please check structure "hx_drv_sensor_image_config_t" for more information
 *
 * \param[out] pimg_config		Img_width, img_height, jpeg_address, jpeg_size, raw_address, raw_size will be assigned by driver after initial success
 * \retval	HX_DRV_LIB_PASS		Initial success
 * \retval	HX_DRV_LIB_ERROR	Initial fail
 */
extern HX_DRV_ERROR_E hx_drv_sensor_initial(hx_drv_sensor_image_config_t *pimg_config);

/**
 * \brief	Query Image sensor and capture one JPEG frame and one RAW frame, sensor back to standby mode then.
 * 			both RAW frame and JPEG frame will be provided to target address.
 *			Ex.
 * 				hx_drv_sensor_image_config_t pimg_config;
 *
 *				//sensor start capture and start streaming
 * 				if(hx_drv_sensor_initial(&pimg_config) != HX_DRV_LIB_PASS)
 * 					return ;
 *
 * 			    if(hx_drv_spim_init() != HX_DRV_LIB_PASS)
 * 					return ;
 *
 * 				//continue capture frame
 * 				while(1) {
 *
 * 					//capture one frame
 *					if(hx_drv_sensor_capture(&pimg_config) != HX_DRV_LIB_PASS)
 *						break ;
 *
 * 					//JPEG image data is ready at memory address "pimg_config.jpeg_address"
 *					//send JPEG image out via SPI master
 *					if(hx_drv_spim_send(pimg_config.jpeg_address, pimg_config.jpeg_size, SPI_TYPE_JPG) != HX_DRV_LIB_PASS)
 *						break ;
 *
 *					//RAW image data is ready at memory address "raw_address"
 *					//send RAW image out via SPI master
 *					if(hx_drv_spim_send(pimg_config.raw_address, pimg_config.raw_size, SPI_TYPE_RAW) != HX_DRV_LIB_PASS)
 *						break ;
 * 				}

 *
 * \param[out] pimg_config		Jpeg_size, raw_size of the captured frame will be given after capture success
 * \retval	HX_DRV_LIB_PASS		Capture one frame success
 * \retval	HX_DRV_LIB_ERROR	Capture operation fail
 */
extern HX_DRV_ERROR_E hx_drv_sensor_capture(hx_drv_sensor_image_config_t *pimg_config);

/**
 * \brief	WE1 Stop capture and Sensor stop streaming. Please use API "hx_drv_sensor_initial" if stop and want to re-start
 *			Ex.
 * 				hx_drv_sensor_image_config_t pimg_config;
 *
 *				//sensor start capture and start streaming
 * 				if(hx_drv_sensor_initial(&pimg_config) != HX_DRV_LIB_PASS)
 * 					return ;
 *
 * 				...
 *				if(hx_drv_sensor_capture(&pimg_config) != HX_DRV_LIB_PASS)
 *					return ;
 *
 *				//sensor stop capture and stop streaming
 *				if(hx_drv_sensor_stop_capture() != HX_DRV_LIB_PASS)
 *					return ;
 *
 *				...
 *				//restart sensor
 *				if(hx_drv_sensor_initial(&pimg_config) != HX_DRV_LIB_PASS)
 * 					return ;
 *
 * \retval	HX_DRV_LIB_PASS		Stop capture and streaming success
 * \retval	HX_DRV_LIB_ERROR	Stop capture and streaming fail
 */
extern HX_DRV_ERROR_E hx_drv_sensor_stop_capture();

/**
 * \brief	Image sensor start streaming, it often use after stream off and want to re-start streaming.
 * 			For normal use case, you can skip this API and use
 * 			- hx_drv_sensor_initial and hx_drv_sensor_capture APIs to capture operation
 * 			- hx_drv_sensor_stop_capture and hx_drv_sensor_initial APIs to stop and restart operation
 *
 * \retval	HX_DRV_LIB_PASS		Start streaming success
 * \retval	HX_DRV_LIB_ERROR	Start streaming fail
 */
extern HX_DRV_ERROR_E hx_drv_sensor_stream_on();

/**
 * \brief	Image sensor stop streaming.
 * 			For normal use case, you can skip this API and use
 * 			- hx_drv_sensor_initial and hx_drv_sensor_capture APIs to capture operation
 * 			- hx_drv_sensor_stop_capture and hx_drv_sensor_initial APIs to stop and restart operation
 *
 * \retval	HX_DRV_LIB_PASS		Stop streaming success
 * \retval	HX_DRV_LIB_ERROR	Stop streaming fail
 */
extern HX_DRV_ERROR_E hx_drv_sensor_stream_off();

/**
 * \brief	Image scale down function, make image resolution smaller. Please notice that it will also changes
 *          in_image from UINT8 (0~255) domain to out_image INT8(-128~127) domain.
 *
 * \param[in] in_image			Input image address
 * \param[in] in_image_width	Input image width in pixel
 * \param[in] in_image_height	Input image height in pixel
 * \param[in] out_image			Output image address
 * \param[in] out_image_width	Output image width in pixel, it should be smaller than input image width
 * \param[in] out_image_height	Output image height in pixel, it should be smaller than input image height
 * \retval	HX_DRV_LIB_PASS		Stop streaming success
 * \retval	HX_DRV_LIB_ERROR	Stop streaming fail
 */
extern HX_DRV_ERROR_E hx_drv_image_rescale(uint8_t*in_image, int32_t in_image_width, int32_t in_image_height,  int8_t*out_image, int32_t out_image_width, int32_t out_image_height);

/**
 * \brief	3-axis accelerometer initialization, it start to retrieve data after initial.
 *          It will initial accelerometer with sampling rate 119 Hz, bandwidth 50 Hz, scale selection 4g at continuous mode.
 *
 * \retval	HX_DRV_LIB_PASS		Initial success
 * \retval	HX_DRV_LIB_ERROR	Initial fail
 */
extern HX_DRV_ERROR_E hx_drv_accelerometer_initial();

/**
 * \brief	Receive data from 3-axis accelerometer.
 *			Ex.
 * 				int available_count = 0;
 * 				if (hx_drv_accelerometer_initial() != HX_DRV_LIB_PASS)
 * 					return;
 *
 * 				available_count = hx_drv_accelerometer_available_count();
 * 				for (int i = 0; i < available_count; i++) {
 * 					float x, y, z;
 * 					hx_drv_accelerometer_receive(&x, &y, &z);
 * 				}
 *
 * \param[out] x				Data in x-axis
 * \param[out] y				Data in y-axis
 * \param[out] z				Data in z-axis
 * \retval	HX_DRV_LIB_PASS		Receive data success
 * \retval	HX_DRV_LIB_ERROR	Receive data fail
 */
extern HX_DRV_ERROR_E hx_drv_accelerometer_receive(float *x, float *y, float *z);

/**
 * \brief	Check how many data in the accelerometer FIFO. each count represent 1 set of x-axis,y-axis,z-axis data.
 *
 * \retval	HX_DRV_LIB_PASS		Check success
 * \retval	HX_DRV_LIB_ERROR	Check fail
 */
extern uint8_t hx_drv_accelerometer_available_count();

/**
 * \brief	Microphone initialization, it will initial microphone setting. Please use hx_drv_mic_on() to start record audio after initial.
 *          Receive sampling rate is 16KHz and data format is PDM.
 *
 * \retval	HX_DRV_LIB_PASS		Initial success
 * \retval	HX_DRV_LIB_ERROR	Initial fail
 */
extern HX_DRV_ERROR_E hx_drv_mic_initial();

/**
 * \brief	Capture Single channel audio data from Microphone. Each sample for mono PDM is 16bits little-endian signed data.
 *          During each millisecond, there will be 16 samples(32 bytes) of audio data storage to target address.
 * 			This API is provided for TFLM micro_speech example, which includes some previous audio data for sliding window usage.
 * 			Please use API "hx_drv_mic_capture_dual" for normal case.
 *
 * \param[out] pmic_config		Received data will be assigned by driver with address and size count in bytes about samples.
 * \retval	HX_DRV_LIB_PASS		Capture success
 * \retval	HX_DRV_LIB_ERROR	Capture fail
 */
extern HX_DRV_ERROR_E hx_drv_mic_capture(hx_drv_mic_data_config_t *pmic_config);

/**
 * \brief	Get current time-stamp from audio buffer in driver.
 * 			For current Himax mic driver, time stamp will updated every 100ms.
 *
 * \param[out] time				time-stamp represent in millisecond
 * \retval	HX_DRV_LIB_PASS		Capture success
 * \retval	HX_DRV_LIB_ERROR	Capture fail
 */
extern HX_DRV_ERROR_E hx_drv_mic_timestamp_get(int32_t *time);

/**
 * \brief	Turn on microphone, it will start to record audio. Please call hx_drv_mic_initial() first to initial microphone.
 *
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_mic_on();

/**
 * \brief	Turn off microphone, it will stop receive audio data and time-stamp reset back to zero.
 * 			use hx_drv_mic_on() when need to start again. Please call hx_drv_mic_initial() first to initial microphone.
 *			Ex.
 *				if(hx_drv_mic_initial() != HX_DRV_LIB_PASS)
 *					return ;
 *
 *				if(hx_drv_mic_on() != HX_DRV_LIB_PASS)
 *					return ;
 *
 *				...
 *				// stop recording
 *				if(hx_drv_mic_off() != HX_DRV_LIB_PASS)
 *					return ;
 *
 *				//re-start
 *				if(hx_drv_mic_on() != HX_DRV_LIB_PASS)
 *					return ;
 *
 *
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_mic_off();

/**
 * \brief	Capture Dual channel audio data from Microphone. Each sample for dual PDM are 32 bits, includes Left channel 16bits little-endian signed data
 * 			and right channel 16bits little-endian signed data.
 *          During each millisecond, there will be 16 samples(64 bytes) of audio data storage to target address.
 *          This API often called when get changes by API "hx_drv_mic_timestamp_get"
 * 			This API will retrieve latest 100ms audio data from microphone if return HX_DRV_LIB_PASS. Once the API is done, you can get data from target address
 * 			and wait next time stamp changes (which means wait 100ms) to get it return HX_DRV_LIB_PASS (It will return HX_DRV_LIB_ERROR during time stamp changes).
 *			Ex.
 *				typedef struct {
 *					int16_t left;
 *					int16_t right;
 *				}META_AUDIO_t;
 *
 *				#define AUD_BLK_100MS_SZ 1600
 *				...
 *
 *				hx_drv_mic_data_config_t slt_audio_config;
 *				int32_t time_prev = 0, time_cur = 0;
 *				META_AUDIO_t audio_clip[AUD_BLK_100MS_SZ];
 *
 *				if(hx_drv_mic_initial() != HX_DRV_LIB_PASS)
 *					return ;
 *
 *				if(hx_drv_mic_on() != HX_DRV_LIB_PASS)
 *					return ;
 *
 *				if(hx_drv_mic_timestamp_get(&time_prev) != HX_DRV_LIB_PASS)
 *					return ;
 *				else
 *					time_cur = time_prev;
 *
 *				while(1) {
 *					while(time_cur == time_prev) {
 *						if(hx_drv_mic_timestamp_get(&time_cur) != HX_DRV_LIB_PASS)
 *							return ;
 *					}
 *
 *					time_prev = time_cur;
 *
 *					if(hx_drv_mic_capture_dual(&slt_audio_config)==HX_DRV_LIB_PASS) {
 *						memcpy((void*)audio_clip,(void*)slt_audio_config.data_address,slt_audio_config.data_size*sizeof(uint8_t));
 *						//audio left/right channel data can be found at META_AUDIO_t left/right array
 *						...
 *					}
 *				}
 *
 *
 * \param[out] pmic_config		Received data will be assigned by driver with address and size count in bytes about samples. For example,
 * 								if data_size is 6400, that means 1600 samples(100ms) of audio data in address.
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_mic_capture_dual(hx_drv_mic_data_config_t *pmic_config);
/**
 * \brief	UART initialization with given baud rate. This is for message output.
 * 			UART should be initial again if any change to baud rate
 * 			Ex.
 * 				hx_drv_uart_initial(UART_BR_115200);
 *
 * 				hx_drv_uart_print("UART baud rate set to 115200 bps");
 *
 * 				hx_drv_uart_initial(UART_BR_921600);
 *
 * 				hx_drv_uart_print("UART baud rate set to 921600 bps");
 *
 * \param[in] baud_rate			baud rate setting, support 9600bps to 921600bps
 * \retval	HX_DRV_LIB_PASS		Initial success
 * \retval	HX_DRV_LIB_ERROR	Initial fail
 */
extern HX_DRV_ERROR_E hx_drv_uart_initial(HX_DRV_UART_BAUDRATE_E baud_rate);

/**
 * \brief	Print message to UART port. Uart initial API hx_drv_uart_initial() should be called first.
 *
 * \param[in] fmt				Data to print through UART
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_uart_print(const char*fmt, ...);

/**
 * \brief	Get input from UART port. return HX_DRV_LIB_NODATA if nothing read back
 * 			Ex.
 * 				hx_drv_uart_initial(UART_BR_115200);
 * 				uint8_t get_ch = 0;
 *
 * 				if(hx_drv_uart_getchar(&get_ch) == HX_DRV_LIB_PASS)
 * 					 hx_drv_uart_print("hx_drv_uart_getchar: get [%c]\n", get_ch);
 *
 * \param[out] pch				It catch one character from UART
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 * \retval	HX_DRV_LIB_NODATA	Nothing get back
 */
extern HX_DRV_ERROR_E hx_drv_uart_getchar(uint8_t *pch);

/**
 * \brief	GPIO initialization, please set configuration direction to input/output with dedicated GPIO pin.
 *
 * \param[in/out] pgpio_config	It catch one character from UART
 * \retval	HX_DRV_LIB_PASS		Initial success
 * \retval	HX_DRV_LIB_ERROR	Initial fail
 */
extern HX_DRV_ERROR_E hx_drv_gpio_initial(hx_drv_gpio_config_t *pgpio_config);

/**
 * \brief	For GPIO output setting, set target gpio_data (0 or 1) to dedicated GPIO pin.
 *
 * \param[in/out] pgpio_config	gpio_data should be set to 0 or 1 for GPIO output
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_gpio_set(hx_drv_gpio_config_t *pgpio_config);

/**
 * \brief	Get value from dedicated GPIO pin.
 *
 * \param[out] pgpio_config		Read back data will be assigned to gpio_data by driver
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_gpio_get(hx_drv_gpio_config_t *pgpio_config);

/**
 * \brief	Turn target LED on.
 *
 * \param[in] led				selected LED to turn on
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_led_on(HX_DRV_LED_SELECT_E led);

/**
 * \brief	Turn target LED off.
 *
 * \param[in] led				selected LED to turn off
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_led_off(HX_DRV_LED_SELECT_E led);

/**
 * \brief	Timer initialization. It start to count tick after start operation.
 * 			Please notice that if you are also using SWUART device in your program, they share
 * 			the same timer. Using 'hx_drv_tick_get' across SWUART API should be avoided.
 *
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_tick_start(void);

/**
 * \brief	Get current tick in timer. Convert tick count to second based on WE_I working frequency which is 400Mhz now.
 * 			Please notice that tick count restart from zero when over UINT32_MAX
 * 			Ex.
 * 				 uint32_t tick_start = 0, tick_end = 0;
 * 				 hx_drv_uart_initial(UART_BR_115200);
 * 				 hx_drv_tick_start();
 *
 * 				 hx_drv_tick_get(&tick_start);
 * 				 // your code
 *
 * 				 hx_drv_tick_get(&tick_end);
 *
 * 				 hx_drv_uart_print("time used :%d(msec)\n", (tick_end-tick_start)/400000);
 *
 * \param[out] tick				fill tick address in the parameter and driver will fill tick count data to the address
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_tick_get(uint32_t *tick);

/**
 * \brief	I2c master control. use to set i2c with target ID, target address with data
 *
 * \param[in] slave_addr_sft	target device ID represent in 7-bits mode
 * \param[in] addr				target address to set data
 * \param[in] addr_len			target address size in bytes
 * \param[in] data				data array pointer
 * \param[in] data_len			data array size in bytes
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_i2cm_set_data(uint8_t slave_addr_sft, uint8_t *addr, uint32_t addr_len, uint8_t *data, uint32_t data_len);

/**
 * \brief	I2c master control. use to read i2c data with target ID
 *
 * \param[in] slave_addr_sft	target device ID represent in 7-bits mode
 * \param[in] addr				target address to read data
 * \param[in] addr_len			target address size in bytes
 * \param[out] data				data array pointer
 * \param[out] data_len			data array size in bytes
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_i2cm_get_data(uint8_t slave_addr_sft, uint8_t *addr, uint32_t addr_len, uint8_t *data, uint32_t data_len);

/**
 * \brief	spi master control initial
 *
 * \retval	HX_DRV_LIB_PASS		Initial success
 * \retval	HX_DRV_LIB_ERROR	Initial fail
 */
extern HX_DRV_ERROR_E hx_drv_spim_init();

/**
 * \brief	spi master send data from dedicated memory address
 *
 * \param[in] addr				data array address in memory to send
 * \param[in] size				data array size
 * \param[in] data_type			data type
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_spim_send(uint32_t addr, uint32_t size, HX_DRV_SPI_TYPE data_type);

/**
 * \brief	SPI master and I2C master share the same output pin, we need to switch to needed output mode.
 *          Default output mode is SHARE_MODE_SPIM
 *
 * \param[in] mode				select which device to output
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_share_switch(HX_DRV_SHARE_MODE_E mode);

/**
 * \brief	QWIIC MS8607 device initialization.
 *          Remember do 'hx_drv_share_switch(SHARE_MODE_I2CM)' first such that I2C master as the output pin.
 *
 * \retval	HX_DRV_LIB_PASS		Initial success
 * \retval	HX_DRV_LIB_ERROR	Initial fail
 */
extern HX_DRV_ERROR_E hx_drv_qwiic_ms8607_initial();

/**
 * \brief	QWIIC MS8607 device read sensor data.
 * 			Ex.
 * 				float p=0,t=0,h=0;
 * 				hx_drv_uart_initial(UART_BR_115200);
 * 				hx_drv_share_switch(SHARE_MODE_I2CM);
 * 				if(hx_drv_qwiic_ms8607_initial()!=HX_DRV_LIB_PASS) {
 * 					hx_drv_uart_print("hx_drv_ms8607_initial fail ");
 * 					return ;
 * 				}
 *
 * 				if(hx_drv_qwiic_ms8607_get_data(&t, &p, &h)==HX_DRV_LIB_PASS)
 * 					hx_drv_uart_print("p:%d mbar, t:%d Celsius, h:%d %%RH\n", (uint32_t)p, (int32_t)t, (uint32_t)h);
 **
 *
 *
 * \param[out] t_data			temperature data in Celsius degree
 * \param[out] p_data			pressure data in mbar unit
 * \param[out] h_data			humidity data in %RH
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_qwiic_ms8607_get_data(float* t_data, float* p_data, float* h_data);

/**
 * \brief	QWIIC CCS811 device initialization.
 *          Remember do 'hx_drv_share_switch(SHARE_MODE_I2CM)' first such that I2C master as the output pin.
 *
 * \param[in] i2caddr			CCS811 I2C address selection
 * \retval	HX_DRV_LIB_PASS		Initial success
 * \retval	HX_DRV_LIB_ERROR	Initial fail
 */
extern HX_DRV_ERROR_E hx_drv_qwiic_ccs811_initial(HX_DRV_QWIIC_CCS811_I2C_ADDR_E i2caddr);

/**
 * \brief	QWIIC CCS811 device read sensor data.
 * 			Ex.
 * 				uint16_t co2=0,tvoc=0;
 * 				hx_drv_uart_initial(UART_BR_115200);
 * 				hx_drv_share_switch(SHARE_MODE_I2CM);
 * 				if(hx_drv_qwiic_ccs811_initial(HX_DRV_QWIIC_CCS811_I2C_0X5B)!=HX_DRV_LIB_PASS) {
 * 					hx_drv_uart_print("hx_drv_ccs811_initial fail ");
 * 					return ;
 * 				}
 *
 * 				for (int i = 0; i < 10; i++)
 *              {
 *                  board_delay_cycle(1000 * BOARD_SYS_TIMER_MS_CONV);
 *                  if (hx_drv_qwiic_ccs811_get_data(&co2, &tvoc) == HX_DRV_LIB_PASS)
 *                  {
 *                      hx_drv_uart_print("CO2: %u ppm tVOC: %u ppb\n", co2, tvoc);
 *                  }
 *                  else
 *                  {
 *                      hx_drv_uart_print("Data not ready.\n");
 *                  }
 *              }
 *
 *
 *
 * \param[out] c_data			eC02 data in ppm unit
 * \param[out] t_data			TVOC data in ppb unit
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_qwiic_ccs811_get_data(uint16_t* c_data, uint16_t* t_data);

/**
 * \brief	QWIIC BME280 device initialization.
 *          Remember do 'hx_drv_share_switch(SHARE_MODE_I2CM)' first such that I2C master as the output pin.
 *
 * \param[in] i2caddr			BME280 I2C address selection
 * \retval	HX_DRV_LIB_PASS		Initial success
 * \retval	HX_DRV_LIB_ERROR	Initial fail
 */
extern HX_DRV_ERROR_E hx_drv_qwiic_bme280_initial(HX_DRV_QWIIC_BME280_I2C_ADDR_E i2caddr);

/**
 * \brief	QWIIC BME280 device read sensor data.
 * 			Ex.
 * 				float t=0,h=0;
 *	            uint32_t p=0;
 *	            hx_drv_uart_initial(UART_BR_115200);
 * 				hx_drv_share_switch(SHARE_MODE_I2CM);
 * 				if(hx_drv_qwiic_bme280_initial(HX_DRV_QWIIC_BME280_I2C_0X77)!=HX_DRV_LIB_PASS) {
 * 					hx_drv_uart_print("hx_drv_bme280_initial fail ");
 * 					return ;
 * 				}
 *
 * 				if(hx_drv_qwiic_bme280_get_data(&t, &p, &h)==HX_DRV_LIB_PASS)
 * 					hx_drv_uart_print("p:%d Pa, t:%d Celsius, h:%d %%RH\n", (uint32_t)p, (int32_t)t, (uint32_t)h);
 **
 *
 *
 * \param[out] t_data			temperature data in Celsius degree
 * \param[out] p_data			pressure data in units of kiloPascals
 * \param[out] h_data			humidity data in %RH
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_qwiic_bme280_get_data(float* t_data, uint32_t* p_data, float* h_data);

/**
 * \brief	!!Please notice that this Software UART API is an experimental function and just use for some example here:
 * 			https://github.com/HimaxWiseEyePlus/bsp_tflu/tree/master/HIMAX_WE1_EVB_example
 *
 * 			This is a Software UART function that uses GPIO as UART.
 * 			It uses a shared timer to count the baud rate, so please use only swuart related function from
 * 			initial to de-initial.
 * 			To initial the function, GPIO pin number for Transmit and receive should be given.
 * 			Software UART baud rate range is 9600bps to 460800bps.
 *
 * \param[in] tx_pin			GPIO pin enumeration for Transmit
 * \param[in] rx_pin			GPIO pin enumeration for Receive
 * \param[in] baud_rate			baud rate enumeration
 * \retval	HX_DRV_LIB_PASS		Initial success
 * \retval	HX_DRV_LIB_ERROR	Initial fail
 */
extern HX_DRV_ERROR_E hx_drv_swuart_initial(HX_DRV_GPIO_E tx_pin, HX_DRV_GPIO_E rx_pin, HX_DRV_UART_BAUDRATE_E baud_rate);

/**
 * \brief	!!Please notice that this Software UART API is an experimental function and just use for some example here:
 *			https://github.com/HimaxWiseEyePlus/bsp_tflu/tree/master/HIMAX_WE1_EVB_example
 *
 *			Transfer data to Software UART port.
 * 
 * \param[in] data				data array address in memory to send.
 * \param[in] data_len		    data array size in bytes.
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_swuart_write(const uint8_t *data, uint32_t data_len);

/**
 * \brief	!!Please notice that this Software UART API is an experimental function and just use for some example here:
 * 			https://github.com/HimaxWiseEyePlus/bsp_tflu/tree/master/HIMAX_WE1_EVB_example
 *
 *			Receive single byte data from Software UART port(nonblocking).
 *
 * \param[in] data				data array address for reading data back. you will get one byte of
 * 								data in the data array if the operation is successful.
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_NODATA	nothing in FIFO
 */
extern HX_DRV_ERROR_E hx_drv_swuart_single_read(const uint8_t* data);

/**
 * \brief	!!Please notice that this Software UART API is an experimental function and just use for some example here:
 * 			https://github.com/HimaxWiseEyePlus/bsp_tflu/tree/master/HIMAX_WE1_EVB_example
 *
 *			de-initial Software UART.
 *
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_swuart_deinitial();

/**
 * \brief	initial flash in WE1 and set it to XIP mode
 *
 *
 * \retval	HX_DRV_LIB_PASS		Operation success
 * \retval	HX_DRV_LIB_ERROR	Operation fail
 */
extern HX_DRV_ERROR_E hx_drv_flash_init();

/**
 * \brief	get model address information from flash
 * 			Ex.
 * 				if (hx_drv_flash_init() != HX_DRV_LIB_PASS)
 *				{
 *					hx_drv_uart_print("Spi 0 for flash initial fail.");
 *					return ;
 *				}
 *
 *				//get model (.tflite) from flash
 *   			model = tflite::GetModel((unsigned char*)hx_drv_flash_get_Model_address());
 *
 *
 * \retval	model_address	Operation success
 * \retval	0               unable to find Model
 */
extern uint32_t hx_drv_flash_get_Model_address();


#ifdef __cplusplus
}
#endif

#endif /* HX_DRV_P021_H_ */

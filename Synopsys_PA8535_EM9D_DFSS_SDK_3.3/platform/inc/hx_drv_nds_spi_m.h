/*
 * hx_drv_spi_m.h
 *
 *  Created on: 2018¦~10¤ë4¤é
 *      Author: 902452
 */

#ifndef INC_HX_DRV_NDS_SPI_M_H_
#define INC_HX_DRV_NDS_SPI_M_H_

#include "nds_common.h"

#define NDS_SPI_API_VERSION NDS_DRIVER_VERSION_MAJOR_MINOR(2,01)  /* API version */




// SPI0 (Serial Peripheral Interface) [Driver_SPI0]
// Configuration settings for Driver_SPI0 in component ::Drivers:SPI
#define RTE_SPI0                        1

// DMA
//   Tx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_SPI0_DMA_TX_EN              1
#define RTE_SPI0_DMA_TX_CH              0
#define RTE_SPI0_DMA_TX_REQID           0

//   Rx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_SPI0_DMA_RX_EN              1
#define RTE_SPI0_DMA_RX_CH              1
#define RTE_SPI0_DMA_RX_REQID           1

// SPI1 (Serial Peripheral Interface) [Driver_SPI1]
// Configuration settings for Driver_SPI1 in component ::Drivers:SPI
#define RTE_SPI1                        1

// DMA
//   Tx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_SPI1_DMA_TX_EN              1
#define RTE_SPI1_DMA_TX_CH              0
#define RTE_SPI1_DMA_TX_REQID           2

//   Rx
//     Channel     <0=>0 <1=>1 <2=>2 <3=>3 <4=>4 <5=>5 <6=>6 <7=>7
#define RTE_SPI1_DMA_RX_EN              1
#define RTE_SPI1_DMA_RX_CH              1
#define RTE_SPI1_DMA_RX_REQID           3

/****** SPI Control Codes *****/

#define NDS_SPI_CONTROL_Pos              0
#define NDS_SPI_CONTROL_Msk             (0xFFUL << NDS_SPI_CONTROL_Pos)

/*----- SPI Control Codes: Mode -----*/
#define NDS_SPI_MODE_INACTIVE           (0x00UL << NDS_SPI_CONTROL_Pos)     ///< SPI Inactive
#define NDS_SPI_MODE_MASTER             (0x01UL << NDS_SPI_CONTROL_Pos)     ///< SPI Master (Output on MOSI, Input on MISO); arg = Bus Speed in bps
#define NDS_SPI_MODE_SLAVE              (0x02UL << NDS_SPI_CONTROL_Pos)     ///< SPI Slave  (Output on MISO, Input on MOSI)
#define NDS_SPI_MODE_MASTER_SIMPLEX     (0x03UL << NDS_SPI_CONTROL_Pos)     ///< SPI Master (Output/Input on MOSI); arg = Bus Speed in bps
#define NDS_SPI_MODE_SLAVE_SIMPLEX      (0x04UL << NDS_SPI_CONTROL_Pos)     ///< SPI Slave  (Output/Input on MISO)

/*----- SPI Control Codes: Mode Parameters: Frame Format -----*/
#define NDS_SPI_FRAME_FORMAT_Pos         8
#define NDS_SPI_FRAME_FORMAT_Msk        (7UL << NDS_SPI_FRAME_FORMAT_Pos)
#define NDS_SPI_CPOL0_CPHA0             (0UL << NDS_SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 0, Clock Phase 0 (default)
#define NDS_SPI_CPOL0_CPHA1             (1UL << NDS_SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 0, Clock Phase 1
#define NDS_SPI_CPOL1_CPHA0             (2UL << NDS_SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 1, Clock Phase 0
#define NDS_SPI_CPOL1_CPHA1             (3UL << NDS_SPI_FRAME_FORMAT_Pos)   ///< Clock Polarity 1, Clock Phase 1
#define NDS_SPI_TI_SSI                  (4UL << NDS_SPI_FRAME_FORMAT_Pos)   ///< Texas Instruments Frame Format
#define NDS_SPI_MICROWIRE               (5UL << NDS_SPI_FRAME_FORMAT_Pos)   ///< National Microwire Frame Format

/*----- SPI Control Codes: Mode Parameters: Data Bits -----*/
#define NDS_SPI_DATA_BITS_Pos            12
#define NDS_SPI_DATA_BITS_Msk           (0x3FUL << NDS_SPI_DATA_BITS_Pos)
#define NDS_SPI_DATA_BITS(n)            (((n) & 0x3F) << NDS_SPI_DATA_BITS_Pos) ///< Number of Data bits

/*----- SPI Control Codes: Mode Parameters: Bit Order -----*/
#define NDS_SPI_BIT_ORDER_Pos            18
#define NDS_SPI_BIT_ORDER_Msk           (1UL << NDS_SPI_BIT_ORDER_Pos)
#define NDS_SPI_MSB_LSB                 (0UL << NDS_SPI_BIT_ORDER_Pos)      ///< SPI Bit order from MSB to LSB (default)
#define NDS_SPI_LSB_MSB                 (1UL << NDS_SPI_BIT_ORDER_Pos)      ///< SPI Bit order from LSB to MSB

/*----- SPI Control Codes: Mode Parameters: Slave Select Mode -----*/
#define NDS_SPI_SS_MASTER_MODE_Pos       19
#define NDS_SPI_SS_MASTER_MODE_Msk      (3UL << NDS_SPI_SS_MASTER_MODE_Pos)
#define NDS_SPI_SS_MASTER_UNUSED        (0UL << NDS_SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Not used (default)
#define NDS_SPI_SS_MASTER_SW            (1UL << NDS_SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Software controlled
#define NDS_SPI_SS_MASTER_HW_OUTPUT     (2UL << NDS_SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Hardware controlled Output
#define NDS_SPI_SS_MASTER_HW_INPUT      (3UL << NDS_SPI_SS_MASTER_MODE_Pos) ///< SPI Slave Select when Master: Hardware monitored Input
#define NDS_SPI_SS_SLAVE_MODE_Pos        21
#define NDS_SPI_SS_SLAVE_MODE_Msk       (1UL << NDS_SPI_SS_SLAVE_MODE_Pos)
#define NDS_SPI_SS_SLAVE_HW             (0UL << NDS_SPI_SS_SLAVE_MODE_Pos)  ///< SPI Slave Select when Slave: Hardware monitored (default)
#define NDS_SPI_SS_SLAVE_SW             (1UL << NDS_SPI_SS_SLAVE_MODE_Pos)  ///< SPI Slave Select when Slave: Software controlled


/*----- SPI Control Codes: Miscellaneous Controls  -----*/
#define NDS_SPI_SET_BUS_SPEED           (0x10UL << NDS_SPI_CONTROL_Pos)     ///< Set Bus Speed in bps; arg = value
#define NDS_SPI_GET_BUS_SPEED           (0x11UL << NDS_SPI_CONTROL_Pos)     ///< Get Bus Speed in bps
#define NDS_SPI_SET_DEFAULT_TX_VALUE    (0x12UL << NDS_SPI_CONTROL_Pos)     ///< Set default Transmit value; arg = value
#define NDS_SPI_CONTROL_SS              (0x13UL << NDS_SPI_CONTROL_Pos)     ///< Control Slave Select; arg: 0=inactive, 1=active
#define NDS_SPI_ABORT_TRANSFER          (0x14UL << NDS_SPI_CONTROL_Pos)     ///< Abort current data transfer


/****** SPI Slave Select Signal definitions *****/
#define NDS_SPI_SS_INACTIVE              0                                  ///< SPI Slave Select Signal Inactive
#define NDS_SPI_SS_ACTIVE                1                                  ///< SPI Slave Select Signal Active


/****** SPI specific error codes *****/
#define NDS_SPI_ERROR_MODE              (NDS_DRIVER_ERROR_SPECIFIC - 1)     ///< Specified Mode not supported
#define NDS_SPI_ERROR_FRAME_FORMAT      (NDS_DRIVER_ERROR_SPECIFIC - 2)     ///< Specified Frame Format not supported
#define NDS_SPI_ERROR_DATA_BITS         (NDS_DRIVER_ERROR_SPECIFIC - 3)     ///< Specified number of Data bits not supported
#define NDS_SPI_ERROR_BIT_ORDER         (NDS_DRIVER_ERROR_SPECIFIC - 4)     ///< Specified Bit order not supported
#define NDS_SPI_ERROR_SS_MODE           (NDS_DRIVER_ERROR_SPECIFIC - 5)     ///< Specified Slave Select Mode not supported


/**
\brief SPI Status
*/
typedef struct _NDS_SPI_STATUS {
  uint32_t busy       : 1;              ///< Transmitter/Receiver busy flag
  uint32_t data_lost  : 1;              ///< Data lost: Receive overflow / Transmit underflow (cleared on start of transfer operation)
  uint32_t mode_fault : 1;              ///< Mode fault detected; optional (cleared on start of transfer operation)
} NDS_SPI_STATUS;


/****** SPI Event *****/
#define NDS_SPI_EVENT_TRANSFER_COMPLETE (1UL << 0)  ///< Data Transfer completed
#define NDS_SPI_EVENT_DATA_LOST         (1UL << 1)  ///< Data lost: Receive overflow / Transmit underflow
#define NDS_SPI_EVENT_MODE_FAULT        (1UL << 2)  ///< Master Mode Fault (SS deactivated when Master)


// Function documentation
/**
  \fn          NDS_DRIVER_VERSION NDS_SPI_GetVersion (void)
  \brief       Get driver version.
  \return      \ref NDS_DRIVER_VERSION

  \fn          NDS_SPI_CAPABILITIES NDS_SPI_GetCapabilities (void)
  \brief       Get driver capabilities.
  \return      \ref NDS_SPI_CAPABILITIES

  \fn          int32_t NDS_SPI_Initialize (NDS_SPI_SignalEvent_t cb_event)
  \brief       Initialize SPI Interface.
  \param[in]   cb_event  Pointer to \ref NDS_SPI_SignalEvent
  \return      \ref execution_status

  \fn          int32_t NDS_SPI_Uninitialize (void)
  \brief       De-initialize SPI Interface.
  \return      \ref execution_status

  \fn          int32_t NDS_SPI_PowerControl (NDS_POWER_STATE state)
  \brief       Control SPI Interface Power.
  \param[in]   state  Power state
  \return      \ref execution_status

  \fn          int32_t NDS_SPI_Send (const void *data, uint32_t num)
  \brief       Start sending data to SPI transmitter.
  \param[in]   data  Pointer to buffer with data to send to SPI transmitter
  \param[in]   num   Number of data items to send
  \return      \ref execution_status

  \fn          int32_t NDS_SPI_Receive (void *data, uint32_t num)
  \brief       Start receiving data from SPI receiver.
  \param[out]  data  Pointer to buffer for data to receive from SPI receiver
  \param[in]   num   Number of data items to receive
  \return      \ref execution_status

  \fn          int32_t NDS_SPI_Transfer (const void *data_out,
                                               void *data_in,
                                         uint32_t    num)
  \brief       Start sending/receiving data to/from SPI transmitter/receiver.
  \param[in]   data_out  Pointer to buffer with data to send to SPI transmitter
  \param[out]  data_in   Pointer to buffer for data to receive from SPI receiver
  \param[in]   num       Number of data items to transfer
  \return      \ref execution_status

  \fn          uint32_t NDS_SPI_GetDataCount (void)
  \brief       Get transferred data count.
  \return      number of data items transferred

  \fn          int32_t NDS_SPI_Control (uint32_t control, uint32_t arg)
  \brief       Control SPI Interface.
  \param[in]   control  Operation
  \param[in]   arg      Argument of operation (optional)
  \return      common \ref execution_status and driver specific \ref spi_execution_status

  \fn          NDS_SPI_STATUS NDS_SPI_GetStatus (void)
  \brief       Get SPI status.
  \return      SPI status \ref NDS_SPI_STATUS

  \fn          void NDS_SPI_SignalEvent (uint32_t event)
  \brief       Signal SPI Events.
  \param[in]   event \ref SPI_events notification mask
  \return      none
*/
typedef void (*NDS_SPI_SignalEvent_t) (uint32_t event);  ///< Pointer to \ref NDS_SPI_SignalEvent : Signal SPI Event.


/**
\brief SPI Driver Capabilities.
*/
typedef struct _NDS_SPI_CAPABILITIES {
  uint32_t simplex          : 1;        ///< supports Simplex Mode (Master and Slave)
  uint32_t ti_ssi           : 1;        ///< supports TI Synchronous Serial Interface
  uint32_t microwire        : 1;        ///< supports Microwire Interface
  uint32_t event_mode_fault : 1;        ///< Signal Mode Fault event: \ref NDS_SPI_EVENT_MODE_FAULT
} NDS_SPI_CAPABILITIES;


/**
\brief Access structure of the SPI Driver.
*/
typedef struct _NDS_DRIVER_SPI {
  NDS_DRIVER_VERSION   (*GetVersion)      (void);                             ///< Pointer to \ref NDS_SPI_GetVersion : Get driver version.
  NDS_SPI_CAPABILITIES (*GetCapabilities) (void);                             ///< Pointer to \ref NDS_SPI_GetCapabilities : Get driver capabilities.
  int32_t              (*Initialize)      (NDS_SPI_SignalEvent_t cb_event);   ///< Pointer to \ref NDS_SPI_Initialize : Initialize SPI Interface.
  int32_t              (*Uninitialize)    (void);                             ///< Pointer to \ref NDS_SPI_Uninitialize : De-initialize SPI Interface.
  int32_t              (*PowerControl)    (NDS_POWER_STATE state);            ///< Pointer to \ref NDS_SPI_PowerControl : Control SPI Interface Power.
  int32_t              (*Send)            (const void *data, uint32_t num);   ///< Pointer to \ref NDS_SPI_Send : Start sending data to SPI Interface.
  int32_t              (*Receive)         (      void *data, uint32_t num);   ///< Pointer to \ref NDS_SPI_Receive : Start receiving data from SPI Interface.
  int32_t              (*Transfer)        (const void *data_out,
                                                 void *data_in,
                                           uint32_t    num);                  ///< Pointer to \ref NDS_SPI_Transfer : Start sending/receiving data to/from SPI.
  uint32_t             (*GetDataCount)    (void);                             ///< Pointer to \ref NDS_SPI_GetDataCount : Get transferred data count.
  int32_t              (*Control)         (uint32_t control, uint32_t arg);   ///< Pointer to \ref NDS_SPI_Control : Control SPI Interface.
  NDS_SPI_STATUS       (*GetStatus)       (void);                             ///< Pointer to \ref NDS_SPI_GetStatus : Get SPI status.
} const NDS_DRIVER_SPI;

#endif /* INC_HX_DRV_NDS_SPI_M_H_ */

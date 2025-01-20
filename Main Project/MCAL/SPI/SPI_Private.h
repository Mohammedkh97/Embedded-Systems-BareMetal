/*
 * SPI_Private.h
 *
 *  Created on: Oct 19, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef SPI_SPI_PRIVATE_H_
#define SPI_SPI_PRIVATE_H_

typedef struct
{
	volatile u32 CR1;
	volatile u32 CR2;
	volatile u32 SR;
	volatile u32 DR;
	volatile u32 CRCPR;
	volatile u32 RXCRCR;
	volatile u32 TXCRCR;
	volatile u32 I2SCFGR;

} SPI_t;


typedef enum {
    CPHA_SPI,       /** Clock Phase */
    CPOL_SPI,       /** Clock Polarity */
    MSTR,       /** Master Selection */
    BR0,        /** Baud Rate Control Bit 0 */
    BR1,        /** Baud Rate Control Bit 1 */
    BR2,        /** Baud Rate Control Bit 2 */
    SPE,        /** SPI Enable */
    LSBFIRST,   /** LSB First */
    SSI,        /** Internal Slave Select */
    SSM,        /** Software Slave Management */
    RXONLY,     /** Receive Only */
    DFF,        /** Data Frame Format */
    CRCNEXT,    /** CRC Transfer Next */
    CRCEN,      /** Hardware CRC Calculation Enable */
    BIDIOE,     /** Output Enable in Bidirectional Mode */
    BIDIMODE    /** Bidirectional Data Mode Enable */
} CR1_Bits_t;

typedef enum {
    RXDMAEN,    /** RX Buffer DMA Enable */
    TXDMAEN,    /** TX Buffer DMA Enable */
    SSOE,       /** SS Output Enable */
    FRF,        /** Frame Format */
    ERRIE,      /** Error Interrupt Enable */
    RXNEIE,     /** RX Buffer Not Empty Interrupt Enable */
    TXEIE      /** TX Buffer Empty Interrupt Enable */

} CR2_Bits_t;

typedef enum {
    RXNE_SPI,       /** Receive Buffer Not Empty */
    TXE_SPI,        /** Transmit Buffer Empty */
    CHSIDE,     /** Channel Side */
    UDR,        /** Underrun Flag */
    CRCERR,     /** CRC Error Flag */
    MODF,       /** Mode Fault */
    OVR,        /** Overrun Flag */
    BSY,        /** Busy Flag */
    FRE         /** Frame Format Error */

} SR_Bits_t;


/************************************** Private Functions Prototypes ***************************/
static void SPI_void_Pin_Configurations(SPI_Channel_t SPI_ID, SPI_Mode_t Mode);
static void void_SPI_Enable(SPI_Channel_t SPI_ID);
static void void_SPI_Mode(SPI_Channel_t SPI_ID, SPI_Mode_t SPI_Mode);
static void void_SPI1_Mode(SPI_Mode_t Mode);
static void void_SPI2_Mode(SPI_Mode_t Mode);
static void SPI_void_Set_Direction(SPI_Channel_t SPI_ID, Direction_Data_Mode_t Direction_Mode);
static void SPI1_Set_Direction(Direction_Data_Mode_t Direction_Mode);
static void SPI2_Set_Direction(Direction_Data_Mode_t Direction_Mode);
static void void_SPI_Set_DataFormat(SPI_Channel_t SPI_ID, SPI_DataFormat_t DataFormat);
static void void_SPI1_DataFormat(SPI_DataFormat_t DataFormat);
static void void_SPI2_DataFormat(SPI_DataFormat_t DataFormat);
void void_SPI_Set_ClockPolarity(SPI_Channel_t SPI_ID, SPI_Clock_Polarity_t ClockPolarity);
void void_SPI1_Set_ClockPolarity(SPI_Clock_Polarity_t ClockPolarity);
void void_SPI2_Set_ClockPolarity(SPI_Clock_Polarity_t ClockPolarity);
void void_SPI_Set_ClockPhase(SPI_Channel_t SPI_ID, SPI_Clock_Phase_t ClockPhase);
void void_SPI1_Set_ClockPhase(SPI_Clock_Phase_t ClockPhase);
void void_SPI2_Set_ClockPhase(SPI_Clock_Phase_t ClockPhase);
void void_SPI_Set_Baud_Rate_Prescaler(SPI_Channel_t SPI_ID, SPI_Baud_Rate_Prescaler_t Prescaler);
static void void_SPI_NSS_Management(SPI_Channel_t SPI_ID, SPI_NSS_Management_t NSSManagement);
static void void_SPI1_NSS_Management(SPI_NSS_Management_t NSSManagement);
static void void_SPI2_NSS_Management(SPI_NSS_Management_t NSSManagement);


#endif /* SPI_SPI_PRIVATE_H_ */

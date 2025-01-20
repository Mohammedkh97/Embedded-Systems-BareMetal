/*
 * USART_Private.h
 *
 *  Created on: Sep 25, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef USART_USART_PRIVATE_H_
#define USART_USART_PRIVATE_H_


/*
  @brief Universal Synchronous Asynchronous Receiver Transmitter
*/


typedef struct
{
  volatile u32 SR;         /*!< USART Status register,                   Address offset: 0x00 */
  volatile u32 DR;         /*!< USART Data register,                     Address offset: 0x04 */
  volatile u32 BRR;        /*!< USART Baud rate register,                Address offset: 0x08 */
  volatile u32 CR1;        /*!< USART Control register 1,                Address offset: 0x0C */
  volatile u32 CR2;        /*!< USART Control register 2,                Address offset: 0x10 */
  volatile u32 CR3;        /*!< USART Control register 3,                Address offset: 0x14 */
  volatile u32 GTPR;       /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} USART_t;

typedef enum    /** @note Flags Register (Status)*/
{
    PE,     /** @note: Parity Error */
    FE,     /** @note: Framing Error */
    NE,     /** @note: Noise Error */
    ORE,    /** @note: Overrun Error */
    IDLE,   /** @note: Idle Line Detect */
    RXNE,   /** @note: Read Data Register Not Empty */
    TC,     /** @note: Transmission Complete */
    TXE,    /** @note: Transmitt Data Register Empty */
    LBD,    /** @note: LIN Break Detection */
    CTS     /** @note: CTS Flag */
}SR_Bits_t;  /** @note Other bits are reserved */

typedef enum
{
    SBK     ,  /** @note: Send Break */
    RWU     ,  /** @note: Receiver Wakeup */
    RE      ,  /** @note: Receiver Enable */
    TE      ,  /** @note: Transmitter Enable */
    IDLEIE  ,  /** @note: IDLE Interrupt Enable */
    RXENIE  ,  /** @note: RXNE Interrupt Enable */
    TCIE    ,  /** @note: Transmission Complete Interrupt Enable */
    TXEIE   ,  /** @note: TXE Interrupt Enable */
    PEIE    ,  /** @note: PE Interrupt Enable */
    PS      ,  /** @note: Parity Selection */
    PCE     ,  /** @note: Parity Control Enable */
    WAKE    ,  /** @note: Wakeup Method */
    M       ,  /** @note: Word Length */
    UE      /** @note: USART Enable */
} CR1_Bits_t; /** @note Other bits are reserved */


typedef enum
{
    ADD0    ,  /** @note: Address Bit 0 */
    ADD1    ,  /** @note: Address Bit 1 */
    ADD2    ,  /** @note: Address Bit 2 */
    ADD3    ,  /** @note: Address Bit 3 */
    LBDL    ,  /** @note: LIN Break Detection Length */
    LBDIE   ,  /** @note: LIN Break Detection Interrupt Enable */
    LBCL    ,  /** @note: Last Bit Clock Pulse */
    CPHA    ,  /** @note: Clock Phase */
    CPOL    ,  /** @note: Clock Polarity */
    CLKEN   ,  /** @note: Clock Enable */
    STOP0   ,  /** @note: STOP Bit 0 */
    STOP1   ,  /** @note: STOP Bit 1 */
    LINEN   /** @note: LIN Mode Enable */
} CR2_Bits_t; /** @note Other bits are reserved */


typedef enum
{
    EIE     ,  /** @note: Error Interrupt Enable */
    IREN    ,  /** @note: IrDA Enabler */
    IRLP    ,  /** @note: IrDA Low-Pulse */
    HDSEL   ,  /** @note: Half-Duplex Selection */
    NACK    ,  /** @note: Smartcard NACK Enable */
    SCEN    ,  /** @note: Smartcard Mode Enable */
    DMAR    ,  /** @note: DMA Enable Receiver */
    DMAT    ,  /** @note: DMA Enable Transmitter */
    RTSE    ,  /** @note: RTS Enable */
    CTSE    ,  /** @note: CTS Enable */
    CTSIE   /** @note: CTS Interrupt Enable */
} CR3_Bits_t; /** @note Other bits are reserved */




/****************************************************** Private Functions *******************************/

static void void_USART_Enable		(USART_Channel_t USART_ID);
static void void_USART_Disable		(USART_Channel_t USART_ID);

static void void_Set_Word_Length (USART_Channel_t USART_ID, u8 Data_Word);

static void void_Stop_Bits_Selection (USART_Channel_t USART_ID, USART_StopBits_t Stop_Bits);

static void void_Set_Wakeup_Method(USART_Channel_t USART_ID, USART_WakeupMethod_t WakeupMethod);

static void void_USART_Parity_Bit_Selection (USART_Channel_t USART_ID, USART_Parity_t Parity_State);
static void void_USART_Mode		(USART_Channel_t USART_ID, USART_Mode_t USART_Mode);

static void void_Set_Baud_Rate	(USART_Channel_t USART_ID, u32 Baud_Rate);
void voidCalculateBaudRate(u32 Copy_u32BaudRate, u16 *Address_u16BRRValue);

static void void_USART1_Mode(USART_Mode_t Mode);
static void void_USART2_Mode(USART_Mode_t Mode);
static void void_USART3_Mode(USART_Mode_t Mode);


#endif /* USART_USART_PRIVATE_H_ */

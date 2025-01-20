/*
 * RCC_Interface.h
 *
 *  Created on: Sep 20, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef MCAL_RCC_RCC_INTERFACE_H_
#define MCAL_RCC_RCC_INTERFACE_H_

#include "stdTypes.h"
#include "FLASH_ACR_Private.h"
/**
 * @brief Enum for RCC bus types.
 *
 * This enum defines the different types of RCC buses (AHB, APB1, APB2) that can be enabled.
 */
typedef enum
{
    RCC_AHBENR    		= 0,   /**< AHB bus  		AHB Peripheral Clock enable register (RCC_AHBENR)*/
	RCC_APB1ENR    		= 1,   /**< APB1 bus  	APB1 peripheral reset register (RCC_APB1RSTR)*/
    RCC_APB2ENR    		= 2,    /**< APB2 bus 	APB2 peripheral clock enable register (RCC_APB2ENR)*/
	RCC_PLL_BUS			= 3
} RCC_Bus_t;


/* SYSTEM BUS CONTROLLER Using MACROS*/

#define   SYSTEM_BUS_AHB           ( (0b0000) )        /* Advanced High Performance Bus */
#define   SYSTEM_BUS_APB1          ( (0b0001) )        /* Advanced Performance Bus 1 */
#define   SYSTEM_BUS_APB2          ( (0b0010) )        /* Advanced Performance Bus 2 */

#define   SYSTEM_PLL               ( (0b0011) )        /* Phase Locked Loop ID */

/**
 * @brief Enum for AHB peripheral enable bits.
 *
 * This enum defines the bit positions in the AHBENR register for enabling specific peripherals
 * on the AHB bus.
 */
typedef enum
{
    AHB_DMA1_EN     = 0,   /**< Enable DMA1 */
    AHB_DMA2_EN     = 1,   /**< Enable DMA2 */
    AHB_SRAM_EN     = 2,   /**< Enable SRAM */
    AHB_FLITF_EN    = 4,   /**< Enable Flash Interface (FLITF) */
    AHB_CRC_EN      = 6,   /**< Enable CRC calculation unit */
    AHB_FSMC_EN     = 8,   /**< Enable FSMC (Flexible Static Memory Controller) */
    AHB_SDIO_EN     = 10   /**< Enable SDIO (Secure Digital Input Output) */
} AHB_Bits_t;

/**
 * @brief Enum for APB1 peripheral enable bits.
 *
 * This enum defines the bit positions in the APB1ENR register for enabling specific peripherals
 * on the APB1 bus.
 */
typedef enum
{
    APB1_TIM2_EN       = 0,   /**< Enable TIM2 (Timer 2) */
    APB1_TIM3_EN       = 1,   /**< Enable TIM3 (Timer 3) */
    APB1_TIM4_EN       = 2,   /**< Enable TIM4 (Timer 4) */
    APB1_SPI2_EN       = 14,  /**< Enable SPI2 (Serial Peripheral Interface 2) */
    APB1_USART2_EN     = 17,  /**< Enable USART2 (Universal Synchronous Asynchronous Receiver Transmitter 2) */
    APB1_USART3_EN     = 18,  /**< Enable USART3 (Universal Synchronous Asynchronous Receiver Transmitter 3) */
    APB1_I2C1_EN       = 21,  /**< Enable I2C1 (Inter-Integrated Circuit 1) */
    APB1_I2C2_EN       = 22,  /**< Enable I2C2 (Inter-Integrated Circuit 2) */
    APB1_USB_EN        = 23,  /**< Enable USB (Universal Serial Bus) */
    APB1_CAN_EN        = 25   /**< Enable CAN (Controller Area Network) */
} APB1_Bits_t;


/**
 * @brief Enum for APB2 peripheral enable bits.
 *
 * This enum defines the bit positions in the APB2ENR register for enabling specific peripherals
 * on the APB2 bus.
 */
typedef enum
{
    APB2_AFIO_EN       = 0,  /**< Enable AFIO (Alternate Function I/O) */
    APB2_GPIOA_EN      = 2,  /**< Enable GPIOA */
    APB2_GPIOB_EN      = 3,  /**< Enable GPIOB */
    APB2_GPIOC_EN      = 4,  /**< Enable GPIOC */
    APB2_GPIOD_EN      = 5,  /**< Enable GPIOD */
    APB2_ADC1_EN       = 9,  /**< Enable ADC1 (Analog-to-Digital Converter 1) */
    APB2_ADC2_EN       = 10, /**< Enable ADC2 (Analog-to-Digital Converter 2) */
    APB2_TIM1_EN       = 11, /**< Enable TIM1 (Timer 1) */
    APB2_SPI1_EN       = 12, /**< Enable SPI1 (Serial Peripheral Interface 1) */
    APB2_USART1_EN     = 14, /**< Enable USART1 (Universal Synchronous Asynchronous Receiver Transmitter 1) */
    APB2_ADC3_EN       = 15  /**< Enable ADC3 (Analog-to-Digital Converter 3) */
} APB2_Bits_t;




// Clock Types
typedef enum
{
    RCC_HSI,            // High-Speed Internal oscillator
    RCC_HSE_CRYSTAL,    // High-Speed External crystal oscillator
    RCC_HSE_RC,         // High-Speed External RC oscillator
    RCC_PLL             // Phase-Locked Loop (PLL)
} RCC_ClockType_t;


/*Using MACROS*/
/* SYSTEM INPUT CLOCK SOURCE */

#define   SYSTEM_CLOCK_LSE         ( (0b0000) )      /* Low Speed External Clock Source */
#define   SYSTEM_CLOCK_LSI         ( (0b0001) )      /* Low Speed Internal Clock Source */
#define   SYSTEM_CLOCK_HSE_CRYSTAL ( (0b0010) )      /* High Speed External Clock Source - CRYSTAL */
#define   SYSTEM_CLOCK_HSE_RC      ( (0b0011) )      /* High Speed External Clock Source - RC    */
#define   SYSTEM_CLOCK_HSI         ( (0b0100) )      /* High Speed Internal Clock Source */
#define   SYSTEM_CLOCK_PLL         ( (0b0101) )      /* Phase Locked Loop Clock Source */




/**
 * @brief Enum for PLL input options.
 *
 * This enum defines the options for the PLL input clock sources.
 */
typedef enum
{
    RCC_PLL_IN_HSI_DIV_2	= 0,  // HSI divided by 2 as PLL input
    RCC_PLL_IN_HSE_DIV_2	= 1,  // HSE divided by 2 as PLL input
    RCC_PLL_IN_HSE			= 2   // HSE as PLL input (PLL INPUT HSE DIRECT)

} RCC_PLL_Input_t;

/** @defgroup PLL INPUT CLOCK SOURCE */
#define   PLL_INPUT_HSI_DIV_2      ( (0b0000) )
#define   PLL_INPUT_HSE_DIV_2      ( (0b0001) )
#define   PLL_INPUT_HSE_DIRECT     ( (0b0010) )


/**
 * @brief Enum for PLL multiplier factors.
 *
 * This enum defines the multiplier factors for the PLL configuration.
 */
typedef enum
{
    NO_CLOCK_FACTOR                       = 0b0000,  /**< No clock factor */
    PLL_CLOCK_MULTIPLE_BY_2               = 0b0000,  /**< Multiply by 2 */
    PLL_CLOCK_MULTIPLE_BY_3               = 0b0001,  /**< Multiply by 3 */
    PLL_CLOCK_MULTIPLE_BY_4               = 0b0010,  /**< Multiply by 4 */
    PLL_CLOCK_MULTIPLE_BY_5               = 0b0011,  /**< Multiply by 5 */
    PLL_CLOCK_MULTIPLE_BY_6               = 0b0100,  /**< Multiply by 6 */
    PLL_CLOCK_MULTIPLE_BY_7               = 0b0101,  /**< Multiply by 7 */
    PLL_CLOCK_MULTIPLE_BY_8               = 0b0110,  /**< Multiply by 8 */
    PLL_CLOCK_MULTIPLE_BY_9               = 0b0111,  /**< Multiply by 9 */
    PLL_CLOCK_MULTIPLE_BY_10              = 0b1000,  /**< Multiply by 10 */
    PLL_CLOCK_MULTIPLE_BY_11              = 0b1001,  /**< Multiply by 11 */
    PLL_CLOCK_MULTIPLE_BY_12              = 0b1010,  /**< Multiply by 12 */
    PLL_CLOCK_MULTIPLE_BY_13              = 0b1011,  /**< Multiply by 13 */
    PLL_CLOCK_MULTIPLE_BY_14              = 0b1100,  /**< Multiply by 14 */
    PLL_CLOCK_MULTIPLE_BY_15              = 0b1101,  /**< Multiply by 15 */
    PLL_CLOCK_MULTIPLE_BY_16              = 0b1110   /**< Multiply by 16 */
} RCC_PLL_MultiplierFactor_t;

/**
 * @brief Enum for AHB (Advanced High-Performance Bus) Prescalers
 * These prescalers divide the system clock to generate the AHB clock.
 */
typedef enum
{
    AHB_PRESCALER_1   = 0b0000, /**< No division, AHB clock = System clock */
    AHB_PRESCALER_2   = 0b1000, /**< AHB clock = System clock / 2 */
    AHB_PRESCALER_4   = 0b1001, /**< AHB clock = System clock / 4 */
    AHB_PRESCALER_8   = 0b1010, /**< AHB clock = System clock / 8 */
    AHB_PRESCALER_16  = 0b1011, /**< AHB clock = System clock / 16 */
    AHB_PRESCALER_64  = 0b1100, /**< AHB clock = System clock / 64 */
    AHB_PRESCALER_128 = 0b1101, /**< AHB clock = System clock / 128 */
    AHB_PRESCALER_256 = 0b1110, /**< AHB clock = System clock / 256 */
    AHB_PRESCALER_512 = 0b1111  /**< AHB clock = System clock / 512 */
} AHB_Prescaler_t;

/*

#define    AHB_PRESCALER_1        ( (0b0000) )
#define    AHB_PRESCALER_2        ( (0b1000) )
#define    AHB_PRESCALER_4        ( (0b1001) )
#define    AHB_PRESCALER_8        ( (0b1010) )
#define    AHB_PRESCALER_16       ( (0b1011) )
#define    AHB_PRESCALER_64       ( (0b1100) )
#define    AHB_PRESCALER_128      ( (0b1101) )
#define    AHB_PRESCALER_256      ( (0b1110) )
#define    AHB_PRESCALER_512      ( (0b1111) )
*/
/**
 * @brief Enum for APB1 (Advanced Peripheral Bus 1) Prescalers
 * These prescalers divide the AHB clock to generate the APB1 clock.
 */
typedef enum
{
    APB1_PRESCALER_1  = 0b000, /**< No division, APB1 clock = AHB clock */
    APB1_PRESCALER_2  = 0b100, /**< APB1 clock = AHB clock / 2 */
    APB1_PRESCALER_4  = 0b101, /**< APB1 clock = AHB clock / 4 */
    APB1_PRESCALER_8  = 0b110, /**< APB1 clock = AHB clock / 8 */
    APB1_PRESCALER_16 = 0b111  /**< APB1 clock = AHB clock / 16 */
} APB1_Prescaler_t;

/*
#define   APB1_PRESCALER_1        ( (0b000) )
#define   APB1_PRESCALER_2        ( (0b100) )
#define   APB1_PRESCALER_4        ( (0b101) )
#define   APB1_PRESCALER_8        ( (0b110) )
#define   APB1_PRESCALER_16       ( (0b111) )

*/

/**
 * @brief Enum for APB2 (Advanced Peripheral Bus 2) Prescalers
 * These prescalers divide the AHB clock to generate the APB2 clock.
 */
typedef enum
{
    APB2_PRESCALER_1  = 0b000, /**< No division, APB2 clock = AHB clock */
    APB2_PRESCALER_2  = 0b100, /**< APB2 clock = AHB clock / 2 */
    APB2_PRESCALER_4  = 0b101, /**< APB2 clock = AHB clock / 4 */
    APB2_PRESCALER_8  = 0b110, /**< APB2 clock = AHB clock / 8 */
    APB2_PRESCALER_16 = 0b111  /**< APB2 clock = AHB clock / 16 */
} APB2_Prescaler_t;


/*
#define    APB2_PRESCALER_1       ( (0b000) )
#define    APB2_PRESCALER_2       ( (0b100) )
#define    APB2_PRESCALER_4       ( (0b101) )
#define    APB2_PRESCALER_8       ( (0b110) )
#define    APB2_PRESCALER_16      ( (0b111) )

 */


/***************************** The same RCC_PLL_Multiplier Factors using MACROS       ********************************/
//#define  PLL_MUL_2    ( (0b0000) )
//#define  PLL_MUL_3    ( (0b0001) )
//#define  PLL_MUL_4    ( (0b0010) )
//#define  PLL_MUL_5    ( (0b0011) )
//#define  PLL_MUL_6    ( (0b0100) )
//#define  PLL_MUL_7    ( (0b0101) )
//#define  PLL_MUL_8    ( (0b0110) )
//#define  PLL_MUL_9    ( (0b0111) )
//#define  PLL_MUL_10   ( (0b1000) )
//#define  PLL_MUL_11   ( (0b1001) )
//#define  PLL_MUL_12   ( (0b1010) )
//#define  PLL_MUL_13   ( (0b1011) )
//#define  PLL_MUL_14   ( (0b1100) )
//#define  PLL_MUL_15   ( (0b1101) )
//#define  PLL_MUL_16   ( (0b1110) )

/********************************** Functions Prototype ******************************************/
//void RCC_void_System_Clock_Init(RCC_ClockType_t clockType, RCC_PLL_Input_t pllInput, RCC_PLL_MultiplierFactor_t pllMulFactor, FLASH_ACR_t Flash_Latency, AHB_Prescaler_t AHB_Prescaler, APB1_Prescaler_t APB1Prescaler, APB2_Prescaler_t APB2Prescaler);
void RCC_void_System_Clock_Init(RCC_ClockType_t clockType, RCC_PLL_Input_t pllInput, RCC_PLL_MultiplierFactor_t pllMulFactor);
/*
 In RCC_void_Enable_Clock:
 Peripheral_ID is according to RCC Bus and its Bits such as: AHB includes AHB_DMA1_EN, AHB_DMA2_EN, CRC and So on...
 */
void RCC_void_Enable_Clock(RCC_Bus_t Bus_ID , u8 Peripheral_ID);
void RCC_void_Disable_Clock(RCC_Bus_t Bus_ID , u8 Peripheral_ID);


//void RCC_EnablePLL(RCC_PLL_Input_t PLL_CLock_Source, RCC_PLL_MultiplierFactor_t PLL_Value);
//static void RCC_void_Enable_HSI(u8 Clock_Flag);
//static void RCC_void_Enable_HSE(u8 Copy_u8SetSystemClockFlag, RCC_ClockType_t HSE_InputType);

static void RCC_void_Decoder(RCC_Bus_t BusType, u8 Value);
void RCC_void_APB2ENR_Enable (APB2_Bits_t REG_BIT);
void RCC_void_APB2ENR_Disable(APB2_Bits_t REG_BIT);
void RCC_Enable_8_MHz_HSI(void);

#endif /* MCAL_RCC_RCC_INTERFACE_H_ */

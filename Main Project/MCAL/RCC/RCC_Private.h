/*
 * RCC_Private.h
 *
 *  Created on: Sep 20, 2024
 *      Author: Mohammed Khalaf
 */

#ifndef MCAL_RCC_RCC_PRIVATE_H_
#define MCAL_RCC_RCC_PRIVATE_H_

#include "RCC_Interface.h"
/*******************   Register Definition     ***********************/
typedef struct
{

	volatile u32 CR;
	volatile u32 CFGR;
	volatile u32 CIR;
	volatile u32 APB2RSTR;
	volatile u32 APB1RSTR;
	volatile u32 AHBENR;
	volatile u32 APB2ENR;
	volatile u32 APB1ENR;
	volatile u32 BDCR;
	volatile u32 CSR;
} RCC_t;

typedef enum
{
	HSION = 0, /* R/W, Enable HSI */
	HSIRDY = 1, /* R,   Check HSI */
	/************** HSITRIM[0:4]  Starts from BIT: 3 to BIT: 7 ***************/
	HSITRIM_3 = 3, /* R/W, HSI TRIM */
	HSITRIM_4 = 4, /* R/W, HSI TRIM */
	HSITRIM_5 = 5, /* R/W, HSI TRIM */
	HSITRIM_6 = 6, /* R/W, HSI TRIM */
	HSITRIM_7 = 7, /* R/W, HSI TRIM */
	HSICAL_8 = 8, /* R,   HSI CALIBRATION */
	HSICAL_9 = 9, /* R,   HSI CALIBRATION */
	HSICAL_10 = 10, /* R,   HSI CALIBRATION */
	HSICAL_11 = 11, /* R,   HSI CALIBRATION */
	HSICAL_12 = 12, /* R,   HSI CALIBRATION */
	HSICAL_13 = 13, /* R,   HSI CALIBRATION */
	HSICAL_14 = 14, /* R,   HSI CALIBRATION */
	HSICAL_15 = 15, /* R,   HSI CALIBRATION */
	HSEON = 16, /* R/W, Enable HSE */
	HSERDY = 17, /* R,   Check  HSE */
	HSEBYP = 18, /* R/W, HSE  Bypass */
	CSSON = 19, /* R/W, Enable  CSS */
	PLLON = 24, /* R/W, Enable  PLL */
	PLLRDY = 25 /* R,   Check  PLL */
} RCC_CR_BITS_t;

typedef enum
{
	SW_0 = 0, /* R/W: System Clock Switch Bit 0
	 * Selects the system clock source:
	 * 00: HSI, 01: HSE, 10: PLL. */

	SW_1 = 1, /* R/W: System Clock Switch Bit 1
	 * In combination with SW_0, defines the system clock source. */

	SWS_2 = 2, /* R: System Clock Switch Status Bit 0
	 * Indicates the current system clock source:
	 * 00: HSI, 01: HSE, 10: PLL. */

	SWS_3 = 3, /* R: System Clock Switch Status Bit 1
	 * Combined with SWS_2, shows the current system clock source. */

	HPRE_4 = 4, /* R/W: AHB Prescaler Bit 0
	 * Defines the AHB clock prescaler:
	 * 0xxx: No division, 1000: Division by 2, 1001: Division by 4, etc. */

	HPRE_5 = 5, /* R/W: AHB Prescaler Bit 1
	 * Combined with HPRE_4, HPRE_6, and HPRE_7 to configure the AHB prescaler. */

	HPRE_6 = 6, /* R/W: AHB Prescaler Bit 2
	 * Works with HPRE_4, HPRE_5, and HPRE_7 for AHB clock division. */

	HPRE_7 = 7, /* R/W: AHB Prescaler Bit 3
	 * Used with HPRE_4 to HPRE_6 to set AHB clock speed. */

	PPRE1_8 = 8, /* R/W: APB1 Low-Speed Prescaler Bit 0
	 * Sets the APB1 prescaler:
	 * 0xx: No division, 100: Division by 2, 101: Division by 4, etc. */

	PPRE1_9 = 9, /* R/W: APB1 Low-Speed Prescaler Bit 1
	 * Combined with PPRE1_8 and PPRE1_10 to define APB1 prescaler. */

	PPRE1_10 = 10, /* R/W: APB1 Low-Speed Prescaler Bit 2
	 * Sets the APB1 (low-speed peripheral) clock prescaler. */

	PPRE2_11 = 11, /* R/W: APB2 High-Speed Prescaler Bit 0
	 * Sets the APB2 prescaler (e.g., High-speed peripheral clock):
	 * 0xx: No division, 100: Division by 2, 101: Division by 4, etc. */

	PPRE2_12 = 12, /* R/W: APB2 High-Speed Prescaler Bit 1
	 * Combined with PPRE2_11 and PPRE2_13 to define APB2 prescaler. */

	PPRE2_13 = 13, /* R/W: APB2 High-Speed Prescaler Bit 2
	 * Sets the APB2 (high-speed peripheral) clock prescaler. */

	ADCPRE_14 = 14, /* R/W: ADC Prescaler Bit 0
	 * Sets the ADC clock prescaler:
	 * 00: PCLK2 divided by 2, 01: Divided by 4, 10: Divided by 6, 11: Divided by 8. */

	ADCPRE_15 = 15, /* R/W: ADC Prescaler Bit 1
	 * Used with ADCPRE_14 to configure ADC clock division. */

	PLLSRC = 16, /* R/W: PLL Entry Clock Source
	 * Selects the input clock for the PLL:
	 * 0: HSI/2, 1: HSE. */

	PLLXTPRE = 17, /* R/W: HSE Divider for PLL Entry
	 * If the PLL source is HSE, this bit configures whether HSE is divided by 2:
	 * 0: HSE, 1: HSE divided by 2. */

	PLLMUL_18 = 18, /* R/W: PLL Clock Multiplier Bit 0
	 * Sets the multiplier for the PLL:
	 * 0000: PLL input clock x2, 0001: x3, ..., 1111: x16. */

	PLLMUL_19 = 19, /* R/W: PLL Clock Multiplier Bit 1
	 * Used with PLLMUL_18 to PLLMUL_21 for PLL clock multiplication. */

	PLLMUL_20 = 20, /* R/W: PLL Clock Multiplier Bit 2
	 * Multiplies the PLL input frequency by a selected factor. */

	PLLMUL_21 = 21, /* R/W: PLL Clock Multiplier Bit 3
	 * Part of the multiplier setting for the PLL clock. */

	USBPRE = 22, /* R/W: USB Prescaler
	 * Sets the prescaler for the USB clock:
	 * 0: PLL clock divided by 1.5, 1: PLL clock divided by 1. */

	MCO_24 = 24, /* R/W: Microcontroller Clock Output Bit 0
	 * Selects the clock to be output on the MCO pin:
	 * 000: No clock, 100: SYSCLK, 101: HSI, 110: HSE, 111: PLL/2. */

	MCO_25 = 25, /* R/W: Microcontroller Clock Output Bit 1
	 * Part of MCO clock selection bits. */

	MCO_26 = 26 /* R/W: Microcontroller Clock Output Bit 2
	 * Works with MCO_24 and MCO_25 to define which clock is output on the MCO pin. */
} RCC_CFGR_BITS_t;

typedef enum
{
	LSIRDYF = 0, /* R, LSI Ready Interrupt Flag */
	LSERDYF = 1, /* R, LSE Ready Interrupt Flag */
	HSIRDYF = 2, /* R, HSI Ready Interrupt Flag */
	HSERDYF = 3, /* R, HSE Ready Interrupt Flag */
	PLLRDYF = 4, /* R, PLL Ready Interrupt Flag */
	CSSF = 7, /* R, CSS Ready Interrupt Flag */
	LSIRDIE = 8, /* R/W, LSI Interrupt Enable */
	LSERDYIE = 9, /* R/W, LSE Interrupt Enable */
	HSIRDYIE = 10, /* R/W, HSI Interrupt Enable */
	HSERDYIE = 11, /* R/W, HSE Interrupt Enable */
	PLLRDYIE = 12, /* R/W, PLL Interrupt Enable */
	LSIRDYC = 16, /* W,   LSI Interrupt Clear */
	LSERDYC = 17, /* W,   LSE Interrupt Clear */
	HSIRDYC = 18, /* W,   HSI Interrupt Clear */
	HSERDYC = 19, /* W,   HSE Interrupt Clear */
	PLLRDYC = 20, /* W,   PLL Interrupt Clear */
	CSSC = 23 /* W,   CSS Interrupt Clear */
} RCC_CIR_BITS_t;

/** @defgroup RCC_AHB_Clock_Source AHB Clock Source
 * @{
 */

#define RCC_CFGR_HPRE_DIV1                   0x00000000U                       /*!< SYSCLK not divided */
#define RCC_CFGR_HPRE_DIV2                   0x00000080U                       /*!< SYSCLK divided by 2 */
#define RCC_CFGR_HPRE_DIV4                   0x00000090U                       /*!< SYSCLK divided by 4 */
#define RCC_CFGR_HPRE_DIV8                   0x000000A0U                       /*!< SYSCLK divided by 8 */
#define RCC_CFGR_HPRE_DIV16                  0x000000B0U                       /*!< SYSCLK divided by 16 */
#define RCC_CFGR_HPRE_DIV64                  0x000000C0U                       /*!< SYSCLK divided by 64 */
#define RCC_CFGR_HPRE_DIV128                 0x000000D0U                       /*!< SYSCLK divided by 128 */
#define RCC_CFGR_HPRE_DIV256                 0x000000E0U                       /*!< SYSCLK divided by 256 */
#define RCC_CFGR_HPRE_DIV512                 0x000000F0U                       /*!< SYSCLK divided by 512 */

#define RCC_SYSCLK_DIV1                  RCC_CFGR_HPRE_DIV1   /*!< SYSCLK not divided */
#define RCC_SYSCLK_DIV2                  RCC_CFGR_HPRE_DIV2   /*!< SYSCLK divided by 2 */
#define RCC_SYSCLK_DIV4                  RCC_CFGR_HPRE_DIV4   /*!< SYSCLK divided by 4 */
#define RCC_SYSCLK_DIV8                  RCC_CFGR_HPRE_DIV8   /*!< SYSCLK divided by 8 */
#define RCC_SYSCLK_DIV16                 RCC_CFGR_HPRE_DIV16  /*!< SYSCLK divided by 16 */
#define RCC_SYSCLK_DIV64                 RCC_CFGR_HPRE_DIV64  /*!< SYSCLK divided by 64 */
#define RCC_SYSCLK_DIV128                RCC_CFGR_HPRE_DIV128 /*!< SYSCLK divided by 128 */
#define RCC_SYSCLK_DIV256                RCC_CFGR_HPRE_DIV256 /*!< SYSCLK divided by 256 */
#define RCC_SYSCLK_DIV512                RCC_CFGR_HPRE_DIV512 /*!< SYSCLK divided by 512 */

#define RCC_CFGR_PPRE1_DIV1                  0x00000000U                       /*!< HCLK not divided */
#define RCC_CFGR_PPRE1_DIV2                  0x00000400U                       /*!< HCLK divided by 2 */
#define RCC_CFGR_PPRE1_DIV4                  0x00000500U                       /*!< HCLK divided by 4 */
#define RCC_CFGR_PPRE1_DIV8                  0x00000600U                       /*!< HCLK divided by 8 */
#define RCC_CFGR_PPRE1_DIV16                 0x00000700U                       /*!< HCLK divided by 16 */

#define RCC_HCLK_DIV1                    RCC_CFGR_PPRE1_DIV1  /*!< HCLK not divided */
#define RCC_HCLK_DIV2                    RCC_CFGR_PPRE1_DIV2  /*!< HCLK divided by 2 */
#define RCC_HCLK_DIV4                    RCC_CFGR_PPRE1_DIV4  /*!< HCLK divided by 4 */
#define RCC_HCLK_DIV8                    RCC_CFGR_PPRE1_DIV8  /*!< HCLK divided by 8 */
#define RCC_HCLK_DIV16                   RCC_CFGR_PPRE1_DIV16 /*!< HCLK divided by 16 */

/*
 ----------------------------------------------------------------------------------------------------
 !-                                   PRIVATE FUNCTIONS PROTOTYPE
 ----------------------------------------------------------------------------------------------------
 */

static void RCC_void_Enable_HSI(u8 System_Clock_Flag);
static void RCC_void_Enable_HSE(u8 System_Clock_Flag,
		RCC_ClockType_t HSE_InputType);
static void RCC_void_Decoder(RCC_Bus_t BusType, u8 Value);
static void RCC_void_Enable_PLL(RCC_PLL_Input_t PLL_Input_Type,
		RCC_PLL_MultiplierFactor_t pllMultiplier, u8 system_Clock_Flag);
static void RCC_void_Set_Bus_Prescaler(void);
#endif /* MCAL_RCC_RCC_PRIVATE_H_ */

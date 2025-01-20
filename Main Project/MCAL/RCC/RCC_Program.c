/*
 * RCC_Program.c
 *
 *  Created on: Sep 21, 2024
 *  Author: Mohammed Khalaf
 */


#include "stdTypes.h"
#include "RCC_MemoryMap.h"
#include "BitwiseOperations_LIB.h"
#include "RCC_Private.h"
#include "RCC_Config.h"
#include "RCC_Interface.h"
#include "FLASH_ACR_MemoryMap.h"

/**
 * @brief Initialize the system clock source.
 *
 * @param clockType  Specifies the clock source (HSI, HSE, PLL).
 *                   Possible values: RCC_HSI, RCC_HSE_CRYSTAL, RCC_HSE_RC, RCC_PLL.
 *
 * @param pllInput   Specifies the PLL input clock source if PLL is selected.
 *                   Possible values: RCC_PLL_IN_HSI_DIV_2, RCC_PLL_IN_HSE_DIV_2, RCC_PLL_IN_HSE.
 *
 * @param pllMulFactor Specifies the multiplication factor for the PLL (only valid when PLL is used).
 *                     Range: 2 to 16 (depending on the microcontroller specification).
 *                     Example: Use 9 for 72MHz from 8MHz HSE.
 */


void RCC_void_System_Clock_Init(RCC_ClockType_t clockType, RCC_PLL_Input_t pllInput, RCC_PLL_MultiplierFactor_t pllMulFactor)
{
    switch (clockType)
    {
        case RCC_HSI:  // Case 1: HSI (High-Speed Internal oscillator) selected as system clock
            // Clear SW bits (SW_0 and SW_1) to select HSI as system clock source
            CLEAR_BIT(RCC->CFGR, SW_0);
            CLEAR_BIT(RCC->CFGR, SW_1);
            // Enable HSI oscillator
            SET_BIT(RCC->CR, HSION);
            break;

        case RCC_HSE_CRYSTAL:  // Case 2: HSE with crystal oscillator selected as system clock
            // Set SW_0 and clear SW_1 to select HSE as system clock source
            SET_BIT(RCC->CFGR, SW_0);
            CLEAR_BIT(RCC->CFGR, SW_1);
            // Disable bypass for the HSE, as we are using a crystal
            CLEAR_BIT(RCC->CR, HSEBYP);
            // Turn on HSE oscillator
            SET_BIT(RCC->CR, HSEON);
            break;

        case RCC_HSE_RC:  // Case 3: HSE with external RC oscillator selected as system clock
            // Set SW_0 and clear SW_1 to select HSE as system clock source
            SET_BIT(RCC->CFGR, SW_0);
            CLEAR_BIT(RCC->CFGR, SW_1);
            // Enable bypass for HSE, as we are using an external RC oscillator
            SET_BIT(RCC->CR, HSEBYP);
            // Turn on HSE oscillator
            SET_BIT(RCC->CR, HSEON);
            break;

        case RCC_PLL:  // Case 4: PLL (Phase-Locked Loop) selected as system clock
            // First, select PLL as system clock by clearing SW_0 and setting SW_1
            CLEAR_BIT(RCC->CFGR, SW_0);
            SET_BIT(RCC->CFGR, SW_1);

            // Set the PLL multiplication factor. Clear PLL multiplier bits and set desired multiplier.
            RCC->CFGR &= ~((0b1111) << PLLMUL_18);  // Clear bits 18-21 for PLL multiplier
            /*
           Step-by-step clearing of PLL multiplier bits (18-21)
           CLEAR_BIT(RCC->CFGR, PLLMUL_18); // Clear bit 18
           CLEAR_BIT(RCC->CFGR, PLLMUL_19); // Clear bit 19
           CLEAR_BIT(RCC->CFGR, PLLMUL_20); // Clear bit 20
           CLEAR_BIT(RCC->CFGR, PLLMUL_21); // Clear bit 21
            */
            RCC->CFGR |= (pllMulFactor << PLLMUL_18);  // Set the PLL multiplier based on the user input
          /*
          // Step-by-step setting of PLL multiplier bits based on the user input
            if (pllMulFactor & (1 << 0)) SET_BIT(RCC->CFGR, PLLMUL_18); // Set bit 18 if bit 0 of pllMulFactor is set
            if (pllMulFactor & (1 << 1)) SET_BIT(RCC->CFGR, PLLMUL_19); // Set bit 19 if bit 1 of pllMulFactor is set
            if (pllMulFactor & (1 << 2)) SET_BIT(RCC->CFGR, PLLMUL_20); // Set bit 20 if bit 2 of pllMulFactor is set
            if (pllMulFactor & (1 << 3)) SET_BIT(RCC->CFGR, PLLMUL_21); // Set bit 21 if bit 3 of pllMulFactor is set
*/
            // Configure the PLL input source
            switch (pllInput)
            {
                case RCC_PLL_IN_HSI_DIV_2:  // PLL input is HSI/2
                    // Clear PLLSRC bit to select HSI as PLL clock source
                    CLEAR_BIT(RCC->CFGR, SW_0);
                    CLEAR_BIT(RCC->CFGR, SW_1);
                    CLEAR_BIT(RCC->CFGR, PLLSRC);
                    break;

                case RCC_PLL_IN_HSE_DIV_2:  // PLL input is HSE/2
                    // Turn on HSE to use as PLL input
                    SET_BIT(RCC->CR, HSEON);
                    // Set PLLSRC bit to select HSE as PLL input source
                    SET_BIT(RCC->CFGR, PLLSRC);
                    // Set PLLXTPRE bit to divide HSE clock by 2 before feeding it to PLL
                    SET_BIT(RCC->CFGR, PLLXTPRE);
                    break;

                case RCC_PLL_IN_HSE:  // PLL input is HSE
                    // Turn on HSE to use as PLL input
                    SET_BIT(RCC->CR, HSEON);
                    // Set PLLSRC bit to select HSE as PLL input source
                    SET_BIT(RCC->CFGR, PLLSRC);
                    // Clear PLLXTPRE bit to not divide the HSE clock before feeding it to PLL
                    CLEAR_BIT(RCC->CFGR, PLLXTPRE);
                    break;

                default:
                    // Handle invalid PLL input error here if needed
                    break;
            }

            // To ensure that the APB1 peripheral clock remains below 36 MHz, divide it by 2
            SET_BIT(RCC->CFGR, PPRE1_10);

            // Enable PLL by setting PLLON bit
            SET_BIT(RCC->CR, PLLON);
            // Wait for PLL to stabilize and be ready to use as clock source
            while (GET_BIT(RCC->CR, PLLRDY) == 0);
            break;

        default:
            // Handle invalid clock type error here if needed (optional logging or error handling)
            break;
    }
}

// Use Flash Memory:

//void RCC_void_System_Clock_Init(RCC_ClockType_t clockType, RCC_PLL_Input_t pllInput, RCC_PLL_MultiplierFactor_t pllMulFactor, FLASH_ACR_t Flash_Latency, AHB_Prescaler_t AHB_Prescaler, APB1_Prescaler_t APB1Prescaler, APB2_Prescaler_t APB2Prescaler)
//{
//    // Step 1: Configure Flash Latency
//    FLASH->ACR &= ~((0b111) << LATENCY_1); // Clear LATENCY bits
////  FLASH->ACR |= (flashLatency << LATENCY_1); // Set the desired flash latency
//    SET_BIT(FLASH->ACR , Flash_Latency);
//
//    // Step 2: Configure the clock source
//    switch (clockType)
//    {
//        case RCC_HSI:  // High-Speed Internal oscillator
//            CLEAR_BIT(RCC->CFGR, SW_0);
//            CLEAR_BIT(RCC->CFGR, SW_1);
//            SET_BIT(RCC->CR, HSION);  // Enable HSI
//            break;
//
//        case RCC_HSE_CRYSTAL:  // HSE with crystal oscillator
//            SET_BIT(RCC->CFGR, SW_0);
//            CLEAR_BIT(RCC->CFGR, SW_1);
//            CLEAR_BIT(RCC->CR, HSEBYP); // Disable bypass
//            SET_BIT(RCC->CR, HSEON);  // Enable HSE
//            break;
//
//        case RCC_HSE_RC:  // HSE with external RC oscillator
//            SET_BIT(RCC->CFGR, SW_0);
//            CLEAR_BIT(RCC->CFGR, SW_1);
//            SET_BIT(RCC->CR, HSEBYP); // Enable bypass
//            SET_BIT(RCC->CR, HSEON);  // Enable HSE
//            break;
//
//        case RCC_PLL:  // Phase-Locked Loop
//            CLEAR_BIT(RCC->CFGR, SW_0);
//            SET_BIT(RCC->CFGR, SW_1);
//
//            RCC->CFGR &= ~((0b1111) << PLLMUL_18); // Clear PLLMUL bits
//            RCC->CFGR |= (pllMulFactor << PLLMUL_18); // Set PLL multiplier factor
//
//            // Step 3: Configure PLL input source
//            switch (pllInput)
//            {
//                case RCC_PLL_IN_HSI_DIV_2:  // HSI/2 as PLL input
//                    CLEAR_BIT(RCC->CFGR, PLLSRC);
//                    break;
//
//                case RCC_PLL_IN_HSE_DIV_2:  // HSE/2 as PLL input
//                    SET_BIT(RCC->CR, HSEON);  // Enable HSE
//                    SET_BIT(RCC->CFGR, PLLSRC);
//                    SET_BIT(RCC->CFGR, PLLXTPRE);  // Divide HSE by 2
//                    break;
//
//                case RCC_PLL_IN_HSE:  // HSE as PLL input
//                    SET_BIT(RCC->CR, HSEON);  // Enable HSE
//                    SET_BIT(RCC->CFGR, PLLSRC);
//                    CLEAR_BIT(RCC->CFGR, PLLXTPRE);  // No division
//                    break;
//
//                default:
//                    // Error handling for invalid PLL input
//                    break;
//            }
//
//            SET_BIT(RCC->CR, PLLON);  // Enable PLL
//            while (GET_BIT(RCC->CR, PLLRDY) == 0);  // Wait for PLL to be ready
//            break;
//
//        default:
//            // Error handling for invalid clock type
//            break;
//    }
//
//    // Step 4: Configure clock dividers for AHB, APB1, APB2
//    RCC->CFGR &= ~(0b1111 << HPRE_4);  			// Clear AHB Prescaler bits
//    RCC->CFGR |= AHB_Prescaler << HPRE_4;  	// AHB Clock Prescaler (no division)
//
//
//    RCC->CFGR &= ~(0b111 << PPRE1_8);  // Clear APB1 Prescaler bits
//    RCC->CFGR |= APB1Prescaler << PPRE1_8;  // APB1 Clock Prescaler (divided by 2)
//
//    RCC->CFGR &= ~(0b111 << PPRE2_11);  // Clear APB2 Prescaler bits
//    RCC->CFGR |= APB2Prescaler << PPRE2_11;  // APB2 Clock Prescaler (no division)
//}


void RCC_void_Enable_Clock(RCC_Bus_t Bus_ID , u8 Peripheral_ID)
{
    // Check if the peripheral ID is within valid range (0 to 31)
    if (Peripheral_ID <= 31)
    {
        switch (Bus_ID)
        {
            case RCC_AHBENR:
                SET_BIT(RCC->AHBENR, Peripheral_ID); // Enable clock on AHB bus
                break;
            case RCC_APB1ENR:
                SET_BIT(RCC->APB1ENR, Peripheral_ID); // Enable clock on APB1 bus
                break;
            case RCC_APB2ENR:
                SET_BIT(RCC->APB2ENR, Peripheral_ID); // Enable clock on APB2 bus
                break;
            default:
                // Handle invalid bus ID error
                // You may want to log or assert an error here
                break;
        }
    }
    else
    {
        // Handle invalid peripheral ID error
        // You may want to log or assert an error here
    }
}

void RCC_void_Disable_Clock(RCC_Bus_t Bus_ID , u8 Peripheral_ID)
{
    if (Peripheral_ID <= 31)
    {
        switch (Bus_ID)
        {
            case RCC_AHBENR  :
              CLEAR_BIT(RCC->AHBENR  ,Peripheral_ID);
              break;
            case RCC_APB1ENR :
              CLEAR_BIT(RCC->APB1ENR ,Peripheral_ID);
              break;
            case RCC_APB2ENR :
              CLEAR_BIT(RCC->APB2ENR ,Peripheral_ID);
              break;

              default:
        	/* Return Error */
        	break;
        }
    }

    else
    {
        /* Return Error */
    }
}

void RCC_void_APB2ENR_Enable(APB2_Bits_t REG_BIT)
{
  SET_BIT(RCC->APB2ENR , REG_BIT);
}

void RCC_void_APB2ENR_Disable(APB2_Bits_t REG_BIT)
{
  CLEAR_BIT(RCC->APB2ENR , REG_BIT);
}



/*
----------------------------------------------------------------------------------------------------
!-                                 PRIVATE FUNCTIONS IMPLEMENTATION
----------------------------------------------------------------------------------------------------
*/

// ===> From Config File :


static void RCC_void_Enable_HSI(u8 System_Clock_Flag)
{
    /** configure HSI */
    SET_BIT(RCC->CR, HSION);  // Enable HSI

    /* Wait for HSI to stabilize */
    while (!(GET_BIT(RCC->CR, HSIRDY)));

    if (System_Clock_Flag == TRUE)
    {
        /* Set HSI as system clock: 00 in SW bits */
        CLEAR_BIT(RCC->CFGR, SW_0);
        CLEAR_BIT(RCC->CFGR, SW_1);
    }
}





static void RCC_void_Enable_HSE(u8 System_Clock_Flag, RCC_ClockType_t HSE_InputType)
{
    if (HSE_InputType == RCC_HSE_RC)
    {
        /** Configure HSE RC */
        SET_BIT(RCC->CR, HSEBYP);  // Enable HSE with bypass (RC)
        /** Wait until the signal get stable */
         while( !(GET_BIT(RCC->CR, HSERDY)) );
    }
    else if (HSE_InputType == RCC_HSE_CRYSTAL)
    {
        /** @def Configure HSE crystal */
    	CLEAR_BIT(RCC->CR, HSEBYP);  // Enable HSE without bypass (Crystal)
        /** Wait until the signal get stable */
         while( !(GET_BIT(RCC->CR, HSERDY)) );
    }

    /** @def Enable HSE */
    SET_BIT(RCC->CR, HSEON);

    /** @def Wait for HSE to stabilize */
    while (!(GET_BIT(RCC->CR, HSERDY)));

    if (System_Clock_Flag == TRUE)
    {
        /** Set HSE as system clock: 01 in SW bits */
    	SET_BIT(RCC->CFGR, SW_0);
    	CLEAR_BIT(RCC->CFGR, SW_1);
    }
    else
    {

    }
}

static void RCC_void_Enable_PLL(RCC_PLL_Input_t PLL_Input_Type, RCC_PLL_MultiplierFactor_t pllMultiplier, u8 system_Clock_Flag)
{
    // PLL input source configuration
    switch (PLL_Input_Type)
    {
        case RCC_PLL_IN_HSI_DIV_2:  // PLL input is HSI divided by 2
            // Enable HSI
            RCC_void_Enable_HSI(FALSE);
            // Set HSI as PLL clock source
            CLEAR_BIT(RCC->CFGR, PLLXTPRE);
            CLEAR_BIT(RCC->CFGR, PLLSRC);
            break;

        case RCC_PLL_IN_HSE_DIV_2:  // PLL input is HSE divided by 2
            // Enable HSE
            RCC_void_Enable_HSE(FALSE, RCC_HSE_RC);
            // Set HSE as PLL clock source with division by 2
            SET_BIT(RCC->CFGR, PLLXTPRE);
            SET_BIT(RCC->CFGR, PLLSRC);
            break;

        case RCC_PLL_IN_HSE:  // PLL input is HSE directly
            // Enable HSE
        	RCC_void_Enable_HSI(FALSE);
            // Set HSE as PLL clock source without division
        	CLEAR_BIT(RCC->CFGR, PLLXTPRE);
        	SET_BIT(RCC->CFGR, PLLSRC);
            break;

        default:
            // Handle invalid PLL input type here (optional logging or error handling)
            return;  // Exit the function if invalid input
    }

    // Set the PLL multiplier using a helper function or bit manipulation
    RCC_void_Decoder(RCC_PLL_BUS, pllMultiplier);  // Set PLL multiplier

    // Enable the PLL
    SET_BIT(RCC->CR, PLLON);
    // Wait until PLL is ready
    while (!(GET_BIT(RCC->CR, PLLRDY)));

    // If systemClockFlag is set, select PLL as the system clock source
    if (system_Clock_Flag == TRUE)
    {
    	CLEAR_BIT(RCC->CFGR, SW_0);
        SET_BIT(RCC->CFGR, SW_1);
    }
    else
    {

    }
} /** RCC_void_Enable_PLL */



void RCC_Enable_8_MHz_HSI(void){
	SET_BIT(RCC -> CR, HSION); //Enable HSI.
	while(GET_BIT(RCC -> CR, HSIRDY)); //Polling until HSI is ready.
	SET_BIT(RCC -> CIR, HSIRDYC); //Clear HSI ready flag.
	CLEAR_BIT(RCC -> CFGR, SW_0); //Select HSI as system clock.
	CLEAR_BIT(RCC -> CFGR, SW_1); //Select HSI as system clock.
}

static void RCC_void_Decoder(RCC_Bus_t BusType, u8 Value)
{
   switch (BusType)
   {
        case RCC_AHBENR :
				RCC->CFGR &=  (u32) (~( (0b1111) << (HPRE_4) ));
				RCC->CFGR |=  (u32) ((Value) << (HPRE_4));
            break;
        case RCC_APB1ENR:
				RCC->CFGR &=  (u32) (~( (0b111) << (PPRE1_8) ));
				RCC->CFGR |=  (u32) ((Value) << (PPRE1_8));
            break;
        case RCC_APB2ENR:
				RCC->CFGR &=  (u32) (~( (0b111) << (PPRE2_11) ));
				RCC->CFGR |=  (u32) ((Value) << (PPRE2_11));
            break;
        case  RCC_PLL_BUS:
				RCC->CFGR &=  (u32) (~( (0b111) << (PLLMUL_18) ));
				RCC->CFGR |=  (u32) ((Value) << (PLLMUL_18));
            break;
        default: return; /** @todo error handler */
   }
}

static void RCC_void_Set_Bus_Prescaler(void)
{
	RCC_void_Decoder(RCC_AHBENR,  AHB_PRESCALER);
	RCC_void_Decoder(RCC_APB1ENR, APB1_PRESCALER);
	RCC_void_Decoder(RCC_APB2ENR, APB2_PRESCALER);

}/** @end RCC_voidSetBusPrescaler */


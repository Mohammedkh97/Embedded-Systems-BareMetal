/*
 * 	MainApp.c
 *  Created on: Sep 15, 2024
 *  Author: Mohammed Khalaf
 */

/* -----------------------------------------------Private Inclusions -------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include <stdlib.h>
#include <stdio.h>

/* ------------------------------------------------ Inclusions ------------------------------------------------------------------*/

#include "stdTypes.h"
#include "RCC_Interface.h"
#include "GPIO_Interface.h"
#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "GLCD_ST7920_Interface.h"
#include "delay.h"
#include "USART_Interface.h"
#include "USART_Services.h"
#include "HX711_Load_Cell.h"
#include "Scale Configurations.h"
#include "SPI_Interface.h"
#include "String_lib.h"

#include "Al-Ahram.h"
#include "App_Consideration.h"
#include "App_Services.h"

#include "../../HAL/LCD_TFT_ST7789v/TFT_Interface.h"

/*---------------------------------------------------------- Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
/* ----------------------------------------------------- Private App function prototypes -----------------------------------------------*/

/* ------------------------------------------------------- Global Variable Definitions ------------------------------------- -----------*/

f32 weight;
u8 strWeight[30];
u32 stableWeight = 0;
f32 avgSpecies = INITIAL_SPEC_AVG;
f32 previousAvg = 0;
f32 UpdatedAvg = 0;

// Real Time Counters:
u16 Normal_Species_Counts = 0;
u16 Strange_Species_Counts = 0;
u16 Total_Counts = 0;

u16 AccumulatedCounts = 0;
u16 total_Static_Counts = 0;
f32 AccumulatedWeight = 0.0;
f32 avgWeight = 0;

u8 i = 0;
u8 data[20];
u8 dataToSend[30];
u8 sendCount = 0;
/* --------------------------------------------------------------- Flags -------------------------------------------------- */
u8 stableFlag = 0;
u8 exitFlag = 1;
u8 sendFlag = 0;

/* ------------------------------------------------- Application Functions Declaration ----------------------------*/

void Al_Ahram_setup()
{
//	HAL_Init();
	Al_Ahram_SystemClock_Config();
//	RCC_void_System_Clock_Init(RCC_PLL, RCC_PLL_IN_HSE_DIV_2, PLL_CLOCK_MULTIPLE_BY_9);
//	RCC_void_System_Clock_Init(RCC_PLL, RCC_PLL_IN_HSE_DIV_2, PLL_CLOCK_MULTIPLE_BY_9, LATENCY_2, AHB_PRESCALER_1, APB1_PRESCALER_2, APB2_PRESCALER_1);
	Al_Ahram_MX_TIM1_Init();

//	delay_init();	//	HAL_TIM_Base_Start(&handler_timer1);

	HAL_TIM_Base_Start(&htim1);

	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOA_EN);
	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOC_EN);
	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOB_EN);
	GPIO_void_Initializtion();

//	GPIO_void_SetPinMode1(BUTTON_GENERAL_RESULT, DIO_INPUT_FLOATING);
//	GPIO_void_SetPinMode1(BUTTON_PAGE_1, DIO_INPUT_FLOATING);
//	GPIO_void_SetPinMode1(BUTTON_PAGE_2, DIO_INPUT_FLOATING);
//	GPIO_void_SetPinMode1(HOLD_BUTTON, DIO_INPUT_FLOATING);
//	GPIO_void_SetPinMode1(STABLE_LED, DIO_OUTPUT_PUSHPULL_10MHZ);

//	USART_void_Initializtion(USART_1, USART_MODE_TX_RX, USART_PARITY_NONE, USART_PARITY_NONE, USART_WORDLENGTH_8_BITS, 115200);
//	SPI_void_Initialization(SPI_2, SPI_MODE_MASTER, SPI_DIRECTION_2LINES, SPI_DATAFORMAT_8_BIT, SPI_CPOL_HIGH, SPI_CPHA_FIRST_EDGE, PRESCALER_16, SPI_NSS_SOFT);

	GLCD_ST7920_init();
//	HTFT_voidInit();
//	HTFT_voidFillScreen(COLOR_RED);
	GLCD_ST7920_SendString(1, 0, (u8*) "Mohammed");
//	HTFT_voidWriteString(15, 5, (u8*) "Mohammed ESWE", COLOR_BLACK, COLOR_RED);
//	HTFT_voidWriteString(15, 0, (u8*) "\nWelcome!   ", COLOR_BLACK, COLOR_RED);

//	HX711_Calibrate();
}

void Al_Ahram_Runnable()
{
	weight = HX711_WeightRead();
	if (weight < 0)
	{
		weight = 0;
	}
	//GLCD_ST7920_WriteNumber(1, 0, weight, 5);
	intoString(weight, strWeight);
	HTFT_voidWriteString(15, 100, strWeight, COLOR_BLACK, COLOR_RED);

//	Normal_Species_Counts = detectSpecies(weight, &Strange_Species_Counts);
//
//	stableWeight = getStableWeight(weight, &AccumulatedCounts,
//			&AccumulatedWeight, avgSpecies);
//	Total_Counts = Normal_Species_Counts + Strange_Species_Counts;
//
//	// Display Options:
//	if (GPIO_DIO_PinVoltage_Read_Pin_Method1(BUTTON_GENERAL_RESULT) == HIGH)
//	{
//		//		GLCD_Display_Result(stableWeight, AccumulatedCounts, Normal_Species_Counts, Strange_Species_Counts, Total_Counts, AccumulatedWeight);
//	}
//	else if (GPIO_DIO_PinVoltage_Read_Pin_Method1(BUTTON_PAGE_1) == HIGH)
//	{
//		//		DisplayPage1();
//
//	}
//	else if (GPIO_DIO_PinVoltage_Read_Pin_Method1(BUTTON_PAGE_2) == HIGH)
//	{
//		//		DisplayPage2();
//	}
//
//	//	DisplayPage2();
//	GLCD_Display_Result(stableWeight, AccumulatedCounts, Normal_Species_Counts, Strange_Species_Counts, Total_Counts, AccumulatedWeight);

	/*	 if ((staticNormalCounts == SPECIES_NUM && !sendFlag) || (total_Static_Counts >= SPECIES_NUM &&!sendFlag))
	 {
	 avgSpecies = (staticWeights / staticNormalCounts);
	 sendDataToESP32(normalCounts , strangeCounts , totalCounts , staticNormalCounts, avgSpecies);
	 sendFlag = 1;
	 previousAvg = avgSpecies;
	 }
	 */

}

f32 getStableWeight(f32 currentWeight, u16 *pAccumulatedCounts,
		f32 *pAccumulatedWeight, f32 avgWeight)
{
	static f32 previousWeight = 0.0;  // Previous weight from the last iteration
	static f32 lastStableWeight = 0.0;     // Last known stable weight
	static f32 totalStableWeight = 0.0;    // Accumulated stable weight
//    static u16 totalSpeciesCount = 0;      // Total species count for all stable weights
	static u16 stableCounter = 0;          // Stability counter
	static u16 Counts = 0;

//    // Noise tolerance (ignore small fluctuations)
//    const f32 NOISE_THRESHOLD = 300.0;      // Adjust based on your sensor's sensitivity

	// Check if the weight is stable within the threshold
	if (get_AbsoluteValue(
			currentWeight - previousWeight) <= STATIC_WEIGHT_THRESHOLD)
	{
		GPIO_void_Write_Pin_Method1(STABLE_LED, LOW);
		stableCounter++;  // Increment stability counter
	}
	else
	{
		stableCounter = 0;  // Reset stability counter on instability
	}

	// If weight stabilizes for sufficient time
	if (stableCounter >= STABLE_COUNT_THRESHOLD)
	{
		stableCounter = STABLE_COUNT_THRESHOLD;  // Prevent counter overflow

		// Check for meaningful weight addition (above noise threshold)
		if ((currentWeight - lastStableWeight) > NOISE_THRESHOLD)
		{
			f32 addedWeight = currentWeight - lastStableWeight; // Calculate the added weight
			totalStableWeight += addedWeight;  // Update the total stable weight
			lastStableWeight = currentWeight;  // Update the last stable weight
			GPIO_void_Write_Pin_Method1(STABLE_LED, HIGH);

		}
		else if ((lastStableWeight - currentWeight) > NOISE_THRESHOLD) // Weight removed
		{
			lastStableWeight = currentWeight; // Update the last stable weight (only for tracking)
		}
	}

	previousWeight = currentWeight; // Update previous weight for the next iteration

	// Static Counts that used to calculate the updated Average:

	Counts = (u16) (totalStableWeight / (avgWeight));

	// Reset logic if needed (optional, based on your logic)
	if (Counts == (SPECIES_NUM) || Counts >= SPECIES_NUM)
	{
		UpdatedAvg = (totalStableWeight) / SPECIES_NUM;
		avgSpecies = UpdatedAvg;
		Counts = 0;
		totalStableWeight = 0;  // Reset stable weight accumulation
	}
	// Update parameters for external use
	*pAccumulatedCounts = Counts;       		// Total detected species count
	*pAccumulatedWeight = totalStableWeight;         // Total stable weight
	//   *pTotalStaticCounts = totalSpeciesCount;     // Total species count  //Not used until Now

	return currentWeight;  // Return the current stable weight
}

u16 detectSpecies(f32 currentWeight, u16 *pStrangeCount)
{
	u16 strangeSpecCount = 0;
	u16 normalCounts = 0;

	while (currentWeight >= (avgSpecies + SPEC_VARIANCE)
			|| currentWeight >= (avgSpecies - SPEC_VARIANCE))
	{
		if ((currentWeight >= (avgSpecies + STRANGE_VARIANCE_0))
				&& (currentWeight <= (avgSpecies + STRANGE_VARIANCE_1)))
		{
			strangeSpecCount++;
		}
		else if (currentWeight
				>= (avgSpecies - SPEC_VARIANCE) /*&& currentWeight <= (avgSpecies + SPEC_VARIANCE)*/)
		{
			normalCounts++;
		}
		else if (currentWeight <= (avgSpecies + SPEC_VARIANCE))
		{
			normalCounts++;
		}

		currentWeight = currentWeight - avgSpecies;
	}

	*pStrangeCount = strangeSpecCount;
	//	*pNormStableCounts = total_Static_Counts;
	return normalCounts;
}

void sendDataToESP32(u16 Normal, u16 Strange, u16 TotalCounts, u16 Static_Total,
		u16 avgSpecies)
{
//	sprintf((u8*)data, (u8*)"%u,%u,%u,%u,%u ", Normal, Strange, TotalCounts , Static_Total , avgSpecies);
	//sprintf((u8*)data, (u8*)"%u", avgSpecies);
	intoString(avgSpecies, data);
	//sprintf((u8*)data , "%u" , avgSpecies);
	// Debug print to see the data being sent
	// 	GLCD_ST7920_Clear();
	// 	GLCD_ST7920_SendString(2, 0, (u8*)data);
	//	GLCD_ST7920_DisplayPage1();

	USART_Transmit_String(USART_1, data, '\n');

	data[0] = '\0';
}

void GLCD_Display_Result(f32 weight, u16 AccumulatedCounts, u16 Normal_Counts,
		u16 Strange_Counts, u16 total_Counts, u16 AccumulatedWeight)
{
	GLCD_ST7920_SendString(0, 0, (u8*) "Initial Avg.");
	GLCD_ST7920_WriteNumber(0, 6, INITIAL_SPEC_AVG, 3);
	GLCD_ST7920_SendString(1, 0, (u8*) "Up Avg.");
	GLCD_ST7920_WriteFloatNumber(1, 4, avgSpecies, 1, 5);

	// Display Conuts: Real Time Normal, Strange, and Total counts
	GLCD_ST7920_WriteNumber(2, 0, Normal_Counts, 2);
	GLCD_ST7920_WriteNumber(2, 2, Strange_Counts, 2);
	GLCD_ST7920_WriteNumber(2, 4, total_Counts, 2);
	GLCD_ST7920_WriteNumber(2, 6, AccumulatedCounts, 2);
	//	GLCD_ST7920_WriteNumber(2,6,staticNormalCounts);

	// Display stable weights and weight in kg
	GLCD_ST7920_WriteNumber(3, 0, AccumulatedWeight, 5);  // Weight in grams
//	GLCD_ST7920_WriteNumber(3, 0, weight, 5);
	f32 weight_KG = weight / KILOGRAM;
	GLCD_ST7920_WriteFloatNumber(3, 4, weight_KG, 2, 6);

}

void DisplayPage1()
{
//	GLCD_ST7920_Clear();
	GLCD_ST7920_SendString(0, 0, (u8*) "Page 1:");
	GLCD_ST7920_SendString(1, 0, (u8*) "Trial Parameters:");
	GLCD_ST7920_SendString(2, 0, (u8*) "Measured:");
	GLCD_ST7920_WriteFloatNumber(2, 5, weight / 1000.0, 1, 5);
	GLCD_ST7920_SendString(3, 0, (u8*) "Stable:");
	GLCD_ST7920_WriteNumber(3, 4, stableWeight, 5);

}

void DisplayPage2()
{
//	GLCD_ST7920_Clear();
	GLCD_ST7920_SendString(0, 0, (u8*) "Page 2: Counters");
	GLCD_ST7920_SendString(1, 0, (u8*) "Normal");
	GLCD_ST7920_SendString(2, 0, (u8*) "Strange");
	GLCD_ST7920_WriteNumber(1, 4, Normal_Species_Counts, 1);
	GLCD_ST7920_SendString(1, 5, (u8*) "Up Avg");
	GLCD_ST7920_WriteNumber(2, 5, avgSpecies, 3);
	GLCD_ST7920_WriteNumber(2, 4, Strange_Species_Counts, 1);
	GLCD_ST7920_SendString(3, 0, (u8*) "Total   Accum.");
	GLCD_ST7920_WriteNumber(3, 3, Total_Counts, 1);
	GLCD_ST7920_WriteNumber(3, 7, AccumulatedCounts, 1);
}

void DisplayPage3()
{
	GLCD_ST7920_Clear();
	GLCD_ST7920_SendString(0, 0, (u8*) "Page 3:");
	GLCD_ST7920_SendString(1, 0, (u8*) "Yet Another Page");
}

/* -------------------------- Declaration of Private App Functions ---------------------------------- */
void Al_Ahram_SystemClock_Config()
{
	RCC_OscInitTypeDef RCC_OscInitStruct =
	{ 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct =
	{ 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Al_Ahram_Error_Handler();
	}

	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
	{
		Al_Ahram_Error_Handler();
	}
}

static void Al_Ahram_MX_TIM1_Init()
{
	TIM_ClockConfigTypeDef sClockSourceConfig =
	{ 0 };
	TIM_MasterConfigTypeDef sMasterConfig =
	{ 0 };

	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 72 - 1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 0xffff - 1;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
	{
		Al_Ahram_Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
	{
		Al_Ahram_Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Al_Ahram_Error_Handler();
	}
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Al_Ahram_Error_Handler()
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t *file, uint32_t line)
{
	/* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

//// SEND TO ESP USING AT COMMANDS:
////u8 receivedString[10];
//
//// void UART_SendCommand(const char *cmd)
//// {
//// 	UART_TransmitString(cmd, UART0);
//// 	UART_TransmitString("\r\n", UART0);
//
// void sysInit()
//{
//	GPIO_void_Initializtion();
//	init_pins();
//
//	GLCD_ST7920_init();
//	USART_void_Initializtion(USART_1, USART_MODE_TX_RX, USART_PARITY_NONE,
//			USART_STOPBITS_1, USART_WORDLENGTH_8_BITS, 9600);
//
//	GLCD_ST7920_SendString(0, 0, (u8*) "Hi");
//
//	// Send AT command to ESP32
//	//  UART_TransmitString((u8*)"AT\r\n", UART0);
//	//_delay_ms(500);
//
//	USART_Transmit_String(USART_1, (u8*) "AT+CWMODE=1",'\0');
//	USART_Transmit_String(USART_1, (u8*) "\r\n",'\0');
//	HAL_Delay(1000);
//	USART_Transmit_String(USART_1, (u8*) "AT+CWJAP=\"Ahmed Hassan\",\"Ahmed 111\"",'\0');
//	USART_Transmit_String(USART_1, (u8*) "\r\n", '\0');
//	// Wait for a short time to allow ESP32 to respond
//	HAL_Delay(5000);
//	USART_Transmit_String(USART_1, (u8*) "AT+CIPSTART=\"TCP\",\"ue-dt.somee.com\",80", '\0');
//	USART_Transmit_String(USART_1, (u8*) "\r\n", '\0');
//	HAL_Delay(1000);
//	USART_Transmit_String(USART_1, (u8*) "AT+CIPSEND=180", '\0');
//	USART_Transmit_String(USART_1, (u8*) "\r\n", '\0');
//	//send the size of get request
//	HAL_Delay(1000);
//	//make a get request
//	USART_Transmit_String(USART_1, (u8*) "GET /api/Cows/AddNewCow?cow_ID=77788&weight=77788&issues=1&barn_ID=2&typeOfCows_ID=3&supplierId=4 HTTP/1.1\r\nHost: ue-dt.somee.com\r\nConnection: close\r\n\r\n",'\0');
//	USART_Transmit_String(USART_1, (u8*) "\r\n", '\0');
//	HAL_Delay(1000);
//
//
//}
// void sysRunnable()
//{
//
//}

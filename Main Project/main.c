/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stdTypes.h"
#include "RCC_Interface.h"
#include "GPIO_Interface.h"
//#include "LCD_interface.h"
#include "KEYPAD_interface.h"
#include "GLCD_ST7920_Interface.h"
#include "bitmap.h"
#include "delay.h"
#include "horse.h"

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */

int main(void)
{
	HAL_Init();
	/* Configure the system clock */
	SystemClock_Config();
	//RCC_void_System_Clock_Init(RCC_PLL, RCC_PLL_IN_HSE_DIV_2, PLL_CLOCK_MULTIPLE_BY_9, LATENCY_2);
//	RCC_void_System_Clock_Init(RCC_PLL, RCC_PLL_IN_HSE_DIV_2, PLL_CLOCK_MULTIPLE_BY_9, LATENCY_2, AHB_PRESCALER_1, APB1_PRESCALER_2, APB2_PRESCALER_1);
	/*
	 Final System Clock:
	 The system clock will be 16 MHz.
	 Here's the calculation breakdown:

	 HSE = 8 MHz
	 HSE divided by 2 → 4 MHz (input to PLL)
	 4 MHz multiplied by 4 (PLL multiplier) → 16 MHz
	 */
	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOA_EN);
	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOC_EN);
	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOB_EN);
	/* USER CODE BEGIN SysInit */
	/* Initialize all configured peripherals */
//	MX_GPIO_Init();
	MX_TIM1_Init();
//	/* USER CODE BEGIN 2 */
//	HAL_TIM_Base_Start(&htim1);
	/* USER CODE END 2 */
	GPIO_void_Initializtion();
//	LCD_Init();
	KEYPAD_init();
	delay_init();
	GLCD_ST7920_init();
//	GLCD_ST7920_SendString(0, 0, (u8*) "Mohammed Khalaf");
//	LCD_GoTo_WriteFloatNumber(1, 14, 2.5, 2);
//	LCD_Goto_WriteString(1, 1, (u8*) "I'm Mohammed");

	GLCD_ST7920_GraphicMode(1);
//	GLCD_ST7920_DrawBitMap(bitmap);
	u8 cursor = 1;
	while (1)
	{
		GLCD_ST7920_DrawBitMap(horse1);
		GLCD_ST7920_DrawBitMap(horse2);
		GLCD_ST7920_DrawBitMap(horse3);
		GLCD_ST7920_DrawBitMap(horse4);
		GLCD_ST7920_DrawBitMap(horse5);
		GLCD_ST7920_DrawBitMap(horse6);
		GLCD_ST7920_DrawBitMap(horse7);
		GLCD_ST7920_DrawBitMap(horse8);
		GLCD_ST7920_DrawBitMap(horse9);
		GLCD_ST7920_DrawBitMap(horse10);
//		u8 key = KEYPAD_GetKey();  // Get the key pressed
//
//		if (key != NO_KEY)
//		{
////			LCD_Goto_WriteCharacter(2, cursor, key);
////			cursor++;
//
//			// Control LEDs based on the key pressed
//			switch (key)
//			{
//			case '1':  // Turn LED 1 ON/OFF
//				GPIO_void_Toggle_Pin(PINC13); // Assuming LED 1 is connected to PINC0
//				//GPIO_void_Write_Pin_Method1(PINC13, HIGH);
//				break;
//
//			case '2':  // Turn LED 2 ON/OFF
//				GPIO_void_Toggle_Pin(PINC14); // Assuming LED 2 is connected to PINC1
//				//GPIO_void_Write_Pin_Method1(PINC13, LOW);
//				break;
//
//			case '3':  // Turn LED 3 ON/OFF
//				GPIO_void_Toggle_Pin(PINC15); // Assuming LED 3 is connected to PINC2
//				break;
//
//			case '4':  // Turn LED 4 ON/OFF
//				GPIO_void_Toggle_Pin(PINA1); // Assuming LED 4 is connected to PINC3
//				break;
//			case '5':
//				GPIO_void_Toggle_Pin(PINA2);
//				break;
//			case '6':
//				GPIO_void_Toggle_Pin(PINA3);
//				break;
//				// You can add more cases for additional LEDs
//			case '7':
//				GPIO_void_Toggle_Pin(PINB9);
//			default:
//				break;
//			}
//		}
		}
//	/* USER CODE END 3 */
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
void SystemClock_Config (void)
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
  if (HAL_RCC_OscConfig (&RCC_OscInitStruct) != HAL_OK)
    {
      Error_Handler ();
    }

  /** Initializes the CPU, AHB and APB buses clocks
   */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
      | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig (&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
    {
      Error_Handler ();
    }
}
/**
 * @brief TIM1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_TIM1_Init (void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig =
    { 0 };
  TIM_MasterConfigTypeDef sMasterConfig =
    { 0 };

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 72 - 1;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 0xffff - 1;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init (&htim1) != HAL_OK)
    {
      Error_Handler ();
    }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource (&htim1, &sClockSourceConfig) != HAL_OK)
    {
      Error_Handler ();
    }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization (&htim1, &sMasterConfig) != HAL_OK)
    {
      Error_Handler ();
    }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct =
	{ 0 };
	/* USER CODE BEGIN MX_GPIO_Init_1 */
	/* USER CODE END MX_GPIO_Init_1 */

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOD_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();
	__HAL_RCC_GPIOB_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB,
	GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8,
			GPIO_PIN_RESET);

	/*Configure GPIO pins : PB3 PB4 PB5 PB6
	 PB7 PB8 */
	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6
			| GPIO_PIN_7 | GPIO_PIN_8;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

	/* USER CODE BEGIN MX_GPIO_Init_2 */
	/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void)
{
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1)
	{
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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

//#include "main.h"
//#include "stdTypes.h"
//#include "RCC_Interface.h"
//#include "GPIO_Interface.h"
//#include "LCD_interface.h"
//#include "KEYPAD_interface.h"
//#include "GLCD_ST7920_Interface.h"
//#include "bitmap.h"
//#include "delay.h"
//#define LED_PIN         PINC14
////#define BUTTON_PIN      PINB5
//
//TIM_HandleTypeDef htim1;
//
//#include "stm32f1xx_hal.h"  // Replace with your device family, e.g., stm32f4xx_hal.h for STM32F4 series
//
///* Private function prototypes -----------------------------------------------*/
//void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
//static void MX_TIM1_Init(void);
//
//int main(void)
//{
//	HAL_Init();  // Initialize the HAL library (this sets up SysTick)
//// Initialize the system clock
//	/* Initialize all configured peripherals */
////	SystemClock_Config();
////	RCC_void_System_Clock_Init(RCC_HSE_CRYSTAL, RCC_PLL_IN_HSE_DIV_2,
////			PLL_CLOCK_MULTIPLE_BY_4);
//
//	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOA_EN);
//	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOC_EN);
//	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOB_EN);
//
//	SystemClock_Config();
//	GPIO_void_Initializtion();
//	/* Initialize all configured peripherals */
//	MX_GPIO_Init();
//	MX_TIM1_Init();
//
//	LCD_Init();
//	KEYPAD_init();
//
//	delay_init();
////	GLCD_ST7920_init();
////	GLCD_ST7920_SendString(0, 0, (u8*) "Mohammed Khalaf");
////
////	LCD_GoTo_WriteFloatNumber(1, 14, 2.51, 1);
////	LCD_Goto_WriteString(1, 1, (u8*) "I'm Mohammed ESWE");
////	HAL_Delay(2000);
////	GLCD_ST7920_Clear();
//
////	GLCD_ST7920_GraphicMode(1);
////
////	GLCD_ST7920_DrawBitMap(bitmap);
//	u8 cursor = 1;
//
//	while (1)
//	{
//		/****************************************** Test Writing on The Bits *******************************************/
//
////	  GPIO_void_Write_Pin_Method2(PORTC, PINC13, HIGH);
////	  GPIO_void_Write_Pin_Method1(PINA2, HIGH);
////	  GPIO_void_Write_Pin_Method2(PORTC, PINC13, LOW);
////      GPIO_void_Write_Pin_Method1(PINA2, LOW);
////      GPIO_void_Write_Pin_Method1(PINA3, HIGH);
////      HAL_Delay(1000);          // Delay 1 second
//		/*************************** Test Read Bits and Get the value of Register Bit ********************************/
//
//		// if (!(GPIO_DIO_PinVoltage_Read_Pin_Method2(PORTB, BUTTON_PIN)))
////    	  if(GPIO_DIO_PinVoltage_Read_Pin_Method2(PORTB, BUTTON_PIN) == LOW)
////      {
////          // Turn on the LED
////          GPIO_void_Write_Pin_Method1(LED_PIN, HIGH);
////      }
////      else if(GPIO_DIO_PinVoltage_Read_Pin_Method2(PORTB, BUTTON_PIN))
////      {
////          // Turn off the LED
////          GPIO_void_Write_Pin_Method1(LED_PIN, LOW);
////      }
//		/********************************************* Test Toggle Bits *************************************************/
////	  GPIO_void_Write_Pin_Method1(PINA3, HIGH);        // Delay 1 second
//		u8 key = KEYPAD_GetKey();  // Get the key pressed
//
//		if (key != NO_KEY)
//		{
//			// Control LEDs based on the key pressed
//			switch (key)
//			{
//			case '1':  // Turn LED 1 ON/OFF
//				GPIO_void_Toggle_Pin(PINC13); // Assuming LED 1 is connected to PINC0
//				break;
//
//			case '2':  // Turn LED 2 ON/OFF
//				GPIO_void_Toggle_Pin(PINC14); // Assuming LED 2 is connected to PINC1
//				break;
//
//			case '3':  // Turn LED 3 ON/OFF
//				GPIO_void_Toggle_Pin(PINC15); // Assuming LED 3 is connected to PINC2
//				break;
//
//			case '4':  // Turn LED 4 ON/OFF
//				GPIO_void_Toggle_Pin(PINA1); // Assuming LED 4 is connected to PINC3
//				break;
//			case '5':
//				GPIO_void_Toggle_Pin(PINA2);
//				break;
//			case '6':
//				GPIO_void_Toggle_Pin(PINA3);
//				break;
//				// You can add more cases for additional LEDs
//			case '7':
//				GPIO_void_Toggle_Pin(PINB9);
//			default:
//				break;
//			}
//			//GLCD_ST7920_WriteChar(0, cursor-1, key);
//			cursor++;
//			if (cursor >= 16)
//			{
//				cursor = 0;
//			}
//		}
//
//	}
//}
//
//void SystemClock_Config(void)
//{
//	RCC_OscInitTypeDef RCC_OscInitStruct =
//	{ 0 };
//	RCC_ClkInitTypeDef RCC_ClkInitStruct =
//	{ 0 };
//
//	/** Initializes the CPU, AHB and APB busses clocks
//	 */
//	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
//	RCC_OscInitStruct.HSEState = RCC_HSE_ON;
//	RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
//	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
//	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
//	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
//	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
//	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	/** Initializes the CPU, AHB and APB busses clocks
//	 */
//	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
//			| RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
//	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
//	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
//	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
//	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
//
//	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
//	{
//		Error_Handler();
//	}
//}
//static void MX_TIM1_Init(void)
//{
//
//	/* USER CODE BEGIN TIM1_Init 0 */
//
//	/* USER CODE END TIM1_Init 0 */
//
//	TIM_ClockConfigTypeDef sClockSourceConfig =
//	{ 0 };
//	TIM_MasterConfigTypeDef sMasterConfig =
//	{ 0 };
//
//	/* USER CODE BEGIN TIM1_Init 1 */
//
//	/* USER CODE END TIM1_Init 1 */
//	htim1.Instance = TIM1;
//	htim1.Init.Prescaler = 72 - 1;
//	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
//	htim1.Init.Period = 0xffff - 1;
//	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
//	htim1.Init.RepetitionCounter = 0;
//	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
//	if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
//	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
//	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
//	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
//	{
//		Error_Handler();
//	}
//	/* USER CODE BEGIN TIM1_Init 2 */
//
//	/* USER CODE END TIM1_Init 2 */
//
//}
//static void MX_GPIO_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct =
//	{ 0 };
//
//	/* GPIO Ports Clock Enable */
//	__HAL_RCC_GPIOB_CLK_ENABLE();  // Enable GPIOB clock
//
//	/* Configure GPIO pin Output Level */
//	HAL_GPIO_WritePin(GPIOB,
//	GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8,
//			GPIO_PIN_RESET);
//
//	/* Configure GPIO pins : PB3 PB4 PB5 PB6 PB7 PB8 PB9 */
//	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6
//			| GPIO_PIN_7 | GPIO_PIN_8;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;  // Push-pull output mode
//	GPIO_InitStruct.Pull = GPIO_NOPULL;          // No pull resistor
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW; // Low speed
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//}
//void Error_Handler(void)
//{
//	/* USER CODE BEGIN Error_Handler_Debug */
//	/* User can add his own implementation to report the HAL error return state */
//
//	/* USER CODE END Error_Handler_Debug */
//}
//
//#ifdef  USE_FULL_ASSERT
///**
//  * @brief  Reports the name of the source file and the source line number
//  *         where the assert_param error has occurred.
//  * @param  file: pointer to the source file name
//  * @param  line: assert_param error line source number
//  * @retval None
//  */
//void assert_failed(uint8_t *file, uint32_t line)
//{
//  /* USER CODE BEGIN 6 */
//  /* User can add his own implementation to report the file name and line number,
//     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//  /* USER CODE END 6 */
//}
//#endif /* USE_FULL_ASSERT */


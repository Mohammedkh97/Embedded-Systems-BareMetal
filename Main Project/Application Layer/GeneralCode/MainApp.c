/*
 * MainApp.cpp
 *
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
#include "bitmap.h"
#include "delay.h"
#include "horse.h"
#include "USART_Interface.h"
#include "USART_Services.h"
#include "HX711_Load_Cell.h"
#include "RFID/MFRC522.h"
#include "SPI_Interface.h"
#include "String_lib.h"
#include "RFID2/SPI.h"
/*---------------------------------------------------------- Private variables ---------------------------------------------------------*/

TIM_HandleTypeDef htim2;

// UART_HandleTypeDef huart1;
/* ----------------------------------------------------- Private App function prototypes -----------------------------------------------*/

void SystemClock_Config(void);
static void MX_TIM1_Init(void);

void ESP32_Connect_To_Wifi();
void ESP32_SendCommand(u8 *cmd);

/* ------------------------------------------------------- Global Variable Definitions ------------------------------------- -----------*/
u8 cursor = 1;
u8 key = 0;
f32 Weight;
u8 masterData = 0, SlaveData = 1;
u8 string[100];
u8 ReceivedData[20];
u8 x = 0;
u8 ssid[] = "Ahmed Hassan";
u8 password[] = "ahmed1234";
u8 mode[] = "1";
u8 Buffer[10];

u8 RFID[4];
void SysInit()
{
	HAL_Init();
	SystemClock_Config();
	//	RCC_void_System_Clock_Init(RCC_PLL, RCC_PLL_IN_HSE_DIV_2, PLL_CLOCK_MULTIPLE_BY_9);
	//	RCC_void_System_Clock_Init(RCC_PLL, RCC_PLL_IN_HSE_DIV_2, PLL_CLOCK_MULTIPLE_BY_9, LATENCY_2, AHB_PRESCALER_1, APB1_PRESCALER_2, APB2_PRESCALER_1);
	MX_TIM1_Init();
	HAL_TIM_Base_Start(&htim2);

	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOA_EN);
	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOC_EN);
	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOB_EN);
	GPIO_void_Initializtion();
	delay_init();
	GLCD_ST7920_init();

	USART_void_Initializtion(USART_1, USART_MODE_TX_RX, USART_PARITY_NONE, USART_PARITY_NONE, USART_WORDLENGTH_8_BITS, 115200);
//	SPI_void_Initialization(SPI_2, SPI_MODE_MASTER, SPI_DIRECTION_2LINES, SPI_DATAFORMAT_8_BIT, SPI_CPOL_HIGH, SPI_CPHA_FIRST_EDGE, PRESCALER_16, SPI_NSS_SOFT);
//	SPI2_Init();
SPI_Init(SPI_2);
	MFRC522_Init();

	MFRC522_DumpVersionToSerial();
	u8 result = MFRC522_PerformSelfTest();
	if (result)
	{
		GLCD_ST7920_SendString(1, 6, (u8*) "OK");
	}
	else
	{
		GLCD_ST7920_SendString(1, 0, (u8*) "Detect or Unknown");
	}

}

void System_Runnable()
{
	if (MFRC522_Check(RFID))
	{
		u8 data[20];
		GLCD_ST7920_SendString(2, 0, (u8*) "RFID Code is");
		sprintf(data, "%X %X %X %X", RFID[0], RFID[1], RFID[2], RFID[3]);
		GLCD_ST7920_SendString(3, 0, data);
	}
	//	GLCD_ST7920_SendString(1, 0, (u8*)"Buffer:");
	//	intoString(weight_KG, Buffer);
	//	GLCD_ST7920_SendString(1, 4, (u8*)"    ");
	//	GLCD_ST7920_SendString(1, 4, (u8*)Buffer);

	//	USART_Transmit_String(USART_1, Buffer,'\0');
	//	USART_void_Transmit_Byte(USART_1, '=');
	//	memset(Buffer,0,sizeof(Buffer));
	//	memorySet(Buffer,0 , sizeof(Buffer));
	//	GLCD_ST7920_SendString(3, 2, (u8*)"  ");
}

// void SysInit()
//{
//	HAL_Init();
//	SystemClock_Config();
////	RCC_void_System_Clock_Init(RCC_PLL, RCC_PLL_IN_HSE_DIV_2, PLL_CLOCK_MULTIPLE_BY_9);
////	RCC_void_System_Clock_Init(RCC_PLL, RCC_PLL_IN_HSE_DIV_2, PLL_CLOCK_MULTIPLE_BY_9, LATENCY_2, AHB_PRESCALER_1, APB1_PRESCALER_2, APB2_PRESCALER_1);
//
//	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOA_EN);
//	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOC_EN);
//	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOB_EN);
//	GPIO_void_Initializtion();
//	MX_TIM1_Init();
//	HAL_TIM_Base_Start(&htim2);
//
////	USART_void_Initializtion(USART_1, USART_MODE_TX_RX, USART_PARITY_NONE, USART_PARITY_NONE, USART_WORDLENGTH_8_BITS, 115200);
//
//	SPI_void_Initialization(SPI_2, SPI_MODE_MASTER, SPI_DIRECTION_2LINES,
//			SPI_DATAFORMAT_8_BIT, SPI_CPOL_HIGH, SPI_CPHA_FIRST_EDGE,
//			PRESCALER_32, SPI_NSS_SOFT);
//
//	LCD_Init();
////	KEYPAD_init();
//	delay_init();
//	GLCD_ST7920_init();
//	LCD_Goto_WriteString(1, 1, (u8*) "Master");
//	GLCD_ST7920_SendString(0, 0, (u8*) "Mohammed Khalaf");
//
////	SPI_u8_Send_Receive_Byte(SPI_2, 'A');
////	HX711_Calibrate();
////	USART_Transmit_String(USART_1, (u8*) "KHALAF", '\0');
////	LCD_Goto_WriteString(1, 1, (u8*) "Master");
//
////	GLCD_ST7920_SendString(0, 0, (u8*) "Welcome");
////	SPI_sendString(SPI_2, (u8*)"Mohammed");
//
//
//
//
//}

// void SysInit()
//{
//	HAL_Init();
//	SystemClock_Config();
//	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOA_EN);
//	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOB_EN);
//	RCC_void_Enable_Clock(RCC_APB2ENR, APB2_GPIOC_EN);
//	MX_TIM1_Init();
//	HAL_TIM_Base_Start(&htim2);
//	GPIO_void_Initializtion();
//	delay_init();
//	GLCD_ST7920_init();
//
//	// Initialize USART
//	USART_void_Initializtion(USART_1, USART_MODE_TX_RX, USART_PARITY_NONE,
//			USART_STOPBITS_1, USART_WORDLENGTH_8_BITS, 9600);
//	USART_void_Initializtion(USART_3, USART_MODE_TX_RX, USART_PARITY_NONE,
//			USART_STOPBITS_1, USART_WORDLENGTH_8_BITS, 9600);
//	USART_void_Initializtion(USART_2, USART_MODE_TX_RX, USART_PARITY_NONE,
//			USART_STOPBITS_1, USART_WORDLENGTH_8_BITS, 9600);
//
//	// Display welcome message
//	GLCD_ST7920_SendString(0, 0, (u8*) "Initializing...");
//	delay_ms(1000);
//
//	// Send an AT command and display response
////    ESP32_SendCommand((u8*)"AT");
//	ESP32_Connect_To_Wifi();
//	delay_ms(2000);
//	GLCD_ST7920_Clear();
//	GLCD_ST7920_SendString(0, 0, (u8*) "Welcome...");
//}

// void System_Runnable()
//{
////	Weight = HX711_WeightRead();
////	if (Weight < 0)
////	{
////		Weight = 0;
////	}
////
////	GLCD_ST7920_WriteNumber(3, 5, Weight, 3);
////	f32 weight_KG = Weight / 1000.0;
////	GLCD_ST7920_WriteFloatNumber(3, 0, weight_KG, 2, 3);
//	masterData = SPI_u8_Send_Receive_Byte(SPI_2, SlaveData++);
////	SPI_void_Write_Data(SPI_2, SlaveData++);
////	SPI_void_Write_Data(SPI_2, x++);
////	SPI_sendString(SPI_2, (u8*)"Mohammed");
//	LCD_Goto_WriteNumber(2, 1, masterData);
//	LCD_Goto_WriteNumber(1, 10, x++);
////	key = KEYPAD_GetKey();
//
////	if (key != NO_KEY)
////	{
////		LCD_Goto_Writeu8acter(1, cursor++, key);
////		if (cursor == 17)
////			cursor = 1;
////		if (key == '1')
////		{
////			GPIO_void_Toggle_Pin(PINC13);
////		}
////		else if (key == '2')
////		{
////			GPIO_void_Toggle_Pin(PINC14);
////		}
////		else if (key == '3')
////		{
////			GPIO_void_Toggle_Pin(PINC15);
////		}
////	}
////	GLCD_ST7920_WriteNumber(3, 0, x++, 2);
////	USART_Transmit_String(USART_3, (u8*) "Welcome from STM32", '\n');
//	HAL_Delay(1000);
//////	USART_void_Receive_Byte(USART_3);
//////	USART_void_Transmit_Byte(USART_3, 'M');
////	USART_ReceiveString(USART_3, ReceivedData, '\n', 20);
////	GLCD_ST7920_SendString(1, 0, 	ReceivedData);
//
//}

//void ESP32_SendCommand(u8 *cmd)
//{
//	u8 response[100];					   // Buffer for the response
//	memset(response, 0, sizeof(response)); // Clear the buffer
//
//	USART_Transmit_String(USART_1, cmd, '\0');
//	USART_Transmit_String(USART_1, (u8 *)"\r\n", '\0');
//
//	// Receive the response in a non-blocking way
//	USART_ReceiveString(USART_1, (u8 *)response, '\r', sizeof(response) - 1);
//
//	// Display response on the GLCD starting from row 1, column 0
//	GLCD_ST7920_SendString(1, 0, (u8 *)response);
//}

//void ESP32_Connect_To_Wifi()
//{
//	u8 wifimode_cmd[20]; // Buffer to hold the mode command
//	u8 wifi_cmd[100];	 // Buffer to hold the complete Wi-Fi connection command
//
//	// Form the Wi-Fi mode command
//	strcpy((u8 *)wifimode_cmd, (u8 *)"AT+CWMODE=");
//	strcat((u8 *)wifimode_cmd, (u8 *)mode);
//
//	// Send the Wi-Fi mode command
//	ESP32_SendCommand(wifimode_cmd);
//	delay_ms(1000); // Wait for the command to be processed
//
//	// Form the Wi-Fi connection command
//	strcpy((u8 *)wifi_cmd, (u8 *)"AT+CWJAP=\"");
//	strcat((u8 *)wifi_cmd, (u8 *)ssid);
//	strcat((u8 *)wifi_cmd, (u8 *)"\",\"");
//	strcat((u8 *)wifi_cmd, (u8 *)password);
//	strcat((u8 *)wifi_cmd, (u8 *)"\"");
//
//	// Send the Wi-Fi connection command
//	ESP32_SendCommand(wifi_cmd);
//	delay_ms(3000); // Wait longer for the connection to be established
//}

/* -------------------------- Declaration of Private App Functions ---------------------------------- */
void SystemClock_Config(void)
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
		Error_Handler();
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
		Error_Handler();
	}
}

static void MX_TIM1_Init(void)
{
	TIM_ClockConfigTypeDef sClockSourceConfig =
	{ 0 };
	TIM_MasterConfigTypeDef sMasterConfig =
	{ 0 };

	htim2.Instance = TIM1;
	htim2.Init.Prescaler = 72 - 1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 0xffff - 1;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.RepetitionCounter = 0;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

// static void MX_USART1_UART_Init(void) {
//
//	/* USER CODE BEGIN USART1_Init 0 */
//
//	/* USER CODE END USART1_Init 0 */
//
//	/* USER CODE BEGIN USART1_Init 1 */
//
//	/* USER CODE END USART1_Init 1 */
//	huart1.Instance = USART1;
//	huart1.Init.BaudRate = 115200;
//	huart1.Init.WordLength = UART_WORDLENGTH_8B;
//	huart1.Init.StopBits = UART_STOPBITS_1;
//	huart1.Init.Parity = UART_PARITY_NONE;
//	huart1.Init.Mode = UART_MODE_TX_RX;
//	huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
//	huart1.Init.OverSampling = UART_OVERSAMPLING_16;
//	if (HAL_UART_Init(&huart1) != HAL_OK) {
//		Error_Handler();
//	}
//	/* USER CODE BEGIN USART1_Init 2 */
//
//	/* USER CODE END USART1_Init 2 */
//
// }
// static void MX_GPIO_Init(void)
//{
//	GPIO_InitTypeDef GPIO_InitStruct =
//	{ 0 };
//	/* USER CODE BEGIN MX_GPIO_Init_1 */
//	/* USER CODE END MX_GPIO_Init_1 */
//
//	/* GPIO Ports Clock Enable */
//	__HAL_RCC_GPIOD_CLK_ENABLE();
//	__HAL_RCC_GPIOA_CLK_ENABLE();
//	__HAL_RCC_GPIOB_CLK_ENABLE();
//
//	/*Configure GPIO pin Output Level */
//	HAL_GPIO_WritePin(GPIOB,
//	GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7 | GPIO_PIN_8,
//			GPIO_PIN_RESET);
//
//	/*Configure GPIO pins : PB3 PB4 PB5 PB6
//	 PB7 PB8 */
//	GPIO_InitStruct.Pin = GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6
//			| GPIO_PIN_7 | GPIO_PIN_8;
//	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//	GPIO_InitStruct.Pull = GPIO_NOPULL;
//	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
//
//	/* USER CODE BEGIN MX_GPIO_Init_2 */
//	/* USER CODE END MX_GPIO_Init_2 */
// }

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
//// void UART_SendCommand(const u8 *cmd)
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

/*
* Al-Ahram.c
*
* Created: 05/07/2024 23:21:09
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "DIO_interface.h"
#include "Utils.h"
#include "MemoryMap.h"
#include "DIO_interface.h"
#include "GLCD_ST7920.h"
#include "HX711_Load_Cell.h"
#include "HX711_Config.h"
#include "Scale Configurations.h"
#include "Ex_int.h"
#include "LCD_Private.h"
#include "SPI.h"
#include "UART.h"
#include "UART_Services.h"
#include "Timers.h"

#include "Al-Ahram.h"
#include "App_Consideration.h"
#include "App_Services.h"
#include <avr/io.h>
/************************************************************************/
/*				Global Variables                                        */
/************************************************************************/
u8 exitFlag = 1;
//u16 Holded_Weight = 0;
u8 buffer1[16];
u8 buffer2[16];
u8 buffer3[16];
u8 decimalPlaces = 3;

f32 weight;
f32 avgSpecies= SPEC_AVG;
/************************************************************************/
/*	Global Variables Used in Runnable System                            */
/************************************************************************/
u16 normalCounts = 0;
u16 strangeCounts = 0;
u16 totalCounts = 0;
u16 staticNormalCounts = 0;

/************************************************************************/
/*								 Flags                                  */
/************************************************************************/

u8 speciesNum = 0;
u8 i = 0;
u8 data[20];
u8 dataToSend[30];


/************************************************************************/
/*                                                                      */
/************************************************************************/

u8 flagNormalStaticCounts = 0 , flagNormalDynamicCounts;
u16 noramlDynamicCounts = 0;
u16 noramlStaticCounts = 0;
u16 strangeSpecCount = 0;
static volatile f32 stableWeight = 0.0;

static volatile u16 previousWeight = 0;
#define F_CPU 16000000UL
#include <util/delay.h>

void setup()
{
	DIO_init();
	init_pins();
	//SPI_initMaster();
	GLCD_ST7920_init();
	DIO_initPin1(HX711_SCK_PIN, OUTPUT);
	EXI_init();
	EXI_Enable(EX_INT0);
	UART_Init(115200 , UART0);
	//
	ENABLE_GLOBAL_INTERRUPT();
	TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_64);
	TCNT0 = 156;    // Initialize counter to 0
	TIMER0_OV_InterruptEnable();  // Enable Timer0 overflow interrupt
	
	HX711_Calibrate();

}

void systemRunnable(void) {
	
	weight = HX711_WeightRead();
	if (weight < 0)
	{weight = 0;}
	
	normalCounts = detectSpecies(weight , &strangeCounts);
	f32 stableWeight = getStableWeight(weight , &staticNormalCounts);
	totalCounts = normalCounts + strangeCounts;
	
	GLCD_printApp(stableWeight , normalCounts ,strangeCounts, totalCounts);
		
	//	transmitDataToESP32(normalCounts , strangeCounts , totalCounts , buffer1 , buffer2 , buffer3);
	//sendDataToESP32(normalCounts , strangeCounts , totalCounts);
	//Hold Value Using EXTI INT0
	// 	while(!exitFlag)
	// 	{
	// 		//Holded_Weight = weight_KG;
	// 		//GLCD_ST7920_SendString(3, 0, (u8*)"Hold Val: ");
	// 		GLCD_ST7920_WriteNumber(3,6,weight_KG);
	// 		exitFlag = 1;
	// 	}
	
	}

void GLCD_printApp(f32 weight , u16 normal_Counts , u16 strange_Counts , u16 total_Counts)
{
	GLCD_ST7920_SendString(0, 0, (u8*)"NormalSpec= ");
	GLCD_ST7920_WriteNumber(0, 6, normal_Counts);

	GLCD_ST7920_SendString(1, 0, (u8*)"Strange = ");
	GLCD_ST7920_WriteNumber(1, 6, strange_Counts);
	//	GLCD_ST7920_SendString(2,0,(u8*)"Total = ");
	GLCD_ST7920_WriteNumber(2,6,total_Counts);
	//GLCD_ST7920_WriteNumber(2,6,staticNormalCounts);
	GLCD_ST7920_WriteNumber(3,5,weight);
	f32 weight_KG = weight / 1000.0;
	GLCD_ST7920_WriteFloatNumber(3,0,weight_KG , 2);
	
}

f32 getStableWeight(f32 currentWeight , u16 *pStaticCounts) {
	static f32 previousWeight = 0.0;   // Static variable to store the previous weight
	static u16 stableCount = 0;        // Counter to detect stable weight
	static f32 stableWeight = 0.0;     // Holds the last stable weight

	// Check if the weight change is within the stability threshold
	if (get_AbsoluteValue(currentWeight - previousWeight) <= STATIC_WEIGHT_THRESHOLD) {
		stableCount++;  // Increment stable count if weight change is within threshold
		GLCD_ST7920_SendString(2,0,(u8*)"Stable");
		// If stable count reaches the required threshold
		if (stableCount >= STABLE_COUNT_THRESHOLD) {
			stableWeight = currentWeight;  // Update stable weight
			stableCount = STABLE_COUNT_THRESHOLD;  // Keep stable count at max to prevent overflow
		}
		} else {
		stableCount = 0;  // Reset stable count if weight change is significant
		GLCD_ST7920_SendString(2,0,(u8*)"       ");
	}

	previousWeight = currentWeight;  // Update the previous weight after processing

	return stableWeight;  // Return the last stable weight
}

u16 detectSpecies(f32 currentWeight , u16 *pStrangeCount)
{
	u16 strangeSpecCount = 0;
	u16 normalCounts = 0;
	static u16 TotalnormalCounts = 0;
	static f32 previousWeight = 0.0; // Static variable to store the previous weight
	static u16 staticWeightCounter = 0; // Counter to detect static weight

	//noramlStaticCounts = currentWeight / SPEC_AVG;
	//avgSpecies = currentWeight / noramlDynamicCounts;
	previousWeight = currentWeight;
	while (currentWeight >= (avgSpecies + SPEC_VARIANCE ) || currentWeight >= (avgSpecies - SPEC_VARIANCE))
	{
		if ((currentWeight >= (avgSpecies + STRANGE_VARIANCE_0)) && (currentWeight <= (avgSpecies + STRANGE_VARIANCE_1)))
		{
			strangeSpecCount++;
		}
		else if (currentWeight >= (avgSpecies + SPEC_AVG) || currentWeight >= (avgSpecies - SPEC_VARIANCE))
		{
			//			/GLCD_ST7920_WriteChar(2,3,'a');
			noramlDynamicCounts++;
			normalCounts++;
		}

		currentWeight = currentWeight - avgSpecies;
	}
	
	//  	if (normalCounts > TotalnormalCounts)
	//  	{
	//  		TotalnormalCounts = normalCounts;
	// 	}
	//
	//	*pStaticCounts = TotalnormalCounts;
	*pStrangeCount = strangeSpecCount;
	return normalCounts;
}

/*
u16 detectSpecies(f32 currentWeight, u16 *pStrangeCount, u16* pStaticCounts, u16 *pNewSpecies) {

u16 strangeSpecCount = 0;
u16 normalCounts = 0;
static u16 TotalnormalStaticCounts = 0;

static u16 staticWeightCounter = 0; // Counter to detect static weight
const f32 WEIGHT_CHANGE_THRESHOLD = 10.0; // Define a threshold for weight change

flagNormalStaticCounts = 0;
flagNormalDynamicCounts = 0;
// Check if the weight change is significant
if (fabs(currentWeight - previousWeight) > WEIGHT_CHANGE_THRESHOLD) {
while (currentWeight >= (avgSpecies + SPEC_VARIANCE) || currentWeight >= (avgSpecies - SPEC_VARIANCE)) {
if ((currentWeight >= (avgSpecies + STRANGE_VARIANCE_0)) && (currentWeight <= (avgSpecies + STRANGE_VARIANCE_1))) {
strangeSpecCount++;
} else if (currentWeight >= (avgSpecies + SPEC_AVG) || currentWeight >= (avgSpecies - SPEC_VARIANCE)) {
noramlDynamicCounts++;
normalCounts++;
flagNormalDynamicCounts = 1;

GLCD_ST7920_WriteChar(3,4,'a');
}
currentWeight = currentWeight - avgSpecies;
}
previousWeight = currentWeight; // Update previous weight only if a significant change is detected
}
else
{
GLCD_ST7920_WriteChar(2,4,'a');
flagNormalStaticCounts = 1;
}

// 	// Update total normal species count
// 	if (flagNormalDynamicCounts && flagNormalStaticCounts==0)
// 	{
// 		TotalnormalStaticCounts++;
// 		*pNewSpecies = noramlDynamicCounts; // Store the number of newly added species
// 	}
// 	else
// 	{
// 		*pNewSpecies = 0; // No new species detected
// 	}

if (TotalnormalStaticCounts < noramlDynamicCounts)
{
TotalnormalStaticCounts = noramlDynamicCounts;
*pNewSpecies = noramlDynamicCounts; // Store the number of newly added species
}
else
{
*pNewSpecies = 0; // No new species detected

}
// 	if (normalCounts > 0)
// 	{
// 		TotalnormalStaticCounts = TotalnormalStaticCounts + normalCounts;
// 	}

*pStaticCounts = TotalnormalStaticCounts;
*pStrangeCount = strangeSpecCount;
return normalCounts;
}
*/

void sendDataToESP32(u16 Normal, u16 Strange, u16 TotalCounts)
{
	sprintf((u8*)data, (u8*)"%u,%u,%u   ", Normal, Strange, TotalCounts);
	// Debug print to see the data being sent
	GLCD_ST7920_SendString(2, 0, (u8*)data);
}

ISR(INT0_vect)				  // Works on Falling Edge   // Don't Forget Push button is INPULL
{
	//sei(); // AVR not support Interrupt Nesting. But we can do it by SW that sei Give this interrupt the ability to be cut by another interrupt
	exitFlag = 0;
}

// Timer0 overflow interrupt service routine
ISR(TIMER0_OVF_vect) {
	static u16 overflowCount = 0;
	overflowCount++;
	
	if (overflowCount >= 976) {  // Check if 1 second has passed
		DIO_TogglePin(Toggle_LED); // Toggle the LED
		//UART_TransmitString(data ,'\n', UART0);
		overflowCount = 0;  // Reset the overflow count
	}
}

















void transmitDataToESP32(u16 Normal , u16 Strange , u16 TotalCounts , u8* Buffer1, u8* Buffer2, u8* Buffer3)
{
	intoString(Normal    , Buffer1); // Convert the float to a string
	intoString(Strange     , Buffer2); // Convert the float to a string
	intoString(TotalCounts, Buffer3); // Convert the float to a string
	
	// Clear the dataToSend buffer
	memset(dataToSend, 0, sizeof(dataToSend));

	// Concatenate the strings with commas
	stringConcat(dataToSend, Buffer1, sizeof(dataToSend));
	appendChar(dataToSend, ',', sizeof(dataToSend));
	stringConcat(dataToSend, Buffer2, sizeof(dataToSend));
	appendChar(dataToSend, ',', sizeof(dataToSend));
	stringConcat(dataToSend, Buffer3, sizeof(dataToSend));
	appendChar(dataToSend, '\0', sizeof(dataToSend));

	// Debug print to see the data being sent
	GLCD_ST7920_SendString(1, 0, (u8*)"Sending:");
	GLCD_ST7920_SendString(2, 0, dataToSend);
	_delay_ms(500);  // Delay to ensure message is displayed

	// Transmit the data over UART
	//UART_TransmitString(dataToSend, '\n', UART0);

	// Small delay to ensure the UART buffer is flushed
	_delay_ms(100);

}
// u16 normalCountSpecies(f32 currentWeight)
// {
// 	u16 Counts = 0;
// 	Counts = currentWeight / (avgSpecies - SPEC_VARIANCE);
// 	//if ((((avgSpecies - SPEC_VARIANCE) <= currentWeight) || (currentWeight <= (avgSpecies + SPEC_VARIANCE))) || (currentWeight <= (avgSpecies + SPEC_VARIANCE)) || (currentWeight <= (avgSpecies - SPEC_VARIANCE)))
// 	while((currentWeight > (avgSpecies + SPEC_VARIANCE )) /*|| (currentWeight > (avgSpecies - SPEC_VARIANCE))*/)
// 	{
// 		tempCountAvg = currentWeight / (avgSpecies - SPEC_VARIANCE);
// 		Counts = Counts + 1;
// 		currentWeight = currentWeight - avgSpecies;
//
// 		if (currentWeight >= (avgSpecies + STRANGE_VARIANCE_0) && currentWeight <= (avgSpecies + STRANGE_VARIANCE_1))
// 		{
// 			Counts = Counts - 1;
// 		}
//
//
// 	}
// 	return Counts;
// }

// u16 detectStrangeSpecies(f32 currentWeight)
// {
// 	u16 strangeSpecCount = 0;
// 	//weight = HX711_WeightRead();
// 	while(currentWeight >= (avgSpecies + STRANGE_VARIANCE_1) || currentWeight >= (avgSpecies + STRANGE_VARIANCE_0))
// 	{
// 		if ((currentWeight >= (avgSpecies + STRANGE_VARIANCE_0)) && (currentWeight <= (avgSpecies + STRANGE_VARIANCE_1)))
// 		{
// 			strangeSpecCount = strangeSpecCount + 1;
// 		}
// 		currentWeight = currentWeight - (avgSpecies + SPEC_VARIANCE);
// 	}
// 	return strangeSpecCount;
// }
/*
* HX711_interface.c
*
* Created: 6/9/2024 1:50:32 PM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "Utils.h"
#include "MemoryMap.h"
#include "LCD_int.h"
#include "DIO_interface.h"
#include "HX711_interface.h"
#include "HX711_Config.h"

u8 GAIN;		                // Amplification factor
f64 OFFSET;	                // used for tare weight
f32 SCALE;	                    // used to return weight in grams, kg, ounces, whatever

#define F_CPU 16000000UL
#include <util/delay.h>
//Main


void HX711_init(HX711_Channel_t gain)
{

/************************************************************************/
//SCK_SET_OUTPUT;
//DATA_OUT_SET_INPUT;                                                    
/***********************************************************************/

// Set Data Pin HIGH:
DIO_initPin1(HX711_SCK_PIN , OUTPUT);
DIO_initPin1(HX711_DATA_PIN , INFREE);

HX711_set_gain(gain);
}

//new
// void HX711_init(void) {
// 	// Set PD_SCK as output
// 	DDRD |= (1 << HX711_SCK_PIN);
// 	// Set DOUT as input
// 	DDRD &= ~(1 << HX711_DATA_PIN);
// 	
// 	// Initialize PD_SCK to low
// 	CLEAR_BIT(PORTD, HX711_SCK_PIN);
// 	// Wait for HX711 to be ready
// 
// 	while (DIO_ReadPin1(HX711_DATA_PIN));
// }

u8 HX711_is_ready(void)
{
// 	u8 pinStatus = DIO_ReadPin1(HX711_DATA_PIN);
// 	return !pinStatus;
	return ( DIO_ReadPin1(HX711_DATA_PIN) == LOW );
}
// Main
// void HX711_set_gain(HX711_Channel_t gain)
// {
// 	switch(gain)
// 	{
// 		case GAIN_CHANNEL_A_128:
// 		GAIN = 1;
// 		break;
// 		case GAIN_CHANNEL_A_64:
// 		GAIN = 2;
// 		break;
// 		case GAIN_CHANNEL_B_32:
// 		GAIN = 3;
// 		break;
// 		case GAIN_DEFAULT:
// 		break;
// 	}
// 	/************************************************************************/
// // 	Pin PD_SCK input is used to power down the
// // 	HX711. When PD_SCK Input is low, chip is in
// // 	normal working mode														*/
// 	/************************************************************************/
// 	DIO_WritePin1(HX711_SCK_PIN , LOW);
// 	// OR:
// 	//CLEAR_BIT(HX711_PD_SCK_PORT , HX711_PD_SCK_PIN);
// 	
// 	HX711_read();
// }

void HX711_set_gain(HX711_Channel_t gain) {
	u8 i;

	switch (gain)
	{
		case GAIN_CHANNEL_A_128:
		i = 25;
		break;  // Channel A, Gain = 128
		case GAIN_CHANNEL_A_64:
		i = 27;
		break;  // Channel A, Gain = 64
		case GAIN_CHANNEL_B_32:
		i = 26;
		break;  // Channel B, Gain = 32
		default:
		return;         // Invalid gain, do nothing
	}

	// Set the gain by sending the appropriate number of pulses
	for (u8 j = 0; j < i; j++) {
		SET_BIT(PORTD, HX711_SCK_PIN);
		_delay_us(1);
		CLEAR_BIT(PORTD, HX711_SCK_PIN);
		_delay_us(1);
	}
}


//new fun
/*
u32 HX711_read(void) {
u32 counter = 0;
u8 i;

// Wait until DOUT goes low
while (DIO_ReadPin(PD, HX711_DOUT));

for (i = 0; i < 24; i++) {
// Pulse PD_SCK
SET_BIT(PORTD, HX711_SCK);
_delay_us(1);
counter = counter << 1;
CLEAR_BIT(PORTD, HX711_SCK);
_delay_us(1);
if (DIO_ReadPin(PD, HX711_DOUT))
{
counter++;
}
}

// Set the 25th pulse
SET_BIT(PORTD, HX711_SCK);
counter ^= 0x800000;
_delay_us(1);
CLEAR_BIT(PORTD, HX711_SCK);
_delay_us(1);

return counter;
}
*/
// Main funtion

u32 HX711_read(void)
{
	// wait for the chip to become ready
	while (!HX711_is_ready());
	u32 counter = 0;
	u8 pulse  = 0 ;

	DIO_WritePin1(HX711_DATA_PIN , HIGH);
	SET_BIT(HX711_DATA_OUT_PORT ,HX711_DATA_PIN);
	_delay_us(1);

	DIO_WritePin1(HX711_SCK_PIN , LOW);
	_delay_us(1);

	while(DIO_ReadPin1(HX711_DATA_PIN));
	for(pulse=0;pulse < 24 ; pulse++)
	{
		DIO_WritePin1(HX711_SCK_PIN , HIGH);
		_delay_us(1);
		counter = counter << 1;
		DIO_WritePin1(HX711_SCK_PIN , LOW);
		_delay_us(1);
		if(DIO_ReadPin1(HX711_DATA_PIN))
		counter++;
	}

	counter = counter >> 6;
	DIO_WritePin1(HX711_SCK_PIN , HIGH);
	_delay_us(1);
	DIO_WritePin1(HX711_SCK_PIN , LOW);
	_delay_us(1);
	counter ^= 0x800000;

	return counter;
}

u32 HX711_read_average(u8 times)
{
	u32 sum = 0 , avg = 0;
	for(u8 i = 0 ; i < times ; i++)
	{
		sum += HX711_read();
	}
	avg = sum / times;
	return avg;
}

f64 HX711_get_value()  // The same time in read avg function
{
	return HX711_read_average(1) - OFFSET;
}

f64 HX711_get_mean_value(u8 times) 
{
	return HX711_read_average(times) - OFFSET;
}

f32 HX711_get_units() 
{
	return HX711_get_value() / SCALE;
}

f32 HX711_get_mean_units(u8 times) 
{
	return HX711_get_mean_value(times) / SCALE;
}

void HX711_set_scale(f32 scale)
{
	SCALE = scale;
}

f32 HX711_get_scale(void)
{
	return SCALE;
}

void HX711_tare(u8 times)
{
	f64 sum = HX711_read_average(times);
	HX711_set_offset(sum);
}

void HX711_set_offset(f64 offset)
{
	OFFSET = offset;
}

f64 HX711_get_offset(void)
{
	return OFFSET;
}



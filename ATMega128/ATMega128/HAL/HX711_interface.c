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
#include "ADC_int.h"

u8 GAIN;		                // Amplification factor
f64 OFFSET;	                // used for tare weight
f32 SCALE;	                    // used to return weight in grams, kg, ounces, whatever

u32 tareValue = 0;
f32 scaleFactor = 0.0;

static volatile u8 pinStatus;

// Global variables for calibration
u32 sample = 0;
u32 count = 0;
f32 val = 0;

#define F_CPU 8000000UL
#include <util/delay.h>

void HX711_init()
{
	SET_BIT(HX711_SCK_DDR , HX711_SCK_PIN);			 // SCK_SET_OUTPUT;
	CLEAR_BIT(HX711_DATA_OUT_DDR , HX711_DATA_PIN);  // DATA_OUT_SET_INPUT;
	// Set Data Pin HIGH:
	DIO_WritePin1(HX711_DATA_PIN , HIGH);
	// The same
	//SET_BIT(HX711_DATA_OUT_PORT , HX711_DATA_PIN);

	// Set SCK PIN OUTPUT
	SET_BIT(HX711_SCK_DDR , HX711_SCK_PIN);
	//Power Down and Serial Clock Pin
	DIO_WritePin1(HX711_SCK_PIN , LOW);

	// Set DT pin as INPUT:
	CLEAR_BIT(HX711_DATA_OUT_DDR , HX711_DATA_PIN);
	
	HX711_SetGain(64);
	//HX711_set_gain(GAIN_CHANNEL_A_128);
	
}

//new

void HX711_init2(void) {
	// Set PD_SCK as output
	//DDRB |= (1 << HX711_SCK_PIN);
	SET_BIT(HX711_SCK_DDR, HX711_SCK_PIN);
	
	// Set DOUT as input
	//DDRB &= ~(1 << HX711_DATA_PIN);
	CLEAR_BIT(HX711_DATA_OUT_DDR , HX711_DATA_PIN);
	
	// Initialize PD_SCK to low
	CLEAR_BIT(HX711_SCK_PORT, HX711_SCK_PIN);
	
	// Wait for HX711 to be ready

	while (DIO_ReadPin1(HX711_DATA_PIN));
}


u8 HX711_is_ready(void)
{
	pinStatus = DIO_ReadPin1(HX711_DATA_PIN);
	// For Debugging
	//LCD_Goto_WriteNumber(1,10,pinStatus);
	return !pinStatus;
}
void HX711_set_gain(HX711_Channel_t gain)
{
	switch(gain)
	{
		case GAIN_CHANNEL_A_128:
		GAIN = 1;
		break;
		
		case GAIN_CHANNEL_A_64:
		GAIN = 3;
		break;
		
		case GAIN_CHANNEL_B_32:
		GAIN = 2;
		break;
		
		case GAIN_DEFAULT:
		break;
	}
	/************************************************************************/
	/*
	Pin PD_SCK input is used to power down the
	HX711. When PD_SCK Input is low, chip is in
	normal working mode														*/
	/************************************************************************/
	DIO_WritePin1(HX711_SCK_PIN , LOW);
	// OR:
	//CLEAR_BIT(HX711_PD_SCK_PORT , HX711_PD_SCK_PIN);
	
	HX711_Read();
}

void HX711_SetGain(u8 gain) {
	u8 i;

	switch (gain)
	{
		case 128:
		i = 25;
		break;  // Channel A, Gain = 128
		case 64:
		i = 27;
		break;  // Channel A, Gain = 64
		case 32:
		i = 26;
		break;  // Channel B, Gain = 32
		default:
		return;         // Invalid gain, do nothing
	}

	// Set the gain by sending the appropriate number of pulses
	for (u8 j = 0; j < i; j++) {
		SET_BIT(PORTD, HX711_SCK_PIN);
		_delay_us(100);
		CLEAR_BIT(PORTD, HX711_SCK_PIN);
		_delay_us(100);
	}
}


// Main function
u32 HX711_Read(void)
{
	// wait for the chip to become ready
	// For Debugging:
	//LCD_Goto_WriteNumber(1,16,HX711_is_ready());
	
	while (!HX711_is_ready());
	
	u32 count = 0;
	u8 pulse  = 0 ;

	DIO_WritePin1(HX711_DATA_PIN , HIGH);
	SET_BIT(HX711_DATA_OUT_PORT ,HX711_DATA_PIN);
	_delay_us(10);

	DIO_WritePin1(HX711_SCK_PIN , LOW);
	_delay_us(10);
	// For Debugging
	//LCD_Goto_WriteNumber(1,12,DIO_ReadPin1(HX711_DATA_PIN));
	while(DIO_ReadPin1(HX711_DATA_PIN));
	// For Debugging
	//LCD_Goto_WriteString(2,10,(u8*)"HI");
	for(pulse=0; pulse < 24 ; pulse++)
	{
		DIO_WritePin1(HX711_SCK_PIN , HIGH);
		_delay_us(10);
		count = count << 1;
		DIO_WritePin1(HX711_SCK_PIN , LOW);
		_delay_us(10);
		if(DIO_ReadPin1(HX711_DATA_PIN))
		count++;
	}

	count = count >> 6;
	DIO_WritePin1(HX711_SCK_PIN , HIGH);
	_delay_us(10);
	DIO_WritePin1(HX711_SCK_PIN , LOW);
	_delay_us(10);
	count ^= 0x800000;

	return count;
}

//new fun
u32 HX711_Read2(void) {
	u32 count = 0;
	u8 i;

	// Wait until DOUT goes low
	while (!DIO_ReadPin1(HX711_DATA_PIN));

	for (i = 0; i < 24; i++) {
		// Pulse PD_SCK
		SET_BIT(HX711_SCK_PORT, HX711_SCK_PIN);
		_delay_us(1);
		count = count << 1;
		CLEAR_BIT(HX711_SCK_PORT, HX711_SCK_PIN);
		_delay_us(1);
		if (DIO_ReadPin(HX711_DATA_OUT_PORT, HX711_DATA_PIN))
		{
			count++;
		}
	}

	// Set the 25th pulse
	SET_BIT(HX711_SCK_PORT, HX711_SCK_PIN);
	count ^= 0x800000;
	_delay_us(1);
	CLEAR_BIT(HX711_SCK_PORT, HX711_SCK_PIN);
	_delay_us(1);
	
	/*
	DIO_WritePin1(HX711_SCK_PIN , HIGH);
	_delay_us(1);
	DIO_WritePin1(HX711_SCK_PIN , LOW);
	_delay_us(1);
	*/
	return count;
}


u32 HX711_read_average(u8 times)
{
	u32 sum = 0 , avg = 0;
	for(u8 i = 0 ; i < times ; i++)
	{
		sum += HX711_Read();
	}
	avg = sum / times;
	return avg;
}

f64 HX711_get_value(u8 times)  // The same time in read avg function
{
	for (u8 i = 0; i < times; i++);
	return HX711_read_average(times) - OFFSET;
}

void HX711_set_scale(f32 scale)
{
	SCALE = scale;
}

f32 HX711_get_scale(void)
{
	return SCALE;
}

//Function to Tare (Set Zero) the Load Cell

void HX711_tare2(u8 times)
{
	tareValue = HX711_read_average(times);
	HX711_set_offset(tareValue);
}

void HX711_set_offset(f32 offset)
{
	OFFSET = offset;
}

f64 HX711_get_offset(void)
{
	return OFFSET;
}

void HX711_tare(void) 
{
	tareValue = HX711_Read();
} 

void HX711_Calibrate1(f32 knownWeight) {
	 u32 raw_Value_With_Known_Weight = HX711_Read();
	scaleFactor = knownWeight / (f32)(raw_Value_With_Known_Weight - tareValue);
	//For debugging 	
	//LCD_GoTo_WriteFloatNumber(1,8,scaleFactor,1);
}

f32 HX711_GetWeight(void) {
	u32 rawValue = HX711_Read();
	//For debugging 
	//LCD_Goto_WriteNumber(2,1,rawValue);
	//LCD_Goto_WriteNumber(2,9,tareValue);
	f32 weight = (rawValue - tareValue) * scaleFactor;
	//LCD_GoTo_WriteFloatNumber(2,10, (rawValue - tareValue),1);
	return weight;
}

void HX711_Calibrate2() {
	LCD_Clear();
	LCD_Goto_WriteString(1,1,(u8*)"Calibrating...");
	LCD_Goto_WriteString(2,1,(u8*)"Please Wait...");

	// Accumulate 100 readings to calculate the average no-load value
	sample = 0;
	for (int i = 0; i < 100; i++) 
	{
		count = HX711_Read();
		sample += count;
		_delay_ms(5); // Small delay between readings
	}
	sample /= 100;

	LCD_Clear();
	LCD_Goto_WriteString(1,1,(u8*)"Put 100g weight");
	count = 0;
	
	// Wait until the weight stabilizes
	while (count < 1000) {
		count = HX711_Read();
		count = sample - count;
		_delay_ms(1); // Small delay between readings
	}

	LCD_Clear();
	LCD_Goto_WriteString(1,1,(u8*)"Please Wait....");
	_delay_ms(2000);

	// Accumulate 100 readings with the known weight to calculate the scale factor
	val = 0;
	for (int i = 0; i < 100; i++) {
		count = HX711_Read();
		val += sample - count;
		_delay_ms(10); // Small delay between readings
	}
	val = val / 100.0;
	val = val / 100.0;  // Assuming the calibrating weight is 100 grams

	LCD_Clear();
}

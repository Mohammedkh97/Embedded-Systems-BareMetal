/*
* ADC_int.c
*
* Created: 11/8/2023 3:53:51 PM
*  Author: Mohammed Khalaf
*/

#include "stdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "ADC_int.h"
#include "LCD_int.h"
#define  F_CPU 8000000UL
#include <util/delay.h>

u8 BusyFlag;
void ADC_init(ADC_VREF_t vref,ADC_Prescaler_t scaler)
{
	
	/* Clock*/
	/*VREF*/
	switch(vref)
	{
		case VREF_AREF:
		CLEAR_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
		case VREF_VCC:
		SET_BIT(ADMUX,REFS0); 
		CLEAR_BIT(ADMUX,REFS1);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	
	ADCSRA&=0XF8;//0B11111000
	scaler&=0X07;//0B00000111     // To make sure the scaler has limited value 7
	ADCSRA|=scaler;
	//ADCSRA |= (scaler & 0x07); // Set new prescaler value  ((one line ))
	
	/* ADC enable*/
	SET_BIT(ADCSRA,ADEN);
	
	/*
	// Set the ADC prescaler
	ADCSRA &= 0xF8; // Clear prescaler bits (ADPS2:0)    //0B11111000
	ADCSRA |= (scaler & 0x07); // Set new prescaler value   //0B00000111

	// Enable the ADC
	SET_BIT(ADCSRA, ADEN);
	*/
	
}

// Set the ADC channel and gain
void ADC_SetChannel(ADC_Channel_t channel) {
	// Clear the older channel selection
	ADMUX &= 0xF0;
	// Set the new channel selection
	ADMUX |= (channel & 0x1F); // Use only lower 5 bits for MUX selection
}

u16 ADC_Read(ADC_Channel_t ch)
{
	// Select the ADC channel by setting the MUX bits in the ADMUX register
	ADMUX&=0XE0;   // Clear previous channel selection bits (MUX4:0) //0B11100000
	//ADMUX|=ch;     // Set the new channel selection bits
	ADMUX |= (ch & 0x1F);   //0b00001011   & 00011111 
	
	/* start conversion*/
	SET_BIT(ADCSRA,ADSC);
	
	/* wait until ADC end conversion*/  // until ADSC is cleared ADSC ==> 0
	//_delay_ms(1);  // 104 uSec 
	
	while(GET_BIT(ADCSRA,ADSC));// busy wait or blocking  while the condition is true you are in loop until is cleared when adc conversion time finished
	
/* read register*/
	//u16 adc = (ADCH<<8)|(ADCL) ;
	
	//return (ADCH<<8)|(ADCL);
	return ADC;
}


u16 ADC_ReadVolt(ADC_Channel_t ch)
{
	u16 adc=ADC_Read(ch);
	u16 volt=((u32)5000*adc)/1024;
	return volt;
	
}

void ADC_StartConversion(ADC_Channel_t ch )
{
	if (BusyFlag == 0)
	{
		ADMUX&=0XE0;//0B11100000
		ADMUX|=ch;
		/* start conversion*/
		SET_BIT(ADCSRA,ADSC);
		
		BusyFlag = 1;
	}

}
u16 ADC_GetRead()
{
	while(GET_BIT(ADCSRA,ADSC));// busy wait or blocking

	//return (ADCH<<8)|(ADCL);
	return ADC;
}

u8 ADC_GetReadPeriodic(u16* pData) //Polling
{
	if(GET_BIT(ADCSRA,ADSC))
	{
		return 0;
	}
	else
	{
		*pData = ADC;
		BusyFlag = 0;
		return 1;
	}
}


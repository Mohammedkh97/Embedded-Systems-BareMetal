/*
 * ADC_int.h
 *
 * Created: 11/8/2023 3:54:30 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef ADC_INT_H_
#define ADC_INT_H_

typedef enum
{
	VREF_AREF,
	VREF_VCC,
	VREF_256
}ADC_VREF_t;

typedef enum{
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
}ADC_Prescaler_t;

typedef enum{
    CH_0 = 0,  // Single-ended input channel 0
    CH_1,      // Single-ended input channel 1
    CH_2,      // Single-ended input channel 2
    CH_3,      // Single-ended input channel 3
    CH_4,      // Single-ended input channel 4
    CH_5,      // Single-ended input channel 5
    CH_6,      // Single-ended input channel 6
    CH_7,      // Single-ended input channel 7
    
    // Differential channels with gain
    DIFF_0_0_GAIN_10 = 0x08,
    DIFF_1_0_GAIN_10 = 0x09,
    DIFF_0_0_GAIN_200 = 0x0A,
    DIFF_1_0_GAIN_200 = 0x0B,
    DIFF_2_2_GAIN_10 = 0x0C,
    DIFF_3_2_GAIN_10 = 0x0D,
    DIFF_2_2_GAIN_200 = 0x0E,
    DIFF_3_2_GAIN_200 = 0x0F
}ADC_Channel_t;


void ADC_init(ADC_VREF_t vref,ADC_Prescaler_t scaler);
void ADC_SetChannel(ADC_Channel_t channel);
u16 ADC_Read(ADC_Channel_t ch);

u16 ADC_ReadVolt(ADC_Channel_t ch);

u16 ADC_PeriodicRead(u16* pData);


#endif /* ADC_INT_H_ */
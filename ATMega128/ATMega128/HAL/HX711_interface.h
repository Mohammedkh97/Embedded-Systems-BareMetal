/*
* HX711_interface.h
*
* Created: 6/9/2024 1:12:40 PM
*  Author: Mohammed Khalaf
*/


#ifndef HX711_INTERFACE_H_
#define HX711_INTERFACE_H_

typedef enum
{
	
	GAIN_CHANNEL_A_128,
	GAIN_CHANNEL_A_64,
	GAIN_CHANNEL_B_32,
	GAIN_DEFAULT

}HX711_Channel_t;


void HX711_init();
void HX711_init2();
u8 HX711_is_ready();
void HX711_set_gain(HX711_Channel_t gain);
u32 HX711_Read();
u32 HX711_Read2();
u32 HX711_read_average(u8 times);
f64 HX711_get_value(u8 times);
void HX711_set_scale(f32 scale);
f32 HX711_get_scale(void);
void HX711_set_offset(f32 offset);
f64 HX711_get_offset(void);		

void HX711_tare(void);
void HX711_Calibrate1(f32 knownWeight);
void HX711_Calibrate2();
f32 HX711_GetWeight(void);
void HX711_SetGain(u8 gain);



























/*
float HX711_get_units(u8 times);
void HX711_tare(u8 times);
void HX711_set_scale(f32 scale);
float HX711_get_scale();
void HX711_set_offset(s32 offset);
s32 HX711_get_offset();
void HX711_power_down();
void HX711_power_up();
u8 shiftIn(void);
*/


#endif /* HX711_INTERFACE_H_ */
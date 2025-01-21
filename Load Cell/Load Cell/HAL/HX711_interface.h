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


void HX711_init(HX711_Channel_t gain);
//void HX711_init(void);
u8 HX711_is_ready(void);
void HX711_set_gain(HX711_Channel_t gain);
void HX711_SetGain(u8 gain);
u32 HX711_read();
u32 HX711_read_average(u8 times);
f64 HX711_get_value();
void HX711_set_scale(f32 scale);
void HX711_tare(u8 times);
f64 HX711_get_mean_value(u8 times);
f32 HX711_get_units();
f32 HX711_get_mean_units(u8 times);
f32 HX711_get_scale(void);
void HX711_set_offset(f64 offset);
f64 HX711_get_offset(void);		
unsigned long Readcounter(void);



























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
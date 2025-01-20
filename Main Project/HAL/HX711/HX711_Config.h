/*
 * HX711_Config.h
 *
 * Created: 05/06/2024 1:52:30 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef HX711_CONFIG_H_
#define HX711_CONFIG_H_

// Define the pins for HX711
/*======================================================*/

#define HX711_DATA_PIN					PINB9 		                    // Serial Data Output Pin

#define HX711_SCK_PIN					PINB8                             // Power Down and Serial Clock Pin


#define RESET_CALIBRATION				PINB3
#define HOLD_BUTTON						PIND0

//Gain Definitions

#define HX711_GAIN_CHANNEL_A_128		128
#define HX711_GAIN_CHANNEL_A_64			64
#define HX711_GAIN_CHANNEL_B_32			32

#define HX711_GAIN_DEFAULT				HX711_GAIN_CHANNEL_A_128



#endif /* HX711_CONFIG_H_ */

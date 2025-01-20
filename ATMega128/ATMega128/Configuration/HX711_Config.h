/*
 * HX711_Config.h
 *
 * Created: 6/9/2024 1:52:30 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef HX711_CONFIG_H_
#define HX711_CONFIG_H_

/*======================================================*/
#define HX711_DATA_OUT_PORT				PORTB                           // Serial Data Output Port
#define HX711_DATA_OUT_DDR				DDRB                            // Serial Data Output DDR
#define HX711_DATA_PIN					PINB6 		                    // Serial Data Output Pin

#define HX711_SCK_PORT				PORTB	                        // Power Down and Serial Clock Input Port
#define HX711_SCK_DDR				DDRB                            // Power Down and Serial Clock DDR
#define HX711_SCK_PIN				PINB7                             // Power Down and Serial Clock Pin

//Gain Definitions
#define HX711_GAIN_CHANNEL_A_128		128
#define HX711_GAIN_CHANNEL_A_64			64
#define HX711_GAIN_CHANNEL_B_32			32
#define HX711_GAIN_DEFAULT				HX711_GAIN_CHANNEL_A_128

#endif /* HX711_CONFIG_H_ */
/*
 * App_Consideration.h
 *
 * Created: 8/6/2024 2:22:56 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef APP_CONSIDERATION_H_
#define APP_CONSIDERATION_H_

#define SPEC_VARIANCE			400
#define INITIAL_SPEC_AVG		1200
#define STRANGE_VARIANCE_0		600
#define STRANGE_VARIANCE_1		700
#define SPECIES_NUM				10
#define AVG_VARIANCE			250

//#define STATIC_WEIGHT_THRESHOLD 1980 // Threshold to detect static weight

#define STATIC_WEIGHT_THRESHOLD 300  	// Define a threshold for weight change to consider as stable
#define STABLE_COUNT_THRESHOLD 	3     	// Number of consecutive stable readings needed to consider the weight stable
#define NOISE_THRESHOLD			400.0	// Noise tolerance (ignore small fluctuations) / Adjust based on your sensor's sensitivity


#endif /* APP_CONSIDERATION_H_ */

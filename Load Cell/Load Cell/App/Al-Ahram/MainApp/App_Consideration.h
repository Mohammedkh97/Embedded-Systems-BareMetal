/*
 * App_Consideration.h
 *
 * Created: 8/6/2024 2:22:56 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef APP_CONSIDERATION_H_
#define APP_CONSIDERATION_H_
 
#define SPEC_VARIANCE			50
#define SPEC_AVG				2000.0
#define STRANGE_VARIANCE_0		300
#define STRANGE_VARIANCE_1		500
#define SPECIES_NUM				8

//#define STATIC_WEIGHT_THRESHOLD 1980 // Threshold to detect static weight
#define SOME_STATIC_THRESHOLD 2 // Number of consecutive readings to consider weight as static
#define STATIC_WEIGHT_THRESHOLD 100  // Define a threshold for weight change to consider as stable
#define STABLE_COUNT_THRESHOLD 2     // Number of consecutive stable readings needed to consider the weight stable

#endif /* APP_CONSIDERATION_H_ */
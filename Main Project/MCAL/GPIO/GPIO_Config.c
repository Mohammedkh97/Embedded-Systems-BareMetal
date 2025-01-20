/*
 * GPIO_Config.c
 *
 *  Created on: Sep 20, 2024
 * 	Author: Mohammed Khalaf
 */


#include "GPIO_Interface.h"

// Array to hold the initial configuration for each pin
const DIO_PinStatus_t InitializationPinsArray[TOTAL_PINS] = {
    // Port A Pins
	DIO_OUTPUT_PUSHPULL_10MHZ,          // PA0: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ,          // PA1: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ,   		// PA2: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ,          // PA3: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ,    		// PA4: Output push-pull 2 MHz
	DIO_OUTPUT_PUSHPULL_50MHZ,    		// PA5: Output push-pull 2 MHz
	DIO_OUTPUT_PUSHPULL_50MHZ,      	// PA6: Input with pull-up/down
	DIO_OUTPUT_PUSHPULL_50MHZ,    		// PA7: Output push-pull 2 MHz
	DIO_INPUT_PULL_UP_DOWN,          	// PA8: Input floating
	DIO_INPUT_PULL_UP_DOWN,      		// PA9: Input with pull-up/down
	DIO_OUTPUT_PUSHPULL_10MHZ,   			// PA10: Output push-pull 10 MHz (e.g., USART TX)
	DIO_INPUT_PULL_UP_DOWN,   			// PA11: Output push-pull 10 MHz
	DIO_OUTPUT_PUSHPULL_10MHZ,          // PA12: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ,   		// PA13: Output push-pull 50 MHz (e.g., SWDIO)
	DIO_OUTPUT_PUSHPULL_10MHZ,          		// PA14: Input floating (e.g., SWCLK)
	DIO_OUTPUT_PUSHPULL_10MHZ,          // PA15: Input floating

    // Port B Pins
	DIO_OUTPUT_PUSHPULL_50MHZ,          // PB0: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ,          // PB1: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ,          // PB2: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ,    // PB3: Output push-pull 2 MHz
	DIO_OUTPUT_PUSHPULL_10MHZ,    // PB4: Output push-pull 2 MHz
	DIO_INPUT_PULL_UP_DOWN,      // PB5: Input with pull-up/down
	DIO_INPUT_PULL_UP_DOWN,     // PB6: Alternate function push-pull 50 MHz (e.g., I2C)
	DIO_INPUT_PULL_UP_DOWN,     // PB7: Alternate function push-pull 50 MHz (e.g., I2C)
	DIO_OUTPUT_PUSHPULL_10MHZ,    // PB8: Output push-pull 2 MHz
	DIO_INPUT_FLOATING,      // PB9: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ,      // PB10: Input with pull-up/down
    DIO_OUTPUT_PUSHPULL_10MHZ,   // PB11: Output push-pull 10 MHz
	DIO_OUTPUT_PUSHPULL_10MHZ,   	 // PB12: Output push-pull 50 MHz 	SPI_2 NSS
    DIO_OUTPUT_PUSHPULL_2MHZ,   // PB13: Output push-pull 50 MHz 	SPI_2 SCK
	DIO_INPUT_PULL_UP_DOWN,   // PB14: Output push-pull 50 MHz	SPI_2 MISO
    DIO_OUTPUT_PUSHPULL_50MHZ,   // PB15: Output push-pull 50 MHz	SPI_2 MOSI

    // Port C Pins
    DIO_INPUT_FLOATING,          // PC0: Input floating
    DIO_INPUT_FLOATING,          // PC1: Input floating
    DIO_INPUT_FLOATING,          // PC2: Input floating
    DIO_INPUT_FLOATING,          // PC3: Input floating
    DIO_INPUT_FLOATING,          // PC4: Input floating
    DIO_INPUT_FLOATING,          // PC5: Input floating
    DIO_OUTPUT_PUSHPULL_2MHZ,    // PC6: Output push-pull 2 MHz
    DIO_OUTPUT_PUSHPULL_2MHZ,    // PC7: Output push-pull 2 MHz
    DIO_OUTPUT_PUSHPULL_2MHZ,    // PC8: Output push-pull 2 MHz
    DIO_OUTPUT_PUSHPULL_2MHZ,    // PC9: Output push-pull 2 MHz
    DIO_INPUT_FLOATING,          // PC10: Input floating
    DIO_INPUT_FLOATING,          // PC11: Input floating
    DIO_OUTPUT_PUSHPULL_10MHZ,   // PC12: Output push-pull 10 MHz
	DIO_OUTPUT_PUSHPULL_10MHZ,          // PC13: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ,   // PC14: Input floating
	DIO_OUTPUT_PUSHPULL_10MHZ           // PC15: Input floating
};

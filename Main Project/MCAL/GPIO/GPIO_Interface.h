/********************************************************************/
/* 	GPIO_Interface.h												*/
/*  Created on: Sep 20, 2024										*/
/*  Author: Mohammed Khalaf											*/
/********************************************************************/

#ifndef MCAL_GPIO_GPIO_INTERFACE_H_
#define MCAL_GPIO_GPIO_INTERFACE_H_

#include "stdTypes.h"

// Enums for GPIO ports

typedef enum
{
	PORTA,
	PORTB,
	PORTC
}DIO_Port_t;

// Enum for GPIO pin voltage level

typedef enum
{
    LOW = 0,   // Low voltage (0)
    HIGH       // High voltage (1)
} DIO_PinVoltage_t;


// Enums for GPIO pin status

typedef enum
{
	/***************   INPUT Mode definition   ******************/
    DIO_INPUT_ANALOG              = 0b0000,     /** @note: */
    DIO_INPUT_FLOATING            = 0b0100,     /** @note: */
    DIO_INPUT_PULL_UP_DOWN        = 0b1000,     /** @note: */

	/***************   OUTPUT Mode definition of Bits ******************/

	// For 2 MHz
    DIO_OUTPUT_PUSHPULL_2MHZ      = 0b0010,     /** @note: */
    DIO_OUTPUT_OPENDRAIN_2MHZ     = 0b0110,     /** @note: */
    DIO_AFIO_OPENDRAIN_2MHZ       = 0b1110,     /** @note: */
    DIO_AFIO_PUSHPULL_2MHZ        = 0b1010,     /** @note: */

	// For 10 MHz
    DIO_OUTPUT_PUSHPULL_10MHZ     = 0b0001,     /** @note: */
    DIO_OUTPUT_OPENDRAIN_10MHZ    = 0b0101,     /** @note: */
    DIO_AFIO_OPENDRAIN_10MHZ      = 0b1101,     /** @note: */
    DIO_AFIO_PUSHPULL_10MHZ       = 0b1001,     /** @note: */

	// For 50 MHz
    DIO_OUTPUT_PUSHPULL_50MHZ     = 0b0011,     /** @note: */
    DIO_OUTPUT_OPENDRAIN_50MHZ    = 0b0111,     /** @note: */
    DIO_AFIO_OPENDRAIN_50MHZ      = 0b1111,     /** @note: */
    DIO_AFIO_PUSHPULL_50MHZ       = 0b1011      /** @note: */

}DIO_PinStatus_t;

typedef enum
{
    // GPIO Port A Pins
    PINA0 = 0,  // PA0
    PINA1,      // PA1
    PINA2,      // PA2
    PINA3,      // PA3
    PINA4,      // PA4
    PINA5,      // PA5
    PINA6,      // PA6
    PINA7,      // PA7
    PINA8,      // PA8
    PINA9,      // PA9
    PINA10,     // PA10
    PINA11,     // PA11
    PINA12,     // PA12
    PINA13,     // PA13
    PINA14,     // PA14
    PINA15,     // PA15

    // GPIO Port B Pins
    PINB0,      // PB0
    PINB1,      // PB1
    PINB2,      // PB2
    PINB3,      // PB3
    PINB4,      // PB4
    PINB5,      // PB5
    PINB6,      // PB6
    PINB7,      // PB7
    PINB8,      // PB8
    PINB9,      // PB9
    PINB10,     // PB10
    PINB11,     // PB11
    PINB12,     // PB12
    PINB13,     // PB13
    PINB14,     // PB14
    PINB15,     // PB15

    // GPIO Port C Pins
    PINC0,      // PC0
    PINC1,      // PC1
    PINC2,      // PC2
    PINC3,      // PC3
    PINC4,      // PC4
    PINC5,      // PC5
    PINC6,      // PC6
    PINC7,      // PC7
    PINC8,      // PC8
    PINC9,      // PC9
    PINC10,     // PC10
    PINC11,     // PC11
    PINC12,     // PC12
    PINC13,     // PC13
    PINC14,     // PC14
    PINC15,     // PC15,

    TOTAL_PINS  // Total number of pins
} DIO_Pins_t;


/***********************************  FUNCTIONS PROTOTYPE ******************************/

void GPIO_void_Initializtion();
void GPIO_void_SetPinMode1(DIO_Pins_t Pin_Number , DIO_PinStatus_t status);
void GPIO_void_SetPinMode2(DIO_Port_t Port , DIO_Pins_t Pin_Number, DIO_PinStatus_t status);
void GPIO_void_Write_Pin_Method1(DIO_Pins_t Pin_Number ,DIO_PinVoltage_t volt);
void GPIO_void_Write_Pin_Method2(DIO_Port_t port , DIO_Pins_t Pin_Number ,DIO_PinVoltage_t volt);
void GPIO_void_Write_Pin_Method3(DIO_Pins_t Pin_Number, DIO_PinVoltage_t volt);

DIO_PinVoltage_t GPIO_DIO_PinVoltage_Read_Pin_Method1(DIO_Pins_t pin);
DIO_PinVoltage_t GPIO_DIO_PinVoltage_Read_Pin_Method2(DIO_Port_t port , u8 Pin_Number);

void GPIO_void_Toggle_Pin(DIO_Pins_t pin);
void GPIO_void_Write_Port(DIO_Port_t port, u8 value);
u32  GPIO_Read_Port(DIO_Port_t port);



#endif /* MCAL_GPIO_GPIO_INTERFACE_H_ */

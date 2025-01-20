/*
 * GPIO_Program.c
 *
 *  Created on: Sep 20, 2024
 * 	Author: Mohammed Khalaf
 */

#include "GPIO_MemoryMap.h"
#include "stdTypes.h"
#include "BitwiseOperations_LIB.h"
#include "GPIO_Interface.h"
#include "GPIO_Private.h"

void GPIO_void_Initializtion()
{
	u8 pinNumber;
	for (pinNumber = PINA0; pinNumber < TOTAL_PINS; ++pinNumber)
	{
		GPIO_void_SetPinMode1(pinNumber , InitializationPinsArray[pinNumber]);
	}

}

void GPIO_void_SetPinMode1(DIO_Pins_t Pin_Number, DIO_PinStatus_t status)

{
    DIO_Port_t port;
    u8 pin;

	port= Pin_Number / 16;  // Extract the port number (assuming 16 pins per port)
	pin= Pin_Number % 16;   // Extract the pin number (0-15)

    switch (port)
    {
        /*** PORT A ***/
        case PORTA:  // For Port A
            if (pin <= 7)
            {
                // For pins 0-7, use CRL
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOA->CRL, (pin * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOA->CRL, (pin * 4 + i)); // Set bits according to status
                    }
                }
            }
            else
            {
                // For pins 8-15, use CRH
                pin -= 8; // Adjust for CRH
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOA->CRH, (pin * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOA->CRH, (pin * 4 + i)); // Set bits according to status
                    }
                }
            }
            break;

        /*** PORT B ***/
        case PORTB:  // For Port B
            if (pin <= 7)
            {
                // For pins 0-7, use CRL
                for (u8 i = 0; i < 4; i++)
                {
                    CLEAR_BIT(GPIOB->CRL, (pin * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOB->CRL, (pin * 4 + i)); // Set bits according to status
                    }
                }
//                GPIOB->CRL &= ~(0xF << (pin * 4));             /* Clear the nibble  */
//                GPIOB->CRL |= (status << (pin * 4)); /* 4: because the shifted nibble */

            }
            else
            {
                // For pins 8-15, use CRH
                pin -= 8; // Adjust for CRH
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOB->CRH, (pin * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOB->CRH, (pin * 4 + i)); // Set bits according to status
                    }
                }
            }
            break;

        /*** PORT C ***/
        case PORTC:  // For Port C
            if (pin <= 7)
            {
                // For pins 0-7, use CRL
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOC->CRL, (pin * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOC->CRL, (pin * 4 + i)); // Set bits according to status
                    }
                }
            }
            else
            {
                // For pins 8-15, use CRH
                pin -= 8; // Adjust for CRH
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOC->CRH, (pin * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOC->CRH, (pin * 4 + i)); // Set bits according to status
                    }
                }
            }
            break;

        default:
            // Handle invalid port error
            break;
    }
}

void GPIO_void_SetPinMode2(DIO_Port_t Port, DIO_Pins_t Pin_Number, DIO_PinStatus_t status)
{
	Pin_Number = Pin_Number%16;

    switch (Port)
    {
        /*** PORT A ***/
        case PORTA:
            if (Pin_Number <= 7)
            {
                // For pins 0-7, we use CRL
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOA->CRL, (Pin_Number * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOA->CRL, (Pin_Number * 4 + i)); // Set bits according to status
                    }
                }
            }
            else if (Pin_Number > 7 && Pin_Number <= 15)
            {
                // For pins 8-15, we use CRH
                Pin_Number -= 8; // Adjust for CRH register
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOA->CRH, (Pin_Number * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOA->CRH, (Pin_Number * 4 + i)); // Set bits according to status
                    }
                }
            }
            break;

        /*** PORT B ***/
        case PORTB:
            if (Pin_Number <= 7)
            {
                // For pins 0-7, we use CRL
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOB->CRL, (Pin_Number * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOB->CRL, (Pin_Number * 4 + i)); // Set bits according to status
                    }
                }
            }
            else if (Pin_Number > 7 && Pin_Number <= 15)
            {
                // For pins 8-15, we use CRH
                Pin_Number -= 8; // Adjust for CRH register
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOB->CRH, (Pin_Number * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOB->CRH, (Pin_Number * 4 + i)); // Set bits according to status
                    }
                }
            }
            break;

        /*** PORT C ***/
        case PORTC:
            if (Pin_Number <= 7)
            {
                // For pins 0-7, we use CRL
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOC->CRL, (Pin_Number * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOC->CRL, (Pin_Number * 4 + i)); // Set bits according to status
                    }
                }
            }
            else if (Pin_Number > 7 && Pin_Number <= 15)
            {
                // For pins 8-15, we use CRH
                Pin_Number -= 8; // Adjust for CRH register
                for (u8 i = 0; i < 4; i++) {
                    CLEAR_BIT(GPIOC->CRH, (Pin_Number * 4 + i)); // Clear bits
                    if (status & (1 << i)) {
                        SET_BIT(GPIOC->CRH, (Pin_Number * 4 + i)); // Set bits according to status
                    }
                }
            }
            break;

        default:
            // Handle invalid port error
            break;
    }
}

void GPIO_void_Write_Pin_Method1(DIO_Pins_t Pin_Number, DIO_PinVoltage_t volt)
{
    DIO_Port_t port;
    u8 pin;

    port = (DIO_Port_t)Pin_Number / 16;  // Extract the port number (assuming 16 pins per port)
    pin  = Pin_Number % 16;   // Extract the pin number (0-15)

    if (volt == HIGH)
    {
        switch (port)
        {
            case PORTA:
                SET_BIT(GPIOA->ODR, pin);  // Set the corresponding pin in ODR for Port A
//                GPIOA->BSRR = (1<<Pin_Number);
                break;
            case PORTB:
                SET_BIT(GPIOB->ODR, pin);  // Set the corresponding pin in ODR for Port B
                break;
            case PORTC:
                SET_BIT(GPIOC->ODR, pin);  // Set the corresponding pin in ODR for Port C
                break;
            default:
                // Handle invalid port error (optional)
                break;
        }
    }
    else if (volt == LOW) // If voltage is LOW
    {
        switch (port)
        {
            case PORTA:
                CLEAR_BIT(GPIOA->ODR, pin);  // Clear the corresponding pin in ODR for Port A
                break;
            case PORTB:
                CLEAR_BIT(GPIOB->ODR, pin);  // Clear the corresponding pin in ODR for Port B
                break;
            case PORTC:
                CLEAR_BIT(GPIOC->ODR, pin);  // Clear the corresponding pin in ODR for Port C
                break;
            default:
                // Handle invalid port error (optional)
                break;
        }
    }
}

void GPIO_void_Write_Pin_Method2(DIO_Port_t port, DIO_Pins_t Pin_Number, DIO_PinVoltage_t volt)
{
	u8 pin_num;
	pin_num  = Pin_Number % 16;   // Extract the pin number (0-15)
    // Check if voltage is HIGH or LOW and handle accordingly
    if (volt == HIGH)
    {
        switch (port)
        {
            case PORTA:
                SET_BIT(GPIOA->ODR, pin_num);  // Set the corresponding pin in ODR for Port A
                break;
            case PORTB:
                SET_BIT(GPIOB->ODR, pin_num);  // Set the corresponding pin in ODR for Port B
                break;
            case PORTC:
                SET_BIT(GPIOC->ODR, pin_num);  // Set the corresponding pin in ODR for Port C
                break;
            default:
                // Handle invalid port error (optional)
                break;
        }
    }
    else if (volt == LOW)  // If voltage is LOW
    {
        switch (port)
        {
            case PORTA:
                CLEAR_BIT(GPIOA->ODR, pin_num);  // Clear the corresponding pin in ODR for Port A
                break;
            case PORTB:
                CLEAR_BIT(GPIOB->ODR, pin_num);  // Clear the corresponding pin in ODR for Port B
                break;
            case PORTC:
                CLEAR_BIT(GPIOC->ODR, pin_num);  // Clear the corresponding pin in ODR for Port C
                break;
            default:
                // Handle invalid port error (optional)
                break;
        }
    }
}

// Using BSRR Register:

void GPIO_void_Write_Pin_Method3(DIO_Pins_t Pin_Number, DIO_PinVoltage_t volt)
{
    DIO_Port_t port;
    u8 pin;

    port = (DIO_Port_t)Pin_Number / 16;  // Extract the port number (assuming 16 pins per port)
    pin  = Pin_Number % 16;   // Extract the pin number (0-15)

    if (volt == HIGH)
    {
        switch (port)
        {
            case PORTA:
                GPIO_Set_Pin(GPIOA, pin);  // Set the corresponding pin using macro
                break;
            case PORTB:
                GPIO_Set_Pin(GPIOB, pin);  // Set the corresponding pin using macro
                break;
            case PORTC:
                GPIO_Set_Pin(GPIOC, pin);  // Set the corresponding pin using macro
                break;
            default:
                // Handle invalid port error (optional)
                break;
        }
    }
    else if (volt == LOW) // If voltage is LOW
    {
        switch (port)
        {
            case PORTA:
                GPIO_Clear_Pin(GPIOA, pin);  // Clear the corresponding pin using macro
                break;
            case PORTB:
                GPIO_Clear_Pin(GPIOB, pin);  // Clear the corresponding pin using macro
                break;
            case PORTC:
                GPIO_Clear_Pin(GPIOC, pin);  // Clear the corresponding pin using macro
                break;
            default:
                // Handle invalid port error (optional)
                break;
        }
    }
}


DIO_PinVoltage_t GPIO_DIO_PinVoltage_Read_Pin_Method1(DIO_Pins_t pin)
{
    DIO_Port_t port;
    u8 Pin_Number;
    DIO_PinVoltage_t status = LOW;

    // Determine the port and pin number
    port = (DIO_Port_t)(pin / 16);
    Pin_Number = pin % 16;

    // Check the port and read the corresponding pin state
    switch (port)
    {
        case PORTA:
            status = GET_BIT(GPIOA->IDR, Pin_Number);  // Read from IDR for Port A
            break;
        case PORTB:
            status = GET_BIT(GPIOB->IDR, Pin_Number);  // Read from IDR for Port B
            break;
        case PORTC:
            status = GET_BIT(GPIOC->IDR, Pin_Number);  // Read from IDR for Port C
            break;
        default:
            // Handle invalid port error (optional)
            break;
    }

    return status;  // Return the read voltage level
}

DIO_PinVoltage_t GPIO_DIO_PinVoltage_Read_Pin_Method2(DIO_Port_t port, u8 Pin_Number)
{
    DIO_PinVoltage_t status = LOW;
	u8 pin_num;
	pin_num  = Pin_Number % 16;   // Extract the pin number (0-15)

    // Check the port and read the corresponding pin state
    switch (port) {
        case PORTA:
            status = GET_BIT(GPIOA->IDR, pin_num);  // Read from IDR for Port A
            break;
        case PORTB:
            status = GET_BIT(GPIOB->IDR, pin_num);  // Read from IDR for Port B
            break;
        case PORTC:
            status = GET_BIT(GPIOC->IDR, pin_num);  // Read from IDR for Port C
            break;
        default:
            // Handle invalid port error (optional)
            break;
    }

    return status;  // Return the read voltage level
}

void GPIO_void_Toggle_Pin(DIO_Pins_t pin)
{
    DIO_Port_t port;
    u8 pin_num;

    // Determine the port and pin number
    port = (DIO_Port_t)(pin / 16);  // Extract the port number (assuming 16 pins per port)
    pin_num = pin % 16;             // Extract the pin number (0-15)

    switch (port) {
        case PORTA:
            TOGGLE_BIT(GPIOA->ODR, pin_num); // Toggle the corresponding pin in ODR for Port A
            break;
        case PORTB:
            TOGGLE_BIT(GPIOB->ODR, pin_num); // Toggle the corresponding pin in ODR for Port B
            break;
        case PORTC:
            TOGGLE_BIT(GPIOC->ODR, pin_num); // Toggle the corresponding pin in ODR for Port C
            break;
        default:
            // Handle invalid port error (optional)
            break;
    }
}

void GPIO_void_Write_Port(DIO_Port_t port, u8 value)
{
    switch (port) {
        case PORTA:
            GPIOA->ODR = value; // Write the value to Port A output data register
            break;
        case PORTB:
            GPIOB->ODR = value; // Write the value to Port B output data register
            break;
        case PORTC:
            GPIOC->ODR = value; // Write the value to Port C output data register
            break;
        default:
            // Handle invalid port error (optional)
            break;
    }
}

u32 GPIO_Read_Port(DIO_Port_t port)
{
    u32 value = 0; // Variable to hold the read value

    switch (port) {
        case PORTA:
            value = GPIOA->IDR; // Read the input data register of Port A
            break;
        case PORTB:
            value = GPIOB->IDR; // Read the input data register of Port B
            break;
        case PORTC:
            value = GPIOC->IDR; // Read the input data register of Port C
            break;
        default:
            // Handle invalid port error (optional)
            break;
    }

    return value; // Return the read value
}

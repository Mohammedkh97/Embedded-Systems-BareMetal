/*
* DIO.c
*
* Created: 5/17/2023 12:54:34 AM
*  Author: Mohammed Khalaf
*/
#include "MemoryMap.h"
#include "stdTypes.h"
#include "DIO_interface.h"
#include "Utils.h" // MCAL needs Utils file
#include "DIO_private.h"
#include "DIO_Config.h"

void DIO_init()
{
	DIO_Pins_t i;
	for (i = PINA0 ; i < TOTAL_PINS ; i++)
	{
		DIO_initPin1(i , DIO_PinsStatusArr[i]);
	}
}
// To keep out of problems due to calling this function we can set it as static function
/*void DIO_initPin(DIO_Port_t port , u8 pin_num , DIO_PinStatus_t status)
{
switch(status)
{
case OUTPUT:
switch(port)
{
case PA:
SET_BIT(DDRA ,pin_num);
CLEAR_BIT(PORTA , pin_num);
break;
case PB:
SET_BIT(DDRB ,pin_num);
CLEAR_BIT(PORTB , pin_num);
break;
case PC:
SET_BIT(DDRD ,pin_num);
CLEAR_BIT(PORTD , pin_num);
break;
case PD:
SET_BIT(DDRD ,pin_num);
CLEAR_BIT(PORTD , pin_num);
break;
}
break;
case INFREE:
switch(port)
{
case PA:
CLEAR_BIT(DDRA ,pin_num);   // Zero on DDR to set it as input not output
CLEAR_BIT(PORTA , pin_num); // to off pull up resistor
break;
case PB:
CLEAR_BIT(DDRB ,pin_num);
CLEAR_BIT(PORTB , pin_num);
break;
case PC:
CLEAR_BIT(DDRD ,pin_num);
CLEAR_BIT(PORTD , pin_num);
break;
case PD:
CLEAR_BIT(DDRD ,pin_num);
CLEAR_BIT(PORTD , pin_num);
break;
}
break;

case INPULL:
switch(port)
{
case PA:
CLEAR_BIT(DDRA ,pin_num);
SET_BIT(PORTA , pin_num);
break;
case PB:
CLEAR_BIT(DDRB ,pin_num);
SET_BIT(PORTB , pin_num);
break;
case PC:
CLEAR_BIT(DDRD ,pin_num);
SET_BIT(PORTD , pin_num);
break;
case PD:
CLEAR_BIT(DDRD ,pin_num);
SET_BIT(PORTD , pin_num);
break;
}
break;
}
}*/

void DIO_WritePin(DIO_Port_t port , u8 pin_num,DIO_PinVoltage_t volt)
{
	if (volt == HIGH)
	{
		switch(port)
		{
			case PA:
			SET_BIT(PORTA , pin_num);
			break;
			case PB:
			SET_BIT(PORTB , pin_num);
			break;
			case PC:
			SET_BIT(PORTD , pin_num);
			break;
			case PD:
			SET_BIT(PORTD , pin_num);
			break;
			case PE:
			SET_BIT(PORTE , pin_num);
			break;
			case PF:
			SET_BIT(PORTF , pin_num);
			break;
			case PG:
			SET_BIT(PORTG , pin_num);
			break;
		}
	}
	else if (volt == LOW)
	{
		switch(port)
		{
			case PA:
			CLEAR_BIT(DDRA ,pin_num);
			break;
			case PB:
			CLEAR_BIT(DDRB ,pin_num);
			break;
			case PC:
			CLEAR_BIT(DDRD ,pin_num);
			break;
			case PD:
			CLEAR_BIT(DDRD ,pin_num);
			break;
			case PE:
			CLEAR_BIT(DDRE ,pin_num);
			break;
			case PF:
			CLEAR_BIT(DDRF ,pin_num);
			break;
			case PG:
			CLEAR_BIT(DDRG ,pin_num);
			break;
		}
	}
}

DIO_PinVoltage_t DIO_ReadPin(DIO_Port_t port , u8 pin_num)
{
	DIO_PinVoltage_t status = 0;
	
	switch(port)
	{
		case PA:
		status = GET_BIT(PINA , pin_num);
		break;
		case PB:
		status = GET_BIT(PINB , pin_num);
		break;
		case PC:
		status = GET_BIT(PINC , pin_num);
		break;
		case PD:
		status = GET_BIT(PIND , pin_num);
		break;
		case PE:
		status = GET_BIT(PINE , pin_num);
		break;
		case PF:
		status = GET_BIT(PINE , pin_num);
		break;
		case PG:
		status = GET_BIT(PING , pin_num);
		break;
	}
	return status;
}


void DIO_initPin1(DIO_Pins_t pin, DIO_PinStatus_t status)
{
	DIO_Port_t port;
	u8 pin_num;

	port = (pin / 8);
	pin_num = pin % 8;

	switch (status)
	{
		case OUTPUT:
		switch (port)
		{
			case PA:
			SET_BIT(DDRA, pin_num);
			CLEAR_BIT(PORTA, pin_num);
			break;
			
			case PB:
			SET_BIT(DDRB, pin_num);
			CLEAR_BIT(PORTB, pin_num);
			break;
			
			case PC:
			SET_BIT(DDRC, pin_num);
			CLEAR_BIT(PORTC, pin_num);
			break;
			
			case PD:
			SET_BIT(DDRD, pin_num);
			CLEAR_BIT(PORTD, pin_num);
			break;
			
			case PE:
			SET_BIT(DDRE, pin_num);
			CLEAR_BIT(PORTE, pin_num);
			break;
			
			case PF:
			SET_BIT(DDRF, pin_num);
			CLEAR_BIT(PORTF, pin_num);
			break;
			
			case PG:
			SET_BIT(DDRG, pin_num);
			CLEAR_BIT(PORTG, pin_num);
			break;			
		}
		break;
		case INFREE:
		switch (port)
		{
			case PA:
			CLEAR_BIT(DDRA, pin_num);
			CLEAR_BIT(PORTA, pin_num);
			break;
			
			case PB:
			CLEAR_BIT(DDRB, pin_num);
			CLEAR_BIT(PORTB, pin_num);
			break;
			
			case PC:
			CLEAR_BIT(DDRC, pin_num);
			CLEAR_BIT(PORTC, pin_num);
			break;
			
			case PD:
			CLEAR_BIT(DDRD, pin_num);
			CLEAR_BIT(PORTD, pin_num);
			break;

			case PE:
			CLEAR_BIT(DDRE, pin_num);
			CLEAR_BIT(PORTE, pin_num);
			break;
			
			case PF:
			CLEAR_BIT(DDRF, pin_num);
			CLEAR_BIT(PORTF, pin_num);
			break;
			
			case PG:
			CLEAR_BIT(DDRG, pin_num);
			CLEAR_BIT(PORTG, pin_num);
			break;
		}
		break;
		case INPULL:
		switch (port)
		{
			case PA:
			CLEAR_BIT(DDRA, pin_num);
			SET_BIT(PORTA, pin_num);
			break;
			case PB:
			CLEAR_BIT(DDRB, pin_num);
			SET_BIT(PORTB, pin_num);
			break;
			case PC:
			CLEAR_BIT(DDRC, pin_num);
			SET_BIT(PORTC, pin_num);
			break;
			case PD:
			CLEAR_BIT(DDRD, pin_num);
			SET_BIT(PORTD, pin_num);
			break;
			
			case PE:
			CLEAR_BIT(DDRE, pin_num);
			SET_BIT(PORTE, pin_num);
			break;
			case PF:
			CLEAR_BIT(DDRF, pin_num);
			SET_BIT(PORTF, pin_num);
			break;
			case PG:
			CLEAR_BIT(DDRG, pin_num);
			SET_BIT(PORTG, pin_num);
			break;
		}
		break;
	}
}


void DIO_WritePin1(DIO_Pins_t pin, DIO_PinVoltage_t volt)
{
	DIO_Port_t port;
	u8 pin_num;

	port = (DIO_Port_t)(pin / 8);
	pin_num = pin % 8;

	if (volt == HIGH)
	{
		switch (port)
		{
			case PA:
			SET_BIT(PORTA, pin_num);
			break;
			
			case PB:
			SET_BIT(PORTB, pin_num);
			break;
			
			case PC:
			SET_BIT(PORTC, pin_num);
			break;
			
			case PD:
			SET_BIT(PORTD, pin_num);
			break;

			case PE:
			SET_BIT(PORTE, pin_num);
			break;
			
			case PF:
			SET_BIT(PORTF, pin_num);
			break;
			
			case PG:
			SET_BIT(PORTG, pin_num);
			break;
		}
	}
	else if (volt == LOW)
	{
		switch (port)
		{
			case PA:
			CLEAR_BIT(PORTA, pin_num);
			break;
			
			case PB:
			CLEAR_BIT(PORTB, pin_num);
			break;
			
			case PC:
			CLEAR_BIT(PORTC, pin_num);
			break;
			
			case PD:
			CLEAR_BIT(PORTD, pin_num);
			break;

			case PE:
			CLEAR_BIT(PORTE, pin_num);
			break;
			
			case PF:
			CLEAR_BIT(PORTF, pin_num);
			break;
			
			case PG:
			CLEAR_BIT(PORTG, pin_num);
			break;
		}
	}
}

DIO_PinVoltage_t DIO_ReadPin1(DIO_Pins_t pin)
{
	DIO_Port_t port;
	u8 pin_num;
	DIO_PinVoltage_t status = 0;

	port = (DIO_Port_t)(pin / 8);
	pin_num = pin % 8;

	switch (port)
	{
		case PA:
		status = GET_BIT(PINA, pin_num);
		break;
		
		case PB:
		status = GET_BIT(PINB, pin_num);
		break;
		
		case PC:
		status = GET_BIT(PINC, pin_num);
		break;
		
		case PD:
		status = GET_BIT(PIND, pin_num);
		break;
		
		case PE:
		status = GET_BIT(PINE, pin_num);
		break;
		
		case PF:
		status = GET_BIT(PINF, pin_num);
		break;
		
		case PG:
		status = GET_BIT(PING, pin_num);
		break;
	}
	return status;
}

void DIO_TogglePin(DIO_Pins_t pin)
{
	DIO_PinVoltage_t currentStatus = DIO_ReadPin1(pin);
	if (currentStatus == HIGH)
	{
		DIO_WritePin1(pin, LOW);
	}
	else
	{
		DIO_WritePin1(pin, HIGH);
	}
}

void DIO_Write_Port(DIO_Port_t port, u8 value)
{
	switch (port)
	{
		case PA:
		PORTA = value;
		break;
		
		case PB:
		PORTB = value;
		break;
		
		case PC:
		PORTC = value;
		break;
		
		case PD:
		PORTD = value;
		break;

		case PE:
		PORTE = value;
		break;
		
		case PF:
		PORTF = value;
		break;
		
		case PG:
		PORTG = value;
		break;
	}
}

u8 DIO_Read_Port(DIO_Port_t port)
{
	u8 value = 0;
	switch (port)
	{
		case PA:
		value = PINA; // Read the value of Port A
		break;
		
		case PB:
		value = PINB; // Read the value of Port B
		break;
		
		case PC:
		value = PINC; // Read the value of Port C
		break;
		
		case PD:
		value = PIND; // Read the value of Port D
		break;
		
		case PE:
		value = PINE; // Read the value of Port E
		break;
		
		case PF:
		value = PINF; // Read the value of Port F
		break;
		
		case PG:
		value = PING; // Read the value of Port G
		break;
	}
	return value;
}


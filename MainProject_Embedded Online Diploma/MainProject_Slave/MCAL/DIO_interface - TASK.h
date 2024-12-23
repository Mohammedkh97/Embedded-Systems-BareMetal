/*
* DIO_interface.h
*
* Created: 10/17/2023 12:55:05 AM
*  Author: Mohammed Khalaf
*/


#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

typedef enum
{
	OUTPUT,
	INFREE,
	INPULL
}DIO_PinStatus_type;

typedef enum
{
	PA,
	PB,
	PC,
	PD
}DIO_Port_type;

typedef enum
{
	LOW= 0,
	HIGH
	}DIO_PinVoltage_type;

typedef enum
{
	PINA0 = 0,
	PINA1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	TotalPins
	}DIO_Pins_type;
	
void DIO_initPin1(DIO_Pins_type pin , DIO_PinStatus_type status);
void DIO_initPin( DIO_Port_type port, u8 pin_num , DIO_PinStatus_type status);

void DIO_WritePin1(DIO_Pins_type pin ,DIO_PinVoltage_type volt);
void DIO_WritePin(DIO_Port_type port , u8 pin_num ,DIO_PinVoltage_type volt);

DIO_PinVoltage_type DIO_ReadPin(DIO_Port_type port , u8 pin_num);

void DIO_TogglePin(DIO_Pins_type);
void DIO_Write_Port(DIO_Port_type port, u8 value);
u8 DIO_Read_Port(DIO_Port_type port);




#endif /* DIO_INTERFACE_H_ */
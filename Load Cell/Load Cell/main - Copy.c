/*
* Load Cell.c
*
* Created: 6/9/2024 12:41:32 PM
* Author : Mohammed Khalaf
*/



//#include "Application File.h"

#define F_CPU 16000000UL
#include <util/delay.h>

#include "stdTypes.h"
#include "DIO_interface.h"
#include "Utils.h"
#include "MemoryMap.h"
#include "DIO_interface.h"
#include "GLCD_ST7920.h"
#include "HX711_Load_Cell.h"
#include "HX711_Config.h"
#include "Scale Configurations.h"
#include "Ex_int.h"
#include "LCD_Private.h"
#include "SPI.h"
#include "UART.h"
#include "UART_Services.h"
#include "Timers.h"
#include "SPI.h"

#include <avr/io.h>
//#include <avr/interrupt.h>

u8 timer0Flag= 0;
u8 x = 0;
#define LED_PIN PINB4
// int main(void)
// {
// 	DIO_init();
// 	// Enable global interrupts
// 	sei();
//
// 	// Timer0 configuration
// 	TCCR0 = 0x04; // Set prescaler to 64
// 	TCNT0 = 0; // Initialize counter
// 	TIMSK = 0x01; // Enable Timer0 overflow interrupt (TOIE0)
// 	init_pins();
// 	// 	//SPI_initMaster();
// 	GLCD_ST7920_init();
// 	// 	DIO_initPin1(HX711_SCK_PIN, OUTPUT);
// 	EXI_init();
// 	EXI_Enable(EX_INT0);
// 	UART_Init(115200 , UART0);
// // 	ENABLE_GLOBAL_INTERRUPT();
// // 	//TCCR0 = 4;
// // 	TCNT0 = 156;
// // 	TIMSK = 1;
// 	//TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_64);
// 	//TIMER0_OV_InterruptEnable();  // Enable Timer0 overflow interrupt
// 	//TIMER0_OC0_non_PWM_Mode(OC0_DISCONNECTED);
//
// 	//TIMER0_OV_InterruptEnable();
// 	// 	GLCD_ST7920_SendString(0, 0, (u8*)"Weight");
// 	GLCD_ST7920_SendString(1, 0, (u8*)"Measurement");
// 	HX711_Calibrate();
//
// 	// 	DIO_WritePin1(PINB4 , HIGH);
// 	//	setup();
// 	// Replace with your application code
//
// 	while (1)
// 	{
// 		//systemRunnable();
//
// 		//GLCD_ST7920_SendString(0, 0, (u8*)"Weight");
// 		//GLCD_ST7920_SendString(1, 0, (u8*)"Measurement");
// 		//GLCD_ST7920_SendString(0,0,(u8*)"Here");
// 		GLCD_ST7920_WriteNumber(0,5,x);
// 		x++;
// 		_delay_ms(100);
// 	}
// }




// Timer0 overflow ISR
// ISR(TIMER0_OVF_vect)
// {
// 	static u16 overflowCount = 0;
// 	overflowCount++;
//
// 	if (overflowCount >= 976)
// 	{  // Adjust this value for 1 second based on the prescaler
// 		DIO_TogglePin(PINB4); // Toggle the LED
// 		overflowCount = 0;  // Reset the overflow count
// 	}
// }

/*
int main(void)
{
DIO_init();   // Initialize I/O pins
init_pins();  // Initialize other pins as needed
GLCD_ST7920_init();  // Initialize the GLCD

// Enable global interrupts
sei();

// Timer0 configuration
TCCR0 = 0x04; // Set prescaler to 64
TCNT0 = 0;    // Initialize counter to 0
TIMSK |= (1 << TOIE0); // Enable Timer0 overflow interrupt


//  	TCCR0 = 4;
//  TCNT0 = 156;
//  	TIMSK = 1;
//  	ENABLE_GLOBAL_INTERRUPT();
//  	TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_64);
// 	TCNT0 = 0;    // Initialize counter to 0
//  	TIMER0_OV_InterruptEnable();  // Enable Timer0 overflow interrupt
// Initialize external interrupt (if used)
// 	EXI_init();
// 	EXI_Enable(EX_INT0);

while (1)
{
GLCD_ST7920_WriteNumber(0, 5, x);  // Display the number on the GLCD
x++;
_delay_ms(100);  // Delay for 100 ms
}
}

// Timer0 overflow ISR
ISR(TIMER0_OVF_vect)
{
static uint16_t overflowCount = 0;
overflowCount++;

if (overflowCount >= 976)
{
DIO_TogglePin(LED_PIN); // Toggle the LED every second
overflowCount = 0;  // Reset overflow counter
}
}

*/

// Function to initialize the LED pin as output
void DIO_init1() {
	// Set PINB4 as output for LED
	DDRB |= (1 << PINB4);
}

// Function to toggle the LED pin
void DIO_TogglePin1(uint8_t pin) {
	PORTB ^= (1 << pin);
}

int main(void) {
	// Initialize I/O
	DIO_init();  // Initialize the LED pin
	init_pins();  // Initialize other pins as needed
	GLCD_ST7920_init();  // Initialize the GLCD

	// Enable global interrupts
	
 	ENABLE_GLOBAL_INTERRUPT();
 	TIMER0_Init(TIMER0_NORMAL_MODE, TIMER0_SCALER_64);
	TCNT0 = 0;    // Initialize counter to 0
 	TIMER0_OV_InterruptEnable();  // Enable Timer0 overflow interrupt

	while (1) {
		// Main loop does nothing; work is done in ISR
		GLCD_ST7920_WriteNumber(0, 5, x);  // Display the number on the GLCD
		x++;
		_delay_ms(100);  // Delay for 100 ms
	}
}

// Timer0 overflow interrupt service routine
ISR(TIMER0_OVF_vect) {
	static uint16_t overflowCount = 0;
	overflowCount++;

	if (overflowCount >= 976) {  // Check if 1 second has passed
		DIO_TogglePin1(PINB4); // Toggle the LED
		overflowCount = 0;  // Reset the overflow count
	}
}
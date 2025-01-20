/*
 * App_Services.c
 *
 * Created: 05/09/2024 16:04:31
 *  Author: Mohammed Khalaf
 */ 

#include "stdTypes.h"
#include "App_Services.h"


f32 get_AbsoluteValue(f32 value)
{
	return (value < 0) ? -value : value;
}
//
//void ESP32_WiFi_Config(u8* SSID, u8* password)
//{
//	u8 command[100];
//	// Set Wi-Fi mode to Station mode
//	UART_TransmitString((u8*)"AT+CWMODE=1", UART0);
//	UART_TransmitString((u8*)"\r\n", UART0);
//	_delay_ms(1000); // Wait for response
//
//	// Format the AT command with the SSID and password
//	sprintf((u8*)command, "AT+CWJAP=\"%s\",\"%s\"", SSID, password);
//
//	UART_TransmitString((u8*)"AT+CWJAP=\"Ahmed Hassan\",\"Ahmed 111\"" , UART0);
//	UART_TransmitString((u8*)"\r\n" , UART0);
//	// Send the command to join the network
//	UART_TransmitString(command, UART0);
//	UART_TransmitString((u8*)"\r\n", UART0);
//
//	// Wait for a short time to allow ESP32 to respond
//	_delay_ms(5000);
//}


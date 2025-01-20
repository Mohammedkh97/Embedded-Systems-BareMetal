/*
 * MFRC522_Config.h
 *
 * Created: 7/18/2024 5:06:48 PM
 *  Author: Mohammed Khalaf
 */ 


#ifndef MFRC522_CONFIG_H_
#define MFRC522_CONFIG_H_

// Constants for the MFRC522 communication

#define MI_NOTAGERR           0
#define MI_OK                 1
#define MI_ERR                0

// Define the pins used for the ChipSelectPin SDA (SS) and RST (reset) pins
// Constants for the MFRC522 communication
#define MI_NOTAGERR           0
#define MI_OK                 1
#define MI_ERR                0

// Define the pins used for the ChipSelectPin SDA (SS) and RST (reset) pins

#define ChipSelectPin				PINB12
#define RESET_PIN					PINA9
#define UNUSED_PIN					255
#define TOGGLE_PIN					PINB4
#define RFID_PORT					GPIOB->CRL
#define RFID_SPI_CHANNEL			SPI_2
/************************************************************************/
/*						SPI PINS CONFIGURATIONS                         */
/************************************************************************/

#define SPI_SS						PINB12
#define SPI_SCK						PINB13
#define SPI_MOSI					PINB15
#define SPI_MISO					PINB14

#define MAX_LEN						16



#endif /* MFRC522_CONFIG_H_ */

/*
 * SPI_Configuration.h
 *
 *  Created on: Oct 19, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef SPI_SPI_CONFIGURATION_H_
#define SPI_SPI_CONFIGURATION_H_


// SPI1 Pin Definitions
//#define SPI1_SCK_PIN       GPIO_PIN_5    // PINA5

#define SPI1_SCK_PIN       PINA5    // PINA5
#define SPI1_SCK_PORT      GPIOA

#define SPI1_MOSI_PIN      PINA7    // PINA7
#define SPI1_MOSI_PORT     GPIOA

#define SPI1_MISO_PIN      PINA6    // PINA6
#define SPI1_MISO_PORT     GPIOA

#define SPI1_NSS_PIN       PINA4    // PINA4
#define SPI1_NSS_PORT      GPIOA

// SPI2 Pin Definitions
#define SPI2_SCK_PIN       PINB13   // PINB13
#define SPI2_SCK_PORT      GPIOB

#define SPI2_MOSI_PIN      PINB15   // PINB15
#define SPI2_MOSI_PORT     GPIOB

#define SPI2_MISO_PIN      PINB14   // PINB14
#define SPI2_MISO_PORT     GPIOB

#define SPI2_NSS_PIN       PINB12   // PINB12
#define SPI2_NSS_PORT      GPIOB

#define SPI_SSI			SPI_SSI_HIGH

#endif /* SPI_SPI_CONFIGURATION_H_ */

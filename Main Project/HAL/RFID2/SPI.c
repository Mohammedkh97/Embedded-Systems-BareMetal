#include "stm32f1xx_hal.h"
#include "stm32f1xx.h"
#include <stdlib.h>
#include <stdio.h>
#include "stm32f103xb.h"
#include "stdTypes.h"
#include "GLCD_ST7920/GLCD_ST7920_Interface.h"
// SPI2 Initialization
void SPI2_Init(void) {
    // Enable clocks for SPI2 and GPIOB
    RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // Configure GPIO for SPI2 (PB13: SCK, PB14: MISO, PB15: MOSI)
    GPIOB->CRH &= ~((0xF << (4 * (13 - 8))) | (0xF << (4 * (14 - 8))) | (0xF << (4 * (15 - 8))));
    GPIOB->CRH |= ((0xB << (4 * (13 - 8))) | (0x4 << (4 * (14 - 8))) | (0xB << (4 * (15 - 8))));

    // Configure SPI2
    SPI2->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_BR_0 | SPI_CR1_SSM | SPI_CR1_SSI;  // Master mode, fPCLK/16, Software NSS
    SPI2->CR1 |= SPI_CR1_SPE;  // Enable SPI2
}

// Send and receive data via SPI
uint8_t SPI2_Transfer(uint8_t data) {
    while (!(SPI2->SR & SPI_SR_TXE));  // Wait until TX buffer is empty
    SPI2->DR = data;                  // Send data
    while (!(SPI2->SR & SPI_SR_RXNE)); // Wait until RX buffer is full
    return SPI2->DR;                  // Return received data
}




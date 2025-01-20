/*
 * GPIO_MemoryMap.h
 *
 *  Created on: Sep 20, 2024
 *      Author: Mohammed
 */

#ifndef MCAL_GPIO_GPIO_MEMORYMAP_H_
#define MCAL_GPIO_GPIO_MEMORYMAP_H_



/*

// Here’s the equivalent #define representation for the GPIO registers on the STM32F103C8T6:

// Base addresses of GPIO ports
#define GPIOA_BASE  (0x40010800UL)
#define GPIOB_BASE  (0x40010C00UL)
#define GPIOC_BASE  (0x40011000UL)
#define GPIOD_BASE  (0x40011400UL)
#define GPIOE_BASE  (0x40011800UL)

// GPIO register offsets
#define GPIO_CRL_OFFSET   (0x00UL)  // Control register low
#define GPIO_CRH_OFFSET   (0x04UL)  // Control register high
#define GPIO_IDR_OFFSET   (0x08UL)  // Input data register
#define GPIO_ODR_OFFSET   (0x0CUL)  // Output data register
#define GPIO_BSRR_OFFSET  (0x10UL)  // Bit set/reset register
#define GPIO_BRR_OFFSET   (0x14UL)  // Bit reset register
#define GPIO_LCKR_OFFSET  (0x18UL)  // Configuration lock register

// GPIOA Register definitions
#define GPIOA_CRL  (*(volatile unsigned long*)(GPIOA_BASE + GPIO_CRL_OFFSET))
#define GPIOA_CRH  (*(volatile unsigned long*)(GPIOA_BASE + GPIO_CRH_OFFSET))
#define GPIOA_IDR  (*(volatile unsigned long*)(GPIOA_BASE + GPIO_IDR_OFFSET))
#define GPIOA_ODR  (*(volatile unsigned long*)(GPIOA_BASE + GPIO_ODR_OFFSET))
#define GPIOA_BSRR (*(volatile unsigned long*)(GPIOA_BASE + GPIO_BSRR_OFFSET))
#define GPIOA_BRR  (*(volatile unsigned long*)(GPIOA_BASE + GPIO_BRR_OFFSET))
#define GPIOA_LCKR (*(volatile unsigned long*)(GPIOA_BASE + GPIO_LCKR_OFFSET))

// GPIOB Register definitions
#define GPIOB_CRL  (*(volatile unsigned long*)(GPIOB_BASE + GPIO_CRL_OFFSET))
#define GPIOB_CRH  (*(volatile unsigned long*)(GPIOB_BASE + GPIO_CRH_OFFSET))
#define GPIOB_IDR  (*(volatile unsigned long*)(GPIOB_BASE + GPIO_IDR_OFFSET))
#define GPIOB_ODR  (*(volatile unsigned long*)(GPIOB_BASE + GPIO_ODR_OFFSET))
#define GPIOB_BSRR (*(volatile unsigned long*)(GPIOB_BASE + GPIO_BSRR_OFFSET))
#define GPIOB_BRR  (*(volatile unsigned long*)(GPIOB_BASE + GPIO_BRR_OFFSET))
#define GPIOB_LCKR (*(volatile unsigned long*)(GPIOB_BASE + GPIO_LCKR_OFFSET))

// GPIOC Register definitions
#define GPIOC_CRL  (*(volatile unsigned long*)(GPIOC_BASE + GPIO_CRL_OFFSET))
#define GPIOC_CRH  (*(volatile unsigned long*)(GPIOC_BASE + GPIO_CRH_OFFSET))
#define GPIOC_IDR  (*(volatile unsigned long*)(GPIOC_BASE + GPIO_IDR_OFFSET))
#define GPIOC_ODR  (*(volatile unsigned long*)(GPIOC_BASE + GPIO_ODR_OFFSET))
#define GPIOC_BSRR (*(volatile unsigned long*)(GPIOC_BASE + GPIO_BSRR_OFFSET))
#define GPIOC_BRR  (*(volatile unsigned long*)(GPIOC_BASE + GPIO_BRR_OFFSET))
#define GPIOC_LCKR (*(volatile unsigned long*)(GPIOC_BASE + GPIO_LCKR_OFFSET))

// GPIOD Register definitions
#define GPIOD_CRL  (*(volatile unsigned long*)(GPIOD_BASE + GPIO_CRL_OFFSET))
#define GPIOD_CRH  (*(volatile unsigned long*)(GPIOD_BASE + GPIO_CRH_OFFSET))
#define GPIOD_IDR  (*(volatile unsigned long*)(GPIOD_BASE + GPIO_IDR_OFFSET))
#define GPIOD_ODR  (*(volatile unsigned long*)(GPIOD_BASE + GPIO_ODR_OFFSET))
#define GPIOD_BSRR (*(volatile unsigned long*)(GPIOD_BASE + GPIO_BSRR_OFFSET))
#define GPIOD_BRR  (*(volatile unsigned long*)(GPIOD_BASE + GPIO_BRR_OFFSET))
#define GPIOD_LCKR (*(volatile unsigned long*)(GPIOD_BASE + GPIO_LCKR_OFFSET))

// GPIOE Register definitions
#define GPIOE_CRL  (*(volatile unsigned long*)(GPIOE_BASE + GPIO_CRL_OFFSET))
#define GPIOE_CRH  (*(volatile unsigned long*)(GPIOE_BASE + GPIO_CRH_OFFSET))
#define GPIOE_IDR  (*(volatile unsigned long*)(GPIOE_BASE + GPIO_IDR_OFFSET))
#define GPIOE_ODR  (*(volatile unsigned long*)(GPIOE_BASE + GPIO_ODR_OFFSET))
#define GPIOE_BSRR (*(volatile unsigned long*)(GPIOE_BASE + GPIO_BSRR_OFFSET))
#define GPIOE_BRR  (*(volatile unsigned long*)(GPIOE_BASE + GPIO_BRR_OFFSET))
#define GPIOE_LCKR (*(volatile unsigned long*)(GPIOE_BASE + GPIO_LCKR_OFFSET))

 */

/****************************  Peripheral_memory_map ************************/


#define FLASH_BASE 					0x08000000UL      /*!< FLASH base address in the alias region */
#define FLASH_BANK1_END 			0x0801FFFFUL /*!< FLASH END address of bank1 */
#define SRAM_BASE 					0x20000000UL       /*!< SRAM base address in the alias region */
#define PERIPH_BASE 				0x40000000UL     /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE 				0x22000000UL   /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE 				0x42000000UL /*!< Peripheral base address in the bit-band region */

/*!< Peripheral memory map */

#define APB1PERIPH_BASE 			PERIPH_BASE
#define APB2PERIPH_BASE 			(PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE 				(PERIPH_BASE + 0x00020000UL)


/*******************   BASE Address Definition    *********************/

#define GPIOA_BASE 					(APB2PERIPH_BASE + 0x00000800UL)
#define GPIOB_BASE 					(APB2PERIPH_BASE + 0x00000C00UL)
#define GPIOC_BASE 					(APB2PERIPH_BASE + 0x00001000UL)
#define GPIOD_BASE 					(APB2PERIPH_BASE + 0x00001400UL)
#define GPIOE_BASE 					(APB2PERIPH_BASE + 0x00001800UL)


/***********   REGISTER ADDRESSES FOR GPIOx     ***********************/

#define GPIOA 						((GPIO_t *)GPIOA_BASE)
#define GPIOB 						((GPIO_t *)GPIOB_BASE)
#define GPIOC 						((GPIO_t *)GPIOC_BASE)
#define GPIOD 						((GPIO_t *)GPIOD_BASE)
#define GPIOE 						((GPIO_t *)GPIOE_BASE)



#endif /* MCAL_GPIO_GPIO_MEMORYMAP_H_ */

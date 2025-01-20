/*
 * RCC_MemoryMap.h
 *
 *  Created on: Sep 21, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef RCC_RCC_MEMORYMAP_H_
#define RCC_RCC_MEMORYMAP_H_

#define FLASH_BASE 0x08000000UL      /*!< FLASH base address in the alias region */
#define FLASH_BANK1_END 0x0801FFFFUL /*!< FLASH END address of bank1 */
#define SRAM_BASE 0x20000000UL       /*!< SRAM base address in the alias region */

#define PERIPH_BASE 0x40000000UL     /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE 0x22000000UL   /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE 0x42000000UL /*!< Peripheral base address in the bit-band region */

/*!< Peripheral memory map */
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE + 0x00010000UL)

#define AHBPERIPH_BASE (PERIPH_BASE + 0x00020000UL)

/*******************   BASE Address Definition    *********************/
#define RCC_BASE (AHBPERIPH_BASE + 0x00001000UL)

#define RCC ((RCC_t *)RCC_BASE)


#endif /* RCC_RCC_MEMORYMAP_H_ */

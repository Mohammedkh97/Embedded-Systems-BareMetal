/*
 * FLASH_ACR_MemoryMap.h
 *
 *  Created on: Oct 24, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef EMBEDDED_FLASH_MEMORY_FLASH_ACR_MEMORYMAP_H_
#define EMBEDDED_FLASH_MEMORY_FLASH_ACR_MEMORYMAP_H_

#define FLASH_BASE 0x08000000UL      /*!< FLASH base address in the alias region */

#define PERIPH_BASE 0x40000000UL     /*!< Peripheral base address in the alias region */

#define SRAM_BB_BASE 0x22000000UL   /*!< SRAM base address in the bit-band region */
#define PERIPH_BB_BASE 0x42000000UL /*!< Peripheral base address in the bit-band region */

/*!< Peripheral memory map */
#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE 		(PERIPH_BASE + 0x00010000UL)
#define AHBPERIPH_BASE 			(PERIPH_BASE + 0x00020000UL)
#define FLASH_R_BASE          	(AHBPERIPH_BASE + 0x00002000UL) /*!< Flash registers base address */
#define FLASH        			((FLASH_t*)FLASH_R_BASE)



#endif /* EMBEDDED_FLASH_MEMORY_FLASH_ACR_MEMORYMAP_H_ */

/*
 * FLASH_ACR_Private.h
 *
 *  Created on: Oct 24, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef EMBEDDED_FLASH_MEMORY_FLASH_ACR_PRIVATE_H_
#define EMBEDDED_FLASH_MEMORY_FLASH_ACR_PRIVATE_H_

typedef struct
{
	volatile u32 ACR;   // Access control register
	volatile u32 KEYR;  // Flash key register
	volatile u32 OPTKEYR; // Option key register
	volatile u32 SR;    // Status register
	volatile u32 CR;    // Control register
	volatile u32 AR;    // Address register
	volatile u32 OBR;   // Option byte register
	volatile u32 WRPR;  // Write protection register
} FLASH_t;

typedef enum
{
	LATENCY_0 = 0,           // 0 wait states
	LATENCY_1 = 1,           // 1 wait state
	LATENCY_2 = 2,           // 2 wait states
	LATENCY_3 = 3,           // 3 wait states
	PRFTBE = 4,           // Prefetch buffer enable
	PRFTBS = 5            // Prefetch buffer status
} FLASH_ACR_t;

/*
 Flash Latency Values:
 For STM32 microcontrollers, here’s the mapping of latency values to clock speeds:

 0 wait states: For system clock ≤ 24 MHz
 1 wait state: For system clock between 24 MHz and 48 MHz
 2 wait states: For system clock between 48 MHz and 72 MHz
 So, in your case (running at 72 MHz), you should set the latency to 2 wait states to ensure stable access to the flash memory.
 * */
#endif /* EMBEDDED_FLASH_MEMORY_FLASH_ACR_PRIVATE_H_ */

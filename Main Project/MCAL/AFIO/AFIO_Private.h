/*
 * AFIO_Private.h
 *
 *  Created on: Nov 28, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef AFIO_PRIVATE_H_
#define AFIO_PRIVATE_H_

typedef struct {
    volatile u32 EVCR;        // Event Control Register (Offset: 0x00)
    volatile u32 MAPR;        // Re-map and Debug I/O Configuration Register (Offset: 0x04)
    volatile u32 EXTICR1;     // External Interrupt Configuration Register 1 (EXTI0 - EXTI3) (Offset: 0x08)
    volatile u32 EXTICR2;     // External Interrupt Configuration Register 2 (EXTI4 - EXTI7) (Offset: 0x0C)
    volatile u32 EXTICR3;     // External Interrupt Configuration Register 3 (EXTI8 - EXTI11) (Offset: 0x10)
    volatile u32 EXTICR4;     // External Interrupt Configuration Register 4 (EXTI12 - EXTI15) (Offset: 0x14)
    volatile u32 MAPR2;       // Additional Remap Register (High-density devices only) (Offset: 0x1C)
} AFIO_t;

#endif /* AFIO_PRIVATE_H_ */

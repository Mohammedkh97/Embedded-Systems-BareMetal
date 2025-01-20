/*
 * GPIO_Private.h
 *
 *  Created on: Sep 20, 2024
 *      Author: Mohammed
 */

#ifndef MCAL_GPIO_GPIO_PRIVATE_H_
#define MCAL_GPIO_GPIO_PRIVATE_H_

/*
 *  @brief General Purpose I/O
 */
extern const DIO_PinStatus_t InitializationPinsArray[TOTAL_PINS];
typedef struct
{

	volatile u32 CRL  ;
	volatile u32 CRH  ;
	volatile u32 IDR  ;
	volatile u32 ODR  ;
	volatile u32 BSRR ;
	volatile u32 BRR  ;
	volatile u32 LCKR ;

}GPIO_t;

// Special Macros for BSRR Register :
#define GPIO_Set_Pin(GPIOx, Pin)    ((GPIOx)->BSRR = (1 << (Pin)))         // Set pin
//#define GPIO_Clear_Pin(GPIOx, Pin)  ((GPIOx)->BSRR = (1 << ((Pin) + 16)))  // Clear pin
#define GPIO_Clear_Pin(GPIOx, Pin)  ((GPIOx)->BRR  = (1 << (Pin)))   // Clear pin using BRR




#endif /* MCAL_GPIO_GPIO_PRIVATE_H_ */

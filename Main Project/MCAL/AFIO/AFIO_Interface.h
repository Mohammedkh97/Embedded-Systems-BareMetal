/*
 * AFIO_Interface.h
 *
 *  Created on: Nov 28, 2024
 *  Author: Mohammed Khalaf
 */

#ifndef AFIO_AFIO_INTERFACE_H_
#define AFIO_AFIO_INTERFACE_H_

/** Event control register (AFIO_EVCR) **/

typedef enum
{
    AFIO_EVCR_PIN_0 = 0,  // Event on Pin 0
    AFIO_EVCR_PIN_1 = 1,  // Event on Pin 1
    AFIO_EVCR_PIN_2 = 2,  // Event on Pin 2
    AFIO_EVCR_PIN_3 = 3,  // Event on Pin 3
    AFIO_EVCR_PIN_4 = 4,  // Event on Pin 4
    AFIO_EVCR_PIN_5 = 5,  // Event on Pin 5
    AFIO_EVCR_PIN_6 = 6,  // Event on Pin 6
    AFIO_EVCR_PIN_7 = 7,  // Event on Pin 7
    AFIO_EVCR_PIN_8 = 8,  // Event on Pin 8
    AFIO_EVCR_PIN_9 = 9,  // Event on Pin 9
    AFIO_EVCR_PIN_10 = 10,// Event on Pin 10
    AFIO_EVCR_PIN_11 = 11,// Event on Pin 11
    AFIO_EVCR_PIN_12 = 12,// Event on Pin 12
    AFIO_EVCR_PIN_13 = 13,// Event on Pin 13
    AFIO_EVCR_PIN_14 = 14,// Event on Pin 14
    AFIO_EVCR_PIN_15 = 15,// Event on Pin 15

} AFIO_EVCR_PIN_t;

typedef enum
{
    AFIO_EVCR_EVOE_DISABLE = 0,  // Event Output Disabled
    AFIO_EVCR_EVOE_ENABLE  = 1,  // Event Output Enabled
} AFIO_EVCR_EVOE_t;

typedef enum
{
    AFIO_EVCR_PORT_A = 0,  // Event for GPIO Port A
    AFIO_EVCR_PORT_B = 1,  // Event for GPIO Port B
    AFIO_EVCR_PORT_C = 2,  // Event for GPIO Port C
    AFIO_EVCR_PORT_D = 3,  // Event for GPIO Port D
    AFIO_EVCR_PORT_E = 4,  // Event for GPIO Port E
    AFIO_EVCR_PORT_F = 5,  // Event for GPIO Port F
    AFIO_EVCR_PORT_G = 6,  // Event for GPIO Port G
} AFIO_EVCR_PORT_t;


/**** AF remap and debug I/O configuration register (AFIO_MAPR) ****/

typedef enum
{
    AFIO_MAPR_SPI1_REMAP       		= (1U << 0),  /**< SPI1 Remapping */
    AFIO_MAPR_I2C1_REMAP       		= (1U << 1),  /**< I2C1 Remapping */
    AFIO_MAPR_USART1_REMAP     		= (1U << 2),  /**< USART1 Remapping */
    AFIO_MAPR_USART2_REMAP     		= (1U << 3),  /**< USART2 Remapping */
    AFIO_MAPR_USART3_REMAP_0   		= (1U << 4),  /**< USART3 Remapping Bit 0 */
    AFIO_MAPR_USART3_REMAP_1   		= (1U << 5),  /**< USART3 Remapping Bit 1 */
    AFIO_MAPR_TIM1_REMAP_0     		= (1U << 6),  /**< TIM1 Remapping Bit 0 */
    AFIO_MAPR_TIM1_REMAP_1     		= (1U << 7),  /**< TIM1 Remapping Bit 1 */
    AFIO_MAPR_TIM2_REMAP_0     		= (1U << 8),  /**< TIM2 Remapping Bit 0 */
    AFIO_MAPR_TIM2_REMAP_1     		= (1U << 9),  /**< TIM2 Remapping Bit 1 */
    AFIO_MAPR_TIM3_REMAP_0     		= (1U << 10), /**< TIM3 Remapping Bit 0 */
    AFIO_MAPR_TIM3_REMAP_1     		= (1U << 11), /**< TIM3 Remapping Bit 1 */
    AFIO_MAPR_TIM4_REMAP       		= (1U << 12), /**< TIM4 Remapping */
    AFIO_MAPR_CAN_REMAP_0      		= (1U << 13), /**< CAN Remapping Bit 0 */
    AFIO_MAPR_CAN_REMAP_1      		= (1U << 14), /**< CAN Remapping Bit 1 */
    AFIO_MAPR_PD01_REMAP       		= (1U << 15), /**< PD01 Remapping */
    AFIO_MAPR_ADC1_ETRGINJ_REMAP 	= (1U << 16), /**< ADC1 External Trigger Injected Remapping */
    AFIO_MAPR_ADC1_ETRGREG_REMAP 	= (1U << 17), /**< ADC1 External Trigger Regular Remapping */
    AFIO_MAPR_ADC2_ETRGINJ_REMAP 	= (1U << 18), /**< ADC2 External Trigger Injected Remapping */
    AFIO_MAPR_ADC2_ETRGREG_REMAP 	= (1U << 19), /**< ADC2 External Trigger Regular Remapping */
    AFIO_MAPR_TIM5CH4_REMAP    		= (1U << 20), /**< TIM5 Channel 4 Internal Remapping */
    AFIO_MAPR_SWJ_CFG_0        		= (1U << 24), /**< Serial Wire JTAG Configuration Bit 0 */
    AFIO_MAPR_SWJ_CFG_1        		= (1U << 25), /**< Serial Wire JTAG Configuration Bit 1 */
    AFIO_MAPR_SWJ_CFG_2        		= (1U << 26)  /**< Serial Wire JTAG Configuration Bit 2 */
} AFIO_MAPR_t;



typedef enum {
    GPIO_A = 0x0,  // GPIOA
    GPIO_B = 0x1,  // GPIOB
    GPIO_C = 0x2,  // GPIOC
    GPIO_D = 0x3,  // GPIOD
    GPIO_E = 0x4,  // GPIOE
    GPIO_F = 0x5,  // GPIOF
    GPIO_G = 0x6,  // GPIOG
    GPIO_H = 0x7,  // GPIOH
    GPIO_I = 0x8   // GPIOI (available on some STM32 models)

} GPIO_Port;

typedef struct {
    GPIO_Port EXTI0_Port;  // GPIO Port for EXTI Line 0
    GPIO_Port EXTI1_Port;  // GPIO Port for EXTI Line 1
    GPIO_Port EXTI2_Port;  // GPIO Port for EXTI Line 2
    GPIO_Port EXTI3_Port;  // GPIO Port for EXTI Line 3

} AFIO_EXTICR1_Config;

typedef struct
{
    GPIO_Port EXTI4_Port;  // GPIO Port for EXTI Line 4
    GPIO_Port EXTI5_Port;  // GPIO Port for EXTI Line 5
    GPIO_Port EXTI6_Port;  // GPIO Port for EXTI Line 6
    GPIO_Port EXTI7_Port;  // GPIO Port for EXTI Line 7

} AFIO_EXTICR2_Config;

typedef struct
{
    GPIO_Port EXTI8_Port;  // GPIO Port for EXTI Line 8
    GPIO_Port EXTI9_Port;  // GPIO Port for EXTI Line 9
    GPIO_Port EXTI10_Port; // GPIO Port for EXTI Line 10
    GPIO_Port EXTI11_Port; // GPIO Port for EXTI Line 11

} AFIO_EXTICR3_Config;

typedef struct
{
    GPIO_Port EXTI12_Port;  // GPIO Port for EXTI Line 12
    GPIO_Port EXTI13_Port;  // GPIO Port for EXTI Line 13
    GPIO_Port EXTI14_Port;  // GPIO Port for EXTI Line 14
    GPIO_Port EXTI15_Port;  // GPIO Port for EXTI Line 15

} AFIO_EXTICR4_Config;

#endif /* AFIO_AFIO_INTERFACE_H_ */

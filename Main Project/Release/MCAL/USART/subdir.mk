################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/USART/USART_Configuration.c \
../MCAL/USART/USART_Program.c 

C_DEPS += \
./MCAL/USART/USART_Configuration.d \
./MCAL/USART/USART_Program.d 

OBJS += \
./MCAL/USART/USART_Configuration.o \
./MCAL/USART/USART_Program.o 


# Each subdirectory must supply rules for building sources it contributes
MCAL/USART/%.o MCAL/USART/%.su MCAL/USART/%.cyclo: ../MCAL/USART/%.c MCAL/USART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/RCC" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/GPIO" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/USART" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/EXTI" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/Embedded Flash memory" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/SPI" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Application Layer" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Application Layer/Al-Ahram" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Utils" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Services/USART_Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Services/Timers_Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/String" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/App_Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/Delay" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/Bitmaps Graphics Display" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/GLCD_ST7920" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/Liquid Crystal Display" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/HX711" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/KEYPAD" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Application Layer/GeneralCode" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL-2f-USART

clean-MCAL-2f-USART:
	-$(RM) ./MCAL/USART/USART_Configuration.cyclo ./MCAL/USART/USART_Configuration.d ./MCAL/USART/USART_Configuration.o ./MCAL/USART/USART_Configuration.su ./MCAL/USART/USART_Program.cyclo ./MCAL/USART/USART_Program.d ./MCAL/USART/USART_Program.o ./MCAL/USART/USART_Program.su

.PHONY: clean-MCAL-2f-USART


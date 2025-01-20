################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/HX711\ V2.0/hx711_V2.c 

C_DEPS += \
./HAL/HX711\ V2.0/hx711_V2.d 

OBJS += \
./HAL/HX711\ V2.0/hx711_V2.o 


# Each subdirectory must supply rules for building sources it contributes
HAL/HX711\ V2.0/hx711_V2.o: ../HAL/HX711\ V2.0/hx711_V2.c HAL/HX711\ V2.0/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/RCC" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/GPIO" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/USART" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/EXTI" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/Embedded Flash memory" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Application Layer" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Utils" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/String" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/App_Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/Delay" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/Bitmaps Graphics Display" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/GLCD_ST7920" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/Liquid Crystal Display" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/HX711" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/HX711 V2.0" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/KEYPAD" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"HAL/HX711 V2.0/hx711_V2.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-HX711-20-V2-2e-0

clean-HAL-2f-HX711-20-V2-2e-0:
	-$(RM) ./HAL/HX711\ V2.0/hx711_V2.cyclo ./HAL/HX711\ V2.0/hx711_V2.d ./HAL/HX711\ V2.0/hx711_V2.o ./HAL/HX711\ V2.0/hx711_V2.su

.PHONY: clean-HAL-2f-HX711-20-V2-2e-0


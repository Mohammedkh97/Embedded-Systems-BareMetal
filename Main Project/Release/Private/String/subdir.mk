################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Private/String/String_lib.c 

C_DEPS += \
./Private/String/String_lib.d 

OBJS += \
./Private/String/String_lib.o 


# Each subdirectory must supply rules for building sources it contributes
Private/String/%.o Private/String/%.su Private/String/%.cyclo: ../Private/String/%.c Private/String/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/RCC" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/GPIO" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/USART" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/EXTI" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/Embedded Flash memory" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/SPI" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/SysTick" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Application Layer" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Application Layer/Al-Ahram" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Utils" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Services/USART_Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Services/Timers_Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/String" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/App_Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/Delay" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/Bitmaps Graphics Display" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/GLCD_ST7920" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/Liquid Crystal Display" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/HX711" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/KEYPAD" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/LCD_TFT_ST7789v" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Application Layer/GeneralCode" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/RFID" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/RFID2" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Private-2f-String

clean-Private-2f-String:
	-$(RM) ./Private/String/String_lib.cyclo ./Private/String/String_lib.d ./Private/String/String_lib.o ./Private/String/String_lib.su

.PHONY: clean-Private-2f-String


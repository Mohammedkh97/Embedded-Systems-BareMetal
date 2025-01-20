################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/LCD_TFT_ST7789v/Fonts.c \
../HAL/LCD_TFT_ST7789v/TFT_Program.c 

C_DEPS += \
./HAL/LCD_TFT_ST7789v/Fonts.d \
./HAL/LCD_TFT_ST7789v/TFT_Program.d 

OBJS += \
./HAL/LCD_TFT_ST7789v/Fonts.o \
./HAL/LCD_TFT_ST7789v/TFT_Program.o 


# Each subdirectory must supply rules for building sources it contributes
HAL/LCD_TFT_ST7789v/%.o HAL/LCD_TFT_ST7789v/%.su HAL/LCD_TFT_ST7789v/%.cyclo: ../HAL/LCD_TFT_ST7789v/%.c HAL/LCD_TFT_ST7789v/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/RCC" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/GPIO" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/USART" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/EXTI" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/Embedded Flash memory" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/SPI" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/MCAL/SysTick" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Application Layer" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Application Layer/Al-Ahram" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Utils" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Services/USART_Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Services/Timers_Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/String" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/App_Services" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/Delay" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Private/Bitmaps Graphics Display" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/GLCD_ST7920" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/Liquid Crystal Display" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/HX711" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/KEYPAD" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/LCD_TFT_ST7789v" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/Application Layer/GeneralCode" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/RFID" -I"D:/MyFiles/Embedded Systems/STM32/Main Project/HAL/RFID2" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL-2f-LCD_TFT_ST7789v

clean-HAL-2f-LCD_TFT_ST7789v:
	-$(RM) ./HAL/LCD_TFT_ST7789v/Fonts.cyclo ./HAL/LCD_TFT_ST7789v/Fonts.d ./HAL/LCD_TFT_ST7789v/Fonts.o ./HAL/LCD_TFT_ST7789v/Fonts.su ./HAL/LCD_TFT_ST7789v/TFT_Program.cyclo ./HAL/LCD_TFT_ST7789v/TFT_Program.d ./HAL/LCD_TFT_ST7789v/TFT_Program.o ./HAL/LCD_TFT_ST7789v/TFT_Program.su

.PHONY: clean-HAL-2f-LCD_TFT_ST7789v


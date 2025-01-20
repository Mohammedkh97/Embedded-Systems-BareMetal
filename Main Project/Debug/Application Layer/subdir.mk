################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/MyFiles/Embedded_Systems/Embedded_Systems\ _CPP/My_Projects/Main\ Project/Application\ Layer/MainApp.c 

OBJS += \
./Application\ Layer/MainApp.o 

C_DEPS += \
./Application\ Layer/MainApp.d 


# Each subdirectory must supply rules for building sources it contributes
Application\ Layer/MainApp.o: D:/MyFiles/Embedded_Systems/Embedded_Systems\ _CPP/My_Projects/Main\ Project/Application\ Layer/MainApp.c Application\ Layer/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL/GPIO" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL/RCC" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/Utils" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/Application Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application Layer/MainApp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-20-Layer

clean-Application-20-Layer:
	-$(RM) ./Application\ Layer/MainApp.cyclo ./Application\ Layer/MainApp.d ./Application\ Layer/MainApp.o ./Application\ Layer/MainApp.su

.PHONY: clean-Application-20-Layer


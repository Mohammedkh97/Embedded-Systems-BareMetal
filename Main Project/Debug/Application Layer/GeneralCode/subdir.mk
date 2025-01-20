################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application\ Layer/GeneralCode/MainApp.c 

OBJS += \
./Application\ Layer/GeneralCode/MainApp.o 

C_DEPS += \
./Application\ Layer/GeneralCode/MainApp.d 


# Each subdirectory must supply rules for building sources it contributes
Application\ Layer/GeneralCode/MainApp.o: ../Application\ Layer/GeneralCode/MainApp.c Application\ Layer/GeneralCode/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL/GPIO" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL/RCC" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/Utils" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/Application Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application Layer/GeneralCode/MainApp.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-20-Layer-2f-GeneralCode

clean-Application-20-Layer-2f-GeneralCode:
	-$(RM) ./Application\ Layer/GeneralCode/MainApp.cyclo ./Application\ Layer/GeneralCode/MainApp.d ./Application\ Layer/GeneralCode/MainApp.o ./Application\ Layer/GeneralCode/MainApp.su

.PHONY: clean-Application-20-Layer-2f-GeneralCode


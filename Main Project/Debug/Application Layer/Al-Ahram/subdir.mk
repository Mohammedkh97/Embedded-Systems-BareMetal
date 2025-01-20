################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Application\ Layer/Al-Ahram/Al-Ahram.c 

OBJS += \
./Application\ Layer/Al-Ahram/Al-Ahram.o 

C_DEPS += \
./Application\ Layer/Al-Ahram/Al-Ahram.d 


# Each subdirectory must supply rules for building sources it contributes
Application\ Layer/Al-Ahram/Al-Ahram.o: ../Application\ Layer/Al-Ahram/Al-Ahram.c Application\ Layer/Al-Ahram/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL/GPIO" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL/RCC" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/Utils" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/Application Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application Layer/Al-Ahram/Al-Ahram.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Application-20-Layer-2f-Al-2d-Ahram

clean-Application-20-Layer-2f-Al-2d-Ahram:
	-$(RM) ./Application\ Layer/Al-Ahram/Al-Ahram.cyclo ./Application\ Layer/Al-Ahram/Al-Ahram.d ./Application\ Layer/Al-Ahram/Al-Ahram.o ./Application\ Layer/Al-Ahram/Al-Ahram.su

.PHONY: clean-Application-20-Layer-2f-Al-2d-Ahram


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCAL/USART/USART_Configuration.c \
../MCAL/USART/USART_Program.c 

OBJS += \
./MCAL/USART/USART_Configuration.o \
./MCAL/USART/USART_Program.o 

C_DEPS += \
./MCAL/USART/USART_Configuration.d \
./MCAL/USART/USART_Program.d 


# Each subdirectory must supply rules for building sources it contributes
MCAL/USART/%.o MCAL/USART/%.su MCAL/USART/%.cyclo: ../MCAL/USART/%.c MCAL/USART/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL/GPIO" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/MCAL/RCC" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/Utils" -I"D:/MyFiles/Embedded_Systems/Embedded_Systems _CPP/My_Projects/Main Project/Application Layer" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MCAL-2f-USART

clean-MCAL-2f-USART:
	-$(RM) ./MCAL/USART/USART_Configuration.cyclo ./MCAL/USART/USART_Configuration.d ./MCAL/USART/USART_Configuration.o ./MCAL/USART/USART_Configuration.su ./MCAL/USART/USART_Program.cyclo ./MCAL/USART/USART_Program.d ./MCAL/USART/USART_Program.o ./MCAL/USART/USART_Program.su

.PHONY: clean-MCAL-2f-USART


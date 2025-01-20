################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/KeyPad.c \
../HAL/LCD.c \
../HAL/Sensors.c \
../HAL/Stepper.c \
../HAL/servo.c \
../HAL/ultrasonic.c 

OBJS += \
./HAL/KeyPad.o \
./HAL/LCD.o \
./HAL/Sensors.o \
./HAL/Stepper.o \
./HAL/servo.o \
./HAL/ultrasonic.o 

C_DEPS += \
./HAL/KeyPad.d \
./HAL/LCD.d \
./HAL/Sensors.d \
./HAL/Stepper.d \
./HAL/servo.d \
./HAL/ultrasonic.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o: ../HAL/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -I"F:\WorkSpaces\Workspace_Eclipse\MB2_Scheduler" -I"F:\WorkSpaces\Workspace_Eclipse\MB2_Scheduler\HAL" -I"F:\WorkSpaces\Workspace_Eclipse\MB2_Scheduler\MCAL" -I"F:\WorkSpaces\Workspace_Eclipse\MB2_Scheduler\Scheduler" -I"F:\WorkSpaces\Workspace_Eclipse\MB2_Scheduler\SERVICES" -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



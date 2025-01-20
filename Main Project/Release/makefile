################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Services/USART_Services/subdir.mk
-include Private/String/subdir.mk
-include Private/Delay/subdir.mk
-include Private/App_Services/subdir.mk
-include MCAL/USART/subdir.mk
-include MCAL/SysTick/subdir.mk
-include MCAL/SPI/subdir.mk
-include MCAL/RCC/subdir.mk
-include MCAL/GPIO/subdir.mk
-include MCAL/EXTI/subdir.mk
-include MCAL/AFIO/subdir.mk
-include HAL/RFID2/subdir.mk
-include HAL/RFID/subdir.mk
-include HAL/Liquid\ Crystal\ Display/subdir.mk
-include HAL/LCD_TFT_ST7789v/subdir.mk
-include HAL/KEYPAD/subdir.mk
-include HAL/HX711/subdir.mk
-include HAL/GLCD_ST7920/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Application\ Layer/Magzer_BarCode/subdir.mk
-include Application\ Layer/GeneralCode/subdir.mk
-include Application\ Layer/Al-Ahram/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := Main Project
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Main\ Project.elf \

MAP_FILES += \
Main\ Project.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Main\ Project.list \

OBJCOPY_HEX += \
Main\ Project.hex \

OBJCOPY_VERILOG += \
Main\ Project.verilog \

OBJCOPY_SREC += \
Main\ Project.srec \


# All Target
all: main-build

# Main-build Target
main-build: Main\ Project.elf secondary-outputs

# Tool invocations
Main\ Project.elf Main\ Project.map: $(OBJS) $(USER_OBJS) D:\MyFiles\Embedded\ Systems\STM32\Main\ Project\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "Main Project.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"D:\MyFiles\Embedded Systems\STM32\Main Project\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Main Project.map" -Wl,--gc-sections -static -L"D:\MyFiles\Embedded_Systems\Embedded_Systems _CPP\My_Projects\Main Project\Private\String" --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Main\ Project.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Main Project.list"
	@echo 'Finished building: $@'
	@echo ' '

Main\ Project.hex: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Main Project.hex"
	@echo 'Finished building: $@'
	@echo ' '

Main\ Project.verilog: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O verilog $(EXECUTABLES) "Main Project.verilog"
	@echo 'Finished building: $@'
	@echo ' '

Main\ Project.srec: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O srec $(EXECUTABLES) "Main Project.srec"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) Main\ Project.elf Main\ Project.hex Main\ Project.list Main\ Project.map Main\ Project.srec Main\ Project.verilog Main\\ Project.elf default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_VERILOG) $(OBJCOPY_SREC)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Z_RTOS/subdir.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include subdir.mk
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

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
U15_Z-RTOS_Session_5.axf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
U15_Z-RTOS_Session_5.list \

OBJCOPY_BIN += \
U15_Z-RTOS_Session_5.bin \


# All Target
all: U15_Z-RTOS_Session_5.axf secondary-outputs

# Tool invocations
U15_Z-RTOS_Session_5.axf: $(OBJS) $(USER_OBJS) C:\Users\hesham\ mohamed\STM32CubeIDE\workspace_2_1.4.0\U15_Z-RTOS_Session_5\STM32F103C6TX_FLASH.ld
	arm-none-eabi-gcc -gdwarf-2 -o "U15_Z-RTOS_Session_5.axf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\Users\hesham mohamed\STM32CubeIDE\workspace_2_1.4.0\U15_Z-RTOS_Session_5\STM32F103C6TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="U15_Z-RTOS_Session_5.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

U15_Z-RTOS_Session_5.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "U15_Z-RTOS_Session_5.list"
	@echo 'Finished building: $@'
	@echo ' '

U15_Z-RTOS_Session_5.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "U15_Z-RTOS_Session_5.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

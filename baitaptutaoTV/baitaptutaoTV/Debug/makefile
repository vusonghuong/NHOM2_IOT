################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
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


BUILD_ARTIFACT_NAME := baitaptutaoTV
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
baitaptutaoTV.elf \

MAP_FILES += \
baitaptutaoTV.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
baitaptutaoTV.list \


# All Target
all: main-build

# Main-build Target
main-build: baitaptutaoTV.elf secondary-outputs

# Tool invocations
baitaptutaoTV.elf baitaptutaoTV.map: $(OBJS) $(USER_OBJS) C:\Users\hauho\STM32CubeIDE\workspace_1.15.0\baitaptutaoTV\STM32F401RETX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "baitaptutaoTV.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\hauho\STM32CubeIDE\workspace_1.15.0\baitaptutaoTV\STM32F401RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="baitaptutaoTV.map" -Wl,--gc-sections -static -L"C:\Users\hauho\Downloads\IOT-Programming-with-Master-Embedded-773df849394c85dc7b3938106d0abe7e95302a84\IOT-Programming-with-Master-Embedded-773df849394c85dc7b3938106d0abe7e95302a84\Courseware 2\SDK_1.0.3_NUCLEO-F401RE\SDK_1.0.3_NUCLEO-F401RE\lib_stm" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

baitaptutaoTV.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "baitaptutaoTV.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) baitaptutaoTV.elf baitaptutaoTV.list baitaptutaoTV.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

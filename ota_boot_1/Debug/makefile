################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include bsw/utils/subdir.mk
-include bsw/ota/subdir.mk
-include bsw/mcal/uds/server/subdir.mk
-include bsw/mcal/uart2/subdir.mk
-include bsw/mcal/tp/subdir.mk
-include bsw/mcal/com/subdir.mk
-include bsw/mcal/can/subdir.mk
-include bsw/dcm/subdir.mk
-include Drivers/STM32F1xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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


BUILD_ARTIFACT_NAME := ota_boot_1
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
ota_boot_1.elf \

MAP_FILES += \
ota_boot_1.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
ota_boot_1.list \

OBJCOPY_BIN += \
ota_boot_1.bin \


# All Target
all: main-build

# Main-build Target
main-build: ota_boot_1.elf secondary-outputs

# Tool invocations
ota_boot_1.elf ota_boot_1.map: $(OBJS) $(USER_OBJS) C:\D\Bico\Virtual_Machine\bico_ubuntu_22_04_3\Shared_Folder\stm32CubeIDE\ota\ota_boot_1\STM32F103C8TX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "ota_boot_1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m3 -T"C:\D\Bico\Virtual_Machine\bico_ubuntu_22_04_3\Shared_Folder\stm32CubeIDE\ota\ota_boot_1\STM32F103C8TX_FLASH.ld" --specs=nosys.specs -Wl,-Map="ota_boot_1.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

ota_boot_1.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "ota_boot_1.list"
	@echo 'Finished building: $@'
	@echo ' '

ota_boot_1.bin: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "ota_boot_1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) default.size.stdout ota_boot_1.bin ota_boot_1.elf ota_boot_1.list ota_boot_1.map
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets

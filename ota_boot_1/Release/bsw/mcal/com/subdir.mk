################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsw/mcal/com/com_proc.c 

OBJS += \
./bsw/mcal/com/com_proc.o 

C_DEPS += \
./bsw/mcal/com/com_proc.d 


# Each subdirectory must supply rules for building sources it contributes
bsw/mcal/com/%.o bsw/mcal/com/%.su bsw/mcal/com/%.cyclo: ../bsw/mcal/com/%.c bsw/mcal/com/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DUDS_SYS=UDS_SYS_CUSTOM -DUDS_TP_ISOTP_C -DUDS_CUSTOM_MILLIS -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/D/Bico/Virtual_Machine/bico_ubuntu_22_04_3/Shared_Folder/stm32CubeIDE/ota/ota_boot_1/bsw" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsw-2f-mcal-2f-com

clean-bsw-2f-mcal-2f-com:
	-$(RM) ./bsw/mcal/com/com_proc.cyclo ./bsw/mcal/com/com_proc.d ./bsw/mcal/com/com_proc.o ./bsw/mcal/com/com_proc.su

.PHONY: clean-bsw-2f-mcal-2f-com


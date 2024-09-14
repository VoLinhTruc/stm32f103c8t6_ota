################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsw/utils/circular_buffer.c \
../bsw/utils/flash_handling.c \
../bsw/utils/us_memcpy.c 

OBJS += \
./bsw/utils/circular_buffer.o \
./bsw/utils/flash_handling.o \
./bsw/utils/us_memcpy.o 

C_DEPS += \
./bsw/utils/circular_buffer.d \
./bsw/utils/flash_handling.d \
./bsw/utils/us_memcpy.d 


# Each subdirectory must supply rules for building sources it contributes
bsw/utils/%.o bsw/utils/%.su bsw/utils/%.cyclo: ../bsw/utils/%.c bsw/utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DUDS_SYS=UDS_SYS_CUSTOM -DUDS_TP_ISOTP_C -DUDS_CUSTOM_MILLIS -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/D/Bico/Virtual_Machine/bico_ubuntu_22_04_3/Shared_Folder/stm32CubeIDE/ota/ota_boot/bsw" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsw-2f-utils

clean-bsw-2f-utils:
	-$(RM) ./bsw/utils/circular_buffer.cyclo ./bsw/utils/circular_buffer.d ./bsw/utils/circular_buffer.o ./bsw/utils/circular_buffer.su ./bsw/utils/flash_handling.cyclo ./bsw/utils/flash_handling.d ./bsw/utils/flash_handling.o ./bsw/utils/flash_handling.su ./bsw/utils/us_memcpy.cyclo ./bsw/utils/us_memcpy.d ./bsw/utils/us_memcpy.o ./bsw/utils/us_memcpy.su

.PHONY: clean-bsw-2f-utils


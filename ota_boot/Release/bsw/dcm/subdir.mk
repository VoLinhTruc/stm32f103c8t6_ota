################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsw/dcm/dcm.c 

OBJS += \
./bsw/dcm/dcm.o 

C_DEPS += \
./bsw/dcm/dcm.d 


# Each subdirectory must supply rules for building sources it contributes
bsw/dcm/%.o bsw/dcm/%.su bsw/dcm/%.cyclo: ../bsw/dcm/%.c bsw/dcm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DUDS_SYS=UDS_SYS_CUSTOM -DUDS_TP_ISOTP_C -DUDS_CUSTOM_MILLIS -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/D/Bico/Virtual_Machine/bico_ubuntu_22_04_3/Shared_Folder/stm32CubeIDE/ota/ota_boot/bsw" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsw-2f-dcm

clean-bsw-2f-dcm:
	-$(RM) ./bsw/dcm/dcm.cyclo ./bsw/dcm/dcm.d ./bsw/dcm/dcm.o ./bsw/dcm/dcm.su

.PHONY: clean-bsw-2f-dcm


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsw/mcal/tp/isotp.c 

OBJS += \
./bsw/mcal/tp/isotp.o 

C_DEPS += \
./bsw/mcal/tp/isotp.d 


# Each subdirectory must supply rules for building sources it contributes
bsw/mcal/tp/%.o bsw/mcal/tp/%.su bsw/mcal/tp/%.cyclo: ../bsw/mcal/tp/%.c bsw/mcal/tp/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DUDS_SYS=UDS_SYS_CUSTOM -DUDS_TP_ISOTP_C -DUDS_CUSTOM_MILLIS -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/D/Bico/Virtual_Machine/bico_ubuntu_22_04_3/Shared_Folder/stm32CubeIDE/ota/ota_boot/bsw" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsw-2f-mcal-2f-tp

clean-bsw-2f-mcal-2f-tp:
	-$(RM) ./bsw/mcal/tp/isotp.cyclo ./bsw/mcal/tp/isotp.d ./bsw/mcal/tp/isotp.o ./bsw/mcal/tp/isotp.su

.PHONY: clean-bsw-2f-mcal-2f-tp


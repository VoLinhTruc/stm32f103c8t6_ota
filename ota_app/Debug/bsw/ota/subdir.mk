################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsw/ota/ota.c 

OBJS += \
./bsw/ota/ota.o 

C_DEPS += \
./bsw/ota/ota.d 


# Each subdirectory must supply rules for building sources it contributes
bsw/ota/%.o bsw/ota/%.su bsw/ota/%.cyclo: ../bsw/ota/%.c bsw/ota/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUDS_SYS=UDS_SYS_CUSTOM -DUDS_TP_ISOTP_C -DUDS_CUSTOM_MILLIS -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/D/Bico/Virtual_Machine/bico_ubuntu_22_04_3/Shared_Folder/stm32CubeIDE/ota/ota_app/bsw" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsw-2f-ota

clean-bsw-2f-ota:
	-$(RM) ./bsw/ota/ota.cyclo ./bsw/ota/ota.d ./bsw/ota/ota.o ./bsw/ota/ota.su

.PHONY: clean-bsw-2f-ota


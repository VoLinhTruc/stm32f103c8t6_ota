################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bsw/mcal/uds/server/uds_server.c 

OBJS += \
./bsw/mcal/uds/server/uds_server.o 

C_DEPS += \
./bsw/mcal/uds/server/uds_server.d 


# Each subdirectory must supply rules for building sources it contributes
bsw/mcal/uds/server/%.o bsw/mcal/uds/server/%.su bsw/mcal/uds/server/%.cyclo: ../bsw/mcal/uds/server/%.c bsw/mcal/uds/server/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DUDS_SYS=UDS_SYS_CUSTOM -DUDS_TP_ISOTP_C -DUDS_CUSTOM_MILLIS -DSTM32F103xB -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/D/Bico/Virtual_Machine/bico_ubuntu_22_04_3/Shared_Folder/stm32CubeIDE/ota/ota_boot_1/bsw" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-bsw-2f-mcal-2f-uds-2f-server

clean-bsw-2f-mcal-2f-uds-2f-server:
	-$(RM) ./bsw/mcal/uds/server/uds_server.cyclo ./bsw/mcal/uds/server/uds_server.d ./bsw/mcal/uds/server/uds_server.o ./bsw/mcal/uds/server/uds_server.su

.PHONY: clean-bsw-2f-mcal-2f-uds-2f-server


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01.c 

OBJS += \
./Drivers/BSP/stm32l475e_iot01.o 

C_DEPS += \
./Drivers/BSP/stm32l475e_iot01.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/stm32l475e_iot01.o: /home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Drivers/BSP/B-L475E-IOT01/stm32l475e_iot01.c Drivers/BSP/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DRFU '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -DUSE_HAL_DRIVER -DSENSOR -DENABLE_IOT_ERROR '-DMQTTCLIENT_PLATFORM_HEADER=MQTTCMSIS.h' -DSTM32L475xx -DENABLE_IOT_INFO -c -I../../Inc -I/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Drivers/STM32L4xx_HAL_Driver/Src -I/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/hx8347g -I../../../../../../../Drivers/BSP/B-L475E-IOT01 -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../../../Utilities/Log -I"/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Projects/B-L475E-IOT01A/Applications/USB_Host/MSC_Standalone/STM32CubeIDE/Drivers/STM32L4xx_HAL_Driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP

clean-Drivers-2f-BSP:
	-$(RM) ./Drivers/BSP/stm32l475e_iot01.cyclo ./Drivers/BSP/stm32l475e_iot01.d ./Drivers/BSP/stm32l475e_iot01.o ./Drivers/BSP/stm32l475e_iot01.su

.PHONY: clean-Drivers-2f-BSP


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/Third_Party/FatFs/src/option/syscall.c \
/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/Third_Party/FatFs/src/option/unicode.c 

OBJS += \
./Middlewares/FatFs/Option/syscall.o \
./Middlewares/FatFs/Option/unicode.o 

C_DEPS += \
./Middlewares/FatFs/Option/syscall.d \
./Middlewares/FatFs/Option/unicode.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FatFs/Option/syscall.o: /home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/Third_Party/FatFs/src/option/syscall.c Middlewares/FatFs/Option/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DRFU '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -DUSE_HAL_DRIVER -DSENSOR -DENABLE_IOT_ERROR '-DMQTTCLIENT_PLATFORM_HEADER=MQTTCMSIS.h' -DSTM32L475xx -DENABLE_IOT_INFO -c -I../../Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/hx8347g -I../../../../../../../Drivers/BSP/B-L475E-IOT01 -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../../../Utilities/Log -I"/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Projects/B-L475E-IOT01A/Applications/USB_Host/MSC_Standalone/STM32CubeIDE/Drivers/STM32L4xx_HAL_Driver" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FatFs/Option/unicode.o: /home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/Third_Party/FatFs/src/option/unicode.c Middlewares/FatFs/Option/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DRFU '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -DUSE_HAL_DRIVER -DSENSOR -DENABLE_IOT_ERROR '-DMQTTCLIENT_PLATFORM_HEADER=MQTTCMSIS.h' -DSTM32L475xx -DENABLE_IOT_INFO -c -I../../Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/hx8347g -I../../../../../../../Drivers/BSP/B-L475E-IOT01 -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../../../Utilities/Log -I"/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Projects/B-L475E-IOT01A/Applications/USB_Host/MSC_Standalone/STM32CubeIDE/Drivers/STM32L4xx_HAL_Driver" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FatFs-2f-Option

clean-Middlewares-2f-FatFs-2f-Option:
	-$(RM) ./Middlewares/FatFs/Option/syscall.cyclo ./Middlewares/FatFs/Option/syscall.d ./Middlewares/FatFs/Option/syscall.o ./Middlewares/FatFs/Option/syscall.su ./Middlewares/FatFs/Option/unicode.cyclo ./Middlewares/FatFs/Option/unicode.d ./Middlewares/FatFs/Option/unicode.o ./Middlewares/FatFs/Option/unicode.su

.PHONY: clean-Middlewares-2f-FatFs-2f-Option


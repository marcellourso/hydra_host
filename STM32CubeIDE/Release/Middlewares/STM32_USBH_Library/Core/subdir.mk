################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c \
/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c \
/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c \
/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c 

OBJS += \
./Middlewares/STM32_USBH_Library/Core/usbh_core.o \
./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.o \
./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.o \
./Middlewares/STM32_USBH_Library/Core/usbh_pipes.o 

C_DEPS += \
./Middlewares/STM32_USBH_Library/Core/usbh_core.d \
./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.d \
./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.d \
./Middlewares/STM32_USBH_Library/Core/usbh_pipes.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/STM32_USBH_Library/Core/usbh_core.o: /home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_core.c Middlewares/STM32_USBH_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DRFU '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -DUSE_HAL_DRIVER -DSENSOR -DENABLE_IOT_ERROR '-DMQTTCLIENT_PLATFORM_HEADER=MQTTCMSIS.h' -DSTM32L475xx -DENABLE_IOT_INFO -c -I../../Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/hx8347g -I../../../../../../../Drivers/BSP/B-L475E-IOT01 -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../../../Utilities/Log -I"/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Projects/B-L475E-IOT01A/Applications/USB_Host/MSC_Standalone/STM32CubeIDE/Drivers/STM32L4xx_HAL_Driver" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.o: /home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ctlreq.c Middlewares/STM32_USBH_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DRFU '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -DUSE_HAL_DRIVER -DSENSOR -DENABLE_IOT_ERROR '-DMQTTCLIENT_PLATFORM_HEADER=MQTTCMSIS.h' -DSTM32L475xx -DENABLE_IOT_INFO -c -I../../Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/hx8347g -I../../../../../../../Drivers/BSP/B-L475E-IOT01 -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../../../Utilities/Log -I"/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Projects/B-L475E-IOT01A/Applications/USB_Host/MSC_Standalone/STM32CubeIDE/Drivers/STM32L4xx_HAL_Driver" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Core/usbh_ioreq.o: /home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_ioreq.c Middlewares/STM32_USBH_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DRFU '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -DUSE_HAL_DRIVER -DSENSOR -DENABLE_IOT_ERROR '-DMQTTCLIENT_PLATFORM_HEADER=MQTTCMSIS.h' -DSTM32L475xx -DENABLE_IOT_INFO -c -I../../Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/hx8347g -I../../../../../../../Drivers/BSP/B-L475E-IOT01 -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../../../Utilities/Log -I"/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Projects/B-L475E-IOT01A/Applications/USB_Host/MSC_Standalone/STM32CubeIDE/Drivers/STM32L4xx_HAL_Driver" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/STM32_USBH_Library/Core/usbh_pipes.o: /home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Middlewares/ST/STM32_USB_Host_Library/Core/Src/usbh_pipes.c Middlewares/STM32_USBH_Library/Core/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -DRFU '-DMBEDTLS_CONFIG_FILE=<mbedtls_config.h>' -DUSE_HAL_DRIVER -DSENSOR -DENABLE_IOT_ERROR '-DMQTTCLIENT_PLATFORM_HEADER=MQTTCMSIS.h' -DSTM32L475xx -DENABLE_IOT_INFO -c -I../../Inc -I../../../../../../../Drivers/CMSIS/Include -I../../../../../../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../../../../../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../../../../../../Drivers/BSP/Components/hx8347g -I../../../../../../../Drivers/BSP/B-L475E-IOT01 -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../../../../../../../Middlewares/ST/STM32_USB_Host_Library/Class/MSC/Inc -I../../../../../../../Middlewares/Third_Party/FatFs/src -I../../../../../../../Middlewares/Third_Party/FatFs/src/drivers -I../../../../../../../Utilities/Log -I"/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Projects/B-L475E-IOT01A/Applications/USB_Host/MSC_Standalone/STM32CubeIDE/Drivers/STM32L4xx_HAL_Driver" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-STM32_USBH_Library-2f-Core

clean-Middlewares-2f-STM32_USBH_Library-2f-Core:
	-$(RM) ./Middlewares/STM32_USBH_Library/Core/usbh_core.cyclo ./Middlewares/STM32_USBH_Library/Core/usbh_core.d ./Middlewares/STM32_USBH_Library/Core/usbh_core.o ./Middlewares/STM32_USBH_Library/Core/usbh_core.su ./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.cyclo ./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.d ./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.o ./Middlewares/STM32_USBH_Library/Core/usbh_ctlreq.su ./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.cyclo ./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.d ./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.o ./Middlewares/STM32_USBH_Library/Core/usbh_ioreq.su ./Middlewares/STM32_USBH_Library/Core/usbh_pipes.cyclo ./Middlewares/STM32_USBH_Library/Core/usbh_pipes.d ./Middlewares/STM32_USBH_Library/Core/usbh_pipes.o ./Middlewares/STM32_USBH_Library/Core/usbh_pipes.su

.PHONY: clean-Middlewares-2f-STM32_USBH_Library-2f-Core


################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Application/Startup/startup_stm32l475vgtx.s 

OBJS += \
./Application/Startup/startup_stm32l475vgtx.o 

S_DEPS += \
./Application/Startup/startup_stm32l475vgtx.d 


# Each subdirectory must supply rules for building sources it contributes
Application/Startup/%.o: ../Application/Startup/%.s Application/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -c -I"/home/marcello/STM32CubeIDE/workspace_1.13.1/STM32CubeL4/Projects/B-L475E-IOT01A/Applications/USB_Host/MSC_Standalone/STM32CubeIDE/Drivers/STM32L4xx_HAL_Driver" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Application-2f-Startup

clean-Application-2f-Startup:
	-$(RM) ./Application/Startup/startup_stm32l475vgtx.d ./Application/Startup/startup_stm32l475vgtx.o

.PHONY: clean-Application-2f-Startup


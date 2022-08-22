################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utils/cobs.c \
../Utils/ringBuffer.c 

OBJS += \
./Utils/cobs.o \
./Utils/ringBuffer.o 

C_DEPS += \
./Utils/cobs.d \
./Utils/ringBuffer.d 


# Each subdirectory must supply rules for building sources it contributes
Utils/%.o Utils/%.su: ../Utils/%.c Utils/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/NDC/Desktop/conc_test/Utils" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS/include" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS/portable/MemMang" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Utils

clean-Utils:
	-$(RM) ./Utils/cobs.d ./Utils/cobs.o ./Utils/cobs.su ./Utils/ringBuffer.d ./Utils/ringBuffer.o ./Utils/ringBuffer.su

.PHONY: clean-Utils


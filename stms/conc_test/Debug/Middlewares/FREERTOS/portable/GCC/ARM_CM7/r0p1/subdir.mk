################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1/port.c 

OBJS += \
./Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1/port.o 

C_DEPS += \
./Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1/%.o Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1/%.su: ../Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1/%.c Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/NDC/Desktop/conc_test/Utils" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS/include" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS/portable/MemMang" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FREERTOS-2f-portable-2f-GCC-2f-ARM_CM7-2f-r0p1

clean-Middlewares-2f-FREERTOS-2f-portable-2f-GCC-2f-ARM_CM7-2f-r0p1:
	-$(RM) ./Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1/port.d ./Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1/port.o ./Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1/port.su

.PHONY: clean-Middlewares-2f-FREERTOS-2f-portable-2f-GCC-2f-ARM_CM7-2f-r0p1


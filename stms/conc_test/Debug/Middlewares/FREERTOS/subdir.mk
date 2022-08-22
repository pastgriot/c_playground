################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FREERTOS/croutine.c \
../Middlewares/FREERTOS/event_groups.c \
../Middlewares/FREERTOS/list.c \
../Middlewares/FREERTOS/queue.c \
../Middlewares/FREERTOS/stream_buffer.c \
../Middlewares/FREERTOS/tasks.c \
../Middlewares/FREERTOS/timers.c 

OBJS += \
./Middlewares/FREERTOS/croutine.o \
./Middlewares/FREERTOS/event_groups.o \
./Middlewares/FREERTOS/list.o \
./Middlewares/FREERTOS/queue.o \
./Middlewares/FREERTOS/stream_buffer.o \
./Middlewares/FREERTOS/tasks.o \
./Middlewares/FREERTOS/timers.o 

C_DEPS += \
./Middlewares/FREERTOS/croutine.d \
./Middlewares/FREERTOS/event_groups.d \
./Middlewares/FREERTOS/list.d \
./Middlewares/FREERTOS/queue.d \
./Middlewares/FREERTOS/stream_buffer.d \
./Middlewares/FREERTOS/tasks.d \
./Middlewares/FREERTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FREERTOS/%.o Middlewares/FREERTOS/%.su: ../Middlewares/FREERTOS/%.c Middlewares/FREERTOS/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I"C:/Users/NDC/Desktop/conc_test/Utils" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS/include" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS/portable/GCC/ARM_CM7/r0p1" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS/portable/MemMang" -I"C:/Users/NDC/Desktop/conc_test/Middlewares/FREERTOS" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../USB_DEVICE/App -I../USB_DEVICE/Target -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-FREERTOS

clean-Middlewares-2f-FREERTOS:
	-$(RM) ./Middlewares/FREERTOS/croutine.d ./Middlewares/FREERTOS/croutine.o ./Middlewares/FREERTOS/croutine.su ./Middlewares/FREERTOS/event_groups.d ./Middlewares/FREERTOS/event_groups.o ./Middlewares/FREERTOS/event_groups.su ./Middlewares/FREERTOS/list.d ./Middlewares/FREERTOS/list.o ./Middlewares/FREERTOS/list.su ./Middlewares/FREERTOS/queue.d ./Middlewares/FREERTOS/queue.o ./Middlewares/FREERTOS/queue.su ./Middlewares/FREERTOS/stream_buffer.d ./Middlewares/FREERTOS/stream_buffer.o ./Middlewares/FREERTOS/stream_buffer.su ./Middlewares/FREERTOS/tasks.d ./Middlewares/FREERTOS/tasks.o ./Middlewares/FREERTOS/tasks.su ./Middlewares/FREERTOS/timers.d ./Middlewares/FREERTOS/timers.o ./Middlewares/FREERTOS/timers.su

.PHONY: clean-Middlewares-2f-FREERTOS


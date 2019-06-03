################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Third-party/FreeRTOS/org/Source/croutine.c \
../Third-party/FreeRTOS/org/Source/event_groups.c \
../Third-party/FreeRTOS/org/Source/list.c \
../Third-party/FreeRTOS/org/Source/queue.c \
../Third-party/FreeRTOS/org/Source/stream_buffer.c \
../Third-party/FreeRTOS/org/Source/tasks.c \
../Third-party/FreeRTOS/org/Source/timers.c 

OBJS += \
./Third-party/FreeRTOS/org/Source/croutine.o \
./Third-party/FreeRTOS/org/Source/event_groups.o \
./Third-party/FreeRTOS/org/Source/list.o \
./Third-party/FreeRTOS/org/Source/queue.o \
./Third-party/FreeRTOS/org/Source/stream_buffer.o \
./Third-party/FreeRTOS/org/Source/tasks.o \
./Third-party/FreeRTOS/org/Source/timers.o 

C_DEPS += \
./Third-party/FreeRTOS/org/Source/croutine.d \
./Third-party/FreeRTOS/org/Source/event_groups.d \
./Third-party/FreeRTOS/org/Source/list.d \
./Third-party/FreeRTOS/org/Source/queue.d \
./Third-party/FreeRTOS/org/Source/stream_buffer.d \
./Third-party/FreeRTOS/org/Source/tasks.d \
./Third-party/FreeRTOS/org/Source/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Third-party/FreeRTOS/org/Source/%.o: ../Third-party/FreeRTOS/org/Source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32 -DSTM32F4 -DSTM32F407VGTx -DSTM32F407G_DISC1 -DDEBUG -DSTM32F40XX -DSTM32F40_41xxx -DUSE_STDPERIPH_DRIVER -I"C:/Users/Zeljko/workspace/RTOS_workspace/STM32_project/StdPeriph_Driver/inc" -I"C:/Users/Zeljko/workspace/RTOS_workspace/STM32_project/Third-party/FreeRTOS/org" -I"C:/Users/Zeljko/workspace/RTOS_workspace/STM32_project/Config" -I"C:/Users/Zeljko/workspace/RTOS_workspace/STM32_project/Third-party/FreeRTOS/org/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Zeljko/workspace/RTOS_workspace/STM32_project/Third-party/FreeRTOS/org/Source/include" -I"C:/Users/Zeljko/workspace/RTOS_workspace/STM32_project/inc" -I"C:/Users/Zeljko/workspace/RTOS_workspace/STM32_project/CMSIS/device" -I"C:/Users/Zeljko/workspace/RTOS_workspace/STM32_project/CMSIS/core" -O0 -g3 -Wall -fmessage-length=0 -ffunction-sections -c -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



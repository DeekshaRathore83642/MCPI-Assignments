################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Inc/itm.c \
../Inc/led.c \
../Inc/main.c \
../Inc/syscalls.c \
../Inc/sysmem.c \
../Inc/system_stm32f4xx.c \
../Inc/timer.c 

OBJS += \
./Inc/itm.o \
./Inc/led.o \
./Inc/main.o \
./Inc/syscalls.o \
./Inc/sysmem.o \
./Inc/system_stm32f4xx.o \
./Inc/timer.o 

C_DEPS += \
./Inc/itm.d \
./Inc/led.d \
./Inc/main.d \
./Inc/syscalls.d \
./Inc/sysmem.d \
./Inc/system_stm32f4xx.d \
./Inc/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Inc/%.o Inc/%.su Inc/%.cyclo: ../Inc/%.c Inc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F407G_DISC1 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Inc

clean-Inc:
	-$(RM) ./Inc/itm.cyclo ./Inc/itm.d ./Inc/itm.o ./Inc/itm.su ./Inc/led.cyclo ./Inc/led.d ./Inc/led.o ./Inc/led.su ./Inc/main.cyclo ./Inc/main.d ./Inc/main.o ./Inc/main.su ./Inc/syscalls.cyclo ./Inc/syscalls.d ./Inc/syscalls.o ./Inc/syscalls.su ./Inc/sysmem.cyclo ./Inc/sysmem.d ./Inc/sysmem.o ./Inc/sysmem.su ./Inc/system_stm32f4xx.cyclo ./Inc/system_stm32f4xx.d ./Inc/system_stm32f4xx.o ./Inc/system_stm32f4xx.su ./Inc/timer.cyclo ./Inc/timer.d ./Inc/timer.o ./Inc/timer.su

.PHONY: clean-Inc


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/log.c \
../src/main.c \
../src/montgomery.c \
../src/mp_arith.c \
../src/mp_print.c \
../src/platform.c 

S_UPPER_SRCS += \
../src/asm_func.S 

OBJS += \
./src/asm_func.o \
./src/log.o \
./src/main.o \
./src/montgomery.o \
./src/mp_arith.o \
./src/mp_print.o \
./src/platform.o 

S_UPPER_DEPS += \
./src/asm_func.d 

C_DEPS += \
./src/log.d \
./src/main.d \
./src/montgomery.d \
./src/mp_arith.d \
./src/mp_print.d \
./src/platform.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../helloworld_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../helloworld_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../oldsrc/lscript.ld 

C_SRCS += \
../oldsrc/log.c \
../oldsrc/main.c \
../oldsrc/montgomery.c \
../oldsrc/mp_arith.c \
../oldsrc/mp_print.c \
../oldsrc/platform.c 

S_UPPER_SRCS += \
../oldsrc/asm_func.S 

OBJS += \
./oldsrc/asm_func.o \
./oldsrc/log.o \
./oldsrc/main.o \
./oldsrc/montgomery.o \
./oldsrc/mp_arith.o \
./oldsrc/mp_print.o \
./oldsrc/platform.o 

S_UPPER_DEPS += \
./oldsrc/asm_func.d 

C_DEPS += \
./oldsrc/log.d \
./oldsrc/main.d \
./oldsrc/montgomery.d \
./oldsrc/mp_arith.d \
./oldsrc/mp_print.d \
./oldsrc/platform.d 


# Each subdirectory must supply rules for building sources it contributes
oldsrc/%.o: ../oldsrc/%.S
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../helloworld_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

oldsrc/%.o: ../oldsrc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../helloworld_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



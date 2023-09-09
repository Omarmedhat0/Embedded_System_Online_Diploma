################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DC_Motor.c \
../PWM_Timer0.c \
../buzzer.c \
../external_eeprom.c \
../gpio.c \
../i2c.c \
../microcontroller2.c \
../timer.c \
../uart.c 

OBJS += \
./DC_Motor.o \
./PWM_Timer0.o \
./buzzer.o \
./external_eeprom.o \
./gpio.o \
./i2c.o \
./microcontroller2.o \
./timer.o \
./uart.o 

C_DEPS += \
./DC_Motor.d \
./PWM_Timer0.d \
./buzzer.d \
./external_eeprom.d \
./gpio.d \
./i2c.d \
./microcontroller2.d \
./timer.d \
./uart.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



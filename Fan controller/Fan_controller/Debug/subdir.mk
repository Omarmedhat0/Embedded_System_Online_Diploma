################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DC_Motor.c \
../Fan_controller.c \
../PWM_Timer0.c \
../adc.c \
../gpio.c \
../lcd.c \
../lm35_sensor.c 

OBJS += \
./DC_Motor.o \
./Fan_controller.o \
./PWM_Timer0.o \
./adc.o \
./gpio.o \
./lcd.o \
./lm35_sensor.o 

C_DEPS += \
./DC_Motor.d \
./Fan_controller.d \
./PWM_Timer0.d \
./adc.d \
./gpio.d \
./lcd.d \
./lm35_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '



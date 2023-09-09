/******************************************************************************
 * Module: DC_Motor
 *
 * File Name : DC_Motor.c
 *
 * Description: Source file for the ATmega16 DC_Motor driver
 *
 * Author: Omar Medhat
 *
*******************************************************************************/
#include "DC_MOTOR.h"
#include "PWM_TIMER0.h"
#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use ICU/Timer1 Registers */
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the DC Motor 
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void)
{
	GPIO_setupPinDirection(DC_motor_PORT, DC_motor_PIN_1,PIN_OUTPUT); // Setup the first pin of motor direction as output pin
	GPIO_setupPinDirection(DC_motor_PORT, DC_motor_PIN_2,PIN_OUTPUT);// Setup the second pin of motor direction as output pin
	// Stop the DC-Motor at the beginning
	GPIO_writePin(DC_motor_PORT, DC_motor_PIN_1, LOGIC_LOW);
	GPIO_writePin(DC_motor_PORT, DC_motor_PIN_2, LOGIC_LOW);
}
/*
 * Description
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed)
{
	//Rotate Clockwise
	if (state==CW)
	{
		GPIO_writePin(DC_motor_PORT, DC_motor_PIN_1, LOGIC_LOW);
		GPIO_writePin(DC_motor_PORT, DC_motor_PIN_2, LOGIC_HIGH);
		PWM_Timer0_Start(speed);
	}
	//Rotate Anti-Clockwise
	else if(state==A_CW)
	{
		GPIO_writePin(DC_motor_PORT, DC_motor_PIN_1, LOGIC_HIGH);
		GPIO_writePin(DC_motor_PORT, DC_motor_PIN_2, LOGIC_LOW);
		PWM_Timer0_Start(speed);
	}
	// Stop Motor
	else if(state==stop)
	{
		GPIO_writePin(DC_motor_PORT, DC_motor_PIN_1, LOGIC_LOW);
		GPIO_writePin(DC_motor_PORT, DC_motor_PIN_2, LOGIC_LOW);
		PWM_Timer0_Start(speed);
	}
	else
	{
		/*  Do Nothing */
	}
}

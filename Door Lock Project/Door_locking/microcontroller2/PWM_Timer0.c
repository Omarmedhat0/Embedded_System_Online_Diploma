
 /******************************************************************************
 *
 * Module: PWM Timer
 *
 * File Name: PWM_Timer0.c
 *
 * Description: Source file for the AVR PWM Timer0 driver
 *
 * Author: Omar Medhat
 *
 *******************************************************************************/
#include "PWM_TIMER0.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "gpio.h"
#include <avr/io.h> /* To use Timer0 Registers */


/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Function to initialize the ICU driver
 * 	1. The function responsible for trigger the Timer0 with the PWM Mode.
 * 	2. Setup the PWM mode with Non-Inverting.
 * 	3. Setup the prescaler with F_CPU/8.
 * 	4. Setup the compare value based on the required input duty cycle
 *	5. Setup the direction for OC0 as output pin through the GPIO driver.
 *	6. The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 */
void PWM_Timer0_Start(uint8 duty_cycle)
{
	TCNT0 = 0; // duty_cycle
	OCR0  = ((float)duty_cycle / 100) * 255; // Set Compare Value
	// Setup Oc0 as an output pin
	GPIO_setupPinDirection (PWM_PORT , PWM_PIN ,PIN_OUTPUT );
	/*
	 * Configure Timer0 control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 = (1<<WGM01) | (1<<WGM00) | (1<<COM01) | (1<<CS01) ;
}

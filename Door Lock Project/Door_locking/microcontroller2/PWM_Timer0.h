
 /******************************************************************************
 *
 * Module: PWM Timer
 *
 * File Name: PWM_Timer0.h
 *
 * Description: Source file for the AVR PWM Timer0 driver
 *
 * Author: Omar Medhat
 *
 *******************************************************************************/
#ifndef PWM_TIMER0_H_
#define PWM_TIMER0_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define PWM_PORT 	    PORTB_ID      
#define	PWM_PIN 		PIN3_ID
/*******************************************************************************
 *                      Functions Prototypes                                   *
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
void PWM_Timer0_Start(uint8 duty_cycle) ;


#endif /* PWM_TIMER0_H_ */

 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: Source file for the buzzer AVR driver
 *
 * Author: Omar Medhat
 *
 *******************************************************************************/
#include "buzzer.h"
#include "gpio.h"
#include <avr/io.h>
/*******************************************************************************
 *                      Functions Definitions                                  *
*******************************************************************************/
/*
 * Description :
 * Initialize the buzzer and configure it's pin by gpio driver
 */
void buzzer_Init(void)
{
	// Setup pin of buzzer as output Pin
	GPIO_setupPinDirection(Buzzer_PORT_ID, Buzzer_PIN_ID, PIN_OUTPUT);
	//Initialize it by Zero at starting
	GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_LOW);
}

/*
 * Description :
 * Turn on the buzzer
 */
void buzzer_On(void)
{
	GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_HIGH);
}

/*
 * Description :
 * Turn off the buzzer
 */
void buzzer_Off(void)
{
	GPIO_writePin(Buzzer_PORT_ID,Buzzer_PIN_ID,LOGIC_LOW);
}

 /******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer AVR driver
 *
 * Author: Omar Medhat
 *
 *******************************************************************************/

#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define Buzzer_PIN_ID		PIN3_ID
#define Buzzer_PORT_ID		PORTD_ID
/*******************************************************************************
 *                      Functions Prototype                                 *
*******************************************************************************/
/*
 * Description :
 * Initialize the buzzer and configure it's pin by gpio driver
 */
void buzzer_Init(void);
/*
 * Description :
 * Turn on the buzzer
 */
void buzzer_On(void);
/*
 * Description :
 * Turn off the buzzer
 */
void buzzer_Off(void);

#endif /* BUZZER_H_ */

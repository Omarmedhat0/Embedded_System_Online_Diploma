/******************************************************************************
 * Module: Microcontroller2
 *
 * File Name : microcontroller2.h
 *
 * Description: Header file for the microcontroller2 in door locking project
 *
 * Author: Omar Medhat
 *
 * Created on: Sep 3, 2023
 ******************************************************************************/
#ifndef MICROCONTROLLER2_H_
#define MICROCONTROLLER2_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "micro_config.h"
#include "external_eeprom.h"
#include "buzzer.h"
#include "DC_MOTOR.h"
#include "timer.h"
#include "uart.h"
#include <util/delay.h>
/*******************************************************************************
 *                                Definitions and Gloabal variables              *
 *******************************************************************************/
#define PASSWORD_SIZE		5
#define	Send				0xA0
#define Command				0x10
#define New_Password		0x20
#define W_EEPROM			0x30
#define R_EEPROM			0x40
#define buzzer				0x50
#define motor				0x60
#define Pass_Address		0x0311
#define Minute				60
uint8 g_timer_counter=		0;
uint8 g_flag_buzzer=		0;
uint8 g_flag_motor=			0;
uint8 g_New_Password_check[10];
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/* Description :
 1- Initiates microcontroller2 modules (global interrupts , UARt module ,EEPROM module ,DcMotor module )
 */
void Init_Microcontroller2_Modules(void);

/* Description :
 * Function receives an command from microcontroller1
  and do an action according to the command which will be sent
 */
void Receive_Command(void);

/* Description :
 1- Function receives the new password from microcontroller1 that the user entered
   to microcontroller2
 2- Check if the user typed the new password correctly twice 
 3- Send the result of checking to microcontroller1
 */
void Receive_And_Check_New_Password(void);

/* Description :
 1- Function receives the old password from microcontroller1 that the user entered
   to microcontroller2
 2- Check if the user typed the old equals the current password in EEPROM 
 3- Send the result of checking to microcontroller1
 */
void Receive_And_Check_Old_Password(void);

/* Description :
 * Function saves the variable in the current global array in EEPROM at a certain  address
 */
void Save_Password_In_EEPROM (void);

/* Description :
 1- Set g_flag_buzzer by 1 
 2- Initiate Timer 1 to count 1 Sec
 3- Handling when the buzzer on and when the buzzer off
 */
void buzzer_action(void);

/* Description :
 1- Initiate Timer 1 to count 1 Sec
 2-  Handling when the motor on and when the motor off
 */
void motor_action(void);

/*******************************************************************************
 *         					  Extra  Features Functions     				   *
 *******************************************************************************/

/* Description :
 * Function that read old password from EEPROM and send it to microcontroller1
 */
void Send_Old_Passord(void);


#endif /* MICROCONTROLLER2_H_ */

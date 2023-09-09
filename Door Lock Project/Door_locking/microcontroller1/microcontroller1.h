/******************************************************************************
 * Module: Microcontroller1
 *
 * File Name : microcontroller1.h
 *
 * Description: Header file for the microcontroller1 in door locking project
 *
 * Author: Omar Medhat
 *
 * Created on: Sep 3, 2023
 ******************************************************************************/
#ifndef MICROCONTROLLER1_H_
#define MICROCONTROLLER1_H_
#include <avr/io.h>
#include <avr/interrupt.h>
#include "micro_config.h"
#include <util/delay.h>
#include "uart.h"
#include "timer.h"
#include "keypad.h"
#include "lcd.h"
/*******************************************************************************
 *                                Definitions and Gloabal variables            *
 *******************************************************************************/
#define PASSWORD_SIZE		5
#define Debounce_Handler 	0xF0
#define Command				0x10
#define New_Password		0x20
#define W_EEPROM			0x30
#define R_EEPROM			0x40
#define buzzer				0x50
#define motor				0x60
#define	Send				0xA0
#define Minute				60
uint8 g_Key_pressed= 		0;
uint8 g_flag_status=		0;
uint8 g_operator_plus=	    0;
uint8 g_timer_counter=		0;
uint8 g_New_Password[10];

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/* Description :
 * Function sends a command to perform something to microcontroller2
 */
void Send_Command(uint8 Command_Name);

/* Description :
 1- Function handels the home page that the user will with the system through it
 2- Controlling if the user want to open the door or change password
 */
void Home_Page(void);

/* Description :
 1- Initiates microcontroller2 modules (global interrupts , UARt module ,LCD module )
 */
void Init_Microcontroller1_Modules(void);

/**************************************************************/
/* Description :
 1- Function gets a new password from user 
 2- Save it in the first 5 elements of global array g_New_Password
 */
void Get_New_Password(void);

/* Description :
 1- Function gets a new password for the second time for confirmation from user 
 2- Save it in the second 5 elements of global array g_New_Password
 */
void Re_Enter_New_Password(void);

/*
* Description :
 1- Function to send New and Re-new or Old Password to microcontroller 1 
*/
void Send_Password_To_Be_Checked(const uint8 arr[] );

/* Description :
 1- Function receives the result of checking the new password from microcontroller2
 2- If the New and Re-new Password are identical it sends a command to microcontroller2 to store it in EEPROM
 */
void Receive_The_Result_Of_New_Password(void);

/* Description :
 1- Function handeles the sequence to make an new password
 */
void Setup_A_New_Password (void);

/**************************************************************/
/* Description :
 1- Function gets an old password from user 
 2- Save it in the first 5 elements of global array g_New_Password
 */
void Enter_Old_Password(void);

/* Description :
 1- Function receives the result of checking the old password from microcontroller2
 2- If the old password matches with the password in EEPROM , it sends a command to microcontroller2 to open the door 
 		or changing password according to the date provided
 */
void Receive_The_Result_Of_OLD_Password(void);

/* Description :
 1- Function handles the sequence to enter and check the password
 */
void GET_And_Check_Old_Password (void);

/* Description :
 1- Initiates microcontroller2 modules (global interrupts , UARt module ,LCD module )
 */
void Open_The_door(void);

/************************************************************/


/*******************************************************************************
 *         					  Extra  Features Functions     				   *
 *******************************************************************************/
/*
Description :
 * Function that display the new password and the re-typing of it
   before sends it to compare between 2 passwords in micro 2
 */
 // void Display_Password(void);

/* Description :
 * Function that read the old password from microcontroller2 and display it on LCD on microcontroller1
 */
 // void Read_Old_Password_From_EEPROM(void);


#endif /* MICROCONTROLLER1_H_ */

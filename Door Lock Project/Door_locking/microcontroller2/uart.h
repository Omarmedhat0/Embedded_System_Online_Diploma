 /******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.h
 *
 * Description: Header file for the UART AVR driver
 *
 * Author: Omar Medhat
 *
 *******************************************************************************/

#ifndef UART_H_
#define UART_H_

#include "std_types.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	_100=100,_200=200,_300=300,_1200=1200,_2400=2400,_4800=4800,_9600=9600,_19200=19200,_38400=38400,_57600=57600,_115200=115200
}Baud_Rate_config;
typedef enum
{
	_5_Bits,_6_Bits,_7_Bits,_8_Bits,Reserved1,Reserved2,Reserved3,_9_Bits
}Character_Size;

typedef enum
{
	Disable,Reserved4,Eeven,Odd
}Parity_Mode;
typedef enum
{
	_1_bit,_2_bit
}Num_Of_Stop_Bits;
typedef enum
{
	Asynchronous_Operation , synchronous_Operation
}Mode_Select;
typedef enum
{
	Asynchronous__Operation , synchronous__Operation
}Clock_Polarity;
typedef struct
{
	Baud_Rate_config	Baud_Rate;
	Character_Size		size;
	Parity_Mode			Parity ;
	Num_Of_Stop_Bits	Stop_bits;	
	Mode_Select			Mode ;
	Clock_Polarity		Clock;
}Uart_ConfigType;
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const Uart_ConfigType *ptr_config);

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data);

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void);

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str);

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str); // Receive until #

#endif /* UART_H_ */

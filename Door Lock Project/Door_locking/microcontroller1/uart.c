/******************************************************************************
 *
 * Module: UART
 *
 * File Name: uart.c
 *
 * Description: Source file for the UART AVR driver
 *
 * Author: Omar Medhat
 *
 *******************************************************************************/

#include "uart.h"
#include "avr/io.h" /* To use the UART Registers */
#include "micro_config.h"
#include "common_macros.h" /* To use the macros like SET_BIT */

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description :
 * Functional responsible for Initialize the UART device by:
 * 1. Setup the Frame format like number of data bits, parity bit type and number of stop bits.
 * 2. Enable the UART.
 * 3. Setup the UART baud rate.
 */
void UART_init(const Uart_ConfigType *ptr_config)
{
	uint16 ubrr_value = 0;

	/* U2X = 1 for double transmission speed */
	UCSRA = (1<<U2X);

	/************************** UCSRB Description **************************
	 * RXCIE = 0 Disable USART RX Complete Interrupt Enable
	 * TXCIE = 0 Disable USART Tx Complete Interrupt Enable
	 * UDRIE = 0 Disable USART Data Register Empty Interrupt Enable
	 * RXEN  = 1 Receiver Enable
	 * RXEN  = 1 Transmitter Enable
	 * RXB8 & TXB8 not used for 8-bit data mode
	 * Insert the required number of data bits in the frame through UCSZ2 Bit
	 ***********************************************************************/ 
	UCSRB = (1<<RXEN) | (1<<TXEN);
	UCSRB = (UCSRB & 0xFB) | (((ptr_config->size)&0x04));

	/************************** UCSRC Description **************************
	 * Set URSEL BIT to 1 when writing the UCSRC
	 * Insert the required mode of opeartion (Asynchronous/synchronous) through UMSEL bit 
	 * Insert the required mode of Parity through UPM1:0 bits
	 * Insert the required number of Stop Bits through USBS bit
	 * Insert the required mode of opeartion (Asynchronous/synchronous) through UMSEL bit
	 * Insert the required number of data bits in the frame through UCSZ1:0 Bits
	 * Insert the required Clock Polarity through UCPOL Bits

	 ***********************************************************************/ 	
	SET_BIT(UCSRC,URSEL);
	//UCSRC |=(1<<UCSRC);
	UCSRC = (UCSRC & 0xBF)|((ptr_config->Mode)<<6);
	UCSRC =	(UCSRC & 0xCF)|((ptr_config->Parity)<<4);
	UCSRC = (UCSRC & 0xF7)|((ptr_config->Stop_bits)<<3);
	UCSRC = (UCSRC & 0xF9)|(((ptr_config->size)&0x03)<<1);
	//UCSRC|= (1<<UCSZ0) | (1<<UCSZ1);
	UCSRC = (UCSRC & 0xFE)|(ptr_config->Clock);



	/* Calculate the UBRR register value with required BaudRate*/
	ubrr_value = (uint16)(((F_cpu / ((ptr_config->Baud_Rate) * 8UL))) - 1);

	/* First 8 bits from the BAUD_PRESCALE inside UBRRL and last 4 bits in UBRRH*/
	UBRRH = ubrr_value>>8;
	UBRRL = ubrr_value;
}

/*
 * Description :
 * Functional responsible for send byte to another UART device.
 */
void UART_sendByte(const uint8 data)
{
	/*
	 * UDRE flag is set when the Tx buffer (UDR) is empty and ready for
	 * transmitting a new byte so wait until this flag is set to one
	 */
	while(BIT_IS_CLEAR(UCSRA,UDRE)){}

	/*
	 * Put the required data in the UDR register and it also clear the UDRE flag as
	 * the UDR register is not empty now
	 */
	UDR = data;

	/************************* Another Method *************************
	UDR = data;
	while(BIT_IS_CLEAR(UCSRA,TXC)){} // Wait until the transmission is complete TXC = 1
	SET_BIT(UCSRA,TXC); // Clear the TXC flag
	 *******************************************************************/
}

/*
 * Description :
 * Functional responsible for receive byte from another UART device.
 */
uint8 UART_recieveByte(void)
{
	/* RXC flag is set when the UART receive data so wait until this flag is set to one */
	while(BIT_IS_CLEAR(UCSRA,RXC)){}

	/*
	 * Read the received data from the Rx buffer (UDR)
	 * The RXC flag will be cleared after read the data
	 */
	return UDR;
}

/*
 * Description :
 * Send the required string through UART to the other UART device.
 */
void UART_sendString(const uint8 *Str)
{
	uint8 i = 0;

	/* Send the whole string */
	while(Str[i] != '\0')
	{
		UART_sendByte(Str[i]);
		i++;
	}
	/************************* Another Method *************************
	while(*Str != '\0')
	{
		UART_sendByte(*Str);
		Str++;
	}		
	 *******************************************************************/
}

/*
 * Description :
 * Receive the required string until the '#' symbol through UART from the other UART device.
 */
void UART_receiveString(uint8 *Str)
{
	uint8 i = 0;

	/* Receive the first byte */
	Str[i] = UART_recieveByte();

	/* Receive the whole string until the '#' */
	while(Str[i] != '#')
	{
		i++;
		Str[i] = UART_recieveByte();
	}

	/* After receiving the whole string plus the '#', replace the '#' with '\0' */
	Str[i] = '\0';
}

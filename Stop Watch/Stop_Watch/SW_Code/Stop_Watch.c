/*
 ============================================================================
 Name        : Stop_Watch.c
 Author      : Omar MEdhat
 Description : Stop Watch System Project
 Date        : 30/8/2023
 ============================================================================
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
unsigned char count_second=0 ; // Global Variable flag to write 1 on it when timer count 1 mil sec
unsigned char g_sec =0 ; // Global Variable  the counts total seconds
unsigned char g_min =0 ;// Global Variable the counts minutes
unsigned char g_hur=0 ;//Global Variable the hours

//configure Timer1 in compare mode
//Interrupt Service Routine for timer1 compare mode channel A
ISR (TIMER1_COMPA_vect)
{
	count_second = 1 ; // write 1 on it when timer count 1 mil sec on count_second
}
void Timer1_Init_CTC_Mode(unsigned short tick)
{
	/* Timer initial value*/
	TCNT1 = 0 ; 
	/* Timer compare value*/
	OCR1A = tick ;

	/* Configure timer1 control registers
	 * 1. Non PWM mode FOC1A=1 and FOC1B=1
	 * 2. No need for OC1A & OC1B in this example so COM1A0=0 & COM1A1=0 & COM1B0=0 & COM1B1=0
	 * 3. CTC Mode and compare value in OCR1A WGM10=0 & WGM11=0 & WGM12=1 & WGM13=0
	 */
	TCCR1A = (1<<FOC1A ) | (1<<FOC1B);

	/*
	 * 4. Clock = F_CPU/1024 CS10=1 CS11=0 CS12=1
	 */
	TCCR1B = (1<<WGM12) | (1 <<CS12 ) | (1<<CS10);

	TIMSK |= (1<<OCIE1A ) ; //enable interrupt in compare mode fro channel A
}

//Interrupt Service Routine for external interrupt 0
ISR (INT0_vect)
{
	/*reset global variables*/
	g_sec =0;
	g_min=0;
	g_hur=0;
}

//Interrupt Service Routine for external interrupt 1
ISR (INT1_vect)
{
	/*  Turn off the clock
	Clear the timer clock bits (CS10=0 CS11=0 CS12=0) to stop the timer clock */
	TCCR1B &= 0xF8;
}

//Interrupt Service Routine for external interrupt 2
ISR (INT2_vect)
{
	/* resume the stop watch by enable the timer through the clock bits. */
	TCCR1B |= (1 <<CS12 ) | (1<<CS10);
}

//External interrupt 0 Configure function
void Init_INT0(void)
{
	SREG &= ~(1<<7); // Disable global interrupts in MC.
	DDRD &= ~(1<<PD2); //Configure pin 2 in port D as an Input pin
	PORTD |= (1<<PD2);// Enable internal pull up resistor for pin2
	MCUCR |= (1<<ISC01);// Trigger INT0 with the falling edge ISC01 =0 , ISC00 =1
	SREG |=(1<<7); //Enable global interrupts in MC.
}

//External interrupt 1 Configure function
void Init_INT1(void)
{
	SREG &= ~(1<<7);// Disable global interrupts in MC.
	DDRD &= ~(1<<PD3);// Configure pin 3 in port D as an Input pin
	MCUCR |= (1<<ISC11) |(1<<ISC10) ; //// Trigger INT1 with the raising edge
	GICR  |= (1<<INT1);// Enable external interrupt pin INT1
	SREG |=(1<<7);  //Enable global interrupts in MC.
}

//External interrupt 2 Configure function
void Init_INT2(void)
{
	SREG &= ~(1<<7);// Disable global interrupts in MC.
	DDRD &= ~(1<<PB2); // Configure pin 2 in port B as an Input pin
	PORTD |= (1<<PB2); // Enable internal pull up resistor for pin2
	GICR  |= (1<<INT2);// Enable external interrupt pin INT2
	/*Trigger INT2 with the falling edge by put 0 on ISC2 at MCUCSR register*/
	SREG |=(1<<7); //Enable global interrupts in MC.
}
int main(void)
{
	DDRC |= 0x0F ; // Configure the first 4 pins in Port C As output pins
	PORTC &= 0xF0 ;// initialize the first 4 pins in Port C by zero
	DDRA |= 0x3F ; // Configure the first 6 pins in Port A As output pins
	PORTA |= 0x3F; // Enable internal pull up resistor for the first 6 pins in Port A 
	SREG  |= (1<<7);//Enable global interrupts in MC.
	Timer1_Init_CTC_Mode(1000);//// Configure the number of ticks to timer0 to counts 1 sex
	Init_INT0();// Activate external interrupt INT0
	Init_INT1();// Activate external interrupt INT1
	Init_INT2();// Activate external interrupt INT2
	while(1)
	{

		if (count_second==1)// when timer counts 1 sec
		{
			//increment seconds count
			g_sec ++ ;
			if (g_sec==60)
			{
				/*if seconds counter counts 60 so this mean it complete 1 min
				 so reset to 0 and increment minutes count */
				g_sec=0;
				g_min++;
			}
			if (g_min==60)
			{
				/*if minutes counter counts 60 so this mean it complete 1 hours
				 so reset to 0 and increment hours count */
				g_min =0 ;
				g_hur++;
			}
			if (g_hur==24)
			{
				/*if hours counter counts 24 reset to 0  */
				g_hur=0;
			}
			count_second =0 ;
		}
		else
		{
			// display the number of seconds
			PORTA = (PORTA & 0xC0) | 0x01;
			PORTC = (PORTC & 0xF0) | (g_sec%10);
			_delay_ms(2); //Make a small delay to observe the difference on 7-segment
			PORTA = (PORTA & 0xC0) | 0x02;
			PORTC = (PORTC & 0xF0) | (g_sec/10);
			_delay_ms(2);//Make a small delay to observe the difference on 7-segment

			// display the number of seconds
			PORTA = (PORTA & 0xC0) | 0x04;
			PORTC = (PORTC & 0xF0) | (g_min%10);
			_delay_ms(2);//Make a small delay to observe the difference on 7-segment
			PORTA = (PORTA & 0xC0) | 0x08;
			PORTC = (PORTC & 0xF0) | (g_min/10);
			_delay_ms(2);//Make a small delay to observe the difference on 7-segment

			// display the number of seconds
			PORTA = (PORTA & 0xC0) | 0x10;
			PORTC = (PORTC & 0xF0) | (g_hur%10);
			_delay_ms(2);//Make a small delay to observe the difference on 7-segment
			PORTA = (PORTA & 0xC0) | 0x20;
			PORTC = (PORTC & 0xF0) | (g_hur/10);
			_delay_ms(2);//Make a small delay to observe the difference on 7-segment
		}
	}
}

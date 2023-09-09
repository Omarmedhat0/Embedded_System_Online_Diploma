/******************************************************************************
 * Module: Timer
 *
 * File Name : timer.c
 *
 * Description: Source file for the ATmega16 Timer driver
 *
 * Author: Omar Medhat
 ******************************************************************************/
#include "timer.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include <avr/io.h> /* To use Timer1 Registers */
#include <avr/interrupt.h>  /* To use Interrupt Service Routine */

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application for timer 0 */
static volatile void (*g_callBackPtr0)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function in the application for timer 1 */
static volatile void (*g_callBackPtr1)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function in the application for timer 2 */
static volatile void (*g_callBackPtr2)(void) = NULL_PTR;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/
//Interrupt Service Routine for timer 0 Overflow Mode
ISR(TIMER0_OVF_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
//Interrupt Service Routine for timer 0 Compare Mode
ISR(TIMER0_COMP_vect)
{
	if(g_callBackPtr0 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
//Interrupt Service Routine for timer 1 Overflow Mode
ISR(TIMER1_OVF_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
//Interrupt Service Routine for timer 1 Compare Mode Channel A
ISR(TIMER1_COMPA_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
//Interrupt Service Routine for timer 1 Compare Mode Channel B
ISR(TIMER1_COMPB_vect)
{
	if(g_callBackPtr1 != NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtr1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
}
//Interrupt Service Routine for timer 2 Compare Mode
ISR(TIMER2_OVF_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}
//Interrupt Service Routine for timer 2 Compare Mode
ISR(TIMER2_COMP_vect)
{
	if(g_callBackPtr2 != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr2)(); /* another method to call the function using pointer to function g_callBackPtr(); */
	}
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/* Description :
 * Initialization the timer module
 * Select which timer that wanted to be used
 */
void Timer_init(const Timer_ConfigType * Config_Ptr)
{
	if ((Config_Ptr->Timer)==Timer0)//Select Timer 0
	{
		Timer0_init(Config_Ptr);
	}
	else if( ((Config_Ptr->Timer)==Timer1_CHA) | ((Config_Ptr->Timer)==Timer1_CHB) )//Select Timer 1 and which channel needs to work on
	{
		Timer1_init(Config_Ptr);
	}
	else if((Config_Ptr->Timer)==Timer2)//Select Timer 2
	{
		Timer2_init(Config_Ptr);
	}
}

/* Description :
 * Initialization Timer0 function with specification with Compare Mode or Overflow Mode
 */

void Timer0_init(const Timer_ConfigType * Config_Ptr)
{
	/* Configure the timer control register*/

	//Set The required Timer initial value in TCNT0 Registers
	TCNT0 = Config_Ptr->Initial_value;

	//Set The required Timer Compare value in compare mode in OCR0 Registers
	OCR0 = Config_Ptr->Compare_value;

	/*************************** Configure TCCR0 register***************************/
	//Non PWM mode FOC0=1
	SET_BIT(TCCR0,FOC0);

	//Insert the required Waveform Generation mode through WGM00:1 BITS
	TCCR0 = (TCCR0 & 0xBF) | (((Config_Ptr->Waveform_Generation)&0x01)<<6);
	TCCR0 = (TCCR0 & 0xF7) | (((Config_Ptr->Waveform_Generation)&0x02)<<2);


	//Insert the required Clock Select Prescaler through COM00:2 BITS
	TCCR0 = (TCCR0 & 0xF8) | (Config_Ptr->Prescaler);

	//Insert the required Compare Output mode through COM00:1 BITS
	//Enabled Interrupt for Overflow or Compare mode as required
	if ((Config_Ptr->Waveform_Generation)==Over_Flow)//Setup Overflow case
	{
		// Reset Bit COM00 & COM01
		CLEAR_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
		SET_BIT(TIMSK,TOIE0);
	}
	else if ((Config_Ptr->Waveform_Generation)==Compare)//Setup compare mode case
	{
		// SET Bit COM00 & COM01
		CLEAR_BIT(TCCR0,COM00);
		CLEAR_BIT(TCCR0,COM01);
		SET_BIT(TIMSK,OCIE0);
	}
}

/*
 * Description: Function to set the Call Back function address for timer 0.
 */
void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr0 = a_ptr;
}

/*
 * Description: Function to disable the Timer0 to stop the Timer Driver
 */
void Timer0_diinit(void)
{
	TCNT0 = 0 ;
	OCR0 = 0 ;
	TCCR0 =0 ;
	TIMSK =0 ;
}

/* Description :
 * Initialization Timer1 function with specification with Compare Mode or Overflow Mode and configure channels
 */
void Timer1_init(const Timer_ConfigType * Config_Ptr)
{
	/* Configure the timer control registesr*/

	//Set The required Timer initial value in TCNT1 Registers for both channels
	TCNT1 = Config_Ptr->Initial_value;

	//Insert the required Clock Select Prescaler through COM10:2 BITS
	TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->Prescaler);

	/*Description
	 * Set The required Timer Compare value in compare mode for both channels
	 * Adjust TCCR1A and TCCR1B  Register
	 * Insert the required Compare Output mode
	 * Enabled Interrupt for Overflow or Compare mode as required
	 */

	if ((Config_Ptr->Timer)==Timer1_CHA)//Setup Channel A in timer 1 
	{

		SET_BIT(TCCR1A,FOC1A);  //Non PWM mode FOC1A=1,FOC1B=1
		SET_BIT(TCCR1A,FOC1B);

		//To set Compare Output and waveform mode In case of Overflow Mode
		if ((Config_Ptr->Waveform_Generation)==Over_Flow)
		{
			//Insert the required Waveform Generation mode which is overflow at this case
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			//Insert the required Compare Output mode
			// Reset Bit COM1A0 & COM1A1
			/*CLEAR_BIT(TCCR1A,COM1A0);
			CLEAR_BIT(TCCR1A,COM1A1);*/
			SET_BIT(TIMSK,TOIE1);//Enabled Interrupt
		}
		//To set Compare Output mode and waveform in case of Compare Mode
		else if ((Config_Ptr->Waveform_Generation)==Compare)
		{
			OCR1A = Config_Ptr->Compare_value;// Compare value for channel A
			//Insert the required Waveform Generation mode which is compare at this case
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			//Insert the required Compare Output mode
			// SET Bit COM1A0 & COM1A1
			/*SET_BIT(TCCR1A,COM1A0);
			SET_BIT(TCCR1A,COM1A1);*/
			SET_BIT(TIMSK,OCIE1A);//Enabled Interrupt
		}

	}
	else if ((Config_Ptr->Timer)==Timer1_CHB)//Setup Channel B in timer 1 
	{

		SET_BIT(TCCR1A,FOC1B);  //Non PWM mode FOC1A=1,FOC1B=1
		SET_BIT(TCCR1A,FOC1A);

		//To set Compare Output and waveform mode In case of Overflow Mode
		if ((Config_Ptr->Waveform_Generation)==Over_Flow)
		{
			//Insert the required Waveform Generation mode through WGM10:3 BITS
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			CLEAR_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			//Insert the required Compare Output mode
			// Reset Bit COM1B0 & COM1B1
			/*CLEAR_BIT(TCCR1A,COM1B0);
			CLEAR_BIT(TCCR1A,COM1B1);*/
			SET_BIT(TIMSK,TOIE1);//Enabled Interrupt
		}
		//To set Compare Output and waveform mode In case of Compare Mode
		else if ((Config_Ptr->Waveform_Generation)==Compare)
		{
			OCR1B = Config_Ptr->Compare_value;// Compare value for channel B
			//Insert the required Waveform Generation mode through WGM10:3 BITS
			CLEAR_BIT(TCCR1A,WGM10);
			CLEAR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLEAR_BIT(TCCR1B,WGM13);
			//Insert the required Compare Output mode
			// SET Bit COM1B0 & COM1B1
			/*SET_BIT(TCCR1A,COM1B0);
			SET_BIT(TCCR1A,COM1B1);*/
			SET_BIT(TIMSK,OCIE1B);//Enabled Interrupt
		}
	}
}

/*
 * Description: Function to set the Call Back function address for timer 1.
 */
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr1 = a_ptr;
}

/*
 * Description: Function to disable the Timer1 to stop the Timer Driver
 */
void Timer1_diinit(void)
{
	TCNT1 = 0 ;
	OCR1A = 0 ;
	OCR1B = 0 ;
	TCCR1A = 0 ;
	TCCR1B = 0 ;
	TIMSK = 0 ;
}

/* Description :
 * Initialization Timer2 function with specification with Compare Mode or Overflow Mode
 */
void Timer2_init(const Timer_ConfigType * Config_Ptr)

{
	/* Configure the timer control registesr*/

	//Set The required Timer initial value in TCNT2 Registers
	TCNT2 = Config_Ptr->Initial_value;

	//Set The required Timer Compare value in compare mode in OCR2 Registers
	OCR2 = Config_Ptr->Compare_value;

	/*************************** Configure TCCR0 register***************************/
	//Non PWM mode FOC2=1
	SET_BIT(TCCR2,FOC2);

	//Insert the required Waveform Generation mode through WGM20:1 BITS
	TCCR2 = (TCCR2 & 0xBF) | (((Config_Ptr->Waveform_Generation)&0x01)<<6);
	TCCR2 = (TCCR2 & 0xF7) | (((Config_Ptr->Waveform_Generation)&0x02)<<2);


	//Insert the required Clock Select Prescaler through COM20:2 BITS
	TCCR2 = (TCCR2 & 0xF8) | (Config_Ptr->Prescaler);

	//Insert the required Compare Output mode through COM20:1 BITS
	//Enabled Interrupt for Overflow or Compare mode as required
	if ((Config_Ptr->Waveform_Generation)==Over_Flow)//Overflow mode
	{
		CLEAR_BIT(TCCR2,COM20);
		CLEAR_BIT(TCCR2,COM21);
		SET_BIT(TIMSK,TOIE2);
	}
	else if ((Config_Ptr->Waveform_Generation)==Compare)//compare mode
	{
		CLEAR_BIT(TCCR2,COM20);
		CLEAR_BIT(TCCR2,COM21);
		SET_BIT(TIMSK,OCIE2);
	}
}

/*
 * Description: Function to set the Call Back function address for timer 2.
 */
void Timer2_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr2 = a_ptr;
}

/*
 * Description: Function to disable the Timer2 to stop the Timer Driver
 */
void Timer2_diinit(void)
{
	TCNT2 = 0 ;
	OCR2 = 0 ;
	TCCR2 =0 ;
	TIMSK =0 ;
}


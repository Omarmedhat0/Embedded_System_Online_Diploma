/******************************************************************************
 *
 * Module: Measure the distance using ultrasonic sensor project
 *
 * File Name: Measure_the_distance
 *
 * Description: Source file for project
 *
 * Author: Omar Medhat
 *
 *******************************************************************************/
#include "lcd.h"
#include <avr/io.h>
#include "ultrasonic.h"
int main(void)
{
	uint16 Distance=0;//Variable to save the distance in it
	SREG |= (1<<7);//Enable global Interrupt
	Ultrasonic_init();//Initialize Ultrasonic module
	LCD_init();//Initialize LCD module
	/* Print :
							Distance=     cm
		* On screen
	*/
	LCD_displayString("Distance=     cm");

	while(1)//programe loop
	{
		//Reading the current distance byUltrasonic_readDistance(); and assign the value in Distance variable
		Distance=Ultrasonic_readDistance();

		//Move the cursot to the place which the distance will be written on
		LCD_moveCursor(0,10);

		//Display the distance on display at '#' places
		/* Print :
							Distance= ###  cm
		* On screen
		*/
		LCD_intgerToString(Distance);

		//Display a " " after writing the number as if the distance consists of 3 digits and reduced to be in 2 digits so LCD will clear the previous rest digit that didn't erase
		LCD_displayString(" ");
	}
}

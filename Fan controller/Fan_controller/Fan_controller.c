/******************************************************************************
 *
 * Module: Fan controller Project
 *
 * File Name: Fan_controller.c
 *
 * Description: Source file for the AVR Fan_controller
 *
 * Author: Omar Medhat
 *
 *******************************************************************************/
#include <avr/io.h>
#include "adc.h"
#include "DC_Motor.h"
#include "lcd.h"
#include "lm35_sensor.h"
int main(void)
{
	uint8 temp; // To save the result of temperature sensor in it

	SREG  |= (1<<7); // To enable interrupt

	ADC_ConfigType  ADC_Config ={Internal_2_56v_ ,F_CPU_8 }; //Variable from the type ADC_ConfigType which have ADC configuration

	ADC_init(&ADC_Config); // Pass configuration to init function of ADC to start conversion

	DcMotor_Init();//Initialize Motor driver

	LCD_init();//Initialize Motor driver

	/* Display "Temp =    C" in the second row */
	LCD_moveCursor(1,4);
	LCD_displayString("Temp =    C");

	while(1)
	{
		/* Set the value of LM35 in temp variable*/
		temp= LM35_getTemperature();

		/* Control the duty cycle of PWM signal according to temperature sensor signal  */
		if (temp >= 120)
		{
			/* Turn on the fan Clockwise with 100% of its maximum speed. */
			DcMotor_Rotate(CW,100);

			/* Display "Fan state" in the first row */
			LCD_moveCursor(0,4);
			LCD_displayString("FAN IS ON");
			LCD_displayCharacter(' ');

			/* Display "temperature value" in the same position every time */
			LCD_moveCursor(1,11);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if (temp >= 90)
		{
			/* Turn on the fan Clockwise with 75% of its maximum speed. */
			DcMotor_Rotate(CW,75);

			/* Display "Fan state" in the first row */
			LCD_moveCursor(0,4);
			LCD_displayString("FAN IS ON");
			LCD_displayCharacter(' ');

			/* Display "temperature value" in the same position every time */
			LCD_moveCursor(1,11);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if (temp >= 60)
		{
			/* Turn on the fan Clockwise with 50% of its maximum speed. */
			DcMotor_Rotate(CW,50);

			/* Display "Fan state" in the first row */
			LCD_moveCursor(0,4);
			LCD_displayString("FAN IS ON");

			/* Display "temperature value" in the same position every time */
			LCD_displayCharacter(' ');
			LCD_moveCursor(1,11);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if (temp >= 30)
		{
			/* Turn on the fan Clockwise with 25% of its maximum speed. */
			DcMotor_Rotate(CW,25);

			/* Display "Fan state" in the first row */
			LCD_moveCursor(0,4);
			LCD_displayString("FAN IS ON");
			LCD_displayCharacter(' ');

			/* Display "temperature value" in the same position every time */
			LCD_moveCursor(1,11);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
		else if (temp < 30)
		{
			/* Turn off the fan */
			DcMotor_Rotate(stop,0);

			/* Display "Fan state" in the first row */
			LCD_moveCursor(0,4);
			LCD_displayString("FAN IS OFF");
			LCD_displayCharacter(' ');

			/* Display "temperature value" in the same position every time */
			LCD_moveCursor(1,11);
			LCD_intgerToString(temp);
			LCD_displayCharacter(' ');
		}
	}
}

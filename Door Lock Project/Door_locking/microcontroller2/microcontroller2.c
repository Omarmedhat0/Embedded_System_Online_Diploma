/******************************************************************************
 * Module: Microcontroller2
 *
 * File Name : microcontroller2.c
 *
 * Description: Source file for the microcontroller2 in door locking project
 *
 * Author: Omar Medhat
 *
 * Created on: Sep 3, 2023
 ******************************************************************************/

#include "microcontroller2.h"

/*******************************************************************************
 *           CallBack Functions for handling ISR code for Timers               *
 *******************************************************************************/
/* Description :
 1- Function handles what happens when timer 1 counts 1 sec to Buzzer status
 */
void Handle_Buzzer_Alert(void)
{
	//Increment g_timer_counter by one when Timer counts 1 Sec 
	++g_timer_counter;

	//When g_timer_counter counts 60 times that mean that the timer counted 1 minute
	if (g_timer_counter==Minute)
	{
		g_flag_buzzer=0;//Set g_flag_buzzer to Zero
		g_timer_counter=0 ;//Set g_flag_buzzer to Zero
		Timer1_diinit();//Turn off timer
	}
}

/* Description :
 1- Function handles what happens when timer 1 counts 1 sec to Motor status
 */
void Handle_Motor(void)
{
	//Increment g_timer_counter by one when Timer counts 1 Sec
	++g_timer_counter;

	//When g_timer_counter counts 1 time that mean that the timer counted 1 sec 
	if (g_timer_counter==1)
	{
		g_flag_motor=1;//Set g_flag_buzzer to One
	}
	//When g_timer_counter counts 4 times that mean that the timer counted another 3 sec 
	else if (g_timer_counter==4)
	{
		g_flag_motor=2;//Set g_flag_buzzer to Two
	}
	//When g_timer_counter counts 5 times that mean that the timer counted another 1 sec 
	else if (g_timer_counter==5)
	{
		g_flag_motor=3;//Set g_flag_buzzer to Three
		g_timer_counter=0 ;//Set g_flag_buzzer to Zero
		Timer1_diinit();//Turn off timer
	}
}

/*******************************************************************************
 *         					  Main Program     				   				   *
 *******************************************************************************/
int main(void)
{
	//Enable microcontroller2 modules
	Init_Microcontroller2_Modules();

	//Receive And Check New Password for the first time and send the result to microcontroller1
	Receive_And_Check_New_Password();

	//Program loop
	while(1)
	{
		//Waiting for receiving a command from microcontroller1 and perform it
		Receive_Command();
	}
}

/*******************************************************************************
 *         					     Functions Declaration     					 								   *
 *******************************************************************************/
/* Description :
 * Function receives an command from microcontroller1
  and do an action according to the command which will be sent
 */
void Receive_Command(void)
{
	//Wait until microcontroller1 send an order to receives a command
	while (UART_recieveByte() != Command);

	//Save the command in variable "Command_Name"
	uint8 Command_Name =  UART_recieveByte();

	//Check which command has been sent
	switch(Command_Name)
	{
	case New_Password : // If it was New_Password call Receive_And_Check_New_Password function
		Receive_And_Check_New_Password(); ;
		break;
	case W_EEPROM:// If it was W_EEPROM call Save_Password_In_EEPROM function
		Save_Password_In_EEPROM ();
		break;
	case R_EEPROM:// If it was R_EEPROM call Send_Old_Passord function
		Send_Old_Passord();
		break;
	case '+' :// If it was '+' call Receive_And_Check_Old_Password function
		Receive_And_Check_Old_Password();
		break;
	case '-' :// If it was '-' call Receive_And_Check_Old_Password function
		Receive_And_Check_Old_Password();
		break;
	case buzzer :// If it was buzzer call buzzer_action function
		buzzer_action();
		break;
	case motor:// If it was motor call motor_action function
		motor_action();
		break;
	default://Else UART_sendByte Command
		UART_sendByte(Command);
		break;
	}
}

/* Description :
 1- Initiates microcontroller2 modules (global interrupts , UARt module ,EEPROM module ,DcMotor module )
 */
void Init_Microcontroller2_Modules(void)
{
	SREG |= (1<<7) ; ///Enable global interrupts in MC.

	//Enable UARt module
	Uart_ConfigType UART_Configuration ={_9600 ,_8_Bits, Disable,_1_bit,Asynchronous_Operation,Asynchronous__Operation};
	UART_init(&UART_Configuration);

	//Enable EEPROM module
	EEPROM_init();

	//Enable DcMotor module
	DcMotor_Init();

	//Enable buzzer module
	buzzer_Init();
}


/* Description :
 1- Function receives the new password from microcontroller1 that the user entered
   to microcontroller2 and save it in globabl array consists of 10 elemnts
 2- Check if the user typed the new password correctly twice 
 3- Send the result of checking to microcontroller1
 */
void Receive_And_Check_New_Password(void)
{
	//Wait until microcontroller1 send an order to receives a new password
	while(UART_recieveByte()!= Send);
	uint8 count =0 ; // Initial local counter for looping process

	//Receives the new password and save it in global array g_New_Password_check
	while (count !=(PASSWORD_SIZE*2))
	{
		g_New_Password_check[count]=UART_recieveByte();
		count ++;
	}

	/*
	  * Initiate count by Zero value agian to re-looping
	  * Initiate local variable passwordMatch with true value to re-check 
	  	if the 2 password were identical or not 
	*/
	uint8 passwordMatch = TRUE;
	count =0 ;
	//Check if the first 5 element in g_New_Password_check is equal to the second t 5 element in g_New_Password_check
	while (count!=PASSWORD_SIZE)
	{
		if (g_New_Password_check[count]!=g_New_Password_check[(count)+5])
		{
			passwordMatch = FALSE;
			break ;
		}
		count++;
	}

	/*
	  * Sending the result of checking if it was TRUE during identical passwords
	  	or FALSE during un-identical passwords to microcontroller1
	*/
	if (passwordMatch)
	{
		UART_sendByte(Send);
		UART_sendByte(TRUE); // Send TRUE if passwords match
	}
	else
	{
		UART_sendByte(Send);
		UART_sendByte(FALSE); // Send FALSE if passwords don't match
	}
}

/* Description :
 1- Function receives the old password from microcontroller1 that the user entered
   to microcontroller2
 2- Check if the user typed the old equals the current password in EEPROM 
 3- Send the result of checking to microcontroller1
 */
void Receive_And_Check_Old_Password(void)
{
	//Wait until microcontroller1 send an order to receives a new password
	while(UART_recieveByte()!= Send);

	uint8 count =0 ;// Initial local counter for looping process

	//Receives the old password and save it in global array g_New_Password_check
	while (count !=(PASSWORD_SIZE*2))
	{
		g_New_Password_check[count]=UART_recieveByte();
		count ++;
	}

	/*
	  * Initiates count by Zero value again to re-looping
	  * Initiate local array of PASSWORD_SIZE elements to save the password which will be read from EEPROM
	  * Check the old password with the local array password
	  * Initiate local variable passwordMatch with true value to re-check 
	  	if the 2 password were identical or not 
	*/
	count =0 ;
	uint8 arr[PASSWORD_SIZE];
	uint8 passwordMatch = TRUE;
	//Check if the first 5 element in g_New_Password_check is equal to the 5 digit password saved in EEPROM
	while (count!=PASSWORD_SIZE)
	{
		EEPROM_readByte((Pass_Address+count), &arr[count]);
		_delay_ms(10);
		if (g_New_Password_check[count] != arr[count])
		{
			passwordMatch = FALSE;

			break ;
		}
		count++;
	}

	/*
	  * Sending the result of checking if it was TRUE during identical passwords
	  	or FALSE during un-identical passwords to microcontroller1
	*/
	if (passwordMatch)
	{
		UART_sendByte(Send);
		UART_sendByte(TRUE); // Send TRUE if passwords match
	}
	else
	{
		UART_sendByte(Send);
		UART_sendByte(FALSE); // Send FALSE if passwords don't match
	}
}


/* Description :
 * Function saves the variable in the current global array in EEPROM at a certain  address
 */
void Save_Password_In_EEPROM (void)
{
	uint8 count =0 ;// Initial local counter for looping process

	//looping on password in g_New_Password_check and save it in EEPROM in a certain  address
	while(count<PASSWORD_SIZE)
	{
		EEPROM_writeByte((Pass_Address+count),g_New_Password_check[count]);
		_delay_ms(10);
		count++;
	}

}

/* Description :
 1- Set g_flag_buzzer by 1 
 2- Initiate Timer 1 to count 1 Sec
 3- Handling when the buzzer on and when the buzzer off
 */
void buzzer_action(void)
{
	g_flag_buzzer=1;//Set g_flag_buzzer by 1 

	/*
	  * Initiate timer with this specific configuration
	  {
		- Work on Timer 1 channel A , Compare Mode , prescaler Fcpu_1024 , Initial value = "0"  
		- As Fcpu = 8MHZ so F_tick = Fcpu/prescaler -> 8MHZ/1024  
		  T_tick = 1/(Fcpu/prescaler) -> 1/(8MHZ/1024)
		  As we need the timer to count 1 sec so
		  Compare value = T_required/T_Tick -> 1/(1/(8MHZ/1024))= "7813"
	  }
	  * Pass TimerConfiguration to Init function
	  * Call setcallback function to perform the desired action when timer count 
	*/
	Timer_ConfigType Timer_Configuration = {Timer1_CHA,0,7813,Compare,Fcpu_1024};
	Timer_init(&Timer_Configuration);
	Timer1_setCallBack(Handle_Buzzer_Alert);

	//Turn on Buzzer
	buzzer_On();

	//Wait until timer count 1 sec and change g_flag_buzzer to 0 
	while(g_flag_buzzer!=0);

	//Turn off Buzzer
	buzzer_Off();
}

/* Description :
 1- Initiate Timer 1 to count 1 Sec
 2-  Handling when the motor on and when the mototr off
 */
void motor_action(void)
{
	/*
	  * Initiate timer with this specific configuration
	  {
		- Work on Timer 1 channel A , Compare Mode , prescaler Fcpu_1024 , Initial value = "0"  
		- As Fcpu = 8MHZ so F_tick = Fcpu/prescaler -> 8MHZ/1024  
		  T_tick = 1/(Fcpu/prescaler) -> 1/(8MHZ/1024)
		  As we need the timer to count 1 sec so
		  Compare value = T_required/T_Tick -> 1/(1/(8MHZ/1024))= "7813"
	  }
	  * Pass TimerConfiguration to Init function
	  * Chack the old password with the local array password
	  * Call setcallback function to perform the desired action when timer count 
	*/
	Timer_ConfigType Timer_Configuration = {Timer1_CHA,0,7813,Compare,Fcpu_1024};
	Timer_init(&Timer_Configuration);
	Timer1_setCallBack(Handle_Motor);

	/*
	* Motor control to rotate clockwise for 1 Sec as handeld in Handle_Motor function
	*/
	DcMotor_Rotate(CW,100);
	while (g_flag_motor!=1){};

	/*
	* Motor control to holding motor motion for 3 Sec as handled in Handle_Motor function
	*/
	DcMotor_Rotate(stop,0);
	while (g_flag_motor!=2){};

	/*
	* Motor control to rotate Ant-clockwise for 1 Sec as handled in Handle_Motor function
	*/	
	DcMotor_Rotate(A_CW,100);
	while (g_flag_motor!=3){};

	/*
	* Motor control to stop motor
	* Re-set g_flag_motor to zero
	*/
	DcMotor_Rotate(stop,0);
	g_flag_motor=0;
}

/*******************************************************************************
 *         					  Extra  Features Functions     				   *
 *******************************************************************************/

/* Description :
 * Function that read old password from EEPROM and send it to microcontroller1
 */
void Send_Old_Passord(void)
{
	uint8 count =0 ;// Initial local counter for looping process

	//Read the old password form EEPROM and save it in local array arr[]
	uint8 arr[PASSWORD_SIZE];
	while(count<PASSWORD_SIZE)
	{

		EEPROM_readByte((Pass_Address+count), &arr[count]);
		_delay_ms(10);
		count++;
	}

	// Initiates count by Zero value again to re-looping
	count=0;

	/*send a command Send to microcontroller1 to tell it
	  that microcontroller2 will start send the saved password in EEPROM
	 */
	UART_sendByte(Send);
	while(count<PASSWORD_SIZE)
	{
		UART_sendByte(arr[count]);
		count++;
	}
}

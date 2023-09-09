
/******************************************************************************
 * Module: Microcontroller1
 *
 * File Name : microcontroller1.c
 *
 * Description: Source file for the microcontroller1 in door locking project
 *
 * Author: Omar Medhat
 *
 * Created on: Sep 3, 2023
 ******************************************************************************/

#include "microcontroller1.h"

/*******************************************************************************
 *           CallBack Functions for handling ISR code for Timers               *
 *******************************************************************************/
/* Description :
 1- Function handles what happens when timer 1 counts 1 sec to allert on screen
 */
void Handle_Screen_Alert(void)
{

	//Increment g_timer_counter by one when Timer counts 1 Sec 
	++g_timer_counter;

	//When g_timer_counter counts 60 times that mean that the timer counted 1 minute
	if (g_timer_counter==Minute)
	{
		g_flag_status=0;//Set g_flag_status to Zero
		g_timer_counter=0 ;//Set g_timer_counter to Zero
		Timer1_diinit();//Turn off timer
	}
}

/* Description :
 1- Function handles what happens when timer 1 counts 1 sec to Motor on screen
 */
void Handle_Screen_Motor_Status(void)
{
	//Increment g_timer_counter by one when Timer counts 1 Sec
	++g_timer_counter;

	//When g_timer_counter counts 1 time that mean that the timer counted 1 sec 
	if (g_timer_counter==1)
	{
		g_flag_status=1;//Set g_flag_status to One
	}
	//When g_timer_counter counts 4 times that mean that the timer counted another 3 sec 
	else if (g_timer_counter==4)
	{
		g_flag_status=2;//Set g_flag_status to Two
	}
	//When g_timer_counter counts 5 times that mean that the timer counted another 1 sec 
	else if (g_timer_counter==5)
	{
		g_flag_status=3;//Set g_flag_buzzer to Three
		g_timer_counter=0 ;//Set g_flag_buzzer to Zero
		Timer1_diinit();//Turn off timer
	}
}

/*******************************************************************************
 *         								  Main Program    					   *
 *******************************************************************************/
int main(void)
{
	//Enable microcontroller1 modules
	Init_Microcontroller1_Modules();

	//Welcome Message for the first time the user run the program
	LCD_displayStringRowColumn(0,4,"Welcome to Door Lock System");
	_delay_ms(2000);

	//Setup a new password for the first time the user run the programme
	Setup_A_New_Password ();

	//Program loop
	while(1)
	{
		//Home page that the user will interface with it to perform an action
		Home_Page();
	}
}

/*******************************************************************************
 *         					     Functions Declaration     					 								   *
 *******************************************************************************/
/* Description :
 * Function sends a command to perform something to microcontroller2
 */
void Send_Command(uint8 Command_Name)
{
	UART_sendByte(Command);//Sending "command" to make microcontroller 2 starting receive a new command
	UART_sendByte(Command_Name);//Sending command name
}

/* Description :
 1- Function handles the home page that the user will with the system through it
 2- Controlling if the user want to open the door or change password
 */
void Home_Page(void)
{
	LCD_clearScreen();//Clear screen from any previous data displayed on LCD

	/* Print :
							'+' Open door
							'-'  Change password
		* On screen
	*/
	LCD_displayStringRowColumn(0,4,"'+' Open door");
	LCD_displayStringRowColumn(1,4,"'-'  Change password");

	//Waiting until entering a command by user 
	while ((KEYPAD_getPressedKey()!= '+') && (KEYPAD_getPressedKey()!= '-'));
	//Perform an action according to the command which has been written
	switch(KEYPAD_getPressedKey())
	{

	// If it was "+" The opening door process will be executed
	case '+':
		//Set g_that the operator_plus to 1 that decades that the system is in + mode
		g_operator_plus=1;
		Send_Command('+');//send "+" command to microcontroller2
		/*- Take old password from user and check it
		  - Perfrom opening door process if the user entering a correct password
		*/
		GET_And_Check_Old_Password();
		g_flag_status=0; //Set g_flag_status to Zero
		break;



	// If it was "-" The changing password process will be executed
	case '-' :
		//Set g_that the operator_plus to 0 that decades that the system isn't in + mode
		g_operator_plus=0;
		Send_Command('-');//send "-" command to microcontroller2
		GET_And_Check_Old_Password ();//Take old password from user and check it
		/*If the old password was correct compared with the password in EEPROM
		  make the user to enter new pasSwword and save it instead of the old one
		 */
		Send_Command(New_Password);//send New_Password command to microcontroller2
		Setup_A_New_Password ();//Perform setup new password process if the user entering a correct password
		break;

	//Send "command" at default case
	default:
		UART_sendByte(Command);
		break;
	}
}

/* Description :
 1- Function gets a new password from user 
 2- Save it in the first 5 elements of global array g_New_Password
 */
void Get_New_Password(void)
{
	LCD_clearScreen();//Clear screen from any previous data displayed on LCD

	/* Print :
							Please Enter New Password
		* On screen
	*/
	LCD_displayStringRowColumn(0,4,"Please Enter New Password");
	LCD_moveCursor(1,5);//move to the second row on LCD
	uint8 counter=0 ;// Initial local counter for looping process
	// Initial local prev_key for save the previous value entered by keypad on it during to debouncing problem
	uint8 prev_key = 0;
	//Wait until user entered a new key and save it in global variable g_Key_pressed
	g_Key_pressed = KEYPAD_getPressedKey();
	//If user enter "=" that means he entered the password so break the loop
	while(g_Key_pressed != '=')
	{
		//Wait until user entered a new key and save it in global variableg_Key_pressed
		g_Key_pressed = KEYPAD_getPressedKey();
		if (g_Key_pressed == prev_key)//This line to handle debouncing due to keypad
		{
			// Same key is pressed again, wait for debouncing
			_delay_ms(500);;
			/*Assign the value of Debounce_Handler in prev key to take another from 0:9 only
			 and not not equal '+'or '-' or '*' or '/' or '='
			*/
			prev_key = Debounce_Handler ;
		}
		else
		{
			/* - Now debouncing problem has been solved so wating for taking a number from user
				 - Number should bu in range of 0:9 and not equal'+'or '-' or '*' or '/' or '='
			*/
			if( (g_Key_pressed >= 0) && (g_Key_pressed <= 9) )
			{
				//Save the number that the user will enter it in the first 5 elements in global array g_New_Password
				if(counter < PASSWORD_SIZE)
				{
					g_New_Password[counter]=g_Key_pressed;
					/* Print :
							
												*
					* On screen
					*/
					LCD_displayCharacter('*');
					counter ++ ;
				}
			}
			prev_key = g_Key_pressed;//Assign the current value of keypressed in prev_key to handle debouncing problem
		}
	}
}

/* Description :
 1- Function gets a new password for the second time for confirmation from user 
 2- Save it in the second 5 elements of global array g_New_Password
 */
void Re_Enter_New_Password(void)
{
	LCD_clearScreen();//Clear screen from any previous data displayed on LCD

		/* Print :
							Please Re Enter New Password
		* On screen
	*/
	LCD_displayStringRowColumn(0,4,"Please Re Enter New Password");
	LCD_moveCursor(1,10);//move to the second row on LCD
	uint8 counter=0 ;// Initial local counter for looping process
	// Initial local prev_key for save the previous value entered by keypad on it during to debouncing problem
	uint8 prev_key = 0;
	//Wait until user entered a new key and save it in global variableg_Key_pressed
	g_Key_pressed = KEYPAD_getPressedKey();
	//If user enter "=" that means he entered the password so break the loop
	while(g_Key_pressed != '=')
	{
		//Wait until user entered a new key and save it in global variableg_Key_pressed
		g_Key_pressed = KEYPAD_getPressedKey();
		if (g_Key_pressed == prev_key)//This line to handle debouncing duo to keypad
		{
			// Same key is pressed again, wait for debouncing
			_delay_ms(500);
			/*Assign the value of Debounce_Handler in prev key to take another from 0:9 only
			 and not not equal '+'or '-' or '*' or '/' or '='
			*/
			prev_key = Debounce_Handler ;
		}
		else
		{
			/* - Now debouncing problem has been solved so waiting for taking a number from user
				 - Number should bu in range of 0:9 and not equal'+'or '-' or '*' or '/' or '='
			*/
			if ((g_Key_pressed >= 0) && (g_Key_pressed <= 9))
			{
				//Save the number that the user will enter it in the second 5 elements in global array g_New_Password

				if(counter < PASSWORD_SIZE)
				{
					g_New_Password[counter+5]=g_Key_pressed;
					/* Print :
							
												*
					* On screen
					*/
					LCD_displayCharacter('*');
					counter ++ ;
				}
			}
			prev_key = g_Key_pressed;//Assign the current value of keypressed in prev_key to handle debouncing problem
		}
	}
}

/*
* Description :
 1- Function to send New and Re-new or Old Password to microcontroller 1 
*/
void Send_Password_To_Be_Checked(const uint8 arr[])
{
	/*
	Send "Send" command to tell microcontroller2 that 
	microcontroller1 will start send Password to be checked
	*/
	UART_sendByte(Send);
	uint8 count1 =0 ;// Initial local counter for looping process
	while (count1 !=(PASSWORD_SIZE*2))
	{
		UART_sendByte(g_New_Password[count1]);//Send Password
		count1 ++;
	}
}

/* Description :
 1- Function receives the result of checking the new password from microcontroller2
 2- If the New and Re-new Password are identical it sends a command to microcontroller2 to store it in EEPROM
 */
void Receive_The_Result_Of_New_Password(void)
{
	// Wait until Receive a "send"command from microcontroller2 to get the result of checking
	while(UART_recieveByte()!= Send);
	if (UART_recieveByte()==  FALSE)//If the 2 password are different 
	{
		LCD_clearScreen();//Clear screen from any previous data displayed on LCD

		/* Print :
							You Entered 2 Different
							Passwords Please Try Again !!
		* On screen
		*/
		LCD_displayString("You Entered 2 Different");
		LCD_displayStringRowColumn(1,0,"Passwords Please Try Again !!");
		_delay_ms(2000);
		Send_Command(New_Password);//Sending "New_Password" to make microcontroller 2 starting receive a new password
		Setup_A_New_Password ();//Call Setup_A_New_Password sequence again
	}
	else//If the 2 password are identical 
	{
		LCD_clearScreen();//Clear screen from any previous data displayed on LCD

		/* Print :
							Password Confirmed ....

		* On screen
	 */
		LCD_displayString("Password Confirmed ....");
		//Send a command to microcontroller2 to save the current password in EEPROM
		Send_Command(W_EEPROM);
	}
}

/* Description :
 1- Function handeles the sequence to make an new password
 */
void Setup_A_New_Password (void)
{
	Get_New_Password();//Take a new password
	_delay_ms(300);// Same key is pressed again, wait for debouncing
	Re_Enter_New_Password();//Re-take a new password for confirmation
	_delay_ms(300);// Same key is pressed again, wait for debouncing
	Send_Password_To_Be_Checked(g_New_Password);//Send New and Re-new password to microcontroller2 
	_delay_ms(300);
	Receive_The_Result_Of_New_Password();//Check the result and send a command to microcontroller2 to save it in EPPROM in case of identicality
	_delay_ms(300);
}

/*************************************************************************************************************/

/* Description :
 1- Function gets an old password from user 
 2- Save it in the first 5 elements of global array g_New_Password
 */
void Enter_Old_Password(void)
{
	LCD_clearScreen();//Clear screen from any previous data displayed on LCD

	/* Print :
							Please Enter Password
		* On screen
	*/
	LCD_displayStringRowColumn(0,4,"Please Enter Password");
	LCD_moveCursor(1,10);
	uint8 counter=0 ;// Initial local counter for looping process
	// Initial local prev_key for save the previous value entered by keypad on it during to debouncing problem
	uint8 prev_key = 0;
	//Wait until user entered a new key and save it in global variable g_Key_pressed
	g_Key_pressed = KEYPAD_getPressedKey();
	//If user enter "=" that means he entered the password so break the loop
	while(g_Key_pressed != '=')
	{
		//Wait until user entered a new key and save it in global variableg_Key_pressed
		g_Key_pressed = KEYPAD_getPressedKey();
		if (g_Key_pressed == prev_key)//This line to handle debouncing due to keypad
		{
			// Same key is pressed again, wait for debouncing
			_delay_ms(500);
			/*Assign the value of Debounce_Handler in prev key to take another from 0:9 only
			 and not not equal '+'or '-' or '*' or '/' or '='
			*/
			prev_key = Debounce_Handler ;
		}
		else
		{
			/* - Now debouncing problem has been solved so waiting for taking a number from user
				 - Number should be in range of 0:9 and not equal'+'or '-' or '*' or '/' or '='
			*/
			if ((g_Key_pressed >= 0) && (g_Key_pressed <= 9))
			{
				//Save the number that the user will enter it in the first 5 element in global array g_New_Password
				if(counter < PASSWORD_SIZE)
				{
					g_New_Password[counter]=g_Key_pressed;
					/* Print :
							
												*
					* On screen
					*/
					LCD_displayCharacter('*');
					counter ++ ;
				}
			}
			prev_key = g_Key_pressed;//Assign the current value of keypressed in prev_key to handle debouncing problem
		}
	}
}

/* Description :
 1- Function receives the result of checking the old password from microcontroller2
 2- If the old password matches with the password in EEPROM , it sends a command to microcontroller2 to open the door 
 		or changing password according to the date provided
 */
void Receive_The_Result_Of_OLD_Password(void)
{
		// Wait until Receive a "send"command from microcontroller2 to get the result of checking
	while(UART_recieveByte()!= Send);
	uint8 result = UART_recieveByte();//Assign the value of UART_recieveBytein local variable result
	if (result==  FALSE)//If the 2 password are different 
	{
		LCD_clearScreen();//Clear screen from any previous data displayed on LCD

		/* Print :
							You Entered a wrong
							Password Please Try Again !!
		* On screen
		*/
		LCD_displayString("You Entered a wrong");
		LCD_displayStringRowColumn(1,0,"Password Please Try Again !!");
		_delay_ms(2000);
		if (g_operator_plus ==1)//That means the program it Opening Door Mode
		{
			g_flag_status ++;//Increment g_flag_status by one
			/*
			Check if g_flag_status not equal 3 that means that user entered the password wrong for less than 3 times
			*/
			if (g_flag_status!=3)
			{
				Send_Command('+');//send "+" command to microcontroller2
				GET_And_Check_Old_Password();//Call GET_And_Check_Old_Password sequence again
			}

			/*
			Check if g_flag_status equal 3 that means that user entered the password wrong for than 3 times
			*/
			else if (g_flag_status==3)
			{
				g_flag_status=1;//Set g_flag_status to One
				Send_Command(buzzer);//send "buzzer" command to microcontroller2

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
				Timer1_setCallBack(Handle_Screen_Alert);

				LCD_clearScreen();//Clear screen from any previous data displayed on LCD

				/* Print :
							     ALERT!! ALERT!! ALERT!!
							     THIEEF ! ! !
				* On screen
				*/
				LCD_displayStringRowColumn(0,4,"ALERT!! ALERT!! ALERT!!");
				LCD_displayStringRowColumn(1,11,"THIEEF ! ! !");
				while (g_flag_status!=0){};//Wait until the timer counts the required time and change global flag value
			}
			g_operator_plus =0;//Set g_flag_status to Zero
		}
		else //That means the program it Changing password Mode
		{
			Send_Command('-');//Send a command '-' to microcontroller2
			GET_And_Check_Old_Password();//Call GET_And_Check_Old_Password sequence again
		}
	}
	else if (result == TRUE)//If the 2 password are identical 
	{
		LCD_clearScreen();//Clear screen from any previous data displayed on LCD

	/* Print :
							Correct Password ....

		* On screen
	 */
		LCD_displayString("Correct Password ....");
		_delay_ms(1000);
		if (g_operator_plus ==1)//That means the program it Opening Door Mode
		{
			Send_Command(motor);//Send a command 'motor' to microcontroller2
			Open_The_door();//Perform open the door sequence on LCD
			g_operator_plus =0;//Set g_flag_status to Zero
		}
	}
}

/* Description :
 1- Function handeles the sequence to enter and check the password
 */
void GET_And_Check_Old_Password (void)
{
	Enter_Old_Password();//Take the old password
	_delay_ms(300);// Same key is pressed again, wait for debouncing
	Send_Password_To_Be_Checked(g_New_Password);//Send New and Re-new password to microcontroller2 
	_delay_ms(300);
	Receive_The_Result_Of_OLD_Password();//Check the result and send a command to microcontroller2 to open the door on change password in case of identicality
	_delay_ms(300);
}

/* Description :
 1- Function handles the sequence of opening door on screen
 */
void Open_The_door(void)
{
	LCD_clearScreen();//Clear screen from any previous data displayed on LCD

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
	  * Check the old password with the local array password
	  * Call setcallback function to perform the desired action when timer count 
	*/
	Timer_ConfigType Timer_Configuration = {Timer1_CHA,0,7813,Compare,Fcpu_1024};
	Timer_init(&Timer_Configuration);
	Timer1_setCallBack(Handle_Screen_Motor_Status);

	/* Print :
							Door is opening
							
		* On screen
	*/
	LCD_displayStringRowColumn(0,4,"Door is opening");
	while (g_flag_status!=1){};//Waiting until g_flag_status change its value by one by Handle_Screen_Motor_Status function that works by timer
	LCD_clearScreen();//Clear screen from any previous data displayed on LCD

	/* Print :
							Holding......
							
		* On screen
	*/
	LCD_displayStringRowColumn(0,4,"Holding......");
	while (g_flag_status!=2){};//Waiting until g_flag_status change its value by two by Handle_Screen_Motor_Status function that works by timer
	LCD_clearScreen();//Clear screen from any previous data displayed on LCD

	/* Print :
							Door is closing
							
		* On screen
	*/
	LCD_displayStringRowColumn(0,4,"Door is closing");
	while (g_flag_status!=3){};//Waiting until g_flag_status change its value by three by Handle_Screen_Motor_Status function that works by timer
}


/* Description :
 1- Initiates microcontroller2 modules (global interrupts , UARt module ,LCD module )
 */
void Init_Microcontroller1_Modules(void)
{
	SREG |= (1<<7); ///Enable global interrupts in MC.

	//Enable LCD module
	LCD_init();

	//Enable UARt module
	Uart_ConfigType UART_Configuration ={_9600 ,_8_Bits, Disable,_1_bit,Asynchronous_Operation,Asynchronous__Operation} ;
	UART_init(&UART_Configuration);
}
/*****************************************************************************************************************
 *                               Extra  Features Functions
 ********************************************************************************************************************/

/* Description :
 * Function that display the new password and the re-typing of it
   before sends it to compare between 2 passwords in micro 2
 */
/*
void Display_Password(void)
{
	LCD_clearScreen();
	uint8 count =0 ;
	LCD_moveCursor(0,13);
	while (count!=PASSWORD_SIZE)
	{
		LCD_intgerToString(g_New_Password[count]);
		count ++ ;
	}
	count=0;
	LCD_moveCursor(1,13);
	while (count!=PASSWORD_SIZE)
	{
		LCD_intgerToString(g_New_Password[count+5]);
		count ++ ;
	}
}
 */
/* Description :
 * Function that read the old password from microcontroller2 and display it on LCD on microcontroller1
 */

/*
void Read_Old_Password_From_EEPROM(void)
{
	LCD_clearScreen();
	uint8 count=0 ;
	uint8 arr[5];
	while (UART_recieveByte() != Send );
	while(count<PASSWORD_SIZE)
	{
		arr[count]=UART_recieveByte();
		count++;
	}
	count=0;
	while(count<PASSWORD_SIZE)
	{
		LCD_intgerToString(arr[count]);
		count++;
	}
}
 */


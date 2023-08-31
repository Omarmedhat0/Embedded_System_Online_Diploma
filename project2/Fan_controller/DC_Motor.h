/******************************************************************************
 * Module: DC_Motor
 *
 * File Name : DC_Motor.h
 *
 * Description: header file for the ATmega16 DC_Motor driver
 *
 * Author: Omar Medhat
 *
*******************************************************************************/
#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"
/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define DC_motor_PIN_1		PIN0_ID
#define DC_motor_PIN_2		PIN1_ID
#define DC_motor_PORT		PORTB_ID
/*******************************************************************************
 *                               Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
	CW , A_CW ,stop
}DcMotor_State;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Description : Function to initialize the DC Motor
 * The Function responsible for setup the direction for the two motor pins through the GPIO driver.
 * Stop at the DC-Motor at the beginning through the GPIO driver.
 */
void DcMotor_Init(void);

/*
 * Description
 * The function responsible for rotate the DC Motor CW/ or A-CW or stop the motor based on the state input state value.
 * Send the required duty cycle to the PWM driver based on the required speed value.
 */
void DcMotor_Rotate(DcMotor_State state,uint8 speed);

#endif /* DC_MOTOR_H_ */

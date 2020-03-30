/*
 * SERVO.c
 *
 *  Created on: Sep 16, 2019
 *      Author: Assem
 */

#include "../../STD_Types.h"
#include "../../macros.h"
#include "../../MCAL/DIO/DIO.h"
#include "SERVO.h"
#include "../../MCAL/TIMER/TIMER1/TIMER1.h"
#include "../../MCAL/TIMER/TIMER0/TIMER0.h"
#define F_CPU	8000000UL
#include "avr/delay.h"


extern void SERVO_f32Init(u8 u8Pos,u16 delay,u16 Val,f32 f32angle
		,u16 u16prescaler,u8 u8Timer)
{
/*start: 650, middle 1700, end:2550 *for 8 prescaler* */
	static f32 val=650.0;
	f32 OCR=0;

	switch (u8Pos)
	{
		case SERV_START:
			val= 650;
			break;

		case SERV_MIDDLE:
			val= 1700;
			break;

		case SERV_END:
			val= 2550;
			break;

		case SERV_Togg:
	    	val+=20;
		    if(val>2550)
			  {val=650.0;}
			_delay_ms(delay);
		    break;

		case SERV_Angle:
			val=650.0+(f32angle*1900.0/180.0);
			break;

		case SERV_Val:
			val=Val;
			break;
	}
	if(u16prescaler != 0)
	{
		OCR=val/(u16prescaler/8);
	}
	else
	{
		OCR=val;
	}

	switch(u8Timer)
	{
	case SERV_TIMER0:
		TIMER0_vidInit(TIMER0_FAST_PWM);
		TIMER0_setOCR0((u8)OCR);

		break;

	case SERV_TIMER1:
		TIMER1_vidInit(TIMER1_FAST_PWM);
		TIMER1_setOCR1A((u16)OCR);
		break;
	}


}



/*
 * LCD.c
 *
 *  Created on: Aug 23, 2019
 *      Author: Assem
 */

#include "../../STD_Types.h"
#include "../../macros.h"
#include "../../MCAL/DIO/DIO.h"
#include "KEYPAD.h"
#include "KEYPAD_CFG.h"
#define F_CPU	8000000UL
#include "avr/delay.h"

static u8 Columns[] = { C0_PIN , C1_PIN , C2_PIN , C3_PIN} ;
static u8 Rows[] = {R0_PIN , R1_PIN , R2_PIN , R3_PIN} ;

void KEYPAD_vidInit(void)
{
    /*Set columns ports as output*/
    DIO_vidSetPortLowNibbleDir(Col_PORT,OUTPUT);
    /*Set columns Ports =1*/
    DIO_vidSetPortLowNibbleValue(Col_PORT,HIGH);
	/*Set Rows ports as input*/
    DIO_vidSetPortHighNibbleDir(Row_PORT,INPUT);
    /*Set Rows Ports =1 to activate pull up resistors*/
    DIO_vidSetPortHighNibbleValue(Row_PORT,HIGH);
}

u8 KEYPAD_u8GetKeyCode (void)
{
	u8 retVal=0, c , r ;
	while(retVal==0){
	for(c=0;c<4;c++)
	{
		/*Activate column by making C=0 so we can check the buttons*/
		DIO_vidSetPinValue(Col_PORT,Columns[c],LOW);
		for(r=0;r<4;r++)
		{

			if( DIO_u8GetPinValue(Row_PORT,Rows[r]) == LOW)
			{
				retVal =((r * 4)+c+1);
				/*wait to depress the key*/
				while(DIO_u8GetPinValue(Row_PORT,Rows[r] ) == LOW);
				_delay_ms(50);
			}
		}
		DIO_vidSetPinValue(Col_PORT,Columns[c],HIGH);
	}
	}
	return retVal ;
}

u8 KEYPAD_u8GetKeyChar(void)
{
	u8 retVal=0;

	switch (KEYPAD_u8GetKeyCode())
	{
	case Key_No1: retVal =  '1';
	break;
	case Key_No2:retVal = '2';
	break;
	case Key_No3:retVal =  '3';
	break;
	case Key_A:retVal =  'A';
	break;
	case Key_No4:retVal =  '4';
	break;
	case Key_No5:retVal =  '5';
	break;
	case Key_No6:retVal =  '6';
	break;
	case Key_B:retVal =  'B';
	break;
	case Key_No7:retVal =  '7';
	break;
	case Key_No8:retVal = '8';
	break;
	case Key_No9:retVal = '9';
	break;
	case Key_C:retVal = 'C';
	break;
	case Key_STAR:retVal = '*';
	break;
	case Key_No0:retVal = '0';
	break;
	case Key_HASH:retVal = '#';
	break;
	case Key_D:retVal = 'D';
	}

	return retVal ;
}

u8 KEYPAD_u8GetKeyNum(void)
{
	u8 retVal=0;

	    switch (KEYPAD_u8GetKeyCode())
	    {
	    case Key_No1: retVal =  1;
		break;
		case Key_No2:retVal = 2;
		break;
		case Key_No3:retVal =  3;
		break;
		case Key_No4:retVal =  4;
		break;
		case Key_No5:retVal =  5;
		break;
		case Key_No6:retVal =  6;
		break;
		case Key_No7:retVal =  7;
		break;
		case Key_No8:retVal = 8;
		break;
		case Key_No9:retVal = 9;
		break;
		case Key_No0:retVal = 0;
		break;

		default :retVal = 0;
		break;
	    }



	return retVal ;
}


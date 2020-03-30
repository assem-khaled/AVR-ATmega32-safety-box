/*
 * app.c
 *
 *  Created on: Aug 31, 2019
 *      Author: Assem
 */

#include "STD_Types.h"
#include "macros.h"
#include "MCAL/DIO/DIO.h"
#include "HAL/KEYPAD/KEYPAD.h"
#include "HAL/KEYPAD/KEYPAD_CFG.h"
#include "HAL/LCD/LCD.h"
#include "HAL/LCD/LCD_CFG.h"
#include "HAL/SERVO/SERVO.h"
#include "MCAL/TW/TW.h"
#include "HAL/EEPROM/EEPROM.h"
#include "MCAL/Interrupt/INTERRUPT.h"
#include "MCAL/Interrupt/INTERRUPT_CFG.h"
#include "MCAL/TIMER/TIMER1/TIMER1.h"
#define F_CPU 8000000UL
#include "avr/delay.h"

u8 LCD_sec = 0, LCD_min = 0, LCD_hr = 0 ,flag=0, eepromf=0;
u16 counter = 0;
f32 int_counter =0.0;

void bank(void)
{
	u8 x[4]={0} ,pass[4]={0} ,i=0 ,n=0 ,ep=0;

	DIO_vidSetPinDir(CPORT,PIN4,OUTPUT);
	DIO_vidSetPinValue(CPORT,PIN4,HIGH);

	EEPROM_u8ReadByte(0x11,&ep);

	if (ep == 0x10)
	{
		LCD_vidClrDis();
		LCD_vidWriteString("  Enter  New         "
				"                      Password");
		for(i=0;i<4;i=i++)
		{
			pass[i] =KEYPAD_u8GetKeyChar();
			if(i==0)
			{
				LCD_vidClrDis();
			}
			//LCD_vidWriteChar('*');
			LCD_vidWriteChar(pass[i]);
			EEPROM_u8WriteByte(i+i+40,pass[i]);
			_delay_ms(50);
		}
		EEPROM_u8WriteByte(0x11,0x9);
		LCD_vidClrDis();
		LCD_vidWriteString("Password Saved");
		_delay_ms(1500);
	}


for(u8 c=0;c<3;c++)
{
	LCD_vidClrDis();
	LCD_vidWriteString(" ENTER PASSWORD");
	for(i=0;i<4;i++)
	{
		x[i] =KEYPAD_u8GetKeyChar();
		if(i==0)
			{
			LCD_vidClrDis();
			}
		LCD_vidWriteChar('*');
	}

	for(i=0;i<4;i++)
		{
			EEPROM_u8ReadByte(i+i+40,&pass[i]);
			_delay_ms(50);
		}

	_delay_ms(200);

		if(x[0]==pass[0] && x[1]==pass[1] && x[2]==pass[2] && x[3]==pass[3])
		{
			DIO_vidSetPinValue(CPORT,PIN4,LOW);
			DIO_vidSetPinDir(CPORT,PIN5,OUTPUT);
			DIO_vidSetPinValue(CPORT,PIN5,HIGH);
			LCD_vidClrDis();
			LCD_vidWriteString("    UNLOCKED");
			SERVO_f32Init(SERV_END,0,0,0,256,SERV_TIMER0);
			_delay_ms(500);
			SERVO_f32Init(SERV_START,0,0,0,256,SERV_TIMER0);
			_delay_ms(800);
			LCD_vidClrDis();
			LCD_vidPrntMyName();
			LCD_vidSetDDRAMadd(LINE2,0);
			LCD_vidWriteString("BALANCE : 3.5$");
			_delay_ms(2000);
			if (eepromf!=1)
			{
			LCD_vidClrDis();
			LCD_vidWriteString(" Press '*' to ");
			LCD_vidSetDDRAMadd(LINE2,0);
			LCD_vidWriteString("Change Password");
			}
			eepromf = KEYPAD_u8GetKeyChar();
			DIO_vidSetPinValue(CPORT,PIN5,LOW);
			SERVO_f32Init(SERV_END,0,0,0,256,SERV_TIMER0);
			return;
		}
		else
		{
			LCD_vidClrDis();
			LCD_vidWriteString(" WRONG PASSWORD");
			_delay_ms(1500);
			n++;
		}

		if(n==3)
		{
			DIO_vidSetPinValue(CPORT,PIN4,LOW);
			DIO_vidSetPinDir(CPORT,PIN7,OUTPUT);
			DIO_vidSetPinDir(CPORT,PIN6,OUTPUT);
			DIO_vidSetPinValue(CPORT,PIN7,HIGH);
			DIO_vidSetPinValue(CPORT,PIN6,HIGH);
			LCD_vidClrDis();
			LCD_vidWriteString("  !EMSK 7ARAMY! ");
			_delay_ms(2000);
			KEYPAD_u8GetKeyChar();
			DIO_vidSetPinValue(CPORT,PIN7,LOW);
			DIO_vidSetPinValue(CPORT,PIN6,LOW);
			n=0;
		}
}
}

void App_fn(void)
{
	counter++;
}


int main ()
{

	INT_vidInterruptInit(INT2);
	KEYPAD_vidInit();
	LCD_vidInit();
	TIMER1_vidInit(TIMER1_COMP1A);
	TIMER1_setCallBack(App_fn);
	EEPROM_vidInit();


	while (1)
	{
		if(!flag)
		{
			if(counter>=20)
			{

				LCD_sec= LCD_sec + (counter/20);
				if(LCD_sec >= 60)
				{
					LCD_sec = LCD_sec - 60;
					LCD_min++;
				}
				if(LCD_min >= 60)
				{
					LCD_min = LCD_min - 60;
					LCD_hr++;
				}
				/*print on LCD*/
				/*clear display*/
				LCD_vidClrDis();
				/*print LCD_hr*/
				if (LCD_hr<10)
				{
					LCD_vidWriteChar('0');
					LCD_vidWriteNum(LCD_hr);
				}
				else
				{
					LCD_vidWriteNum(LCD_hr);
				}
				LCD_vidWriteChar(':');
				/*print LCD_min*/
				if (LCD_min<10)
				{
					LCD_vidWriteChar('0');
					LCD_vidWriteNum(LCD_min);
				}
				else
				{
					LCD_vidWriteNum(LCD_min);
				}
				LCD_vidWriteChar(':');
				/*print LCD_sec*/
				if (LCD_sec<10)
				{
					LCD_vidWriteChar('0');
					LCD_vidWriteNum(LCD_sec);
				}
				else
				{
					LCD_vidWriteNum(LCD_sec);
				}
			  counter = 0;

			}
		}
		else if(flag)
		{
			bank();
			if (eepromf=='*')
			{
				EEPROM_u8WriteByte(0x11,0x10);
				_delay_ms(20);
				eepromf=1;
				bank();
				eepromf=0;
			}
			flag=0;
		}
	}

}


ISR(ISR_INT2)
{
flag=flag^1;

}



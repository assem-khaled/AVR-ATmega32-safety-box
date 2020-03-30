/*
 * LCD.c
 *
 *  Created on: Aug 23, 2019
 *      Author: Assem
 */

#include "../../STD_Types.h"
#include "../../macros.h"
#include "../../MCAL/DIO/DIO.h"
#include "LCD.h"
#include "LCD_CFG.h"
#define F_CPU	8000000UL
#include "avr/delay.h"



static void LOC_vidSendInstruction(u8 Ins);

extern void LCD_vidInit(void)
{
	/* initializing LCD */
	DIO_vidSetPortDir(LCD_PORT,OUTPUT);
	DIO_vidSetPinDir(LCD_RSPORT,LCD_RSPIN,OUTPUT);
	DIO_vidSetPinDir(LCD_RWPORT,LCD_RWPIN,OUTPUT);
	DIO_vidSetPinDir(LCD_EPORT,LCD_EPIN,OUTPUT);

	_delay_ms(30) ;
	LOC_vidSendInstruction(0b00111100);
	_delay_ms(2);
	LOC_vidSendInstruction(0b00001100);
	_delay_ms(2);
	LOC_vidSendInstruction(0b00000001);
	_delay_ms(2);
	LOC_vidSendInstruction(0b00000110);
}

static void LOC_vidSendInstruction(u8 Ins)
{
	/*set RS = 0*/
	DIO_vidSetPinValue(LCD_RSPORT,LCD_RSPIN,0) ;
	/*set RW = 0*/
	DIO_vidSetPinValue(LCD_RWPORT,LCD_RWPIN,0) ;
	/*Set D0~D7*/
	DIO_vidSetPortValue(LCD_PORT,Ins);
	/*Falling edge*/
	DIO_vidSetPinValue(LCD_EPORT,LCD_EPIN,HIGH);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_EPORT,LCD_EPIN,LOW);
}

extern void LCD_vidWriteChar(u8 ch)
{
	/*set RS = 1*/
	DIO_vidSetPinValue(LCD_RSPORT,LCD_RSPIN,1) ;
	/*set RW = 0*/
	DIO_vidSetPinValue(LCD_RWPORT,LCD_RWPIN,0) ;
	/*Set D0~D7*/
	DIO_vidSetPortValue(LCD_PORT,ch);
	/*Falling edge*/
	DIO_vidSetPinValue(LCD_EPORT,LCD_EPIN,HIGH);
	_delay_ms(1);
	DIO_vidSetPinValue(LCD_EPORT,LCD_EPIN,LOW);
	/*Execution Time*/
	_delay_ms(1);
}

extern void LCD_vidWriteString(u8 String[])
{
	u8 i=0;
	while(String[i] != 0)
	{
		LCD_vidWriteChar(String[i]);
		i++;
	}

}

/*
extern void LCD_vidWriteNum1(u16 u16Num)
{
	u8 k =0 , i =0 ;
	f32 h =0;
	s16 c = 0  ;
	if(u16Num <10)
	{
		LCD_vidWriteChar(u16Num + 0x30);
	}
	else if(u16Num < 100)
	{
	   for( i = 89; i>8;i=i-10)
	   {
     	if(u16Num > i)
	    	{
		     k = (i+1)/10;//ex: 89+1=90/10-> 9
	    	LCD_vidWriteChar(k + 0x30);
	    	u16Num = u16Num - (i+1) ;
	    	LCD_vidWriteChar(u16Num+ 0x30);
		    }
	   }
	}
	else if(u16Num < 1000)
	{
		   for(c = 899; c>89;c=c-100)
		   {
			   if(u16Num > c)
			   {
				    k = (c+1)/100;  //ex: 899+1=900/100-> 9
			    	LCD_vidWriteChar(k + 0x30);
			    	u16Num =u16Num - (c+1);

			    	if(u16Num <10)
			    	{
			    		LCD_vidWriteChar('0');
			    		LCD_vidWriteChar(u16Num + 0x30);
			    	}
			    	else
			    	{
					   	   for(h = 89; h>8;h=h-10)
					   	   {
					        	if(u16Num > h)
					   	    	{
					   		    k = (h+1)/10;  //ex: 89+1=90/10-> 9
					   	    	LCD_vidWriteChar(k + 0x30);
					   	    	u16Num = u16Num - (h+1) ;
					   	    	LCD_vidWriteChar(u16Num+ 0x30);
					   		    }
					   	   }
			    	}
			   }

		   }

	}
}
*/

extern void LCD_vidWriteNum(u32 u32Num)
{
	u8  i , j , temp , num[10]={0} ;

	if (u32Num == 0)
	{
		LCD_vidWriteChar('0');
		return;
	}

	for(i=0;u32Num>0;i++)
		{
			num[i]=u32Num%10 + 0x30;
			u32Num=u32Num/10;
		}
	for(j=0,i--;j<i;j++,i--)
		{
			temp=num[i];
			num[i]=num[j];
			num[j]=temp;
		}
	LCD_vidWriteString(num);
}

extern void LCD_vidShift(u8 direction)
{
	LOC_vidSendInstruction(direction);
	/*Execution Time*/
	_delay_ms(1);
}

extern void LCD_vidRetHome(void)
{
	LOC_vidSendInstruction(0x02);
	/*Execution Time*/
	_delay_ms(2);
}

extern void LCD_vidClrDis(void)
{
	LOC_vidSendInstruction(0x01);
	/*Execution Time*/
	_delay_ms(2);
}

extern void LCD_vidSetDDRAMadd(u8 Line, u8 Address)
{
	LOC_vidSendInstruction((Line + Address));
	/*Execution Time*/
	_delay_ms(1);
}

extern void LCD_vidSetCGRAMadd(void)
{
	LOC_vidSendInstruction(0b01000000);
	/*Execution Time*/
	_delay_ms(1);
}

extern void LCD_vidPrntMyName(void)
{
	LCD_vidWriteChar('A');
	_delay_ms(20);
	LCD_vidWriteChar('S');
	_delay_ms(20);
	LCD_vidWriteChar('S');
	_delay_ms(20);
	LCD_vidWriteChar('E');
	_delay_ms(20);
	LCD_vidWriteChar('M');
	_delay_ms(20);
	LCD_vidWriteChar(' ');
	_delay_ms(20);
	LCD_vidWriteChar('K');
	_delay_ms(20);
	LCD_vidWriteChar('H');
	_delay_ms(20);
	LCD_vidWriteChar('A');
	_delay_ms(20);
	LCD_vidWriteChar('L');
	_delay_ms(20);
	LCD_vidWriteChar('E');
	_delay_ms(20);
	LCD_vidWriteChar('D');

}

extern void LCD_vidPrntTime(void)
{
	static u8 LCD_sec = 0, LCD_min = 0, LCD_hr = 0;

	LCD_sec++ ;
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

}


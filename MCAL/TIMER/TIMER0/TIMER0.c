/*
 * TIMER.c
 *
 *  Created on: Sep 6, 2019
 *      Author: Assem
 */

#include "../../../STD_Types.h"
#include "../../../macros.h"
#include "../../DIO/DIO.h"
#include "TIMER0.h"
#define F_CPU 8000000UL
#include "avr/delay.h"

/*Status Register Bit 7 – I: Global Interrupt Enable*/
#define SREG_REGISTER *((volatile u8*) 0x5F)
#define SREG_I_REG 7
/*Timer/Counter Control Register*/
#define TCCR0_REGISTER *((volatile u8*)0x53)
#define CS00_REG 0
#define CS01_REG 1
#define CS02_REG 2
#define WGM00_REG 6
#define WGM01_REG 3
#define COM00_REG 4
#define COM01_REG 5
#define FOC0_REG 7
/*Timer/Counter0 Register*/
#define TCNT0_REGISTER *((volatile u8*)0x52)
/*Output Compare Register*/
#define OCR0_REGISTER *((volatile u8*)0x5C)
/*Timer/Counter Interrupt Mask Register*/
#define TIMSK_REGISTER *((volatile u8*)0x59)
#define TOIE0_REG 0
#define OCIE0_REG 1
/*Timer/Counter Interrupt Flag Register*/
#define TIFR_REGISTER *((volatile u8*)0x58)
#define TOV0_REG 0
#define OCF0_REG 1

u16 Timer0_counter ;
void (*Timer_CallBack0)(void)=NULL;

void TIMER0_vidInit(u8 TIMER0_mode)
{
	switch (TIMER0_mode)
	{
	case TIMER0_COMP:
	/*Waveform Generation Mode*/
	set_bit(TCCR0_REGISTER,WGM01_REG);
	//TCNT0_REGISTER=1;
    OCR0_REGISTER=250;

    /*Enable interrupt*/
	set_bit(SREG_REGISTER,SREG_I_REG);
	set_bit(TIMSK_REGISTER,OCIE0_REG);

	/* prescaller -> Enable */
	set_bit(TCCR0_REGISTER,CS01_REG);/*prescaling 8*/
	break;

	case TIMER0_OVF:
	    TCNT0_REGISTER=0;

	    /*Enable interrupt*/
		set_bit(SREG_REGISTER,SREG_I_REG);
		set_bit(TIMSK_REGISTER,TOIE0_REG);

		/* prescaller -> Enable */
	    //8 prescaling
		set_bit(TCCR0_REGISTER,CS01_REG);
	    //1024 prescaling
		//set_bit(TCCR0_REGISTER,CS00_REG);
		//set_bit(TCCR0_REGISTER,CS02_REG);

		//Timer0_counter = 0;
	break;

	case TIMER0_FAST_PWM:
		DIO_vidSetPinDir(BPORT,PIN3,OUTPUT);
		/*Waveform Generation Mode*/
		set_bit(TCCR0_REGISTER,COM01_REG);
		set_bit(TCCR0_REGISTER,WGM00_REG);
		set_bit(TCCR0_REGISTER,WGM01_REG);
		OCR0_REGISTER=10;// we use set_OCR0

		/* prescaller -> Enable */
		//set_bit(TCCR0_REGISTER,CS00_REG);/*prescaling 256*/
		//set_bit(TCCR0_REGISTER,CS01_REG);
		set_bit(TCCR0_REGISTER,CS02_REG);
	break;
	}

}

/*
ISR(ISR_TIMER0_COMP)
 {

		if (Timer_CallBack0 !=NULL)
		{
			Timer_CallBack0();
		}

 }
void TIMER0_setCallBack (void (*fn)(void))
 {
 	Timer_CallBack0  = fn ;
 }
*/

/*
ISR(ISR_TIMER0_OVF)
{
	 Timer0_counter++;

	 if (counter==3907)
	 {
		 DIO_vidSetPinDir(DPORT,PIN0,OUTPUT);

		 DIO_vidSetPinValue(DPORT,PIN0,HIGH);
		 _delay_ms(2000);
		 DIO_vidSetPinValue(DPORT,PIN0,LOW);

		 TCNT0_REGISTER=192;
		 Timer0_counter=0;
	 }

}
*/

u8 TIMER0_readTCNT0(void)
{
	return TCNT0_REGISTER;
}

void TIMER0_setTCNT0(u16 u16new)
{
	TCNT0_REGISTER=u16new;
}

void TIMER0_setOCR0(u8 u8num)
{
	OCR0_REGISTER=u8num;
}

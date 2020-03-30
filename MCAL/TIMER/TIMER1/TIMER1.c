/*
 * TIMER1.c
 *
 *  Created on: Sep 7, 2019
 *      Author: Assem
 */

#include "../../../STD_Types.h"
#include "../../../macros.h"
#include "../../DIO/DIO.h"
#include "TIMER1.h"
#define F_CPU 8000000UL
#include "avr/delay.h"

/*Status Register Bit 7 – I: Global Interrupt Enable*/
#define SREG_REGISTER *((volatile u8*) 0x5F)
#define SREG_I_REG 7
/*Timer/Counter1 Control Register A*/
#define TCCR1A_REGISTER *((volatile u8*) 0x4F)
#define WGM10_REG 0
#define WGM11_REG 1
#define FOC1B_REG 2
#define FOC1A_REG 3
#define COM1B0_REG 4
#define COM1B1_REG 5
#define COM1A0_REG 6
#define COM1A1_REG 7
/*Timer/Counter1 Control Register B*/
#define TCCR1B_REGISTER *((volatile u8*) 0x4E)
#define CS10_REG 0
#define CS11_REG 1
#define CS12_REG 2
#define WGM12_REG 3
#define WGM13_REG 4
#define ICES1_REG 6
#define ICNC1_REG 7
/*Output Compare Register 1 A*/
#define OCR1AH_REGISTER *((volatile u16*) 0x4B)
#define OCR1AL_REGISTER *((volatile u16*) 0x4A)
/*Output Compare Register 1 B*/
#define OCR1BH_REGISTER *((volatile u16*) 0x49)
#define OCR1BL_REGISTER *((volatile u16*) 0x48)
/*Timer/Counter1 Register*/
#define TCNT1H_REGISTER *((volatile u16*) 0x4D)
#define TCNT1L_REGISTER *((volatile u16*) 0x4C)
/*Input Capture Register 1*/
#define ICR1H_REGISTER *((volatile u16*) 0x47)
#define ICR1L_REGISTER *((volatile u16*) 0x46)
/*Timer/Counter Interrupt Mask Register*/
#define TIMSK_REGISTER *((volatile u8*)0x59)
#define TOIE1_REG 2
#define OCIE1B_REG 3
#define OCIE1A_REG 4
#define TICIE1_REG 5
/*Timer/Counter Interrupt Flag Register*/
#define TIFR_REGISTER *((volatile u8*)0x58)
#define TOV1_REG 2
#define OCF1B_REG 3
#define OCF1A_REG 4
#define ICF1_REG 5


void (*Timer_CallBack)(void)=NULL;

void TIMER1_vidInit(u8 TIMER1_mode)
{
	switch (TIMER1_mode)
	{
	case TIMER1_FAST_PWM:
	DIO_vidSetPinDir(DPORT,PIN5,OUTPUT);
	/*Waveform Generation Mode*/
	set_bit(TCCR1A_REGISTER,COM1A1_REG);
	set_bit(TCCR1A_REGISTER,WGM11_REG);
	set_bit(TCCR1B_REGISTER,WGM12_REG);
	set_bit(TCCR1B_REGISTER,WGM13_REG);
	OCR1AL_REGISTER=15000; // we use set_OCR1A
	ICR1L_REGISTER= 20000;

	/* prescaller -> Enable */
	set_bit(TCCR1B_REGISTER,CS11_REG);/*prescaling 8*/
	break;

	case TIMER1_COMP1A:
	/*Waveform Generation Mode*/
	set_bit(TCCR1B_REGISTER,WGM12_REG);
	OCR1AL_REGISTER=50000;

    /*Enable interrupt*/
	set_bit(SREG_REGISTER,SREG_I_REG);
	set_bit(TIMSK_REGISTER,OCIE1A_REG);

	/* prescaller -> Enable */
	set_bit(TCCR1B_REGISTER,CS11_REG);/*prescaling 8*/
	break;
	}

}

ISR(ISR_TIMER1_COMPA)
{

	if (Timer_CallBack!=NULL)
	{
		Timer_CallBack();
	}

}

void TIMER1_setCallBack (void (*fn)(void))
{
	Timer_CallBack  = fn ;
}


void TIMER1_setOCR1A(u16 u16num)
{
	OCR1AL_REGISTER=u16num;
}


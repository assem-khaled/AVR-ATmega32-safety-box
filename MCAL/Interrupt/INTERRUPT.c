/*
 * Intrupt.c
 *
 *  Created on: Sep 4, 2019
 *      Author: Assem
 */

#include "../../STD_Types.h"
#include "../../macros.h"
#include "INTERRUPT.h"
#include "INTERRUPT_CFG.h"
#include "../DIO/DIO.h"
#define F_CPU	8000000UL
#include "avr/delay.h"

/*Local defines */
/*External Interrupts*/

/*Status Register Bit 7 – I: Global Interrupt Enable*/
#define SREG_REGISTER *((volatile u8*) 0x5F)
#define SREG_I_REG 7
/*General Interrupt Control Register*/
#define GICR_REGISTER *((volatile u8*) 0x5B)
#define INT0_REG 6
#define INT1_REG 7
#define INT2_REG 5
/*General Interrupt Flag Register*/
#define GIFR_REGISTER *((volatile u8*) 0x5A)
#define INTF0_REG 6
#define INTF1_REG 7
#define INTF2_REG 5
/*MCU Control Register*/
#define MCUCR_REGISTER *((volatile u8*) 0x55)
#define ISC00_REG 0
#define ISC01_REG 1
#define ISC10_REG 2
#define ISC11_REG 3
/*MCU Control and Status Register*/
#define MCUCSR_REGISTER *((volatile u8*) 0x54)
#define ISC2_REG 6

void INT_vidInterruptInit(u8 INTNum)
{
	switch(INTNum)
	{
	case INT0:
	 	/*set PD2 input*/
		DIO_vidSetPinDir(INT_PORT,INT0_PIN,INPUT);
		/*activate pull up res*/
		DIO_vidSetPinValue(INT_PORT,INT0_PIN,HIGH);

		/*Falling edge*/
		set_bit(MCUCR_REGISTER,ISC01_REG);
		/*Rising edge*/
		//set_bit(MCUCR_REGISTER,ISC01_REG);
		//set_bit(MCUCR_REGISTER,ISC00_REG);
		/*Any logical change*/
		//set_bit(MCUCR_REGISTER,ISC01_REG);

		/*Bit 6 – INT0: External Interrupt Request 0 Enable */
		set_bit(GICR_REGISTER,INT0_REG);
		/*Global Interrupt Enable*/
		set_bit(SREG_REGISTER,SREG_I_REG);
	break;

	case INT1:
	 	/*set PD3 input*/
		DIO_vidSetPinDir(INT_PORT,INT1_PIN,INPUT);
		/*activate pull up res*/
		DIO_vidSetPinValue(INT_PORT,INT1_PIN,HIGH);

		/*Falling edge*/
		set_bit(MCUCR_REGISTER,ISC11_REG);
		/*Bit 7 – INT1: External Interrupt Request 1 Enable*/
		set_bit(GICR_REGISTER,INT1_REG);
		/*Global Interrupt Enable*/
		set_bit(SREG_REGISTER,SREG_I_REG);
	break;

	case INT2:
	 	/*set PB2 input*/
		DIO_vidSetPinDir(INT2_PORT,INT2_PIN,INPUT);
		/*activate pull up res*/
		DIO_vidSetPinValue(INT2_PORT,INT2_PIN,HIGH);

		/*Falling edge*/
		//set_bit(MCUCSR_REGISTER,ISC2_REG);
		/*Bit 5 – INT2: External Interrupt Request 2 Enable*/
		set_bit(GICR_REGISTER,INT2_REG);
		/*Global Interrupt Enable*/
		set_bit(SREG_REGISTER,SREG_I_REG);
	break;
	}
}

/*
ISR(ISR_INT0)
{

}


ISR(ISR_INT1)
{

delay
}


ISR(ISR_INT2)
{


}
*/


/*
 * DIO.c
 *
 *  Created on: Aug 17, 2019
 *      Author: Assem
 */

#include "../../STD_Types.h"
#include "../../macros.h"
#include "DIO.h"


/*Local defines*/

/*PORTA Registers*/
#define DDRA_REGISTER  *((volatile u8*) 0x3A)
#define PORTA_REGISTER  *((volatile u8*) 0x3B)
#define PINA_REGISTER    *((volatile u8*) 0x39)

/*PORTB Registers*/
#define DDRB_REGISTER  *((volatile u8*) 0x37)
#define PORTB_REGISTER  *((volatile u8*) 0x38)
#define PINB_REGISTER    *((volatile u8*) 0x36)

/*PORTC Registers*/
#define DDRC_REGISTER  *((volatile u8*) 0x34)
#define PORTC_REGISTER  *((volatile u8*) 0x35)
#define PINC_REGISTER    *((volatile u8*) 0x33)

/*PORTD Registers*/
#define DDRD_REGISTER  *((volatile u8*) 0x31)
#define PORTD_REGISTER  *((volatile u8*) 0x32)
#define PIND_REGISTER    *((volatile u8*) 0x30)


extern void DIO_vidSetPortDir(u8 u8portName, u8 u8PortDir)
{
	switch(u8portName)
	{
	case APORT:
	     	if(u8PortDir==INPUT)
	      	{
	      	   DDRA_REGISTER = 0x00;
	        }
	    	else
	    	{
	     		DDRA_REGISTER = 0xff;
	    	}break;

	case BPORT:
	    	if(u8PortDir==INPUT)
			{
				DDRB_REGISTER = 0x00;
			}
			else
			{
				DDRB_REGISTER = 0xff;
			}break;

	case CPORT:
			if(u8PortDir==INPUT)
			{
				DDRC_REGISTER = 0x00;
			}
			else
			{
				DDRC_REGISTER = 0xff;
			}break;

	case DPORT:
	    	if(u8PortDir==INPUT)
			{
				DDRD_REGISTER = 0x00;
			}
			else
			{
				DDRD_REGISTER = 0xff;
			}break;
	}
}

extern void DIO_vidSetPinDir(u8 u8portName, u8 u8PinNo , u8 u8PinDir)
{
	switch (u8portName)
	{
	case APORT:
		if (u8PinDir==INPUT)
		{
			clr_bit (DDRA_REGISTER,u8PinNo);
		}
		else
		{
			set_bit(DDRA_REGISTER,u8PinNo);
		}break;

	case BPORT:
			if (u8PinDir==INPUT)
			{
				clr_bit (DDRB_REGISTER,u8PinNo);
			}
			else
			{
				set_bit(DDRB_REGISTER,u8PinNo);
			}break;

	case CPORT:
			if (u8PinDir==INPUT)
			{
				clr_bit (DDRC_REGISTER,u8PinNo);
			}
			else
			{
				set_bit(DDRC_REGISTER,u8PinNo);
			}break;

	case DPORT:
			if (u8PinDir==INPUT)
			{
				clr_bit (DDRD_REGISTER,u8PinNo);
			}
			else
			{
				set_bit(DDRD_REGISTER,u8PinNo);
			}break;
	}
}

extern void DIO_vidSetPortHighNibbleDir(u8 u8portName, u8 u8PinDir)
{
	switch (u8portName)
	{
	case APORT:
		if (u8PinDir==INPUT)
		{
			clr_HighNibble(DDRA_REGISTER);
		}
		else
		{
			set_HighNibble(DDRA_REGISTER);
		}break;

	case BPORT:
			if (u8PinDir==INPUT)
			{
				clr_HighNibble(DDRB_REGISTER);

			}
			else
			{
				set_HighNibble(DDRB_REGISTER);
			}break;

	case CPORT:
			if (u8PinDir==INPUT)
			{
				clr_HighNibble(DDRC_REGISTER);
			}
			else
			{
				set_HighNibble(DDRC_REGISTER);
			}break;

	case DPORT:
			if (u8PinDir==INPUT)
			{
				clr_HighNibble(DDRD_REGISTER);
			}
			else
			{
				set_HighNibble(DDRD_REGISTER);
			}break;
	}
}

extern void DIO_vidSetPortLowNibbleDir(u8 u8portName, u8 u8PinDir)
{
	switch (u8portName)
	{
	case APORT:
		if (u8PinDir==INPUT)
		{
			clr_LowNibble(DDRA_REGISTER);
		}
		else
		{
			set_LowNibble(DDRA_REGISTER);
		}break;

	case BPORT:
			if (u8PinDir==INPUT)
			{
				clr_LowNibble(DDRB_REGISTER);

			}
			else
			{
				set_LowNibble(DDRB_REGISTER);
			}break;

	case CPORT:
			if (u8PinDir==INPUT)
			{
				clr_LowNibble(DDRC_REGISTER);
			}
			else
			{
				set_LowNibble(DDRC_REGISTER);
			}break;

	case DPORT:
			if (u8PinDir==INPUT)
			{
				clr_LowNibble(DDRD_REGISTER);
			}
			else
			{
				set_LowNibble(DDRD_REGISTER);
			}break;
	}
}

extern void DIO_vidSetPortValue(u8 u8PortName , u8 u8PortValue)
{
	switch (u8PortName)
		{
			case APORT :
			{
				PORTA_REGISTER = u8PortValue;
			}break;

			case BPORT :
			{
				PORTB_REGISTER = u8PortValue;
			}break ;

			case CPORT :
			{
				PORTC_REGISTER = u8PortValue;
			}break ;

			case DPORT :
			{
				PORTD_REGISTER = u8PortValue;
			}break ;
		}
}

extern void DIO_vidSetPinValue(u8 u8PortName , u8 u8PinNo, u8 u8pinValue)
{
	switch (u8PortName)
		{
			case APORT :
			{
				ass_bit(PORTA_REGISTER,u8PinNo,u8pinValue) ;
			}break;

			case BPORT :
			{
				ass_bit(PORTB_REGISTER,u8PinNo,u8pinValue) ;
			}break ;

			case CPORT :
			{
				ass_bit(PORTC_REGISTER,u8PinNo,u8pinValue) ;
			}break ;

			case DPORT :
			{
				ass_bit(PORTD_REGISTER,u8PinNo,u8pinValue) ;
			}break;
		}
}

extern void DIO_vidSetPortHighNibbleValue(u8 u8PortName , u8 u8pinValue)
{
	switch (u8PortName)
		{
			case APORT :
			{
				ass_HighNibble(PORTA_REGISTER,u8pinValue);
			}break;

			case BPORT :
			{
				ass_HighNibble(PORTB_REGISTER,u8pinValue);
			}break ;

			case CPORT :
			{
				ass_HighNibble(PORTC_REGISTER,u8pinValue);
			}break ;

			case DPORT :
			{
				ass_HighNibble(PORTD_REGISTER,u8pinValue);
			}break;
		}
}

extern void DIO_vidSetPortLowNibbleValue(u8 u8PortName , u8 u8pinValue)
{
	switch (u8PortName)
		{
			case APORT :
			{
				ass_LowNibble(PORTA_REGISTER,u8pinValue) ;
			}break;

			case BPORT :
			{
				ass_LowNibble(PORTB_REGISTER,u8pinValue) ;
			}break ;

			case CPORT :
			{
				ass_LowNibble(PORTC_REGISTER,u8pinValue) ;
			}break ;

			case DPORT :
			{
				ass_LowNibble(PORTD_REGISTER,u8pinValue) ;
			}break;
		}
}

extern u8 DIO_u8GetPortVal(u8 u8PortName)
{
	u8 retVal;
	switch(u8PortName)
	{
	case APORT:
		retVal = PINA_REGISTER;
		break;

	case BPORT:
		retVal = PINB_REGISTER;
		break;

	case CPORT:
		retVal = PINC_REGISTER;
		break;

	case DPORT:
		retVal = PIND_REGISTER;
		break;
	}
	return retVal;
}

extern u8 DIO_u8GetPinValue(u8 u8PortName , u8 u8PinNo)
{
	u8 Value ;
		switch (u8PortName)
		{
			case APORT :
			{
				Value =  get_bit(PINA_REGISTER, u8PinNo);
			}break ;
			case BPORT :
			{
				Value =  get_bit(PINB_REGISTER, u8PinNo);
			}break ;
			case CPORT :
			{
				Value =  get_bit(PINC_REGISTER, u8PinNo);
			}break ;

			case DPORT :
			{
				Value =  get_bit(PIND_REGISTER, u8PinNo);
			}break ;
		}

		return Value ;
}


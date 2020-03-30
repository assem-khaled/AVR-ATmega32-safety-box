/*
 * TW.c
 *
 *  Created on: Oct 11, 2019
 *      Author: Assem
 */

#include "../../STD_Types.h"
#include "../../macros.h"
#include "../DIO/DIO.h"
#include "TW.h"


/*TWI Bit Rate Register*/
#define TWBR_REGISTER *((volatile u8*) 0x20)
#define TWBR0_REG  0
#define TWBR1_REG  1
#define TWBR2_REG  2
#define TWBR3_REG  3
#define TWBR4_REG  4
#define TWBR5_REG  5
#define TWBR6_REG   6
#define TWBR7_REG  7
/*TWI Control Register*/
#define TWCR_REGISTER *((volatile u8*) 0x56)
#define TWIE_REG  0
#define TWEN_REG  2
#define TWWC_REG  3
#define TWSTO_REG 4
#define TWSTA_REG 5
#define TWEA_REG  6
#define TWINT_REG 7
/*TWI Status Register*/
#define TWSR_REGISTER *((volatile u8*) 0x21)
#define TWPS0_REG  0
#define TWPS1_REG  1
#define TWS3_REG   3
#define TWS4_REG   4
#define TWS5_REG   5
#define TWS6_REG   6
#define TWS7_REG   7
/*TWI Data Register*/
#define TWDR_REGISTER *((volatile u8*) 0x23)
#define TWD0_REG   0
#define TWD1_REG   1
#define TWD2_REG   2
#define TWD3_REG   3
#define TWD4_REG   4
#define TWD5_REG   5
#define TWD6_REG   6
#define TWD7_REG   7
/*TWI (Slave) Address Register*/
#define TWAR_REGISTER *((volatile u8*) 0x22)
#define TWGCE_REG  0
#define TWA0_REG   1
#define TWA1_REG   2
#define TWA2_REG   3
#define TWA3_REG   4
#define TWA4_REG   5
#define TWA5_REG   6
#define TWA6_REG   7

void TW_vidInit(void)
{
	//frequency = 222kHZ , prescaller =1
	TWBR_REGISTER = 10;

	// Two Wire Bus Slave Address: 0x1
	// General Call Recognition: Off
	//TWAR_REGISTER= 0x02;

	//TWI Enable
	//TWI Enable acknowledge bit
	TWCR_REGISTER = (1 << TWEA_REG) | (1 << TWEN_REG);

}

void TW_vidSTART(void)
{
	// Send Start Condition
	TWCR_REGISTER = (1 << TWINT_REG) | (1 << TWSTA_REG) | (1 << TWEN_REG);


	//Wait for TWINT flag set in TWCR Register
	while (get_bit(TWCR_REGISTER,TWINT_REG)==0);
}

void TW_vidSTOP(void)
{
	// Send Stop Condition
	TWCR_REGISTER = (1 << TWINT_REG) | (1 << TWEN_REG) | (1 << TWSTO_REG);
}


void TW_vidWRITE(u8 data)
{
	//Load data
	TWDR_REGISTER = data;

	// Send Data
	TWCR_REGISTER = (1 << TWINT_REG) | (1 << TWEN_REG);

	//Wait for TWINT flag set in TWCR Register
	while (get_bit(TWCR_REGISTER,TWINT_REG)==0);
}

u8 TW_u8READ(void)
{
	//enable ACK
	TWCR_REGISTER = (1 << TWINT_REG) | (1 << TWEN_REG) | (1 << TWEA_REG);

	//Wait for TWINT flag set in TWCR Register
	while (get_bit(TWCR_REGISTER,TWINT_REG)==0);

	// Read Data
	return TWDR_REGISTER;
}

u8 TW_u8ACK(void)
{
	//send ACK
	TWCR_REGISTER = (1 << TWINT_REG) | (1 << TWSTO_REG) | (1 << TWEA_REG);

	//Wait for TWINT flag set in TWCR Register
	while (get_bit(TWCR_REGISTER,TWINT_REG)==0);

	return TWDR_REGISTER;
}

u8 TW_u8NACK(void)
{
	//send NACK
	TWCR_REGISTER = (1 << TWINT_REG) | (1 << TWSTO_REG);

	//Wait for TWINT flag set in TWCR Register
	while (get_bit(TWCR_REGISTER,TWINT_REG)==0);

	return TWDR_REGISTER;//
}

u8 TW_u8GetStatus(void)
{
	u8 status;
	status =TWSR_REGISTER & 0xF8;

	return status ;
}

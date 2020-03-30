/*
 * TW.h
 *
 *  Created on: Oct 12, 2019
 *      Author: Assem
 */

#ifndef MCAL_TW_TW_H_
#define MCAL_TW_TW_H_

void TW_vidInit(void);
void TW_vidSTART(void);
void TW_vidSTOP(void);
void TW_vidWRITE(u8 data);
u8 TW_u8READ(void);
u8 TW_u8ACK(void);
u8 TW_u8NACK(void);
u8 TW_u8GetStatus(void);


#define TW_START       		  0x08
#define TW_REP_START          0x10
#define TW_MT_SLA_ACK  		  0x18
#define TW_MT_SLA_NOT_ACK 	  0x20
#define TW_MT_DATA_ACK		  0x28
#define TW_MT_DATA_NOT_ACK	  0x30
#define TW_MT_ARB_LOST 		  0x38

#define TW_MR_ARB_LOST 		  0x38
#define TW_MR_SLA_ACK    	  0x40
#define TW_MR_SLA_NOT_ACK  	  0x48
#define TW_MR_DATA_ACK  	  0x50
#define TW_MR_DATA_NOT_ACK 	  0x58


#endif /* MCAL_TW_TW_H_ */

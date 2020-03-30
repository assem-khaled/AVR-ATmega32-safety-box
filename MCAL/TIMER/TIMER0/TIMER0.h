/*
 * TIMER.h
 *
 *  Created on: Sep 6, 2019
 *      Author: Assem
 */

#ifndef MCAL_TIMER_TIMER0_TIMER0_H_
#define MCAL_TIMER_TIMER0_TIMER0_H_

void TIMER0_vidInit(u8 u8mode);
void TIMER0_setCallBack (void (*fn)(void));
void TIMER0_setTCNT0(u16 u16new);
u8 TIMER0_readTCNT0(void);
void TIMER0_setOCR0(u8 u8num);

#define TIMER0_OVF      0
#define TIMER0_COMP     1
#define TIMER0_FAST_PWM 2

#endif /* MCAL_TIMER_TIMER0_TIMER0_H_ */

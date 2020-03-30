/*
 * TIMER1.h
 *
 *  Created on: Sep 7, 2019
 *      Author: Assem
 */

#ifndef MCAL_TIMER_TIMER1_TIMER1_H_
#define MCAL_TIMER_TIMER1_TIMER1_H_

void TIMER1_vidInit(u8 u8mode);
void TIMER1_setCallBack (void (*fn)(void));
void TIMER1_setOCR1A(u16 u16num);

#define TIMER1_FAST_PWM 0
#define TIMER1_COMP1A    1


#endif /* MCAL_TIMER_TIMER1_TIMER1_H_ */

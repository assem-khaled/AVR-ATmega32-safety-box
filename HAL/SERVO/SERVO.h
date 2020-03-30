/*
 * SERVO.h
 *
 *  Created on: Sep 16, 2019
 *      Author: Assem
 */

#ifndef HAL_SERVO_SERVO_H_
#define HAL_SERVO_SERVO_H_

/*
 *O -> GND
 *O -> VCC
 *O -> control
*/

/* TIMER0 -> PB3
 * TIMER1 -> PD5
*/

extern void SERVO_f32Init(u8 u8Pos,u16 delay,u16 Val,f32 f32angle
		,u16 u16prescaler,u8 u8Timer);

#define SERV_START   0
#define SERV_MIDDLE  1
#define SERV_END     2
#define SERV_Togg    3
#define SERV_Angle   4
#define SERV_Val     5
#define SERV_TIMER0 6
#define SERV_TIMER1 7


#endif /* HAL_SERVO_SERVO_H_ */

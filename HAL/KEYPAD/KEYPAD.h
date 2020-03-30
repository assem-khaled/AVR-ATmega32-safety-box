/*
 * LCD.h
 *
 *  Created on: Aug 23, 2019
 *      Author: Assem
 */

#ifndef HAL_KYE_BAD_H_
#define HAL_KYE_BAD_H_



void KEYPAD_vidInit(void);
u8 KEYPAD_u8GetKeyCode (void);
u8 KEYPAD_u8GetKeyChar(void);
u8 KEYPAD_u8GetKeyNum(void);

#define Key_No1  1
#define Key_No2  2
#define Key_No3  3
#define Key_No4  5
#define Key_No5  6
#define Key_No6  7
#define Key_No7  9
#define Key_No8  10
#define Key_No9  11
#define Key_No0  14
#define Key_A  4
#define Key_B  8
#define Key_C  12
#define Key_D  16
#define Key_STAR  13
#define Key_HASH  15

#endif /* HAL_KYE_BAD_H_ */

/*
 * LCD.h
 *
 *  Created on: Aug 23, 2019
 *      Author: Assem
 */

#ifndef HAL_LCD_H_
#define HAL_LCD_H_



extern void LCD_vidInit(void);
extern void LCD_vidWriteChar(u8 ch);
extern void LCD_vidWriteString(u8 String[]);
extern void LCD_vidWriteNum(u32 u32Num);
//extern void LCD_vidWriteNum1(u16 u16Num);
extern void LCD_vidShift(u8 direction);
extern void LCD_vidRetHome(void);
extern void LCD_vidClrDis(void);
extern void LCD_vidSetDDRAMadd(u8 Line,u8 Address);
extern void LCD_vidSetCGRAMadd(void);
extern void LCD_vidPrntMyName(void);
extern void LCD_vidPrntTime(void);


#define LEFT   0b0000011000
#define RIGHT  0b0000011100

#define LINE1 (0x00+0x80)
#define LINE2 (0x40+0x80)


#endif /* HAL_LCD_H_ */

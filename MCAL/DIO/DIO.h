/*
 * DIO.h
 *
 *  Created on: Aug 17, 2019
 *      Author: Assem
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

/*
 *    0-> Input
 *    1-> Output
 */

extern void DIO_vidSetPortDir(u8 u8portName, u8 u8PortDir);
extern void DIO_vidSetPinDir(u8 u8portName, u8 u8PinNo , u8 u8PinDir);
extern void DIO_vidSetPortHighNibbleDir(u8 u8portName, u8 u8PinDir);
extern void DIO_vidSetPortLowNibbleDir(u8 u8portName, u8 u8PinDir);
extern void DIO_vidSetPortValue(u8 u8PortName , u8 u8PortValue);
extern void DIO_vidSetPinValue(u8 u8PortName , u8 u8PinNo, u8 u8pinValue);
extern void DIO_vidSetPortHighNibbleValue(u8 u8PortName , u8 u8pinValue);
extern void DIO_vidSetPortLowNibbleValue(u8 u8PortName , u8 u8pinValue);
extern u8 DIO_u8GetPortVal(u8 u8PortName);
extern u8 DIO_u8GetPinValue(u8 u8PortName , u8 u8PinNo);


#define APORT 1
#define BPORT 2
#define CPORT 3
#define DPORT 4

#define OUTPUT 1
#define INPUT 0

#define HIGH   1
#define LOW    0


#define PIN0   ((u8)0x00)
#define PIN1   ((u8)0x01)
#define PIN2   ((u8)0x02)
#define PIN3   ((u8)0x03)
#define PIN4   ((u8)0x04)
#define PIN5   ((u8)0x05)
#define PIN6   ((u8)0x06)
#define PIN7   ((u8)0x07)


#endif /* MCAL_DIO_DIO_H_ */


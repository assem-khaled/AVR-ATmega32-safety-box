/*
 * EEPROM.h
 *
 *  Created on: Oct 12, 2019
 *      Author: Assem
 */

#ifndef HAL_EEPROM_EEPROM_H_
#define HAL_EEPROM_EEPROM_H_

void EEPROM_vidInit(void);
u8 EEPROM_u8WriteByte(u8 addr, u8 data);
u8 EEPROM_u8ReadByte(u8 addr, u8 *data);


#define ACK 	 0
#define NACK	 1

#endif /* HAL_EEPROM_EEPROM_H_ */

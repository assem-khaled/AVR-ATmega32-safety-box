/*
 * EEPROM.c
 *
 *  Created on: Oct 12, 2019
 *      Author: Assem
 */

#include "../../STD_Types.h"
#include "../../macros.h"
#include "../../MCAL/DIO/DIO.h"
#include "EEPROM.h"
#include "../../MCAL/TW/TW.h"



void EEPROM_vidInit(void)
{
	TW_vidInit();
}

u8 EEPROM_u8WriteByte(u8 addr, u8 data)
{
	  u8 state = 0;

	  /* Start TWI*/
	  TW_vidSTART();
	  /* Get State*/
	  state = TW_u8GetStatus();
	  /* Check if TWI Start*/
	  if (state != TW_START)
	  {
	    return NACK;
	  }
	  // Send Slave Address -> For EEPROM 24cXX Address of Chip is 0b1010
	  //Set Action To Write -> 0
	  //So, we need to send 0xA0

	  TW_vidWRITE(0xA0);
	  // Get Status
	  state = TW_u8GetStatus();
	  // Check if it is TW_MT_SLA_ACK
	  if (state != TW_MT_SLA_ACK)
	  {
	    return NACK;
	  }

	  // Write the Rest of Location Address(8 Bits)
	  TW_vidWRITE(addr);

	  // Get State
	  state = TW_u8GetStatus();

	  // check if it is TW_MT_DATA_ACK
	  if (state != TW_MT_DATA_ACK)
	  {
	    return NACK;
	  }

	  // Send Data
	  TW_vidWRITE(data);

	  // Get Status
	  state = TW_u8GetStatus();

	  // Check if it is TW_MT_DATA_ACK
	  if (state != TW_MT_DATA_ACK)
	  {
	    return NACK;
	  }

	  // TWI Stop
	  TW_vidSTOP();
	  // Return ACK
	  return ACK;
}

u8 EEPROM_u8ReadByte(u8 addr, u8 *data)
{
  u8 state = 0;

  // Start TWI
  TW_vidSTART();

  // Get State
  state = TW_u8GetStatus();

  /* Check if I2C_ Start*/
  if (state != TW_START)
  { return NACK;}

  //Send Slave Address -> For EEPROM 24cXX Address of Chip is 0b1010
  //  Set Action To Write -> 1
  // So, we need to send 0xA0


  TW_vidWRITE(0xA0);

  // Get Status
  state = TW_u8GetStatus();

  // Check if it is TW_MT_SLA_ACK
  if (state != TW_MT_SLA_ACK)
   {return NACK;}

  // Write the Rest of Location Address(8 Bits)
  TW_vidWRITE(addr);

  /*Get State*/
  state = TW_u8GetStatus();

  /* check if it is TW_MT_DATA_ACK*/
  if (state != TW_MT_DATA_ACK)
    return NACK;

  // Now The Master Will Be Master Receiver

  // Now we need to Send Start Bit Again
  // Start I2C_
  TW_vidSTART();

  // Get State
  state = TW_u8GetStatus();

  /* Check if TW_REP_START*/
  if (state != TW_REP_START)
    return NACK;

  // Send Slave Address -> For EEPROM 24cXX Address of Chip is 0b1010
  //  Set Action To Write -> 1
  // So, we need to send 0xA1


  TW_vidWRITE(0xA1);
  // Get Status
  state = TW_u8GetStatus();

  // Check if it is TW_MR_SLA_ACK
  if (state != TW_MR_SLA_ACK)
    return NACK;

  // Read Data
  *data = TW_u8READ();

  // Get Status
  state = TW_u8GetStatus();

  // Check if it's ACK
  if (state != TW_MR_DATA_ACK)
  {
    return NACK;
  }
  // I2C_ Stop
  TW_vidSTOP();

  // Return Done
  return ACK;
}

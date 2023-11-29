/*
 * EEPROM.h
 *
 *  Created on: Sep 19, 2022
 *      Author: original
 */

#ifndef MCAL_EEPROM_EEPROM_H_
#define MCAL_EEPROM_EEPROM_H_

#include <avr/io.h>
#include "../../STD_Types.h"
#include "../../Bit_Math.h"


void EEPROM_write(uint16 address, uint8 data );
uint8 EEPROM_read(uint16 address );

#endif /* MCAL_EEPROM_EEPROM_H_ */

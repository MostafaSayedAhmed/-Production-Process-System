/*
 * EEPROM.C
 *
 *  Created on: Sep 19, 2022
 *      Author: original
 */
#define F_CPU 8000000UL
#include<util/delay.h>
#include "EEPROM.h"

void EEPROM_write(uint16 address, uint8 data )
{

EEAR=address;

EEDR=data ;

SET_BIT(EECR,EEMWE);
SET_BIT(EECR,EEWE);
while(GET_BIT(EECR,EEWE)==1);


}

uint8 EEPROM_read(uint16 address )
{

EEARL=(sint8)address;
EEARH=(sint8)(address>>8);

SET_BIT(EECR,EERE);

return EEDR ;
}






/*
 * Dio_cfg.h
 *
 *  Created on: ١٢‏/٠٩‏/٢٠٢٢
 *      Author: HP
 */

#ifndef MCAL_DIO_DIO_CFG_H_
#define MCAL_DIO_DIO_CFG_H_

#include "Dio_Types.h"

#define PIN_COUNT	26

typedef struct{
	Dio_Port_type 	PinPort;
	Dio_Pin_type	pin;
	Dio_Dir_type	pinDir;
	Dio_PULLUP_type pullup;
}DIO_PinCfg;


extern DIO_PinCfg Dio_Confg_Pins[PIN_COUNT];


//void Dio_Cfg_init(void);



#endif /* MCAL_DIO_DIO_CFG_H_ */

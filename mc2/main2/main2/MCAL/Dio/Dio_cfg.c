/*
 * Dio_cfg.c
 *
 *  Created on: ١٢‏/٠٩‏/٢٠٢٢
 *      Author: HP
 */

#include "Dio_cfg.h"
#include "Dio.h"

DIO_PinCfg Dio_Confg_Pins[] = {
		{PORT_C, PIN_0, OUTPUT,PULLUP_OFF},
		{PORT_C, PIN_1, OUTPUT,PULLUP_OFF},
		{PORT_C, PIN_2, OUTPUT,PULLUP_OFF},
		{PORT_C, PIN_3, OUTPUT,PULLUP_OFF},
		{PORT_C, PIN_4, OUTPUT,PULLUP_OFF},
		{PORT_C, PIN_5, OUTPUT,PULLUP_OFF},
		{PORT_C, PIN_6, OUTPUT,PULLUP_OFF},
		{PORT_C, PIN_7, OUTPUT,PULLUP_OFF},

		{PORT_B, PIN_0, OUTPUT},
		{PORT_B, PIN_1, OUTPUT},
		{PORT_B, PIN_2, OUTPUT},
		{PORT_B, PIN_3, OUTPUT},
		{PORT_B, PIN_4, OUTPUT},
		{PORT_B, PIN_5, OUTPUT},
		{PORT_B, PIN_6, OUTPUT},
		{PORT_B, PIN_7, OUTPUT},

		{PORT_A, PIN_0, OUTPUT,PULLUP_OFF},
		{PORT_A, PIN_1, OUTPUT,PULLUP_OFF},
		{PORT_A, PIN_2, OUTPUT,PULLUP_OFF},
		{PORT_A, PIN_3, OUTPUT,PULLUP_OFF},
		{PORT_A, PIN_4,INPUT,PULLUP_ON},
		{PORT_A, PIN_5,INPUT,PULLUP_ON},
		{PORT_A, PIN_6,INPUT,PULLUP_ON},
		{PORT_A, PIN_7,INPUT,PULLUP_ON},

		{PORT_D, PIN_2,INPUT,PULLUP_OFF},
		{PORT_D, PIN_3,OUTPUT,PULLUP_OFF},
		{PORT_D, PIN_4,OUTPUT,PULLUP_OFF}

};


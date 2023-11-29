/*
 * Dio.h
 *
 *  Created on: ١١‏/٠٩‏/٢٠٢٢
 *      Author: HP
 */

#ifndef MCAL_DIO_DIO_H_
#define MCAL_DIO_DIO_H_

#include <avr/io.h>
#include "../../STD_Types.h"
#include "../../Bit_Math.h"
#include "Dio_Types.h"
#include "Dio_cfg.h"

void Dio_init(void);
void Dio_write(channel_type chanel, Dio_status_type state);
void Dio_toggle(channel_type chanel);
Dio_status_type Dio_read(channel_type chanel);

#endif /* MCAL_DIO_DIO_H_ */

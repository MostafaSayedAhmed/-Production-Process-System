/*
 * UART.h
 *
 *  Created on: ٢٥‏/٠٩‏/٢٠٢٢
 *      Author: HP
 */

#ifndef MCAL_UART_UART_H_
#define MCAL_UART_UART_H_
#include "../../STD_Types.h"
#include<avr/io.h>

void UART_init(void);

void UART_send_data(uint8 data);

uint8 UART_get_recieved_data();

#endif /* MCAL_UART_UART_H_ */

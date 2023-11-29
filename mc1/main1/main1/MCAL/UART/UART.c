/*
 * UART.c
 *
 *  Created on: ٢٥‏/٠٩‏/٢٠٢٢
 *      Author: HP
 */

#include "../UART/UART.h"

#define F_CPU 				8000000UL		/* Define frequency here its 8MHz */
#define USART_BAUDRATE 		9600
#define BAUD_PRESCALE 		(((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

void UART_init(void)
{
	//int BAUD_PRESCALE = 25;

	//Put the upper part of the baud number here (bits 8 to 11)
	UBRRH = (unsigned char) (BAUD_PRESCALE >> 8);

	//Put the remaining part of the baud number here
	UBRRL = (unsigned char) BAUD_PRESCALE;

	//Enable the receiver and transmitter
	UCSRB = (1 << RXEN) | (1 << TXEN);

	//Set 2 stop bits and data bit length is 8-bit
	UCSRC = (1 << USBS) | (3 << UCSZ0);

}


void UART_send_data(uint8 data)
{
	//Wait until the Transmitter is ready
	while (! (UCSRA & (1 << UDRE)) );

	//put data to transport here!
	UDR = data;
}

uint8 UART_get_recieved_data()
{
	while (! (UCSRA & (1 << RXC)) );

	return UDR;
}

void UART_Flush( void )
{
unsigned char dummy;
	while ( UCSRA & (1<<RXC) )
	{
		dummy = UDR;
	}
}



#include <avr/io.h>
#define F_CPU 8000000UL
#include <util/delay.h>
#include "Bit_Math.h"
//#include "HAL/SEVEN_SEGMENT/SS.h"
#include "STD_Types.h"
#include "MCAL/Dio/Dio.h"
#include"HAL/LCD/Lcd.h"
#include"HAL/keypad/keypad.h"
#include"avr/interrupt.h"
#include "math.h"
#include "MCAL/ADC/ADC.h"
#include<stdio.h>
#include "MCAL/UART/UART.h"

#include <avr/interrupt.h>			//?= 1- include this header to use sei();

#include "MCAL/Ext_Interrupt/EX_interrupts.h"

//FUNCTION TO FLASH LED
//void flash(uint8 times)
//{
	//	for(uint8 i=0; i<times; i++)
	//	{
		//		Dio_write(PORTC_0, HIGH);
		//		_delay_ms(100);
		//		Dio_write(PORTC_0, LOW);
		//		_delay_ms(100);
	//	}
//}

//SEND DATA
//void send_data(void)
//{
	//	UART_send_data(3);				//TX : ask u2 to flash his LED 3 times
//}
//

void send1(void)
{
	UART_send_data(1);					//tO U2
}

void send2(void)
{
	UART_send_data(2);					//tO U2
}

int main(void)
{
	char buffer[16];
	Dio_init();
	UART_init();
	ADC_init();
	sei();
	EXTI_init();


	uint8 recieved_data;


	while (1){
		
		uint16 result = ADC_read();
		//sprintf(buffer,"result =%d",result);

		if(result<3)
		{
			UART_send_data('N');
			
		}else
		{
			UART_send_data('M');

		}
		_delay_ms(500);






	}


}


/*
 * Dio.c
 *
 *  Created on: ١١‏/٠٩‏/٢٠٢٢
 *      Author: HP
 */

#include "Dio.h"


void Dio_init(void)
{
	int i = 0;
	for( i=0; i<PIN_COUNT; i++){
		if(Dio_Confg_Pins[i].PinPort == PORT_A){
			if(Dio_Confg_Pins[i].pinDir == OUTPUT){
				SET_BIT(DDRA, Dio_Confg_Pins[i].pin);
			}
			else{
				CLR_BIT(DDRA, Dio_Confg_Pins[i].pin);
				if(Dio_Confg_Pins[i].pullup == PULLUP_ON )
				{
					SET_BIT(PORTA, Dio_Confg_Pins[i].pin);
				}
			}
		}

		if(Dio_Confg_Pins[i].PinPort == PORT_B){
			if(Dio_Confg_Pins[i].pinDir == OUTPUT){
				SET_BIT(DDRB, Dio_Confg_Pins[i].pin);
			}
			else{
				CLR_BIT(DDRB, Dio_Confg_Pins[i].pin);
				if(Dio_Confg_Pins[i].pullup == PULLUP_ON )
				{
					SET_BIT(PORTB, Dio_Confg_Pins[i].pin);

				}
			}
		}

		if(Dio_Confg_Pins[i].PinPort == PORT_C){
			if(Dio_Confg_Pins[i].pinDir == OUTPUT){
				SET_BIT(DDRC, Dio_Confg_Pins[i].pin);
			}
			else{
				CLR_BIT(DDRC, Dio_Confg_Pins[i].pin);
				if(Dio_Confg_Pins[i].pullup == PULLUP_ON )
				{
					SET_BIT(PORTC, Dio_Confg_Pins[i].pin);

				}
			}
		}

		if(Dio_Confg_Pins[i].PinPort == PORT_D){
			if(Dio_Confg_Pins[i].pinDir == OUTPUT){
				SET_BIT(DDRD, Dio_Confg_Pins[i].pin);
			}
			else{
				CLR_BIT(DDRD, Dio_Confg_Pins[i].pin);
				if(Dio_Confg_Pins[i].pullup == PULLUP_ON )
				{
					SET_BIT(PORTD, Dio_Confg_Pins[i].pin);

				}
			}
		}

	}
}

void Dio_toggle(channel_type chanel)
{
	Dio_Port_type port = chanel / 8;
	Dio_Pin_type pin = chanel % 8;

	if(port == PORT_A){
		TOG_BIT(PORTA, pin);
	}

	else if(port == PORT_B){
		TOG_BIT(PORTB, pin);
	}
	else if(port == PORT_C){
		TOG_BIT(PORTC, pin);
	}
	else if(port == PORT_D){
		TOG_BIT(PORTD, pin);
	}

}

void Dio_write(channel_type chanel, Dio_status_type state)
{
	Dio_Port_type port = chanel / 8;
	Dio_Pin_type pin = chanel % 8;

	if(port == PORT_A){
		if(state == HIGH){
			SET_BIT(PORTA, pin);
		}else{
			CLR_BIT(PORTA, pin);
		}
	}

	else if(port == PORT_B){
			if(state == HIGH){
				SET_BIT(PORTB, pin);
			}else{
				CLR_BIT(PORTB, pin);
			}
		}

	else if(port == PORT_C){
			if(state == HIGH){
				SET_BIT(PORTC, pin);
			}else{
				CLR_BIT(PORTC, pin);
			}
		}

	else if(port == PORT_D){
			if(state == HIGH){
				SET_BIT(PORTD, pin);
			}else{
				CLR_BIT(PORTD, pin);
			}
		}
}

Dio_status_type Dio_read(channel_type chanel)
{
	Dio_Port_type port = chanel / 8;
	Dio_Pin_type pin = chanel % 8;

	Dio_status_type state = 0;

	if(port == PORT_A){
		state = GET_BIT(PINA, pin);
	}
	else if(port == PORT_B){
			state = GET_BIT(PINB, pin);
	}
	else if(port == PORT_C){
				state = GET_BIT(PINC, pin);
	}
	else if(port == PORT_D){
				state = GET_BIT(PIND, pin);
	}
	return state;
}

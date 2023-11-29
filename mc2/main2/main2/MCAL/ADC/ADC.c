/*
 * ADC.c
 *
 *  Created on: Sep 24, 2022
 *      Author: Alryada
 */
#include <avr/io.h>

#include "ADC.h"


void ADC_init(){
SET_BIT(ADMUX,REFS0); //configure VREF
SET_BIT(ADMUX,REFS1);
SET_BIT(ADCSRA,ADEN); // enable ADC
/* adjust ADC clock*/
SET_BIT(ADCSRA,ADPS2);
SET_BIT(ADCSRA,ADPS1);


}
uint16 ADC_read(void){
     unsigned short read_val;
	ADMUX|=(1<<MUX0); //SELECT ADC1 ON PIN A1
	SET_BIT(ADCSRA,ADSC);
	while(GET_BIT(ADCSRA,ADIF));//stay in your position till ADIF become 1
	SET_BIT(ADCSRA,ADIF); // clear ADIF
	read_val=(ADCL);
	read_val|=(ADCH<<8);
	return read_val ;



}

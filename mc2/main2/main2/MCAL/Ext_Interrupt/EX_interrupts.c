/*
 * EX_interrupts.c
 *
 *  Created on: Sep 22, 2022
 *      Author: Alryada
 */

#include"avr/io.h"
#include"EX_interrupts.h"
#include"../../Bit_Math.h"
#include<avr/interrupt.h>

void(*p2f_INT0)(void);
void(*p2f_INT1)(void);
void(*p2f_INT2)(void);



void EXTI_init(){
#if EXT_INT0_MODE == ENABLE
        EXTI_enable(EXTI0);
#if INT0_SENSE_MODE==LOW_LEVEL_TRIG
            CLR_BIT(MCUCR,ISC00);
			CLR_BIT(MCUCR,ISC01);
#elif INT0_SENSE_MODE==ANY_LOGIC_TRIG

			SET_BIT(MCUCR,ISC00);
          	CLR_BIT(MCUCR,ISC01);
#elif INT0_SENSE_MODE==FALLING_EDGGE_TRIG

			CLR_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);

#elif INT0_SENSE_MODE==RASING_EDGGE_TRIG

			SET_BIT(MCUCR,ISC00);
			SET_BIT(MCUCR,ISC01);


#endif
#endif


#if EXT_INT1_MODE == ENABLE

		EXTI_enable(EXTI1);
		if(INT0_SENSE_MODE==LOW_LEVEL_TRIG)
		{
			CLR_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);

		}else if(INT0_SENSE_MODE==ANY_LOGIC_TRIG)
		{
			SET_BIT(MCUCR,ISC10);
			CLR_BIT(MCUCR,ISC11);
		}else if(INT0_SENSE_MODE==FALLING_EDGGE_TRIG)
		{
			CLR_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
		}else if(INT0_SENSE_MODE==RASING_EDGGE_TRIG)
		{
			SET_BIT(MCUCR,ISC10);
			SET_BIT(MCUCR,ISC11);
		}
#endif


}
void EXTI_enable(EXTI_type interrupt){

	switch (interrupt)
	{

	case EXTI0:
		SET_BIT(GICR, INT0);
		break;


	case EXTI1:
		SET_BIT(GICR, INT1);
		break;


	case EXTI2:
		SET_BIT(GICR, INT2);
		break;

	}

}


void EXTI_disable(EXTI_type interrupt){

	switch (interrupt)
	{

	case EXTI0:
		CLR_BIT(GICR, INT0);
		break;


	case EXTI1:
		CLR_BIT(GICR, INT1);
		break;


	case EXTI2:
		CLR_BIT(GICR, INT2);
		break;

	}
}

void set_callback_INT0(void (*p2f)(void))
{

	p2f_INT0=p2f;
}
void set_callback_INT1(void (*p2f)(void)){
	p2f_INT1=p2f;


}
void set_callback_INT2(void (*p2f)(void)){
	p2f_INT2=p2f;


}

ISR(INT0_vect)
{
	if(p2f_INT0!=0){

		p2f_INT0();
	}

}


//ISR(INT1_vect)
//{
//	if(p2f_INT1!=0){
//
//		p2f_INT1();
//	}
//
//}


//ISR(INT2_vect)
//{
//	if(p2f_INT2!=0){
//
//		p2f_INT2();
//	}
//
//}

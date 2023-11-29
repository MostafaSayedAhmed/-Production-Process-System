/*
 * EX_interrupts.h
 *
 *  Created on: Sep 22, 2022
 *      Author: Alryada
 */

#ifndef MCAL_EX_INTERRUPTS_EX_INTERRUPTS_H_
#define MCAL_EX_INTERRUPTS_EX_INTERRUPTS_H_
#include "EX_interrupts_confg.h"

void EXTI_init();
void EXTI_enable(EXTI_type interrupt);
void EXTI_disable(EXTI_type interrupt);

void set_callback_INT0(void (*p2f)(void));
void set_callback_INT1(void (*p2f)(void));
void set_callback_INT2(void (*p2f)(void));

#endif /* MCAL_EX_INTERRUPTS_EX_INTERRUPTS_H_ */

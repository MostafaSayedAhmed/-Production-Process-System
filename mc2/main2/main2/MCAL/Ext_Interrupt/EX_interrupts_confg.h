/*
 * EX_interrupts_confg.h
 *
 *  Created on: Sep 22, 2022
 *      Author: Alryada
 */

#ifndef MCAL_EX_INTERRUPTS_EX_INTERRUPTS_CONFG_H_
#define MCAL_EX_INTERRUPTS_EX_INTERRUPTS_CONFG_H_

typedef enum {
	EXTI0,
	EXTI1,
	EXTI2

}EXTI_type;

#define DISABLE 0
#define ENABLE 1

#define EXT_INT0_MODE  ENABLE
#define EXT_INT1_MODE  DISABLE
#define EXT_INT2_MODE  DISABLE


#define LOW_LEVEL_TRIG       0
#define ANY_LOGIC_TRIG       1
#define FALLING_EDGGE_TRIG   2
#define RASING_EDGGE_TRIG    3

#define INT0_SENSE_MODE  FALLING_EDGGE_TRIG
#define INT1_SENSE_MODE  RASING_EDGGE_TRIG
#define INT2_SENSE_MODE  RASING_EDGGE_TRIG





#endif /* MCAL_EX_INTERRUPTS_EX_INTERRUPTS_CONFG_H_ */

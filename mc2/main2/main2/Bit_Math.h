/*
 * Bit_math.h
 *
 * 	Created on:
 * 		Author:
 */

#ifndef E15_LAB_SRC_UTILS_BIT_MATH_H_
#define E15_LAB_SRC_UTILS_BIT_MATH_H_

#define SET_BIT(REG, PIN)	(REG |= (1<<PIN))
#define CLR_BIT(REG, PIN)	(REG &= ~(1<<PIN))
#define GET_BIT(REG, PIN)	((REG >> PIN) & 0x1)
#define TOG_BIT(REG, PIN)	(REG ^= (1<<PIN))
#endif

/*
 * Lcd.h
 *
 *  Created on: ١٢‏/٠٩‏/٢٠٢٢
 *      Author: HP
 */

#ifndef HAL_LCD_LCD_H_
#define HAL_LCD_LCD_H_

#include "../../MCAL/Dio/Dio.h"
#include "Lcd_Config.h"

void Lcd_Init(void);
void LCD_movecursor(uint8 row,uint8 coloumn);
void LCD_clearscreen();

void Lcd_SendCmd(unsigned char cmd);
void Lcd_SendChar(unsigned char data);

void Lcd_SendString(unsigned char *data);
void Lcd_SendString_xy(unsigned char *data, unsigned char x, unsigned char y);

void Lcd_Send_Number(unsigned char n);
void Lcd_Send_Number_xy(unsigned char n, unsigned char x, unsigned char y);

void Lcd_Send_Long_Number(sint16 n);
void Lcd_Send_Long_Number_xy(uint16 n, unsigned char x, unsigned char y);

#endif /* HAL_LCD_LCD_H_ */

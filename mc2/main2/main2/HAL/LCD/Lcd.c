/*
 * Lcd.c
 *
 *  Created on: ١٢‏/٠٩‏/٢٠٢٢
 *      Author: HP
 */


#define F_CPU 8000000UL
#include<util/delay.h>
#include "Lcd.h"
#include "Lcd_cmd.h"

static void Trigger_Enable();

void Lcd_Init(){
	_delay_ms(20);
	Lcd_SendCmd(0x33);
	Lcd_SendCmd(0x32);
	//Lcd_sendcmd(0x02);
	Lcd_SendCmd(0x28);
	Lcd_SendCmd(0x0E);
	Lcd_SendCmd(0x06);
	_delay_ms(10);
	Lcd_SendCmd(0x80);
	Lcd_SendCmd(0x01);
	_delay_ms(10);
	

}
void Lcd_SendCmd(unsigned char cmd){

	Dio_write(RS, LOW);
	Dio_write(RW, LOW);

	(GET_BIT(cmd, 7)) ? Dio_write(D7, HIGH) : Dio_write(D7, LOW);
	(GET_BIT(cmd, 6)) ? Dio_write(D6, HIGH) : Dio_write(D6, LOW);
	(GET_BIT(cmd, 5)) ? Dio_write(D5, HIGH) : Dio_write(D5, LOW);
	(GET_BIT(cmd, 4)) ? Dio_write(D4, HIGH) : Dio_write(D4, LOW);

	Trigger_Enable();

	(GET_BIT(cmd, 3)) ? Dio_write(D7, HIGH) : Dio_write(D7, LOW);
	(GET_BIT(cmd, 2)) ? Dio_write(D6, HIGH) : Dio_write(D6, LOW);
	(GET_BIT(cmd, 1)) ? Dio_write(D5, HIGH) : Dio_write(D5, LOW);
	(GET_BIT(cmd, 0)) ? Dio_write(D4, HIGH) : Dio_write(D4, LOW);

	Trigger_Enable();

}

void Lcd_SendChar(unsigned char data){

	Dio_write(RS, HIGH);
	Dio_write(RW, LOW);

	(GET_BIT(data, 7)) ? Dio_write(D7, HIGH) : Dio_write(D7, LOW);
	(GET_BIT(data, 6)) ? Dio_write(D6, HIGH) : Dio_write(D6, LOW);
	(GET_BIT(data, 5)) ? Dio_write(D5, HIGH) : Dio_write(D5, LOW);
	(GET_BIT(data, 4)) ? Dio_write(D4, HIGH) : Dio_write(D4, LOW);

	Trigger_Enable();

	(GET_BIT(data, 3)) ? Dio_write(D7, HIGH) : Dio_write(D7, LOW);
	(GET_BIT(data, 2)) ? Dio_write(D6, HIGH) : Dio_write(D6, LOW);
	(GET_BIT(data, 1)) ? Dio_write(D5, HIGH) : Dio_write(D5, LOW);
	(GET_BIT(data, 0)) ? Dio_write(D4, HIGH) : Dio_write(D4, LOW);

	Trigger_Enable();

}

void Lcd_SendString(unsigned char *data){
	unsigned char c = *data;
	unsigned char counter = 0;
	unsigned char flag = 1;

	while(c != '\0'){
		counter++;
		if(counter > 16 && flag)
		{
			//force cursor to 2nd line
			Lcd_SendCmd(LCD_CMD_CURSOR_BEGIN_2ND_LINE);
			flag = 0;
		}
		Lcd_SendChar(c);
		c = *(++data);
	}

}

void Lcd_SendString_xy(unsigned char *data, unsigned char x, unsigned char y){

	if(y==0 && x<16)
	{
		Lcd_SendCmd((x & LCD_CMD_SHIF_CURSOR_POS_RIGHT) | LCD_CMD_CURSOR_BEGIN_1ST_LINE);
	}
	else if (y==1 && x<16)
	{
	   Lcd_SendCmd((x & LCD_CMD_SHIF_CURSOR_POS_RIGHT)| LCD_CMD_CURSOR_BEGIN_2ND_LINE);
	}
	Lcd_SendString(data);
}

void Lcd_Send_Number(unsigned char n){

	unsigned char c = (n / 100) + '0';
	Lcd_SendChar(c);

	c = ((n/10)%10) + '0';
	Lcd_SendChar(c);

	c = (n % 10) + '0' ;
	Lcd_SendChar(c);
}

void Lcd_Send_Number_xy(unsigned char n, unsigned char x, unsigned char y){

	if(y==0 && x<16)
	{
		Lcd_SendCmd((0x80 + x));
	}
	else if (y==1 && x<16)
	{
		Lcd_SendCmd((0x80 + 64 + x));;
	}
	Lcd_Send_Number(n);

}

void Lcd_Send_Long_Number_xy(uint16 n, unsigned char x, unsigned char y){

	if(y==0 && x<16)
	{
		Lcd_SendCmd((0x80 + x));
	}
	else if (y==1 && x<16)
	{
		Lcd_SendCmd((0x80 + 64 + x));
	}
	Lcd_Send_Long_Number(n);

}

void Lcd_Send_Long_Number(sint16 n){
	uint8 c_arr[5];
	uint8 counter = 0;
	uint8 sign = 0;

	if(n<0)
	{
		sign = 1;
		n *= -1;
	}

	while(n)
	{
		c_arr[counter] = n%10;
		counter++;
		n = n / 10;
	}

	if(sign)
		Lcd_SendChar('-');

	for(uint8 i=counter-1; i>=0; i--)
	{
		Lcd_SendChar((c_arr[i]+'0'));
	}

}

static void Trigger_Enable(){

	Dio_write(EN, HIGH);
	_delay_us(1);
	Dio_write(EN, LOW);
	_delay_ms(2);


}
void LCD_movecursor(uint8 row,uint8 coloumn)
{
	char data ;
	if(row>2||row<1||coloumn>16||coloumn<1)
	{
		data=0x80;
	}
	else if(row==1)
	{
		data=0x80+coloumn-1 ;
	}
	else if (row==2)
	{
		data=0xc0+coloumn-1;
	}
	Lcd_SendCmd(data);
	_delay_ms(1);
}
void LCD_clearscreen()
{
	Lcd_SendCmd(0x01);
}
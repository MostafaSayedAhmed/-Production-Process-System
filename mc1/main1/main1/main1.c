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
#include "MCAL/EX_interrupts/EX_interrupts.h"
#include "MCAL/EEPROM/EEPROM.h"


#define MODE_PASS_WORD		0
#define MODE_CALCULATOR		1
#define MODE_TEMP			2
#define MODE_LIGHT			3

//PASS WORD VARIABLES
#define  EEPROM_STATUS_LOCATION 0x20
#define  EEPROM_PASSWORD_LOCATION1 0x21
#define  EEPROM_PASSWORD_LOCATION2 0x22
#define  EEPROM_PASSWORD_LOCATION3 0x23
#define  EEPROM_PASSWORD_LOCATION4 0x24
#define MAX_TRIES 3
#define NOT_PRESSED 255
void change_pass();
uint8 arr[4];
uint8 mode = MODE_PASS_WORD;
uint8 pass_flag = 0;			//must be = 1 to go to other modes

uint8 display_mode_flag = 1; 	//to ensure mode title will not repeated on LCD


//CALC VARIABLES
sint8 key_value_arr[20];
uint8 counter = 0;
uint8 cntr = 0;
uint8 operator = 0;			//mean no operator
uint16 op1;					//operand
uint16 op2;
uint8 op1_flag = 1;			//ready to enter operand1 first digit
uint8 op2_flag = 1;			//ready to enter operand2 first digit

uint8 recieved_data;

//--------------------------------------- FUNCTION USED WITH INTERRUPT --------------------------------------------
void set_mode(void)
{
	if (pass_flag)
	{
		mode++;
		if (mode > 3)
			mode = 1;
		display_mode_flag = 1;
	}
}

//-------------------------------------- save_kp_value -----------------------------------------------------
void save_kp_value(uint8 c) {
	key_value_arr[counter] = c;
	counter++;
}

//-------------------------------------- display_result ---------------------------------------------------
void display_result(void) {
	//Lcd_SendCmd(0xc0); 	//start at 2nd line
	switch (operator) {
	case '+':
		Lcd_Send_Number_xy((op1 + op2), 5, 1);
		operator = 0;
		op1 = 0;
		op2 = 0;

		break;

	case '-':
		Lcd_Send_Number_xy((op1 - op2), 5, 1);
		operator = 0;
		op1 = 0;
		op2 = 0;
		break;

	case '*':
		Lcd_Send_Number_xy((op1 * op2), 5, 1);
		operator = 0;
		op1 = 0;
		op2 = 0;
		break;

	case '/':
		if(op2 == 0)
		{
			Lcd_SendString_xy(("invalid"), 5, 1);
			break;
		}
		Lcd_Send_Number_xy((op1 / op2), 5, 1);
		operator = 0;
		op1 = 0;
		op2 = 0;
		break;
	}
}

//-------------------------------------- dclear_all ---------------------------------------------------
void clear_all(void) {
	counter = 0;
	Lcd_SendCmd(0x1);
}

//-------------------------------------- check_pass_word ---------------------------------------------------
/*uint8 check_pass_word(void) {
	for (uint8 i = 0; i < 4; i++) {
		if (entered_pass_word[i] != correct_pass_word[i])
			return 0;
	}
	return 1;
}*/

//-------------------------------------- display_mode_title ---------------------------------------------------
void display_mode_title(uint8 *titl) {
	if (display_mode_flag) {
		display_mode_flag = 0;
		clear_all();
		Lcd_SendString(titl);

	}
}

//-------------------------------------- set_calc ---------------------------------------------------
void set_calc(void)
{
	if (display_mode_flag)
	{
		display_mode_flag = 0;
		clear_all();
		Lcd_SendString("clc: ");

		if(op1)
		{
			Lcd_Send_Number(op1);
			if(operator)
			{
				Lcd_SendChar(operator);
				if(op2)
				{
					Lcd_Send_Number(op2);
					display_result();
				}
			}
		}
	}
}

///////////////////////////////////////////////////  main()  ///////////////////////////////////////////////

int main(void)
{
	uint8 value = NOT_PRESSED;
	uint8 flag = 0, i;
	uint8 tries = MAX_TRIES;

	EXTI_init();
	SREG|=(1<<7);
	Dio_init();
	Lcd_Init();
	set_callback_INT0(set_mode);
	UART_init();
	ADC_init();



	uint8 key_pad_value;

	Lcd_SendCmd(0x1);
	Lcd_SendString("ENTER PASSWORD");
	Lcd_SendCmd(0xc0);


	while (1) {

		//---------------------------------------------- MODE PASS WORD ---------------------------------------------
		if (mode == MODE_PASS_WORD) {
			LCD_clearscreen();
			set: if (EEPROM_read(EEPROM_STATUS_LOCATION) == 0xff) {
				Lcd_SendString("set pass:");

				for (i = 0; i <= 3; i++) {
					do {
						value = kp_getpressed();
					} while (value == NOT_PRESSED);
					Lcd_SendChar(value);
					_delay_ms(500);
					LCD_movecursor(1, 10 + i);
					Lcd_SendChar('*');
					EEPROM_write(EEPROM_PASSWORD_LOCATION1 + i, value);
				}
				EEPROM_write(EEPROM_STATUS_LOCATION, 0x00);

			}
			
			while (flag == 0) {
				arr[0] = arr[1] = arr[2] = arr[3] = NOT_PRESSED;
				LCD_clearscreen();
				Lcd_SendString("check password :");
				for (i = 0; i <= 3; i++) {
					do {
						if (Dio_read(PORTA_0) == 1) {
							_delay_ms(500);

							change_pass();
							goto set;

						}
						arr[i] = kp_getpressed();
					} while (arr[i] == NOT_PRESSED);

					
					Lcd_SendChar(arr[i]);
					_delay_ms(500);
					LCD_movecursor(2, 8 + i);
					Lcd_SendChar('*');

				}
				if (EEPROM_read(EEPROM_PASSWORD_LOCATION1) == arr[0]
				&& EEPROM_read(EEPROM_PASSWORD_LOCATION2) == arr[1]
				&& EEPROM_read(EEPROM_PASSWORD_LOCATION3) == arr[2]
				&& EEPROM_read(EEPROM_PASSWORD_LOCATION4) == arr[3]) {
					LCD_clearscreen();
					Lcd_SendString("Right Password");
					Lcd_SendString_xy("Calculator Activ", 0,1);
					_delay_ms(2000);
					mode = MODE_CALCULATOR;
					flag=1;
					pass_flag=1;
					clear_all();

				} else {
					tries = tries - 1;
					if (tries > 0) {
						LCD_clearscreen();
						Lcd_SendString("Wrong password");
						LCD_clearscreen();
						Lcd_SendString("tries left:");
						Lcd_SendChar(tries + 48);
						_delay_ms(1000);
					} else {
						LCD_clearscreen();
						Lcd_SendString("Wrong password");
						Lcd_SendString_xy("safe closed", 2, 1);
						flag = 1;
					}

				}

			}
		}		

		//---------------------------------------------- MODE CALCULATOR ---------------------------------------------

		else if (mode == MODE_CALCULATOR)
		{
			Dio_write(PORTD_4,LOW);
			//set up calculator mode title and redisplay operations if any
			set_calc();

			//monitor user input
			key_pad_value = kp_getpressed();
			if (key_pad_value != kp_realesed) 	//if we get key pad value
			{
				// if key ' ON/C '
				if (key_pad_value == 'A') 			// ON/C ? 'A'
				{
					display_mode_flag = 1;			//to enable proceed into next function
					display_mode_title("clc: ");	//clear and set title
				}
				// if key ' = '
				else if (key_pad_value == '=')
				{
					display_result();
				}
				// if key any of +-/*
				else if ((key_pad_value == '+') || (key_pad_value == '-')
						|| (key_pad_value == '*') || (key_pad_value == '/'))
				{
					Lcd_SendChar(key_pad_value);	//display operator
					_delay_ms(500);

					operator = key_pad_value;		//store it
				}
				//------------------- if key 0 ? 9 ----------------
				else
				{
					// display it
					Lcd_SendChar(key_pad_value);
					_delay_ms(500);

					// store it as a number in op1 and op2
					if ((operator == 0) && (op1_flag == 1)) //op1 first digit
					{
						op1 = key_pad_value - '0';
						op1_flag = 0;
					}
					else if ((operator == 0) && (op1_flag == 0)) //op1 other digit
					{
						op1 = op1 * 10 + key_pad_value - '0';
					}
					else if ((operator != 0) && (op2_flag == 1)) //op2 first digit
					{
						op2 = key_pad_value - '0';
						op2_flag = 0;
					}
					else if ((operator != 0) && (op1_flag == 0)) //op2 other digit
							{
						op2 = op2 * 10 + key_pad_value - '0';
					}

				}
			}
		}
		//---------------------------------------------- MODE TEMPRETURE ---------------------------------------------

		else if (mode == MODE_TEMP)
		{
			Dio_write(PORTD_4,LOW);
			display_mode_title("ALARM SYSTEM: ");
			uint16 result =(ADC_read()*0.25);
			Lcd_Send_Number_xy(result, 0, 1);
			Lcd_SendChar('c');

			if(result > 50)
			{
				Dio_toggle(PORTA_2);	//puzzer
				Dio_toggle(PORTA_3);	//LED
				_delay_ms(150);
				Dio_write(PORTB_3, HIGH);	//MOTOR ? NEED ADJUSTMENT ???
				Dio_write(PORTB_1, LOW);	//DIR_1
				Dio_write(PORTB_2, HIGH);	//DIR_2
			}
			if(result <= 50)
			{
				Dio_toggle(PORTA_3);	//LED
				_delay_ms(200);
				Dio_write(PORTB_3, HIGH);	//MOTOR ? NEED ADJUSTMENT ???
				Dio_write(PORTB_1, HIGH);	//DIR_1
				Dio_write(PORTB_2, LOW);	//DIR_2
			}
		}

		//---------------------------------------------- MODE LIGHT ---------------------------------------------

		else if (mode == MODE_LIGHT)
		{
			
			display_mode_title("LIGHT MODE: ");
			Dio_write(PORTB_3, LOW);
			recieved_data = UART_get_recieved_data();

			if (recieved_data == 'N')
			{
				Lcd_SendString_xy("NIGHT", 5, 1);
				Dio_write(PORTD_4,HIGH);
			}
			else if (recieved_data == 'M')
			{
				Lcd_SendString_xy("MORNING",5,1);
				Dio_write(PORTD_4,LOW);
			}

		}
	} //end while

} //end main

	void change_pass() {
		char i = 0;
		LCD_clearscreen();
		Lcd_SendString("old pass:");
		for (i = 0; i <= 3; i++) {
			do {
				arr[i] = kp_getpressed();

			} while (arr[i] == NOT_PRESSED);
			LCD_movecursor(2, 8 + i);
			Lcd_SendChar(arr[i]);
			LCD_movecursor(2, 8 + i);
			_delay_ms(500);
			Lcd_SendChar('*');
		}
		if (EEPROM_read(EEPROM_PASSWORD_LOCATION1) == arr[0]
		&& EEPROM_read(EEPROM_PASSWORD_LOCATION2) == arr[1]
		&& EEPROM_read(EEPROM_PASSWORD_LOCATION3) == arr[2]
		&& EEPROM_read(EEPROM_PASSWORD_LOCATION4) == arr[3]) {
			LCD_clearscreen();
			Lcd_SendString("password cleared");
			_delay_ms(1000);
			LCD_clearscreen();
			EEPROM_write(EEPROM_STATUS_LOCATION, 0xff);
			EEPROM_write(EEPROM_PASSWORD_LOCATION1, 0xff);
			EEPROM_write(EEPROM_PASSWORD_LOCATION2, 0xff);
			EEPROM_write(EEPROM_PASSWORD_LOCATION3, 0xff);
			EEPROM_write(EEPROM_PASSWORD_LOCATION4, 0xff);
		} else {
			LCD_clearscreen();
			Lcd_SendString("wrong pass");
			_delay_ms(1000);
			LCD_clearscreen();

		}
	}

/*
 * keypad.c
 *
 *  Created on: Sep 18, 2022
 *      Author: Alryada
 */


#include "keypad.h"




 static uint8 Kp_MapArr[4][4]={

		{'7','8','9','/'},
		{'4','5','6','*'},
		{'1','2','3','-'},
		{'A','0','=','+'}


};

 uint8 kp_getpressed()
 {
	 uint8 row ,coloumn,x;
	 uint8 return_val = NOT_PRESSED;
	 for(row=0;row<4;row++)
	 {
		 Dio_write(PORTB_4, HIGH);
		 Dio_write(PORTB_5, HIGH);
		 Dio_write(PORTB_6, HIGH);
		 Dio_write(PORTB_7, HIGH);

		 Dio_write(PORTB_4 + row, LOW);
		 for(coloumn=0;coloumn<4;coloumn++)
		 {
			 x= Dio_read(PORTA_0 +coloumn+4);
			 if(x==0)
			 {
				 return_val= Kp_MapArr[row][coloumn];
				 break;
			 }

		 }

		 if(x==0)
		 {
			 break;
		 }


	 }

	 return return_val;

 }

/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */



#include "APP.h"

int main(void)
{
	uint8_t key_pressed = 0;
	uint8_t flag = 0 ;
	uint8_t LED_NO ;
	clock_init();
	HAL_init();
	LCD_clear_screen();
	delay_function_ms(100);
	LCD_send_string("Enter LED No.:");


	while (1)
	{

		key_pressed = KEYPAD_read_button();
		switch (key_pressed)
		{
		case 'A':
			break;
		case 'C':
			LCD_clear_screen();
			LCD_send_string("Enter LED Number:");
			flag = 0 ;
			break;
		case '=' :
			if (flag) {changeStatus(LED_NO);}
			break ;
		default:
		{
			if()
			LED_NO = key_pressed ;

			Pin_call(key_pressed);
			flag = 1 ;
			break;
		}
		}
	}
}










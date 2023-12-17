/*
 * LCD_driver.c
 *
 * Created: 12/12/2023 1:56:35 PM
 * Author : m7med
 */

#include "LCD_driver/lcd.h"

void app_init()
{
	s_LCD_Config_t LCD_config;
	LCD_config.e_DispCtrl	= ON_DISP | ON_BLINK | ON_CURSOR ;
	LCD_config.e_EntryMode	= NOSHIFT_INCREMENT;
	LCD_config.e_FuncSet	= EIGHT_BIT_MODE_2LINE_10DOTS;
	LCD_init(&LCD_config);
	
}




int main(void)
{
	uint8_t key_pressed;
	Keypad_init();
	app_init();
	while (1)
	{
		key_pressed = Keypad_getkey();
		switch(key_pressed){
			case 'A':
			break;
			case '?':
			LCD_clear_screen();
			break;
			default:
			LCD_send_char(key_pressed);
			break;
		}
	}

	return 0;
}


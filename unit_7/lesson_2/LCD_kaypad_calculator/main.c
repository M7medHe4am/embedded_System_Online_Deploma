/*
 * LCD_driver.c
 *
 * Created: 12/12/2023 1:56:35 PM
 * Author : m7med
 */

#include "LCD_driver/lcd.h"
#include "keypad_driver/keypad.h"
#include "calculator/calc.h"
void app_init()
{
	s_LCD_Config_t LCD_config;
	LCD_config.e_DispCtrl	= ON_DISP | ON_BLINK | ON_CURSOR ;
	LCD_config.e_EntryMode	= NOSHIFT_INCREMENT;
	LCD_config.e_FuncSet	= EIGHT_BIT_MODE_2LINE_10DOTS;
	LCD_init(&LCD_config);
	KEYPAD_init();
}



int main(void)
{
	uint8_t key_pressed ;
	app_init();
	s_num_t var;
	s_parameter_t parameter;
	calc_reset_parameters(&parameter);
	while (1)
	{
	key_pressed = KEYPAD_read_button();
	switch(key_pressed)
		{
		case 'A' :
		//DO nothing 
			break;
		case 'C':
			LCD_clear_screen();
			calc_reset_parameters(&parameter);
			break;
		default:
		{
			LCD_send_char(key_pressed);
			if (calc_key_pressed_check(&var , key_pressed ,&parameter))
			{
				LCD_send_string(var.string);
			}
			break;
		}
			
	
		}
	}

	return 0;
}


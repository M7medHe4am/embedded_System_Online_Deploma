/*
 * ATMEGA32_DRIVERS.c
 *
 * Created: 12/22/2023 4:11:41 PM
 * Author : m7med
 */ 

#include "lcd.h"




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
	
	app_init();
	while (1)
	{
		LCD_clear_screen();
		_delay_ms(500);
		LCD_send_string("Learn in depth !");
		
		_delay_ms(5000);
	}
	


	return 0;
}




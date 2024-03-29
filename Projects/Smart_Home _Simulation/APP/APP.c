/*
 * APP.c
 *
 *  Created on: Feb 5, 2024
 *      Author: m7med
 */

#include "APP.h"


LED_t LEDs[]={
		{GPIOA, { LED1 ,GPIO_MODE_OUT_PP,GPIO_SPEED_10M	} , 1  }
		,{GPIOA, { LED2 ,GPIO_MODE_OUT_PP,GPIO_SPEED_10M	} , 1}
		,{GPIOB, { LED3 ,GPIO_MODE_OUT_PP,GPIO_SPEED_10M	} , 1}
		,{GPIOB, { LED4 ,GPIO_MODE_OUT_PP,GPIO_SPEED_10M	} , 1}
		,{GPIOB, { LED5 ,GPIO_MODE_OUT_PP,GPIO_SPEED_10M	} , 1}
		,{GPIOB, { LED6 ,GPIO_MODE_OUT_PP,GPIO_SPEED_10M	} , 1}
		,{GPIOB, { LED7 ,GPIO_MODE_OUT_PP,GPIO_SPEED_10M	} , 1}
		,{GPIOB, { LED8 ,GPIO_MODE_OUT_PP,GPIO_SPEED_10M	} , 1}
};



void clock_init(void)
{
	//GPIOA ,GPIOB ,GPIOC AFIO CLOCK ENABLE
	RCC_GPIOA_CLCK_EN()	;
	RCC_GPIOB_CLCK_EN()	;
	RCC_GPIOC_CLCK_EN()	;
}



void HAL_init(void)
{
	//LCD configurations
	s_LCD_Config_t LCD_CONFIG;
	LCD_CONFIG.e_DispCtrl	= ON_DISP | ON_CURSOR | ON_BLINK ;
	LCD_CONFIG.e_EntryMode	= NOSHIFT_INCREMENT;

	LCD_CONFIG.e_FuncSet	= EIGHT_BIT_MODE_2LINE_10DOTS;
	LCD_init(&LCD_CONFIG);

	//Kaypad configurations


	KEYPAD_init();
	uint8_t ledsNo = sizeof(LEDs)/sizeof(LED_t);
	for (int i = 0; i< ledsNo ; i++ )
	{
		LED_init(&LEDs[i]);
	}

}

//void GPIO_CNFG(void)
//{
//	GPIO_PinConfig_t pinConfig;
//	//LED1 >> PA
//	pinConfig.GPIO_Mode 		= GPIO_MODE_OUT_PP	;
//	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M	;
//	pinConfig.GPIO_PinNumber	= LED1		;
//	MCAL_GPIO_Init(GPIOA,&pinConfig);
//	//LED2 >>PA
//	pinConfig.GPIO_Mode 		= GPIO_MODE_OUT_PP	;
//	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M	;
//	pinConfig.GPIO_PinNumber	= LED2		;
//	MCAL_GPIO_Init(GPIOA,&pinConfig);
//	//>>>>>> PB
//	pinConfig.GPIO_Mode 		= GPIO_MODE_OUT_PP	;
//	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M	;
//	pinConfig.GPIO_PinNumber	= LED3		;
//	MCAL_GPIO_Init(GPIOB,&pinConfig);
//	//PA3
//	pinConfig.GPIO_Mode 		= GPIO_MODE_OUT_PP;
//	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M	;
//	pinConfig.GPIO_PinNumber	= LED4		;
//	MCAL_GPIO_Init(GPIOB,&pinConfig);
//	//PA4
//	pinConfig.GPIO_Mode 		= GPIO_MODE_OUT_PP	;
//	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M	;
//	pinConfig.GPIO_PinNumber	= LED5		;
//	MCAL_GPIO_Init(GPIOB,&pinConfig);
//	//PA5
//	pinConfig.GPIO_Mode 		= GPIO_MODE_OUT_PP	;
//	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M	;
//	pinConfig.GPIO_PinNumber	=LED6		;
//	MCAL_GPIO_Init(GPIOB,&pinConfig);
//	//PA6
//	pinConfig.GPIO_Mode 		= GPIO_MODE_OUT_PP	;
//	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M	;
//	pinConfig.GPIO_PinNumber	= LED7		;
//	MCAL_GPIO_Init(GPIOB,&pinConfig);
//	//PA7
//	pinConfig.GPIO_Mode 		= GPIO_MODE_OUT_PP	;
//	pinConfig.GPIO_Output_Speed = GPIO_SPEED_10M	;
//	pinConfig.GPIO_PinNumber	= LED8		;
//	MCAL_GPIO_Init(GPIOB,&pinConfig);
//
//}


void Pin_call(uint8_t pinRead)
{
	uint8_t pinStatus = 2 ;
//	LCD_clear_screen();
//	LCD_send_string("YOU CHOSE : LED");
//	LCD_send_char(pinRead);
//	delay_function_ms(1000);
	LCD_clear_screen();
	uint8_t ledNo = pinRead - '1' ;
//	uint8_t ledsNo = sizeof(LEDs)/sizeof(LED_t);
//	if (ledNo > ledsNo);
	pinStatus = LED_getStatus(&LEDs[ledNo]);
	LCD_send_string("THE LED");
	LCD_send_char(pinRead);
	if (pinStatus == 1 )
	{
		LCD_send_string(" IS ON");
	}
	else if (pinStatus == 0)
	{
		LCD_send_string(" IS OFF");
	}
	LCD_set_position(1, 0);
	LCD_send_string("Toggle : '='");
}





void changeStatus(uint8_t LED_NO)
{

	uint8_t ledNo = LED_NO - '1' ;

	LED_toggleStatus(&LEDs[ledNo]);
	Pin_call(LED_NO);
}













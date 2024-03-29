/*
 * sevensegment.c
 *
 *  Created on: Dec 19, 2023
 *      Author: m7med
 */

#include "sevensegment.h"
void sevensegment_init()
{

	GPIO_PinConfig_t pinCnfg;


	pinCnfg.GPIO_PinNumber = GPIO_PIN_9;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &pinCnfg);


	pinCnfg.GPIO_PinNumber = GPIO_PIN_10;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &pinCnfg);



	pinCnfg.GPIO_PinNumber = GPIO_PIN_11;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &pinCnfg);



	pinCnfg.GPIO_PinNumber = GPIO_PIN_12;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &pinCnfg);



	pinCnfg.GPIO_PinNumber = GPIO_PIN_13;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &pinCnfg);




	pinCnfg.GPIO_PinNumber = GPIO_PIN_14;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &pinCnfg);




	pinCnfg.GPIO_PinNumber = GPIO_PIN_15;
	pinCnfg.GPIO_Mode = GPIO_MODE_OUT_PP ;
	pinCnfg.GPIO_Output_Speed = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &pinCnfg);


}

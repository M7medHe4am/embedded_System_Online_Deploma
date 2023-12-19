/*
 * util.c
 *
 *  Created on: Dec 19, 2023
 *      Author: m7med
 */

#include "LCD_adaptor.h"
void delay_function_ms(uint32_t time)
{
	uint32_t i , j ;
	for(i=0;i< time ;i++)
		for(j=0;j<255;j++);
}

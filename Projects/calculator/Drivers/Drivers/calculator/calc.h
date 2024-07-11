/*
 * calc.h
 *
 * Created: 12/17/2023 11:08:25 PM
 *  Author: m7med
 */ 


#ifndef CALC_H_
#define CALC_H_
//========================================INCLUDES=========================================
#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "avr/io.h"
#include "string.h"

//=========================================================================================




//===============================TYPEDEFINED STRUCTURES=====================================

typedef struct  
{
	char  firstNumber[10];
	char  secondNumber[10];
	char op;
	long  result;
	char string[50];
}s_num_t;

typedef struct
{
	uint8_t i ;
	uint8_t j ;
	uint8_t counter ;
}s_parameter_t;

//=========================================================================================





//========================================FUNCTIONS========================================
void calc_store_firstnumber(s_num_t* var, uint8_t firstNumber,uint8_t i);
void calc_store_secondnumber(s_num_t* var,uint8_t secondNumber ,uint8_t j);
void calc_store_operator(s_num_t* var , uint8_t operator);
void calc_result(s_num_t *var);
uint8_t calc_key_pressed_check(s_num_t *var , uint8_t key_pressed,s_parameter_t* parameter);
void calc_reset_parameters(s_parameter_t* parameter);

//=========================================================================================





#endif /* CALC_H_ */
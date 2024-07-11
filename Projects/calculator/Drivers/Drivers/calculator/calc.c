/*
 * calc.c
 *
 * Created: 12/17/2023 11:08:12 PM
 *  Author: m7med
 */ 
#include "calc.h"


//========================================FUNCTIONS========================================


void calc_store_firstnumber(s_num_t* var, uint8_t firstNumber,uint8_t i)
{
		
	var->firstNumber[i] = firstNumber;
}

void calc_store_secondnumber(s_num_t* var,uint8_t secondNumber ,uint8_t j)
{
	var->secondNumber[j] = secondNumber;
}





void calc_store_operator(s_num_t* var , uint8_t operator)
{
	
	var->op = operator ;	
}



void calc_result(s_num_t *var)
{
	long  num1 =0  , num2 = 0;
	//const char 
	num1 = atoi(var->firstNumber);
	num2 = atoi(var->secondNumber);
	
	switch(var->op)
	{
		case '*':
			var->result = num1 *  num2;
			break;
		case '/':
			var->result = num1 /  num2;
			break;
		case '+' :
			var->result = num1 +  num2;
			break;
		default: 
			var->result = num1 -  num2;
			break ;
	}
	sprintf(var->string,"%ld",var->result);
	
}




uint8_t calc_key_pressed_check(s_num_t *var , uint8_t key_pressed,s_parameter_t* parameter)
{

	if ((key_pressed == '=') || (parameter->counter == 2))
	{
		calc_result(var);
		calc_reset_parameters(parameter);
		return 1 ;
	}
	else if (  (key_pressed == '*') || (key_pressed == '/')|| (key_pressed == '+')|| (key_pressed == '-'))
	{
		calc_store_operator(var,key_pressed);
		(parameter->counter)++;	
	}
	else
	{
		if(parameter->counter == 0)
		{
			calc_store_firstnumber(var , key_pressed , parameter->i);
			(parameter->i)++;
			calc_store_firstnumber(var , '\0' , parameter->i);
		}
		else
		{
			calc_store_secondnumber(var,key_pressed,parameter->j);
			(parameter->j)++;
			calc_store_secondnumber(var , '\0' , parameter->j);
		}
	}
	return 0 ;
}


void calc_reset_parameters(s_parameter_t* parameter)
{
	parameter->counter = 0;
	parameter->i =0;
	parameter->j =0;
}
//=========================================================================================

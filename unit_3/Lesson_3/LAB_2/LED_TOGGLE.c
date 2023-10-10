#include "stdint.h"
typedef volatile uint32_t vuint32_t ;
#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800
#define APB2ENR (*((vuint32_t*)(RCC_BASE+0x18)))
#define CRH (*((vuint32_t*)(GPIOA_BASE+0x04)))
#define ODR (*((vuint32_t*)(GPIOA_BASE+0x0c)))
uint8_t g_var[3]={1,2,3};
uint8_t const const_var[3]={1,2,3};
uint8_t ug_var;

int main(void)
{
	APB2ENR |=(1<<2);
	CRH&=0xFF0FFFFF;
	CRH|=0x00200000;
	while(1)
	{
		int i;
		ODR &=~(1<<13); //Resetting bit 13
		for(i=0;i<100000;i++);//DELAY
		ODR |=(1<<13);//Setting bit 13
		for(i=0;i<100000;i++);//DELAY

	}

	return 0;
}

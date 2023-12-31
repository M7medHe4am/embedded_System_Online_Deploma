#include "Platform_Types.h"
#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800
#define APB2ENR (*((vuint32_t*)(RCC_BASE+0x18)))
#define CRH (*((vuint32_t*)(GPIOA_BASE+0x04)))
#define ODR (*((vuint32_t*)(GPIOA_BASE+0x0c)))

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

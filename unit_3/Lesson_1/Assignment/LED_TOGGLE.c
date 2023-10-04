#include "Platform_Types.h"
#define RCC_BASE 0x40021000
#define GPIOA_BASE 0x40010800
typedef union {
	vuint32_t ALL_PORTS;
	struct {
		vuint32_t reserved:2;
		vuint32_t bit2:1;
	}APB2ENR_Field;

}APB2ENR_R;
typedef union {
	vuint32_t ALL_PORTS;
	struct {
		vuint32_t reserved:20;
		vuint32_t bits:4;
	}CRH_Field;

}CRH_R;
typedef union {
	vuint32_t ALL_PORTS;
	struct {
		vuint32_t reserved:13;
		vuint32_t bit13:1;
	}ODR_Field;

}ODR_R;
volatile ODR_R*ODR = (volatile ODR_R*)(GPIOA_BASE+0x0c);
volatile CRH_R*CRH = (volatile CRH_R*)(GPIOA_BASE+0x04);
volatile APB2ENR_R *APB2ENR = (volatile APB2ENR_R *)(RCC_BASE+0x18);
int main(void)
{
	APB2ENR->APB2ENR_Field.bit2=1;
	CRH->CRH_Field.bits=2;
	while(1)
	{
		ODR->ODR_Field.bit13=1; //Setting bit 13
		for(int i=0;i<10000;i++);//DELAY
		ODR->ODR_Field.bit13=0; //Resetting bit 13
		for(int i=0;i<10000;i++);//DELAY


	}

	return 0;
}

//Copyrights reserved to : >> EtCh << 

#include <stdint.h>
typedef volatile uint32_t vuint32_t ; 
#define SYSCTL_BASE 0x400FE000
#define GPIOF_BASE  0x40025000
#define RCGC2_R        (*((vuint32_t*)(SYSCTL_BASE+0x108)))
#define GPIOF_DIR_R    (*((vuint32_t*)(GPIOF_BASE +0x400)))
#define GPIOF_DEN_R    (*((vuint32_t*)(GPIOF_BASE +0x51C)))
#define GPIOF_DATA_R   (*((vuint32_t*)(GPIOF_BASE +0x3FC)))
/*
typedef union
{
	vuint32_t ALL_PORTS ;
	struct 
	{
		vuint32_t reserved:3;
		vuint32_t bit3:1;
		vuint32_t reserved_2:28;
	}pin;
}GPIOF_DATA_R;

vuint32_t GPIOF_DATA_R* DATA_R = ((vuint32_t*)(GPIOF_BASE+0x3FC));
*/
int main(void)
{
	//Note That delay count must be volatile so as for loop isn't to be removed if optimization is on 
	vuint32_t delay_count;
	RCGC2_R = 0x20 ;  //GPIOF is enabled 
	//Delay to make sure that GPIOF is up and running
	for (delay_count=0;delay_count<200;delay_count++); //DELAY

	GPIOF_DIR_R |=(1<<3);// DIR_PIN3 is set for output 
	GPIOF_DEN_R |=(1<<3);
	while (1)
	{
		/*
		DATA_R->pin.bit3=1;//setting bit3
		for (delay_count=0;delay_count<200000;delay_count++); //DELAY
		DATA_R->pin.bit3=0;//resetting bit3
		for (delay_count=0;delay_count<200000;delay_count++); //DELAY
		*/
		GPIOF_DATA_R |=(1<<3); //setting bit3 
		for (delay_count=0;delay_count<200000;delay_count++); //DELAY
		GPIOF_DATA_R &=~(1<<3);//resetting bit3 
 		for (delay_count=0;delay_count<200000;delay_count++); //DELAY
	}

	return 0;
}


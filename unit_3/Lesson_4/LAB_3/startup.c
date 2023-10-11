
#include "stdint.h"
extern int main(void);
void _reset_handler(void);
void Default_handler(void)
{
	_reset_handler();
}
void _NMI_handler()__attribute__((weak,alias("Default_handler")));;
void _HARD_FAULT_handler()__attribute__((weak,alias("Default_handler")));;
void _MM_handler()__attribute__((weak,alias("Default_handler")));;
void _BUS_FAULT_handler()__attribute__((weak,alias("Default_handler")));;
void _Usage_fault_handler()__attribute__((weak,alias("Default_handler")));;
//booking 1024 B located by .bss through uninitialized array of int 256 Element(256*4=1024)
//Also global to be saved in .data section and static to be seen only by this file 
static uint32_t Stack_Top[256];
/*
uint32_t vectors[]__attribute__((section(".vectors")))=
{
(uint32_t) (&Stack_Top[0]+sizeof(Stack_Top)),
(uint32_t)  &_reset_handler,
(uint32_t)	&_NMI_handler,  
(uint32_t)	&_HARD_FAULT_handler,
(uint32_t)	&_MM_handler,
(uint32_t)	&_BUS_FAULT_handler,
(uint32_t)	&_Usage_fault_handler
};
*/
void (* const g_p_fn_vectors[])()__attribute__((section(".vectors")))=
{
(void (*)()) ((uint32_t)Stack_Top+sizeof(Stack_Top)),
&_reset_handler,
&_NMI_handler,  
&_MM_handler,
&_BUS_FAULT_handler,
&_Usage_fault_handler
};
extern uint32_t E_Text;
extern uint32_t S_Data;
extern uint32_t E_Data;
extern uint32_t S_Bss;
extern uint32_t E_Bss;

void _reset_handler(void)
{
	//size of .data section
	uint32_t Data_Size =((uint8_t*)&E_Data) - ((uint8_t*)&S_Data);
	//size of .bss section
	uint32_t Bss_Size =((uint8_t*)&E_Bss) - ((uint8_t*)&S_Bss);
	uint8_t*p_src =((uint8_t*)&E_Text) ;
	uint8_t*p_dst =((uint8_t*)&S_Data) ;
	int i;
	//copying .data from flash to sram "AT RUNTIME FOR SURE"
	for(i=0;i<Data_Size;i++)
	{
			*((uint8_t*)p_dst)=*((uint8_t*)p_src);
			p_dst++;
			p_src++;
	}
	//initializing .Bss
	p_dst=((uint8_t*)&S_Bss) ;
	for(i=0 ; i<Bss_Size ;i++)
	{
		*((uint8_t*)p_dst)=(uint8_t)0;
		p_dst++;
	}
	main ();
}








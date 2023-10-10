/*Copyright >>> EtCh <<< 
 Entry point 0x08000000  needs the stack address 
stack_top 
SRAM starts AT 0x20000000*/

MEMORY
{
	flash(rx) : ORIGIN = 0x08000000, LENGTH = 128k
	sram(rwx) : ORIGIN = 0x20000000, LENGTH = 20k

}


SECTIONS
{
	.text :
	{
		*(.vectors*)
		*(.text*)
		E_Text = .;
	}>flash
	.data :
	{
		S_Data = .;
		*(.data)
		E_Data = . ;
	}>sram AT> flash 
	.bss :
	{
		S_Bss = . ;
		*(.bss*)
		E_Bss = . ;
		. = . + 0x1000 ;
		stack_top = . ;
	}>sram

}








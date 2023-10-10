#@CopyRight >> EtCh <<

Project_name=LED_CORTEX_M3
CC=arm-none-eabi-
CFLAGS = -gdwarf-2 -mcpu=cortex-m3 -mthumb
INCS=-I .
LIBS=
SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
As = $(wildcard *.s)
As_OBJ = $(As:.s=.o)
Ld=$(wildcard *.ld)
Ld_OBJ=$(Ld:.ld=.ld)

all : $(Project_name).bin 
	@echo ">>>>>>>>>>>>>>>>>>>> DONE <<<<<<<<<<<<<<<<<<<<"

#%.o : %.s
#	@echo ">>>>>>>>>>>>>>>>>>>> Processing <<<<<<<<<<<<<<<<<<<<"
#	$(CC)as.exe $(CFLAGS)  $< -o $@
%.o : %.c 
	@echo ">>>>>>>>>>>>>>>>>>>> Processing <<<<<<<<<<<<<<<<<<<<"
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(Project_name).elf:$(Ld_OBJ) $(As_OBJ) $(OBJ) 
	$(CC)ld.exe -T $(Ld_OBJ) $(As_OBJ) $(OBJ) $(LIBS) -o $@ -Map=map_file.map
$(Project_name).bin:$(Project_name).elf 
	$(CC)objcopy.exe -O binary $< $@
	
clean_all :
	rm *.elf *.bin *.o *.map 
	@echo "Everything is now clean :)"
clean :
	rm *.elf *.bin	
	@echo "Everything is now clean :)"
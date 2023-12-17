/*
 * lcd.c
 *
 * Created: 12/12/2023 1:57:08 PM
 *  Author: m7med
 */ 

#include "lcd.h"


//=====================STATIC FUNCTION PROTOTYPES===================
static void LCD_send_command(uint8_t command);
static void LCD_kick(void);
static void LCD_update_position(void);


//==================================================================

//=====================GLOBAL VARIABLES===================
uint8_t LCD_address = 0 ;

//==================================================================







void LCD_init(s_LCD_Config_t* LCD_CONFIG)
{
	// writing low on the CTRL PINS 
	LCD_CTRL_PORT &= ~((1<<LCD_RS_PIN) | (1<<LCD_RW_PIN) | (1<<LCD_EN_PIN) );
	
	//SETTING CTRL PINS DIR TO >> OUTPUT
	LCD_CTRL_DIR  |=  ((1<<LCD_RS_PIN) | (1<<LCD_RW_PIN) | (1<<LCD_EN_PIN) );
	
	// writing low on the DATA PINS
	LCD_DATA_PORT = 0x00 ;
	
	//SETTING DATA PINS DIR TO >> OUTPUT
	LCD_DATA_DIR = 0xFF ;
	
	//Waiting for more than 15 ms after VCC rises to 4.5 V
	 _delay_ms(20);
	  LCD_return_home();
	 LCD_function_set(LCD_CONFIG->e_FuncSet);
	 LCD_disp_ctrl(LCD_CONFIG->e_DispCtrl);
	 LCD_entry_mode_set(LCD_CONFIG->e_EntryMode);
	
	 LCD_clear_screen();
	  LCD_return_home(); //?? return home ??? ????? ??? ?? clear 
}

void LCD_clear_screen(void)
{
	LCD_send_command(0x01);
	LCD_address = 0;
}


void LCD_return_home(void)
{
	LCD_send_command(0x02);
	
	//delay to make sure the LCD isn't busy according to data sheet 
	_delay_ms(2);
	LCD_address = 0;
}
void LCD_entry_mode_set(e_EntryMode_t entryMode)
{
	LCD_send_command(entryMode);
	
   //delay to make sure the LCD isn't busy according to data sheet
	_delay_ms(1);
}

void LCD_disp_ctrl(e_DispCtrl_t dispCTRL)
{
	LCD_send_command(dispCTRL);
	
	//delay to make sure the LCD isn't busy according to data sheet
	_delay_ms(1);
}

void LCD_function_set(e_FuncSet_t funcSet)
{
	LCD_send_command(funcSet);
	
	//delay to make sure the LCD isn't busy according to data sheet
	_delay_ms(1);
}


void LCD_cursor_disp_shift(e_ShiftDir_t shiftDir)
{
	LCD_send_command(shiftDir);
	//delay to make sure the LCD isn't busy according to data sheet
	_delay_ms(1);
	
	// >> LCD_address << variable should be manipulated also here  , so as to work properly
}



static void LCD_send_command(uint8_t command)
{
	//setting RS PIN as low 
	LCD_CTRL_PORT &= ~(1<<LCD_RS_PIN);
	// RW IS LOW BY DEFAULT 
	 
	LCD_DATA_PORT = command;   ////////////////////////////////////////////////////////////////////
	
	LCD_kick();
	
}


static void LCD_kick(void)
{	
	//setting EN pin to high 
	LCD_CTRL_PORT |=  (1<<LCD_EN_PIN);
	_delay_ms(1);
	//setting EN pin to low
	LCD_CTRL_PORT &= ~(1<<LCD_EN_PIN);
}

uint8_t LCD_set_position(uint8_t row , uint8_t col)
{
	uint8_t address;
	if(!((row < 2) && (col<16)))
	{
		return 0 ;
	}
	
	address = (row == 0)? (0x00):(0x40) ;
	LCD_send_command((1<<7) | (address+col));    
	LCD_address = address+col;
	return 1;
	
}

static void LCD_update_position(void)
{
	if(LCD_address == 15 )
	{
		LCD_set_position(1,0);
	}
	else 
	{
		LCD_address++;
	}
}


void LCD_send_char(uint8_t c)
{
	//RW is set to low by default 
	//setting RS to high >> data mode 
	LCD_CTRL_PORT |= (1<<LCD_RS_PIN);
	LCD_DATA_PORT = c;
	LCD_kick();
	LCD_update_position();
	 
}


void LCD_send_string(uint8_t *string)
{
	while (*string)
	{
		LCD_send_char(*string++);
	}
}
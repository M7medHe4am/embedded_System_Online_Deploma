/*
 * lcd.h
 *
 * Created: 12/12/2023 1:56:59 PM
 *  Author: m7med
 */


#ifndef LCD_H_
#define LCD_H_


//==========================================NOTES==========================================
//in this code , the busyFlag (BF) isn't used , instead delays is used to do the job
//=========================================================================================

//========================================INCLUDES=========================================
#include "LCD_adaptor.h"

//=========================================================================================

//===================================TYPEDEFINED ENUMS=====================================

typedef enum
{
	NOSHIFT_INCREMENT	= 0x04,
	NOSHIFT_DECREMENT	= 0x06,
	SHIFT_DISP_RIGHT	= 0x05,
	SHIFT_DISP_LEFT		= 0x07
}e_EntryMode_t;


typedef enum
{
	OFF_DISP_OFFCURSOR_OFF_BLINK	= 0x08,
	ON_DISP							= 0x0C,
	ON_CURSOR						= 0x0A,
	ON_BLINK						= 0x09
}e_DispCtrl_t;

typedef enum
{
	CURSOR_RIGHT	= 0x14,
	CURSOR_LEFT		= 0x10,
	DISP_RIGHT		= 0x1C,
	DISP_LEFT		= 0x18
}e_ShiftDir_t;

typedef enum
{
	EIGHT_BIT_MODE_1LINE_10DOTS		= 0x34,
	EIGHT_BIT_MODE_2LINE_10DOTS		= 0x3C,
	EIGHT_BIT_MODE_1LINE_8DOTS		= 0x30,
	EIGHT_BIT_MODE_2LINE_8DOTS		= 0x38,

	FOUR_BIT_MODE_1LINE_10DOTS		= 0x24,
	FOUR_BIT_MODE_2LINE_10DOTS		= 0x2C,
	FOUR_BIT_MODE_1LINE_8DOTS		= 0x20,
	FOUR_BIT_MODE_2LINE_8DOTS		= 0x28

}e_FuncSet_t;

//=========================================================================================

//==================================TYPEDEFINED structures=================================

typedef struct
{
	e_EntryMode_t e_EntryMode;
	e_DispCtrl_t  e_DispCtrl;
	e_FuncSet_t   e_FuncSet;
}s_LCD_Config_t;

//=========================================================================================

//========================================FUNCTIONS========================================
void LCD_init(s_LCD_Config_t* LCD_CONFIG);
void LCD_clear_screen(void);
void LCD_return_home(void);
void LCD_entry_mode_set(e_EntryMode_t entryMode);
void LCD_disp_ctrl(e_DispCtrl_t dispCTRL);
void LCD_cursor_disp_shift(e_ShiftDir_t shiftDir);
void LCD_function_set(e_FuncSet_t funcSet);
void LCD_send_char(uint8_t c);
void LCD_send_string(uint8_t *string);
uint8_t LCD_set_position(uint8_t row , uint8_t col);
//=========================================================================================









#endif /* LCD_H_ */

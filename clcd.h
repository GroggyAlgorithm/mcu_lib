/**
 * \file lcd.h
 * \author Tim Robbins
 * \brief Header file for LCD character displays. \n
 * \version v2.0.0.0
 * REQUIREMENTS: requires a "config.h" file for the macro definitions, "mcuUtils.h", and "mcuDelays.h" in this files folder. \n
 *
 * NOTE: All commands and most macros are checked for prior definitions. Example: If you define LCD_RETURN_HOME_CMD, this header will NOT DEFINE IT, allowing for commands to be customized elsewhere \n
 * 
 * IMPORTANT: IF DEFINED LCD_CUSTOM_SEND_CMD == 1 LcdSendCommand will not exist in the connected source file and MUST be create \n
 * IMPORTANT: IF DEFINED LCD_CUSTOM_SEND_DATA == 1 LcdSendData will not exist in the connected source file and MUST be create \n
 *
 *
 * LCD_ROW_COUNT must be defined for the amount of rows on the lcd, \n
 * LCD_COLUMN_COUNT must be defined for the amount of columns on the LCD, \n
 *
 * Port registers defined as LCD_CONTROL_PORT, LCD_DATA_PORT, LCD_DATA_PORT_READ, LCD_DATA_PORT_DIR. The commands assume the pins are ordered sequentially. \n
 * LCD_RS_PIN, LCD_RW_PIN, and LCD_E_PIN for control pin positions on LCD_CONTROL_PORT. These do not need to be defined in sequential order. \n
 * Alternatively, you may define LCD_WR_PIN instead of LCD_E_PIN. Doing so will undefine and override the definition of LCD_E_PIN \n
 *
 * To include a CS pin, define LCD_CS_PIN on the LCD_CONTROL_PORT \n
 * To include a RESET pin, define LCD_RESET_PIN on the LCD_CONTROL_PORT \n
 *
 * For each control pin, you may also define LCD_X_PIN_ACTIVE_HIGH as 1 to define pin activation and deactivation settings. This will default to active low for each value \n
 * For the RW(aka READ/WRITE) pin, WRITE is set according to LCD_RW_PIN_ACTIVE_HIGH \n
 * For the RS(aka register select) pin, LCD_RS_PIN_ACTIVE_HIGH defined as 1 will set 1 to be == to instruction, 0 == data \n
 *
 * If LCD_WR_PIN is defined, LCD_RW_ACTIVE_HIGH will undefine and override LCD_E_PIN_ACTIVE_HIGH \n
 * if LCD_CS_PIN is defined, the default will be LCD_CS_PIN_ACTIVE_HIGH	1 \n
 * if LCD_RESET_PIN is defined, the default will be LCD_RESET_PIN_ACTIVE_HIGH	1 \n
 *
 * LCD_BUSY_FLAG_POSITION as the pin position of the busy flag pin on LCD_DATA_PORT. \n
 * If LCD_BUSY_FLAG_POSITION is not defined, LCD_BUSY_FLAG_POSITION will default to 7
 *
 * LCD_USE_4_BIT_MODE is used to describe using the LCD in 4 bit mode. This must be defined as 1 to be active. \n
 * If LCD_USE_4_BIT_MODE is selected, pins as LCD_D7, LCD_D6, LCD_D5, LCD_D4 must be defined as their respective pin numbers. \n
 *
 * To see any define ERRORS, define LCD_SHOW_DEFINE_ERRORS as 1 \n
 *
 * Defining LCD_DATA_PORT_AS_PORT_LETTER as 1 will override the need for LCD_DATA_PORT_DIR and LCD_DATA_PORT_READ and will instead require you to define LCD_DATA_PORT as the ports plain text letter (ex. #define LCD_DATA_PORT_AS_PORT_LETTER C for PORTC) \n
 * If LCD_DATA_PORT_AS_PORT_LETTER is defined as 1, this will undefine and override any definitions for LCD_DATA_PORT_DIR and LCD_DATA_PORT_READ
 *
 *
 *
 *
 *
 * Possible major macro summary \n
 *
 * Must define ports: LCD_CONTROL_PORT, LCD_DATA_PORT. If NOT defined "LCD_DATA_PORT_AS_PORT_LETTER", LCD_DATA_PORT_READ, LCD_DATA_PORT_DIR must be defined \n
 *
 * Must define info: LCD_ROW_COUNT, LCD_COLUMN_COUNT \n
 *
 * Must define pins: LCD_RW_PIN, LCD_RS_PIN, LCD_E_PIN (unless LCD_WR_PIN is defined) \n
 * If LCD_USE_4_BIT_MODE is defined, LCD_D7, LCD_D6, LCD_D5, LCD_D4
 *
 * Optional pins: LCD_CS_PIN, LCD_RESET_PIN, LCD_WR_PIN (overrides LCD_E_PIN), LCD_BUSY_FLAG_POSITION \n
 *
 * Optional Pin operation: \n
 * LCD_E_PIN_ACTIVE_HIGH(unless LCD_WR_PIN_ACTIVE_HIGH defined as 1)
 * LCD_RW_PIN_ACTIVE_HIGH, LCD_RS_PIN_ACTIVE_HIGH, LCD_CS_PIN_ACTIVE_HIGH, LCD_RESET_PIN_ACTIVE_HIGH \n
 *
 * Optional info: LCD_USE_4_BIT_MODE, LCD_SHOW_DEFINE_ERRORS, LCD_DATA_PORT_AS_PORT_LETTER \n
 * 
 * 
 * \todo Needs to have 4 bit modes tested.
 */ 
#ifndef CLCD_H_
#define CLCD_H_             1
#define __INCLUDED_CLCD__   1

#ifdef __cplusplus
extern "C" {
#endif


//INCLUDES
    
#include "config.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



#ifdef __AVR

#include <avr/io.h>

#elif defined(__XC)

#include <xc.h>        /* XC8 General Include File */

#elif defined(HI_TECH_C)

#include <htc.h>       /* HiTech General Include File */

#elif defined(__18CXX)

#include <p18cxxx.h>   /* C18 General Include File */

#elif (defined __XC8)

#include <xc.h>            /* XC8 General Include File */

#endif


//ERROR AND MACRO CHECKING


//The amount of columns on the display
#ifndef LCD_COLUMN_COUNT
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//The amount of rows on the display
#ifndef LCD_ROW_COUNT
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif
    
//The output register for the control pins
#ifndef LCD_CONTROL_PORT
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//The output register for the data pins
#ifndef LCD_DATA_PORT
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif


//Selection for only defining data port
#if defined(LCD_DATA_PORT_AS_PORT_LETTER) && LCD_DATA_PORT_AS_PORT_LETTER == 1

	#if defined(LCD_DATA_PORT_READ)
		#undef LCD_DATA_PORT_READ
	#endif

	#if defined(LCD_DATA_PORT_DIR)
		#undef LCD_DATA_PORT_DIR
	#endif


	#define LCD_DATA_PORT_READ	_GET_READ_REG(LCD_DATA_PORT)
	#define LCD_DATA_PORT_DIR	_GET_DIR_REG(LCD_DATA_PORT)

#else

	//The read register for the data pins
	#ifndef LCD_DATA_PORT_READ
	#define CLCD_C_ -1
	#undef __INCLUDED_CLCD__
	#endif

	//The direction register for the data pins
	#ifndef LCD_DATA_PORT_DIR
	#define CLCD_C_ -1
	#undef __INCLUDED_CLCD__
	#endif


#endif


//The bit position of the e control pin
#if !defined(LCD_E_PIN) && !defined(LCD_WR_PIN)
	#define CLCD_C_ -1
	#undef __INCLUDED_CLCD__

#elif defined(LCD_WR_PIN)

	#if defined(LCD_E_PIN)
		#undef LCD_E_PIN
	#endif
	
	#define LCD_E_PIN	LCD_WR_PIN
	
	#if defined(LCD_E_PIN_ACTIVE_HIGH) && defined(LCD_WR_PIN_ACTIVE_HIGH)
		#undef LCD_E_PIN_ACTIVE_HIGH
	#endif
	
	#if defined(LCD_WR_PIN_ACTIVE_HIGH)
		#define LCD_E_PIN_ACTIVE_HIGH	LCD_WR_PIN_ACTIVE_HIGH
	#endif
	
	

#endif







//The bit position of the rs control pin
#ifndef LCD_RS_PIN
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif


//The bit position of the rw control pin
#ifndef LCD_RW_PIN
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif

//Position of the busy flag pin
#ifndef LCD_BUSY_FLAG_POSITION
#define LCD_BUSY_FLAG_POSITION  7
#if defined(__INCLUDED_CLCD__) && __INCLUDED_CLCD__ == 1
	#if defined(__GNUC__)
		#pragma message __FILE__ ": LCD_BUSY_FLAG_POSITION is defaulted to 7, define LCD_BUSY_FLAG_POSITION in config file to change."
	#else
		#warning "clcd.h: LCD_BUSY_FLAG_POSITION is defaulted to 7, define LCD_BUSY_FLAG_POSITION in config file to change."
	#endif
	
#endif
#endif

//If 4 bit mode, the positions of D6, D5, and D4 must be defined
#if defined(LCD_USE_4_BIT_MODE) && LCD_USE_4_BIT_MODE == 1
#if !defined(LCD_D7) || !defined(LCD_D6) || !defined(LCD_D5) || !defined(LCD_D4)
#define CLCD_C_ -1
#undef __INCLUDED_CLCD__
#endif
#endif
    
    
    
    
    
#if defined(__INCLUDED_CLCD__) && __INCLUDED_CLCD__ == 1


///For clearing the RS Pin
#define LCD_CLEAR_RS_PIN()									LCD_CONTROL_PORT &= ~(1 << LCD_RS_PIN)

///For setting the RS Pin
#define LCD_SET_RS_PIN()									LCD_CONTROL_PORT |= (1 << LCD_RS_PIN)

///For clearing the RW Pin
#define LCD_CLEAR_RW_PIN()									LCD_CONTROL_PORT &= ~(1 << LCD_RW_PIN)

///For setting the RW Pin
#define LCD_SET_RW_PIN()									LCD_CONTROL_PORT |= (1 << LCD_RW_PIN)

///For clearing the E Pin
#define LCD_CLEAR_E_PIN()			LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN)

///For setting the E Pin
#define LCD_SET_E_PIN()				LCD_CONTROL_PORT |= (1 << LCD_E_PIN)


#if !defined(LCD_E_PIN_ACTIVE_HIGH)
	#define LCD_E_PIN_ACTIVE_HIGH			0
#endif

#if !defined(LCD_RW_PIN_ACTIVE_HIGH)
	#define LCD_RW_PIN_ACTIVE_HIGH			0
#endif

#if !defined(LCD_RS_PIN_ACTIVE_HIGH)
	#define LCD_RS_PIN_ACTIVE_HIGH			0
#endif


#if LCD_RW_PIN_ACTIVE_HIGH == 1
	#define LCD_RW_SELECT_WRITE()			LCD_SET_RW_PIN()
	#define LCD_RW_SELECT_READ()			LCD_CLEAR_RW_PIN()
#else
	#define LCD_RW_SELECT_WRITE()			LCD_CLEAR_RW_PIN()
	#define LCD_RW_SELECT_READ()			LCD_SET_RW_PIN()
#endif

#if LCD_RS_PIN_ACTIVE_HIGH == 1
	#define LCD_RS_SELECT_DATA()			LCD_CLEAR_RS_PIN()
	#define LCD_RS_SELECT_INSTRUCTION()		LCD_SET_RS_PIN()
#else
	#define LCD_RS_SELECT_DATA()			LCD_SET_RS_PIN()
	#define LCD_RS_SELECT_INSTRUCTION()		LCD_CLEAR_RS_PIN()
#endif

#if LCD_E_PIN_ACTIVE_HIGH == 1
	#define LCD_E_PIN_ENABLE()				LCD_SET_E_PIN()
	#define LCD_E_PIN_DISABLE()				LCD_CLEAR_E_PIN()
#else
	#define LCD_E_PIN_ENABLE()				LCD_CLEAR_E_PIN()
	#define LCD_E_PIN_DISABLE()				LCD_SET_E_PIN()
#endif



///For clearing the E Pin
	#define LCD_CLEAR_E_PIN()			LCD_CONTROL_PORT &= ~(1 << LCD_E_PIN)

	///For setting the E Pin
	#define LCD_SET_E_PIN()				LCD_CONTROL_PORT |= (1 << LCD_E_PIN)


#if defined(LCD_CS_PIN)

	///For clearing the CS Pin
	#define LCD_CLEAR_CS_PIN()			LCD_CONTROL_PORT &= ~(1 << LCD_CS_PIN)

	///For setting the CS Pin
	#define LCD_SET_CS_PIN()			LCD_CONTROL_PORT |= (1 << LCD_CS_PIN)
	
	#if !defined(LCD_CS_PIN_ACTIVE_HIGH)
		#define LCD_CS_PIN_ACTIVE_HIGH			1
	#endif

	
	
	#if LCD_CS_PIN_ACTIVE_HIGH == 1
		#define LCD_CS_SELECT()			LCD_SET_CS_PIN()
		#define LCD_CS_DESELECT()		LCD_CLEAR_CS_PIN()
	#else
		#define LCD_CS_SELECT()			LCD_CLEAR_CS_PIN()
		#define LCD_CS_DESELECT()		LCD_SET_CS_PIN()
	#endif

#endif


#if defined(LCD_RESET_PIN)

	///For clearing the reset Pin
	#define LCD_CLEAR_RESET_PIN()		LCD_CONTROL_PORT &= ~(1 << LCD_RESET_PIN)

	///For setting the reset Pin
	#define LCD_SET_RESET_PIN()			LCD_CONTROL_PORT |= (1 << LCD_RESET_PIN)
	
	#if !defined(LCD_RESET_PIN_ACTIVE_HIGH)
		#define LCD_RESET_PIN_ACTIVE_HIGH		1
	#endif
	
	#if LCD_RESET_PIN_ACTIVE_HIGH == 1
		#define LCD_RESET_SELECT()		LCD_SET_CS_PIN()
		#define LCD_RESET_DESELECT()	LCD_CLEAR_RESET_PIN()
	#else
		#define LCD_RESET_SELECT()		LCD_CLEAR_RESET_PIN()
		#define LCD_RESET_DESELECT()	LCD_SET_CS_PIN()
	#endif

#endif


#if !defined(LCD_OMEGA_SYMBOL)
///Value for LCD omega symbol for cfah2004A family
#define LCD_OMEGA_SYMBOL			0xDE
#endif

#if !defined(LCD_LEFT_ARROW)
///Value for left arrow for cfah2004A family
#define LCD_LEFT_ARROW				0b01111111
#endif

#if !defined(LCD_RIGHT_ARROW)
///Value for right arrow for cfah2004A family
#define LCD_RIGHT_ARROW				0b01111110
#endif

#if !defined(LCD_DEGREES_UPPER_LEFT)
///Value for degrees symbol for cfah2004A family
#define LCD_DEGREES_UPPER_LEFT		223
#endif

#if !defined(LCD_DEGREES_LOWER_LEFT)
///Value for degrees symbol  for cfah2004A family
#define LCD_DEGREES_LOWER_LEFT		0b10100001
#endif



#if !defined(LCD_BS_CMD)
///Backspace
#define LCD_BS_CMD					    0x08
#endif



#if !defined(LCD_TAB_CMD)
///Horizontal Tab
#define LCD_TAB_CMD					    0x09
#endif

#if !defined(LCD_LF_CMD)
///Linefeed
#define LCD_LF_CMD					    0x0A
#endif

#if !defined(LCD_FF_CMD)
///Formfeed
#define LCD_FF_CMD					    0x0C
#endif

#if !defined(LCD_CR_CMD)
///Carriage return
#define LCD_CR_CMD					    0x0D
#endif

#if !defined(LCD_TOP_CMD)
///Top of page
#define LCD_TOP_CMD					    0x0E
#endif


#if !defined(LCD_BOTTOM_CMD)
///Bottom of page
#define LCD_BOTTOM_CMD					0x0F
#endif


#if !defined(LCD_UP_CMD)
///Up 1 line
#define LCD_UP_CMD					    0x1C
#endif


#if !defined(LCD_DN_CMD)
///Down 1 line
#define LCD_DN_CMD					    0x19
#endif


#if !defined(LCD_RT_CMD)
///Right 1 char
#define LCD_RT_CMD					    0x1A
#endif


#if !defined(LCD_LFT_CMD)
///Left 1 char
#define LCD_LFT_CMD					    0x1D
#endif


#if !defined(LCD_EOL_CMD)
///End of Line
#define LCD_EOL_CMD					    0x17
#endif


#if !defined(LCD_CLEAR_SCREEN_CMD)
///Clear screen command
#define LCD_CLEAR_SCREEN_CMD		    0x01
#endif


#if !defined(LCD_RETURN_HOME_CMD)
///Return home command
#define LCD_RETURN_HOME_CMD			    0x02
#endif


#if !defined(LCD_DISPLAY_OFF_CMD)
///Display off command
#define LCD_DISPLAY_OFF_CMD			    0x08
#endif


///Display on command, also is cursor off
#if !defined(LCD_DISPLAY_ON_CMD)
#define LCD_DISPLAY_ON_CMD			    0x0C
#endif

#if !defined(LCD_CURSOR_OFF_CMD)
#define LCD_CURSOR_OFF_CMD			    0x0C
#endif


///Cursor on command, also is blink off
#if !defined(LCD_CURSOR_ON_CMD)
#define LCD_CURSOR_ON_CMD			    0x0E
#endif

#if !defined(LCD_CUSOR_NO_BLINK_CMD)
#define LCD_CUSOR_NO_BLINK_CMD		    0x0E
#endif


#if !defined(LCD_CURSOR_BLINK_CMD)
///Cursor blink command
#define LCD_CURSOR_BLINK_CMD		    0x0F
#endif


#if !defined(LCD_DISPLAY_SHIFT_R_CMD)
///Entire Display shift Right
#define LCD_DISPLAY_SHIFT_R_CMD			0x1C
#endif


#if !defined(LCD_DISPLAY_SHIFT_L_CMD)
///Entire Display shift left
#define LCD_DISPLAY_SHIFT_L_CMD			0x18
#endif


#if !defined(LCD_CURSOR_SHIFT_R_CMD)
///Cursor shift Right
#define LCD_CURSOR_SHIFT_R_CMD			0x14
#endif


#if !defined(LCD_CURSOR_SHIFT_L_CMD)
///Cursor shift left
#define LCD_CURSOR_SHIFT_L_CMD			0x10
#endif


#if !defined(LCD_DD_RAM_CMD)
///Command for LCD DD Ram
#define LCD_DD_RAM_CMD					0x80
#endif


#if !defined(LCD_CG_RAM_CMD) 
///Command for LCD CG Ram
#define LCD_CG_RAM_CMD					0x40
#endif


#if !defined(LCD_INITIALIZATION_CMD)
///The value to send for resetting/initialization of the LCD.
#define LCD_INITIALIZATION_CMD			0x30
#endif

    
#if !defined(LCD_MODE_8BIT_CMD)
///LCD 8 bit mode setting cmd
#define LCD_MODE_8BIT_CMD				0x30
#endif


#if !defined(LCD_MODE_4BIT_CMD)
///LCD 4 bit mode setting cmd
#define LCD_MODE_4BIT_CMD				0x03
#endif



///INITIALIZATION RELATED COMMANDS
#if !defined(LCD_Entry_Mode)
#define LCD_Entry_Mode(x,y)				(0x04 | ((x & 0x01) << 1) | (y & 0x01))
#endif

#if !defined(LCD_Display_Mode)
#define LCD_Display_Mode(dp,c,b)		(0x08 | ((dp & 0x01) << 2) | ((c & 0x01) << 1) | (b & 0x01))
#endif

#if !defined(LCD_Shift_Mode)
#define LCD_Shift_Mode(sc,rl)			(0x10 | ((sc & 0x01) << 3) | ((rc & 0x01) << 2))
#endif

#if !defined(LCD_Function_Set)
#define LCD_Function_Set(dl,nV,fV,x,y)	(0x20 | ((dl & 0x01) << 4) | ((nV & 0x01) << 3) | ((fV & 0x01)<< 2) | ((x & 0x01)<<1) | (y & 0x01))
#endif




/*
    Function line, mode, font commands
    RS R/W      DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
    0   0        0   0   1   1   N   F   X   X

*/


#if !defined(LCD_MODE_LINE_1_FONT_5x8_8BIT)
///LCD 5x8 font, 8 bit mode, single line command
#define LCD_MODE_LINE_1_FONT_5x8_8BIT       LCD_Function_Set(1, 1, 1, 0, 0)
#endif

#if !defined(LCD_MODE_LINE_1_FONT_5x11_8BIT)
///LCD 5x11 font, 8 bit mode, single line command
#define LCD_MODE_LINE_1_FONT_5x11_8BIT      LCD_Function_Set(1, 0, 0, 0, 0)
#endif

#if !defined(LCD_MODE_LINE_2_FONT_5x8_8BIT)
///LCD 5x8 font, 8 bit mode, double line command
#define LCD_MODE_LINE_2_FONT_5x8_8BIT       0b00111000
#endif

#if !defined(LCD_MODE_LINE_2_FONT_5x11_8BIT)
///LCD 5x11 font, 8 bit mode, double line command
#define LCD_MODE_LINE_2_FONT_5x11_8BIT      0b00111100
#endif


#if !defined(LCD_MODE_LINE_1_FONT_5x8_4BIT)
///LCD 5x8 font, 4 bit mode, single line command
#define LCD_MODE_LINE_1_FONT_5x8_4BIT       0b00100000
#endif

#if !defined(LCD_MODE_LINE_1_FONT_5x11_4BIT)
///LCD 5x11 font, 4 bit mode, single line command
#define LCD_MODE_LINE_1_FONT_5x11_4BIT      0b00100100
#endif

#if !defined(LCD_MODE_LINE_2_FONT_5x8_4BIT)
///LCD 5x8 font, 4 bit mode, double line command
#define LCD_MODE_LINE_2_FONT_5x8_4BIT       0b00101000
#endif

#if !defined(LCD_MODE_LINE_2_FONT_5x11_4BIT)
///LCD 5x11 font, 4 bit mode, double line command
#define LCD_MODE_LINE_2_FONT_5x11_4BIT      0b00101100
#endif

    



#if !defined(LCD_MOVE_R_NO_SHIFT_CMD)
#define LCD_MOVE_R_NO_SHIFT_CMD				LCD_Entry_Mode(1, 0)
#endif

#if !defined(LCD_MOVE_R_SHIFT_CMD)
#define LCD_MOVE_R_SHIFT_CMD				LCD_Entry_Mode(1, 1)
#endif

#if !defined(LCD_MOVE_L_NO_SHIFT_CMD)
#define LCD_MOVE_L_NO_SHIFT_CMD				LCD_Entry_Mode(0, 0)
#endif

#if !defined(LCD_MOVE_L_SHIFT_CMD)
#define LCD_MOVE_L_SHIFT_CMD				LCD_Entry_Mode(0, 1)
#endif


#if !defined(LCD_DISPLAY_OFF_CURSOR_OFF_CMD)
#define LCD_DISPLAY_OFF_CURSOR_OFF_CMD		LCD_Display_Mode(0,0,0)
#endif

#if !defined(LCD_DISPLAY_ON_NO_CURSOR_CMD)
#define LCD_DISPLAY_ON_NO_CURSOR_CMD  		LCD_Display_Mode(1,0,0)
#endif

#if !defined(LCD_DISPLAY_ON_NO_BLINK_CMD)
#define LCD_DISPLAY_ON_NO_BLINK_CMD			LCD_Display_Mode(1,1,0)
#endif

#if !defined(LCD_DISPLAY_ON_CURSOR_BLINK_CMD)
#define LCD_DISPLAY_ON_CURSOR_BLINK_CMD		LCD_Display_Mode(1,1,1)
#endif


#if defined(LCD_USE_4_BIT_MODE) && LCD_USE_4_BIT_MODE == 1

#define LCD_4_BIT_DATA_PIN_MASK     ((1 << LCD_D7) | (1 << LCD_D6) | (1 << LCD_D5) | (1 << LCD_D4))
#define __LCD_4_BIT_WRITER_HELPER(d7, d6, d5, d4) ((d7 << LCD_D7) | (d6 << LCD_D6) | (d5 << LCD_D5) | (d4 << LCD_D4))
#define __LCD_4_BIT_VAL_WRITER_HELPER_HIGH(val) ((((val & 0x80) >> 7) << LCD_D7) | (((val & 0x40) >> 6) << LCD_D6) | (((val & 0x20) >> 5) << LCD_D5) | (((val & 0x10) >> 4) << LCD_D4))
#define __LCD_4_BIT_VAL_WRITER_HELPER_LOW(val) ((((val & 0x08) >> 3) << LCD_D7) | (((val & 0x04) >> 2) << LCD_D6) | (((val & 0x02) >> 1) << LCD_D5) | (((val & 0x01)) << LCD_D4))

#endif






extern void LcdConstInit(const unsigned char startupSequence[], const unsigned char lineStartPositions[]);
extern void LcdStoreCustomConstCharacter(unsigned char uchrAddress, const unsigned char auchrCharacter[8]);


extern void LcdInit(unsigned char startupSequence[], unsigned char lineStartPositions[]);
extern unsigned char LcdGetCurrentLine();
extern unsigned char LcdGetCurrentColumn();
extern void LcdBusyFlagWait();
extern void LcdPerformCommand(unsigned char cmd);


#if !defined(LCD_CUSTOM_SEND_CMD) || LCD_CUSTOM_SEND_CMD != 1

extern void LcdSendCommand(unsigned char cmd);

#endif


#if !defined(LCD_CUSTOM_SEND_DATA) || LCD_CUSTOM_SEND_DATA != 1

extern void LcdSendData(unsigned char data);

#endif

///Helper for sending the command for clearing the screen
#define LcdClearScreen()		        LcdPerformCommand(LCD_CLEAR_SCREEN_CMD)

///Helper for sending the command for returning to the home position
#define LcdReturnHome()			        LcdPerformCommand(LCD_RETURN_HOME_CMD)

///Helper for sending the command for moving the cursor left
#define LcdCursorLeft()			        LcdPerformCommand(LCD_LFT_CMD)

///Helper for sending the command for moving the cursor right
#define LcdCursorRight()		        LcdPerformCommand(LCD_RT_CMD)	

///Helper for sending the command for moving the cursor up
#define LcdCursorUp()			        LcdPerformCommand(LCD_UP_CMD)

///Helper for sending the command for moving the cursor down
#define LcdCursorDown()			        LcdPerformCommand(LCD_DN_CMD)	

///Helper for sending the command for running the back space command
#define LcdBackspace()			        LcdPerformCommand(LCD_BS_CMD)	

///Helper for sending the command for moving to the top line at the current column
#define LcdToTop()				        LcdPerformCommand(LCD_TOP_CMD)

///Helper for sending the command for turning the display off
#define LcdDisplayOff()			        LcdPerformCommand(LCD_DISPLAY_OFF_CMD)

///Helper for setting if the Lcd is turned on or turned off
#define LcdSetOnOff(state)				LcdPerformCommand(((state == 0) ? LCD_DISPLAY_OFF_CMD : LCD_DISPLAY_ON_CMD))

///Helper for sending commands for the character generator ram
#define LCD_set_cg_ram(val)				LcdSendCommand(LCD_CG_RAM_CMD | (val & 0x3F))

///Helper for sending commands for the DD ram
#define LCD_set_dd_ram(val)				LcdSendCommand(LCD_DD_RAM_CMD | (val))

///Helper for turning the cursor OFF
#define LcdCursorOff()					LcdSendCommand(LCD_DISPLAY_ON_NO_CURSOR_CMD)

///Helper for turning the cursor On without a blink
#define LcdCursorOn()					LcdSendCommand(LCD_DISPLAY_ON_NO_BLINK_CMD)

///Helper for turning the cursor On with a blink
#define LcdBlinkingCursorOn()			LcdSendCommand(LCD_DISPLAY_ON_CURSOR_BLINK_CMD)


extern void LcdStoreCGData(unsigned char cgAddress, unsigned char data[], uint8_t dataLength);
extern void LcdDisplayOn(bool cursorOn, bool cursorBlink);
extern void LcdClearLine(unsigned char uchrLine);
extern void LcdClearLineFromColumn(unsigned char uchrLine, unsigned char uchrColumn);
extern void LcdClearLineAtColumns(unsigned char uchrLine, unsigned char uchrStartColumn, unsigned char uchrEndColumn);
extern void LcdClearPosition(unsigned char uchrLine, unsigned char uchrColumn);
extern void LcdStoreDotRow(unsigned char uchrAddress, unsigned char uchrNewDot);
extern void LcdStoreCustomCharacter(unsigned char uchrAddress, unsigned char auchrCharacter[8]);
extern unsigned char LcdGetAddressCounter();
extern void LcdGoToPosition(unsigned char uchrLine, unsigned char uchrColumn);

extern void LcdSendByte(unsigned char uchrByte);
extern void LcdSendByteDelay(unsigned char uchrByte, unsigned short ushtDelayTime);
extern void LcdSendByteAtPosition(unsigned char uchrByte, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdSendByteDelayAtPosition(unsigned char uchrByte, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);

extern void LcdPrintChar(char uchrChar);
extern void LcdPrintCharDelay(char uchrChar, unsigned short ushtDelayTime);
extern void LcdPrintCharAtPosition(char uchrChar, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdPrintCharDelayAtPosition(char uchrChar, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);
extern void LcdPrintString(char* strToSend);
extern void LcdPrintStringDelay(char* strToSend, unsigned short ushtDelayTime);
extern void LcdPrintStringAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdPrintStringDelayAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);

extern void LcdPrint(char* strToSend);
extern void LcdPrintDelay(char* strToSend, unsigned short ushtDelayTime);
extern void LcdPrintAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdPrintDelayAtPosition(char* strToSend, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);

extern void LcdPrintNumericalByte(uint8_t numVal);
extern void LcdPrintNumericalByteDelay(uint8_t numVal, unsigned short ushtDelayTime);
extern void LcdPrintNumericalByteAtPosition(uint8_t numVal, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdPrintNumericalByteDelayAtPosition(uint8_t numVal, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);

extern void LcdPrintNumericalShort(uint16_t numVal);
extern void LcdPrintNumericalShortDelay(uint16_t numVal, unsigned short ushtDelayTime);
extern void LcdPrintNumericalShortAtPosition(uint16_t numVal, unsigned char uchrRow, unsigned char uchrColumn);
extern void LcdPrintNumericalShortDelayAtPosition(uint16_t numVal, unsigned char uchrRow, unsigned char uchrColumn, unsigned short ushtDelayTime);

extern void LcdDisplayByteHex(uint8_t byteValue);
extern void LcdDisplayByteBinary(uint8_t byteValue);





#elif defined(LCD_SHOW_DEFINE_ERRORS) && LCD_SHOW_DEFINE_ERRORS == 1

//ERROR CHECKING

//The amount of columns on the display
#ifndef LCD_COLUMN_COUNT
#error clcd.h: LCD_COLUMN_COUNT must be defined to use file.
#endif

//The amount of rows on the display
#ifndef LCD_ROW_COUNT
#error clcd.h: LCD_ROW_COUNT must be defined to use file.
#endif
    
//The output register for the control pins
#ifndef LCD_CONTROL_PORT
#error clcd.h: LCD_CONTROL_PORT must be defined to use file.
#endif

//The output register for the data pins
#ifndef LCD_DATA_PORT
#error clcd.h: LCD_DATA_PORT must be defined to use file.
#endif

//The read register for the data pins
#ifndef LCD_DATA_PORT_READ
#error clcd.h: LCD_DATA_PORT_READ must be defined to use file.
#endif

//The direction register for the data pins
#ifndef LCD_DATA_PORT_DIR
#error clcd.h: LCD_DATA_PORT_DIR must be defined to use file.
#endif

//The bit position of the e control pin
#if !defined(LCD_E_PIN) && !defined(LCD_WR_PIN)
#error clcd.h: LCD_E_PIN or LCD_WR_PIN must be defined to use file.
#endif

//The bit position of the rs control pin
#ifndef LCD_RS_PIN
#error clcd.h: LCD_RS_PIN must be defined to use file.
#endif

//The bit position of the rw control pin
#ifndef LCD_RW_PIN
#error clcd.h: LCD_RW_PIN must be defined to use file.
#endif

//If 4 bit mode, the positions of D6, D5, and D4 must be defined
#if defined(LCD_USE_4_BIT_MODE) && LCD_USE_4_BIT_MODE == 1

#if !defined(LCD_D6)
#error clcd.h: LCD_D6 must be defined to use file.
#endif

#if !defined(LCD_D5)
#error clcd.h: LCD_D5 must be defined to use file.
#endif

#if !defined(LCD_D4)
#error clcd.h: LCD_D4 must be defined to use file.
#endif

#endif


#else


#if defined(__GNUC__)
#pragma message __FILE__ ": Definitions missing. View required definitions to include."
#else
#warning "clcd.h: Check required definitions to include file of define LCD_SHOW_DEFINE_ERRORS as 1 in config file."
#endif


#endif



#ifdef __cplusplus
}
#endif





#endif
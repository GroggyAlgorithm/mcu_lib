# mcu_lib
My personal (growing) library files for microcontrollers


View documentation or source/header files for any requirements. 



Basic requirement is for a "config.h" file to be included in this directory. This is where any important macros
and such should be defined (such as BAUD, F_CPU/XTAL, Decleration macros, etc...).




Most of these could be classes or have pointers for registers. Those files are elsewhere so I wouldn't have to deal with angry compilers during transitions between archetectures (chip shortage).



Example for including:


```

#include "mcu_lib/config.h"
#include "mcu_lib/mcuUtils.h"
#include "mcu_lib/mcuPinUtils.h"
#include "mcu_lib/mcuDelays.h"
#include "mcu_lib/avrTimers.h"
#include "mcu_lib/avrSerial.h"
#include "mcu_lib/mcuAdc.h"
#include "mcu_lib/ckeypadMatrix.h"
#include "mcu_lib/clcd.h"
#include "mcu_lib/font.h"
#include "mcu_lib/ssd1306.h"
#include "mcu_lib/steppers.h"
#include "mcu_lib/spi.h"

```



Example for "config.h" with example macros for LCD, SSD1306, and Keypad Matrix files:

```

/**
 * \file config.h
 * \author Tim Robbins
 * \brief The mcu_utils configuration file for mcu_lib and system definitions.
 */
#ifndef CONFIG_H_
#define CONFIG_H_   1



#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(__XC)


///The frequency being used for the controller
#define _XTAL_FREQ                                  64000000

#else

///The frequency being used for the controller
#define F_CPU                                       12000000UL

#endif


///The baud rate for serial communications
#define BAUD										1200



// Definitions keypad matrix
#define KP_COLUMN_PORT	              PORTA
#define KP_COLUMN_READ	              PINA
#define KP_COLUMN_DIR	                DDRA
#define KP_ROW_PORT		                PORTD
#define KP_ROW_READ		                PIND
#define KP_ROW_DIR		                DDRD
#define KP_COLUMNS		                3
#define KP_ROWS		                    4


//Definitions for LCD
#define LCD_COLUMN_COUNT				      20
#define LCD_ROW_COUNT					        4
#define LCD_CONTROL_PORT				      _GET_OUTPUT_REG(D)
#define LCD_RS_PIN						        2
#define LCD_RW_PIN						        3
#define LCD_E_PIN						          6
#define LCD_DATA_PORT					        _GET_OUTPUT_REG(B)
#define LCD_DATA_PORT_READ				    _GET_READ_REG(B)
#define LCD_DATA_PORT_DIR				      _GET_DIR_REG(B)
#define LCD_BUSY_FLAG_POSITION			  7


//For ssd1306 oled
#define SSD1306_SHOW_ERRORS				    1
#define SSD1306_DRAW_IMMEDIATE			  0
#define SSD1306_CON_PIN_PORT			    PORTB
#define SSD1306_DC_PIN_POSITION			  0
#define SSD1306_RES_PIN_POSITION		  1
#define SSD1306_CS_PORT					      PORTB
#define SSD1306_CS_PIN_POSITIONS		  2, 3



#ifdef	__cplusplus
}
#endif /* __cplusplus */




#endif

```




Example for Keypad Matrix and LCD variables, initialization, and use:


```

///The pin positions for the columns on the matrix
const unsigned char m_uchrKeypdMatrixColumnPins[KP_COLUMNS] = 
{ 
    0,
    1,
    2 
}; 


///The pin positions for the rows on the matrix
const unsigned char m_uchrKeypdMatrixRowPins[KP_ROWS] = 
{ 
    0,
    1,
    6,
    7 
}; 


///The values for the input matrix, when pressed. Adjust for any schematic and button position changes
const unsigned char m_uchrKeypadMatrixValues[KP_ROWS][KP_COLUMNS] =
 { 
    { 
        '1', '2', '3' 
    }, 
    { 
        '4', '5', '6' 
    }, 
    { 
        '7', '8', '9' 
    }, 
    { 
    '*', '0', '#' 
    } 
 };
 
 
 
 ///Startup values for the LCDs startup initialization
const unsigned char m_uchrCFAH2004LcdStartupValues[9] =
{

	#if !defined(LCD_USE_4_BIT_MODE) || LCD_USE_4_BIT_MODE != 1
	LCD_MODE_8BIT_CMD,
	LCD_MODE_8BIT_CMD,
	LCD_MODE_8BIT_CMD,
	LCD_MODE_LINE_1_FONT_5x8_8BIT,
	#else
	LCD_MODE_4BIT_CMD,
	LCD_MODE_4BIT_CMD,
	LCD_MODE_4BIT_CMD,
	LCD_MODE_LINE_1_FONT_5x8_4BIT,
	#endif
	LCD_DISPLAY_OFF_CMD,
	LCD_CLEAR_SCREEN_CMD,
	LCD_MOVE_R_NO_SHIFT_CMD,
	LCD_DISPLAY_ON_NO_CURSOR_CMD, /*To blink or not to blink? To be even on at all?*/
	//LCD_DISPLAY_ON_CURSOR_BLINK, /*To blink or not to blink? To be even on at all?*/
	0x00
};

///Values for CFAH2004A 4-Line LCD's line start addresses
const unsigned char m_uchrCFAH2004LineStartAddresses[] =
{
	0x00, 0x40, 0x14, 0x54
};


void ScanKeypadExample()
{
    //Read any key presses
    unsigned char currentKeypress = kp_Scan_const(m_uchrKeypdMatrixColumnPins, m_uchrKeypdMatrixRowPins,m_uchrKeypadMatrixValues);
}

void LcdInitAndSplashDisplayExample()
{
    //Initialize the display
	LcdConstInit(m_uchrCFAH2004LcdStartupValues, m_uchrCFAH2004LineStartAddresses);


    //Clear the screen
	LcdClearScreen();
	
    //Turn off cursor
	LcdCursorOff();

    //Print design
	for(uint8_t i = 0; i < (LCD_ROW_COUNT * LCD_COLUMN_COUNT); i++)
	{
		LcdPrintCharDelay('-',10000);
	}


    //Print at the appropriate location
	LcdGoToPosition(0,2);
	LcdPrintDelay("This is a,",10000);
	LcdGoToPosition(1,4);
	LcdPrintDelay("Big Test",10000);
	LcdGoToPosition(2,8);
	LcdPrintDelay("Example",10000);
	
	//Clear design in cool way
	LcdPrintDelayAtPosition("                    ",0,0,10000);
	LcdPrintDelayAtPosition("                    ",3,0,10000);
	LcdPrintDelayAtPosition("                    ",1,0,10000);
	LcdPrintDelayAtPosition("                    ",2,0,10000);
}

```







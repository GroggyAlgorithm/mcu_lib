/**
 * \file ExampleMain.cpp
 * 
 * 
 * \author Tim Robbins
 * 
 * 
 * 
 * \brief Example file for library files
 * 
 */


// Definitions keypad matrix
#define KP_COLUMN_PORT	                PORTA
#define KP_COLUMN_READ	                PINA
#define KP_COLUMN_DIR	                DDRA
#define KP_ROW_PORT		                PORTD
#define KP_ROW_READ		                PIND
#define KP_ROW_DIR		                DDRD
#define KP_COLUMNS		                3
#define KP_ROWS		                    4


//Definitions for LCD
#define LCD_COLUMN_COUNT				20
#define LCD_ROW_COUNT					4
#define LCD_CONTROL_PORT				_GET_OUTPUT_REG(D)
#define LCD_RS_PIN						2
#define LCD_RW_PIN						3
#define LCD_E_PIN						6
#define LCD_DATA_PORT					_GET_OUTPUT_REG(B)
#define LCD_DATA_PORT_READ				_GET_READ_REG(B)
#define LCD_DATA_PORT_DIR				_GET_DIR_REG(B)
#define LCD_BUSY_FLAG_POSITION			7


//For ssd1306 oled
#define SSD1306_SHOW_ERRORS				1
#define SSD1306_DRAW_IMMEDIATE			0
#define SSD1306_CON_PIN_PORT			PORTB
#define SSD1306_DC_PIN_POSITION			0
#define SSD1306_RES_PIN_POSITION		1
#define SSD1306_CS_PORT					PORTB
#define SSD1306_CS_PIN_POSITIONS		2, 3

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/atomic.h>

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


/// @brief Example rx value for spi RX interrupt
volatile unsigned char m_uchrSpiRx = 0;

/// @brief Example rx value for USART0 RX interrupt
volatile unsigned char m_uchrUsart0Rx = 0;


///Variable for Timer 1
volatile Timer_t m_udtTimer1;


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



void SSD1306InitializationAndSpiSetupExample()
{
    //Initialize SPI as parent and open spi connection
	SpiInitParent(1,false,false);
	SpiOpen();

    //Initialize oled displays 0 and 1
	SSD1306Initialize(true,0);
	delayForMilliseconds(50);
	
    //Make sure display buffer is cleared
	SSD1306ClearBuffer();
	delayForMilliseconds(50);

    //Make sure displays are awake and their screens are cleared
	SSD1306SelectDisplay(0);
	SSD1306ClearScreen();
	SSD1306SetSleep(true);
	
	SSD1306SelectDisplay(1);
	SSD1306ClearScreen();
	SSD1306SetSleep(true);

    //Draw a full screen outline
	SSD1306DrawRect(0,0,127,63,SSD1306_WHITE);


    //Fancy area left
	SSD1306DrawLine(0,23,11,23,SSD1306_WHITE);
	SSD1306DrawLineUnchecked(11,23,21,63,SSD1306_WHITE);
	SSD1306DrawLine(11,10,21,0,SSD1306_WHITE);
	SSD1306DrawLineUnchecked(0,0,11,23,SSD1306_WHITE);
	
	//Fancy area right
	SSD1306DrawLine(116,23,127,23,SSD1306_WHITE);
	SSD1306DrawLineUnchecked(116,23,106,63,SSD1306_WHITE);
	SSD1306DrawLine(116,10,106,0,SSD1306_WHITE);
	SSD1306DrawLineUnchecked(127,0,116,23,SSD1306_WHITE);
	
	//Bar outline at the bottom
	SSD1306DrawLine(22,51,105,51,SSD1306_WHITE);

    //Draw lowest possible bar fill for initialization
	uint8_t barChunkSizePerStep = (2*5);
	uint8_t minXPos = 63-barChunkSizePerStep;
	uint8_t maxXPos = 63+barChunkSizePerStep;
	SSD1306FillRect(minXPos-1,52,maxXPos+2,62,SSD1306_WHITE);

    //Short delay
    delayForMilliseconds(50);

    //Update all displays
    SSD1306UpdateAll();
}



void ExampleTimer1PwmSetup()
{
    //Setting to 0 in case timer 1 is already running
	TCCR1B = 0;

	//Make sure timer enabled in power register
	#if defined(PRR)
		PRR &= ~(1 << PRTIM1);
	#elif defined(PRR0)
		PRR0 &= ~(1 << PRTIM1);
	#endif

    //Write the PWM output pins to low. Using OCR1 for PWM generation
	PIN_WRITE(OC1B_PIN,LOW,OUTPUT);
	PIN_WRITE(OC1A_PIN,LOW,OUTPUT);

    //Set prescaler 256
	m_udtTimer1.prescaler.cs0 = 0;
	m_udtTimer1.prescaler.cs1 = 0;
	m_udtTimer1.prescaler.cs2 = 1;
	
	//Set for pwm mode, FAST pwm with ICR1 as TOP
	m_udtTimer1.waveform.WGM0 = 0;
	m_udtTimer1.waveform.WGM1 = 1;
	m_udtTimer1.waveform.WGM2 = 1;
	m_udtTimer1.waveform.WGM3 = 1;
	
	//Set output modes
	m_udtTimer1.output_mode.comA			= 2;
	m_udtTimer1.output_mode.comB			= 2;
	m_udtTimer1.output_mode.forceOutA	= 0;
	m_udtTimer1.output_mode.forceOutB	= 0;
	
	//Set interrupts to none
	m_udtTimer1.interrupts.outputCompareMatchA	= 0;
	m_udtTimer1.interrupts.outputCompareMatchB	= 0;
	m_udtTimer1.interrupts.overflow				= 0;
	
	//Set frequency value
	ICR1 = 0x1D0;
	
	//Set interrupts
	TIMSK1 = (m_udtTimer1.interrupts.outputCompareMatchA << OCIE1A | m_udtTimer1.interrupts.outputCompareMatchB << OCIE1B | m_udtTimer1.interrupts.overflow << TOIE1);

	//Setting force out bits
	TCCR1C = (m_udtTimer1.output_mode.forceOutA << FOC1A | m_udtTimer1.output_mode.forceOutB << FOC1B);
	
	//Setting output mode
	TCCR1A = (m_udtTimer1.output_mode.comA << COM1A0 | m_udtTimer1.output_mode.comB << COM1B0);
	
	//Setting waveform bits
	TCCR1A |= (m_udtTimer1.waveform.WGM0 << WGM10 | m_udtTimer1.waveform.WGM1 << WGM11);
	TCCR1B = (m_udtTimer1.waveform.WGM2 << WGM12 | m_udtTimer1.waveform.WGM3 << WGM13);
	
	//Setting m_uchrPrescaler to start timer. We will keep it running and control PWM output through duty cycle settings alone
	TCCR1B |= (m_udtTimer1.prescaler.cs0 << CS10 | m_udtTimer1.prescaler.cs1 << CS11 | m_udtTimer1.prescaler.cs2 << CS12);
	
}



void ExampleUsart0TxWithRxInterruptSetup()
{
    //Serial out pin, output
    PIN_OUTPUT(TX0_PIN);

    //Serial in pin, input 
	PIN_INPUT(RX0_PIN); 

    //Set the register to enable tx, rx, and rx interrupt
	UCSR0B = (1 << RXEN0 | 1 << RXCIE0 | 1 << TXEN0);

    //Clear status register A, not being used
    UCSR0A = 0; 
	
	//Setup mode for, asynchronous, no parity, 1 stop bit, 8 bit size (1000 0110)
	UCSR0C = ((0 << UMSEL00) | (1 << UCSZ01) | (1 << UCSZ00));

	//Enable global interrupts
	interruptsOn();

    /*	
		IMPORTANT: The Baud Rate must be set after the
		transmitter is enabled 
	*/

    //If you're using custom baud...
    //UBRR0 = ((F_CPU / (16 * BAUD))-1);

    //else if you're using the macro library builtin values...
    //Set the baud rate for our serial connection
    USART0SetBaud();
}


void ExampleSpiChildWithInterruptsSetup()
{
    //Initialize pins
    _GET_OUTPUT_REG(A) = 0;
    _GET_OUTPUT_REG(B) = 0;
    _GET_OUTPUT_REG(C) = 0;
    _GET_OUTPUT_REG(D) = 0;
    
    _GET_DIR_REG(A) = FULL_OUTPUT;
    _GET_DIR_REG(B) = FULL_OUTPUT;
    _GET_DIR_REG(C) = FULL_OUTPUT;
    _GET_DIR_REG(D) = FULL_OUTPUT;

    //Configure SPI as a child
    SpiInitChild();
    
	//Enable SPI interrupts
	SPCR |= (1 << SPIE);
	
    //Open spi channel
	SpiOpen();
}

void ExampleStepperMotor(volatile uint8_t* stepperOutputRegister,volatile uint8_t* stepperReadRegister, uint8_t stepperPinPositions[4], uint8_t* currentStepIndex, bool stepCounterClockwise)
{
    
    //Copy the current step index
    uint8_t newStepIndex = *currentStepIndex;

    //Read the current values on the stepper motor read register so we can easily set them without editing other pins
    uint8_t stepperCurrentStepValue = *stepperReadRegister;

    //Take a full step
    StepperFullStep(&stepperCurrentStepValue, stepperPinPositions, &newStepIndex, stepCounterClockwise);

    //Save the step index
    *currentStepIndex = newStepIndex;

    //Ouput the new step pattern
    *stepperOutputRegister = stepperCurrentStepValue;	
    
    
}

void ExampleSpiWriteChild(uint8_t valueToWrite)
{
    //If the chip select pin is low...
    if(PIN_READ(SS_PIN) == 0)
    {
        //Write to the SPI
        SpiWrite(valueToWrite);
    }
}
void ExampleSpiTransmitParent(uint8_t valueToWrite, uint8_t pinOnPortDConnectedToSpiChild)
{
    //Clear the child select pin to select
    PORTD &= ~(1 << pinOnPortDConnectedToSpiChild);

    //Flush
	SpiTransmit(0);
	delayForMicroseconds(10);

    //Send the appropriate value
    SpiTransmit(valueToWrite);
    
    //Deselect the controllers channel
	 PORTD |= (1 << pinOnPortDConnectedToSpiChild);
	
	//Slight delay
	delayForMicroseconds(10);
}


void ExampleAdcInit()
{

    //Set all adc pins to input
    PORT_INPUT_MODE(A);

    //Deselect digital input for all adc pins
    DIDR0 |= 0xFF;

    //Right justify results
    ADC_adjust_right(); 

    //Free running mode
	ADCSRB = (0x00 << ADTS0); 
    
    //Set admux mode
	ADMUX = ADC_REF_MODE_1;

#if defined(ADC_AREF_ENABLE)

    ADC_AREF_ENABLE();
	
#endif

    //Turn on ADC
    ADC_enable(); 
    
}




/**
* \brief Example USART0 RX interrupt
*
*/
ISR(USART0_RX_vect)
{
	
	//Get the received value
	m_uchrUsart0Rx = UDR0;

    if(m_uchrUsart0Rx != 0)
    {
        //Do things...
    }


	
}

/**
 * \brief Example SPI interrupt and receive
 * 
 * 
 */
ISR(SPI_STC_vect)
{
    //Read the rx value
	m_uchrSpiRx = SpiRead();
	
	
		
	//If the spi RX is not 0...
	if(m_uchrSpiRx != 0)
	{

        // Do thing...

    }
}



 
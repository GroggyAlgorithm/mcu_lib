/**
 * \file L297.c
 * \author Tim Robbins
 * \brief Source file for L297 stepper motor controllers
 */

#include "L297.h"
#if !defined(__L297_C__) && __L297_C__ != -1 && defined(__L297_H__) && __L297_H__ == 1
#define __L297_C__	1

#include <avr/io.h>
#include "config.h"
#include "mcuUtils.h"
#include "mcuPinUtils.h"
#include "mcuAdc.h"
#include "mcuDelays.h"




/**
* \brief Reads the L297 HOME pin
* \return True if the L297 Pin is at the home position, False if it is not
*/
void L297InitHomeRead(volatile uint8_t* homeDirectionRegister, volatile uint8_t* homeOutputRegister, uint8_t pinPosition)
{
	*homeOutputRegister |= (1 << pinPosition);
	setBitInput(*homeDirectionRegister, pinPosition);
}



/**
* \brief Reads the L297 HOME pin
* \return True if the L297 Pin is at the home position, False if it is not
*/
uint8_t L297IsHome(volatile uint8_t* homeReadRegister, uint8_t pinPosition)
{
	return (bitIsClear(*homeReadRegister,pinPosition));
}



/**
* \brief Toggles the l297 reset pin and enable pin
*
*/
void L297Reset(volatile uint8_t* resetRegister, uint8_t resetPinPosition, volatile uint8_t* enableRegister, uint8_t enablePinPosition)
{
	*resetRegister &= ~(1 << resetPinPosition);
	*enableRegister |= (1 << enablePinPosition);
	delayForMicroseconds(10);
	*resetRegister |= (1 << resetPinPosition);
	*enableRegister &= ~(1 << enablePinPosition);
}



/**
* \brief Has the L297 take a step, ACTIVE LOW PULSE
* \param micro second wait time for pin toggle
*/
void L297TakeStep(volatile uint8_t* clockRegister, uint8_t clockPinPosition, unsigned short waitTime_Micro)
{
	*clockRegister |= (1 << clockPinPosition);
	delayForMicroseconds(waitTime_Micro);
	*clockRegister &= ~(1 << clockPinPosition);
	delayForMicroseconds(waitTime_Micro);
	*clockRegister |= (1 << clockPinPosition);
}





/**
* \brief Selects the step pattern for the L297
*
*/
void L297SetStepPattern(volatile uint8_t* stepSelectRegister, uint8_t stepSelectPinPosition, uint8_t useHalfStep)
{
	writeBit(*stepSelectRegister,stepSelectPinPosition,(useHalfStep));
}



/**
* \brief Selects the direction for the L297
*
*/
void L297SetDirection(volatile uint8_t* stepDirectionRegister, uint8_t stepDirectionPinPosition, uint8_t direction)
{
	writeBit(*stepDirectionRegister,stepDirectionPinPosition,(direction));
}


//
///**
//* \brief Checks for a stall from the L297
//*
//*/
//uint8_t L297CheckForStall(adc_channel_t sense_1_channel, adc_channel_t sense_2_channel, unsigned short cutout_range_low, unsigned short cutout_range_high)
//{
	//
	//uint8_t hasStalled = 0; //If a stall is detected
	//volatile unsigned short senseAdc_1 = 0; //Adc value from sense 1
	//volatile unsigned short senseAdc_2 = 0; //Adc value from sense 2
	//
	//
	//senseAdc_1 = AdcGet(sense_1_channel);
	//
	//if(senseAdc_1 > cutout_range_high || senseAdc_1 < cutout_range_low)
	//{
		//hasStalled = 1;
	//}
	//else
	//{
		//senseAdc_2 = AdcGet(sense_2_channel);
		//if(senseAdc_2 > cutout_range_high || senseAdc_2 < cutout_range_low)
		//{
			//hasStalled = 1;
		//}
		//
	//}
	//
	//
	//return hasStalled;
//}
//
//
//
/////**
////* \brief Toggles the l297 reset pin and enable pin
////*
////*/
////void L297Reset()
////{
	////PIN_LOW(L297_RESET);
	////PIN_HIGH(L297_ENABLE);
	////delayForMicroseconds(10);
	////PIN_HIGH(L297_RESET);
	////PIN_LOW(L297_ENABLE);
////}
//
//
//
/////**
////* \brief Toggles the l297 reset pin and enable pin
////*
////*/
////void L297Reset() 
////{
	////PIN_LOW(L297_RESET);
	////PIN_HIGH(L297_ENABLE);
	////delayForMicroseconds(10);
	////PIN_HIGH(L297_RESET);
	////PIN_LOW(L297_ENABLE);
////}
//
//
//
/////**
////* \brief Has the L297 take a step
////* \param micro second wait time for pin toggle
////*/
////void L297Step(unsigned short waitTime_Micro) 
////{
	////PIN_TOGGLE(L297_CLOCK);
	////delayForMicroseconds(waitTime_Micro);
	////PIN_TOGGLE(L297_CLOCK);
////}
//
//
//#if L297_STEP_SELECT != -1
//
/////**
////* \brief Selects the step pattern for the L297
////*
////*/
////void L297SetStepPattern(uint8_t useHalfStep) 
////{
	////PIN_WRITE(L297_STEP_SELECT,useHalfStep);
////}
////
////#endif
////
////
/////**
////* \brief Selects the direction for the L297
////*
////*/
////void L297SetDirection(uint8_t direction) 
////{
	////PIN_WRITE(L297_DIR_SELECT,direction);
	////L297_Reset();
////}
//
//
//
//
//
//
//
#endif

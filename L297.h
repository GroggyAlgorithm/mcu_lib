/**
 * \file L297.h
 * \author Tim Robbins
 * \brief Header file for L297 stepper motor controllers
 */


#ifndef __L297_H__
#define __L297_H__	1

#ifdef __cplusplus
extern "C" {
#endif
	
#include <avr/io.h>
#include <stdbool.h>



#define L297_FULL_STEP				0
#define L297_1_PHASE_ON_FULL_STEP	0
#define L297_2_PHASE_ON_FULL_STEP	0
#define L297_HALF_STEP				1






extern void L297InitHomeRead(volatile uint8_t* homeDirectionRegister, volatile uint8_t* homeOutputRegister, uint8_t pinPosition);
extern uint8_t L297IsHome(volatile uint8_t* homeReadRegister, uint8_t pinPosition);
extern void L297Reset(volatile uint8_t* resetRegister, uint8_t resetPinPosition, volatile uint8_t* enableRegister, uint8_t enablePinPosition);
extern void L297TakeStep(volatile uint8_t* clockRegister, uint8_t clockPinPosition, unsigned short waitTime_Micro);
extern void L297SetStepPattern(volatile uint8_t* stepSelectRegister, uint8_t stepSelectPinPosition, uint8_t useHalfStep);
extern void L297SetDirection(volatile uint8_t* stepDirectionRegister, uint8_t stepDirectionPinPosition, uint8_t direction);



inline void L297Enable(volatile uint8_t* enableOutputRegister, uint8_t pinPosition)
{
	*enableOutputRegister |= (1 << pinPosition);
}



inline void L297Disable(volatile uint8_t* enableOutputRegister, uint8_t pinPosition)
{
	*enableOutputRegister &= ~(1 << pinPosition);
}



inline void L297SetToHalfStep(volatile uint8_t* stepSelectRegister, uint8_t stepSelectPinPosition)
{
	*stepSelectRegister |= (1 << stepSelectPinPosition);
}



inline void L297SetToFullStep(volatile uint8_t* stepSelectRegister, uint8_t stepSelectPinPosition)
{
	*stepSelectRegister &= ~(1 << stepSelectPinPosition);
}









#ifdef __cplusplus
}
#endif



#endif /* L297_H_ */
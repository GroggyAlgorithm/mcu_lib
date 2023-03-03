/**
 * \file avrTimers.h
 * \author Tim Robbins
 * \version v2.0.0
 * \brief header file for avr timers functions and utilities
 *
 * \todo Finish remaking functions for timer 2 and timer 3.
 */
#ifndef __AVR_TIMERS_H__
#define __AVR_TIMERS_H__

#if defined(__AVR)

#ifdef __cplusplus
extern "C" {
#endif

 #include <avr/io.h>
 #include <stdlib.h>
 #include <stdbool.h>


typedef struct _OUTPUT_COMPARE_MODE_SELECT_BITS {

    uint8_t comA:2;
    uint8_t comB:2;
    uint8_t forceOutA:1;
    uint8_t forceOutB:1;
    uint8_t __RESERVED:2;


} 

/**
* \brief Struct for output compare settings
*/
Output_compare_bits;


typedef struct _WAVEFORM_BIT_SELECTS {

    uint8_t WGM0:1;
    uint8_t WGM1:1;
    uint8_t WGM2:1;
    uint8_t WGM3:1;
    uint8_t __RESERVED:4;

} 
/**
* \brief Struct for waveform select settings
*
*/
Waveform_select_bits;



typedef struct _PRESCALE_BIT_SELECTS
{
    uint8_t cs0:1;
    uint8_t cs1:1;
    uint8_t cs2:1;

    uint8_t __RESERVED:5;

}
/**
* \brief Struct for prescaler bit settings
*
*/
 Prescaler_select_bits;



typedef struct _INT_MASK_BIT_SELECTS
{
    uint8_t outputCompareMatchA : 1;
    uint8_t outputCompareMatchB : 1;
    uint8_t overflow : 1;

    uint8_t __RESERVED:5;

} 
/**
* \brief Struct for timer interrupt masks
*
*/
Interrupt_mask_bits;



typedef struct _TIMERS_ {
    Output_compare_bits output_mode;
    Waveform_select_bits waveform;
    Prescaler_select_bits prescaler;
    Interrupt_mask_bits interrupts;
} 

/**
* \brief Struct for timers including the select structs
*/
Timer_t;


#ifdef TCNT0
    #define T0Load(v)                           TCNT0 = v;
    #define T0ClearPrescaler()					TCCR0B &= ~(1 << CS00 | 1 << CS01 | 1 << CS02)
    
	/**
	* \brief Sets the prescaler bits for Timer 0
	* \param prescaler Prescaler struct variable to set the timer from
	*/
	static inline void T0SetPrescaler(Prescaler_select_bits prescaler)
	{
		TCCR0B |= ((prescaler.cs0 << CS00) | (prescaler.cs1 << CS01) | (prescaler.cs2 << CS02));
	}

	extern int8_t Timer0Init(Timer_t timer_settings);
	extern void Timer0Enable();
	extern void Timer0Disable();
	
	#if defined(OCR0A)
	#define Pwm0LoadDutyCycleA(dc)				OCR0A = dc
    extern void Pwm0ASetDutyCycle(uint8_t dutyCycle);
	#endif
	
	#if defined(OCR0B)
	#define Pwm0LoadDutyCycleB(dc)				OCR0B = dc
    extern void Pwm0BSetDutyCycle(uint8_t dutyCycle);
	#endif
	
	
#endif


#ifdef TCNT1
    #define T1Load(v)											TCNT1 = v;
    #define T1Load_HL(vL, vH)									TCNT1H = (vH & 0xFF); TCNT1L = (vL & 0xFF)

    
	
	#define T1ClearPrescaler()									TCCR1B &= ~(1 << CS10 | 1 << CS11 | 1 << CS12)
    
	/**
	* \brief Sets the prescaler bits for Timer 1
	* \param prescaler Prescaler struct variable to set the timer from
	*/
	static inline void T1SetPrescaler(Prescaler_select_bits prescaler)
	{
		TCCR1B |= ((prescaler.cs0 << CS10) | (prescaler.cs1 << CS11) | (prescaler.cs2 << CS12));
	}
	
	
	
	

	
	

	extern int8_t Timer1Init(Timer_t timer_settings);
	extern void Timer1Enable();
	extern void Timer1Disable();
	
	#if defined(OCR1A)
	#define Pwm1A_load_reg(dc)									OCR1A = dc
	#define Pwm1A_load_reg_HL(dcL, dcH)							OCR1AH = dcH; OCR1AL = dcL
	
	static inline void Pwm1ADisable()
	{
		TCCR1A &= ~(1 << COM1A0 | 1 << COM1A1);
	}
	extern void Pwm1ASetDutyCycle(uint16_t dutyCycle);
	#endif
	
	#if defined(OCR1B)
	#define Pwm1B_load_reg(dc)									OCR1B = dc
	#define Pwm1B_load_reg_HL(dcL, dcH)							OCR1BH = dcH; OCR1BL = dcL
	static inline void Pwm1BDisable()
	{
		TCCR1A &= ~(1 << COM1B0 | 1 << COM1B1);
	}
	extern void Pwm1BSetDutyCycle(uint16_t dutyCycle);
	#endif

#endif

#ifdef TCNT2


	
	
	

    extern int8_t Timer2Init(Output_compare_bits outputCompBits, Waveform_select_bits waveFormBits, Interrupt_mask_bits interrupts);
    extern void Timer2Enable();
    extern void Timer2Disable();
	
	#if defined(OCR2A)
	#define Pwm2A_load_reg(dc)					OCR2A = dc
    extern void Pwm2ASetDutyCycle(uint16_t dutyCycle);
	#endif
	
	#if defined(OCR2B)
	#define Pwm2B_load_reg(dc)					OCR2B = dc
	extern void Pwm2BSetDutyCycle(uint16_t dutyCycle);
	#endif
	
#endif

#ifdef TCNT3
    extern int8_t Timer3Init(Output_compare_bits outputCompBits, Waveform_select_bits waveFormBits, Interrupt_mask_bits interrupts);
    extern void Timer3Enable();
    extern void Timer3Disable();
#endif


#ifdef ICR0
    #define ICR0_INPUT_CAPTURE_load_reg_HL(vL, vH)       ICR0H = vH; ICR0L = vL;
    #define ICR0_INPUT_CAPTURE_load_reg(v)               ICR0 = v
#endif

#ifdef ICR1
    #define ICR1_INPUT_CAPTURE_load_reg_HL(vL, vH)       ICR1H = vH; ICR1L = vL
    #define ICR1_INPUT_CAPTURE_load_reg(v)               ICR1 = v
#endif





#ifdef __cplusplus
}
#endif

#endif




#endif
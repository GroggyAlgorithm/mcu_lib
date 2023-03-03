/**
 * \file avrTimers.c
 * \author Tim Robbins
 * \version v2.0.0
 * \brief source file for avr timers functions
 * \todo Finish remaking functions for timer 2 and timer 3.
 */
#ifndef __AVR_TIMERS_C__
#define __AVR_TIMERS_C__

#include "avrTimers.h"

#ifdef TCNT0


/**
 * \brief Initializes Timer/Counter 0 without the prescaler
 * 
 * \param timer_settings - UDT timer struct with the settings structs
 *
 * \return Initialization status.  
 */
int8_t Timer0Init(Timer_t timer_settings)
{

    
	/* Enable TC0 From Power Reduction Register */
	#ifdef PRR0
	    PRR0 &= ~(1 << PRTIM0);
    #else
        #ifdef PRR
	        PRR &= ~(1 << PRTIM0);
        #endif
    #endif

    //Make sure timer 0, stopped
    TCCR0B = 0;

    TCNT0 = 0;
    OCR0A = 0;
    OCR0B = 0;



	TCCR0A = (timer_settings.output_mode.comA << COM0A0) | (timer_settings.output_mode.comB << COM0B0) | 
        (timer_settings.waveform.WGM1 << WGM01) | (timer_settings.waveform.WGM0 << WGM00);


    TIMSK0 = (timer_settings.interrupts.outputCompareMatchA << OCIE0A | timer_settings.interrupts.outputCompareMatchB << OCIE0B | 
        timer_settings.interrupts.overflow << TOIE0);

    TCCR0B = (timer_settings.output_mode.forceOutA << FOC0A | timer_settings.output_mode.forceOutB << FOC0B | 
        timer_settings.waveform.WGM2 << WGM02);


	return 0;
}



/**
 * \brief Enables Timer/Counter 0 on the power reduction register 
 */
void Timer0Enable() {

    /* Enable TC0 From Power Reduction Register */

    #ifdef PRR0
	    PRR0 &= ~(1 << PRTIM0);
    #else
        #ifdef PRR
	        PRR &= ~(1 << PRTIM0);
        #endif
    #endif

    
}



/**
 * \brief Disables Timer/Counter 0 on the power reduction register 
 */
void Timer0Disable() {
    
    /* Disable TC0 From Power Reduction Register */
	
    #ifdef PRR0
	    PRR0 |= (1 << PRTIM0);
    #else
        #ifdef PRR
	        PRR |= (1 << PRTIM0);
        #endif
    #endif
}



#if defined(OCR0A)
/**
 * \brief Sets the duty cycle of OCR0A
 * 
 * 
 * \param dutyCycle The value to set for PWM
 */
void Pwm0ASetDutyCycle(uint8_t dutyCycle)
{

    //Save reference to Timer control register
    uint8_t conB = TCCR0B;

	//Clear prescaler to stop timer
	T0ClearPrescaler();
	
	OCR0A = dutyCycle;

	//Restart an reset timer
	TCCR0B |= conB;
}
#endif



#if defined(OCR0B)
/**
 * \brief Sets the duty cycle of OCR0B
 * 
 * 
 * \param dutyCycle The value to set for PWM
 */
void Pwm0BSetDutyCycle(uint8_t dutyCycle)
{

    //Save reference to Timer control register
	uint8_t conB = TCCR0B;

	//Clear prescaler to stop timer
    T0ClearPrescaler();

	OCR0B = dutyCycle;

	//Restart and reset timer
	TCCR0B |= conB;
}
#endif




#endif


#ifdef TCNT1


/**
 * \brief Initializes Timer/Counter 1
 * 
 * \param timer_settings - UDT timer struct with the settings structs
 * 
 * \return Initialization status.  
 */
int8_t Timer1Init(Timer_t timer_settings)
{

    /* Enable TC1 From Power Reduction Register */
    #ifdef PRR0
	    PRR0 &= ~(1 << PRTIM1);
    #else
        #ifdef PRR
	        PRR &= ~(1 << PRTIM1);
        #endif
    #endif

    //Make sure timer stopped
    TCCR1B = 0;

    TCNT1 = 0;
    OCR1AH = 0;
    OCR1AL = 0;
    OCR1BH = 0;
    OCR1BL = 0;

	TCCR1A = (timer_settings.output_mode.comA << COM1A0)   
	         | (timer_settings.output_mode.comB << COM1B0) 
	         | (timer_settings.waveform.WGM1 << WGM11) | (timer_settings.waveform.WGM0 << WGM10);


    TIMSK1 = (timer_settings.interrupts.outputCompareMatchA << OCIE1A | 
        timer_settings.interrupts.outputCompareMatchB << OCIE1B | timer_settings.interrupts.overflow << TOIE1);

    TCCR1B = (timer_settings.waveform.WGM2 << WGM12);

    #ifdef WGM13
        TCCR1B |= (timer_settings.waveform.WGM3 << WGM13);
    #endif

    TCCR1C = (timer_settings.output_mode.forceOutA << FOC1A | timer_settings.output_mode.forceOutB << FOC1B);

	return 0;
}


/**
 * \brief Enables Timer/Counter 1 on the power reduction register 
 */
void Timer1Enable() 
{

    /* Enable TC1 From Power Reduction Register */
    #ifdef PRR0
	    PRR0 &= ~(1 << PRTIM1);
    #else
        #ifdef PRR
	        PRR &= ~(1 << PRTIM1);
        #endif
    #endif
}



/**
 * \brief Disables Timer/Counter 1 on the power reduction register 
 */
void Timer1Disable() 
{
    /* Disable TC1 From Power Reduction Register */

    #ifdef PRR0
	    PRR0 |= (1 << PRTIM1);
    #else
        #ifdef PRR
	        PRR |= (1 << PRTIM1);
        #endif
    #endif
}



#if defined(OCR1A)
/**
 * \brief Sets the duty cycle of OCR1A
 * 
 * 
 * \param dutyCycle The value to set for PWM
 */
void Pwm1ASetDutyCycle(uint16_t dutyCycle)
{

    //Save reference to Timer control register
    uint8_t conB = TCCR1B;

	//Clear prescaler register and stop timer
	TCCR1B = 0;

	//Set the duty cycle
	Pwm1A_load_reg(dutyCycle);

	//Restart an reset timer
	TCCR1B |= conB;
}
#endif



#if defined(OCR1B)
/**
 * \brief Sets the duty cycle of OCR1B
 * 
 * 
 * \param dutyCycle The value to set for PWM
 */
void Pwm1BSetDutyCycle(uint16_t dutyCycle)
{

    //Save reference to Timer control register
	uint8_t conB = TCCR1B;

	//Clear prescaler register and stop timer
	TCCR1B = 0;

	//Set the duty cycle
	Pwm1B_load_reg(dutyCycle);

	//Restart and reset timer
	TCCR1B |= conB;
}
#endif




#endif


#ifdef TCNT2

/**
 * \brief Initializes Timer/Counter 2
 * 
 * \param outputCompBits - UDT struct with the output compare bit values
 * \param waveFormBits - UDT struct with the waveform bit values
 * \param interrupts - UDT struct with the interrupt bit values
 * \return Initialization status.  
 */
int8_t Timer2Init(Output_compare_bits outputCompBits, Waveform_select_bits waveFormBits, Interrupt_mask_bits interrupts)
{

    
	// /* Enable TC2 From Power Reduction Register */
	PRR0 &= ~(1 << PRTIM2);

    TCNT2 = 0;

    //Make sure timer 2, stopped
    TCCR2B = 0;

	TCCR2A = (outputCompBits.comA << COM2A0)   
	         | (outputCompBits.comB << COM2B0) 
	         | (waveFormBits.WGM1 << WGM21) | (waveFormBits.WGM0 << WGM20);


    TIMSK2 = (interrupts.outputCompareMatchA << OCIE2A | interrupts.outputCompareMatchB << OCIE2B | interrupts.overflow << TOIE2);

    TCCR2B = (outputCompBits.forceOutA << FOC2A | outputCompBits.forceOutB << FOC2B |waveFormBits.WGM2 << WGM22);


	return 0;
}


/**
 * \brief Enables Timer/Counter 2 on the power reduction register 
 */
void Timer2Enable()
{
    /* Enable TC2 From Power Reduction Register */
	PRR0 &= ~(1 << PRTIM2);
}

/**
 * \brief Disables Timer/Counter 2 on the power reduction register 
 */
void Timer2Disable()
{
    /* Disable TC2 From Power Reduction Register */
	PRR0 |= (1 << PRTIM2);
}



#if defined(OCR2A)
/**
 * \brief Sets the duty cycle of OCR2A
 * 
 * 
 * \param dutyCycle The value to set for PWM
 */
void Pwm2ASetDutyCycle(uint16_t dutyCycle)
{

    //Save reference to Timer control register
    uint8_t conB = TCCR2B;

	//Clear prescaler register and stop timer
	TCCR2B = 0;

	//Set the duty cycle
	Pwm2A_load_reg(dutyCycle);

	//Restart an reset timer
	TCCR2B |= conB;
}
#endif



#if defined(OCR2B)
/**
 * \brief Sets the duty cycle of OCR2B
 * 
 * 
 * \param dutyCycle The value to set for PWM
 */
void Pwm2BSetDutyCycle(uint16_t dutyCycle)
{

    //Save reference to Timer control register
	uint8_t conB = TCCR2B;

	//Clear prescaler register and stop timer
	TCCR2B = 0;

	//Set the duty cycle
	Pwm2B_load_reg(dutyCycle);

	//Restart and reset timer
	TCCR2B |= conB;
}
#endif


#endif


#ifdef TCNT3


/**
 * \brief Initializes Timer/Counter 3
 * 
 * \param outputCompBits - UDT struct with the output compare bit values
 * \param waveFormBits - UDT struct with the waveform bit values
 * \param interrupts - UDT struct with the interrupt bit values
 * \return Initialization status.  
 */
int8_t Timer3Init(Output_compare_bits outputCompBits, Waveform_select_bits waveFormBits, Interrupt_mask_bits interrupts)
{

    
	/* Enable TC3 From Power Reduction Register */
	PRR1 &= ~(1 << PRTIM3);

    //Make sure timer 3, stopped
    TCCR3B = 0;

    TCNT3 = 0;
    OCR3AH = 0;
    OCR3AL = 0;
    OCR3BH = 0;
    OCR3BL = 0;


	TCCR3A = (outputCompBits.comA << COM3A0)   
	         | (outputCompBits.comB << COM3B0) 
	         | (waveFormBits.WGM1 << WGM31) | (waveFormBits.WGM0 << WGM30);


    TIMSK3 = (interrupts.outputCompareMatchA << OCIE3A | interrupts.outputCompareMatchB << OCIE3B | interrupts.overflow << TOIE3);

    TCCR3B |= (waveFormBits.WGM2 << WGM32);
    TCCR3C = (outputCompBits.forceOutA << FOC3A | outputCompBits.forceOutB << FOC3B);

	return 0;
}


/**
 * \brief Enables Timer/Counter 3 on the power reduction register 
 */
void Timer3Enable() {
    /* Enable TC3 From Power Reduction Register */
	PRR1 &= ~(1 << PRTIM3);
}

/**
 * \brief Disables Timer/Counter 3 on the power reduction register 
 */
void Timer3Disable() {
    /* Disable TC3 From Power Reduction Register */
	PRR1 |= (1 << PRTIM3);
}


#endif












#endif
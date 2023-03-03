/**
 * \file mcuAdc.c
 * \author Tim Robbins
 * \brief Source file for analog to digital (ADC) functionalities, including digital to analog (DAC) functionalities
 */
#ifndef MCU_ADC_C_
#define MCU_ADC_C_ 1

#include "mcuAdc.h"



/**
 * \brief Gets an adc value
 * \param adcChannel The adc channel to use
 * \return The adc value
 */
uint16_t AdcGet(adc_channel_t adcChannel)
{

    //Variables
    uint16_t adcVal = 0; //The return value from the ADC
    
    //Set the passed channel selection
    ADC_CHANNEL_REG |= adcChannel;
    
    //Start the ADC conversion
    ADC_start_conversion();
    
    //Wait for adc conversion to end
    while(ADC_get_status());

    //Get the result
    adcVal = (uint16_t)ADC_get_result();

    //Clear the passed channel selection
    ADC_CHANNEL_REG &= ~(adcChannel);
    
    //Return the adc value
    return adcVal;
    
}



/**
 * \brief Samples an ADC reading for x counts and returns the average
 * \param adcChannel The adc channel to use
 * \param sampleCount The amount of times to sample the ADC
 * \return  The average adc value
 */
uint16_t AdcSample(adc_channel_t adcChannel, uint8_t sampleCount)
{
    //Variables
    uint16_t adcResult = 0; //Return value from the ADC
    
    //If the sample count is greater than 0, avoid divide by 0 errors,...
    if(sampleCount > 0)
    {
        //Create a variable for the loop
        uint8_t i = 0;

        //Select the passed channel
        ADC_CHANNEL_REG |= adcChannel;

        //While the index is less than the passed sample count...
        while(i < sampleCount)
        {
            i++;

            ADC_start_conversion();
            while(ADC_get_status());
            adcResult += (uint16_t)ADC_get_result();
        }
        
        adcResult /= sampleCount;

        //Make sure the clear the selected channel on the way out
        ADC_CHANNEL_REG &= ~adcChannel;

    }
    
    return adcResult;
}





#if defined(__DAC_INCLUDED__)


/**
 * \brief Sets and outputs a passed DAC value
 * \param dacValue the value to load into the DAC data register
 */
void DacSet(uint16_t dacValue)
{
    //If the value is 0....
    if(dacValue == 0)
    {
        //Disable the DAC and clear the values
        DAC_disable();
        DAC_output_disable();
        DAC_load(0);
    }
    //Else...
    else
    {
        //Enable the DAC
        DAC_enable();
        
        //Disable the output while loading
        DAC_output_disable();
        
        //Load the DAC value
        DAC_load(dacValue);
        
        //Re-enable the DAC output
        DAC_output_enable();
    }
    
    
    
}


#endif


#endif

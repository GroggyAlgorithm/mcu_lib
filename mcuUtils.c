/**
 * \file mcuUtils.c
 * \author Tim Robbins
 * \brief Utilities file for micro controllers
 */ 

#include "mcuUtils.h"

#ifndef MCUUTILS_C_
#define MCUUTILS_C_ 1





/**
* \brief Calculates the top value needed based off of the global cpu speed/(prescaler * (1+hertz). Replacing hertz with the value for TOP will give you the hertz generated
* \param cpuSpeed The speed of the CPU in HERTZ
* \param prescaler The value of the prescaler. Ex: prescaler == 256 or prescaler == 64
* \param hertz The value for the hertz desired. Replacing this with an already know TOP value will give you the hertz created.
* \return The TOP value needed to create a frequency at X hertz, or if entering a know top value, the hertz.
*/
uint32_t CalculateFrequencyTop(uint64_t cpuSpeed, uint16_t prescaler, uint16_t hertz)
{
	
	uint32_t newFreq = 0;
	
	if( (uint32_t)(prescaler * ( 1 + hertz) ) != 0 && (uint32_t)(prescaler * ( 1 + hertz) ) < cpuSpeed)
	{
		newFreq = ((cpuSpeed) / ((prescaler) * ( 1 + hertz)));
	}
	
	return newFreq;
}


/**
* \brief Turns the passed value into a char array
* \param valueAsCharArray The array to load the value into
* \param numVal The value to convert to an array
* \param ignoreInitialEmpties If 0, all empty values will be equal to '0'. Else, they will be equal to ' '  until first value found
*/
void ShortToCharArray(char valueAsCharArray[6], uint16_t numVal, uint8_t ignoreInitialEmpties)
{
	//Variables
	uint8_t firstValue =  (numVal / 10000);
	uint8_t secondValue = ((numVal / 1000) % 10);
	uint8_t thirdValue =  ((numVal % 1000)/100);
	uint8_t fourthValue = ((numVal % 100) / 10);
	uint8_t fifthValue =  ((numVal % 10));
	
	for(uint8_t i = 0; i < 6; i++)
	{
		valueAsCharArray[i] = ' ';
	}
	
	//Always form the last value, 0 or not
	fifthValue += 0x30;
	valueAsCharArray[4] = (char)fifthValue;
	
	if(ignoreInitialEmpties == 0)
	{
		firstValue += (0x30);
		secondValue += (0x30);
		thirdValue += (0x30);
		fourthValue += (0x30);
		valueAsCharArray[0] = (char)firstValue;
		valueAsCharArray[1] = (char)secondValue;
		valueAsCharArray[2] = (char)thirdValue;
		valueAsCharArray[3] = (char)fourthValue;
	}
	else
	{
		//Form the characters
		if(firstValue > 0)
		{
			firstValue += (0x30);
			secondValue += (0x30);
			thirdValue += 0x30;
			fourthValue += 0x30;
			valueAsCharArray[0] = (char)firstValue;
			valueAsCharArray[1] = (char)secondValue;
			valueAsCharArray[2] = (char)thirdValue;
			valueAsCharArray[3] = (char)fourthValue;
		}
		else if (secondValue > 0)
		{
			secondValue += (0x30);
			thirdValue += 0x30;
			fourthValue += 0x30;
			valueAsCharArray[1] = (char)secondValue;
			valueAsCharArray[2] = (char)thirdValue;
			valueAsCharArray[3] = (char)fourthValue;
		}
		else if (thirdValue > 0)
		{
			thirdValue += 0x30;
			fourthValue += 0x30;
			valueAsCharArray[2] = (char)thirdValue;
			valueAsCharArray[3] = (char)fourthValue;
		}
		else if(fourthValue > 0)
		{
			fourthValue += 0x30;
			valueAsCharArray[3] = (char)fourthValue;
		}
	}

}


/**
* \brief Converts the passed value to a percentage in the range of min to max values
* \param minValue The minimum possible value
* \param maxValue The maximum possible value
* \param value The value to convert to a percentage
* \return uint8_t percentage
*/
uint8_t NormalizeToPercentage(uint16_t minValue, uint16_t maxValue, uint16_t value)
{
    //The calculated value for the value from the percentage value passed
	uint8_t calculatedValue = 0; 
	
    //If the min value is greater than the max value...
    if(minValue > maxValue)
    {
		//Swap the values
        maxValue ^= minValue;
        minValue ^= maxValue;
        maxValue ^= minValue;
    }
    
	//If the percentage passed is greater than or equal to 100%...
	if(value >= maxValue || minValue == maxValue)
	{
		//Set to 100%
		calculatedValue = 100;
	}
	//else if the value is greater than minValue...
	else if(value > minValue)
	{
        
		//Get the beginning point of the value
		float normalizedValue =  (float)((float)(value-minValue)/(maxValue - minValue));
		
		//Multiply this value by 100
		calculatedValue = (uint8_t)(normalizedValue * 100);
	
	}
	//else...
    else
    {
		//Just make sure the calculated value is at 0.
        calculatedValue = 0;
    }
	
	return calculatedValue;
}



/**
* \brief Converts the passed percentage value to a value in the range of min to max
* \param minValue The minimum possible value
* \param maxValue The maximum possible value
* \param percentageValue The percentage value in the range
* \return uint16_t calculated value
*/
int16_t ConvertPercentageInRange(int16_t minValue, int16_t maxValue, uint16_t percentageValue)
{
    //The calculated value for the value from the percentage value passed
	int16_t calculatedValue = 0; 
	
    //If the min value is greater than the max value...
    if(minValue > maxValue)
    {
		//Swap the values
        maxValue ^= minValue;
        minValue ^= maxValue;
        maxValue ^= minValue;
    }
    
	//If the percentage passed is greater than or equal to 100% or min value is equal to the max value...
	if(percentageValue >= 100 || minValue == maxValue)
	{
		//Set to the max value
		calculatedValue = maxValue;
	}
	//else if the value is greater than minValue...
	else if(percentageValue > 0)
	{
		//Get the beginning point of the value by taking the percentage and dividing by 100
		float normalizedValue =  (float)((float)percentageValue/100.0f);
		
		//Multiply this value by the max - min value to get the calculated value.
		calculatedValue = (int16_t)(normalizedValue * (maxValue - minValue));
	
	}
    else
    {
        calculatedValue = minValue;
    }
	
	return calculatedValue;
}



/**
* \brief Converts the passed percentage value to a value in the range of 0 to max
* \param maxValue The maximum possible value
* \param percentageValue The percentage value in the range
* \return uint16_t calculated value
*/
uint16_t ConvertPercentage(uint16_t maxValue, uint16_t percentageValue)
{
	//The calculated value for the value from the percentage value passed
	uint16_t calculatedValue = 0; 
	
	//If the percentage passed is greater than or equal to 100%...
	if(percentageValue >= 100)
	{
		//Set to the max value
		calculatedValue = maxValue;
	}
	//else if the value is greater than 0...
	else if(percentageValue > 0)
	{
		//Get the beginning point of the value by taking the percentage and dividing by 100
		float mathedUpPercentage =  (float)((float)percentageValue/100.0f);
		
		//Multiply this value by the max value to get the calculated value.
		calculatedValue = (uint16_t)(mathedUpPercentage * maxValue);
	
	}
	
	return calculatedValue;

}



/**
 * \brief Takes a 10 bit ADC value and converts it to a voltage within 5 volts. Max = 5000
 * \param adcValue The adc value done gotten
 * \return The voltage value, up to 5000 = 5 volts
 */
uint16_t Adc10bitTo5Volts(uint16_t adcValue)
{
    //The adc value as a voltage
    uint16_t adcVoltage = 0;
    
	float adcFloat = ADC_10B_TO_5V;
	
	adcFloat *= adcValue;
	
	adcVoltage = (uint16_t)(adcFloat * 1000);
    
    return adcVoltage;
}



/**
 * \brief Takes an ADC value and converts it to a voltage
 * \param adcReferenceVoltage The reference voltage for the ADC
 * \param adcResolution resolution of the adc (10 bit = 1024 or 1023, 8 bit = 256 or 255, ect...)
 * \param adcValue The adc value done gotten
 * \return The voltage value, up to 5000 = 5 volts
 */
uint16_t AdcToVolts(uint8_t adcReferenceVoltage, uint16_t adcResolution, uint16_t adcValue)
{
    //The adc value as a voltage
    uint16_t adcVoltage = 0;
	
	float adcFloat = ((float)(adcReferenceVoltage)/(float)(adcResolution));
	
	adcFloat *= adcValue;
	
	adcVoltage = (uint16_t)(adcFloat * 1000);
    
    return adcVoltage;
}



/**
 * \brief Converts the desired frequency to the number of required timer counts and the amount of required overflow counts for a 16 bit timer
 * \param systemFreq The system frequency in hertz
 * \param prescaler The timer prescaler value. Example: prescaler of 1,8,256,1024
 * \param freqInHz The desired frequency, in Hz
 * \param overflowCounts The amount of overflow counts
 * \return The calculated clock value to count to
 */
uint16_t ClockCountsFor16BitFreq(uint64_t systemFreq, uint16_t prescaler, uint16_t freqInHz, uint16_t *overflowCounts)
{
    //Calculate the time required for the frequency by dividing 1 by the desired frequency
	uint32_t calculatedTotalCounts = CalculateFrequencyTop((uint32_t)systemFreq, prescaler,freqInHz);
	
    //Create a variable for the return value
    uint16_t calculatedTimerCounts = 0;
    
    //Reset the overflow counts
    *overflowCounts = 0;
    
    //If the calculated counts are over 16 bit max
    if(calculatedTotalCounts >= 65536)
    {
        *overflowCounts = (uint16_t)(calculatedTotalCounts / 65536);
        calculatedTotalCounts = 65535;
    }
    
    //Convert the calculated total counts to a unsigned short
    calculatedTimerCounts = ((uint16_t)calculatedTotalCounts);
    
    //Return the calculated number of timer counts
    return calculatedTimerCounts;
    
    
}



/**
 * \brief Converts the desired frequency to the number of required timer counts and the amount of required overflow counts for an 8 bit timer
 * \param systemFreq The system frequency in hertz
 * \param prescaler The timer prescaler value. Example: prescaler of 1,8,256,1024
 * \param freqInHz The desired frequency, in Hz
 * \param overflowCounts The amount of overflow counts
 * \return The calculated clock value to count to
 */
uint8_t ClockCountsFor8BitFreq(uint64_t systemFreq, uint16_t prescaler, uint16_t freqInHz, uint16_t *overflowCounts)
{
    ///Calculate the time required for the frequency by dividing 1 by the desired frequency
    uint32_t calculatedTotalCounts = CalculateFrequencyTop((uint32_t)systemFreq, prescaler,freqInHz);
    
    //Create a variable for the return value
    uint8_t calculatedTimerCounts = 0;
    
    //Reset the overflow counts
    *overflowCounts = 0;
    
    //If the calculated counts are over 8 bit max
    if(calculatedTotalCounts >= 256)
    {
        *overflowCounts = (uint16_t)(calculatedTotalCounts / 256);
        calculatedTotalCounts = 255;
    }
    
    //Convert the calculated total counts to a unsigned char
    calculatedTimerCounts = ((uint8_t)calculatedTotalCounts);
    
    //Return the calculated number of timer counts
    return calculatedTimerCounts;
    
    
}







#endif

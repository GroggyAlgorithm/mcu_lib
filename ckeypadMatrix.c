/**
 * \file ckeypadMatrix.c
 * \author Tim Robbins
 * \brief source file for keypad interfacing
 */
#include "ckeypadMatrix.h"

#if !defined(__CKEYPADMATRIX_C__) && defined(__INCLUDED_CKEYPADMATRIX__)
#define __CKEYPADMATRIX_C__	1

#include "mcuUtils.h"
#include "mcuPinUtils.h"
#include "mcuDelays.h"

/**
* \brief Gets a keypad value from the const 2D array passed and constant pin values
* \return The key pressed, if any from the keypad array
*/
uint8_t kp_Scan_const(const unsigned char uchrColumnPinPositions[KP_COLUMNS],
const unsigned char uchrRowPinPositions[KP_ROWS], const unsigned char uchrKeypadValues[KP_ROWS][KP_COLUMNS]) 
{
	
	//Variables
	uint8_t i = 0; //column index
	uint8_t j = 0; //Subloop row index
	volatile uint8_t currentColumnPress = 0; //The currently pressed column value
	volatile uint8_t currentRowPress = 0; //The currently pressed row value
	uint8_t pressedValue = '\0'; //The return value for the entered value
	uint8_t columnMask = 0; //Mask for the column pins
	uint8_t rowMask = 0; //Mask for the row pins
	
	//Loop through and create a mask for the columns
	for(i = 0; i < KP_COLUMNS; i++)
	{
		columnMask |= (1 << uchrColumnPinPositions[i]);
	}
	
	//Loop through and create a mask for the rows
	for(i = 0; i < KP_ROWS; i++)
	{
		rowMask |= (1 << uchrRowPinPositions[i]);
	}
	
	//Make sure index is reset
	i=0;
	
	//Set ports initial values.
	
	//Output, input initially to not cross contaminate key presses
	writeMaskInput(KP_COLUMN_DIR, columnMask);
	KP_COLUMN_PORT |= columnMask;
	
	//Input pull up
	writeMaskInput(KP_ROW_DIR, rowMask);
	KP_ROW_PORT |= (rowMask);
	
	
	//Loop through and check for columns
	for(i = 0; i < KP_COLUMNS; i++)
	{
		//Set current pin
		setBitOutput(KP_COLUMN_DIR, uchrColumnPinPositions[i]);
		KP_COLUMN_PORT &= ~(1 << uchrColumnPinPositions[i]);
		
		//Slight delay for time to take affect
		delayForMicroseconds(1);
		
		//Read the value on the row pins
		currentRowPress = (KP_ROW_READ & rowMask);
		
		//Slight delay for time to take affect
		delayForMicroseconds(1);
		
		//Reset current pin
		KP_COLUMN_PORT |= (1 << uchrColumnPinPositions[i]);
		setBitInput(KP_COLUMN_DIR, uchrColumnPinPositions[i]);
		
		//If there is a value indicating a key press...
		if(currentRowPress != rowMask)
		{
			
			//Invert the pins
			
			//Output, input initially to not cross contaminate key presses
			writeMaskInput(KP_ROW_DIR, rowMask);
			KP_ROW_PORT |= rowMask;
			
			
			//Input pull up
			writeMaskInput(KP_COLUMN_DIR, columnMask);
			KP_COLUMN_PORT |= (columnMask);
			
			//Slight delay for time to take affect
			delayForMicroseconds(1);
			
			//Loop through the rows...
			for(j = 0; j < KP_ROWS; j++)
			{
				//Set current pin
				setBitOutput(KP_ROW_DIR, uchrRowPinPositions[j]);
				KP_ROW_PORT &= ~(1 << uchrRowPinPositions[j]);
				
				//Slight delay for time to take affect
				delayForMicroseconds(1);
				
				//Read the value on the column pins
				currentColumnPress = (KP_COLUMN_READ & columnMask);
				
				//If there is a value indicating a key press...
				if(currentColumnPress != columnMask)
				{
					//We found our value
					return uchrKeypadValues[j][i];
				}
				
				//Reset current pin
				setBitInput(KP_ROW_DIR, uchrRowPinPositions[j]);
				KP_ROW_PORT &= ~(1 << uchrRowPinPositions[j]);
				
			}
			//Output, input initially to not cross contaminate key presses
			writeMaskInput(KP_COLUMN_DIR, columnMask);
			KP_COLUMN_PORT |= columnMask;
			
			
			//Input pull up
			writeMaskInput(KP_ROW_DIR, rowMask);
			KP_ROW_PORT |= (rowMask);
		}
		
		
		
		
	}
	
	
	return pressedValue;
	

	
}



/**
* \brief Gets a keypad value from the 2D array passed
* \return The key pressed, if any from the keypad array
*/
uint8_t kp_Scan(unsigned char uchrColumnPinPositions[KP_COLUMNS],
unsigned char uchrRowPinPositions[KP_ROWS], unsigned char uchrKeypadValues[KP_ROWS][KP_COLUMNS]) 
{
	
	//Variables
	uint8_t i = 0; //column index
	uint8_t j = 0; //Subloop row index
	volatile uint8_t currentColumnPress = 0; //The currently pressed column value
	volatile uint8_t currentRowPress = 0; //The currently pressed row value
	uint8_t pressedValue = '\0'; //The return value for the entered value
	uint8_t columnMask = 0; //Mask for the column pins
	uint8_t rowMask = 0; //Mask for the row pins
	
	//Loop through and create a mask for the columns
	for(i = 0; i < KP_COLUMNS; i++)
	{
		columnMask |= (1 << uchrColumnPinPositions[i]);
	}
	
	//Loop through and create a mask for the rows
	for(i = 0; i < KP_ROWS; i++)
	{
		rowMask |= (1 << uchrRowPinPositions[i]);
	}
	
	//Make sure index is reset
	i=0;
	
	//Set ports initial values.
	
	//Output, input initially to not cross contaminate key presses
	writeMaskInput(KP_COLUMN_DIR, columnMask);
	KP_COLUMN_PORT |= columnMask;
	
	//Input pull up
	writeMaskInput(KP_ROW_DIR, rowMask);
	KP_ROW_PORT |= (rowMask);
	
	
	//Loop through and check for columns
	for(i = 0; i < KP_COLUMNS; i++)
	{
		//Set current pin
		setBitOutput(KP_COLUMN_DIR, uchrColumnPinPositions[i]);
		KP_COLUMN_PORT &= ~(1 << uchrColumnPinPositions[i]);
		
		//Slight delay for time to take affect
		delayForMicroseconds(1);
		
		//Read the value on the row pins
		currentRowPress = (KP_ROW_READ & rowMask);
		
		//Slight delay for time to take affect
		delayForMicroseconds(1);
		
		//Reset current pin
		KP_COLUMN_PORT |= (1 << uchrColumnPinPositions[i]);
		setBitInput(KP_COLUMN_DIR, uchrColumnPinPositions[i]);
		
		//If there is a value indicating a key press...
		if(currentRowPress != rowMask)
		{
			
			//Invert the pins
			
			//Output, input initially to not cross contaminate key presses
			writeMaskInput(KP_ROW_DIR, rowMask);
			KP_ROW_PORT |= rowMask;
			
			
			//Input pull up
			writeMaskInput(KP_COLUMN_DIR, columnMask);
			KP_COLUMN_PORT |= (columnMask);
			
			//Slight delay for time to take affect
			delayForMicroseconds(1);
			
			//Loop through the rows...
			for(j = 0; j < KP_ROWS; j++)
			{
				//Set current pin
				setBitOutput(KP_ROW_DIR, uchrRowPinPositions[j]);
				KP_ROW_PORT &= ~(1 << uchrRowPinPositions[j]);
				
				//Slight delay for time to take affect
				delayForMicroseconds(1);
				
				//Read the value on the column pins
				currentColumnPress = (KP_COLUMN_READ & columnMask);
				
				//If there is a value indicating a key press...
				if(currentColumnPress != columnMask)
				{
					//We found our value
					return uchrKeypadValues[j][i];
				}
				
				//Reset current pin
				setBitInput(KP_ROW_DIR, uchrRowPinPositions[j]);
				KP_ROW_PORT &= ~(1 << uchrRowPinPositions[j]);
				
			}
			//Output, input initially to not cross contaminate key presses
			writeMaskInput(KP_COLUMN_DIR, columnMask);
			KP_COLUMN_PORT |= columnMask;
			
			
			//Input pull up
			writeMaskInput(KP_ROW_DIR, rowMask);
			KP_ROW_PORT |= (rowMask);
		}
		
		
		
		
	}
	
	
	return pressedValue;
	

	
}








#endif
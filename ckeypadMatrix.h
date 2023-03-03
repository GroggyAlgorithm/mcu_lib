/**
 * \file ckeypadMatrix.h
 * \author Tim Robbins
 * \version v2.0
 * \brief header file for keypad interfacing \n
 * REQUIREMENTS: \n
 * "config.h", "mcuUtils.h", and "mcuDelays.h" must be included. \n
 * KP_COLUMN_PORT, KP_COLUMN_READ, KP_COLUMN_DIR, KP_ROW_PORT, KP_ROW_READ, KP_ROW_DIR must be defined as a macro for their ports in "config.h". \n
 * KP_COLUMNS and KP_ROWS should be defined as the amount of columns and the amount of rows that the keypad has, otherwise it will default to 3x4 \n
 *
 *	\n
 *
 * Example use: \n
 *
 *
 * #define KP_COLUMN_PORT	PORTA \n
 * #define KP_COLUMN_READ	PINA \n
 * #define KP_COLUMN_DIR	DDRA \n
 * #define KP_ROW_PORT		PORTD \n
 * #define KP_ROW_READ		PIND \n
 * #define KP_ROW_DIR		DDRD \n
 * #define KP_COLUMNS		3 \n
 * #define KP_ROWS		    4 \n
 *
 *
 const uint8_t m_uchrKeypdMatrixColumnPins[KP_COLUMNS] = { 0,1,2 }; \n
 const uint8_t m_uchrKeypdMatrixRowPins[KP_ROWS] = { 0,1,6,7 }; \n
 const uint8_t m_uchrKeypadMatrixValues[KP_ROWS][KP_COLUMNS] =
 { \n
    { \n
        '1', '2', '3' \n
    }, \n
    { \n
        '4', '5', '6' \n
    }, \n
    { \n
        '7', '8', '9' \n
    }, \n
    { \n
    '*', '0', '#' \n
    } \n
 }; \n
 \n
 currentKeypress = kp_Scan_const(m_uchrKeypdMatrixColumnPins, m_uchrKeypdMatrixRowPins,m_uchrKeypadMatrixValues); \n
 
 *
 *
 *
 */
#include "config.h"

#ifndef __CKEYPADMATRIX_H__

#define __CKEYPADMATRIX_H__			1
#define __INCLUDED_CKEYPADMATRIX__  1

#ifdef __cplusplus
extern "C" {
#endif



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




#ifndef KP_COLUMN_PORT
//#warning ckeypadMatrix.h: KP_COLUMN_PORT must be defined as the ports output register to use
#define __CKEYPADMATRIX_C__			-1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_COLUMN_READ
//#warning ckeypadMatrix.h: KP_COLUMN_READ must be defined as the ports read register to use
#define __CKEYPADMATRIX_C__			-1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_COLUMN_DIR
//#warning ckeypadMatrix.h: KP_COLUMN_DIR must be defined as the ports direction register to use
#define __CKEYPADMATRIX_C__			-1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_ROW_PORT
//#warning ckeypadMatrix.h: KP_ROW_PORT must be defined as the ports output register to use
#define __CKEYPADMATRIX_C__			-1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_ROW_READ
//#warning ckeypadMatrix.h: KP_ROW_READ must be defined as the ports read register to use
#define __CKEYPADMATRIX_C__			-1
#undef __INCLUDED_CKEYPADMATRIX__
#endif

#ifndef KP_ROW_DIR
//#warning ckeypadMatrix.h: KP_ROW_DIR must be defined as the ports direction register to use
#define __CKEYPADMATRIX_C__			-1
#undef __INCLUDED_CKEYPADMATRIX__
#endif




#if __CKEYPADMATRIX_C__ != -1

#ifndef KP_COLUMNS
//#warning ckeypadMatrix.h: KP_COLUMNS must be defined for the amount of column pins. Defaulting to 3
#define KP_COLUMNS					3
#endif

#ifndef KP_ROWS
//#warning ckeypadMatrix.h: KP_ROWS must be defined for the amount of row pins. Defaulting to 4
#define KP_ROWS						4
#endif


extern uint8_t kp_Scan_const(const unsigned char uchrColumnPinPositions[KP_COLUMNS],
const unsigned char uchrRowPinPositions[KP_ROWS], const unsigned char uchrKeypadValues[KP_ROWS][KP_COLUMNS]);

extern uint8_t kp_Scan(unsigned char uchrColumnPinPositions[KP_COLUMNS],
unsigned char uchrRowPinPositions[KP_ROWS], unsigned char uchrKeypadValues[KP_ROWS][KP_COLUMNS]);



#else
#if defined(__GNUC__)
#pragma message __FILE__ ": Definitions missing. View required definitions to include."
#else
#warning "ckeypadMatrix.h: Check Required macro definitions to include functionality."
#endif

#endif

#ifdef __cplusplus
}
#endif

#endif /* __CKEYPADMATRIX_H__ */
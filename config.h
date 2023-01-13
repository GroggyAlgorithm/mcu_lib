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













#ifdef	__cplusplus
}
#endif /* __cplusplus */




#endif


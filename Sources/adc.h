#ifndef ADC_H_
#define ADC_H_

/*
************************************************************************
                          Include Files
************************************************************************
*/

#include "PE_Types.h"							/* Data Type Definitions */

/*
************************************************************************
*                         Constants and Macros
************************************************************************
*/      

/* Samples to take per conversion for averaging */
#define MICROPHONE_SAMPLES		 	   		1
#define VREF_H_SAMPLES				   		1
#define VREF_L_SAMPLES				   		1

/* ADC Channels to convert  */
typedef enum conversionChannel{
	micOutput		 	  	 = 0,
	vrefHigh		      	 = 1,
	vrefLow			      	 = 2,
}conversionChannel_t;

/*
************************************************************************
*                         Function Prototypes
************************************************************************
*/      

uint16_t collect16BitMicrophoneValue( void );				/* Feedback Voltage Value from RMS-DC Converter */
uint16_t collect16BitVREH( void );							/* VrefH Voltage*/
uint16_t collect16BitVREL( void );							/* VrefL Voltage*/
uint16_t convertMillivolts( conversionChannel_t );			/* Convert ADC values to mV */

#endif /* ADC_H_ */


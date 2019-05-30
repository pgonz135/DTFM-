/*
 * goertzel.h
 *
 *  Created on: May 19, 2019
 *      Author: pablo
 */

#ifndef GOERTZEL_H_
#define GOERTZEL_H_

#include "PE_Types.h"

/* Sine and Cosine components (Hz) for the following tones: 697, 770, 852, 941, 1209, 1336, 1447,1663 */

#define DTFM_FREQUENCIES    8      	 /* Eight total frequencies in DTFM */
#define N                   255    	 /* Number of samples per iteration */
#define TONE_THRESHOLD		800   /* Magnitude threshold of a valid tone */


/* global variable to store samples */
uint16_t samples[N];

void goertzel( uint16_t [] );		/* goertzel function */

#endif /* GOERTZEL_H_ */

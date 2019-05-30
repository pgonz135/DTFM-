/*
 * goertzel.c
 *
 *  Created on: May 19, 2019
 *      Author: pablo
 */

#include "goertzel.h"
#include "PE_Types.h"
#include "TI1.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "math.h"
#include "lcd.h"

uint16_t samples[N] = {0};

/* structure to save real, imaginary and magnitude of all DTMF frequencies */
typedef struct frequencyData {
  float real;
  float img;
  float mag;
}frequencyData_t;

char thresholdDetect( frequencyData_t frequencyData[] );

const char symbol[4][4] = { { '1', '2', '3', 'A' }, 
							{ '4', '5', '6', 'B' }, 
							{ '7', '8', '9', 'C' }, 
							{ '*', '0', '#', 'D' } };

/* cosine and sine based on fs = 8.192kHz and N = 255 samples */
const float cosine_DTFM[ DTFM_FREQUENCIES ] = { 0.85413436951853600, 0.82369322365249000, 	/* 697 and 770 Hz */
												0.78642548848119400, 0.74246216289816400, 	/* 852 and 941 Hz */
												0.59010183190686500, 0.50878871282935400, 	/* 1209 and 1336 Hz */
												0.43374165548836700, 0.27921003773239200 };	/* 1447 and 1633 Hz */

const float sine_DTFM[ DTFM_FREQUENCIES ] =	  { 0.52005238083021400, 0.56703568962541400, 	/* 697 and 770 Hz */
												0.61768515529120100, 0.66988800307557400, 	/* 852 and 941 Hz */
												0.80732882271114400, 0.86089142503422000, 	/* 1209 and 1336 Hz */
												0.90103727797145600, 0.96023005307555100 };	/* 1447 and 1633 Hz */
/*
************************************************************************
                          	  	  goertzel

    Description:
     This function takes N samples collected by the ~8kHz timer interrupt
     and runs them through the Goertzel (DTFM Single Tone Detection Algorithm).
     The real (amplitude), imaginary (phase) and magnitude of the samples is
     saved into a structure for further processing.

    Arguments:
     array of samples[]

    Returns:
     None

***********************************************************************
*/

void goertzel( uint16_t samples[] ) {

  float q0, q1, q2 = 0;                                       	/* q0 = Current Val, q1 = Past Val, q2 = Past Past Val */
  float const scalingFactor = 1000.0f;                			/* magnitude scaling factor */
  int i, j = 0;                                               	/* index counters */
  frequencyData_t tones[ DTFM_FREQUENCIES ] = { { 0 } };        /* initialize structure and arrays */

  /* process N samples through each of the eight-(8) DTFM tones */
  for ( i = 0; i < DTFM_FREQUENCIES; i++ ) {
    /* calculate Goertzel on each N samples */
    q0 = 0; q1 = 0; q2 = 0;
    float a = 2 * cosine_DTFM[i];
    for ( j = 0; j < N ; ++j ) {
      q0 = q1;
      q1 = q2;
      q2 = (   a * q1 - q0 + (float)(samples[j]) );         	/* q0 = coeff * q1 - q2 + sample */
    }
    /* Calculate real and imaginary components, then copy structure to array */
    tones[i].real = ( q2 * cosine_DTFM[i] - q1 );
    tones[i].img =  ( q2 * sine_DTFM[i] );
    tones[i].mag =  ( ( sqrt(( tones[i].real * tones[i].real ) + ( tones[i].img * tones[i].img ))) / scalingFactor );
  }

  /* process detected tones */
  thresholdDetect( tones );
}

/*
************************************************************************
                          	  	  thresholdDetect

    Description:
     This function takes in the entire structure array of calculated real, imaginary
     and magnitude values calculated by the Goertzel function, calculates the two-(2)
     DTFM frequencies, and returns the character related to those tones. It also calls
     the lcd function to print the value of tone detected.

    Arguments:
     array of structures

    Returns:
     (char) actual keypad value

***********************************************************************
*/

char thresholdDetect( frequencyData_t tones[] ) {

  int i, j = 0;
  int toneCounter = 0;
  int firstToneIndex = 0;
  int secondToneIndex = 0;
  static char keypadCharacter[1] = {'X'};
  static char newChar[1] = {'X'};
  static char lastChar[1] = {'X'};

  /* examine DTFM column */
  for ( i = 0; i < ( DTFM_FREQUENCIES / 2 ); i++ ) {
    if ( tones[i].mag >= TONE_THRESHOLD ) {
      firstToneIndex = i;
      toneCounter++;
    }
  }

  /* examine DTFM row */
  uint8_t w = 0;
  for ( j = DTFM_FREQUENCIES / 2; j < ( DTFM_FREQUENCIES ); j++ ) {
    if ( tones[j].mag >= TONE_THRESHOLD ) {
      secondToneIndex = w;
      toneCounter++;
    }
    w++;
  }

  /* no valid tone detected */
  if ( toneCounter < 2 ) {
    keypadCharacter[1] = keypadCharacter[1];
  }

  /* valid tone, indexes point to 2D array */
  else {
    keypadCharacter[1] = ( symbol[ firstToneIndex ][ secondToneIndex ] );
    newChar[1] = keypadCharacter[1];
    if ( 'X' != keypadCharacter[1] && newChar[1] != lastChar[1] ) {
      printLCD( &keypadCharacter[1] );
      lastChar[1] = keypadCharacter[1];
    }
  }
  return keypadCharacter[1];
}

/*
************************************************************************
                          Include Files
************************************************************************
*/

#include <adc.h>
#include <Events.h>

/*
 ************************************************************************
                            Local Variables
 ************************************************************************
*/

uint16_t value[ AD1_CHANNEL_COUNT ];
uint16_t microphoneVoltage = 0;
uint16_t vrefHighVoltage = 0;
uint16_t vrefLowVoltage = 0;

/*
************************************************************************
                          collect16BitMicrophoneValue

    Description:
     This function collects the 16-bit value from the feedback voltage
     channel of the ferro-resonant transformer. It is a value that comes from
     the RMS-DC converter.

    Arguments:
     None

    Returns:
     Average 16 bit feedback voltage value.

***********************************************************************
*/

uint16_t collect16BitMicrophoneValue( void ) {

  uint16_t i = 0;
  uint32_t total = 0;
  uint32_t average = 0;

  /* Take Samples to Average */
  for ( i = 0; i < MICROPHONE_SAMPLES; i++ ) {
	AD1_MeasureChan( TRUE , micOutput );
    AD1_GetChanValue16( micOutput, &value[ micOutput ] );
    microphoneVoltage = value[ micOutput ];
    total += microphoneVoltage;
  }

  /* Take Average */
  average = total / MICROPHONE_SAMPLES;

  /* Reset Totals */
  total = 0x00;

  /* Return the Average */
  return average;
}

/*
************************************************************************
                          collect16BitVREH

    Description:
     This function collects the 16-bit value from the VREFH reference in
     the microprocessor. This is used for more accurate conversions.

    Arguments:
     None

    Returns:
     Average 16 bit VREFH Voltage.

***********************************************************************
*/

uint16_t collect16BitVREH( void ) {

  uint16_t i = 0;
  uint32_t total = 0;
  uint32_t average = 0;

  /*Take Samples to Average*/
  for ( i = 0; i < VREF_H_SAMPLES; i++ ) {
    AD1_MeasureChan( TRUE , vrefHigh );
    AD1_GetChanValue16( vrefHigh, &value[ vrefHigh ] );
    vrefHighVoltage = value[ vrefHigh ];
    total += vrefHighVoltage;
  }

  /*Take Average*/
  average = total / VREF_H_SAMPLES;

  /*Reset Totals*/
  total = 0x00;

  /*Return the Average*/
  return average;
}

/*
************************************************************************
                          collect16BitVREL

    Description:
     This function collects the 16-bit value from the VREFL reference in
     the microprocessor. This is used for more accurate voltage conversions.

    Arguments:
     None

    Returns:
     Average 16 bit VREFL Voltage (Ideally 0mV).

***********************************************************************
*/

uint16_t collect16BitVREL( void ) {

  uint16_t i = 0;
  uint32_t total = 0;
  uint32_t average = 0;

  /* Take Samples to Average */
  for ( i = 0; i < VREF_L_SAMPLES; i++ ) {
    AD1_MeasureChan( TRUE , vrefLow );
    AD1_GetChanValue16( vrefLow, &value[ vrefLow ] );
    vrefLowVoltage = value[ vrefLow ];
    total += vrefLowVoltage;
  }

  /* Take Average */
  average = total / VREF_L_SAMPLES;

  /* Reset Totals */
  total = 0x00;

  /* Return the Average */
  return average;
}

/*
************************************************************************
                          convertMillivolts

    Description:
     This function converts the desired channel bit value into usable volts.
     It uses VREFH and VREFL for accurate DC conversions.

    Arguments:
     conversionChannel_t (Desired ADC channel to convert)

    Returns:
     uint16_t milliVolt value of the desired channel.

***********************************************************************
*/

uint16_t convertMillivolts( conversionChannel_t channel ) {

  static uint16_t sixteenBitRatio = 65535;     /* Sixteen Bit Ratio */
  static uint16_t bits = 0;
  static uint16_t vrefh = 0;
  static uint16_t vrefl = 0;
  static uint16_t mV = 0;
  static uint32_t vrefHval = 0;
  static uint32_t vrefLval = 0;

  switch ( channel ) {
  
    case vrefHigh:
      break;
    case vrefLow:
      break;

    case micOutput:
      bits = collect16BitMicrophoneValue();
      break;
      

    default:
      break;
  }

  /* Collect VREH and VREFL 16-bit values, for precise conversion */
  vrefHval = collect16BitVREH();
  vrefLval = collect16BitVREL();
  /* Convert reference voltages to mV */
  vrefh = (33 * ( (vrefHval * 100) / sixteenBitRatio)); /* Note: Vref = 3000mV */
  vrefl = (33 * ( (vrefLval * 100) / sixteenBitRatio)); /* Note: Vref = 3000mV */
  /* Convert ADC voltage to mV */
  mV = bits * ( vrefh - vrefl ) / sixteenBitRatio;
  /* Return requested value in milliVolts */
  return mV;
}

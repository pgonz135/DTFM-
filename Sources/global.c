/*
************************************************************************
*                         Include Files
************************************************************************
*/   

#include <global.h>
#include <Events.h>
#include <math.h>

/*
************************************************************************
*                         Local Funnctions
************************************************************************
*/   


/*
************************************************************************
                          initGPIOpins

    Description:
     This function initializes all external GPIO pins for input or output
     functionalities depending on the purpose of the pin.

    Arguments:
     None

    Returns:
     None

***********************************************************************
*/

void initGPIOpins( void ) {

  /* Initializing the Port A pins */
  SIM_SCGC5  |= SIM_SCGC5_PORTA_MASK;  /* Turn on clock to PortA module */

  PORTA_PCR1 = PORT_PCR_MUX( 1 );      
  GPIOA_PCOR |= ( 1 <<  1 );           /* Set the initial output state to low */
  GPIOA_PDDR |= ( 1 <<  1 );           /* Set the pins direction to output */

  PORTA_PCR2 = PORT_PCR_MUX( 1 );      
  GPIOA_PCOR |= ( 1 <<  2 );           /* Set the initial output state to low */
  GPIOA_PDDR |= ( 1 <<  2 );           /* Set the pins direction to output */

  PORTA_PCR5 = PORT_PCR_MUX( 1 );      
  GPIOA_PCOR |= ( 1 << 5  );           /* Set the initial output state to low */
  GPIOA_PDDR |= ( 1 << 5  );           /* Set the pins direction to output */

  /* Initializing the Port B pins */
  SIM_SCGC5  |= SIM_SCGC5_PORTB_MASK;  /* Turn on clock to PortC module */

  PORTB_PCR0 = PORT_PCR_MUX( 1 );      
  GPIOB_PCOR |= ( 1 << 0 );            /* Set the initial output state to low */
  GPIOB_PDDR |= ( 1 << 0 );            /* Set the pins direction to output */

  PORTB_PCR1 = PORT_PCR_MUX( 1 );      
  GPIOB_PCOR |= ( 1 << 1 );            /* Set the initial output state to low */
  GPIOB_PDDR |= ( 1 << 1 );            /* Set the pins direction to output */

  PORTB_PCR2 = PORT_PCR_MUX( 1 );    
  GPIOB_PCOR |= ( 1 << 2 );            /* Set the initial output state to low */
  GPIOB_PDDR |= ( 1 << 2 );            /* Set the pins direction to output */

  PORTB_PCR3 = PORT_PCR_MUX( 1 );    
  GPIOB_PCOR |= ( 1 << 3 );            /* Set the initial output state to low */
  GPIOB_PDDR |= ( 1 << 3 );            /* Set the pins direction to output */

  PORTB_PCR8 = PORT_PCR_MUX( 1 );     
  GPIOB_PCOR |= ( 1 << 8 );           /* Set the initial output state to low */
  GPIOB_PDDR |= ( 1 << 8 );           /* Set the pins direction to output */

  PORTB_PCR9 = PORT_PCR_MUX( 1 );     
  GPIOB_PCOR |= ( 1 << 9 );           /* Set the initial output state to low */
  GPIOB_PDDR |= ( 1 << 9 );           /* Set the pins direction to output */

  PORTB_PCR10 = PORT_PCR_MUX( 1 );   
  GPIOB_PCOR |= ( 1 << 10 );           /* Set the initial output state to low */
  GPIOB_PDDR |= ( 1 << 10 );           /* Set the pins direction to output */

  PORTB_PCR11 = PORT_PCR_MUX( 1 );    
  GPIOB_PCOR |= ( 1 << 11 );           /* Set the initial output state to low */
  GPIOB_PDDR |= ( 1 << 11 );           /* Set the pins direction to output */
  
}

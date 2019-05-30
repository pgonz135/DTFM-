/*
 * lcd.c
 *
 *  Created on: May 23, 2019
 *      Author: Pablo J. Gonzalez
 */

#include "PE_Types.h"
#include "global.h"
#include "lcd.h"
#include "WAIT1.h"


#define ZERO_MASK 			0x00
#define UPPER_NIBBLE_MASK 	0x0F
#define LOWER_NIBBLE_MASK 	0xF0

#define _RS_HIGH 			set_RS() 		/* RS (Register Select) High */
#define _RS_LOW	 			reset_RS()		/* RS (Register Select) Low */
#define _READ 				set_READ()    	/* RW (Read/Write) High = 1 for reading */
#define _WRITE	 			set_WRITE()  	/* RW (Read/Write) Low = 0 for writing */
#define _EN_HIGH 			set_EN();		/* EN Enable High */
#define _EN_LOW	 			reset_EN();		/* EN Enable Low */

void dataSend( unsigned char );
void sendCmd( byte );
void dataWrite();
void dataRead();
void checkBusyFlag();

/* Function to write data to the LCD in 8-Bit mode */
void sendData( unsigned char data ) {
  uint8_t i, j = 0;
  byte lowerNibble = 0;
  byte upperNibble = 0;
  
  /* ensure lcd is not busy */
  checkBusyFlag();

  /* mask upper and lower nibbles */
  lowerNibble &= UPPER_NIBBLE_MASK;
  upperNibble &= LOWER_NIBBLE_MASK;

  /* load data into lower and upper nibbles */
  lowerNibble |= ( data | LOWER_NIBBLE_MASK );
  upperNibble |= ( data | UPPER_NIBBLE_MASK );

  _WRITE;
  _RS_HIGH;

  /* set lower nibble GPIOs */
  for ( i = 0; i < 4; i++ ) {
    if ( lowerNibble & 1 << i  ) {
    	set_DB( i );
    }
    else {
    	reset_DB( i );
    }
  }

  uint8_t w = 8; /* start upper nibble sequence at PTB16 */
  /* set higher nibble GPIOs */
  for ( j = 4; j < 8; j++ ) {
    if ( upperNibble & 1 << j  ) {
    	set_DB( w );
    }
    else {
    	reset_DB( w );
    }
    w++;
  }
  
  dataWrite();
}

/* Function to write commands to the LCD in 8-Bit mode */
void sendCmd( byte cmd ) {
  uint8_t i, j = 0;
  byte lowerNibble = 0;
  byte upperNibble = 0;

  /* ensure lcd is not busy */
  checkBusyFlag();

  /* mask upper and lower nibbles */
  lowerNibble &= UPPER_NIBBLE_MASK;
  upperNibble &= LOWER_NIBBLE_MASK;

  /* load data into lower and upper nibbles */
  lowerNibble |= ( cmd | LOWER_NIBBLE_MASK );
  upperNibble |= ( cmd | UPPER_NIBBLE_MASK );

  _WRITE;
  _RS_LOW;

  /* set lower nibble GPIOs */
  for ( i = 0; i < 4; i++ ) {
    if (  lowerNibble & 1 << i  ) {
    	set_DB( i );
    }
    else {
    	reset_DB( i );
    }
  }

  /* set higher nibble GPIOs */
  uint8_t w = 8; /* start upper nibble sequence at PTB16 */
  for ( j = 4; j < 8; j++ ) {
    if ( upperNibble & 1 << j ){
    	set_DB( w );
    }
    else {
    	reset_DB( w );
    }
    w++;
  }
  dataWrite();
}

void dataWrite(){
	checkBusyFlag();
	toggleEnable();
}

void initLCD(){
	/* lcd init. sequence */
	_RS_LOW;
	_WRITE;
	
	
	//checkBusyFlag();
	
	WAIT1_Waitus(1000);
	
	sendCmd( 0x30 );
	WAIT1_Waitus(30000);

	sendCmd( 0x30 );
	WAIT1_Waitus(30000);

	sendCmd( 0x30 );
	WAIT1_Waitus(30000);
	
	sendCmd( 0x38 );
	WAIT1_Waitus(30000);

	sendCmd( 0x08 );
	WAIT1_Waitus(30000);

	sendCmd( 0x01 );
	WAIT1_Waitus(30000);
	
	sendCmd( 0x06 );
	WAIT1_Waitus(30000);
	
	sendCmd( 0x0C );
	WAIT1_Waitus(30000);

	
}

void printLCD( char disp[] ) {
	
  int i = 0;
  static int j = 0;
  
  ++j;
  
  while ( '\0' != disp[i] ) {
    sendData( disp[i++] );
    /* automatically move to next line when first row fills up */
    if ( i == LCD_ROW_CHARS || j == LCD_ROW_CHARS ) {
    	sendCmd( CURSOR_SECOND_LINE );
    	j = 0;
    }
    /* wrap around and return home when second row fills up */
    if ( i == LCD_ROW_CHARS ) sendCmd( RETURN_HOME );
  }
}

void checkBusyFlag() {
  _READ;
  GPIOB_PDDR &= ~( 1 << 11 );                    			/* set DB7 as input */
  while ( ( 1 << 11 ) == ( GPIOB_PDIR & ( 1 << 11 ) ) ) { 	/* lcd is busy, wait */
    _EN_LOW;                      							/* continue reading data from lcd */
    WAIT1_Waitus( 1000 );
    _EN_HIGH;
  }
  GPIOB_PDDR |= ( 1 << 11 );                    			/* set DB7 as output */
  _WRITE;
}

void toggleEnable(){
    _EN_LOW;                      							/* continue reading data from lcd */
    WAIT1_Waitus( 1 );
    _EN_HIGH;
    WAIT1_Waitus( 1 );
    _EN_LOW;                      							/* continue reading data from lcd */
    WAIT1_Waitus( 100 );
}


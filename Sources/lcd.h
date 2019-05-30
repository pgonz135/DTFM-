/*
 * lcd.h
 *
 *  Created on: May 23, 2019
 *      Author: pgonzalez
 */

#ifndef LCD_H_
#define LCD_H_

#define CLEAR_DISPLAY			 0x01	/* Clear display */
#define CURSOR_SECOND_LINE		 0xC0	/* Moves cursor to second line */
#define SET_8_BIT				 0x38	/* Sets to 8-bit operation and selects 2-line display and 5 × 8 dot character font */
#define ON_DISPLAY_CURSOR		 0x0E	/* Turns on display and cursor. All display is in space mode because of initialization. */
#define ENTRY_MODE_SET			 0x06	/* Sets mode to increment the address by one and to shift the cursor to the right at the time of write to the DD/CGRAM. Display is not shifted. */
#define RETURN_HOME				 0x02   /* Returns both display and cursor to the original position (address 0). */
#define LCD_ROW_CHARS		 	 0x10	/* Number of characters that fit into LCD row */

void printLCD( char display[]  );
void initLCD( void );
void toggleEnable();

#endif /* LCD_H_ */

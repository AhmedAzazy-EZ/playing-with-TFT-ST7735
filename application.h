/*
 * application.h
 *
 * Created: 01-Jul-21
 *  Author: Ahmed Azazy
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

#include <avr/io.h>

#define LCD_Dir  DDRF			/* Define LCD data port direction */
#define LCD_Port PORTF			/* Define LCD data port */
#define RS PF0				/* Define Register Select pin */
#define EN PF1 				/* Define Enable signal pin */

/*************************************************
 *			Function Prototypes
 *************************************************/

void LCD_Command( unsigned char cmnd );

void LCD_Char( unsigned char data );

void LCD_Init (void);

void LCD_String (char *str);

void LCD_String_xy (char row, char pos, char *str);

void LCD_Clear(void );

void LCD_DisplayBinary(uint8_t data);

#endif /* APPLICATION_H_ */
/*
 * SD Drivers.c
 *
 * Created: 22-Jul-21
 * Author : Ahmed Azazy
 */ 

#include <avr/io.h>

#include "application.h"
#include "SPI.h"
#include "SD.h"
#include "st7735r.h"
#include "graphic.h"
#define F_CPU 8000000UL
#include <util/delay.h>

SPI_t spi;
uint8_t SD_Response;

memory_t SD;
int main(void)
{
		SD_DDR |= (1<<SD_CS);
		DDRB |= ((1<<MOSI) | (1<<SCK) | (1<<CS));
		ST7735_DDR |= ((1<<ST_DC)|(1<<ST_CS)|(1<<ST_RES));
		ST7735_PORT|=(1<<ST_RES);
		//ST7735_PORT |=(1<<ST_CS);
		SD_PORT |=(1<<SD_CS);
		
		
		spi.SPI_Interrupt = DISABLE;
		spi.SPI_Enable = ENABLE;
		spi.dataOrder = MSB_FIRST;
		spi.SPI_Mode = SPI_MASTER;
		spi.clockPolarity = RISING_LEADING;
		spi.clockPhase = SAMPLE_ON_LEADING;
		spi.clockRate = SPI_2_PRESCALE;
		
		
		/*************SD Init**********************/
		
		SD.numOfObjects = 0xFF;
		SD.toWriteAddress = 0xa00;
		
		/******************************************/
		
		LCD_Init();
		SPI_Init(&spi);
		
		SD_setSPI_Mode();
		
		ST7735_Init();	
		ST7735_Rectangle(0,0,131,165,8025);
		
		drawCircle(&SD , "CIR1" , 65 , 65 , 60 , 564316);
		drawCircle(&SD , "CIR2" , 22 , 22 , 15 , 564316);	
		drawCircle(&SD , "CIR4" , 50 , 50 , 15 , 564316);
		drawRectangle(&SD,"SQ1",88 , 65 , 20 , 20 , 5643165);
		drawLine(&SD , "LN1" , 25 , 25 , 30 , 90 , 25644535);	
		
		//moveShape(&SD , 10 , 20 , "CIR1");
		for(uint16_t i = 0 ; i < 590 ; i++)
			{
				objBuffer[i][0] = 0;
				objBuffer[i][1] = 0;
			}
		_delay_ms(1000);
		ST7735_Rectangle(0,0,131,165,8025);
		load_shape(&SD , "CIR2");
		load_shape(&SD , "CIR4");
		load_shape(&SD , "SQ1");
		load_shape(&SD , "LN1");
		load_shape(&SD , "CIR1");
    while (1) 
    {
		ST7735_Rectangle(0,0,131,165,8025);
		moveShape(&SD , 10 , 20 , "CIR2");
		moveShape(&SD , 10 , 20 , "CIR1");
		moveShape(&SD , 10 , 20 , "CIR4");
		moveShape(&SD , 10 , 20 , "LN1");
		moveShape(&SD , 10 , 20 , "SQ1");
		
		load_shape(&SD , "CIR2");
		load_shape(&SD , "CIR4");
		load_shape(&SD , "SQ1");
		load_shape(&SD , "LN1");
		load_shape(&SD , "CIR1");	
    }
}


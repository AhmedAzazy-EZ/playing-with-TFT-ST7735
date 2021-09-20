/*
 * st7735r.c
 *
 * Created: 24-Jul-21
 *  Author: Ahmed Azazy
 */ 

#include "st7735r.h"
#include "SPI.h"
#include <avr/io.h>
#define  F_CPU 8000000UL
#include <util/delay.h>
#include "SD.h"


//Checked
void ST7735_command(uint8_t command)
{
	ST7735_PORT &=~(1<<ST_CS);
	ST7735_PORT &=~(1<<ST_DC);
	SPI_Send_Receive(command);
	ST7735_PORT |=(1<<ST_CS);
}

//Checked
void ST7735_data(uint8_t data)
{
	ST7735_PORT &=~(1<<ST_CS);
	ST7735_PORT |=(1<<ST_DC);
	SPI_Send_Receive(data);
	ST7735_PORT |=(1<<ST_CS);
}


//Checked
void ST7735_SetArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
	ST7735_command(0x2A);
	ST7735_data(x1 >> 8);
	ST7735_data(x1 & 0xFF);
	ST7735_data(x2 >> 8);
	ST7735_data(x2 & 0xFF);

	ST7735_command(0x2B);
	ST7735_data(y1 >> 8);
	ST7735_data(y1 & 0xFF);
	ST7735_data(y2 >> 8);
	ST7735_data(y2 & 0xFF);
}


//Checked
void ST7735_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t colour)
{
	volatile uint16_t x, y;

	ST7735_SetArea(x1,y1,x2,y2);
	ST7735_command(0x2C);


	ST7735_PORT |= (1<<ST_DC);
	ST7735_PORT &=~(1<<ST_CS);
	//setRS(1);
	//setCS(0);

	for (x=x1; x<x2; x++)
	for (y=y1; y<y2; y++)
	{
		SPI_Send_Receive(colour >> 16);
		SPI_Send_Receive(colour>>8);
		SPI_Send_Receive(colour & 0xFF);
	}

	ST7735_PORT |=(1<<ST_CS);
	//setCS(1);
}


//Checked
void ST7735_Init(void)
{
	
	ST7735_PORT &=~(1<<ST_RES);
	_delay_ms(500);
	ST7735_PORT |=(1<<ST_RES);
	_delay_ms(500);
	
	ST7735_command(0x11);//Sleep out
	_delay_ms(120);
	//ST7735R Frame Rate
	ST7735_command(0xB1);
	ST7735_data(0x01);
	ST7735_data(0x2C);
	ST7735_data(0x2D);
	ST7735_command(0xB2);
	ST7735_data(0x01);
	ST7735_data(0x2C);
	ST7735_data(0x2D);
	ST7735_command(0xB3);
	ST7735_data(0x01);
	ST7735_data(0x2C);
	ST7735_data(0x2D);
	ST7735_data(0x01);
	ST7735_data(0x2C);
	ST7735_data(0x2D);
	//------------------------------------End ST7735R Frame Rate-----------------------------------------//
	ST7735_command(0xB4);//Column inversion
	ST7735_data(0x07);
	//------------------------------------ST7735R Power Sequence-----------------------------------------//
	ST7735_command(0xC0);
	ST7735_data(0xA2);
	ST7735_data(0x02);
	ST7735_data(0x84);
	ST7735_command(0xC1);
	ST7735_data(0xC5);
	ST7735_command(0xC2);
	ST7735_data(0x0A);
	ST7735_data(0x00);
	ST7735_command(0xC3);
	ST7735_data(0x8A);
	ST7735_data(0x2A);
	ST7735_command(0xC4);
	ST7735_data(0x8A);
	ST7735_data(0xEE);
	//---------------------------------End ST7735R Power Sequence-------------------------------------//
	ST7735_command(0xC5);//VCOM
	ST7735_data(0x0E);
	ST7735_command(0x36);//MX, MY, RGB mode
	ST7735_data(0xC8);
	//------------------------------------ST7735R Gamma Sequence-----------------------------------------//
	ST7735_command(0xe0);
	ST7735_data(0x02);
	ST7735_data(0x1c);
	ST7735_data(0x07);
	ST7735_data(0x12);
	ST7735_data(0x37);
	ST7735_data(0x32);
	ST7735_data(0x29);
	ST7735_data(0x2d);
	ST7735_data(0x29);
	ST7735_data(0x25);
	ST7735_data(0x2b);
	ST7735_data(0x39);
	ST7735_data(0x00);
	ST7735_data(0x01);
	ST7735_data(0x03);
	ST7735_data(0x10);
	ST7735_command(0xe1);
	ST7735_data(0x03);
	ST7735_data(0x1d);
	ST7735_data(0x07);
	ST7735_data(0x06);
	ST7735_data(0x2e);
	ST7735_data(0x2c);
	ST7735_data(0x29);
	ST7735_data(0x2d);
	ST7735_data(0x2e);
	ST7735_data(0x2e);
	ST7735_data(0x37);
	ST7735_data(0x3f);
	ST7735_data(0x00);
	ST7735_data(0x00);
	ST7735_data(0x02);
	ST7735_data(0x10);
	ST7735_command(0x2A);
	ST7735_data(0x00);
	ST7735_data(0x02);
	ST7735_data(0x00);
	ST7735_data(0x81);

	ST7735_command(0x2B);
	ST7735_data(0x00);
	ST7735_data(0x01);
	ST7735_data(0x00);
	ST7735_data(0xA0);
	//------------------------------------End ST7735R Gamma Sequence-----------------------------------------//

	ST7735_command(0x3A);
	ST7735_data(0x05);
	ST7735_command(0x3A);//65k mode
	ST7735_data(0x06);
	ST7735_command(0x2C);//Display on
	ST7735_Rectangle(0,0,131,165,8025);
	ST7735_command(0x29);//Display on
}



void ST7735_PutPixel(uint16_t x,uint16_t y,uint32_t colour)
{
	ST7735_SetArea(x,y ,x+1 , y + 1);
	ST7735_command(0x2C);
	
	
	ST7735_PORT |= (1<<ST_DC);
	ST7735_PORT &=~(1<<ST_CS);
	SPI_Send_Receive(colour>>16);
	SPI_Send_Receive(colour >> 8);
	SPI_Send_Receive(colour & 0xFF);
	ST7735_PORT |=(1<<ST_CS);
}


void ST7735_SD_DrawPic(uint32_t address , uint8_t * buffer)
{
	
	volatile int8_t loop = 0 ;
	uint16_t j ;
	SD_setBlockLength(512);
	ST7735_SetArea(0,0,131,165);
	ST7735_command(0x2C);
	
	ST7735_PORT |= (1<<ST_DC);
	
	for(loop = 0; loop < 83 ; loop++ )
	{
		SD_readBlock(address , (uint32_t) 512, buffer);
		address += 512;
		ST7735_PORT &=~(1<<ST_CS);
		for(j = 0 ; j < 512 ; j++)
		{
			SPI_Send_Receive(buffer[j]);
		}
		ST7735_PORT |= (1<<ST_CS);
	}
}
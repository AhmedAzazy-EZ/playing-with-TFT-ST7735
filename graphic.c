/*
 * graphic.c
 *
 * Created: 09-Aug-21 
 *  Author: PC
 */ 


#include "graphic.h"
#include "st7735r.h"
#include "SD.h"
#include <math.h>
#include <string.h>
#include "application.h"

uint8_t objBuffer[590][2];


void drawCircle(memory_t * SD , char *name , uint16_t center_x , uint16_t center_y , uint16_t radius , uint32_t color)
{
	
	strcpy(SD->obj_array[++SD->numOfObjects].name , name);
	SD->obj_array[SD->numOfObjects].length = 360;
	SD->obj_array[SD->numOfObjects].startAddress = SD->toWriteAddress;
	SD->toWriteAddress = SD->toWriteAddress + 720;
	SD->obj_array[SD->numOfObjects].color = color;
	SD->obj_array[SD->numOfObjects].status = OCCUPIED;
	
	volatile uint32_t startAddress = SD->obj_array[SD->numOfObjects].startAddress;
	volatile uint16_t loop = 0 , x_point , y_point;
	for( ; loop < 360 ; loop++)
	{
		x_point = center_x + radius* sin(loop) ;
		y_point = center_y + radius * cos(loop) ;
		
		objBuffer[loop][X_INDEX] = x_point;
		objBuffer[loop][Y_INDEX] = y_point;
		ST7735_PutPixel(x_point ,y_point , color) ;
	}
	SD_setBlockLength(360);
	SD_writeBlock(startAddress , 360 , (uint8_t *)((uint16_t ) objBuffer));
	SD_writeBlock((startAddress+360) , 360 , (uint8_t *)((uint16_t )objBuffer + 360) );
}


void drawRectangle(memory_t * SD , char *name , uint16_t center_x , uint16_t center_y , uint16_t width , uint16_t length , uint32_t color)
{
	
	strcpy(SD->obj_array[++SD->numOfObjects].name , name);
	SD->obj_array[SD->numOfObjects].startAddress = SD->toWriteAddress;
	SD->obj_array[SD->numOfObjects].length = (width + length)*2;
	SD->toWriteAddress = SD->toWriteAddress + (SD->obj_array[SD->numOfObjects].length *2);
	SD->obj_array[SD->numOfObjects].color = color;
	SD->obj_array[SD->numOfObjects].status = OCCUPIED;
	
	volatile uint16_t loop = 0 , x_point , y_point;
	volatile uint32_t startAddress = SD->obj_array[SD->numOfObjects].startAddress;
	
	for( ; loop < width/2 ; loop++)
		{
			x_point = center_x + (length/2);
			y_point = center_y + loop;
			objBuffer[loop*2][X_INDEX] = x_point;
			objBuffer[loop*2][Y_INDEX] = y_point;
			ST7735_PutPixel(x_point ,y_point , color) ;
			
			
			y_point = center_y - loop;
			objBuffer[loop*2+1][X_INDEX] = x_point;
			objBuffer[loop*2+1][Y_INDEX] = y_point;
			ST7735_PutPixel(x_point ,y_point , color) ;
		}
		SD_setBlockLength(width*2);
		SD_writeBlock(startAddress , width*2 , (uint8_t *)objBuffer);
		
		for(loop = 0 ; loop < (width/2) ; loop++)
		{
			x_point = center_x - (length/2);
			y_point = center_y + loop;
			objBuffer[loop*2][X_INDEX] = x_point;
			objBuffer[loop*2][Y_INDEX] = y_point;
			ST7735_PutPixel(x_point ,y_point , color) ;
			y_point = center_y - loop;
			objBuffer[loop*2+1][X_INDEX] = x_point;
			objBuffer[loop*2+1][Y_INDEX] = y_point;			
			ST7735_PutPixel(x_point ,y_point , color) ;
		}
		SD_setBlockLength(width*2);
		SD_writeBlock(startAddress+(width*2) , width*2 , (uint8_t *)objBuffer);
		
				
	for(loop = 0 ; loop < length/2 ; loop++)
	{
		y_point = center_y + (width/2);
		x_point = center_x + loop;
		objBuffer[loop*2][X_INDEX] = x_point;
		objBuffer[loop*2][Y_INDEX] = y_point;
		ST7735_PutPixel(x_point ,y_point , color) ;
		x_point = center_x - loop;
		objBuffer[loop*2+1][X_INDEX] = x_point;
		objBuffer[loop*2+1][Y_INDEX] = y_point;
		ST7735_PutPixel(x_point ,y_point , color) ;
	}
	SD_setBlockLength(length*2);
	SD_writeBlock(startAddress+(4*width) , length*2 , (uint8_t *)objBuffer);
	
	for(loop = 0 ; loop < (length/2) ; loop++)
	{
		y_point = center_y - (width/2);
		x_point = center_x + loop;
		objBuffer[loop*2][X_INDEX] = x_point;
		objBuffer[loop*2][Y_INDEX] = y_point;
		ST7735_PutPixel(x_point ,y_point , color) ;
		x_point = center_x - loop;
		objBuffer[loop*2+1][X_INDEX] = x_point;
		objBuffer[loop*2+1][Y_INDEX] = y_point;
		ST7735_PutPixel(x_point ,y_point , color) ;		
	}
	SD_setBlockLength(length*2);
	SD_writeBlock(startAddress+(4*width)+(2*length) , length*2 , (uint8_t *)objBuffer);
}


void drawLine(memory_t * SD , char *name ,uint16_t start_x , uint16_t start_y , uint16_t length , uint16_t angle ,uint32_t color)
{

	strcpy(SD->obj_array[++SD->numOfObjects].name , name);
	SD->obj_array[SD->numOfObjects].startAddress = SD->toWriteAddress;
	SD->obj_array[SD->numOfObjects].length = length;
	SD->toWriteAddress = SD->toWriteAddress + (SD->obj_array[SD->numOfObjects].length *2);
	SD->obj_array[SD->numOfObjects].color = color;
	SD->obj_array[SD->numOfObjects].status = OCCUPIED;
	
	volatile uint32_t startAddress = SD->obj_array[SD->numOfObjects].startAddress;
	volatile uint16_t loop = 0 , x_point , y_point ;
	
	for(; loop < length ; loop++)
	{
		x_point = start_x + (loop* cos(angle));
		y_point = start_y + (loop * sin(angle));
		objBuffer[loop][X_INDEX] = x_point;
		objBuffer[loop][Y_INDEX] = y_point;
		ST7735_PutPixel(x_point , y_point , color);
	}
	SD_setBlockLength(length*2);
	SD_writeBlock(startAddress , length*2 , (uint8_t *)objBuffer);
}

void load_shape(memory_t * SD , char * name)
{
	for(int i = 0 ; i < MAX_OBJECTS ; i++)
		{
			if(!strcmp(SD->obj_array[i].name , name))
				{
					//uint16_t length = SD->obj_array[i].length ;
					volatile uint32_t startAddress = SD->obj_array[i].startAddress;
					volatile uint32_t length = SD->obj_array[i].length * 2;
					volatile uint32_t color = SD->obj_array[i].color;
					while(length > 512)
					{
						
					SD_setBlockLength(512);	
					SD_readBlock(startAddress , length, (uint8_t *)objBuffer);
					startAddress +=512;
					length-=512;
					drawFromBuffer((uint8_t *)objBuffer , 512 , color);
					}
					if(length > 0)
					{
						SD_setBlockLength(length);
						SD_readBlock(startAddress , length , (uint8_t *)objBuffer);
						drawFromBuffer((uint8_t *)objBuffer , length , color);		
					}
					break;
				}
		}
}


void drawFromBuffer(uint8_t * buffer , uint16_t length , uint32_t color)
{
	for(volatile uint16_t loop = 0 ; loop < length/2 ; loop++)
		{
			ST7735_PutPixel(buffer[loop*2] , buffer[(loop*2)+1] , color);
		}
}


void moveShape(memory_t * SD , uint8_t x_displacement , uint8_t y_displacement , char * name)
{
	for(uint8_t i =0 ; i < MAX_OBJECTS ; i++)
		{
			if(!strcmp(SD->obj_array[i].name , name))
				{
					volatile uint32_t startAddress = SD->obj_array[i].startAddress;
					volatile uint16_t length = SD->obj_array[i].length *2;
					volatile uint16_t bufferAddress = (uint16_t)objBuffer;
					while(length > 512)
						{
							SD_setBlockLength(512);
							SD_readBlock(startAddress , 512 ,(uint8_t *) bufferAddress);
							length-=512 ;
							startAddress+=512;
							bufferAddress+=512;
						}
						
						if(length > 0)
							{
								SD_setBlockLength(length);
								SD_readBlock(startAddress , length , (uint8_t *)bufferAddress);
							}
							
					
					length = SD->obj_array[i].length *2;
					startAddress = SD->obj_array[i].startAddress;
					bufferAddress = (uint16_t)objBuffer;
					for(volatile uint16_t loop = 0 ; loop < length; loop++)
						{
							if(loop & 1)
							{
								*((uint8_t *)bufferAddress + loop)+= y_displacement;
								if(*((uint8_t *)bufferAddress + loop) > 161)
									{
										*((uint8_t *)bufferAddress + loop) -= 161;
									}
							}
							
							
							else
							{
								*((uint8_t *)bufferAddress + loop)+= x_displacement;
								if(*((uint8_t *)bufferAddress + loop) > 131)
									*((uint8_t *)bufferAddress + loop) -= 131;
							}
							
						}

					
					while(length > 512)
					{
						SD_setBlockLength(512);
						SD_writeBlock(startAddress , 512 , (uint8_t *)bufferAddress);
						length-=512;
						startAddress+=512;
						bufferAddress+=512;
					}
					
					if(length > 0)
					{
						SD_setBlockLength(length);
						SD_writeBlock(startAddress , length , (uint8_t *)bufferAddress);						
					}
					break;
				}
		}
}
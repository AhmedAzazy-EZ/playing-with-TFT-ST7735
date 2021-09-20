/*
 * graphic.h
 *
 * Created: 09-Aug-21
 *  Author: PC
 */ 


#ifndef GRAPHIC_H_
#define GRAPHIC_H_

#include <stdint.h>

extern uint8_t objBuffer[590][2];


#define MAX_OBJECTS 10
#define X_INDEX 0
#define Y_INDEX 1


//void drawCircle(uint16_t center_x , uint16_t center_y , uint16_t radius , uint32_t color);
//void drawRectangle(uint16_t center_x , uint16_t center_y , uint16_t width , uint16_t length , uint32_t color);
//void drawLine(uint16_t start_x , uint16_t start_y , uint16_t length , uint16_t angle ,uint32_t color);


typedef enum object_status
{
	FREE = 0 , 
	OCCUPIED = 1	
}object_status_t;

typedef struct obj
{
	char name[5];
	uint16_t length;
	uint32_t startAddress;
	uint32_t color;
	object_status_t status;
}obj_t;

typedef struct memory
{
	uint8_t numOfObjects;
	obj_t obj_array[MAX_OBJECTS];
	uint32_t toWriteAddress;
}memory_t;

void drawLine(memory_t * SD , char *name ,uint16_t start_x , uint16_t start_y , uint16_t length , uint16_t angle ,uint32_t color);
void drawRectangle(memory_t * SD , char *name , uint16_t center_x , uint16_t center_y , uint16_t width , uint16_t length , uint32_t color);
void drawCircle(memory_t * SD , char *name , uint16_t center_x , uint16_t center_y , uint16_t radius , uint32_t color);
void load_shape(memory_t * SD , char * name);
void moveShape(memory_t * SD , uint8_t x_displacement , uint8_t y_displacement , char * name);


void drawFromBuffer(uint8_t * buffer , uint16_t length , uint32_t color);

#endif /* GRAPHIC_H_ */
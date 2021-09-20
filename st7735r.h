/*
 * st7735r.h
 *
 * Created: 24-Jul-21
 *  Author: Ahmed Azazy
 */ 


#ifndef ST7735R_H_
#define ST7735R_H_

#include <stdint.h>

#define ST_DC (1)
#define ST_CS (2)
#define ST_RES (3)

#define ST7735_DDR DDRC
#define ST7735_PORT PORTC


void ST7735_data(uint8_t data);
void ST7735_command(uint8_t command);

void ST7735_Init(void );
void ST7735_Rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint32_t colour);
void ST7735_SetArea(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void ST7735_PutPixel(uint16_t x,uint16_t y,uint32_t colour);

void ST7735_SD_DrawPic(uint32_t address , uint8_t * buffer);
#endif /* ST7735R_H_ */
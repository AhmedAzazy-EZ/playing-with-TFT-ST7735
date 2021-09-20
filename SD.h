/*
 * SD.h
 *
 * Created: 22-Jul-21 
 *  Author: Ahmed Azazy
 */ 


#ifndef SD_H_
#define SD_H_
#include <stdint.h>

#define SD_PORT PORTC
#define SD_DDR DDRC
#define SD_CS (0)

uint8_t SD_setSPI_Mode(void );

uint8_t SD_sendCommand(uint8_t cmd , uint32_t arg);

uint8_t SD_setBlockLength(uint32_t );

uint8_t SD_readBlock(uint32_t address , uint32_t blockLength , uint8_t * buffer);

uint8_t SD_writeBlock(uint32_t address , uint32_t blockLength , uint8_t * buffer);


#endif /* SD_H_ */
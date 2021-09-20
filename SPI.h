/*
 * SPI.h
 *
 * Created: 19-Jul-21
 *  Author: Ahmed Azazy
 */ 


#ifndef SPI_H_
#define SPI_H_

#include <stdint.h>


#define SPI_PORT PORTB
#define SPI_DRR DDRB
#define CS (0)
#define MOSI (2)
#define MISO (3)
#define SCK (1)


typedef enum generic
{
	DISABLE , 
	ENABLE	
}generic_t;


typedef enum DataOrder 
{
	MSB_FIRST ,
	LSB_FIRST
}dataOrder_t;

typedef enum SPI_MODE
{
	SPI_SLAVE,
	SPI_MASTER	
}SPI_Mode_t;

typedef enum Clock_Polarity
{
	RISING_LEADING , 
	FALLING_LEADING	
}clockPolarity_t;

typedef enum Clock_Phase
{
	SAMPLE_ON_LEADING ,
	SAMPLE_ON_TRAILING 	
}clockPhase_t;

typedef enum SPI_Clock_Rate
{
	SPI_4_PRESCALE ,
	SPI_16_PRESCALE ,
	SPI_64_PRESCALE , 
	SPI_128_PRESCALE , 
	SPI_2_PRESCALE , 
	SPI_8_PRESCALE , 
	SPI_32_PRESCALE , 
		
}SPI_ClockRate_t;

typedef struct SPI 
{
	generic_t SPI_Interrupt;
	generic_t SPI_Enable;
	dataOrder_t dataOrder;	
	SPI_Mode_t SPI_Mode;
	clockPolarity_t clockPolarity;
	clockPhase_t clockPhase;
	SPI_ClockRate_t clockRate;
}SPI_t;


uint8_t SPI_Send_Receive(uint8_t data);

void SPI_Init(SPI_t * );

#endif /* SPI_H_ */
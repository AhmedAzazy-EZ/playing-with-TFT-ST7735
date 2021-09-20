/*
 * SPI.c
 *
 * Created: 19-Jul-21
 *  Author: Ahmed Azazy
 */ 

#include "SPI.h"
#include <stdint.h>
#include <avr/io.h>

void SPI_Init(SPI_t * spi)
{
	SPCR |= (spi->SPI_Interrupt << SPIE);
	SPCR |=(spi->dataOrder << DORD);
	SPCR |= (spi->SPI_Mode << MSTR);
	SPCR |= (spi->clockPolarity << CPOL);
	SPCR |=	(spi->clockPhase << CPHA);
	SPCR |= ((spi->clockRate&3));
	
	SPSR |= (spi->clockRate&(1<<2)) >> 2; 
	
	
	SPCR |= (spi->SPI_Enable << SPE);		
}

uint8_t SPI_Send_Receive(uint8_t data)
{
	SPDR = data;
	while(!(SPSR & 1<< SPIF));
	return SPDR;
}



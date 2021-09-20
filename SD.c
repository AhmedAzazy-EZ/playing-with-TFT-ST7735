/*
 * SD.c
 *
 * Created: 22-Jul-21 
 *  Author: Ahmed Azazy
 */ 

#define F_CPU 8000000U
#include "SD.h"
#include "SPI.h"
#include "application.h"
#include <avr/io.h>

#include <util/delay.h>
uint8_t SD_setSPI_Mode(void )
{
	volatile uint8_t response = 0xFF ;
	volatile int32_t i = 0;
	SD_PORT |= (1<<SD_CS);
	
	for( ; i < 10 ; i++)
	{
		SPI_Send_Receive(0xFF);
	}
	
	i = 0;
	
	SD_PORT&=~(1<<SD_CS);
	
	SPI_Send_Receive(0x40);
	SPI_Send_Receive(0x00);
	SPI_Send_Receive(0x00);
	SPI_Send_Receive(0x00);
	SPI_Send_Receive(0x00);
	SPI_Send_Receive(0x95);
	
	//wait for response
	while((response = SPI_Send_Receive(0xFF)) == 0xFF && i++ < 40000);
	return response;	
}

uint8_t SD_sendCommand(uint8_t cmd , uint32_t arg)
{
	volatile uint32_t retry = 0;
	volatile uint8_t response = 0xFF;
	
	SD_PORT&=~(1<<SD_CS);
	SPI_Send_Receive(cmd|0x40);
	SPI_Send_Receive(arg>>24);
	SPI_Send_Receive(arg>>16);
	SPI_Send_Receive(arg>>8);
	SPI_Send_Receive(arg);
	//check Redundency
	SPI_Send_Receive(0x95);
	while(response == 0xFF  && retry++ < 40000)
	{
		response =  SPI_Send_Receive(0xFF);
	}
	
	SD_PORT|=(1<<SD_CS);
	return response;		
}


uint8_t SD_setBlockLength(uint32_t blockLength)
{
	if(blockLength > (uint32_t )512)
		blockLength = 512;
		
	return SD_sendCommand((uint8_t )16 , blockLength);
}

uint8_t SD_readBlock(uint32_t address , uint32_t blockLength , uint8_t * buffer)
	{
			volatile uint8_t SD_Response = 0xFF;
			volatile uint32_t retry = 0;
			SD_PORT&=~(1<<SD_CS);
			//Multiple Block
			SPI_Send_Receive(17|0x40);
			SPI_Send_Receive(address>>24);
			SPI_Send_Receive(address>>16);
			SPI_Send_Receive(address>>8);
			SPI_Send_Receive(address);
			//check Redundency
			SPI_Send_Receive(0x95);
			
			while(SD_Response == 0xFF  && retry++ < 40000)
			{
				SD_Response =  SPI_Send_Receive(0xFF);
			}
		
		if(SD_Response != 0x00)
			return SD_Response;
		
		if(blockLength > (uint32_t )512)
			blockLength = 512;
		
		//wait for start token
		while((SD_Response = SPI_Send_Receive(0xFF)) != 0xFE);
		
		for(retry=0; retry < blockLength ; retry++)
			{
				buffer[retry]=SPI_Send_Receive(0xFF);
			}
			
				//Two additional SPI transfer for CRC , even if ignored
		SPI_Send_Receive(0xFF);
		SPI_Send_Receive(0xFF);
		
		SD_PORT|=(1<<SD_CS);
		return 0x00;		
	}
	
	
uint8_t SD_writeBlock(uint32_t address , uint32_t blockLength , uint8_t * buffer)
{
			volatile uint8_t SD_Response = 0xFF;
			volatile uint32_t retry = 0;
			SD_PORT&=~(1<<SD_CS);
			SPI_Send_Receive(24|0x40);
			SPI_Send_Receive(address>>24);
			SPI_Send_Receive(address>>16);
			SPI_Send_Receive(address>>8);
			SPI_Send_Receive(address);
			//check Redundency
			SPI_Send_Receive(0x95);
			while(SD_Response == 0xFF  && retry++ < 40000)
			{
				SD_Response =  SPI_Send_Receive(0xFF);
			}
			
	if(SD_Response != 0x00)
		return SD_Response;

		if(blockLength > (uint32_t )512)
		blockLength = 512;
		
		
		SPI_Send_Receive(0xFE);
		
		for(retry = 0; retry < blockLength ; retry++)
			{
				SPI_Send_Receive(buffer[retry]);
			}	
		//Two additional SPI transfer to CRC
		SPI_Send_Receive(0xFF);
		SPI_Send_Receive(0xFF);
		SPI_Send_Receive(0xFF);	
		SPI_Send_Receive(0xFF);
		SPI_Send_Receive(0xFF);
		SD_PORT|=(1<<SD_CS);
		return 0x00;
}

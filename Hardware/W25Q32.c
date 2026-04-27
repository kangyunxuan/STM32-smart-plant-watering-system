#include "stm32f10x.h"                  // Device header
#include "SPI.h"
#include "W25Q32.h"
#include <stdlib.h>

void W25Q32_Busy(){
	SPI_Start();
	SPI_SwapByte_MODE0(W25Q32_READ_STATUS_REGISTER_1);
	while(SPI_SwapByte_MODE0(W25Q32_DUMMY_BYTE) & 0x01){
	// the flash is busy
	// busy waiting
	}
	//BUSY FLAG WILL BE CLEAR AUTOMATICALLY WHEN THE OPERATION END
	SPI_Stop();
}

void W25Q32_WriteEnable(void){
	SPI_Start();
	SPI_SwapByte_MODE0(W25Q32_WRITE_ENABLE);
	SPI_Stop();
}

void W25Q32_ReadID(uint8_t *MID, uint16_t *DID){
	SPI_Start();
	SPI_SwapByte_MODE0(W25Q32_JEDEC_ID);
	*MID = SPI_SwapByte_MODE0(W25Q32_DUMMY_BYTE);
	*DID = SPI_SwapByte_MODE0(W25Q32_DUMMY_BYTE); //HIGH 8 bits
	*DID <<=8;
	*DID |= SPI_SwapByte_MODE0(W25Q32_DUMMY_BYTE);
	SPI_Stop();
}

//Page Program allows from one byte to 256 bytes (a page) of data
void W25Q32_PageProgram(uint32_t Addr, uint8_t *BufferArray, uint32_t Count){
	if(BufferArray == NULL || Count == 0) return;

	W25Q32_Busy();
	W25Q32_WriteEnable();
	
	SPI_Start();
	SPI_SwapByte_MODE0(W25Q32_PAGE_PROGRAM);
	
	//address
	SPI_SwapByte_MODE0((Addr >> 16) & 0xFF);
	SPI_SwapByte_MODE0((Addr >> 8) & 0xFF);
	SPI_SwapByte_MODE0(Addr & 0xFF);
	
	//data
	for(uint32_t i=0; i<Count; i++){
		SPI_SwapByte_MODE0(BufferArray[i]);
	}	
	SPI_Stop();
	W25Q32_Busy();
}

void W25Q32_ReadData(uint32_t Addr, uint8_t *BufferArray, uint32_t Count){
	if(BufferArray ==NULL || Count == 0) return;
	W25Q32_Busy();
	SPI_Start();
	SPI_SwapByte_MODE0(W25Q32_READ_DATA);
	// read address: 24bits
	SPI_SwapByte_MODE0((Addr>>16) & 0xFF);
	SPI_SwapByte_MODE0((Addr>>8) & 0xFF);
	SPI_SwapByte_MODE0(Addr & 0xFF);

	// start recieve data
	for(uint32_t i=0; i<Count; i++){
		BufferArray[i] = SPI_SwapByte_MODE0(W25Q32_DUMMY_BYTE);
	}
	SPI_Stop();
}


	
	
void W25Q32_SectorErase(uint32_t Addr){
	W25Q32_Busy();
	W25Q32_WriteEnable();
	SPI_Start();
	SPI_SwapByte_MODE0(W25Q32_SECTOR_ERASE_4KB);
	SPI_SwapByte_MODE0((Addr >> 16) & 0xFF);
	SPI_SwapByte_MODE0((Addr >> 8) & 0xFF);
	SPI_SwapByte_MODE0(Addr & 0xFF);
	SPI_Stop();
	W25Q32_Busy(); //Wait erase end
}

//W25Q_ReadStatus();

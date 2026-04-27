#include "stm32f10x.h"                  // Device header

void SPI_W_SS(uint8_t BitVal){
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitVal);
}
void SPI_W_SCK(uint8_t BitVal){
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitVal);
}
void SPI_W_MOSI(uint8_t BitVal){
	GPIO_WriteBit(GPIOB, GPIO_Pin_1, (BitAction)BitVal);
}
uint8_t SPI_R_MISO(void){
	return GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0);
}
//Mode 0, CPOL = 0, CPHA = 0
void mySPI_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	//use PA4, 5, 6, 11
	// PA4: SS
	// PA5: SCK
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽輸出
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_4 | GPIO_Pin_5  ; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// PB1: MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽輸出
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_1; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// PB0: MISO, Master recieve data
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // 輸入上拉
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	// SPI Initial signal: no operation
	SPI_W_SS(1); //no slave select
	SPI_W_SCK(0);
}

void SPI_Start(void){
	SPI_W_SS(0);
}

void SPI_Stop(void){
	SPI_W_SS(1);
}

//sck 1=read, 0=write
//MSB first
uint8_t SPI_SwapByte_MODE0(uint8_t ByteSend){
	uint8_t ByteRecieve = 0x00;
	for(int i =0; i<8; i++){
		SPI_W_MOSI(ByteSend & (0x80 >> i));
		SPI_W_SCK(1);
		if(SPI_R_MISO() ==1){
			ByteRecieve |= (0x80 >>i);
		}
		SPI_W_SCK(0);
	}
	return ByteRecieve;
}
// mode 1
//sck 1=write, 0=read
//cpol = 0
//cpha = 1
uint8_t SPI_SwapByte_MODE1(uint8_t ByteSend){
	uint8_t ByteRecieve = 0x00;
	for(int i =0; i<8; i++){
		SPI_W_MOSI(ByteSend & (0x80 >>i));
		SPI_W_SCK(1);

		SPI_W_SCK(0);
		if(SPI_R_MISO() ==1){
			ByteRecieve |= (0x80 >>i);
		}
	}
	return ByteRecieve;
}



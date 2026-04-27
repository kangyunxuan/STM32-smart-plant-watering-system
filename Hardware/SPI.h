#ifndef __SPI_H
#define __SPI_H
void SPI_W_SS(uint8_t BitVal);
void SPI_W_SCK(uint8_t BitVal);
void SPI_W_MOSI(uint8_t BitVal);
uint8_t SPI_R_MISO(void);
void mySPI_Init(void);

void SPI_Start(void);
void SPI_Stop(void);

//sck 1=read, 0=write
//MSB first
uint8_t SPI_SwapByte_MODE0(uint8_t ByteSend);
// mode 1
//sck 1=write, 0=read
//cpol = 0
//cpha = 1
uint8_t SPI_SwapByte_MODE1(uint8_t ByteSend);



#endif

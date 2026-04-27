#ifndef __W25Q32_H
#define __W25Q32_H

#define W25Q32_DUMMY_BYTE 				0xFF

#define W25Q32_WRITE_ENABLE				0x06
#define W25Q32_JEDEC_ID					0x9F
#define W25Q32_PAGE_PROGRAM				0x02
#define W25Q32_SECTOR_ERASE_4KB 		0x20
#define W25Q32_BLOCK_ERASE_32KB 		0x52
#define W25Q32_BLOCK_ERASE_64KB 		0xD8
#define W25Q32_READ_DATA 				0x03
#define W25Q32_READ_STATUS_REGISTER_1 	0x05

void W25Q32_Busy();
void W25Q32_WriteEnable(void);
void W25Q32_ReadID(uint8_t *MID, uint16_t *DID);
//Page Program allows from one byte to 256 bytes (a page) of data
void W25Q32_PageProgram(uint32_t Addr, uint8_t *BufferArray, uint32_t Count);
void W25Q32_ReadData(uint32_t Addr, uint8_t *BufferArray, uint32_t Count);
void W25Q32_SectorErase(uint32_t Addr);

#endif


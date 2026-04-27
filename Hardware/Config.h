#ifndef __CONFIG_H
#define __CONFIG_H
#define CONFIG_FLASH_ADDR  0x000000 
#define CONFIG_MAGIC 		0xFAFA
typedef struct {
	uint32_t magic; //check whether the threshold is set, if not set, use default
	uint16_t soil_threshold;
	uint16_t rain_threshold;
} ConfigVal;
extern ConfigVal g_config;
void Config_WriteToW25Q32(void);
void Config_ReadFromW25Q32(void);
void Config_Update(uint16_t rain, uint16_t soil);
#endif

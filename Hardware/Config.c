#include "stm32f10x.h"                  // Device header
#include "Config.h"
#include "SPI.h"
#include "W25Q32.h"

void Config_ReadFromW25Q32(void){
	ConfigVal tmp;
	W25Q32_ReadData(CONFIG_FLASH_ADDR, (uint8_t *)&tmp, sizeof(tmp));
	if(tmp.magic ==CONFIG_MAGIC){ //有設定
		g_config = tmp;
	}
	else{ //DEFAULT SETTING
		g_config.magic = CONFIG_MAGIC;
		g_config.rain_threshold = 2000;
		g_config.soil_threshold = 3000;
		Config_WriteToW25Q32();
	}
}

void Config_WriteToW25Q32(void){
	W25Q32_SectorErase(CONFIG_FLASH_ADDR);
	W25Q32_PageProgram(CONFIG_FLASH_ADDR, (uint8_t *)&g_config, sizeof(g_config));
}

void Config_Update(uint16_t rain, uint16_t soil){
    g_config.rain_threshold = rain;
    g_config.soil_threshold = soil;

	Config_WriteToW25Q32();

}
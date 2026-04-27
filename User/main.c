#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "led.h"
#include "key.h"
#include "OLED.h"
#include "rain.h"
#include "SPI.h"
#include "W25Q32.h"
#include "Config.h"
#include "system.h"
#include "menu.h"
#include "encoder.h"

uint16_t Rain_Val;
uint8_t MID;
uint16_t DID;
ConfigVal g_config;
//if g_config
//ConfigVal g_config = {
//    .magic = 0xFAFA,
//    .soil_threshold = 0,
//    .rain_threshold = 0
//};
int main(void){
	LED_Init();
	OLED_Init();
	mySPI_Init();
	KeyInit();
	Encoder_Init();
	Rain_Init();

	Config_ReadFromW25Q32();
//	OLED_ShowString(1, 1, "MID:");
//	OLED_ShowString(2, 1, "DID:");
//	W25Q32_ReadID(&MID, &DID);
//		
//	OLED_ShowHexNum(1, 5, MID, 4);
//	OLED_ShowHexNum(2, 5, DID, 4);
	while(1){
		System_Update();

		Delay_ms(100);
	}
}

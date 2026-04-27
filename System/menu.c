#include "stm32f10x.h"                  // Device header
#include "menu.h"
#include "led.h"
#include "Config.h"
#include "OLED.h"
#include "rain.h"
#include "encoder.h"
#include "stdbool.h"

extern ADC_Val adc;
SystemState state = STATE_NORMAL; //revise
MenuItem currentItem = ITEM_RAIN;
extern ConfigVal g_config;
//encoder + button UI
//選單邏輯

//extern SystemState state;
//extern MenuItem currentItem;

void Show_Normal(void){
	OLED_ShowString(1,1, "            ");
	OLED_ShowString(2,1, "            ");
	uint16_t rain_val = adc.ch0;
	uint16_t soil_val = adc.ch1;
    OLED_ShowString(1,1,"Rain:");
    OLED_ShowNum(1,6,rain_val,4);

    OLED_ShowString(2,1,"Soil:");
    OLED_ShowNum(2,6,soil_val,4);
	//雨量:濕度高數值低，土壤:濕度高數值低，如果沒下雨且土壤乾澆水
	bool raining = (rain_val < g_config.rain_threshold);
	bool dry     = (soil_val > g_config.soil_threshold);
//	3955 >3000 :0
//	4000 >3000
	if(dry && !raining){
		LED_On(GPIO_Pin_13);   // 澆水
	}else{
		LED_Off(GPIO_Pin_13);  // 不澆水
	}
}
void Show_Menu(void){
    OLED_ShowString(1,1, currentItem == ITEM_RAIN ? ">Rain: " : " Rain:  ");
    OLED_ShowNum(1,7,g_config.rain_threshold ,4);

    OLED_ShowString(2,1, currentItem == ITEM_SOIL ? ">Soil: " : " Soil:  ");
    OLED_ShowNum(2,7, g_config.soil_threshold,4);
}
void Show_Edit(uint16_t value){
    OLED_ShowString(1,1,"Editing ");
	OLED_ShowString(1,9, currentItem == ITEM_SOIL ? "Soil" : "Rain");
	OLED_ShowString(2,1, "          ");
    OLED_ShowNum(2,1,value,4);
	//OLED_ShowNum(3,1,Encoder_Pressed(),4);

}
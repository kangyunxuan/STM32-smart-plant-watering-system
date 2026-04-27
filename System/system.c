#include "stm32f10x.h"                  // Device header
#include "menu.h"
#include "Config.h"
#include "key.h"
#include "encoder.h"
extern SystemState state;
extern MenuItem currentItem;
extern ConfigVal g_config;
void System_Update(void){
    static uint16_t editValue;
    int16_t encoder_cnt = Encoder_cnt();  ///get encoder value: -1, 0, 1
	KeyEvent key = Key_GetEvent();
    switch(state){

    // 🔹 正常顯示
    case STATE_NORMAL:
        Show_Normal();

        if(key ==KEY_OK){ //mid ley
            state = STATE_MENU;
        }
        break;

    // 🔹 選單
    case STATE_MENU:
		if(encoder_cnt != 0) currentItem ^= 1; 
        Show_Menu();
        if(key ==KEY_OK){ //mid ley
		    editValue =(currentItem == ITEM_RAIN)?g_config.rain_threshold: g_config.soil_threshold;
            state = STATE_EDIT;
		}
        if(key ==KEY_BACK){ //mid ley
            state = STATE_NORMAL;
        }
        break;

    // 🔹 編輯數值
    case STATE_EDIT:
        editValue += encoder_cnt * 10;  // 每格調整10
		if(editValue>4096){
			editValue = 4096;
		}
		if(editValue<0){
			editValue = 0;
		}
        Show_Edit(editValue);

        if(key ==KEY_OK){ //mid ley
            if(currentItem == ITEM_RAIN){
                Config_Update(editValue, g_config.soil_threshold);
            }else{
                Config_Update(g_config.rain_threshold, editValue);
            }

            state = STATE_NORMAL;
        }
	    if(key ==KEY_BACK){ //mid ley
            state = STATE_MENU;
        }
        break;
    }
}
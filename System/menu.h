#ifndef __MENU_H
#define __MENU_H

typedef enum {
    STATE_NORMAL,
    STATE_MENU,
    STATE_EDIT
} SystemState;

typedef enum {
    ITEM_RAIN,
    ITEM_SOIL
} MenuItem;
uint16_t ADC_ToPercent(uint16_t adc_val);
void Show_Normal(void);
void Show_Menu(void);
void Show_Edit(uint16_t value);
#endif



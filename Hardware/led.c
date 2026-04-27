#include "stm32f10x.h"                  // Device header

void LED_Init(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
}

void LED_On(uint16_t GPIO_Pin){
		GPIO_ResetBits(GPIOC, GPIO_Pin);
}
void LED_Off(uint16_t GPIO_Pin){
		GPIO_SetBits(GPIOC, GPIO_Pin);
}

void LED1_turn(void){ //翻轉
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_1) == 0){
		GPIO_SetBits(GPIOA, GPIO_Pin_1);
	}
	else{
		GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	}
}
void LED2_turn(void){
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_2) == 0){
		GPIO_SetBits(GPIOA, GPIO_Pin_2);
	}
	else{
		GPIO_ResetBits(GPIOA, GPIO_Pin_2);
	}
}

#ifndef __RAIN_H
#define __RAIN_H
void Rain_Init(void);
uint16_t Read_ADCVal(uint8_t channel);
typedef struct{
	uint16_t ch0; //rain
	uint16_t ch1; //soil
} ADC_Val;
extern ADC_Val adc;
#endif

#ifndef _ADC_H
#define _ADC_H
#include "stm32f4xx.h"
void Phtores_ADC_Init();
u16 get_adc_val();
unsigned short int getAdcAverage1(unsigned char ch,unsigned char times);
#endif
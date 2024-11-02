#ifndef _NVIC_H
#define _NVIC_H
#include "stm32f4xx.h"

void NVIC_Config();
void EXTI4_Config();
void EXTI9_5_Config();
void EXTI12_Config();
void delay_ms_1(int nms);
#endif
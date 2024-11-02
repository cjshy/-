#ifndef _BEEP_H
#define _BEEP_H
#include "stm32f4xx.h"
void Beep_Init();
void Beep_Run();
void Beep_Close();
void Beep_Runs();
void pwm_settone(uint16_t Period);
#endif
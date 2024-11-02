#ifndef _KEY_H
#define _KEY_H
#include "stm32f4xx.h"
void Key_Init();
void Delay_ms(uint32_t seconds);
void Key_read();
void key_Select();
void Set_Device(u8 humi,u8 temp,int *flage,int *mode_flage);
void Fan_Init();
void Fan_Run();
void Fan_Close();
void music_begin();
#endif
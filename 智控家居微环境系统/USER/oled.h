#ifndef _OLED_H
#define _OLED_H
#include "stm32f4xx.h"
int oled_test();
void OLed_ShowChina(uint8_t x,uint8_t y,uint8_t *buf);
void Oled_print(uint8_t x, uint8_t y,char *str);
void OLed_Fill(unsigned char bmp_data);
void WriteOLedData(uint8_t data);
void WriteOLedCmd(uint8_t cmd);
void Show_Welcome();
void Show_End();
void show_mode_1();
void show_mode_2();
#endif
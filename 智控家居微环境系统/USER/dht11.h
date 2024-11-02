#ifndef _DHT11_H
#define _DHT11_H
#include "stm32f4xx.h"
void Set_DHT11_Mode_IN(void);
void Set_DHT11_Mode_OUT(void);
int Start_ask(void);
u8 Read_Bit(void);
u8 Read_Byte(void);
int DHT11_WORK(u8 *humi,u8 *temp);
#endif
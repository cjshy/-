#ifndef _USART_H
#define _USART_H
#include <stdio.h>
void Usart_Config();
void my_printf(const char *str);
int fputc(int ch,FILE *fp);
#endif
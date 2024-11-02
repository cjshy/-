#ifndef _SYSTICK_H
#define _SYSTICK_H
void Systick_Init();
void my_delay_ms(unsigned int num);
void SysTick_Handler ();
void delay_ms_1(int nms);
void delay_us_1(int nus);
#endif
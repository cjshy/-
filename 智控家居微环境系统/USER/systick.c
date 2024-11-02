#include "stm32f4xx.h"
#include "main.h"
unsigned int Timedelay =0;
void Systick_Init()
{
	//����ʱ��ԴΪ168MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//SystemCoreClock/1000����1ms	
	if(SysTick_Config(SystemCoreClock/1000))
	{
		Beep_Run();
	}
}

void my_delay_ms(unsigned int num)
{
	Timedelay = num;
	while(Timedelay !=0);
}

void SysTick_Handler ()
{
	if(Timedelay!=0)
	{
		Timedelay--;
	}
}

void delay_ms_1(int nms)
{
	//1
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//21MHZ
	//2
	SysTick->CTRL &= ~(1<<0);//�رն�ʱ��
	SysTick->LOAD = nms*21000-1;//������װ��ֵ
	SysTick->VAL = 0;//��յ�ǰֵ
	SysTick->CTRL |=(1<<0);//������ʱ��
	while((SysTick->CTRL&0X00010000) == 0);
	SysTick->VAL =0;
	SysTick->CTRL = 0;
}

void delay_us_1(int nus)
{
	//ѡ��ʱ��Դ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//ѡ��21MHZʱ��Դ
	//
	SysTick->CTRL &= ~(1<<0);
	SysTick->LOAD = nus*21000/1000-1;
	SysTick->VAL =0;
	SysTick->CTRL |= (1<<0);
	while((SysTick->CTRL&0X00010000) == 0);
	SysTick->VAL =0;
	SysTick->CTRL = 0;
}
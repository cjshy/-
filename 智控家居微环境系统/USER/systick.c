#include "stm32f4xx.h"
#include "main.h"
unsigned int Timedelay =0;
void Systick_Init()
{
	//配置时钟源为168MHZ
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	//SystemCoreClock/1000就是1ms	
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
	SysTick->CTRL &= ~(1<<0);//关闭定时器
	SysTick->LOAD = nms*21000-1;//加载重装载值
	SysTick->VAL = 0;//清空当前值
	SysTick->CTRL |=(1<<0);//启动定时器
	while((SysTick->CTRL&0X00010000) == 0);
	SysTick->VAL =0;
	SysTick->CTRL = 0;
}

void delay_us_1(int nus)
{
	//选择时钟源
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);//选择21MHZ时钟源
	//
	SysTick->CTRL &= ~(1<<0);
	SysTick->LOAD = nus*21000/1000-1;
	SysTick->VAL =0;
	SysTick->CTRL |= (1<<0);
	while((SysTick->CTRL&0X00010000) == 0);
	SysTick->VAL =0;
	SysTick->CTRL = 0;
}
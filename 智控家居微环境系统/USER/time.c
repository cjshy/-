#include "stm32f4xx.h"
#include "main.h"

//基本定时器配置
void TIME6_Config()
{
	//打开基本定时器 TIME6位于APB1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	TIM_TimeBaseInitTypeDef TIM_Struct;
	//初始化定时器相关参数
	TIM_Struct.TIM_CounterMode = TIM_CounterMode_Up;//计算模式 向上计数
	//配置200ms
	TIM_Struct.TIM_Period = 5000-1;//计算周期 （计算的次数）
	TIM_Struct.TIM_Prescaler = 8400-1;//预分频道 （数值的快慢） 84M/8400 = 10000次 计数的一次时间是100us
	
	TIM_TimeBaseInit(TIM6,&TIM_Struct);
	//设置定时器的中断源 TIM_IT_Update:更新事件时发生中断
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	//使能定时器
	TIM_Cmd(TIM6,ENABLE);
}


//通用定时器配置
void TIME4_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM5,ENABLE);//打开ITM3,4,5的定时器
	
	TIM_TimeBaseInitTypeDef Time_Struct;
	Time_Struct.TIM_CounterMode = TIM_CounterMode_Up;//向上计数
	Time_Struct.TIM_Period = 10000-1; //计算周期 
	Time_Struct.TIM_Prescaler = 8400 -1;//预分 0.1ms
	TIM_TimeBaseInit(TIM4,&Time_Struct);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //设置定时器中断源
	TIM_Cmd(TIM4,ENABLE); //使能定时器
	/*
	Time_Struct.TIM_Period = 4000-1; //计算周期 
	Time_Struct.TIM_Prescaler = 8400 -1;//预分
	TIM_TimeBaseInit(TIM3,&Time_Struct);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //设置定时器中断源
	TIM_Cmd(TIM3,ENABLE); //使能定时器
	
	Time_Struct.TIM_Period = 5000-1; //计算周期 
	Time_Struct.TIM_Prescaler = 8400 -1;//预分
	TIM_TimeBaseInit(TIM5,&Time_Struct);
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //设置定时器中断源
	TIM_Cmd(TIM5,ENABLE); //使能定时器
	*/
}


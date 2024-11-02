#include "stm32f4xx.h"

void NVIC_Config()
{
	//NVIC结构体
		NVIC_InitTypeDef nvic_struct;
	//设置优先级分组
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//外部中断4 EXIT4 
		nvic_struct.NVIC_IRQChannel = EXTI4_IRQn ;//设置中断通道
		nvic_struct.NVIC_IRQChannelCmd = ENABLE;//使能
		nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;//抢占式优先级
		nvic_struct.NVIC_IRQChannelSubPriority = 1;//响应式优先级
		NVIC_Init(&nvic_struct);
	
		nvic_struct.NVIC_IRQChannel =  EXTI9_5_IRQn;
		nvic_struct.NVIC_IRQChannelCmd = ENABLE;
		nvic_struct.NVIC_IRQChannelPreemptionPriority =0;
		nvic_struct.NVIC_IRQChannelSubPriority =1;
		NVIC_Init(&nvic_struct);
	
		nvic_struct.NVIC_IRQChannel = EXTI15_10_IRQn;
		nvic_struct.NVIC_IRQChannelPreemptionPriority =0;
		nvic_struct.NVIC_IRQChannelSubPriority =1;
		NVIC_Init(&nvic_struct);
		
		nvic_struct.NVIC_IRQChannel = TIM6_DAC_IRQn;//定时器6中断通道
		nvic_struct.NVIC_IRQChannelCmd = ENABLE;
		nvic_struct.NVIC_IRQChannelPreemptionPriority = 2;
		nvic_struct.NVIC_IRQChannelSubPriority = 2;
		NVIC_Init(&nvic_struct);
		
		nvic_struct.NVIC_IRQChannel = TIM4_IRQn;
		nvic_struct.NVIC_IRQChannelCmd = ENABLE;
		nvic_struct.NVIC_IRQChannelPreemptionPriority =2;
		nvic_struct.NVIC_IRQChannelSubPriority =1;
		NVIC_Init(&nvic_struct);
		
		nvic_struct.NVIC_IRQChannel = TIM3_IRQn;
		NVIC_Init(&nvic_struct);
		
		nvic_struct.NVIC_IRQChannel = TIM5_IRQn;
		NVIC_Init(&nvic_struct);
		
		nvic_struct.NVIC_IRQChannel = USART1_IRQn;
		nvic_struct.NVIC_IRQChannelPreemptionPriority =0;
		nvic_struct.NVIC_IRQChannelSubPriority =1;
		NVIC_Init(&nvic_struct);
		
		nvic_struct.NVIC_IRQChannel = USART2_IRQn ;
		nvic_struct.NVIC_IRQChannelPreemptionPriority =0;
		nvic_struct.NVIC_IRQChannelSubPriority =2;
		NVIC_Init(&nvic_struct);
}

void EXTI4_Config()
{
	EXTI_InitTypeDef exti_struct;
	//外部中断时钟总线
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//中断线映射函数
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	//初始化
	exti_struct.EXTI_Line = EXTI_Line4;//4引脚
	exti_struct.EXTI_LineCmd = ENABLE;//开启中断
	exti_struct.EXTI_Mode = EXTI_Mode_Interrupt;//中断模式
	exti_struct.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	
	EXTI_Init(&exti_struct);
}

void EXTI9_5_Config()
{
	EXTI_InitTypeDef exti_struct;
	//外部中断时钟总线
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//中断线映射函数
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
	//初始化
	exti_struct.EXTI_Line = EXTI_Line5|EXTI_Line6;//引脚
	exti_struct.EXTI_LineCmd = ENABLE;//开启中断
	exti_struct.EXTI_Mode = EXTI_Mode_Interrupt;//中断模式
	exti_struct.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	
	EXTI_Init(&exti_struct);
}

void EXTI12_Config()
{
	EXTI_InitTypeDef exti_struct;
	//外部中断时钟总线
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//中断线映射函数
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
	//初始化
	exti_struct.EXTI_Line = EXTI_Line13;//引脚
	exti_struct.EXTI_LineCmd = ENABLE;//开启中断
	exti_struct.EXTI_Mode = EXTI_Mode_Interrupt;//中断模式
	exti_struct.EXTI_Trigger = EXTI_Trigger_Falling;//下降沿触发
	
	EXTI_Init(&exti_struct);                        
}
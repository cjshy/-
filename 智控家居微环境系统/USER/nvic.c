#include "stm32f4xx.h"

void NVIC_Config()
{
	//NVIC�ṹ��
		NVIC_InitTypeDef nvic_struct;
	//�������ȼ�����
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	//�ⲿ�ж�4 EXIT4 
		nvic_struct.NVIC_IRQChannel = EXTI4_IRQn ;//�����ж�ͨ��
		nvic_struct.NVIC_IRQChannelCmd = ENABLE;//ʹ��
		nvic_struct.NVIC_IRQChannelPreemptionPriority = 0;//��ռʽ���ȼ�
		nvic_struct.NVIC_IRQChannelSubPriority = 1;//��Ӧʽ���ȼ�
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
		
		nvic_struct.NVIC_IRQChannel = TIM6_DAC_IRQn;//��ʱ��6�ж�ͨ��
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
	//�ⲿ�ж�ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//�ж���ӳ�亯��
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource4);
	//��ʼ��
	exti_struct.EXTI_Line = EXTI_Line4;//4����
	exti_struct.EXTI_LineCmd = ENABLE;//�����ж�
	exti_struct.EXTI_Mode = EXTI_Mode_Interrupt;//�ж�ģʽ
	exti_struct.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	
	EXTI_Init(&exti_struct);
}

void EXTI9_5_Config()
{
	EXTI_InitTypeDef exti_struct;
	//�ⲿ�ж�ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//�ж���ӳ�亯��
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource5);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource6);
	//��ʼ��
	exti_struct.EXTI_Line = EXTI_Line5|EXTI_Line6;//����
	exti_struct.EXTI_LineCmd = ENABLE;//�����ж�
	exti_struct.EXTI_Mode = EXTI_Mode_Interrupt;//�ж�ģʽ
	exti_struct.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	
	EXTI_Init(&exti_struct);
}

void EXTI12_Config()
{
	EXTI_InitTypeDef exti_struct;
	//�ⲿ�ж�ʱ������
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
	//�ж���ӳ�亯��
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC,EXTI_PinSource13);
	//��ʼ��
	exti_struct.EXTI_Line = EXTI_Line13;//����
	exti_struct.EXTI_LineCmd = ENABLE;//�����ж�
	exti_struct.EXTI_Mode = EXTI_Mode_Interrupt;//�ж�ģʽ
	exti_struct.EXTI_Trigger = EXTI_Trigger_Falling;//�½��ش���
	
	EXTI_Init(&exti_struct);                        
}
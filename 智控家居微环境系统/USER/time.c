#include "stm32f4xx.h"
#include "main.h"

//������ʱ������
void TIME6_Config()
{
	//�򿪻�����ʱ�� TIME6λ��APB1
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	TIM_TimeBaseInitTypeDef TIM_Struct;
	//��ʼ����ʱ����ز���
	TIM_Struct.TIM_CounterMode = TIM_CounterMode_Up;//����ģʽ ���ϼ���
	//����200ms
	TIM_Struct.TIM_Period = 5000-1;//�������� ������Ĵ�����
	TIM_Struct.TIM_Prescaler = 8400-1;//Ԥ��Ƶ�� ����ֵ�Ŀ����� 84M/8400 = 10000�� ������һ��ʱ����100us
	
	TIM_TimeBaseInit(TIM6,&TIM_Struct);
	//���ö�ʱ�����ж�Դ TIM_IT_Update:�����¼�ʱ�����ж�
	TIM_ITConfig(TIM6,TIM_IT_Update,ENABLE);
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM6,ENABLE);
}


//ͨ�ö�ʱ������
void TIME4_Config()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4|RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM5,ENABLE);//��ITM3,4,5�Ķ�ʱ��
	
	TIM_TimeBaseInitTypeDef Time_Struct;
	Time_Struct.TIM_CounterMode = TIM_CounterMode_Up;//���ϼ���
	Time_Struct.TIM_Period = 10000-1; //�������� 
	Time_Struct.TIM_Prescaler = 8400 -1;//Ԥ�� 0.1ms
	TIM_TimeBaseInit(TIM4,&Time_Struct);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE); //���ö�ʱ���ж�Դ
	TIM_Cmd(TIM4,ENABLE); //ʹ�ܶ�ʱ��
	/*
	Time_Struct.TIM_Period = 4000-1; //�������� 
	Time_Struct.TIM_Prescaler = 8400 -1;//Ԥ��
	TIM_TimeBaseInit(TIM3,&Time_Struct);
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE); //���ö�ʱ���ж�Դ
	TIM_Cmd(TIM3,ENABLE); //ʹ�ܶ�ʱ��
	
	Time_Struct.TIM_Period = 5000-1; //�������� 
	Time_Struct.TIM_Prescaler = 8400 -1;//Ԥ��
	TIM_TimeBaseInit(TIM5,&Time_Struct);
	TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE); //���ö�ʱ���ж�Դ
	TIM_Cmd(TIM5,ENABLE); //ʹ�ܶ�ʱ��
	*/
}


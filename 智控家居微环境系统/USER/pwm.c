#include "stm32f4xx.h"
#include "stdio.h"
#include "delay.h"
void PWM_TIM2_CH3_BEEP()
{
	//1.��ʱ��2ʱ�ӳ�ʼ��ʹ�� 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//GPIOʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//GPIOB��10����Ա ���ö�ʱ��2
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2);
	//����ģʽ��GPIO_Mode_AF
	GPIO_InitTypeDef beep_pwm_struct;
	beep_pwm_struct.GPIO_Mode = GPIO_Mode_AF;//����ģʽ
	beep_pwm_struct.GPIO_OType = GPIO_OType_PP;
	beep_pwm_struct.GPIO_Pin = GPIO_Pin_10;
	beep_pwm_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&beep_pwm_struct);
	//��ʼ����ʱ��
	TIM_TimeBaseInitTypeDef tim2_struct;
	tim2_struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim2_struct.TIM_Prescaler = 8400-1;  //0.1ms
	tim2_struct.TIM_Period = 100;
	TIM_TimeBaseInit(TIM2,&tim2_struct);
	//��ʼ��ͨ��3
	TIM_OCInitTypeDef TIM_OCInit_Struct;
	TIM_OCInit_Struct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInit_Struct.TIM_OutputState = TIM_OutputState_Enable;//����ȽϼĴ���ʹ��
	TIM_OCInit_Struct.TIM_OCNPolarity = TIM_OCPolarity_High; //�������Ϊ�ߵ�ƽ
	TIM_OCInit_Struct.TIM_Pulse = 50; //�ȽϼĴ�����ֵ  ռ�ձ�
	TIM_OC3Init(TIM2,&TIM_OCInit_Struct);
	
	//��ʱ��2��ͨ�� 3�ıȽϲ���Ĵ���ʹ��
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	//�Զ�װ�ؼĴ���ʹ��
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	//ʹ��TIM2
	TIM_Cmd(TIM2,ENABLE);
}

// ��ʼ�� PWM ���
void PWM_TIM1_CH1N_LED1()
{
    // ���ö�ʱ�� 1 �� GPIOE ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    // ��λ��ʱ��
    TIM_DeInit(TIM1);

    // ���� GPIOE �ĵ� 8 ����Ϊ��ʱ�� 1 ͨ�� 1 �������
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_TIM1); 

    // GPIO ����
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8; 
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // ����ģʽ
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // �������
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // ����ٶ�
    GPIO_Init(GPIOE, &GPIO_InitStruct);

    // ��ʱ����ʼ��
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1; // �������� (10 ms)
    TIM_TimeBaseInitStruct.TIM_Prescaler = 8400 - 1; // Ԥ��Ƶ (1 MHz �ļ���Ƶ��)
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // ʱ�ӷָ�
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // ���ϼ���
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);

    // ��ʼ�� PWM ���ͨ��
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; // PWM ģʽ 1
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Disable; // ʹ�����
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low; // �������Ϊ�ͣ������� CH1N
    TIM_OCInitStruct.TIM_Pulse = 50; // ����ռ�ձ� (0-100)
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC1Init(TIM1, &TIM_OCInitStruct); 

    // ���ñȽϼĴ���Ԥװ��
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 

    // �����Զ����ؼĴ���
    TIM_ARRPreloadConfig(TIM1, ENABLE);

    // ������ʱ��
    TIM_Cmd(TIM1, ENABLE);
}


void PWM_TIM1_CH1_LED()
{
	//1.��ʱ��1ʱ�ӳ�ʼ��ʹ�� 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//GPIOʱ������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//������ʱ��
	TIM_DeInit(TIM1);
	//GPIOE��9����Ա ���ö�ʱ��2
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	//����ģʽ��GPIO_Mode_AF   LED2
	GPIO_InitTypeDef beep_pwm_struct;
	beep_pwm_struct.GPIO_Mode = GPIO_Mode_AF;//����ģʽ
	beep_pwm_struct.GPIO_OType = GPIO_OType_PP;
	beep_pwm_struct.GPIO_Pin = GPIO_Pin_9;
	beep_pwm_struct.GPIO_Speed = GPIO_Speed_50MHz;
	beep_pwm_struct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&beep_pwm_struct);
	//��ʼ����ʱ��
	TIM_TimeBaseInitTypeDef tim1_struct;
	tim1_struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim1_struct.TIM_Prescaler = 8400-1;  //0.1ms
	tim1_struct.TIM_Period = 100-1;
	tim1_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1,&tim1_struct);
	//��ʼ��ͨ��3
	TIM_OCInitTypeDef TIM_OCInit_Struct;
	TIM_OCInit_Struct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInit_Struct.TIM_OutputState = TIM_OutputState_Enable;//����ȽϼĴ���ʹ��
	TIM_OCInit_Struct.TIM_OCNPolarity = TIM_OCPolarity_Low; //�������Ϊ�͵�ƽ
	TIM_OCInit_Struct.TIM_Pulse = 100; //�ȽϼĴ�����ֵ  ռ�ձ�
	TIM_OC1Init(TIM1,&TIM_OCInit_Struct);
	
	//��ʱ��1��ͨ�� 1�ıȽϲ���Ĵ���ʹ��
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	//TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	//�Զ�װ�ؼĴ���ʹ��
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	//ʹ��TIM1
	TIM_Cmd(TIM1,ENABLE);
	TIM_SetCompare1(TIM1,0);
}


static u16 last_pwm_value = 0; // �ϴε�PWMֵ
static const float alpha = 0.3; // ƽ��ϵ����ֵԽС�仯Խƽ��

void Set_LedLight(u16 val)
{
    delay_ms(10);
    u16 pwm_value;

    if(val < 900)
    {
       // printf("���չ�ǿ\r\n");
        pwm_value = 0;
    }
    else if(val > 3500)
    {
        printf("���չ���\r\n");
        pwm_value = 100;
    }
    else
    {
        pwm_value = (val - 900) * 100 / (3500 - 900); // ����ӳ��
    }

    // ʹ�ü�Ȩƽ��ƽ�� PWM ֵ
    pwm_value = (u16)((1 - alpha) * last_pwm_value + alpha * pwm_value);
    
    TIM_SetCompare1(TIM1, pwm_value);
    last_pwm_value = pwm_value; // �����ϴε� PWM ֵ

    delay_ms(10);
}

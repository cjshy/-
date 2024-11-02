#include "stm32f4xx.h"
#include <stdio.h>
void Usart_Config()
{
	//����ʱ��ʹ�� USART1λ��APB1����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//GPIOʱ��ʹ�� PA9,PA10λ��AHB1����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//�ܽŸ���
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	//GPIO���� �Լ���ʼ��
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF;
	gpio_struct.GPIO_OType = GPIO_OType_PP;
	gpio_struct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	gpio_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_struct);
	//���ڵ������Լ���ʼ��
	USART_InitTypeDef usar_t1;
	usar_t1.USART_BaudRate = 115200;
	usar_t1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ����������
	usar_t1.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
	usar_t1.USART_Parity = USART_Parity_No;//��У��
	usar_t1.USART_StopBits = USART_StopBits_1;
	usar_t1.USART_WordLength = USART_WordLength_8b;//�����ֳ�Ϊ 8λ
	USART_Init(USART1,&usar_t1);
	//����ʹ��
	USART_Cmd(USART1,ENABLE);
	//���ڽ����ж�ʹ��
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

void my_printf(const char *str)
{
	int i;
	for(int i=0;*str;i++)
	{
		USART_SendData(USART1,*str);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//�ȴ����ݷ������
		str++;
	}
}

//�ض���
int fputc(int ch,FILE *fp)
{
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//�ȴ����ݷ���
}
#include "stm32f4xx.h"
#include <stdio.h>
void Usart_Config()
{
	//串口时钟使能 USART1位于APB1总线
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	//GPIO时钟使能 PA9,PA10位于AHB1总线
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	//管脚复用
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
	//GPIO配置 以及初始化
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF;
	gpio_struct.GPIO_OType = GPIO_OType_PP;
	gpio_struct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
	gpio_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_struct);
	//串口的配置以及初始化
	USART_InitTypeDef usar_t1;
	usar_t1.USART_BaudRate = 115200;
	usar_t1.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件控制流无
	usar_t1.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
	usar_t1.USART_Parity = USART_Parity_No;//无校验
	usar_t1.USART_StopBits = USART_StopBits_1;
	usar_t1.USART_WordLength = USART_WordLength_8b;//数据字长为 8位
	USART_Init(USART1,&usar_t1);
	//串口使能
	USART_Cmd(USART1,ENABLE);
	//串口接收中断使能
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
}

void my_printf(const char *str)
{
	int i;
	for(int i=0;*str;i++)
	{
		USART_SendData(USART1,*str);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//等待数据发送完成
		str++;
	}
}

//重定向
int fputc(int ch,FILE *fp)
{
	USART_SendData(USART1,ch);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);//等待数据发完
}
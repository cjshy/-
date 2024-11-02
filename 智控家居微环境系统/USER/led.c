#include "stm32f4xx.h"
#include "delay.h"
void Led_Init()
{
	//ʹ��ʱ�� led1 λ��PE8��GPIOE�˿� --PIN_8������  ����AHB1������
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);	
	//GPIO�ṹ�����ü���ʼ��
	GPIO_InitTypeDef gpio_struct;//GPIO�ṹ�����
	gpio_struct.GPIO_Mode=GPIO_Mode_OUT;//ģʽ�����ģʽ
	gpio_struct.GPIO_OType = GPIO_OType_PP;//������ͣ��������
	gpio_struct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;//ָ������
	gpio_struct.GPIO_Speed = GPIO_Speed_2MHz;//����
	GPIO_Init(GPIOE,&gpio_struct);//��ʼ��	
	GPIO_Write(GPIOE,0X0700);
}


void led_open()
{
	GPIO_Write(GPIOE,~0X0700);
}

void led_close()
{
	GPIO_Write(GPIOE,0X0700);
}

void led_run()//��ˮ��
{
	delay_init(168);
	while(1)
	{
		delay_ms(500);
		GPIO_Write(GPIOE,~0X0100);
		delay_ms(500);
		GPIO_Write(GPIOE,~0X0300);
		delay_ms(500);
		GPIO_Write(GPIOE,~0X0700);
		delay_ms(500);
		GPIO_Write(GPIOE,~0X0400);
		delay_ms(500);
		GPIO_Write(GPIOE,~0X0600);
		delay_ms(500);
		GPIO_Write(GPIOE,~0X0700);
	}

}

void Open_Ledn(unsigned int n)
{
	switch(n)
	{
		case 1:
			GPIO_Write(GPIOE,~0X0100);
			break;
		case 2:
			GPIO_Write(GPIOE,~0X0300);
			break;
		case 3:
			GPIO_Write(GPIOE,~0X0700);
			break;
		case 0:
			GPIO_Write(GPIOE,0X0700);
			break;
		default:
			break;
	}
}
#include "stm32f4xx.h"
#include "delay.h"
void Led_Init()
{
	//使能时钟 led1 位于PE8（GPIOE端口 --PIN_8）引脚  挂在AHB1总线上
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);	
	//GPIO结构体配置及初始化
	GPIO_InitTypeDef gpio_struct;//GPIO结构体变量
	gpio_struct.GPIO_Mode=GPIO_Mode_OUT;//模式：输出模式
	gpio_struct.GPIO_OType = GPIO_OType_PP;//输出类型：推挽输出
	gpio_struct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;//指定引脚
	gpio_struct.GPIO_Speed = GPIO_Speed_2MHz;//速率
	GPIO_Init(GPIOE,&gpio_struct);//初始化	
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

void led_run()//流水灯
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
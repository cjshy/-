#include "stm32f4xx.h"
#include "delay.h"
void Beep_Init()
{
	//打开时钟信号 BEEP位于GPIOB端口——PIN10引脚）挂载在AHB1总线上
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef gpio_Beep;
	gpio_Beep.GPIO_Mode = GPIO_Mode_OUT;
	gpio_Beep.GPIO_OType = GPIO_OType_PP;
	gpio_Beep.GPIO_Pin = GPIO_Pin_10;
	gpio_Beep.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB,&gpio_Beep);
}

void Beep_Run()
{
	for(int i=0;i<3;i++)
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_10);
		delay_ms(1000);
		GPIO_ResetBits(GPIOB,GPIO_Pin_10);
		delay_ms(1000);
	}
}

void Beep_Close()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_10);
}

void Beep_Runs()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_10);
}

void pwm_settone(uint16_t Period)
{
	TIM_PrescalerConfig(TIM2,Period,TIM_PSCReloadMode_Immediate);
}
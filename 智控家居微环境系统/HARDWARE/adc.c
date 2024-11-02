#include "stm32f4xx.h"
#include "delay.h"

//光敏电阻的ADC配置
void Phtores_ADC_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_AN; //模拟模式
	gpio_struct.GPIO_Pin = GPIO_Pin_0;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_struct);
	//ADC外设配置以及初始化
	ADC_CommonInitTypeDef adc_comminstruct;
	//adc_comminstruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//失能，这一行可以不写
	adc_comminstruct.ADC_Mode = ADC_Mode_Independent;//独立模式 由于我们只选了一个ADC1选独立模式就可以
	adc_comminstruct.ADC_Prescaler = ADC_Prescaler_Div2;//84MHZ/2 = 42MHZ
	//adc_comminstruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//两个采样阶段之间的延迟5个时钟，这一行可以注释 和DMA有关系
	ADC_CommonInit(&adc_comminstruct);
	
	//ADC 结构体配置以及初始化
	ADC_InitTypeDef adc_initstruct;
	adc_initstruct.ADC_Resolution = ADC_Resolution_12b;
	adc_initstruct.ADC_ContinuousConvMode = DISABLE;//关闭扫描源
	adc_initstruct.ADC_DataAlign = ADC_DataAlign_Right;//s数据右对齐
	adc_initstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//不使用外部触发源 使用内部软件触发
	//adc_initstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;//该行于选择外部触发源需要配置的 可以注释 我们没有选择外部触发源
	adc_initstruct.ADC_NbrOfConversion = 1; //单次转换
	ADC_Init(ADC1,&adc_initstruct);
	
	//使能adc通道
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_3Cycles);
	
	//ADC使能
	ADC_Cmd(ADC1,ENABLE);
}

//获取ADC的值
u16 get_adc_val()
{
	//设置规则通道组
	//ADC1,通道0，一个序列，480个机器周期，提高采样时间可以提高精度，这是采样时间
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_480Cycles);
	//开始转换
	ADC_SoftwareStartConv(ADC1);
	//等待转换结束
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	//获取转换结果
	return ADC_GetConversionValue(ADC1);//当前adc值/4096 *3.3v
}

//获取通道ch的转换值，取times次，然后平均
unsigned short int getAdcAverage1(unsigned char ch,unsigned char times)
{
	//一个通道采集5次 ，取和求平均值
	unsigned short int temp_val =0;
	unsigned char t;
	for(t=0;t<times;t++)
	{
		temp_val +=get_adc_val();
		delay_ms(5);
	}
	return temp_val/times;
}


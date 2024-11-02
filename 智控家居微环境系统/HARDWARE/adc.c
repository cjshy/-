#include "stm32f4xx.h"
#include "delay.h"

//���������ADC����
void Phtores_ADC_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_AN; //ģ��ģʽ
	gpio_struct.GPIO_Pin = GPIO_Pin_0;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio_struct);
	//ADC���������Լ���ʼ��
	ADC_CommonInitTypeDef adc_comminstruct;
	//adc_comminstruct.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;//ʧ�ܣ���һ�п��Բ�д
	adc_comminstruct.ADC_Mode = ADC_Mode_Independent;//����ģʽ ��������ֻѡ��һ��ADC1ѡ����ģʽ�Ϳ���
	adc_comminstruct.ADC_Prescaler = ADC_Prescaler_Div2;//84MHZ/2 = 42MHZ
	//adc_comminstruct.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;//���������׶�֮����ӳ�5��ʱ�ӣ���һ�п���ע�� ��DMA�й�ϵ
	ADC_CommonInit(&adc_comminstruct);
	
	//ADC �ṹ�������Լ���ʼ��
	ADC_InitTypeDef adc_initstruct;
	adc_initstruct.ADC_Resolution = ADC_Resolution_12b;
	adc_initstruct.ADC_ContinuousConvMode = DISABLE;//�ر�ɨ��Դ
	adc_initstruct.ADC_DataAlign = ADC_DataAlign_Right;//s�����Ҷ���
	adc_initstruct.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//��ʹ���ⲿ����Դ ʹ���ڲ��������
	//adc_initstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;//������ѡ���ⲿ����Դ��Ҫ���õ� ����ע�� ����û��ѡ���ⲿ����Դ
	adc_initstruct.ADC_NbrOfConversion = 1; //����ת��
	ADC_Init(ADC1,&adc_initstruct);
	
	//ʹ��adcͨ��
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_3Cycles);
	
	//ADCʹ��
	ADC_Cmd(ADC1,ENABLE);
}

//��ȡADC��ֵ
u16 get_adc_val()
{
	//���ù���ͨ����
	//ADC1,ͨ��0��һ�����У�480���������ڣ���߲���ʱ�������߾��ȣ����ǲ���ʱ��
	ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_480Cycles);
	//��ʼת��
	ADC_SoftwareStartConv(ADC1);
	//�ȴ�ת������
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	//��ȡת�����
	return ADC_GetConversionValue(ADC1);//��ǰadcֵ/4096 *3.3v
}

//��ȡͨ��ch��ת��ֵ��ȡtimes�Σ�Ȼ��ƽ��
unsigned short int getAdcAverage1(unsigned char ch,unsigned char times)
{
	//һ��ͨ���ɼ�5�� ��ȡ����ƽ��ֵ
	unsigned short int temp_val =0;
	unsigned char t;
	for(t=0;t<times;t++)
	{
		temp_val +=get_adc_val();
		delay_ms(5);
	}
	return temp_val/times;
}


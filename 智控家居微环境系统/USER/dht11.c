#include "stm32f4xx.h"
#include "delay.h"
#include "stdio.h"
/*
ͨ��ԭ��ͼ���� ���Է��� DHT11����GND ��VCC ���� ֻ��һ������  �ں�оƬstm32������   ��������� ����PA3
����������Ҫ����˫�����ݽ���  �Ǹ�������� �͵�������ģʽ  ������ ���
*/
//����ģʽ
void Set_DHT11_Mode_IN(void)
{
	//1.ʹ��ʱ�� PA3
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode=GPIO_Mode_IN;	
	gpio.GPIO_Pin=GPIO_Pin_3;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	gpio.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&gpio);
	
}

void Set_DHT11_Mode_OUT(void)
{
	//1.ʹ��ʱ�� PA3
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	GPIO_InitTypeDef gpio;
	gpio.GPIO_Mode=GPIO_Mode_OUT;
	gpio.GPIO_Pin=GPIO_Pin_3;
	gpio.GPIO_Speed=GPIO_Speed_50MHz;
	gpio.GPIO_OType=GPIO_OType_PP;
	GPIO_Init(GPIOA,&gpio);
	
}

//��������һ����ʼ�ź�
int Start_ask(void)
{
		//printf("ceshi\n");
	Set_DHT11_Mode_OUT();
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	//���� 20ms
	GPIO_ResetBits(GPIOA,GPIO_Pin_3);
	delay_ms(20);
	//����
	GPIO_SetBits(GPIOA,GPIO_Pin_3);
	delay_us(30);//��ʱ30us

	//��Ӧ
	Set_DHT11_Mode_IN();//�л�Ϊ����ģʽ
	//�ȴ����  �ȴ���ʱ�䲻��̫�� ������80us  
	int t1=1;	
	while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))&&t1<100)
	{
		delay_us(1);
		t1++;
	}
	//printf("t1:%d\r\n",t1);
		
	int t=0;	
	while(!GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)&&t<80)//���һֱά�ֵ͵�ƽ ��ѭ�� ---���ȴ���ߵ�ƽ
	{
		t++;
		delay_us(1);
		
	}	//printf("t=%d\r\n",t);
	if(t>=80)
	{

		return 0;
	}
	
	//�ȴ� ���
	t1=0;
	while((GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3))&&t1<80)
	{
		delay_us(1);
		t1++;
	}
	//printf("t1=%d\r\n",t1);
	if(t1>=80)
	{
		return 0;
	}

	return 1;
}

u8 Read_Bit(void)
{
	Set_DHT11_Mode_IN();//����ģʽ
	//�ȴ���ƽ���
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==SET);
	//�ȴ���ƽ ���  
	while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==RESET);
	delay_us(40);//40us�Ժ���������Ծ��Ǹߵ�ƽ ��ζ��  ��һλ����Ϊ1
	if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)==SET)
	{
		return 1;
	}
	return 0;
}

u8 Read_Byte(void)
{
	u8 dht11_data=0;
	for(int i=7;i>=0;i--)//MSB  ��λ��ǰ
	{
		dht11_data|=Read_Bit()<<i;
	}
	return dht11_data;
}
u8 buf[5]={0};
int DHT11_WORK(u8 *humi,u8 *temp)
{
	u8 data;
	
	if(Start_ask())//��Ӧ
	{
	//printf("��Ӧ\r\n");
		for(int i=0;i<5;i++)
		{
			buf[i]=Read_Byte();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];		
			*temp=buf[2];
			return 1;
		}
		Set_DHT11_Mode_OUT();
		
	}
	return 0;
}



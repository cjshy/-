#include "stm32f4xx.h"
#include "iic.h"
#include "delay.h"
#include "stdio.h"
//IIC��ʼ��
void IIC_Init()
{
	//ʹ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//GPIO����
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_struct.GPIO_OType = GPIO_OType_OD;//��©
	gpio_struct.GPIO_Pin =IIC_SDA_PIN |IIC_SCL_PIN;
	
	GPIO_Init(GPIOB,&gpio_struct);
}

//����SDAģʽΪ���ģʽ
void SET_SDA_OUT()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_struct.GPIO_OType = GPIO_OType_OD;
	gpio_struct.GPIO_Pin = IIC_SDA_PIN;
	gpio_struct.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOB,&gpio_struct);
}

//����SDAģʽΪ����ģʽ
void SET_SDA_IN()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_IN;
	gpio_struct.GPIO_Pin = IIC_SDA_PIN;
	gpio_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_struct.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOB,&gpio_struct);
}

//��ʼ�ź�
void Start_signal()
{
	//��SDA����Ϊ���ģʽ
	SET_SDA_OUT();
	//����SDA��SCL
	SCL_Write(1);
	SDA_Write(1);
	delay_us(5);
	//����SDA
	SDA_Write(0);
	delay_us(5);
	//����SCL
	SCL_Write(0);
	
}

//�����ź�
void Stop_signal()
{
	//��SDA����Ϊ���ģʽ
	SET_SDA_OUT();
	//����SCL��SDA
	SCL_Write(0);
	SDA_Write(0);
	delay_us(2);
	//����SCL
	SCL_Write(1);
	delay_us(5);
	//����SDA
	SDA_Write(1);
}

//�ȴ��ӻ�Ӧ�� 0��Ӧ��  1����Ӧ��
u8 IIC_get_Ask()
{
	//����SCL
	SCL_Write(0);
	//����ģʽ
	SET_SDA_IN();
	//����SCL
	SCL_Write(1);
	delay_us(5);
	
	if(GPIO_ReadInputDataBit(IIC_PORT,IIC_SDA_PIN) == RESET)
	{
		//Ӧ��
		//����SCL
		SCL_Write(0);
		delay_us(5);
		return 0;
	}
	return 1;
}

//����Ӧ��
void IIC_send_Ask(u8 ask)
{
	//SCL ���� ������Ч
	SCL_Write(0);
	//���ģʽ
	SET_SDA_OUT();
	//����SCL
	SCL_Write(0);
	delay_us(5);
	//SDA׼������
	if(ask)
	{
		SDA_Write(1);
	}
	else
	{
		SDA_Write(0);//Ӧ��
	}
	//����SCL ��������
	SCL_Write(1);
	delay_us(5); //����
	//����SCL
	SCL_Write(0);
	delay_us(5);
}

void IIC_send_Byte(u8 data)
{
	int i;
	//SCL���� ������Ч
	SCL_Write(0);
	//���ģʽ
	SET_SDA_OUT();
	//SCL����
	SCL_Write(0);
	delay_us(2);
	//�������� ��λ��ǰ
	for(i =7;i>=0;i--)
	{
		if(data &(0x01<<i))
		{
			SDA_Write(1);
		}
		else
		{
			SDA_Write(0);
		}
		delay_us(2);
		//����SCL  ��������
		SCL_Write(1);
		delay_us(2);
		//����SCL
		SCL_Write(0);
		delay_us(2);
	}
}

u8 IIC_read_Byte()
{
	u8 data =0;
	int i;
	//SCL����  ������Ч
	SCL_Write(0);
	//���ģʽ
	SET_SDA_IN();
	//SCL SDA����
	SCL_Write(0);
	delay_us(2);
	//������
	for(i =7;i>=0;i--)//MSB
	{
		//����SCL
		SCL_Write(1);
		delay_us(2);
		if(GPIO_ReadInputDataBit(IIC_PORT,IIC_SDA_PIN) == SET)
		{
			data |=1<<i;
		}
		//����SCL
		SCL_Write(0);
		delay_us(2);
	}
	//����SCL
	SCL_Write(1);
	delay_us(2);
	return data;
}

void IIC_AT24C02_write_data(u8 addr,u8 data)
{
	//1.��ʼ�ź�
	Start_signal();
	//2.���ʹӵ�ַ ��д
	IIC_send_Byte(0xA0);
	//3.�ȴ�Ӧ��
	if(IIC_get_Ask()) //1 δӦ��
	{
		printf("Device addr no ask\r\n");
		Stop_signal();
		return ;
	}
	//д�ֵ�ַ
	IIC_send_Byte(addr);
	//�ȴ�Ӧ��
	if(IIC_get_Ask()) //1 δӦ��
	{
		printf("Word addr no ask\r\n");
		Stop_signal();
		return ;
	}
	//д����
	IIC_send_Byte(data);
	//�ȴ�Ӧ��
	if(IIC_get_Ask())//1 δӦ��
	{
		printf("data no ask\r\n");
		Stop_signal();
		return ;
	}
	//ֹͣ�ź�
	Stop_signal();
}

u8 AT24C02_read_data(u8 addr)
{
	//��ʼ�ź�
	Start_signal();
	//���ʹ�������ַ ��д
	IIC_send_Byte(0xA0);
	//�ȴ�Ӧ��
	if(IIC_get_Ask()) //1 δӦ��
	{
		printf("read Device addr no ask\r\n");
		Stop_signal();
	}
	//�����ֵ�ַ
	IIC_send_Byte(addr);
	//�ȴ�Ӧ��
	if(IIC_get_Ask())
	{
		printf("read word addr no ask\r\n");
		Stop_signal();
	}
	//��ʼ�ź�
	Start_signal();
	//���ʹ�������ַ ����
	IIC_send_Byte(0xA1);
	//�ȴ�Ӧ��
	if(IIC_get_Ask())
	{
		printf("read Device2 addr no ask\r\n");
		Stop_signal();
	}
	//������
	u8 data = IIC_read_Byte();
	//�������� ��Ӧ��
	IIC_send_Ask(1);
	//ֹͣ����
	Stop_signal();
	return data;
}
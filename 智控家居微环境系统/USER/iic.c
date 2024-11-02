#include "stm32f4xx.h"
#include "iic.h"
#include "delay.h"
#include "stdio.h"
//IIC初始化
void IIC_Init()
{
	//使能时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//GPIO配置
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_struct.GPIO_OType = GPIO_OType_OD;//开漏
	gpio_struct.GPIO_Pin =IIC_SDA_PIN |IIC_SCL_PIN;
	
	GPIO_Init(GPIOB,&gpio_struct);
}

//设置SDA模式为输出模式
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

//设置SDA模式为输入模式
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

//起始信号
void Start_signal()
{
	//将SDA设置为输出模式
	SET_SDA_OUT();
	//拉高SDA，SCL
	SCL_Write(1);
	SDA_Write(1);
	delay_us(5);
	//拉低SDA
	SDA_Write(0);
	delay_us(5);
	//拉低SCL
	SCL_Write(0);
	
}

//结束信号
void Stop_signal()
{
	//将SDA设置为输出模式
	SET_SDA_OUT();
	//拉低SCL，SDA
	SCL_Write(0);
	SDA_Write(0);
	delay_us(2);
	//拉高SCL
	SCL_Write(1);
	delay_us(5);
	//拉高SDA
	SDA_Write(1);
}

//等待从机应答 0：应答  1：不应答
u8 IIC_get_Ask()
{
	//拉低SCL
	SCL_Write(0);
	//输入模式
	SET_SDA_IN();
	//拉高SCL
	SCL_Write(1);
	delay_us(5);
	
	if(GPIO_ReadInputDataBit(IIC_PORT,IIC_SDA_PIN) == RESET)
	{
		//应答
		//拉高SCL
		SCL_Write(0);
		delay_us(5);
		return 0;
	}
	return 1;
}

//主机应答
void IIC_send_Ask(u8 ask)
{
	//SCL 拉低 数据无效
	SCL_Write(0);
	//输出模式
	SET_SDA_OUT();
	//拉低SCL
	SCL_Write(0);
	delay_us(5);
	//SDA准备数据
	if(ask)
	{
		SDA_Write(1);
	}
	else
	{
		SDA_Write(0);//应答
	}
	//拉高SCL 发送数据
	SCL_Write(1);
	delay_us(5); //保持
	//拉低SCL
	SCL_Write(0);
	delay_us(5);
}

void IIC_send_Byte(u8 data)
{
	int i;
	//SCL拉低 数据无效
	SCL_Write(0);
	//输出模式
	SET_SDA_OUT();
	//SCL拉低
	SCL_Write(0);
	delay_us(2);
	//发送数据 高位在前
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
		//拉高SCL  发送数据
		SCL_Write(1);
		delay_us(2);
		//拉低SCL
		SCL_Write(0);
		delay_us(2);
	}
}

u8 IIC_read_Byte()
{
	u8 data =0;
	int i;
	//SCL拉低  数据无效
	SCL_Write(0);
	//输出模式
	SET_SDA_IN();
	//SCL SDA拉低
	SCL_Write(0);
	delay_us(2);
	//读数据
	for(i =7;i>=0;i--)//MSB
	{
		//拉高SCL
		SCL_Write(1);
		delay_us(2);
		if(GPIO_ReadInputDataBit(IIC_PORT,IIC_SDA_PIN) == SET)
		{
			data |=1<<i;
		}
		//拉低SCL
		SCL_Write(0);
		delay_us(2);
	}
	//拉高SCL
	SCL_Write(1);
	delay_us(2);
	return data;
}

void IIC_AT24C02_write_data(u8 addr,u8 data)
{
	//1.起始信号
	Start_signal();
	//2.发送从地址 ：写
	IIC_send_Byte(0xA0);
	//3.等待应答
	if(IIC_get_Ask()) //1 未应答
	{
		printf("Device addr no ask\r\n");
		Stop_signal();
		return ;
	}
	//写字地址
	IIC_send_Byte(addr);
	//等待应答
	if(IIC_get_Ask()) //1 未应答
	{
		printf("Word addr no ask\r\n");
		Stop_signal();
		return ;
	}
	//写数据
	IIC_send_Byte(data);
	//等待应答
	if(IIC_get_Ask())//1 未应答
	{
		printf("data no ask\r\n");
		Stop_signal();
		return ;
	}
	//停止信号
	Stop_signal();
}

u8 AT24C02_read_data(u8 addr)
{
	//起始信号
	Start_signal();
	//发送从器件地址 ：写
	IIC_send_Byte(0xA0);
	//等待应答
	if(IIC_get_Ask()) //1 未应答
	{
		printf("read Device addr no ask\r\n");
		Stop_signal();
	}
	//发送字地址
	IIC_send_Byte(addr);
	//等待应答
	if(IIC_get_Ask())
	{
		printf("read word addr no ask\r\n");
		Stop_signal();
	}
	//起始信号
	Start_signal();
	//发送从器件地址 ：读
	IIC_send_Byte(0xA1);
	//等待应答
	if(IIC_get_Ask())
	{
		printf("read Device2 addr no ask\r\n");
		Stop_signal();
	}
	//读数据
	u8 data = IIC_read_Byte();
	//主机发送 不应答
	IIC_send_Ask(1);
	//停止服务
	Stop_signal();
	return data;
}
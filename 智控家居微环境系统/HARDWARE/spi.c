#include "stm32f4xx.h"
#include "spi.h"
void SPI1_Init(void)
{
	//使能时钟  SPI接口位于APB2总线  且在GPIOB中，GPIOB位于AHB1总线
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//GPIO结构体配置 SPI_SCK1 SPI_MISO SPI_MOSI
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF;//复用输出模式
	gpio_struct.GPIO_Pin = SPI_MISO1_PIN|SPI_MOSI_Pin|SPI_SCK1_PIN;
	gpio_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;//无上拉电阻
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio_struct);
	//初始化外设CSS W25Q_CS引脚
	gpio_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_struct.GPIO_OType = GPIO_OType_PP;//推挽输出
	gpio_struct.GPIO_Pin = W25Q_CS_PIN;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio_struct);
	
	//设置高电平  --》空闲状态 拉低就意味着要开始与从机通信
	W25Q_CS_Write(1);
	
	//管脚复用
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);
	//spi结构体配置
	SPI_InitTypeDef spi_struct;
	spi_struct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //全双工
	spi_struct.SPI_Mode = SPI_Mode_Master;//主机模式
	spi_struct.SPI_DataSize = SPI_DataSize_8b;
	
	spi_struct.SPI_CPOL = SPI_CPOL_High;
	spi_struct.SPI_CPHA = SPI_CPHA_2Edge;
	spi_struct.SPI_NSS = SPI_NSS_Soft;//nss设置为软件管理
	spi_struct.SPI_BaudRatePrescaler= SPI_BaudRatePrescaler_4;//4分频  84MHZ/4 = 21MHZ
	spi_struct.SPI_FirstBit = SPI_FirstBit_MSB; //高位在前
	SPI_Init(SPI1,&spi_struct);
	
	//SPI1使能
	SPI_Cmd(SPI1,ENABLE);
	
}

u16 W25Q128_SPI_READ_WRITE(u16 data)
{
	while(SPI_GetFlagStatus(SPI1,SPI_FLAG_TXE) == RESET);//等待数据传输完成
	SPI_SendData(SPI1,data);
	while(SPI_GetFlagStatus(SPI1,SPI_FLAG_RXNE) == RESET);
	
	return SPI_ReceiveData(SPI1);//接受数据
}

u16 W25Q128_ReadDeviceId()
{
	u16 ID =0;
	//把CS片选引脚拉低 表示选中
	W25Q_CS_Write(0);
	//发送指令
	W25Q128_SPI_READ_WRITE(0x90);
	//发送地址
	W25Q128_SPI_READ_WRITE(0X00);
	W25Q128_SPI_READ_WRITE(0X00);
	W25Q128_SPI_READ_WRITE(0X00);
	
	//接收厂商ID和设备ID
	ID = W25Q128_SPI_READ_WRITE(0X00) <<8;
	ID |= W25Q128_SPI_READ_WRITE(0x00);
	
	//把cs片选引脚拉高   表示不通信
	W25Q_CS_Write(1);
	return ID;
}
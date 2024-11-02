#include "stm32f4xx.h"
#include "spi.h"
void SPI1_Init(void)
{
	//ʹ��ʱ��  SPI�ӿ�λ��APB2����  ����GPIOB�У�GPIOBλ��AHB1����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//GPIO�ṹ������ SPI_SCK1 SPI_MISO SPI_MOSI
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF;//�������ģʽ
	gpio_struct.GPIO_Pin = SPI_MISO1_PIN|SPI_MOSI_Pin|SPI_SCK1_PIN;
	gpio_struct.GPIO_PuPd = GPIO_PuPd_NOPULL;//����������
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio_struct);
	//��ʼ������CSS W25Q_CS����
	gpio_struct.GPIO_Mode = GPIO_Mode_OUT;
	gpio_struct.GPIO_OType = GPIO_OType_PP;//�������
	gpio_struct.GPIO_Pin = W25Q_CS_PIN;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&gpio_struct);
	
	//���øߵ�ƽ  --������״̬ ���;���ζ��Ҫ��ʼ��ӻ�ͨ��
	W25Q_CS_Write(1);
	
	//�ܽŸ���
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource4,GPIO_AF_SPI1);
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource5,GPIO_AF_SPI1);
	//spi�ṹ������
	SPI_InitTypeDef spi_struct;
	spi_struct.SPI_Direction = SPI_Direction_2Lines_FullDuplex; //ȫ˫��
	spi_struct.SPI_Mode = SPI_Mode_Master;//����ģʽ
	spi_struct.SPI_DataSize = SPI_DataSize_8b;
	
	spi_struct.SPI_CPOL = SPI_CPOL_High;
	spi_struct.SPI_CPHA = SPI_CPHA_2Edge;
	spi_struct.SPI_NSS = SPI_NSS_Soft;//nss����Ϊ�������
	spi_struct.SPI_BaudRatePrescaler= SPI_BaudRatePrescaler_4;//4��Ƶ  84MHZ/4 = 21MHZ
	spi_struct.SPI_FirstBit = SPI_FirstBit_MSB; //��λ��ǰ
	SPI_Init(SPI1,&spi_struct);
	
	//SPI1ʹ��
	SPI_Cmd(SPI1,ENABLE);
	
}

u16 W25Q128_SPI_READ_WRITE(u16 data)
{
	while(SPI_GetFlagStatus(SPI1,SPI_FLAG_TXE) == RESET);//�ȴ����ݴ������
	SPI_SendData(SPI1,data);
	while(SPI_GetFlagStatus(SPI1,SPI_FLAG_RXNE) == RESET);
	
	return SPI_ReceiveData(SPI1);//��������
}

u16 W25Q128_ReadDeviceId()
{
	u16 ID =0;
	//��CSƬѡ�������� ��ʾѡ��
	W25Q_CS_Write(0);
	//����ָ��
	W25Q128_SPI_READ_WRITE(0x90);
	//���͵�ַ
	W25Q128_SPI_READ_WRITE(0X00);
	W25Q128_SPI_READ_WRITE(0X00);
	W25Q128_SPI_READ_WRITE(0X00);
	
	//���ճ���ID���豸ID
	ID = W25Q128_SPI_READ_WRITE(0X00) <<8;
	ID |= W25Q128_SPI_READ_WRITE(0x00);
	
	//��csƬѡ��������   ��ʾ��ͨ��
	W25Q_CS_Write(1);
	return ID;
}
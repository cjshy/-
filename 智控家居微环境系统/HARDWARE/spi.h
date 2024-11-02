#ifndef _SPI_H
#define _SPI_H
#define W25Q_CS_PIN 	GPIO_Pin_2
#define SPI_SCK1_PIN 	GPIO_Pin_3
#define SPI_MISO1_PIN 	GPIO_Pin_4
#define SPI_MOSI_Pin	GPIO_Pin_5

#define W25Q_CS_Write(N) (N)?GPIO_SetBits(GPIOB,W25Q_CS_PIN):GPIO_ResetBits(GPIOB,W25Q_CS_PIN)
void SPI1_Init(void);
u16 W25Q128_SPI_READ_WRITE(u16 data);
uint16_t W25Q128_ReadDeviceId();
#endif
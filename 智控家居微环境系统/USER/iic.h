#ifndef _IIC_H
#define _IIC_H
//IIC端口
#define IIC_PORT GPIOB

//SDA引脚
#define IIC_SDA_PIN GPIO_Pin_7
//SCL引脚
#define IIC_SCL_PIN GPIO_Pin_6

//SCL 时钟线写操作
#define SCL_Write(N) (N)?GPIO_SetBits(IIC_PORT,IIC_SCL_PIN):GPIO_ResetBits(IIC_PORT,IIC_SCL_PIN)
//SDA 数据线写操作
#define SDA_Write(N) (N)?GPIO_SetBits(IIC_PORT,IIC_SDA_PIN):GPIO_ResetBits(IIC_PORT,IIC_SDA_PIN) 
#include "stm32f4xx.h"
void IIC_Init();
void SET_SDA_OUT();
void SET_SDA_IN();
void Start_signal();
void Stop_signal();
u8 IIC_get_Ask();
void IIC_send_Ask(u8 ask);
void IIC_send_Byte(u8 data);
u8 IIC_read_Byte();
void IIC_AT24C02_write_data(u8 addr,u8 data);
u8 AT24C02_read_data(u8 addr);
#endif
#ifndef _MAIN_H
#define _MAIN_H

#include "beep.h"
#include "led.h"
#include "key.h"
#include "nvic.h"
#include "systick.h"
#include "time.h"
#include "pwm.h"
#include "usart.h"
#include "dht11.h"
#include "stdio.h"
#include "string.h"
#include "oled.h"
#include "spi.h"
#include "adc.h"
#include "wifi.h"
extern unsigned int key_flag;
extern unsigned int key2_flag;
extern unsigned int key3_flag;
extern unsigned int key4_flag;
extern u8 data;
extern u8 humi,temp;
extern u16 val;
extern int wifi_rec_flag; //wifi数据接收标志位
extern int wifi_work_flag; //wifi模块服务端工作标志位
extern u8 wifi_buf[1024];
extern int wifi_len;
extern int All_flag;//开关机
void show_Information(u8 *humi,u8 *temp,u16 *val);
void Send_Information(u8 humi,u8 temp,u16 val);
#endif
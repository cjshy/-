#include "stm32f4xx.h"
#include "main.h"
#include "delay.h"
#include "iic.h"
#include "stdio.h"
#include "oled.h"

void show_Information(u8 *humi,u8 *temp,u16 *val)
{
	//printf("光照值：%d\r\n",*val);
	Set_LedLight(*val);//光照强度设置
	if(*val <1000)
	{
		Oled_print(88,4," ");
	}
	char light_str[20];
	sprintf(light_str,"%d",*val);
	Oled_print(64,4,light_str);
	//Oled_print(96,4,"mv");
		
	if(DHT11_WORK(humi,temp))
	{
		//printf("humi:%d temp:%d\r\n",*humi,*temp);
		char temp_str[20];
		sprintf(temp_str,"%d",*temp);
		Oled_print(64,0,temp_str);
		sprintf(temp_str,"%d",*humi);
		Oled_print(64,2,temp_str);	
	}
	delay_ms(500);
}

void Send_Information(u8 humi, u8 temp, u16 val)
{
    char t[40];
    sprintf(t, "%d:%d:%d\r\n", humi, temp, val); 

    // 准备要发送的字符串
    char command[] = "AT+CIPSEND=0,10\r\n"; 

    // 发送所有字符串
    Usart2_Send_str(command); // 发送命令
	delay_ms(100);
    Usart2_Send_str(t); // 发送格式化的信息
	delay_ms(100); 
}


#if 1
int main()
{
	delay_init(168);
	Key_Init();
	IIC_Init();
	Fan_Init();//风扇初始化
	OLed_Fill(0x00);//清空屏幕
	Phtores_ADC_Init();//光敏电阻
	EXTI4_Config();
	EXTI9_5_Config();
	EXTI12_Config();
	NVIC_Config();
	Usart2_Config();
	Usart_Config();
	Led_Init();
	Beep_Init();
	NVIC_Config();
	PWM_TIM1_CH1_LED();//开启定时器1通道1
	Set_Server_Mode();
	//Set_Client_Mode();
	printf("数据发送完成\r\n");
	while(1)
	{
		key_Select();
		
	}
	return 0;
}
#endif


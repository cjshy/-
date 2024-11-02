#include "stm32f4xx.h"
#include "main.h"
#include "delay.h"
void Usart2_Config()
{
	//串口时钟使能 USART2位于APB1总线
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//GPIO时钟使能 PD6,PD5 位于AHB1总线
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	//管脚复用
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	//GPIO配置 以及初始化
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF;
	gpio_struct.GPIO_OType = GPIO_OType_PP;
	gpio_struct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	gpio_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&gpio_struct);
	//串口的配置以及初始化
	USART_InitTypeDef usart2;
	usart2.USART_BaudRate = 115200; //波特率
	usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件控制流无
	usart2.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
	usart2.USART_Parity = USART_Parity_No;//无校验
	usart2.USART_StopBits = USART_StopBits_1;
	usart2.USART_WordLength = USART_WordLength_8b;//数据字长为 8位
	USART_Init(USART2,&usart2);
	//串口使能
	USART_Cmd(USART2,ENABLE);
	//串口接收中断使能
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);//空闲中断
}


//通过串口2发送命令
void Usart2_Send_str(char *s)
{
	int len = strlen(s);
	int i;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2,*s);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET); //等待发完
		s++;
	}
}

//将ESPB266设置为服务端模式
void Set_Server_Mode()
{
	char *ESP8266_AP_Server[] ={
	"AT\r\n",
	"ATE1\r\n",
	"AT+CWMODE=2\r\n",
	"AT+RST\r\n",
	"ATE1\r\n",
	"AT+CWSAP=\"cj\",\"25736721\",1,4\r\n",
	"AT+CIPMUX=1\r\n",
	"AT+CIPSERVER=1,8888\r\n",
	"AT+CIFSR\r\n"
	};
	int i=0;
	for(i=0;i<9;i++)
	{
		Usart2_Send_str(ESP8266_AP_Server[i]);
		delay_ms(1000);
	}
	wifi_work_flag =1; //开始工作
}

void Set_Client_Mode()
{
	char *ESP8266_STA_Client[]={
	"AT\r\n",//检测ESP8266模块是否正常工作
	"ATE1\n\n",//关闭回显功能
	"AT+CWMODE=1\r\n",//设置为STA模式
	"AT+RST\r\n",//重启ESP8266模块
	"ATE1\r\n",//关闭回显功能
	"AT+CWLAP\rn",//查询可以连接的WIFI
	"AT+CWJAP:=\"hqyjcs\",\"hqyj2022\"\r\n",//连接指定的WIFI
	"AT+CIPMUX=O\r\n",//设置为单连接模式
	"AT+CIPMODE=1\r\n",//设置为透传模式
	"AT+CIPSTART:=\"TCP\",\"192.168.91.113\",8888\r\n",//建立TCP连接
	//"AT+CIPSEND\r\n",//发送数据
	};
	int i=0;
	for(i=0;i<10;i++)
	{
		Usart2_Send_str(ESP8266_STA_Client[i]);
		delay_ms(1000);
	}
}

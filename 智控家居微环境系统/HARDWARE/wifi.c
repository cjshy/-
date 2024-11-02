#include "stm32f4xx.h"
#include "main.h"
#include "delay.h"
void Usart2_Config()
{
	//����ʱ��ʹ�� USART2λ��APB1����
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//GPIOʱ��ʹ�� PD6,PD5 λ��AHB1����
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	//�ܽŸ���
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2);
	//GPIO���� �Լ���ʼ��
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode = GPIO_Mode_AF;
	gpio_struct.GPIO_OType = GPIO_OType_PP;
	gpio_struct.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	gpio_struct.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&gpio_struct);
	//���ڵ������Լ���ʼ��
	USART_InitTypeDef usart2;
	usart2.USART_BaudRate = 115200; //������
	usart2.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//Ӳ����������
	usart2.USART_Mode = USART_Mode_Rx |USART_Mode_Tx;
	usart2.USART_Parity = USART_Parity_No;//��У��
	usart2.USART_StopBits = USART_StopBits_1;
	usart2.USART_WordLength = USART_WordLength_8b;//�����ֳ�Ϊ 8λ
	USART_Init(USART2,&usart2);
	//����ʹ��
	USART_Cmd(USART2,ENABLE);
	//���ڽ����ж�ʹ��
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	USART_ITConfig(USART2,USART_IT_IDLE,ENABLE);//�����ж�
}


//ͨ������2��������
void Usart2_Send_str(char *s)
{
	int len = strlen(s);
	int i;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2,*s);
		while(USART_GetFlagStatus(USART2,USART_FLAG_TXE) == RESET); //�ȴ�����
		s++;
	}
}

//��ESPB266����Ϊ�����ģʽ
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
	wifi_work_flag =1; //��ʼ����
}

void Set_Client_Mode()
{
	char *ESP8266_STA_Client[]={
	"AT\r\n",//���ESP8266ģ���Ƿ���������
	"ATE1\n\n",//�رջ��Թ���
	"AT+CWMODE=1\r\n",//����ΪSTAģʽ
	"AT+RST\r\n",//����ESP8266ģ��
	"ATE1\r\n",//�رջ��Թ���
	"AT+CWLAP\rn",//��ѯ�������ӵ�WIFI
	"AT+CWJAP:=\"hqyjcs\",\"hqyj2022\"\r\n",//����ָ����WIFI
	"AT+CIPMUX=O\r\n",//����Ϊ������ģʽ
	"AT+CIPMODE=1\r\n",//����Ϊ͸��ģʽ
	"AT+CIPSTART:=\"TCP\",\"192.168.91.113\",8888\r\n",//����TCP����
	//"AT+CIPSEND\r\n",//��������
	};
	int i=0;
	for(i=0;i<10;i++)
	{
		Usart2_Send_str(ESP8266_STA_Client[i]);
		delay_ms(1000);
	}
}

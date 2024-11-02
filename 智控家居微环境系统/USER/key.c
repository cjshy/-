#include "stm32f4xx.h"
#include "main.h"
#include "wifi.h"
#include "delay.h"
//定义音调名，方便写谱
#define V0  0
#define L1  1
#define L1_ 2
#define L2  3
#define L2_ 4
#define L3  5
#define L4  6
#define L4_ 7
#define L5  8
#define L5_ 9
#define L6  10
#define L6_ 11
#define L7  12

#define M1  13
#define M1_ 14
#define M2  15
#define M2_ 16
#define M3  17
#define M4  18
#define M4_ 19
#define M5  20
#define M5_ 21
#define M6  22
#define M6_ 23
#define M7  24

#define H1  25
#define H1_ 26
#define H2  27
#define H2_ 28
#define H3  29
#define H4  30
#define H4_ 31
#define H5  32
#define H5_ 33
#define H6  34
#define H6_ 35
#define H7  36
uint16_t choose,time;
//定义音调表
uint16_t tone[]={
	0,
	3817,3610,3401,3215,3030,2865,2703,2551,2410,2272,2146,2024,
	1912,1805,1703,1608,1517,1432,1351,1275,1203,1136,1073,1012,
	956,902,851,803,758,715,676,637,602,568,536,506,100
};

//定义简谱表：音调,时值
uint16_t Music[]={
//孤独摇滚 吉他与孤独与蓝色星球（70）
	H1,2,M7,2,M6,2,M7,4,M1,2,M2,2,M3,4,M1,4,L7,4,L7,2,L7,4,
	H1,2,M7,2,M6,2,M7,4,M2,2,M3,4,M1,2,M5,4,M6,2,M5,4,
	H1,2,M7,2,M6,2,M7,4,M1,2,M2,2,M3,4,M1,4,L7,4,L7,2,L7,4,
	H2,4,H3,4,M6,4,H1,2,H2,4,H3,4,H5,4,H3,4,
	H6,4,H5,4,H2,2,H3,4,H3,4,M6,4,M5,2,M6,4,M6,4,
	
	M6,4,M6,2,M6,2,M6,2,M5,2,M5,2,M5,2,M3,4,M5,4,M3,4,M5,4,M3,6,
	M5,2,M3,6,M5,2,M3,6,M5,2,M3,6,M2,2,M1,10,
	M1,4,H1,4,M7,4,M5,4,M3,4,M2,4,M3,4,M2,4,M1,4,M3,6,M3,2,M2,8,
	
	M6,4,M6,2,M6,2,M6,2,M5,2,M5,2,M5,2,M3,4,M5,4,M3,4,M5,4,M3,6,
	M5,2,M3,6,M5,2,M3,6,M5,2,M3,6,M2,2,M1,10,
	M1,4,H1,4,M7,4,M5,4,M3,4,M2,4,M3,4,M2,4,M1,4,M3,6,M4,2,M2,8,
	
	M2,6,M1,2,M1,6,M1,2,M2,6,M1,2,M1,6,M1,2,M2,4,M1,4,M2,4,M5,4,M2,6,M1,2,M1,4,M1,6,
	M1,2,M2,6,M1,2,M1,4,M1,4,M2,6,M1,2,M1,4,M1,4,M2,4,M1,4,M2,4,M5,4,M6,4,M5,2,M5,2,M5,2,	
	M5,2,M6,6,M5,2,M5,4,M5,4,M6,6,M5,2,M5,4,M5,4,M6,4,M5,4,M6,4,H1,4,M7,4,M5,4,M3,4,
	M5,4,M1,12,M3,4,M2,2,M1,2,M1,6,M2,4,M3,6,M2,2,M2,8,M4,6,M3,2,M3,12,
	
	H1,4,M7,4,M5,4,M5,2,M6,2,M6,4,M5,2,M6,2,M6,4,M7,4,H1,4,H2,4,M7,4,M7,4,H1,4,M7,4,M5,4,M3,4,	
	M3,4,M6,2,M5,2,M3,2,M1,2,M2,2,M3,4,M1,2,M2,2,M3,2,M1,4,M2,2,M3,2,M1,4,M2,2,M3,2,M5,2,M3,2,M2,4,M3,4,M2,4,M1,4,M3,8,
	M6,4,M5,4,M5,2,M6,2,M6,4,M5,2,M6,2,M6,4,M7,4,H1,4,H2,4,M7,4,M5,4,H4,6,H3,2,H3,4,
	H1,4,H2,4,H3,4,H4,2,H3,2,H3,2,H2,2,H1,2,M7,2,M7,4,M6,2,M7,2,M7,4,H1,2,H1,4,H1,16,V0,8,
	H1,4,H2,4,H3,4,H4,2,H3,2,H3,2,H2,2,H1,2,M7,8,V0,2,M5,2,M7,4,H1,4,

	//结束标志位
	V0,16,0xFF  
};	

void music_begin()
{
	PWM_TIM2_CH3_BEEP();
	while(1)
	{
		choose=Music[time];  
		(time)++;  //1
		pwm_settone(tone[choose]);					
		delay_ms(77.5*Music[time]);    //数字修改1/16时值
		time++;  //2	
		if(key3_flag ==1||key2_flag ==1 || key4_flag == 1)
		{
			TIM_SetCompare3(TIM2,0);
			TIM_Cmd(TIM2,DISABLE);
			Beep_Init();
			break;
		}
	}
	choose =0;
	time =0;
}

void Key_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOC,ENABLE);
	GPIO_InitTypeDef gpio_key;
	gpio_key.GPIO_Mode =GPIO_Mode_IN;
	gpio_key.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6;
	gpio_key.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_key.GPIO_Speed = GPIO_Speed_25MHz;
	
	GPIO_Init(GPIOE,&gpio_key);
	
	GPIO_InitTypeDef gpio_key2;
	gpio_key2.GPIO_Mode =GPIO_Mode_IN;
	gpio_key2.GPIO_Pin = GPIO_Pin_13;
	gpio_key2.GPIO_PuPd = GPIO_PuPd_UP;
	gpio_key2.GPIO_Speed = GPIO_Speed_25MHz;
	GPIO_Init(GPIOC,&gpio_key2);
}


void Fan_Init()
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	GPIO_InitTypeDef gpio_struct;
	gpio_struct.GPIO_Mode =GPIO_Mode_OUT;
	gpio_struct.GPIO_Pin = GPIO_Pin_15;
	gpio_struct.GPIO_OType = GPIO_OType_PP;
	gpio_struct.GPIO_Speed = GPIO_Speed_25MHz;
	
	GPIO_Init(GPIOB,&gpio_struct);
}

void Fan_Run()
{
	GPIO_SetBits(GPIOB,GPIO_Pin_15);
}

void Fan_Close()
{
	GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}

void Delay_ms(uint32_t seconds)
{
	for(uint32_t i=0;i<seconds;i++)
	{
		for(volatile uint32_t j=0;j<1230;j++);
	}
}

void Key_read()
{
	if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == RESET) //PE$
	{
		delay_ms(50);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == RESET)
		{
			while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == RESET);
			Open_Ledn(1);
			char *str[]={"AT+CIPSEND=0,6\r\n",
						"123456\r\n",
			};
			for(int i=0;i<2;i++)
		{
			Usart2_Send_str(str[i]);
			delay_ms(1000);
		}	
			
		}
	}
	else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == RESET) //PE5
	{
		Delay_ms(50);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == RESET)
		{
			while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == RESET);
			Open_Ledn(2);
			Beep_Run();
		}
	}
	else if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6) == RESET) //PE5
	{
		Delay_ms(50);
		if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6) == RESET)
		{
			while(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6) == RESET);
			Open_Ledn(3);
			Beep_Close();
		}
	}
	else if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == RESET) //PE5
	{
		Delay_ms(50);
		if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == RESET)
		{
			while(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == RESET);
			Open_Ledn(0);
		}
	}
		
}

int All_flag =0;
u8 humi =0;
u8 temp =0;
u16 val =0;
int Fan_flage =0;
int mode_flage = 0;

void key_Select()
{
	if(key_flag == 1)//开机   
		{
			delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) == RESET)
			{
				printf("成功开机\r\n");
				Show_Welcome();
				//music_begin();
				All_flag =1;
				GPIO_ResetBits(GPIOE,GPIO_Pin_10);//打开led3
				TIM_SetCompare1(TIM1,0);//关闭呼吸灯
				GPIO_SetBits(GPIOE,GPIO_Pin_8);
			}
			key_flag = 0;
		}
		else if(key2_flag == 1 && All_flag== 1)
		{
			delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_5) == RESET)
			{
				printf("成功关机\r\n");
				Show_End();
				All_flag =0;
				TIM_SetCompare1(TIM1,0);
				GPIO_SetBits(GPIOE,GPIO_Pin_10);//关闭led3
				TIM_SetCompare1(TIM1,0);//关闭呼
				TIM_Cmd(TIM4,DISABLE); //使能定时器
				GPIO_SetBits(GPIOE,GPIO_Pin_8);
				Fan_Close();
				printf("停止发送数据\r\n");
			}
			key2_flag = 0;
		}
		else if(key3_flag == 1 && All_flag == 1)   //自动模式
		{
			delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_6) == RESET)
			{
				OLed_Fill(0x00);//清空屏幕
				oled_test();//显示文字
				//mode_flage = 0; //自动模式
				val = getAdcAverage1(0,4);
				show_Information(&humi,&temp,&val);	
				TIME4_Config();//用于发送数据信息
				while(1)
				{
					val = getAdcAverage1(0,4);
					show_Information(&humi,&temp,&val);
					Set_Device(humi,temp,&Fan_flage,&mode_flage);
					if(key_flag ==1||key2_flag ==1) break;
					if( key4_flag == 1) 
					{
						mode_flage ^= 1;
						key4_flag =0;
					};
				}
			}
			key3_flag = 0;
		}
		else if(key4_flag == 1 && All_flag == 1) //改变为 独立模式
		{
			delay_ms(20);
			if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13) == RESET)
			{

			}
			key4_flag = 0;
		}
}

void TIM4_IRQHandler()
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{
		
		Send_Information(humi,temp,val);
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
	
}

void Set_Device(u8 humi,u8 temp,int *flage,int *mode_flage)
{	
	if(*mode_flage == 0)
	{
		show_mode_1();
		if(temp >30)
	{		
		if(*flage == 0)
		{
			Beep_Run();
			Fan_Run();
		}
		*flage = 1;
	}
	else
	{
		//*flage = 0;
		Beep_Close();
		Fan_Close();
	}
	return ;
	}
	show_mode_2();
	
}
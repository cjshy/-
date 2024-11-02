#include "stm32f4xx.h"
#include "stdio.h"
#include "delay.h"
void PWM_TIM2_CH3_BEEP()
{
	//1.定时器2时钟初始化使能 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	//GPIO时钟配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	//GPIOB第10个成员 复用定时器2
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_TIM2);
	//复用模式：GPIO_Mode_AF
	GPIO_InitTypeDef beep_pwm_struct;
	beep_pwm_struct.GPIO_Mode = GPIO_Mode_AF;//复用模式
	beep_pwm_struct.GPIO_OType = GPIO_OType_PP;
	beep_pwm_struct.GPIO_Pin = GPIO_Pin_10;
	beep_pwm_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&beep_pwm_struct);
	//初始化定时器
	TIM_TimeBaseInitTypeDef tim2_struct;
	tim2_struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim2_struct.TIM_Prescaler = 8400-1;  //0.1ms
	tim2_struct.TIM_Period = 100;
	TIM_TimeBaseInit(TIM2,&tim2_struct);
	//初始化通道3
	TIM_OCInitTypeDef TIM_OCInit_Struct;
	TIM_OCInit_Struct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInit_Struct.TIM_OutputState = TIM_OutputState_Enable;//输出比较寄存器使能
	TIM_OCInit_Struct.TIM_OCNPolarity = TIM_OCPolarity_High; //输出极性为高电平
	TIM_OCInit_Struct.TIM_Pulse = 50; //比较寄存器的值  占空比
	TIM_OC3Init(TIM2,&TIM_OCInit_Struct);
	
	//定时器2的通道 3的比较捕获寄存器使能
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	//自动装载寄存器使能
	TIM_ARRPreloadConfig(TIM2,ENABLE);
	//使能TIM2
	TIM_Cmd(TIM2,ENABLE);
}

// 初始化 PWM 输出
void PWM_TIM1_CH1N_LED1()
{
    // 启用定时器 1 和 GPIOE 的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    // 复位定时器
    TIM_DeInit(TIM1);

    // 配置 GPIOE 的第 8 引脚为定时器 1 通道 1 反相输出
    GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_TIM1); 

    // GPIO 配置
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8; 
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; // 复用模式
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP; // 推挽输出
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz; // 输出速度
    GPIO_Init(GPIOE, &GPIO_InitStruct);

    // 定时器初始化
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_TimeBaseInitStruct.TIM_Period = 100 - 1; // 设置周期 (10 ms)
    TIM_TimeBaseInitStruct.TIM_Prescaler = 8400 - 1; // 预分频 (1 MHz 的计数频率)
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1; // 时钟分割
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; // 向上计数
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStruct);

    // 初始化 PWM 输出通道
    TIM_OCInitTypeDef TIM_OCInitStruct;
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1; // PWM 模式 1
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Disable; // 使能输出
	TIM_OCInitStruct.TIM_OutputNState = TIM_OutputNState_Enable;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low; // 输出极性为低，适用于 CH1N
    TIM_OCInitStruct.TIM_Pulse = 50; // 设置占空比 (0-100)
	TIM_OCInitStruct.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStruct.TIM_OCNIdleState = TIM_OCNIdleState_Set;
    TIM_OC1Init(TIM1, &TIM_OCInitStruct); 

    // 启用比较寄存器预装载
    TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable); 

    // 启用自动重载寄存器
    TIM_ARRPreloadConfig(TIM1, ENABLE);

    // 启动定时器
    TIM_Cmd(TIM1, ENABLE);
}


void PWM_TIM1_CH1_LED()
{
	//1.定时器1时钟初始化使能 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
	//GPIO时钟配置
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	//重启定时器
	TIM_DeInit(TIM1);
	//GPIOE第9个成员 复用定时器2
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1);
	//复用模式：GPIO_Mode_AF   LED2
	GPIO_InitTypeDef beep_pwm_struct;
	beep_pwm_struct.GPIO_Mode = GPIO_Mode_AF;//复用模式
	beep_pwm_struct.GPIO_OType = GPIO_OType_PP;
	beep_pwm_struct.GPIO_Pin = GPIO_Pin_9;
	beep_pwm_struct.GPIO_Speed = GPIO_Speed_50MHz;
	beep_pwm_struct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOE,&beep_pwm_struct);
	//初始化定时器
	TIM_TimeBaseInitTypeDef tim1_struct;
	tim1_struct.TIM_CounterMode = TIM_CounterMode_Up;
	tim1_struct.TIM_Prescaler = 8400-1;  //0.1ms
	tim1_struct.TIM_Period = 100-1;
	tim1_struct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM1,&tim1_struct);
	//初始化通道3
	TIM_OCInitTypeDef TIM_OCInit_Struct;
	TIM_OCInit_Struct.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInit_Struct.TIM_OutputState = TIM_OutputState_Enable;//输出比较寄存器使能
	TIM_OCInit_Struct.TIM_OCNPolarity = TIM_OCPolarity_Low; //输出极性为低电平
	TIM_OCInit_Struct.TIM_Pulse = 100; //比较寄存器的值  占空比
	TIM_OC1Init(TIM1,&TIM_OCInit_Struct);
	
	//定时器1的通道 1的比较捕获寄存器使能
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	
	//TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Enable);
	//自动装载寄存器使能
	TIM_ARRPreloadConfig(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);
	//使能TIM1
	TIM_Cmd(TIM1,ENABLE);
	TIM_SetCompare1(TIM1,0);
}


static u16 last_pwm_value = 0; // 上次的PWM值
static const float alpha = 0.3; // 平滑系数，值越小变化越平缓

void Set_LedLight(u16 val)
{
    delay_ms(10);
    u16 pwm_value;

    if(val < 900)
    {
       // printf("光照过强\r\n");
        pwm_value = 0;
    }
    else if(val > 3500)
    {
        printf("光照过低\r\n");
        pwm_value = 100;
    }
    else
    {
        pwm_value = (val - 900) * 100 / (3500 - 900); // 线性映射
    }

    // 使用加权平均平滑 PWM 值
    pwm_value = (u16)((1 - alpha) * last_pwm_value + alpha * pwm_value);
    
    TIM_SetCompare1(TIM1, pwm_value);
    last_pwm_value = pwm_value; // 更新上次的 PWM 值

    delay_ms(10);
}

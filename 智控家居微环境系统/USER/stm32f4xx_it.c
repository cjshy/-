/**
  ******************************************************************************
  * @file    Project/STM32F4xx_StdPeriph_Templates/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    04-August-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
//#include "main.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
/*void SysTick_Handler(void)
{
  //TimingDelay_Decrement();
}*/

/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f4xx.s).                                               */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 
unsigned int key_flag =0;
unsigned int key2_flag =0;
unsigned int key3_flag =0;
unsigned int key4_flag =0;
void EXTI4_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line4))
	{
		//GPIO_ToggleBits(GPIOE,GPIO_Pin_8);
		//清楚中断位标志
		EXTI_ClearITPendingBit(EXTI_Line4);
		key_flag =1;
	}
}


void EXTI9_5_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line5))
	{
		//GPIO_ToggleBits(GPIOE,GPIO_Pin_9);
		//清楚中断位标志
		EXTI_ClearITPendingBit(EXTI_Line5);
		key2_flag = 1;
	}
	else if(EXTI_GetITStatus(EXTI_Line6))
	{
		//GPIO_ToggleBits(GPIOE,GPIO_Pin_10);
		//清楚中断位标志
		EXTI_ClearITPendingBit(EXTI_Line6);
		key3_flag = 1;
	}
}

void EXTI15_10_IRQHandler()
{
	if(EXTI_GetITStatus(EXTI_Line13))
	{
		//GPIO_ToggleBits(GPIOB,GPIO_Pin_10);
		EXTI_ClearITPendingBit(EXTI_Line13);
		key4_flag = 1;
		
	}
}

void TIM6_DAC_IRQHandler ()
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update) != RESET)
	{
		GPIO_ToggleBits(GPIOE,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10);
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	}
}
/*
void TIM4_IRQHandler ()
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update) != RESET)
	{
		GPIO_ToggleBits(GPIOE,GPIO_Pin_8);
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
	}
}*/

void TIM3_IRQHandler ()
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update) != RESET)
	{
		GPIO_ToggleBits(GPIOE,GPIO_Pin_9);
		TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	}
}

void TIM5_IRQHandler ()
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update) != RESET)
	{
		
		TIM_ClearITPendingBit(TIM5,TIM_IT_Update);
	}
}

u8 data;
void USART1_IRQHandler()
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET)
	{
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
}

#include "main.h"
int wifi_rec_flag =0; //wifi数据接收标志位
int wifi_work_flag =0; //wifi模块服务端工作标志位
u8 wifi_buf[1024] ={0};
int wifi_len =0;
void USART2_IRQHandler ()
{
	u8 res;
	u8 usart;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) == SET) //接收中断
	{
		 //清楚接收中断标志位
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);
		res = USART_ReceiveData(USART2);
		wifi_buf[wifi_len++] = res;
		USART_SendData(USART1,res);//直接打印到串口助手
		if(wifi_work_flag)
		{
			printf("res = %c  %d\r\n",res,res);
			switch(res)
			{
				case '7':
					GPIO_ResetBits(GPIOE,GPIO_Pin_8);
				break;
				case '2':
					GPIO_SetBits(GPIOE,GPIO_Pin_8);
				break;
				case '3':
					Fan_Run();//打开风扇
					break;
				case '4':
					Fan_Close();//关闭风扇
					break;
				case '5':
					Beep_Runs();//打开警报
					break;
				case '6':
					Beep_Close();//关闭警报
					break;
				default:
					break;
			}
		}
	}
	else if(USART_GetITStatus(USART2,USART_IT_IDLE) == SET)
	{
		usart = USART2->SR;
		usart = USART2->DR;
		if(wifi_rec_flag && strstr(wifi_buf,"CONNECT"))
		{
			wifi_work_flag =1;
		}
		wifi_len =0;
	}
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

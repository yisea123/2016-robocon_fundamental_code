#include "stm32f10x.h"
#include "stdio.h"
#include "RCC_Configuration.h"
#include "GPIO_Configuration.h"
#include "USART_Configuration.h"
#include "LED.h"



int main(void)
{
	vu16 i=0;
	vu16 Message=0;
	RCC_Configuration();
  GPIO_Configuration();
  USART_Configuration();
	LED_Configuration();
	
	while(1)
	{
		
//		if(USART_GetFlagStatus(USART2 , USART_IT_RXNE) == SET)
//		{
//		Message = USART_ReceiveData(USART2);
//		if(Message == '1')
//		{	//USART_SendData(USART2 , USART_ReceiveData(USART2));
//			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
//			
//			//for(i=0;i<500;i++);
//		}
//		if(Message == '2')
//		{	//USART_SendData(USART2 , USART_ReceiveData(USART2));
//			GPIO_ResetBits(GPIOB,GPIO_Pin_9);
//			
//			//for(i=0;i<500;i++);
//		}
//				if(Message == '3')
//		{	//USART_SendData(USART2 , USART_ReceiveData(USART2));
//			GPIO_SetBits(GPIOB,GPIO_Pin_8);
//			
//			//for(i=0;i<500;i++);
//		}
//				if(Message == '4')
//		{	//USART_SendData(USART2 , USART_ReceiveData(USART2));
//			GPIO_SetBits(GPIOB,GPIO_Pin_9);
//			
//			//for(i=0;i<500;i++);
//		}

//	}
	
  }

}


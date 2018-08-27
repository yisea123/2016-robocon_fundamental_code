#include "USART_Configuration.h"
#include "stm32f10x.h"

void USART_Configuration(void)
{
	NVIC_InitTypeDef  nvic;
	USART_InitTypeDef USART_InitStructure ;
	//USART_ClockInitTypeDef USART_ClockInitStructure ;
	USART_DeInit(USART2);
	USART_InitStructure.USART_BaudRate = 115200 ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx ;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b ;
	USART_Init(USART2 , &USART_InitStructure);
	USART_Init(USART2,&USART_InitStructure);
	USART_Cmd(USART2 , ENABLE);
	
	USART_ClearFlag (USART2,USART_IT_RXNE);
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
   
  nvic.NVIC_IRQChannel = USART2_IRQn;
  nvic.NVIC_IRQChannelPreemptionPriority = 0;
  nvic.NVIC_IRQChannelSubPriority = 0;
  nvic.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&nvic);
}

void USART2_IRQHandler(void)
{
		char Message = '0' ;
	 
 
		if(USART_GetFlagStatus(USART2 , USART_IT_RXNE) == SET)
		{
		Message = USART_ReceiveData(USART2);
		if(Message == '1')
		{	//USART_SendData(USART2 , USART_ReceiveData(USART2));
			GPIO_ResetBits(GPIOB,GPIO_Pin_8);
			
			//for(i=0;i<500;i++);
		}
		if(Message == '2')
		{	//USART_SendData(USART2 , USART_ReceiveData(USART2));
			GPIO_ResetBits(GPIOB,GPIO_Pin_9);
			
			//for(i=0;i<500;i++);
		}
				if(Message == '3')
		{	//USART_SendData(USART2 , USART_ReceiveData(USART2));
			GPIO_SetBits(GPIOB,GPIO_Pin_8);
			
			//for(i=0;i<500;i++);
		}
				if(Message == '4')
		{	//USART_SendData(USART2 , USART_ReceiveData(USART2));
			GPIO_SetBits(GPIOB,GPIO_Pin_9);
			
			//for(i=0;i<500;i++);
		}
	  }
		USART_ClearFlag (USART2,USART_IT_RXNE);	
}



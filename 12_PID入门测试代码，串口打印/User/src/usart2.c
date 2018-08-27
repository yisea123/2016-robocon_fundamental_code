#include "stm32f10x.h"
#include "usart2.h"

void Usart_Config(void)
{
	NVIC_InitTypeDef  nvic;
	USART_InitTypeDef USART_InitStructure ;
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA ,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);	

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA , &GPIO_InitStructure) ;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA , &GPIO_InitStructure) ;
	
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



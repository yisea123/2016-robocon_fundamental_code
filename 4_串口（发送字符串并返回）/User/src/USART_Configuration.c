#include "USART_Configuration.h"
#include "stm32f10x.h"


void USART2_Configuration(void)
{
    NVIC_InitTypeDef  nvic;
		USART_InitTypeDef usart;
    GPIO_InitTypeDef  gpio;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //GPIOA 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //USART2

		gpio.GPIO_Pin = GPIO_Pin_3;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&gpio);

    gpio.GPIO_Pin = GPIO_Pin_2;  
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&gpio);

		USART_DeInit(USART2);

    usart.USART_WordLength = USART_WordLength_8b;
    usart.USART_StopBits = USART_StopBits_1;
		usart.USART_BaudRate = 9600;				  //已被改动
    usart.USART_Parity = USART_Parity_No;
    usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   
    USART_Init(USART2,&usart);

		USART_ClearFlag (USART2,USART_IT_RXNE);				//清除中断标志
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);

		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
   
    nvic.NVIC_IRQChannel = USART2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

		USART_Cmd(USART2,ENABLE); 
}

 	u8 temp;
void USART2_IRQHandler(void)
{
 
 
	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)	//接收寄存器非空
	{
			USART_ClearFlag (USART2,USART_IT_RXNE);			//清除中断标志
			USART_ClearITPendingBit(USART2,USART_IT_RXNE);

			temp = USART_ReceiveData(USART2);
	 
	}	
}



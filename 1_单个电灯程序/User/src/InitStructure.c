#include "stm32f10x.h"

void InitStructure_LED(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);	


	//GPIO_ResetBits(GPIOA,GPIO_Pin_9); 
}



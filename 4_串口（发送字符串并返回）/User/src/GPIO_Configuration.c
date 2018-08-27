#include "GPIO_Configuration.h"
#include "stm32f10x.h"

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA , &GPIO_InitStructure) ;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING ;
	GPIO_Init(GPIOA , &GPIO_InitStructure) ;
}

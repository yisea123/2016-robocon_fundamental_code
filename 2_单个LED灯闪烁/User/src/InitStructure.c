#include "stm32f10x.h"

void LED_InitStructure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;		/* ????I?LED????GPIO????*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); /*??LED????GPIO??*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	   /*??I????LED????GPIO????*/

}
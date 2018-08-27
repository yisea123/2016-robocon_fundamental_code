#include "LED.h"
#include "stm32f10x.h"

void LED_Configuration(void)
{
  GPIO_InitTypeDef gpio;   
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);
		
	gpio.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;	
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);
	//GPIO_ResetBits(GPIOE,GPIO_Pin_2);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);

}
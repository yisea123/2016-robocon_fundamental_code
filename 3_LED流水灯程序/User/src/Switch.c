#include "stm32f10x.h"

void Turn_On_LED(u8 LED_NUM)
{
	switch(LED_NUM)
	{
		case 0:
			 GPIO_ResetBits(GPIOB,GPIO_Pin_8);  /*??DS5?*/
       break;
		
		case 1:
			 GPIO_ResetBits(GPIOB,GPIO_Pin_9);  /*??DS5?*/
       break;
		
		case 2:
			 GPIO_ResetBits(GPIOB,GPIO_Pin_3);  /*??DS5?*/
       break;
		
		default:
		   GPIO_ResetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9);
		   GPIO_ResetBits(GPIOB,GPIO_Pin_9);/*?????LED???*/
       break;
	}
}
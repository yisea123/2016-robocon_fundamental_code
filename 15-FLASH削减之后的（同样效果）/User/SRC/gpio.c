#include "main.h"

//  void Delay(vu32 nCount)
//{
//	for(; nCount != 0; nCount--);
//}
void gpio_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

/********   Ϊ�г̿������õ�io��  ����Ҫ�����֤  **************/	

	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9|GPIO_Pin_10; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
}




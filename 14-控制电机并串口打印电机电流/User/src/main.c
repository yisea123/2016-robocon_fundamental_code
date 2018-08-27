#include "stm32f10x.h"
#include "ad.h"
#include "usart.h"
#include "pwm.h"
#include "stdio.h"


void Delay(vu32 nCount);
int main(void)
{
	TIM1_Init();
	ADC_Configuration();
	USART_Configuration();
	//GPIO_SetBits(GPIOB , GPIO_Pin_14);
  //GPIO_ResetBits(GPIOB , GPIO_Pin_12);
	while(1)
	{		
     // printf(" %f \n ", Real_Current);
  		//Delay(0x2FFFFF);		
	}
}

void Delay(vu32 nCount)
{
	for(; nCount != 0; nCount--);
}


//int fputc(int ch, FILE *f)
//{
//   USART_SendData(USART2, (unsigned char) ch);
//   while (USART_GetFlagStatus(USART2 , USART_FLAG_TC) == RESET);
//   return (ch);
//}

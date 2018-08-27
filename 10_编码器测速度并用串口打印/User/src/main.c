#include "stm32f10x.h"
#include "encoder.h"
#include "time.h"
#include "usart.h"
#include "pwm.h"
#include "stdio.h"
#include "stdlib.h"

void Delay(vu32 nCount);

int main(void)
{
	USART_Configuration( );
	TIM1_Init();
	TIM2_Configuration( );
	Encoder_Configuration();
	GPIO_ResetBits(GPIOB , GPIO_Pin_12);
  GPIO_SetBits(GPIOB , GPIO_Pin_14);
	
	while(1)
	{
		
		if(USART_GetFlagStatus(USART2 , USART_IT_RXNE) != SET)
		{
			printf(" %d\n " , speed );
			Delay(0x2FFFFF);		
		}


	}
}



void Delay(vu32 nCount)
{
	for(; nCount != 0; nCount--);
}



int fputc(int ch, FILE *f)
{
   USART_SendData(USART2, (unsigned char) ch);
   while (USART_GetFlagStatus(USART2 , USART_FLAG_TC) == RESET);
   return (ch);
}






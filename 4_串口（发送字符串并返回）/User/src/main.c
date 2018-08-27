#include "stm32f10x.h"
#include "stdio.h"
#include "RCC_Configuration.h"
#include "GPIO_Configuration.h"
#include "USART_Configuration.h"


	u8 value = 0;
int main(void)
{
	vu16 i=0;
 
	RCC_Configuration();
  GPIO_Configuration();
//  USART_Configuration();
	USART2_Configuration();
	while(1)
	{
//		if(USART_GetFlagStatus(USART2 , USART_IT_RXNE) == SET)
//		{
//			value = USART_ReceiveData(USART2) ;
////			USART_SendData(USART2 , value );
////			//printf(" 213 \n ");
////			for(i=0;i<500;i++);
//		}
	}
	
}


//int fputc(int ch, FILE *f)
//{
//   USART_SendData(USART2, (unsigned char) ch);
//   while (USART_GetFlagStatus(USART2 , USART_FLAG_TC) == RESET);
//   return (ch);
//}

//int SendChar (int ch) 
//{
//while (!(USART2->SR & USART_FLAG_TXE));
//  USART2->DR = (ch & 0x1FF);           // USART1 ???????????? 
//	return (ch); 
//	
//}

//int GetKey (void)
// { 
// while (!(USART2->SR & USART_FLAG_RXNE));
// return ((int)(USART2->DR & 0x1FF)); 
// } 


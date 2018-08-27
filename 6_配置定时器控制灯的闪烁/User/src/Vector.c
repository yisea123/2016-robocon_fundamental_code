#include "stm32f10x.h"

extern vu16 CCR1_Val;
extern vu16 CCR2_Val;

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2 ,  TIM_IT_Update) != RESET)
	{
		GPIO_WriteBit(GPIOB , GPIO_Pin_8 ,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOB , GPIO_Pin_8)));
		TIM_ClearITPendingBit(TIM2 ,  TIM_IT_Update);
	}
//		if(TIM_GetITStatus(TIM2 , TIM_IT_CC2) != RESET)
//	{
//		GPIO_WriteBit(GPIOB , GPIO_Pin_9 ,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOB , GPIO_Pin_9)));
//		TIM_ClearITPendingBit(TIM2 , TIM_IT_CC2);
//	}

}
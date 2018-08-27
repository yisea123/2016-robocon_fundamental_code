#include "stm32f10x.h"
#include "time.h"
#include "encoder.h"
#include "usart.h"
//#include "stdio.h"
int  speed  = 0;

void TIM2_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  tim;
	NVIC_InitTypeDef         nvic;

	TIM2_Dis();

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

	nvic.NVIC_IRQChannel = TIM2_IRQn;
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);

	tim.TIM_Prescaler = 9 - 1;    
	tim.TIM_CounterMode = TIM_CounterMode_Up;
	tim.TIM_ClockDivision = TIM_CKD_DIV1;
	tim.TIM_Period = 1000 - 1;				//  
	TIM_TimeBaseInit(TIM2,&tim);
	TIM2_Start();
}

void TIM2_Dis()
{
	TIM_ITConfig(TIM2 , TIM_IT_Update , DISABLE) ;
	TIM_ClearFlag(TIM2 , TIM_FLAG_Update) ; 
	TIM_Cmd(TIM2 , DISABLE) ;
}

void TIM2_Start()
{
	TIM_Cmd(TIM2 , ENABLE) ;
	TIM_ITConfig(TIM2 , TIM_IT_Update , ENABLE) ;
	TIM_ClearFlag(TIM2 , TIM_FLAG_Update) ; 
	TIM2->CNT = 0;
}

void TIM2_IRQHandler()
{
	static int pwm_value = 0;
	if(TIM_GetITStatus(TIM2 , TIM_IT_Update) != RESET)
	{
		TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		pwm_value = Encoder_Get_CNT();
		speed = CountRealSpeed(pwm_value);			
	}
}






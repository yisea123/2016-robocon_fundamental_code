#include "main.h"

int ecorder_resolution_ratio = 500;

void TIM2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  tim;
    NVIC_InitTypeDef         nvic;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    nvic.NVIC_IRQChannel = TIM2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 2;
    nvic.NVIC_IRQChannelSubPriority = 1;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

    tim.TIM_Prescaler = 36-1;    //APB1 is 36MHz?
    tim.TIM_CounterMode = TIM_CounterMode_Up;
    tim.TIM_ClockDivision = TIM_CKD_DIV1;
    tim.TIM_Period = 4000;      //     2ms
	
    TIM_TimeBaseInit(TIM2,&tim);
	
		TIM2_Start();
}

void TIM2_Start(void)
{
    TIM_Cmd(TIM2, ENABLE);	 
    TIM_ITConfig(TIM2, TIM_IT_Update,ENABLE);
    TIM_ClearFlag(TIM2, TIM_FLAG_Update);	
}

void TIM2_IRQHandler(void)
{
		int encoder_get = 0;

		if (TIM_GetITStatus(TIM2,TIM_IT_Update)!= RESET) 
		{
				TIM_ClearFlag(TIM2, TIM_FLAG_Update);
		
				encoder_get = Encoder_Get_CNT();		//获取编码器增量				
				Real_Speed = encoder_get*7500/ecorder_resolution_ratio;		//更新转速  转每分钟    //所乘系数对应500线编码器 即Real_Speed = encoder_get * 15
				Real_Location += encoder_get;  			//更新位置
			
				LocationPID_flag = 1;
				SpeedPID_flag = 1;

		 }
}




#include "stm32f10x.h"
#include "message.h"

void InitStructure_Message(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;		/* ????I?LED????GPIO????*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); /*??LED????GPIO??*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	   /*??I????LED????GPIO????*/

	GPIO_ResetBits(GPIOB , GPIO_Pin_8);	 /* ??LED? */	
}

//#include "stm32f10x.h"
//#include "message.h"

//void InitStructure_Message()
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	GPIO_InitTypeDef GPIO_InitStructure;
//	TIM_OCInitTypeDef  TIM_OCInitStructure;
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
//	//GPIO_InitTypeDef GPIO_InitStructure;
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
//  GPIO_Init(GPIOB, &GPIO_InitStructure);
////	GPIO_SetBits(GPIOB , GPIO_Pin_12);
////	GPIO_SetBits(GPIOB , GPIO_Pin_14);
//		 
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
//	//TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//  TIM_TimeBaseStructure.TIM_Prescaler = 0;    
//	TIM_TimeBaseStructure.TIM_Period = 6000 ; 
//  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;//TIM_CKD_DIV1;	  
//  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

//	//TIM_OCInitTypeDef  TIM_OCInitStructure;
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;        
//  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
//	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
//  TIM_OCInitStructure.TIM_Pulse = 2000 ;     
//  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
//  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
//  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
//  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;	
//  TIM_OC3Init(TIM4 , &TIM_OCInitStructure);
//  TIM_OC3PreloadConfig(TIM4 , TIM_OCPreload_Enable);
//  TIM_ARRPreloadConfig(TIM4 , ENABLE);   
//	TIM_CtrlPWMOutputs(TIM4 , ENABLE);
//	TIM_Cmd(TIM4 , ENABLE);	
//	
//}






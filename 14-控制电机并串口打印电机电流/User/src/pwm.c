#include "stm32f10x.h"
#include "pwm.h"

void GPIO_Initstruture(void);
void TIM1_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 , ENABLE);
	//TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_TimeBaseStructure.TIM_Prescaler = 0;    
	TIM_TimeBaseStructure.TIM_Period = 60000 ; 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;//TIM_CKD_DIV1;	  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	//TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;        
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0 ;//         
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;	
  TIM_OC1Init(TIM1 , &TIM_OCInitStructure);
  TIM_OC1PreloadConfig(TIM1 , TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM1 , ENABLE);   
	TIM_CtrlPWMOutputs(TIM1 , ENABLE);
	TIM_Cmd(TIM1 , ENABLE);	
	GPIO_Initstruture();
}

void GPIO_Initstruture(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB , ENABLE);
	//GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_14;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB , GPIO_Pin_12);
	GPIO_SetBits(GPIOB , GPIO_Pin_14);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}


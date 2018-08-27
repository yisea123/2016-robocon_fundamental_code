#include "stm32f10x.h"

u16 CCR1_Val = 10000 ;
void RCC_Configuration(void);
void GPIO_Configuration(void);
void TIM4_Configuration(void);
void Delay(vu32 nCount);

int main(void)
{
#ifdef DEBUG
  debug();
#endif

	//u8 led_fx=1;

  RCC_Configuration();
  GPIO_Configuration();
  TIM4_Configuration();
	CCR1_Val = 0;

 while(1)
      {
				CCR1_Val += 50;
				Delay(160000);
				if(CCR1_Val == 60000)
					CCR1_Val = 0;
			}
		
    
}
 
void RCC_Configuration(void)
{

	SystemInit();
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4 , ENABLE);
}
 
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}
 
void TIM4_Configuration(void)
{
	//u16 CCR1_Val   ; 
		
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;//
  TIM_TimeBaseStructure.TIM_Prescaler = 0;  //ÆµÂÊÎª   
	TIM_TimeBaseStructure.TIM_Period = 60000; 
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;//TIM_CKD_DIV1;	  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;        
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
  TIM_OCInitStructure.TIM_Pulse = CCR1_Val  ;//         
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;  
  TIM_OC3Init(TIM4, &TIM_OCInitStructure);
  TIM_OC3PreloadConfig(TIM4 , TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM4 , ENABLE);   
	TIM_CtrlPWMOutputs(TIM4, ENABLE);
	TIM_Cmd(TIM4 , ENABLE);	

}

void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}






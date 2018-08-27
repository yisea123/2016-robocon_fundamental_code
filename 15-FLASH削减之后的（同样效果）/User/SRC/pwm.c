#include "main.h"

//PWM----PA8(TIM1_CH1)
//INH----PA9
//INL----PA10

#define abs(x) ((x)>0? (x):(-(x)))

double location_init_speed = 800;                         //寻零是速度选择，设定为4000r/m

/*************************************************************************
                              PWM初始化       
*************************************************************************/
void PWM_Configuration(void)
{
	TIM_TimeBaseInitTypeDef  tim;
	TIM_OCInitTypeDef        oc;
	GPIO_InitTypeDef         gpio;
    
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA |  RCC_APB2Periph_TIM1, ENABLE);
                           
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);		

 	gpio.GPIO_Pin = GPIO_Pin_8;
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);
    
  gpio.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_12;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &gpio);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_14);                     
  GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    
	tim.TIM_Period=5000;				//14.4KHz	       
	tim.TIM_Prescaler=0;             
	tim.TIM_ClockDivision=TIM_CKD_DIV1;
	tim.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1, &tim);
	
	oc.TIM_OCMode = TIM_OCMode_PWM2;
	oc.TIM_OutputState = TIM_OutputState_Enable;
	oc.TIM_OutputNState = TIM_OutputNState_Disable;
	oc.TIM_Pulse = 0;
	oc.TIM_OCPolarity = TIM_OCPolarity_Low;
	oc.TIM_OCNPolarity = TIM_OCPolarity_High;
	oc.TIM_OCIdleState = TIM_OCIdleState_Reset;
	oc.TIM_OCNIdleState = TIM_OCIdleState_Reset;
	TIM_OC1Init(TIM1, &oc);

	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1,ENABLE);   
	TIM_Cmd(TIM1, ENABLE);
}

/*************************************************************************
                                PWM设置
传入参数： int give_pulse      给定占空比         
传入参数： int max_pulse       限定最大的占空比             
*************************************************************************/
void Motor_PWM_Run(int give_pulse,int max_pulse)
{
    max_pulse = abs(max_pulse);
	
		#ifdef __DEBUG2
		give_pulse = abs(give_pulse);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		#endif	
    
    if(give_pulse < 0)
    {
			GPIO_ResetBits(GPIOB,GPIO_Pin_14);
			GPIO_SetBits(GPIOB,GPIO_Pin_12);
			if(give_pulse < (-max_pulse))
			{
				give_pulse = (-max_pulse);
			}
    }
    else 
    {
			GPIO_SetBits(GPIOB,GPIO_Pin_14);
			GPIO_ResetBits(GPIOB,GPIO_Pin_12);
			if(give_pulse > max_pulse)
			{
				give_pulse = max_pulse;
			}
    }												  
    TIM1->CCR1 = abs(give_pulse);

}



void Motor_Free(void)
{
	TIM1->CCR1 = 0;
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);		
}


void Motor_Break(void)
{
	TIM1->CCR1 = 5000;
	GPIO_ResetBits(GPIOB,GPIO_Pin_14);
	GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}


/****************************************************
初始化寻零配置

*****************************************************/
//void location_init(void)
//{
//	MotorMode = LOCATIONMODE;
//	Want_Speed = location_init_speed;
//}











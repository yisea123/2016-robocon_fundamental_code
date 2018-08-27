#include "stm32f10x.h"
#include "encoder.h"

void Encoder_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 , ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA , &GPIO_InitStructure);

	TIM_EncoderInterfaceConfig(TIM3 , TIM_EncoderMode_TI12 , TIM_ICPolarity_Falling , TIM_ICPolarity_Falling);
	TIM_Cmd(TIM3 , ENABLE);	

	Encoder_Start();

}

void Encoder_Start(void)
{
	TIM3->CNT = 32767;
}

float Encoder_Get_CNT(void)
{
	float cnt = 0;
	cnt = 32767 - (TIM3->CNT);
	TIM3->CNT = 32767 ;
	return cnt;
}

int CountRealSpeed(int delat_CNT)
{
	return delat_CNT * 15.0 ;
}








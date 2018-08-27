#include "main.h"

//encoder.INPUT_A---PB6(TIM4_CH1)
//encoder.INPUT_B---PB7(TIM4_CH2)

void Encoder_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(GPIOA , &GPIO_InitStructure); 

    TIM_EncoderInterfaceConfig(TIM3 , TIM_EncoderMode_TI12 , TIM_ICPolarity_Falling , TIM_ICPolarity_Falling);
    TIM_Cmd(TIM3,ENABLE);	

		Encoder_Start();
}

void Encoder_Start(void)
{
    TIM3->CNT = 0x7fff;
}

int Encoder_Get_CNT(void)
{
    int cnt = 0;
    static unsigned char first_flag = 0;
    
    if(first_flag == 0)
    {
        first_flag = 1;
        return 0;
    }
    
    cnt =0x7fff-(TIM3->CNT);
    TIM3->CNT = 0x7fff;
    return cnt;		
}



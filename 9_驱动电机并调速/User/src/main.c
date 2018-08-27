#include "stm32f10x.h"
#include "PWM.h"
#include "GPIO.h"

int main(void)
{
	GPIO_Initstruture( );
	TIM1_Init();
	//GPIO_SetBits(GPIOB , GPIO_Pin_12);
	//GPIO_ResetBits(GPIOB , GPIO_Pin_14);

	while(1)
	{
	GPIO_ResetBits(GPIOB , GPIO_Pin_12);
	GPIO_SetBits(GPIOB , GPIO_Pin_14);
	}
}





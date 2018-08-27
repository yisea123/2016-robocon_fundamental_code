#include "stm32f10x.h"
#include "InitStructure.h"
#include "Delay.h"

int main(void)
{
  LED_InitStructure();
	while(1)
	{
		  GPIO_SetBits(GPIOB,GPIO_Pin_2);             /* ??LED??? */
			Delay(0x2FFFFF);
			GPIO_ResetBits(GPIOB,GPIO_Pin_2);		   	/* ??LED??? */
			Delay(0x2FFFFF);	
	}
}

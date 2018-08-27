#include "stm32f10x.h"
#include "InitStructure.h" 
#include "Delay.h" 
#include "Switch.h" 

int main(void)
{
	u8 count=0;
  LED_InitStructure( );
		
	while(1)
	{
		for(count=0;count<3;count++)
		{			
			GPIO_SetBits(GPIOB,GPIO_Pin_8 | GPIO_Pin_9);             /* ????GPIOA???LED??? */
			GPIO_SetBits(GPIOB,GPIO_Pin_8); 
			Turn_On_LED(count);
			Delay(0x2FFFFF);
		}
	}
}

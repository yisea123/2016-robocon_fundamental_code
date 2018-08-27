#include "stm32f10x.h"
#include "InitStructure.h"

int main(void)
{
	
	InitStructure_LED();
	
	while(1)
	{
		GPIO_SetBits(GPIOB , GPIO_Pin_10);
	}
}




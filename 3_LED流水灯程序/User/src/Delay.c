#include "stm32f10x.h"

void Delay(vu32 nCount)
{
	for(; nCount != 0; nCount--);
}

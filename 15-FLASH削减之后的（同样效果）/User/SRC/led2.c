#include "main.h"

//LED----PC15, '0' is ON,'1' is OFF

void LED_Configuration(void)
{
		GPIO_InitTypeDef gpio;   

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
			
		gpio.GPIO_Pin = GPIO_Pin_9 ;	
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &gpio);                   //CAN �Լ�ɹ�ָʾ��
		LED_OFF();
		
		gpio.GPIO_Pin = GPIO_Pin_8 ;	            // �����Ϊ�������ر�־
		gpio.GPIO_Mode = GPIO_Mode_Out_PP;
		gpio.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &gpio);
		TEST_LED_OFF();                                      
	
}
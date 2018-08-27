#include "stm32f10x.h"
#include "stdio.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);
void USART_Configuration(void);
void ADC_Configuration(void);


int main(void)
{
	float VolValue = 0.00;
	u32 ticks = 0;
	
  RCC_Configuration( );
  GPIO_Configuration( );
  USART_Configuration( );
  ADC_Configuration( );
	printf("\r\n The AD_value is:                        \r\n");
	
	while(1)
	{
		if(ticks++ >= 2000000)
		{
			ticks = 0;
			VolValue = 2.56 * ADC_GetConversionValue(ADC1)/0X0FFF;
			printf("The current VolValue = %.2fv\r\n" , VolValue);
		}
	}
}

void RCC_Configuration(void)
{
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA | RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB , ENABLE);
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_USART2 , ENABLE) ;	
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure ;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA , &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN ;
	GPIO_Init(GPIOB , &GPIO_InitStructure);
}

	void USART_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure ;
	USART_InitStructure.USART_BaudRate = 115200 ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None ;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx ;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_StopBits = USART_StopBits_1 ;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b ;
	USART_Init(USART2 , &USART_InitStructure);
	USART_Cmd(USART2 , ENABLE);
}

void ADC_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE ;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE ;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right ;
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	ADC_Init(ADC1 , &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1 , ADC_Channel_8 , 1 , ADC_SampleTime_55Cycles5);
	ADC_Cmd(ADC1 , ENABLE);
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));
	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));
	ADC_SoftwareStartConvCmd(ADC1 , ENABLE);
	
}




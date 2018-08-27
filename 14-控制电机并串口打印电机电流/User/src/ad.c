#include "stm32f10x.h"
#include "stdio.h"
#include "ad.h"
#define ADC1_DR_Address    ((u32)0x4001244C)
u16 ADC_ConvertedValue[55];

float Real_Current=0; 
float base_current = 0;
float Current_temp1 = 0;
float Current_temp2 = 0;
float Current_temp3 = 0;
float Current_temp4 = 0;
float Current_temp5 = 0;
float Current_temp6 = 0;

/**************************************
          偏置电流检测
**************************************/

int base_current_count1 = 0;
int base_current_count2 = 1667;                     //（1667*250） us
int base_current_flag = 0;
float base_current_temp = 0;

void ADC_Configuration(void)
{
    GPIO_InitTypeDef         	gpio;
		ADC_InitTypeDef          	adc;
		NVIC_InitTypeDef  				nvic;
    DMA_InitTypeDef          	dma;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_GPIOB, ENABLE); 
  


		gpio.GPIO_Pin = GPIO_Pin_0;
    gpio.GPIO_Mode = GPIO_Mode_AIN;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&gpio);
			
			
    DMA_DeInit(DMA1_Channel1);
    dma.DMA_PeripheralBaseAddr = ADC1_DR_Address;
    dma.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;
    dma.DMA_DIR = DMA_DIR_PeripheralSRC;
    dma.DMA_BufferSize =55;
    dma.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    dma.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    dma.DMA_Mode = DMA_Mode_Circular;
    dma.DMA_Priority = DMA_Priority_High;
    dma.DMA_M2M = DMA_M2M_Disable;
    DMA_Init(DMA1_Channel1, &dma);   		
		DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
		
		nvic.NVIC_IRQChannel = DMA1_Channel1_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 2;
    nvic.NVIC_IRQChannelSubPriority = 2;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);
		
		DMA_Cmd(DMA1_Channel1, ENABLE);
    
    adc.ADC_Mode = ADC_Mode_Independent;	 	//ADC1与ADC2独立            
    adc.ADC_ScanConvMode = DISABLE;			   	//多通道扫描  ****改动 单通道       
    adc.ADC_ContinuousConvMode = ENABLE;		//连续扫描              
    adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;  
    adc.ADC_DataAlign = ADC_DataAlign_Right;
    adc.ADC_NbrOfChannel = 1;					  // *******改动  一个通道
    ADC_Init(ADC1, &adc);
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);			//72M/8=9MHz	//总的转换时间4.56us     
    ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_28Cycles5);         //  通道要改
//		ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_28Cycles5);	  
    ADC_DMACmd(ADC1, ENABLE);

    ADC_Cmd(ADC1, ENABLE);
  	ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
		
}

float ADC_Filter(void)
{

		int sum = 0;
    int adc_i = 0;

		
	    for(adc_i=0;adc_i<55;adc_i++)                        														 //250.8us
    { 
			if((GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14) == Bit_SET) && (GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12) == Bit_RESET))
			sum += ADC_ConvertedValue[adc_i];
			else
			sum -= ADC_ConvertedValue[adc_i];
   }
    return (float)((sum/55));
}

void DMA1_Channel1_IRQHandler()
{

		if(DMA_GetITStatus(DMA1_IT_TC1) == SET)
    {
				
        DMA_ClearFlag(DMA1_FLAG_TC1);
        DMA_ClearITPendingBit(DMA1_IT_TC1);
			
				Current_temp6 = Current_temp5;
				Current_temp5 = Current_temp4;
				Current_temp4 = Current_temp3;
				Current_temp3 = Current_temp2;
				Current_temp2 = Current_temp1;
				Current_temp1 = ADC_Filter();
//				Current_temp1 = (Current_temp1 + Current_temp2 + Current_temp3 + Current_temp4 + Current_temp5)/5;

				Real_Current=(float)(((Current_temp1)*3300/(4096*0.40)) - base_current);				  //系数需要标定
//					Real_Current=(float)((ADC_Filter())*3300/(4096));	               //  检测电压 
//				CurrentPID_flag=1;	//main中进行电流PID		
//				LED_TOGGLE();
				if(base_current_flag == 0)
					{
						base_current_count1 ++;                               //
						base_current_temp += Real_Current;
						if(base_current_count1 >= base_current_count2)                                //
						{
							base_current_flag =1;
							base_current = base_current_temp/base_current_count1;
						}
					}
					printf(" %f \n ",Real_Current);
    }
}

int fputc(int ch, FILE *f)
{
   USART_SendData(USART2, (unsigned char) ch);
   while (USART_GetFlagStatus(USART2 , USART_FLAG_TC) == RESET);
   return (ch);
}


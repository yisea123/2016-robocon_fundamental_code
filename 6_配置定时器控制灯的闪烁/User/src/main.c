//#include "stm32f10x.h"

//vu16 CCR1_Val = 40000 ;
//vu16 CCR2_Val = 20000 ;

//void RCC_Configuration(void);
//void GPIO_Configuration(void);
//void NVIC_Configuration(void);
//void TIM_Configuration(void);

//int main(void)
//{
//	RCC_Configuration( );
//  GPIO_Configuration( );
//  NVIC_Configuration( );
//  TIM_Configuration( );
//	
//	TIM_Cmd(TIM2 , ENABLE);
//	while(1)
//	{
//	}
//}

//void RCC_Configuration(void)
//{
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
//}

//void GPIO_Configuration(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB , &GPIO_InitStructure);
//}

//void TIM_Configuration(void)
//{
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	TIM_TimeBaseStructure.TIM_Period = 65535 ;
//	TIM_TimeBaseStructure.TIM_Prescaler = 0 ; 
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseInit(TIM2 , &TIM_TimeBaseStructure);
//	TIM_PrescalerConfig(TIM2 , 7199 , TIM_PSCReloadMode_Immediate);
//	
////	TIM_OCInitTypeDef TIM_OCInitStructure;
////	TIM_OCInitStructure.TIM_OCMode = TIM_OutputState_Enable ;
////	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
////	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
////	TIM_OC1Init(TIM2 , &TIM_OCInitStructure);
////	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
////	TIM_OC2Init(TIM2 , &TIM_OCInitStructure);
////	TIM_OC1PreloadConfig(TIM2 , TIM_OCPreload_Disable);
////	TIM_OC2PreloadConfig(TIM2 , TIM_OCPreload_Disable);
//	TIM_ARRPreloadConfig(TIM2, DISABLE);
//	TIM_ITConfig(TIM2 , TIM_IT_CC1 | TIM_IT_CC2 , ENABLE);
//}

//void NVIC_Configuration(void)
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	#ifdef VECT_TAB_RAM
//	NVIC_SetVectorTable(NVIC_VectTab_RAM , 0x0);
//	#else
//	NVIC_SetVectorTable(NVIC_VectTab_FLASH , 0x0);
//	#endif
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn ; //"TIM2_IRQChannel" is undeclared
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0 ;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE ;
//	NVIC_Init(&NVIC_InitStructure);
//}






#include "stm32f10x.h"

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void GPIO_Configuration(void);
void TIM2_Configuration(void);
void Delay(vu32 nCount);

/*******************************************************************************
* Function Name  : main
* Description    : Main program.
* Input          : None
* Return         : None
*******************************************************************************/
int main(void)
{
#ifdef DEBUG
  debug();
#endif
  
  /* Configure the system clocks */
  RCC_Configuration();
    
  /* NVIC Configuration */
  NVIC_Configuration();
  
  /* Configure the GPIO ports */
  GPIO_Configuration();

  /* Configure the TIM2 */
  TIM2_Configuration();
  
  TIM_Cmd(TIM2, ENABLE);	//?????2
  
  /* Infinite loop */
  while (1)
  {    
  }
}

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Return         : None
*******************************************************************************/
void RCC_Configuration(void)
{
//  ErrorStatus HSEStartUpStatus; 
//  
//  /* RCC system reset(for debug purpose) */
//  RCC_DeInit();

//  /* Enable HSE */
//  RCC_HSEConfig(RCC_HSE_ON);

//  /* Wait till HSE is ready */
//  HSEStartUpStatus = RCC_WaitForHSEStartUp();

//  if (HSEStartUpStatus == SUCCESS)
//  {
//    /* Enable Prefetch Buffer */
//    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

//    /* Flash 2 wait state */
//    FLASH_SetLatency(FLASH_Latency_2);

//    /* HCLK = SYSCLK */
//    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
//  
//    /* PCLK2 = HCLK */
//    RCC_PCLK2Config(RCC_HCLK_Div1); 

//    /* PCLK1 = HCLK/2 */
//    RCC_PCLK1Config(RCC_HCLK_Div2);

//    /* PLLCLK = 8MHz * 9 = 72 MHz */
//    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

//    /* Enable PLL */ 
//    RCC_PLLCmd(ENABLE);

//    /* Wait till PLL is ready */
//    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) {}

//    /* Select PLL as system clock source */
//    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

//    /* Wait till PLL is used as system clock source */
//    while(RCC_GetSYSCLKSource() != 0x08) {}
//  }
  
  /* Enable GPIOC clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  
  /* Enable TIM2 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
}

/*******************************************************************************
* Function Name  : NVIC_Configuration
* Description    : Configures Vector Table base location.
* Input          : None
* Return         : None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
#ifdef  VECT_TAB_RAM  
  /* Set the Vector Table base location at 0x20000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
  /* Set the Vector Table base location at 0x08000000 */ 
  NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
#endif
  
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
  /* Enable the EXTI9_5 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  /* Configure PC.06 as Output push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : TIM2_Configuration
* Description    : ?1?????????(????????).
* Input          : None
* Return         : None
*******************************************************************************/
void TIM2_Configuration(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  //???Timer??????
  TIM_DeInit(TIM2);
  
  //???????TIM2?????
  TIM_InternalClockConfig(TIM2);
  
  //??????36000-1,????????72MHz/36000 = 2kHz
  TIM_TimeBaseStructure.TIM_Prescaler = 36000;
  
  //??????
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  
  //??????????????
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  
  //????????,??2000???????????
  TIM_TimeBaseStructure.TIM_Period = 2000;
  
  //??????TIM2?
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  //????????
  TIM_ClearFlag(TIM2, TIM_FLAG_Update);
  
  //??ARR??????
  TIM_ARRPreloadConfig(TIM2 , DISABLE);  //???????????????????? 
  
  //??TIM2???
  TIM_ITConfig(TIM2, TIM_IT_Update , ENABLE);
}

/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nCount: specifies the delay time length.
* Return         : None
*******************************************************************************/
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

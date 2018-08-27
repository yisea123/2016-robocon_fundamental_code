#include "main.h"



void USART2_Configuration(void)
{
    NVIC_InitTypeDef  nvic;
		USART_InitTypeDef usart;
    GPIO_InitTypeDef  gpio;

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //GPIOA 
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE); //USART2

		gpio.GPIO_Pin = GPIO_Pin_3;
    gpio.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&gpio);

    gpio.GPIO_Pin = GPIO_Pin_2;  
    gpio.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&gpio);

		USART_DeInit(USART2);

    usart.USART_WordLength = USART_WordLength_8b;
    usart.USART_StopBits = USART_StopBits_1;
		usart.USART_BaudRate = 115200;				  //已被改动
    usart.USART_Parity = USART_Parity_No;
    usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   
    USART_Init(USART2,&usart);

		USART_ClearFlag (USART2,USART_IT_RXNE);				//清除中断标志
		USART_ClearITPendingBit(USART2,USART_IT_RXNE);

		USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
   
    nvic.NVIC_IRQChannel = USART2_IRQn;
    nvic.NVIC_IRQChannelPreemptionPriority = 0;
    nvic.NVIC_IRQChannelSubPriority = 0;
    nvic.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic);

		USART_Cmd(USART2,ENABLE); 
}

void USART2_SendChar(char b)
{
    while( USART_GetFlagStatus(USART2,USART_FLAG_TC) == RESET);
	USART_SendData(USART2,b);
	
}

int fputc(int ch, FILE *f)
{
    while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET);
    USART_SendData(USART2, (uint8_t)ch);
    return ch;
}

u8 USART_RX_BUF[32];     //接收缓冲,最大32个字节.

//接收状态
//bit7，接收完成标志
//bit6，接收开始标志
//bit5，接收到0x0d
//bit4~0，接收到的有效字节数目
u8 USART_RX_STA=0;       //接收状态标记	*****已为我所改动，因为pid——flash输入位数不够
u16 temp5;
//void USART2_IRQHandler(void)
//{
//	u8 temp;
//	int	 temp1;
//	int temp2;
//	double temp3;

//	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)	//接收寄存器非空
//	{
//			USART_ClearFlag (USART2,USART_IT_RXNE);			//清除中断标志
//			USART_ClearITPendingBit(USART2,USART_IT_RXNE);

//			temp = USART_ReceiveData(USART2);
//			if((USART_RX_STA&0x40)!=0)//接收已经开始
//			{			
//				if((USART_RX_STA&0x80)==0)//接收未完成
//				{
//					if(USART_RX_STA&0x20)//已接收到了0x0d
//					{
//						if(temp!=0x0a)
//							USART_RX_STA=0;//接收错误,重新开始
//						else 				
//								USART_RX_STA|=0x80;	//接收完成了														
//					}
//					else //还没收到0X0D
//					{	
//						if(temp==0x0d)
//							USART_RX_STA|=0x20;
//						else
//						{
//							USART_RX_BUF[USART_RX_STA&0X2F]=temp;
//							USART_RX_STA++;								   //已被我改动
//							if((USART_RX_STA&0X2F)>31)USART_RX_STA=0;//接收数据错误,重新开始接收	  
//						}		 
//					}
//				}  		
//			}
//			else if(temp=='#')		//接收到包头
//				USART_RX_STA|=0x40;	
//			
//			if((USART_RX_STA&0x80)!=0)			//接收已经完成，立即处理指令
//			{
//				if(USART_RX_BUF[0]=='W')			//USART_flash 写入pid参数
//			  {	
//					if(USART_RX_BUF[1]=='F')
//					{
//						flash_first_flag = 0x01;
//						Flash_Write();
//					}
//					
//					if(USART_RX_BUF[1]=='S')
//					Flash_Write_all();
//					if(USART_RX_BUF[1]=='A')
//					{
//						flash_first_flag = 0x00;
//						Flash_Write();
//					}			
//			  }
//			  else if(USART_RX_BUF[0]=='R')			   //flash_usart 读出并设置pid
//			  {
//					if(USART_RX_BUF[1]=='C')
//					Flash_Read_check();
//					if(USART_RX_BUF[1]=='A')
//					Flash_Read_all();
//			  }
//				else if(USART_RX_BUF[0] == 's' || USART_RX_BUF[0] == 'L' || USART_RX_BUF[0] == 'T')
//				{
//					if(USART_RX_BUF[1] == 'P' || USART_RX_BUF[1] == 'I' || USART_RX_BUF[1] == 'D')
//					{
//						switch(USART_RX_STA&0x1F)
//						{
//							case 3:
//								temp3 = (USART_RX_BUF[2] - 0x30)*0.01; 
//							case 4:
//								temp3 = (USART_RX_BUF[2] - 0x30)*0.1 + (USART_RX_BUF[3] - 0x30)*0.01; 
//								break;
//							case 5:
//								temp3 = (USART_RX_BUF[2] - 0x30) + (USART_RX_BUF[3] - 0x30)*0.1 + (USART_RX_BUF[4] - 0x30)*0.01; 
//								break;
//							case 6:
//								temp3 = (USART_RX_BUF[2] - 0x30)*10 + (USART_RX_BUF[3] - 0x30) + (USART_RX_BUF[4] - 0x30)*0.1 
//														+ (USART_RX_BUF[5] - 0x30)*0.01; 
//								break;
//							case 7:
//								temp3 = (USART_RX_BUF[2] - 0x30)*100 + (USART_RX_BUF[3] - 0x30)*10 + (USART_RX_BUF[4] - 0x30)
//														+ (USART_RX_BUF[5] - 0x30)*0.1 + (USART_RX_BUF[5] - 0x30)*0.01; 
//								break;							
//							default :break;
//						}
//						if(USART_RX_BUF[0] == 's' && USART_RX_BUF[1] == 'P') PidDataSpeed.Kp = temp3;
//						if(USART_RX_BUF[0] == 's' && USART_RX_BUF[1] == 'I') PidDataSpeed.Ki = temp3;
//						if(USART_RX_BUF[0] == 's' && USART_RX_BUF[1] == 'D') PidDataSpeed.Kd = temp3;
//						if(USART_RX_BUF[0] == 'L' && USART_RX_BUF[1] == 'P') PidDataLocation.Kp = temp3;
//						if(USART_RX_BUF[0] == 'L' && USART_RX_BUF[1] == 'I') PidDataLocation.Ki = temp3;
//						if(USART_RX_BUF[0] == 'L' && USART_RX_BUF[1] == 'D') PidDataLocation.Kd = temp3;
//						if(USART_RX_BUF[0] == 'T' && USART_RX_BUF[1] == 'P') PidDataCurrent.Kp = temp3;
//						if(USART_RX_BUF[0] == 'T' && USART_RX_BUF[1] == 'I') PidDataCurrent.Ki = temp3;
//						if(USART_RX_BUF[0] == 'T' && USART_RX_BUF[1] == 'D') PidDataCurrent.Kd = temp3;						
//					}
//					if(USART_RX_BUF[1] == 'b' || USART_RX_BUF[1] == 'o' || USART_RX_BUF[1] == 'f' || USART_RX_BUF[1] == 'a' 
//							|| USART_RX_BUF[1] == 'v' )
//					{
//						switch(USART_RX_STA&0x1F)
//						{
//							case 3:
//								temp3 = (double)(USART_RX_BUF[2] - 0x30); 
//								break;							
//							case 4:
//								temp3 = (double)((USART_RX_BUF[2] - 0x30)*10 + (USART_RX_BUF[3] - 0x30)); 
//								break;
//							case 5:
//								temp3 = (double)((USART_RX_BUF[2] - 0x30)*100 + (USART_RX_BUF[3] - 0x30)*10 + (USART_RX_BUF[4] - 0x30)); 
//								break;
//							case 6:
//								temp3 = (double)((USART_RX_BUF[2] - 0x30)*1000 + (USART_RX_BUF[3] - 0x30)*100 + (USART_RX_BUF[4] - 0x30)*10 
//														+ (USART_RX_BUF[5] - 0x30)); 
//								break;					
//							default :break;
//						}
//						if(USART_RX_BUF[0] == 's' && USART_RX_BUF[1] == 'b') PidDataSpeed.beta = temp3;
//						if(USART_RX_BUF[0] == 's' && USART_RX_BUF[1] == 'o') PidDataSpeed.outbeta = temp3;
//						if(USART_RX_BUF[0] == 's' && USART_RX_BUF[1] == 'a') PidDataSpeed.Kaff = temp3;
//						if(USART_RX_BUF[0] == 's' && USART_RX_BUF[1] == 'v') PidDataSpeed.Kvff = temp3;
//						if(USART_RX_BUF[0] == 's' && USART_RX_BUF[1] == 'f') PidDataSpeed.full_beta = temp3;
//						if(USART_RX_BUF[0] == 'L' && USART_RX_BUF[1] == 'b') PidDataLocation.beta = temp3;
//						if(USART_RX_BUF[0] == 'L' && USART_RX_BUF[1] == 'o') PidDataLocation.outbeta = temp3;
//						if(USART_RX_BUF[0] == 'L' && USART_RX_BUF[1] == 'a') PidDataLocation.Kaff = temp3;
//						if(USART_RX_BUF[0] == 'L' && USART_RX_BUF[1] == 'v') PidDataLocation.Kvff = temp3;
//						if(USART_RX_BUF[0] == 'L' && USART_RX_BUF[1] == 'f') PidDataLocation.full_beta = temp3;
//						if(USART_RX_BUF[0] == 'T' && USART_RX_BUF[1] == 'b') PidDataCurrent.beta = temp3;
//						if(USART_RX_BUF[0] == 'T' && USART_RX_BUF[1] == 'o') PidDataCurrent.outbeta = temp3;
//						if(USART_RX_BUF[0] == 'T' && USART_RX_BUF[1] == 'a') PidDataCurrent.Kaff = temp3;
//						if(USART_RX_BUF[0] == 'T' && USART_RX_BUF[1] == 'v') PidDataCurrent.Kvff = temp3;
//						if(USART_RX_BUF[0] == 'T' && USART_RX_BUF[1] == 'f') PidDataCurrent.full_beta = temp3;						
//					}
//					if(USART_RX_BUF[1] == 'd')
//					{
//						if((USART_RX_STA&0x1F) == 0x03)
//							temp1 = (USART_RX_BUF[2]-0x30);
//						if(USART_RX_BUF[0] == 's')  PidDataSpeed.dif_prior = temp1;
//						if(USART_RX_BUF[0] == 'L')  PidDataLocation.dif_prior = temp1;
//						if(USART_RX_BUF[0] == 'T')  PidDataCurrent.dif_prior = temp1;
//					}
//				}
//				else if(USART_RX_BUF[0] == 'p')
//				{
//					if(USART_RX_BUF[1] == 'c') printf_choose = (USART_RX_BUF[2]-0x30);
//					if(USART_RX_BUF[1] == 'g') get_encorder = (USART_RX_BUF[2]-0x30);
//					if(USART_RX_BUF[1] == 't')
//					{
//						switch(USART_RX_STA&0x1F)
//						{
//							case 3:
//								temp1 =(USART_RX_BUF[2] - 0x30); 
//								break;							
//							case 4:
//								temp1 = ((USART_RX_BUF[2] - 0x30)*10 + (USART_RX_BUF[3] - 0x30)); 
//								break;
//							case 5:
//								temp1 = ((USART_RX_BUF[2] - 0x30)*100 + (USART_RX_BUF[3] - 0x30)*10 + (USART_RX_BUF[4] - 0x30)); 
//								break;
//							case 6:
//								temp1 = ((USART_RX_BUF[2] - 0x30)*1000 + (USART_RX_BUF[3] - 0x30)*100 + (USART_RX_BUF[4] - 0x30)*10 
//														+ (USART_RX_BUF[5] - 0x30)); 
//								break;					
//							default :break;
//						}
//						print_count = temp1;
//					}						
//				}
//				else if(USART_RX_BUF[0] == 'C')
//				{
//					switch(USART_RX_STA&0x1F)
//						{
//							case 3:
//								temp1 =(USART_RX_BUF[2] - 0x30); 
//								break;							
//							case 4:
//								temp1 = ((USART_RX_BUF[2] - 0x30)*10 + (USART_RX_BUF[3] - 0x30)); 
//								break;
//							case 5:
//								temp1 = ((USART_RX_BUF[2] - 0x30)*100 + (USART_RX_BUF[3] - 0x30)*10 + (USART_RX_BUF[4] - 0x30)); 
//								break;
//							case 6:
//								temp1 = ((USART_RX_BUF[2] - 0x30)*1000 + (USART_RX_BUF[3] - 0x30)*100 + (USART_RX_BUF[4] - 0x30)*10 
//														+ (USART_RX_BUF[5] - 0x30)); 
//								break;					
//							default :break;
//						}
//					if(USART_RX_BUF[1] == 'm')	max_current = temp1;
//					if(USART_RX_BUF[1] == 'o')	overcurrent_count = temp1;	
//					if(USART_RX_BUF[1] == 'r')	release_current_count = temp1;	
//					if(USART_RX_BUF[1] == 'b')	base_current_count2 = temp1;	
//				}
//				else if(USART_RX_BUF[0] == 'I')
//				{
//					if(USART_RX_BUF[1] == 'f')  first_location_flag1 = (u16)(USART_RX_BUF[2] - 0x30);
//					if(USART_RX_BUF[1] == 'w')  wait_flag = (u16)(USART_RX_BUF[2] - 0x30);
//					if(USART_RX_BUF[1] == 'c')
//					{
//						switch(USART_RX_STA&0x1F)
//						{
//							case 3:
//								temp1 =(USART_RX_BUF[2] - 0x30); 
//								break;							
//							case 4:
//								temp1 = ((USART_RX_BUF[2] - 0x30)*10 + (USART_RX_BUF[3] - 0x30)); 
//								break;
//							case 5:
//								temp1 = ((USART_RX_BUF[2] - 0x30)*100 + (USART_RX_BUF[3] - 0x30)*10 + (USART_RX_BUF[4] - 0x30)); 
//								break;
//							case 6:
//								temp1 = ((USART_RX_BUF[2] - 0x30)*1000 + (USART_RX_BUF[3] - 0x30)*100 + (USART_RX_BUF[4] - 0x30)*10 
//														+ (USART_RX_BUF[5] - 0x30)); 
//								break;					
//							default :break;
//							}
//							clear_location_count =  temp1;
//						}
//						if(USART_RX_BUF[1] == 's')
//						{
//							switch(USART_RX_STA&0x1F)
//							{
//								case 4:
//									temp1 =(USART_RX_BUF[3] - 0x30); 
//									break;							
//								case 5:
//									temp1 = ((USART_RX_BUF[3] - 0x30)*10 + (USART_RX_BUF[4] - 0x30)); 
//									break;
//								case 6:
//									temp1 = ((USART_RX_BUF[3] - 0x30)*100 + (USART_RX_BUF[4] - 0x30)*10 + (USART_RX_BUF[5] - 0x30)); 
//									break;
//								case 7:
//									temp1 = ((USART_RX_BUF[3] - 0x30)*1000 + (USART_RX_BUF[4] - 0x30)*100 + (USART_RX_BUF[5] - 0x30)*10 
//															+ (USART_RX_BUF[6] - 0x30)); 			
//									break;					
//								default :break;
//							}
//								if( USART_RX_BUF[2] == '-') temp1 = -temp1;
//								location_init_speed = (double)(temp1);
//						}							
//				}
//				else if(USART_RX_BUF[0] == 'D')
//				{
//					if(USART_RX_BUF[1] == 'a') answer_master = (u8)(USART_RX_BUF[2] - 0x30);
//					if(USART_RX_BUF[1] == 'c' || USART_RX_BUF[1] == 'm' || USART_RX_BUF[1] == 't' || USART_RX_BUF[1] == 's' )
//					{
//						if(( USART_RX_BUF[2] >= 0x30) && (USART_RX_BUF[2] <= 0x39)) temp5 = ((u16)(USART_RX_BUF[2] -0x30)<<12);
//						else if(( USART_RX_BUF[2] >= 0x41) && (USART_RX_BUF[2] <= 0x46)) temp5 = (((u16)(USART_RX_BUF[2] -0x37))<<12);
//						if(( USART_RX_BUF[3] >= 0x30) && (USART_RX_BUF[3] <= 0x39)) temp5 |= ((u16)(USART_RX_BUF[3] -0x30)<<8);
//						else if(( USART_RX_BUF[3] >= 0x41) && (USART_RX_BUF[3] <= 0x46)) temp5 |= ((u16)(USART_RX_BUF[3] -0x37)<<8);
//						if(( USART_RX_BUF[4] >= 0x30) && (USART_RX_BUF[4] <= 0x39)) temp5 |= ((u16)(USART_RX_BUF[4] -0x30)<<4);
//						else if(( USART_RX_BUF[4] >= 0x41) && (USART_RX_BUF[4] <= 0x46)) temp5 |= ((u16)(USART_RX_BUF[4] -0x37)<<4);
//						if(( USART_RX_BUF[5] >= 0x30) && (USART_RX_BUF[5] <= 0x39)) temp5 |= ((u16)(USART_RX_BUF[5] -0x30));
//						else if(( USART_RX_BUF[5] >= 0x41) && (USART_RX_BUF[5] <= 0x46)) temp5 |= ((u16)(USART_RX_BUF[5] -0x37));
//					}	
//					if(USART_RX_BUF[1] == 'c') ID_CHOOSE_MODE = temp5;
//					if(USART_RX_BUF[1] == 'm') ID_master = temp5;
//					if(USART_RX_BUF[1] == 't') ID_Master_TEST = temp5;
//					if(USART_RX_BUF[1] == 's') ID_Self_TEST = temp5;
//					if(USART_RX_BUF[1] == 'z') ID_Search_Zero = temp5;
//				}
//				else if(USART_RX_BUF[0]=='E')
//				{
//					switch(USART_RX_STA&0x1F)
//					{
//						case 2:
//							temp1 =(USART_RX_BUF[1] - 0x30); 
//							break;							
//						case 3:
//							temp1 = ((USART_RX_BUF[1] - 0x30)*10 + (USART_RX_BUF[2] - 0x30)); 
//							break;
//						case 4:
//							temp1 = ((USART_RX_BUF[1] - 0x30)*100 + (USART_RX_BUF[2] - 0x30)*10 + (USART_RX_BUF[3] - 0x30)); 
//							break;
//						case 5:
//							temp1 = ((USART_RX_BUF[1] - 0x30)*1000 + (USART_RX_BUF[2] - 0x30)*100 + (USART_RX_BUF[3] - 0x30)*10 
//													+ (USART_RX_BUF[4] - 0x30)); 
//							break;					
//						default :break;
//					}
//					ecorder_resolution_ratio = temp1;
//				}
//				else if(USART_RX_BUF[0]=='M')				                    //模式切换指令       此处看起
//					{
//						if((USART_RX_BUF[1]=='0')||(USART_RX_BUF[1]=='1')||(USART_RX_BUF[1]=='2')||(USART_RX_BUF[1]=='3')||
//							(USART_RX_BUF[1]=='4'))
//						{
//							MotorMode = USART_RX_BUF[1];
//							Want_Location=Real_Location;		//切到位置模式则锁在当前位置
//							Want_Speed=0;										//切到速度模式则锁在零速
//							Want_Current=0;									//锁在电流为0的状态
//							Want_Pwm=0;											//PWM波为0
////							PID_InitALL();									//PID控制器输出为0
//						}
//					}																//模式切换指令OVER
//					if(USART_RX_BUF[0]=='P')		//PWM波设置指令
//					{
//						if(MotorMode!=PWMMODE)
//						{
//							#ifdef __DEBUG
//							printf("Command not available.\r\n");
//							#endif
//						}
//						else
//						{
//							
//							if((USART_RX_BUF[1]==0x2B)||(USART_RX_BUF[1]==0x2D))
//							{
//											             
//								temp2=(USART_RX_BUF[1]==0x2B)?1:-1;
//								switch(USART_RX_STA&0x1F)
//								{
//									case 3:
//										if((USART_RX_BUF[2]>0x2F)&&(USART_RX_BUF[2]<0x3A))
//											Want_Pwm=(USART_RX_BUF[2]-0x30)*temp2;                                       //此处有�
//										break;
//									case 4:
//										if((USART_RX_BUF[2]>0x2F)&&(USART_RX_BUF[2]<0x3A)
//											&&(USART_RX_BUF[3]>0x2F)&&(USART_RX_BUF[3]<0x3A))
//											Want_Pwm=((USART_RX_BUF[2]-0x30)*10+(USART_RX_BUF[3]-0x30))*temp2;
//										break;
//									case 5:
//										if((USART_RX_BUF[2]>0x2F)&&(USART_RX_BUF[2]<0x3A)
//											&&(USART_RX_BUF[3]>0x2F)&&(USART_RX_BUF[3]<0x3A)
//											&&(USART_RX_BUF[4]>0x2F)&&(USART_RX_BUF[4]<0x3A))
//											Want_Pwm=((USART_RX_BUF[2]-0x30)*100+(USART_RX_BUF[3]-0x30)*10+(USART_RX_BUF[4]-0x30))*temp2;
//										break;
//									case 6:
//										if((USART_RX_BUF[2]>0x2F)&&(USART_RX_BUF[2]<0x3A)
//											&&(USART_RX_BUF[3]>0x2F)&&(USART_RX_BUF[3]<0x3A)
//											&&(USART_RX_BUF[4]>0x2F)&&(USART_RX_BUF[4]<0x3A)
//											&&(USART_RX_BUF[5]>0x2F)&&(USART_RX_BUF[5]<0x3A))
//										{
//											temp1=(USART_RX_BUF[2]-0x30)*1000+(USART_RX_BUF[3]-0x30)*100+(USART_RX_BUF[4]-0x30)*10+(USART_RX_BUF[5]-0x30);
//											if(temp1>5000)
//											{
//												#ifdef __DEBUG
//												printf("Error Command.\r\n");
//												#endif
//											}
//											else
//												Want_Pwm=temp1*temp2;	
//										}
//										break;
//									default:
//										break;
//								}
//							}
//						}
//					}												//PWM波设置指令OVER
//				
//				else if(USART_RX_BUF[0]=='S')		//速度设置指令
//					{
//						if(MotorMode!=SPEEDMODE)
//						{
//							#ifdef __DEBUG
//							printf("Command not available.\r\n");
//							#endif
//						}
//						else
//						{
//							if((USART_RX_BUF[1]==0x2B)||(USART_RX_BUF[1]==0x2D))			//+ or -
//							{
//								temp2=(USART_RX_BUF[1]==0x2B)?1:-1;
//								switch(USART_RX_STA&0x1F)
//								{
//									case 3:
//										if((USART_RX_BUF[2]>0x2F)&&(USART_RX_BUF[2]<0x3A))
//											Want_Speed=(USART_RX_BUF[2]-0x30)*temp2;                           //此处有误
//										else
//										{
//											#ifdef __DEBUG
//											printf("Error Command.\r\n");
//											#endif
//										}
//										break;
//									case 4:
//										if((USART_RX_BUF[2]>0x2F)&&(USART_RX_BUF[2]<0x3A)
//											&&(USART_RX_BUF[3]>0x2F)&&(USART_RX_BUF[3]<0x3A))
//											Want_Speed=((USART_RX_BUF[2]-0x30)*10+(USART_RX_BUF[3]-0x30))*temp2;
//										else
//										{
//											#ifdef __DEBUG
//												printf("Error Command.\r\n");
//											#endif
//										}
//										break;
//									case 5:
//										if((USART_RX_BUF[2]>0x2F)&&(USART_RX_BUF[2]<0x3A)
//											&&(USART_RX_BUF[3]>0x2F)&&(USART_RX_BUF[3]<0x3A)
//											&&(USART_RX_BUF[4]>0x2F)&&(USART_RX_BUF[4]<0x3A))
//											Want_Speed=((USART_RX_BUF[2]-0x30)*100+(USART_RX_BUF[3]-0x30)*10+(USART_RX_BUF[4]-0x30))*temp2;
//										else
//										{
//											#ifdef __DEBUG
//												printf("Error Command.\r\n");
//											#endif
//										}
//										break;
//									case 6:
//										if((USART_RX_BUF[2]>0x2F)&&(USART_RX_BUF[2]<0x3A)
//											&&(USART_RX_BUF[3]>0x2F)&&(USART_RX_BUF[3]<0x3A)
//											&&(USART_RX_BUF[4]>0x2F)&&(USART_RX_BUF[4]<0x3A)
//											&&(USART_RX_BUF[5]>0x2F)&&(USART_RX_BUF[5]<0x3A))
//										{
//											temp1=(USART_RX_BUF[2]-0x30)*1000+(USART_RX_BUF[3]-0x30)*100+(USART_RX_BUF[4]-0x30)*10+(USART_RX_BUF[5]-0x30);
//											if(temp1>6000)
//											{
//												#ifdef __DEBUG
//													printf("Error Command.\r\n");
//												#endif
//											}
//											else
//												Want_Speed=temp1*temp2;
//										}
//										else
//										{
//											#ifdef __DEBUG
//											printf("Error Command.\r\n");
//											#endif
//										}
//										break;
//									default:
//										#ifdef __DEBUG
//										printf("Error Command.\r\n");
//										#endif
//										break;
//								}
//								#ifdef __DEBUG
//								printf("OK.\r\n");
//								#endif   	

//							}
//							else
//							{
//								#ifdef __DEBUG
//								printf("Error Command.\r\n");
//								#endif
//							}
//						}
//					}										
//				
//				else if(USART_RX_BUF[0]=='L')																																				//速度位置设置指令
//					{							
//						if(MotorMode!=LOCATIONMODE)
//						{
//							#ifdef __DEBUG
//							printf("Command not available.\r\n");
//							#endif
//						}
//						else if((USART_RX_STA&0x1F)!=13)
//						{
//							#ifdef __DEBUG
//							printf("Error command.\r\n");
//							#endif
//						}
//						else																	
//						{
//							temp1 = ((USART_RX_BUF[2]-0x30)*1000000 + (USART_RX_BUF[3]-0x30)*100000 + (USART_RX_BUF[4]-0x30)*10000 + 
//												(USART_RX_BUF[5]-0x30)*1000 + (USART_RX_BUF[6]-0x30)*100 + (USART_RX_BUF[7]-0x30)*10 + 
//												(USART_RX_BUF[8]-0x30));
//							if(USART_RX_BUF[1] == 0x2D)
//								temp1 = -temp1;
//							temp2 = ((USART_RX_BUF[9]-0x30)*1000+(USART_RX_BUF[10]-0x30)*100
//										+(USART_RX_BUF[11]-0x30)*10+(USART_RX_BUF[12]-0x30));
//										
//							if(abs(temp2)>6000)
//							{

//								#ifdef __DEBUG
//								printf("Speed data overflew.\r\n");
//								#endif
//								
//							}
//							else
//							{
//							 
//								Want_Location = temp1;	//位置数据更新	
//								PidDataLocation.outbeta = temp2;
//								#ifdef __DEBUG
//								printf("OK.\r\n");
//								#endif	
//							}							
//						}
//					}																																											//速度位置设置指令OVER
//				else if(USART_RX_BUF[0]=='T')
//					{
//						temp2 = ((USART_RX_BUF[1]-0x30)*1000+(USART_RX_BUF[2]-0x30)*100
//											+(USART_RX_BUF[3]-0x30)*10+(USART_RX_BUF[4]-0x30));
//						Want_Current = temp2;
//					}		
//			 
//				USART_RX_STA=0;	
//			}
//	}	
//}





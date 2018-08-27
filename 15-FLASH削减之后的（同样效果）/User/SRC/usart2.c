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
		usart.USART_BaudRate = 115200;				  //�ѱ��Ķ�
    usart.USART_Parity = USART_Parity_No;
    usart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    usart.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   
    USART_Init(USART2,&usart);

		USART_ClearFlag (USART2,USART_IT_RXNE);				//����жϱ�־
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

u8 USART_RX_BUF[32];     //���ջ���,���32���ֽ�.

//����״̬
//bit7��������ɱ�־
//bit6�����տ�ʼ��־
//bit5�����յ�0x0d
//bit4~0�����յ�����Ч�ֽ���Ŀ
u8 USART_RX_STA=0;       //����״̬���	*****��Ϊ�����Ķ�����Ϊpid����flash����λ������
u16 temp5;
//void USART2_IRQHandler(void)
//{
//	u8 temp;
//	int	 temp1;
//	int temp2;
//	double temp3;

//	if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)	//���ռĴ����ǿ�
//	{
//			USART_ClearFlag (USART2,USART_IT_RXNE);			//����жϱ�־
//			USART_ClearITPendingBit(USART2,USART_IT_RXNE);

//			temp = USART_ReceiveData(USART2);
//			if((USART_RX_STA&0x40)!=0)//�����Ѿ���ʼ
//			{			
//				if((USART_RX_STA&0x80)==0)//����δ���
//				{
//					if(USART_RX_STA&0x20)//�ѽ��յ���0x0d
//					{
//						if(temp!=0x0a)
//							USART_RX_STA=0;//���մ���,���¿�ʼ
//						else 				
//								USART_RX_STA|=0x80;	//���������														
//					}
//					else //��û�յ�0X0D
//					{	
//						if(temp==0x0d)
//							USART_RX_STA|=0x20;
//						else
//						{
//							USART_RX_BUF[USART_RX_STA&0X2F]=temp;
//							USART_RX_STA++;								   //�ѱ��ҸĶ�
//							if((USART_RX_STA&0X2F)>31)USART_RX_STA=0;//�������ݴ���,���¿�ʼ����	  
//						}		 
//					}
//				}  		
//			}
//			else if(temp=='#')		//���յ���ͷ
//				USART_RX_STA|=0x40;	
//			
//			if((USART_RX_STA&0x80)!=0)			//�����Ѿ���ɣ���������ָ��
//			{
//				if(USART_RX_BUF[0]=='W')			//USART_flash д��pid����
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
//			  else if(USART_RX_BUF[0]=='R')			   //flash_usart ����������pid
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
//				else if(USART_RX_BUF[0]=='M')				                    //ģʽ�л�ָ��       �˴�����
//					{
//						if((USART_RX_BUF[1]=='0')||(USART_RX_BUF[1]=='1')||(USART_RX_BUF[1]=='2')||(USART_RX_BUF[1]=='3')||
//							(USART_RX_BUF[1]=='4'))
//						{
//							MotorMode = USART_RX_BUF[1];
//							Want_Location=Real_Location;		//�е�λ��ģʽ�����ڵ�ǰλ��
//							Want_Speed=0;										//�е��ٶ�ģʽ����������
//							Want_Current=0;									//���ڵ���Ϊ0��״̬
//							Want_Pwm=0;											//PWM��Ϊ0
////							PID_InitALL();									//PID���������Ϊ0
//						}
//					}																//ģʽ�л�ָ��OVER
//					if(USART_RX_BUF[0]=='P')		//PWM������ָ��
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
//											Want_Pwm=(USART_RX_BUF[2]-0x30)*temp2;                                       //�˴����
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
//					}												//PWM������ָ��OVER
//				
//				else if(USART_RX_BUF[0]=='S')		//�ٶ�����ָ��
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
//											Want_Speed=(USART_RX_BUF[2]-0x30)*temp2;                           //�˴�����
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
//				else if(USART_RX_BUF[0]=='L')																																				//�ٶ�λ������ָ��
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
//								Want_Location = temp1;	//λ�����ݸ���	
//								PidDataLocation.outbeta = temp2;
//								#ifdef __DEBUG
//								printf("OK.\r\n");
//								#endif	
//							}							
//						}
//					}																																											//�ٶ�λ������ָ��OVER
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





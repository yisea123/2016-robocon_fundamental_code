#include "main.h"

//VP230---CAN_TX---PA12(CANTX) 
//VP230---CAN_RX---PA11(CANRX) 

void can_normal_mode(void);
void can_loopback_mode(void);
void Answer_Master(void);
void Self_Test(void);

u16 ID_CHOOSE_MODE = 0x0120;
u16 ID_master = 0x0100;
u16 ID_Master_TEST = 0x0200;
u16 ID_Self_TEST = 0x020A;
u16 ID_Search_Zero = 0x020C;
u8 answer_master = 0x02;

CAN_InitTypeDef        can;
NVIC_InitTypeDef   	   nvic;

void CAN_Configuration(void)
{

	CAN_FilterInitTypeDef  can_filter;		
	GPIO_InitTypeDef 	   gpio;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1,  ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |
                           RCC_APB2Periph_AFIO , ENABLE);	

	gpio.GPIO_Pin = GPIO_Pin_11;
	gpio.GPIO_Mode = GPIO_Mode_IPU;       
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);	//CAN_RX 								 

	gpio.GPIO_Pin = GPIO_Pin_12;	   
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gpio);    //CAN_TX
	
	CAN_DeInit(CAN1);

	can_loopback_mode();
	
	can_filter.CAN_FilterNumber = 0;
	can_filter.CAN_FilterMode = CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale = CAN_FilterScale_32bit;
	can_filter.CAN_FilterIdHigh=((((u32)ID_CHOOSE_MODE)<<21)&0xffff0000)>>16;
	can_filter.CAN_FilterIdLow=((((u32)ID_CHOOSE_MODE)<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
	can_filter.CAN_FilterMaskIdHigh=0xFE1F;               //只接收   0x120-0x12f的报文
	can_filter.CAN_FilterMaskIdLow=0xFFFF;	
	can_filter.CAN_FilterFIFOAssignment = 0;
	can_filter.CAN_FilterActivation = ENABLE;
	CAN_FilterInit(&can_filter);
	
	can_filter.CAN_FilterNumber=1;
	can_filter.CAN_FilterMode=CAN_FilterMode_IdMask;
	can_filter.CAN_FilterScale=CAN_FilterScale_32bit;	
	can_filter.CAN_FilterIdHigh=((((u32)ID_Master_TEST)<<21)&0xffff0000)>>16;
	can_filter.CAN_FilterIdLow=((((u32)ID_Master_TEST)<<21)|CAN_ID_STD|CAN_RTR_DATA)&0xffff;
	can_filter.CAN_FilterMaskIdHigh=0xFE1F;
	can_filter.CAN_FilterMaskIdLow=0xFFFF;	
	can_filter.CAN_FilterFIFOAssignment=0;			
	can_filter.CAN_FilterActivation=ENABLE;
	CAN_FilterInit(&can_filter);
    
  CAN_ITConfig(CAN1,CAN_IT_FMP0,ENABLE);
	Self_Test();
	  
}

void USB_LP_CAN1_RX0_IRQHandler(void)                  //CAN RX
{
		double temp_data = 0;
		double temp_data2 = 0;
    CanRxMsg rx_message;
    if (CAN_GetITStatus(CAN1,CAN_IT_FMP0)!= RESET) 
	{
		CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		CAN_Receive(CAN1, CAN_FIFO0, &rx_message);
		if((rx_message.IDE == CAN_Id_Standard)&&       //标准帧
			(rx_message.RTR == CAN_RTR_Data))          //数据帧
		{
			if((rx_message.StdId == ID_Master_TEST) && (rx_message.DLC==0x04))	      
			{
				if(rx_message.Data[0] == 0x50 && rx_message.Data[1] == 0x4f && rx_message.Data[2] == 0x53 && rx_message.Data[3] == 0x54)
				{                                                   
					Answer_Master();                                                      // 主控检查can线
				}
			}
			if(rx_message.StdId == ID_Search_Zero)
			{
				if(rx_message.Data[0]== 0x00)	 
					wait_flag = (wait_flag | 0x02);
				if(rx_message.Data[0]== answer_master )	 
					wait_flag = 0x0020;
			}
			if(rx_message.StdId == ID_CHOOSE_MODE) 
			{
				if(rx_message.DLC==0x03)
				{
					if(rx_message.Data[0]== 0x10)	                     																					//pwm模式设置
					 {										   																				
							MotorMode = PWMMODE;  
							temp_data = (double)((s16)(((u16)(rx_message.Data[1])<<8)|((u16)rx_message.Data[2])));
							if((temp_data <= 5000) && (temp_data >= -5000))
							{									
								Want_Pwm = temp_data;
							}
						}												
					else if((rx_message.Data[0]&0xf0)== 0x20 )         																						 //速度模式
						{
							MotorMode = SPEEDMODE;							
							temp_data = (double)((s16)(((u16)(rx_message.Data[1])<<8)|((u16)rx_message.Data[2])));						
							if((temp_data <= 6000) && (temp_data >= -6000))
							{														 //得到了Speed
								Want_Speed = temp_data;									   
							}
						}														  										
					}
				else if(rx_message.DLC==0x07)
				{
					if(rx_message.Data[0]== 0x30)		     																			 //速度位置模式设置
						{
							MotorMode= LOCATIONMODE;					 									
							temp_data = (double)((s16)(((u16)(rx_message.Data[1])<<8)|rx_message.Data[2]));					
							temp_data2 = (double)((s32)(((u32)(rx_message.Data[3])<<24)|((u32)(rx_message.Data[4])<<16)|((u32)(rx_message.Data[5])<<8)|rx_message.Data[6]));	
							if(temp_data >6000)
							{
								#ifdef __DEBUG
								printf("Speed_Location_Speed_data error.\r\n");
								#endif
							}
							else
							{														
								Want_Location = temp_data2;	
								PidDataLocation.outbeta = temp_data;
							} 
						}	
					}						
				}
			}		
  }
}


void Answer_Master(void)
{
	CanTxMsg tx_message;
	tx_message.StdId = ID_master;							//报文ID号
	tx_message.RTR = CAN_RTR_Data;				//数据帧
	tx_message.IDE = CAN_Id_Standard;			//标准ID	
	tx_message.DLC = 0x04;								            //数据字节数
	tx_message.Data[0] = 0x53;		
	tx_message.Data[1] = 0x55;
	tx_message.Data[2] = 0x43;
	tx_message.Data[3] = answer_master;                              
	CAN_Transmit(CAN1,&tx_message);
}

void Self_Test(void)
{
	CanTxMsg tx_message;
	tx_message.StdId = ID_Self_TEST;							//报文ID号
	tx_message.RTR = CAN_RTR_Data;				//数据帧
	tx_message.IDE = CAN_Id_Standard;			//标准ID	
	tx_message.DLC = 0x01;								            //数据字节数
	tx_message.Data[0] = 0x53;		         //'S'
	CAN_Transmit(CAN1,&tx_message);
	while(CAN_GetITStatus(CAN1,CAN_IT_FMP0) == RESET);
	LED_TOGGLE();
	can_normal_mode();
	CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
	
}

void can_normal_mode(void)
{
	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;
	can.CAN_AWUM = DISABLE;
	can.CAN_NART = DISABLE;	  
	can.CAN_RFLM = DISABLE;																
	can.CAN_TXFP = ENABLE;		
 	can.CAN_Mode = CAN_Mode_Normal;
	can.CAN_SJW = CAN_SJW_1tq;
	can.CAN_BS1 = CAN_BS1_5tq;
	can.CAN_BS2 = CAN_BS2_3tq;
	can.CAN_Prescaler = 4;     
	CAN_Init(CAN1, &can);
	
	nvic.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;  
	nvic.NVIC_IRQChannelPreemptionPriority = 1;
	nvic.NVIC_IRQChannelSubPriority = 1;
	nvic.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic);
	
	
}
 
void can_loopback_mode(void)
{
	can.CAN_TTCM = DISABLE;
	can.CAN_ABOM = DISABLE;
	can.CAN_AWUM = DISABLE;
	can.CAN_NART = DISABLE;	  
	can.CAN_RFLM = DISABLE;																
	can.CAN_TXFP = ENABLE;		
 	can.CAN_Mode = CAN_Mode_LoopBack;
	can.CAN_SJW = CAN_SJW_1tq;
	can.CAN_BS1 = CAN_BS1_5tq;
	can.CAN_BS2 = CAN_BS2_3tq;
	can.CAN_Prescaler = 4;     
	CAN_Init(CAN1, &can);
}

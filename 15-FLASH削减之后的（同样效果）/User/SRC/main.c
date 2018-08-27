#include "main.h"

u8 get_encorder = 0;	                                      //释放电机 获取脉冲数
	                                                                        

int main(void)
{

	SystemInit();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);                                     
	PID_InitALL();
  ADC_Configuration();
	PWM_Configuration();
	USART2_Configuration();
	Encoder_Configuration();
	TIM2_Configuration();
   	
	while(1)
	{                                                    
			switch(MotorMode)
			{
				
				case LOCATIONMODE:
					if(LocationPID_flag)					 																				  
					{			
						PID_Calc(&PidDataLocation,Real_Location,Want_Location);
						Want_Speed=PidDataLocation.U;
						LocationPID_flag = 0;			
					}
					
				case SPEEDMODE:
          if(SpeedPID_flag)		
					{
						PID_Calc(&PidDataSpeed,Real_Speed,Want_Speed);
						Want_Pwm=PidDataSpeed.U;
						SpeedPID_flag = 0;
					}
				
				case PWMMODE:
					  Motor_PWM_Run(Want_Pwm,5000);
					break;
				
				case FREEMODE:
					switch(get_encorder)
					{
						case 0:
							Motor_Break();
							break;
						case 1:
							Motor_Free();
							break;
						default:
							break;
					}
					break;
					
				default:
					break;							
			}
			
	}
}


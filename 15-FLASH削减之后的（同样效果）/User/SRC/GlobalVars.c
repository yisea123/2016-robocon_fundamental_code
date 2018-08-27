#include "main.h"


u8 MotorMode='0';

//flags
u8 CurrentPID_flag=0;
u8 SpeedPID_flag=0;
u8 LocationPID_flag=0;

int Want_Pwm=0;
float Real_Current=0; 
float Want_Current=0;
float Real_Speed=0; 
float Want_Speed=0;
float Real_Location=0; 
float Want_Location=0;

PidTypeDef PidDataCurrent;
PidTypeDef PidDataSpeed;
PidTypeDef PidDataLocation;

void PID_InitALL(void)
{
	PID_Init(&PidDataSpeed);
	PID_SetParam(&PidDataSpeed,1.0,0.01,0,4000,6000,0,0,0,4500);		        		//    7.0  0.5     1.3   0.01
	PID_Init(&PidDataLocation);
	PID_SetParam(&PidDataLocation,1.0,0.01,0,0,6000,0,0,0,0);		             //速度限制6000转每分钟
	PID_Init(&PidDataCurrent);
	PID_SetParam(&PidDataCurrent,7.5,0,0,0,4500,0,0,0,0);			         //PWM限制4500     pwm    ***********停不下来，虽然加速不抖
}








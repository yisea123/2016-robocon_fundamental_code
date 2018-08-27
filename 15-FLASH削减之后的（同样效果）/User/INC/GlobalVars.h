#ifndef _GLOBALVARS_H
#define _GLOBALVARS_H
#include "main.h"


#define FREEMODE				'0'
#define PWMMODE 				'1'
#define SPEEDMODE 			'2'
#define LOCATIONMODE 		'3'
#define TESTMODE				'4'

extern u8 MotorMode;

extern u8 CurrentPID_flag;
extern u8 SpeedPID_flag;
extern u8 LocationPID_flag;
  

extern int Want_Pwm;
extern float Real_Current; 
extern float Want_Current;
extern float Real_Speed; 
extern float Want_Speed;
extern float Real_Location; 
extern float Want_Location;


extern PidTypeDef PidDataCurrent;
extern PidTypeDef PidDataSpeed;
extern PidTypeDef PidDataLocation;

void PID_InitALL(void);

#endif

#include "stdio.h"

typedef struct
{
	float SetSpeed;
	float ActualSpeed;
	float err;
	float err_next;
	float err_last;
	float Kp,Ki,Kd;
}Pid;

void PID_init()
{
	Pid pid;
	pid.SetSpeed = 0.0;
	pid.ActualSpeed = 0.0;
	pid.err = 0.0;
	pid.err_last = 0.0;
	pid.err_next = 0.0;
	pid.Kd = 0.2 ;
	pid.Ki = 0.015;
	pid.Kp = 0.2;
}

float PID_realize(float speed)
{
	PID_init();
	pid.SetSpeed =speed ;
}
















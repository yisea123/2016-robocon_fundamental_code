#include "pid.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//��ʼ��PID 
void PID_Init(PidTypeDef * pid)
{
	memset(pid, 0, sizeof(PidTypeDef));
}

//���ò��� 
void PID_SetParam(PidTypeDef * pid,double p, double i, double d, double beta, double outbeta, int dif_prior,double kaff, double kvff,double full_beta)
{
	pid->Kp = p;
	pid->Ki = i;
	pid->Kd = d;
	pid->beta = beta;
	pid->outbeta = outbeta;
	pid->dif_prior = dif_prior;
	pid->Kaff = kaff;
	pid->Kvff = kvff;
	pid->full_beta = full_beta;
}



//PID���� 
void PID_Calc(PidTypeDef * pid, double rel_val, double set_val)
{
	double p = 0,
         i = 0,
         d = 0,
         kaff = 0,
         kvff = 0;
	pid->s[2] = set_val;
	pid->e[2] = set_val - rel_val; //��ȡ��ǰ���
	pid->r[2] = rel_val; //��ȡ��ǰֵ

	
	/*��������*/
	p = pid->Kp * (pid->e[2] - pid->e[1]);
	
	
	//�����ֱ���
	if(pid->full_beta != 0)
	{
		if(pid->e[1] > pid->full_beta)
			{
				pid->e[2] = ((pid->e[2])>0?0:pid->e[2]);
			}
		else if(pid->e[1] < -pid->full_beta)
			{
				pid->e[2] = ((pid->e[2])>0?pid->e[2]:0);
			}
	}

	
		 //���ַ���
	if (pid->beta == 0)
	{
		i = pid->Ki * (pid->e[2]);
	}
	else
	{
		if (pid->e[2] <= pid->beta && pid->e[2] >= -pid->beta) 
			i = pid->Ki * (pid->e[2]);
		else 
			i = 0;	
	} 
	
	//΢������ 
	if (pid->dif_prior)
	{
		d = pid->Kd * (pid->r[2] - 2 * pid->r[1] + pid->r[0]); 
	}	 
	else
	{
		d = pid->Kd * (pid->e[2] - 2 * pid->e[1] + pid->e[0]); 
	}
	
	kvff = (pid->s[2] - pid->s[1]) * pid->Kvff;//�ٶ�ǰ�� 
	kaff = (pid->s[2] - 2 * pid->s[1] + pid->s[0]) * pid->Kaff;//���ٶ�ǰ�� 
	
	pid->delta_U = p + i + d + kvff + kaff; //����ʽPID 

	
	pid->U = pid->last_U + pid->delta_U; //λ��ʽPID
	
  if(pid->outbeta != 0)
	{
		if(pid->U>pid->outbeta)
			pid->U=pid->outbeta;
		else if(pid->U<-pid->outbeta)
			pid->U=-pid->outbeta;
	}
	
	
	
	/*��¼��һ�����*/
	pid->last_U = pid->U;
	/*�����趨ֵ*/
	pid->s[0] = pid->s[1];
	pid->s[1] = pid->s[2]; 
	/*�������*/
	pid->e[0] = pid->e[1];
	pid->e[1] = pid->e[2]; 
 	/*����ʵ��ֵ*/
	pid->r[0] = pid->r[1];
	pid->r[1] = pid->r[2];   
}


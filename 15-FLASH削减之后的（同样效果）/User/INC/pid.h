#ifndef _PID_H_
#define _PID_H_

typedef struct
{
	//PID �������� 
	double Kp;
	double Ki;
	double Kd;
	//���ַ���
	double beta;//0���ǲ������ַ��룬 �����Ϊ����ô���ǻ��ַ�Χ 
	double outbeta;//0���ǲ�������޷��������Ϊ����ô�����޷���Χ
	//΢������
	int dif_prior;//0�ǲ���΢������ 
	//���ٻ��� 
	//PID���ֵ
	double last_U; //��һ�ε����ֵ 
	double delta_U;//����ʽPID
	double U;//λ��ʽPID
	//�趨ֵ
	double s[3]; 
	//���
	double e[3];//ÿ�ε����2�����µ�1����һ�ε�0�Ǵ��ϴ�
	//ʵ��ֵ
	double r[3];
	//ǰ������
	double Kvff; 
	double Kaff;
	double full_beta;
	 
}PidTypeDef;


void PID_Init(PidTypeDef * pid);

void PID_SetParam(PidTypeDef * pid,double p, double i, double d, double beta, double outbeta,int dif_prior,double kaff, double kvff,double full_beta);

void PID_Calc(PidTypeDef * pid, double rel_val, double set_val);


#endif

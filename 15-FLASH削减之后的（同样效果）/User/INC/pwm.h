#ifndef __PWM_H__
#define __PWM_H__

void PWM_Configuration(void);

void Motor_PWM_Run(int give_pulse,int max_pulse);
void Motor_Free(void);
void Motor_Break(void);
void location_init(void);

#endif

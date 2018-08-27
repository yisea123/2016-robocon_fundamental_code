#ifndef _ENCODER_H
#define _ENCODER_H

#include "stm32f10x.h"

void Encoder_Configuration(void);
void Encoder_Start(void);
float Encoder_Get_CNT(void);
int CountRealSpeed(int delat_CNT);


#endif





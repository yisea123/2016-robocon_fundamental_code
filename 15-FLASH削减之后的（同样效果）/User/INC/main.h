#ifndef __MAIN_H__
#define __MAIN_H__

#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>

#include "encoder.h"
#include "led.h"
#include "beep.h"
#include "pwm.h"
#include "tim2.h"
#include "flash.h"
#include "delay.h"
#include "usart2.h"
#include "can.h"
#include "ad.h"
#include "pid.h"
#include "GlobalVars.h"
#include "visual_scope.h"
#include "gpio.h"


/**********   �����ò�����            ***********/
//#define __DEBUG
//#define __DEBUG1
//#define __DEBUG2

#define Pwm_Mode 			  	'P'
#define Speed_Mode 		  	'S'
#define Location_Mode 		'L'

extern	int printf_flag;         //����pid��������
extern int printf_choose;        //ѡ���ӡ������
extern int print_count;                    //��ӡ���ʱ��  ( X *2 )  ms
extern u8 get_encorder;
/*********************
�������������ز���
*********************/
extern int max_current;
extern int overcurrent_count;              //���� ʱ��      ( X *2 )  ms
extern int release_current_count;           // �������ʱ��    ( X *2 )  ms
extern int base_current_count2;            //��ƫ�õ����� ʱ��    ( X *250 )  us

extern int current_protect_flag; 
extern int overcurrent_flag;


/*******************************
Ѱ����ز���
********************************/
extern double location_init_speed;                   
extern int clear_location_count;           //Ѱ��� ��λ������  ��ʱ��    ( X *2 )  ms  
extern u16 first_location_flag1;

extern u16 wait_flag;
extern int clear_flag;
extern int first_location_temp1;
extern int first_location_temp2;

/**************************
canͨ�ŵ���ز���
***************************/
extern u16 ID_CHOOSE_MODE;
extern u16 ID_master;
extern u16 ID_Master_TEST;
extern u16 ID_Self_TEST;
extern u16 ID_Search_Zero;
extern u8 answer_master;

/***************************
�������������ز���
****************************/
extern int ecorder_resolution_ratio;

/*****************************
FLASH  ��ʼ����־
******************************/
extern u8 flash_first_flag;
#endif


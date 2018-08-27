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


/**********   调试用参数区            ***********/
//#define __DEBUG
//#define __DEBUG1
//#define __DEBUG2

#define Pwm_Mode 			  	'P'
#define Speed_Mode 		  	'S'
#define Location_Mode 		'L'

extern	int printf_flag;         //调试pid参数所用
extern int printf_choose;        //选择打印的数据
extern int print_count;                    //打印间隔时间  ( X *2 )  ms
extern u8 get_encorder;
/*********************
电机过流保护相关参数
*********************/
extern int max_current;
extern int overcurrent_count;              //过流 时间      ( X *2 )  ms
extern int release_current_count;           // 过流解除时间    ( X *2 )  ms
extern int base_current_count2;            //求偏置电流的 时间    ( X *250 )  us

extern int current_protect_flag; 
extern int overcurrent_flag;


/*******************************
寻零相关参数
********************************/
extern double location_init_speed;                   
extern int clear_location_count;           //寻零后 清位置脉冲  的时间    ( X *2 )  ms  
extern u16 first_location_flag1;

extern u16 wait_flag;
extern int clear_flag;
extern int first_location_temp1;
extern int first_location_temp2;

/**************************
can通信的相关参数
***************************/
extern u16 ID_CHOOSE_MODE;
extern u16 ID_master;
extern u16 ID_Master_TEST;
extern u16 ID_Self_TEST;
extern u16 ID_Search_Zero;
extern u8 answer_master;

/***************************
电机、编码器相关参数
****************************/
extern int ecorder_resolution_ratio;

/*****************************
FLASH  初始化标志
******************************/
extern u8 flash_first_flag;
#endif


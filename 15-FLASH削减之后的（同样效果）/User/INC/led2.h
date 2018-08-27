#ifndef __LED_H__
#define __LED_H__

#define LED_OFF()  GPIO_SetBits(GPIOB,GPIO_Pin_9)
#define LED_ON()   GPIO_ResetBits(GPIOB,GPIO_Pin_9)
#define LED_TOGGLE()  GPIOB->ODR ^= GPIO_Pin_9                            //ÁÁ°µ×´Ì¬½»»»

#define TEST_LED_OFF()  GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define TEST_LED_ON()   GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define TEST_LED_TOGGLE()  GPIOB->ODR ^= GPIO_Pin_8                            //ÁÁ°µ×´Ì¬½»»»

void LED_Configuration(void);


#endif 



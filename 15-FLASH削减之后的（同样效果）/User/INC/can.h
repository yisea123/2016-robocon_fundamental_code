#ifndef __CAN_H__
#define __CAN_H__


void CAN_Configuration(void);
void USART2_printf_CAN_rx_data(void);
void CAN1_WriteData(unsigned short can_id);
void CAN_TX(void);


#endif 

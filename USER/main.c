#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "led.h"
#include "motor.h"
#include "encoder.h"
#include "timer.h"
#include "adc.h"
#include "jy61.h"
//#include ".h"

 int main(void)
 {	
	Delay_init();	    	 //��ʱ������ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 

	uart_init(115200);//���ȼ�3
	uart3_init(115200);//imu ,���ȼ�2
	LED_Init();

	Encoder_Init();//���ȼ�1
	 
	Motor_Init();//�������7200
	 
	Adc_Init();	
	 
	TIM1_Int_Init();
	while(1);

 }

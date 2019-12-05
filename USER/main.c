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
#include "spi.h"
#include "24l01.h"
//#include ".h"

 int main(void)
 {	
	Delay_init();	    	 //延时函数初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); 

	uart_init(115200);//优先级3
//	uart3_init(115200);//imu ,优先级2
		LED_Init();
		SPI2_Init();
		NRF24L01_Init();
		while(NRF24L01_Check());
	 
	Encoder_Init();//优先级1
	Motor_Init();//电机满幅7200
// 
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
	NRF24L01_TX_Mode();	 
	TIM1_Int_Init();
	while(1);

 }

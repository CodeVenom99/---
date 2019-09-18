#include "timer.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "encoder.h"
#include "motor.h"
#include "adc.h"
#include "jy61.h"
#include "spi.h"
#include "24l01.h"
int Encoder_Left,Encoder_Right;
int t=0;
u16 vout,adc_date;
int Motor_A,Motor_B;
u8 tmp_buf[33],juli;
extern int tiaojieA,Encoder_A_EXTI;	
void TIM1_Int_Init(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //时钟使能
	
	//定时器TIM1初始化
	TIM_TimeBaseStructure.TIM_Period = 4999; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =143; //143
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //修改这里
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //初始化NVIC寄存器


	TIM_Cmd(TIM1, ENABLE);  //使能TIMx					 
}

void num_change(u8 * num,u8 * buf)
{
u8 shi,ge;
switch ((*num)%10)
	{
		case 0:	ge=0x30;break;
		case 1:	ge=0x31;break;
		case 2:	ge=0x32;break;
		case 3:	ge=0x33;break;
		case 4:	ge=0x34;break;
		case 5:	ge=0x35;break;
		case 6:	ge=0x36;break;
		case 7:	ge=0x37;break;
		case 8:	ge=0x38;break;
		case 9:	ge=0x39;break;
	}
switch ((*num)/10)
	{
		case 0:	shi=0x30;break;
		case 1:	shi=0x31;break;
		case 2:	shi=0x32;break;
		case 3:	shi=0x33;break;
		case 4:	shi=0x34;break;
		case 5:	shi=0x35;break;
		case 6:	shi=0x36;break;
		case 7:	shi=0x37;break;
		case 8:	shi=0x38;break;
		case 9:	shi=0x39;break;
	}
			buf[0]=0x04;//第一位表示要发送的数据个数
			buf[1]=shi;
			buf[2]=ge;
			buf[3]=0x0d;			
			buf[4]=0x0a;
}
	
void TIM1_UP_IRQHandler(void)   //TIM1中断10ms
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
	
		adc_date=Get_Adc_Average(ADC_Channel_10,10);	
		vout=adc_date*330/4096;
		juli=(u8)(20.8/((vout/100.0)-0.34));

	


				
		t++;		
		if(t==50)
		{	
			printf("%d\r\n",juli);
			num_change(&juli,tmp_buf);
			NRF24L01_TxPacket(tmp_buf);
			LED=!LED;t=0;
		}	
		
//		Encoder_Left=Read_Encoder(2);
//		Encoder_Right=Read_Encoder(3);		

//		printf("%d %d\r\n",Encoder_Left,Encoder_Right);
//		Motor_A=Incremental_PI_A(Encoder_Left,20);		
//		Motor_B=Incremental_PI_B(Encoder_Right,20);
//	
//		Xianfu_Pwm();
//	
//		Set_Pwm_Motor1(Motor_A);//左	
//		Set_Pwm_Motor2(Motor_B);
//		imu_date();				
//		TIM3 -> CNT=0;Encoder_A_EXTI=0;
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );						
		}
}
/*
		t++;		

		if(t==50)
		{
		LED=!LED;t=0;
		}
*/




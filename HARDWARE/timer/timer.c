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
u16 send[8],value[8],array[8],i,j,k;;
int Motor_A,Motor_B;
u8 send_date[32],t=0;
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
	
void TIM1_UP_IRQHandler(void)   //TIM1中断10ms
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //检查TIM3更新中断发生与否
		{
//	imu_date();		
		Distance();
/********环形传感器检测***********/			
//		t++;
//		if(t==50)
//		{
//		LED=!LED;
		date_change();
		NRF24L01_TxPacket(send_date);//发送数据		
//		t=0;				
//		}
		Motor_A=Motor_B=PID_position(array[1],20);
		printf("%d %d\r\n",array[1],Motor_A);		
		Xianfu_Pwm();
	
		Set_Pwm_Motor1(Motor_A);//左	
		Set_Pwm_Motor2(Motor_B);

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );						
		}
}
	
//		Encoder_Left=Read_Encoder(2);
//		Encoder_Right=Read_Encoder(3);
//		Motor_A=Incremental_PI_A(Encoder_Left,20);		
//		Motor_B=Incremental_PI_B(Encoder_Right,20);
//		TIM3 -> CNT=0;Encoder_A_EXTI=0;
//		printf("%d %d\r\n",Encoder_Left,Encoder_Right);
//		Motor_A=Motor_B=PID_position(distance,20);

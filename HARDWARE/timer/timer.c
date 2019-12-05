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

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE); //ʱ��ʹ��
	
	//��ʱ��TIM1��ʼ��
	TIM_TimeBaseStructure.TIM_Period = 4999; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =143; //143
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0; //�޸�����
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //��ʼ��NVIC�Ĵ���


	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIMx					 
}
	
void TIM1_UP_IRQHandler(void)   //TIM1�ж�10ms
{
	if (TIM_GetITStatus(TIM1, TIM_IT_Update) != RESET)  //���TIM3�����жϷ������
		{
//	imu_date();		
		Distance();
/********���δ��������***********/			
//		t++;
//		if(t==50)
//		{
//		LED=!LED;
		date_change();
		NRF24L01_TxPacket(send_date);//��������		
//		t=0;				
//		}
		Motor_A=Motor_B=PID_position(array[1],20);
		printf("%d %d\r\n",array[1],Motor_A);		
		Xianfu_Pwm();
	
		Set_Pwm_Motor1(Motor_A);//��	
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

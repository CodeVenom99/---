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
int Motor_A,Motor_B,target_r,target_l;
u8 send_date[32],t=0;
float v_t,v_max=1.7,a_t,a_max=0.1,v_targe_r,v_targe_l;
extern int tiaojieA,Encoder_A_EXTI;	
extern float angle[3];
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
		imu_date();	
		printf("z:%f\r\n",angle[2]);	
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
			
		v_t=0.5;
//		a_t=0;			
//		v_t=v_max*(array[1]-20.0)/(100.0-20.0);//�趨���ٶ�,40Ϊ���������룬20Ϊ������С���루����Ϊ��ȫ���룩
		a_t=a_max*(angle[2]-45.0)/(90.0-45.0);
			
		v_targe_l=v_t+a_t;v_targe_r=v_t-a_t;
		target_l=v_targe_l*100.0/1.7;
		target_r=v_targe_r*100.0/1.7;//������Ϊ130/1.7�����ٶ�ת��Ϊ����������
//		printf("l:%d r:%d \r\n",target_l,target_r);
		Encoder_Left=Read_Encoder(2);	
		Encoder_Right=Read_Encoder(3);
//		printf("Encoder_Left:%d Encoder_Right:%d \r\n",Encoder_Left,Encoder_Right);		
		Motor_A=Incremental_PI_A(Encoder_Left,target_l);		
		Motor_B=Incremental_PI_B(Encoder_Right,target_r);	
		Xianfu_Pwm();	
		Set_Pwm_Motor1(Motor_A);//��	
		Set_Pwm_Motor2(Motor_B);

		TIM_ClearITPendingBit(TIM1, TIM_IT_Update  );						
		}
}
	


//		TIM3 -> CNT=0;Encoder_A_EXTI=0;



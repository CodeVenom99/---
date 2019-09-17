#include "encoder.h"
#include "timer.h"
int Encoder_A_EXTI, Encoder_B_EXTI;

void Encoder_Init_TIM_Exit0(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PA端口时钟
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	            //端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
		GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	  
   // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  													
    NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void Encoder_Init_TIM_Exit1(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //使能PA端口时钟
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	            //端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
		GPIO_Init(GPIOB, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	  
   // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  													
    NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
void Encoder_Init_TIM_Exit6(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	            //端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource6);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line6;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	  
   // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  													
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void Encoder_Init_TIM_Exit7(void)
{
		GPIO_InitTypeDef GPIO_InitStructure;
		EXTI_InitTypeDef EXTI_InitStructure;
		NVIC_InitTypeDef NVIC_InitStructure;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); //使能PA端口时钟
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	            //端口配置
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         //上拉输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);					      //根据设定参数初始化GPIOB 
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource7);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line7;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;//下降沿触发
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	  
   // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  													
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;	  
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}
int Read_Encoder(u8 TIMX)
{
    int Encoder_TIM;    
   switch(TIMX)
	 {
		case 2:  Encoder_TIM=(short)Encoder_A_EXTI;  Encoder_A_EXTI=0; break;	
		case 3:  Encoder_TIM=(short)Encoder_B_EXTI;  Encoder_B_EXTI=0; break;
		default: Encoder_TIM=0;
	 }
		return Encoder_TIM;
}

void EXTI0_IRQHandler(void)  //
{
		EXTI->PR=1<<0;  //清除LINE上的中断标志位
	if(PBin(0)==0)
	{
	if(PBin(1)==0)   Encoder_A_EXTI++;
	else             Encoder_A_EXTI--;
	}
	else
	{
	if(PBin(1)==0)  Encoder_A_EXTI--;
	else             Encoder_A_EXTI++;
	}		
}

void EXTI1_IRQHandler(void)
{			
		EXTI->PR=1<<1;  //清除LINE上的中断标志位
	if(PBin(1)==1)
	{
	if(PBin(0)==0)  Encoder_A_EXTI++;   
	else            Encoder_A_EXTI--;
	}
	else
	{
	if(PBin(0)==0)  Encoder_A_EXTI--;
	else            Encoder_A_EXTI++;
	}		
}

void EXTI9_5_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line6) != RESET)
		{
		EXTI->PR=1<<6;  //清除LINE上的中断标志位
		if(PAin(6)==1)
		{
		if(PAin(7)==0)  Encoder_B_EXTI++;   
		else            Encoder_B_EXTI--;
		}
		else
		{
		if(PAin(7)==0)  Encoder_B_EXTI--;
		else            Encoder_B_EXTI++;
		}
		}
		
	if(EXTI_GetITStatus(EXTI_Line7) != RESET)
		{
		EXTI->PR=1<<7;  //清除LINE上的中断标志位
		if(PAin(7)==0)
		{
		if(PAin(6)==0)  Encoder_B_EXTI++;   
		else            Encoder_B_EXTI--;
		}
		else
		{
		if(PAin(6)==0)  Encoder_B_EXTI--;
		else            Encoder_B_EXTI++;
		}
		}
}
void Encoder_Init(void)
{
	Encoder_Init_TIM_Exit0();//优先级1，0
	Encoder_Init_TIM_Exit1();//优先级1，2
	Encoder_Init_TIM_Exit6();//优先级1，1
	Encoder_Init_TIM_Exit7();//优先级1，3
}

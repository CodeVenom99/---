#ifndef __jy61_H
#define __jy61_H	 

#include "sys.h"

void uart3_init(u32 bound); //初始化 配置USART2
void imu_date(void);//显示欧拉角和3轴速度
void z_axis_calibration(void);//z轴角度归零=将当前位置设为0，需要就引用

		 				    
#endif



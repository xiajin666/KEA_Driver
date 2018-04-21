#include "motor_strategy.h"
#include "FTM.h"

#define stable 						2                                                 //�ȶ�ֵ���м䷶Χ
#define Speed_Max 				80.0
#define Speed_Min 				20.0
#define Sensor_W 					20.0                                              //��о��������ߵĳ���
#define Slope 						(float)((Speed_Max-Speed_Min)/(Sensor_W-stable))  //б��   ��Ϊ�г��������������ø�����
#define Intercept 				(float)(-stable*Slope)                            //�ؾ�
#define speed 						50

float 	diff_speed;
int 		s_l,s_r;

void motor_strategy(int diff_pos)
{
		if(diff_pos<-stable||diff_pos>stable)
		{
				diff_speed=(float)(Slope*diff_pos+Intercept);
		}
		else
		{
				diff_speed=0.0;
		}

		s_l =(int)(speed +(diff_speed /2));
		s_r =(int)(speed -(diff_speed /2));
	
		dianji(s_l,s_r);
}

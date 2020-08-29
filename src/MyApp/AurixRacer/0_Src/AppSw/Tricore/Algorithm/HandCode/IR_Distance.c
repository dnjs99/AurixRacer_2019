//#include "IR_Distance.h"
//#include "Basic.h"
//#include <math.h>
//
//typedef struct
//{
//	float32           Value1;
//	float32           Value2;
//	float32           Value3;
//	float32           Value4;
//}IR_Value; //0 ~ 5V 값
//
//
//float Dis[4]; //실제 Distance 값
//
//IR_Value value;
//
//void IR_Distance_init(void){
//
//	value.Value1 = 0;
//	value.Value2 = 0;
//	value.Value3 = 0;
//	value.Value4 = 0;
//
//}
//
//void IR_Distance_Get(void){
//
//	value.Value1 = IR_AdcResult[0] * 5;
//	value.Value2 = IR_AdcResult[1] * 5;
//	value.Value3 = IR_AdcResult[2] * 5;
//	value.Value4 = IR_AdcResult[3] * 5;
//
//	if( Dis_func(value.Value1) > 150.0 ) Dis[0] = 150.0;
//	else Dis[0] = Dis_func(value.Value1) - 10.0;
//
//	if( Dis_func(value.Value2) > 150.0 ) Dis[1] = 150.0;
//	else Dis[1] = Dis_func(value.Value2);
//
//	if( Dis_func(value.Value3) > 150.0 ) Dis[2] = 150.0;
//	else Dis[2] = Dis_func(value.Value3);
//
//	if( Dis_func(value.Value4) > 150.0 ) Dis[3] = 150.0;
//	else Dis[3] = Dis_func(value.Value4);
//}
//
//
//float Dis_func(float x){
//	float y = 0;
//	y = -18.811*pow(x, 5) + 174.63*pow(x, 4) - 631.21*pow(x,3)+ 1117.4*pow(x, 2) - 1003.7*x + 424.36;
//	return y;
//}

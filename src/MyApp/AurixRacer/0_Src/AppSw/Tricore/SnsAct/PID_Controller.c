/*
 * PID_Controller.c
 *
 *  Created on: 2019. 7. 2.
 *      Author: sal9s
 */

#include <stdio.h>
#include "PID_Controller.h"

#define DELTA_T 0.01	// 20ms?

float k_p = 0.007;
float k_i = 0.06;//.02;
float upper_limit = 3;
float lower_limit = -3;
float error_sum;

float PID_Control(float cur_speed, float goal_speed){
	float error = goal_speed - cur_speed;
	error_sum += error * DELTA_T;						// need to be handle

	if(error_sum > upper_limit){
		error_sum = upper_limit;
	}
	else if(error_sum < lower_limit){
		error_sum = lower_limit;
	}
	float p = k_p * error;
	float i = k_i * error_sum;

	float u = p + i;


	if(u > 0.4)										// 1
		u = 0.4;

	if(goal_speed == 0)
		u = 0;

	return u;
}

/*
 * HallSensor.c
 *
 *  Created on: 2019. 6. 29.
 *      Author: sal9s
 */

#include <stdio.h>
#include "HallSensor.h"

Hall_val_t Hall_val = {
		.speed_rps = 0
};

IfxGtm_Tim_In _timDriver;
float _frequency;
uint32 _period_ticks = 0;

//IFX_EXTERN float goal_speed;
//float data[100];
//int i = 0;

void HallSensor_init(){
	printf("HallSensor_init() called\n");
	IfxGtm_Tim_In_Config configTim;
	IfxGtm_enable(&MODULE_GTM);
	IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_CLK0);
	IfxGtm_Cmu_enableClocks(&MODULE_GTM, IFXGTM_CMU_CLKEN_FXCLK);

	IfxGtm_Tim_In_initConfig(&configTim, &MODULE_GTM);
	configTim.capture.clock 	  = IfxGtm_Cmu_Clk_0;
	configTim.filter.inputPin 	  = &HALL_IN;   // select channel
	configTim.filter.inputPinMode = IfxPort_Mode_inputPullUp; // select mode
	IfxGtm_Tim_In_init(&_timDriver, &configTim);
}

void HallSensor_run(){
	Ifx_GTM_TIM_CH_GPR0 GPR0;
	Ifx_GTM_TIM_CH_GPR1 GPR1;
	if (IfxGtm_Tim_Ch_isNewValueEvent(_timDriver.channel))
		{
			IfxGtm_Tim_Ch_clearNewValueEvent(_timDriver.channel);

			GPR1.U       = _timDriver.channel->GPR1.U;
			GPR0.U       = _timDriver.channel->GPR0.U;
			_period_ticks = GPR1.B.GPR1;

			_frequency = IfxGtm_Cmu_getModuleFrequency(&MODULE_GTM) / (float) _period_ticks;
			Hall_val.speed_rps = _frequency;
//			data[i] = _frequency;
//			i++;
//			if(i == 99)
//				goal_speed = 0;
		}
}

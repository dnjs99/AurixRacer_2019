#include "AppTaskFu.h"

static sint32 task_cnt_1m = 0;
static sint32 task_cnt_10m = 0;
static sint32 task_cnt_100m = 0;
static sint32 task_cnt_1000m = 0;

boolean task_flag_1m = FALSE;
boolean task_flag_10m = FALSE;
boolean task_flag_100m = FALSE;
boolean task_flag_1000m = FALSE;

float angle = 0;
float goal_speed = 40;

void appTaskfu_init(void){
	BasicPort_init();
	Motor_init();
//	BasicPort_run();
	IR_setMotor0En(TRUE); //Motor INH = 1 config
	setSrvAngle(-0.12);
//	angle = 0;
	//IR_setMotor0Vol(-0.5); //setMotor0Vol -> Motor0VolU 값 변경 : -1.0 ~ 1.0 ; 0.0 (듀티 0.5) 이하로
	//BasicVadcBgScan_init();
	//BasicLineScan_init();
//	AEB_init();
	HallSensor_init();
}

void appTaskfu_1ms(void)
{
	task_cnt_1m++;
	if(task_cnt_1m == 1000){
		task_cnt_1m = 0;
	}

}


void appTaskfu_10ms(void)
{
	task_cnt_10m++;
	if(task_cnt_10m == 100){
		task_cnt_10m = 0;
	}
	if(task_cnt_10m%2 == 0){
		//BasicVadcBgScan_run();
		//BasicLineScan_run();
		//InfineonRacer_detectLane_MS();
		//InfineonRacer_camfilter();
		//InfineonRacer_control_MS();
	}

	HallSensor_run();
	setMotorVelocity(PID_Control(getSpeed_rps(), goal_speed) * 2 - 1);
	BasicPort_run();
	EveryMotor_run();
}

void appTaskfu_100ms(void)
{
	task_cnt_100m++;
	if(task_cnt_100m == 100){
		task_cnt_100m = 0;
	}
	//AEB_run();
//	IR_setSrvAngle(angle);
//	angle += 0.01;
//	if(angle >= 1) angle = -1;
}

void appTaskfu_1000ms(void)
{
	task_cnt_1000m++;
	if(task_cnt_1000m == 1000){
		task_cnt_1000m = 0;
	}
}

void appTaskfu_idle(void){
}

void appIsrCb_1ms(void){

}


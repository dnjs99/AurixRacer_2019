#include "AppTaskFu.h"

static sint32 task_cnt_1m = 0;
static sint32 task_cnt_10m = 0;
static sint32 task_cnt_100m = 0;
static sint32 task_cnt_1000m = 0;

boolean task_flag_1m = FALSE;
boolean task_flag_10m = FALSE;
boolean task_flag_100m = FALSE;
boolean task_flag_1000m = FALSE;

float goal_speed = 0;
int change_angle2 = 0;
float servo_angle2 = 0.0;


void appTaskfu_init(void) {
	BasicPort_init();
	Motor_init();
	IR_setMotor0En(TRUE); //Motor INH = 1 config
	setSrvAngle(-0.12);
	HallSensor_init();
	setMotorVelocity(-0.5); //setMotor0Vol -> Motor0VolU 값 변경 : -1.0 ~ 1.0 ; 0.0 (듀티 0.5) 이하로
	DisScan_init();
	LineScan_init();
	AEB_init();
	BasicPort_run();
}

void appTaskfu_1ms(void)
{
	task_cnt_1m++;
	if (task_cnt_1m == 1000) {
		task_cnt_1m = 0;
	}

}


void appTaskfu_10ms(void)
{
	task_cnt_10m++;
	if (task_cnt_10m == 100) {
		task_cnt_10m = 0;
	}

	if (task_cnt_10m % 2 == 0) {
		DisScan_run();
		LineScan_run();
		DetectLane();
		Distance_Get();
		MissionZone_Detect(1);
		BasicPort_run();
	}

	AEB_run();
	HallSensor_run();
	setMotorVelocity(PID_Control(getSpeed_rps(), goal_speed) * 2 - 1);
	EveryMotor_run();
}

void appTaskfu_100ms(void)
{
	task_cnt_100m++;
	if (task_cnt_100m == 100) {
		task_cnt_100m = 0;
	}
}

void appTaskfu_1000ms(void)
{
	task_cnt_1000m++;
	if (task_cnt_1000m == 1000) {
		task_cnt_1000m = 0;
	}
}

void appTaskfu_idle(void) {
}

void appIsrCb_1ms(void) {

}

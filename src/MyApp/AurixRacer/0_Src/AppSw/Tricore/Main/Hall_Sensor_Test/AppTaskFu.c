#include "../Hall_Sensor_Test/AppTaskFu.h"

static sint32 task_cnt_1m = 0;
static sint32 task_cnt_10m = 0;
static sint32 task_cnt_100m = 0;
static sint32 task_cnt_1000m = 0;

boolean task_flag_1m = FALSE;
boolean task_flag_10m = FALSE;
boolean task_flag_100m = FALSE;
boolean task_flag_1000m = FALSE;

float angle = 0;

void appTaskfu_init(void){
	BasicPort_init();
	BasicGtmTom_init();
	BasicPort_run();
	IR_setMotor0En(TRUE); //Motor INH = 1 config
	//printf("test1\n");
	IR_setSrvAngle(-0.16);
	angle = 0;
	IR_setMotor0Vol(-0.65); //setMotor0Vol -> Motor0VolU 값 변경 : -1.0 ~ 1.0 ; 0.0 (듀티 0.5) 이하로
	//BasicVadcBgScan_init();
	//BasicLineScan_init();
	//init();
//	AEB_init();
//	printf("test1\n");
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
//		BasicPort_run();
		BasicGtmTom_run();
//		BasicVadcBgScan_run();
//		BasicLineScan_run();
//		InfineonRacer_detectLane_MS();
//		//InfineonRacer_camfilter();
//		InfineonRacer_control_MS();
////		read_tim();
	HallSensor_run();
	}
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


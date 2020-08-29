#include "Emergency.h"
#include "Basic.h"

uint32 camera[2][128];
boolean FLAG = FALSE;

void emergency_detect(void){
	int sum = 0;
	for(int i = 0; i < 2; i++){
		for(int j = 0; j<128; j++){
			camera[i][j] = IR_LineScan.adcResult[i][j];
			sum += (i+1)*camera[i][j];
		}
	}
	if(sum > 381) emergency_run();
}

void emergency_run(void){
	setMotorVelocity(-0.3);
	setSrvAngle(-0.12);
}

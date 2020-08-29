#include "AEB.h"
#include "Basic.h"

IFX_EXTERN float goal_speed;
IFX_EXTERN int isMission;
int hill_count = 0;
boolean hill_flag = FALSE;

typedef struct
{
	float32           flag_0;
	float32           flag_1;
	float32           flag_2;
	float32           flag_3;
}AEB_flag;

AEB_flag flag;

void AEB_init(void) {

	flag.flag_0 = 0;
	flag.flag_1 = 0;
	flag.flag_2 = 0;
	flag.flag_3 = 0;

}

void AEB_run(void) {

	flag.flag_0 = DisScan_Raw_Result[0];
	flag.flag_1 = DisScan_Raw_Result[1];
	flag.flag_2 = DisScan_Raw_Result[2];
	flag.flag_3 = DisScan_Raw_Result[3];

	if (flag.flag_1 >= 0.25 && flag.flag_2 >= 0.25 && isMission == 2) {
		goal_speed = 0;
	}
	//else IR_setMotor0Vol(-0.6);
}

//void Hill_run(void) {
//
//	flag.flag_0 = DisScan_Raw_Result[0];
//	flag.flag_1 = DisScan_Raw_Result[1];
//	flag.flag_2 = DisScan_Raw_Result[2];
//	flag.flag_3 = DisScan_Raw_Result[3];
//
//	if (flag.flag_0 >= 0.2 && flag.flag_3 >= 0.2 && isMission == 2 && hill_count == 0) {
//		hill_flag = TRUE;
//	}
//	if (hill_flag) {
//		Hill_condition();
//		if (hill_count >= 500) {
//			hill_flag = FALSE;   hill_count = 0;
//		}
//	}
//}
//
//void Hill_condition(void) {
//	goal_speed = 40; hill_count++;
//}

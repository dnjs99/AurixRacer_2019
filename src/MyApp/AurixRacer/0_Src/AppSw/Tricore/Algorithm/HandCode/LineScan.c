#include "LineScan.h"
#include "IR_Distance.h"

#include "Basic.h"

#define STRAIGHT   0
#define RIGHT      1
#define LEFT      2
#define BEFORE      3
#define THRESHOLD   2500
#define MTHRESHOLD  500

#define ARR_SIZE    61

#define L_CAM       33
#define R_CAM       33

#define MISSION_L_MIN	29
#define MISSION_L_MAX	35

#define MISSION_R_MIN	31
#define MISSION_R_MAX	37

#define MAX_SERVO 	0.38	// max 52 = 0.40
#define MIN_SERVO	-0.60	// min -50 = -0.62

#define OBS_COUNT	3

#define N_TARGETSPEED 80

IFX_EXTERN float goal_speed;
// InfineonRacer_t IR_Ctrl  < \brief  global data
/*      ={64, 64, FALSE  };*/


uint32 idx, pixel; //pixel의 min 값
uint32 StraightLine_L = 64;
uint32 StraightLine_R = 64;
uint32 half_camsize = 30;
sint32 state_LineScan;

uint32 Line_L, Line_R; //현재 min pixel 값

sint32 dL_pixel = 0, dR_pixel = 0; //직선pixel과의 차이

float servo_angle = 0;   //   -35 ~ 34 입력, 나중에 100 나누고 -0.12
float servo_before = 0;
float servo_weight = 0.025; //0.05
float speed_weight = 0.2;

uint32 flag_L[ARR_SIZE], flag_R[ARR_SIZE];
float nom_L[ARR_SIZE], nom_R[ARR_SIZE];
float Line_L_sum = 0;
float Line_R_sum = 0;
float Line_avg = 0;

int min_L = 4096, min_R = 4096;

int Lane_num = 0;

int isMission = 0;
int mission_count = 0;
int normal_count = 0;
int detect_count_L = 0;
int detect_count_R = 0;
int Dis_count = 0;
int obstacle_mode = 0;
int mode_count = 0;

int in_out_count = 0;

boolean FindLane_flag = TRUE;

boolean Dis_flag_1 = FALSE;
boolean Dis_flag_2 = FALSE;
boolean Dis_flag_3 = FALSE;

boolean lose_L = FALSE;
boolean lose_R = FALSE;

void DetectLane(void){
	//int flag_L, flag_R;
	int min_Line_L = 4095;
	int max_Line_L = 0;
	int min_Line_R = 4095;
	int max_Line_R = 0;
	for(pixel = 0; pixel < ARR_SIZE; pixel++){
		flag_L[pixel] = IR_LineScan.adcResult[0][pixel+StraightLine_L-half_camsize];
		flag_R[pixel] = IR_LineScan.adcResult[1][pixel+StraightLine_R-half_camsize];
		if (min_Line_L > flag_L[pixel] && THRESHOLD > flag_L[pixel]) {min_Line_L = flag_L[pixel];}
		if (max_Line_L < flag_L[pixel]) {max_Line_L = flag_L[pixel];}
		if (min_Line_R > flag_R[pixel] && THRESHOLD > flag_R[pixel]) {min_Line_R = flag_R[pixel];}
		if (max_Line_R < flag_R[pixel]) {max_Line_R = flag_R[pixel];}
		if(min_Line_L < 0) min_Line_L = 4095;
		if(min_Line_R < 0) min_Line_R = 4095;
		if(max_Line_L < 0) max_Line_L = 0;
		if(max_Line_R < 0) max_Line_R = 0;
	}
	if(min_Line_L < THRESHOLD && min_Line_R < THRESHOLD) state_LineScan = STRAIGHT;
	else if(min_Line_L > THRESHOLD && min_Line_R < THRESHOLD) state_LineScan = LEFT;
	else if(min_Line_L < THRESHOLD && min_Line_R > THRESHOLD) state_LineScan = RIGHT;
	else if(min_Line_L > THRESHOLD && min_Line_R > THRESHOLD) state_LineScan = BEFORE;


	for(pixel = 0; pixel < ARR_SIZE; pixel++) {
		if(max_Line_L <= min_Line_L) {
			nom_L[pixel] = 4095;
		} else if(max_Line_L > min_Line_L) {
			nom_L[pixel] = 4095*((float)(flag_L[pixel]-min_Line_L)/(max_Line_L-min_Line_L));
		}
		if(max_Line_R <= min_Line_R) {
			nom_R[pixel] = 4095;
		} else if(max_Line_R > min_Line_R) {
			nom_R[pixel] = 4095*((float)(flag_R[pixel]-min_Line_R)/(max_Line_R-min_Line_R));
		}
	}
}

void InfineonRacer_control_normal(void){
	min_L = 4095;
	min_R = 4095;
	Lane_num = 0;
	for(pixel = 0; pixel < ARR_SIZE; pixel++) {
		if(min_L > nom_L[pixel] && nom_L[pixel] < MTHRESHOLD) {
			min_L = nom_L[pixel];
			Line_L = pixel;
		}
		if(min_R > nom_R[pixel] && nom_R[pixel] < MTHRESHOLD) {
			min_R = nom_R[pixel];
			Line_R = pixel;
		}
	}
	switch (state_LineScan) {
	case STRAIGHT:
		//둘 다 인식
		dL_pixel = L_CAM - Line_L;
		dR_pixel = R_CAM - Line_R;
		goal_speed = N_TARGETSPEED - pow(fabs((dL_pixel + dR_pixel))/2,2)*speed_weight;
		if(goal_speed <= 50)
			goal_speed = 50;
		servo_angle = servo_angle - pow(((dL_pixel+dR_pixel)/2),3)*servo_weight;   //   -0.2
		servo_before = servo_angle;
		break;
	case LEFT:
		//오른쪽만인식
		dL_pixel = 0;
		dR_pixel = R_CAM - Line_R;
		goal_speed = 50;//N_TARGETSPEED - 10 - pow(fabs(dR_pixel),2)*speed_weight;
		//      if(goal_speed <= 40)
		//         goal_speed = 40;
		servo_angle = -35;
		//servo_angle = servo_angle - pow((dR_pixel),3)*servo_weight;
		servo_before = servo_angle;
		break;
	case RIGHT:
		//왼쪽만 인식
		dL_pixel = L_CAM - Line_L;
		dR_pixel = 0;
		goal_speed = 50;//N_TARGETSPEED - 10 - pow(fabs(dR_pixel),2)*speed_weight;
		//      if(goal_speed <= 40)
		//         goal_speed = 40;
		servo_angle = 34;
		//servo_angle = servo_angle - pow((dL_pixel),3)*servo_weight;
		servo_before = servo_angle;
		break;
	case BEFORE:
		//둘다 인식안됨
		dL_pixel = 0;
		dR_pixel = 0;
		goal_speed = 35;
		servo_angle = servo_before; //직전 값
		break;
	default:
		break;
	}
	servo_angle = servo_angle/100 - 0.12;
	if(servo_angle >= MAX_SERVO)
		servo_angle = MAX_SERVO;
	else if(servo_angle <= MIN_SERVO)
		servo_angle = MIN_SERVO;

	setSrvAngle(servo_angle);

	normal_count++;
	if (normal_count > 1000) {
		normal_count = 200;
	}
}

int InfineonRacer_detect_mission(void) {
	detect_count_L = 0;
	detect_count_R = 0;
	for(pixel = 20; pixel < ARR_SIZE; pixel++){
		if(nom_L[pixel] < MTHRESHOLD) {
			detect_count_L++;
		}
		if(nom_R[pixel-20] < MTHRESHOLD) {
			detect_count_R++;
		}
	}
	Line_avg = (detect_count_L + detect_count_R)/2.0;
	if(isMission == 0 && Line_avg >= 6 && Line_avg <= 11){// && normal_count >= 200) {
		isMission = 1;
	}
	if(isMission == 1 && Line_avg >= 6 && Line_avg <= 11 && mission_count >= 300 && mode_count >= 10) {
		isMission = 2;
	}
	return isMission;
}

void FindLane_Mission(void) {
	min_L = 4095;
	min_R = 4095;

	for(pixel = 10; pixel < 15; pixel++) {
		if(min_L > nom_L[pixel] && nom_L[pixel] < MTHRESHOLD) {
			min_L = nom_L[pixel];
		}
		if(min_R > nom_R[ARR_SIZE-pixel-1] && nom_R[ARR_SIZE-pixel-1] < MTHRESHOLD) {
			min_R = nom_R[ARR_SIZE-pixel-1];
		}
	}
	if(min_L == 0 && min_R != 0) {
		Lane_num = 2;   FindLane_flag = FALSE;
	}
	else if(min_L != 0 && min_R == 0) {
		Lane_num = 1;   FindLane_flag = FALSE;
	}
	else   {
		Lane_num = 0; FindLane_flag = TRUE;
	}
}

void InfineonRacer_modeselect_mission(void) {
	if(Dis_flag_1 == FALSE && Dis_flag_2 == FALSE && Dis_flag_3 == FALSE) {
		float dif = Dis[1]-Dis[2];
		if(Dis[1] < 90 && Dis[2] < 90 && servo_before < 15 && servo_before > -15 && Dis[0] > 90 && Dis[3] > 90){
			Dis_flag_1 = TRUE;   Dis_flag_2 = FALSE;	Dis_flag_3 = FALSE;
			obstacle_mode = 1;
			Dis_count = 0;
		}
		else if(((Dis[3] < 95 && servo_before > 15) || (Dis[1] < 90 && Dis[2] < 90 && dif > 5))){ //1차선 우회전, 2차선 우회전
			Dis_flag_1 = TRUE;   Dis_flag_2 = FALSE;	Dis_flag_3 = FALSE;
			obstacle_mode = 2;
			Dis_count = 0;
		}
		else if(((Dis[0] < 95 && servo_before < -10	) || (Dis[1] < 90 && Dis[2] < 90 && dif < -5))){ //1차선 좌회전, 2차선 좌회전
			Dis_flag_1 = TRUE;   Dis_flag_2 = FALSE;	Dis_flag_3 = FALSE;
			obstacle_mode = 3;
			Dis_count = 0;
		}
		else {
			Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE; Dis_flag_3 = FALSE;
			obstacle_mode = 0;
			Dis_count = 0;
		}
	}
}

void YS(float change_angle){
	servo_angle = change_angle;
	servo_angle = servo_angle/100 - 0.12;
	setSrvAngle(servo_angle);
}

void InfineonRacer_detectLane_mission(void) {
	min_L = 4095;
	min_R = 4095;
	for (pixel = 0; pixel < ARR_SIZE-10; pixel++) {
		if (min_L > nom_L[pixel] && nom_L[pixel] < MTHRESHOLD) {
			min_L = nom_L[pixel];
			Line_L = pixel;
		}
		if (min_R > nom_R[pixel+10] && nom_R[pixel+10] < MTHRESHOLD) {
			min_R = nom_R[pixel+10];
			Line_R = pixel+10;
		}
	}
	if (min_L > THRESHOLD) lose_L = TRUE;
	else lose_L = FALSE;

	if (min_R > THRESHOLD) lose_R = TRUE;
	else lose_R = FALSE;

	switch (obstacle_mode) {
	case 0:   // 일반 주행
		mode_count++;
		if (Lane_num == 0) {
			dL_pixel = L_CAM - Line_L;
			dR_pixel = R_CAM - Line_R;
			goal_speed = 30;
			servo_angle = servo_angle - pow(((dL_pixel+dR_pixel)/2),3)*servo_weight;   //   -0.2
			servo_before = servo_angle;
		}
		else if (Lane_num == 1) {
			if(lose_L == FALSE) {
				dL_pixel = L_CAM - Line_L;
				dR_pixel = 0;
				goal_speed = 40 - pow(fabs(dL_pixel),2)*speed_weight;
				if(goal_speed <= 30)
					goal_speed = 30;
				if(dL_pixel <= 0)
					servo_angle = servo_angle + pow((dL_pixel), 2)*servo_weight*25;	// 1차선 바깥 25
				//servo_angle = servo_angle - dL_pixel*servo_weight*300;
				else if(dL_pixel > 0)
					servo_angle = servo_angle - pow((dL_pixel), 2)*servo_weight*(2.5);	// 1차선 안쪽2.5
				//servo_angle = servo_angle - dL_pixel*servo_weight*70;
			}
			else if(lose_L == TRUE) {
				servo_angle = servo_before;
			}
		}
		else if (Lane_num == 2) {
			if(lose_R == FALSE) {
				dL_pixel = 0;
				dR_pixel = R_CAM - Line_R;
				goal_speed = 40 - pow(fabs(dR_pixel),2)*speed_weight;
				if(goal_speed <= 30)
					goal_speed = 30;
				if(dR_pixel <= 0)
					servo_angle = servo_angle + pow((dR_pixel), 2)*servo_weight*(3.3);	// 2차선 안쪽
				//servo_angle = servo_angle - dR_pixel*servo_weight*70;
				else if(dR_pixel > 0)
					servo_angle = servo_angle - pow((dR_pixel), 2)*servo_weight*27;	// 2차선 바깥
				//servo_angle = servo_angle - dR_pixel*servo_weight*300;
			}
			else if(lose_R == TRUE) {
				servo_angle = servo_before;
			}
		}
		servo_before = servo_angle;
		servo_angle = servo_angle / 100 - 0.12;
		if (servo_angle >= MAX_SERVO)
			servo_angle = MAX_SERVO;
		else if (servo_angle <= MIN_SERVO)
			servo_angle = MIN_SERVO;
		setSrvAngle(servo_angle);

		if(mode_count > 100) {
			mode_count = 50;
		}
		break;
	case 1:   // 직진
		goal_speed = 30;
		mode_count = 0;
		if (Lane_num == 1) {
			//goal_speed = 0;
			if(Dis_flag_1){
				YS(35.0);
				if( Dis_count < 45 ){Dis_flag_1 = TRUE;   Dis_flag_2 = FALSE;   Dis_flag_3 = FALSE;}
				else{Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE;   Dis_flag_3 = FALSE;}
				Dis_count++;
			}
			if (Dis_flag_2) {
				YS(30.0);
				if (Dis[0] > 20 && Dis[0] < 50) { Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE;   Dis_flag_3 = FALSE; }
				else { Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;   Dis_flag_3 = TRUE;}
			}
			if (Dis_flag_3) {
				YS(-30.0);
				if (Line_R >= MISSION_R_MAX || Line_R <= MISSION_R_MIN) { Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;   Dis_flag_3 = TRUE; }
				else { Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;   Dis_flag_3 = FALSE; }
			}

			if ((Dis_flag_1 == FALSE) && (Dis_flag_2 == FALSE) && (Dis_flag_3 == FALSE)) {Lane_num = 2; obstacle_mode = 0;}
		}
		else if (Lane_num == 2) {
			if(Dis_flag_1){
				YS(-50.0);
				if( Dis_count < 40 ){Dis_flag_1 = TRUE;   Dis_flag_2 = FALSE;   Dis_flag_3 = FALSE;} //50
				else{Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE;   Dis_flag_3 = FALSE;}
				Dis_count++;
			}
			if (Dis_flag_2) {
				YS(-25.0);
				if (Dis[3] > 20 && Dis[3] < 50) { Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE;   Dis_flag_3 = FALSE; }
				else { Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;   Dis_flag_3 = TRUE; }
			}
			if (Dis_flag_3) {
				YS(25.0);
				if (Line_L >= MISSION_L_MAX || Line_L <= MISSION_L_MIN) { Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;   Dis_flag_3 = TRUE; }
				else { Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;   Dis_flag_3 = FALSE; }
			}

			if ((Dis_flag_1 == FALSE) && (Dis_flag_2 == FALSE) && (Dis_flag_3 == FALSE)) {Lane_num = 1;   obstacle_mode = 0;}
		}
		break;
	case 2:   // 우회전
		goal_speed = 30;
		mode_count = 0;
		if (Lane_num == 1) {
			if(Dis_flag_1){
				YS(60.0);
				if( Dis_count < 50 ){Dis_flag_1 = TRUE;   Dis_flag_2 = FALSE;   Dis_flag_3 = FALSE;}
				else{Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE;   Dis_flag_3 = FALSE;}
				Dis_count++;
			}
			if (Dis_flag_2) {
				YS(60.0);
				if (Dis[0] > 30 && Dis[0] < 60) { Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE;   Dis_flag_3 = FALSE; }
				else { Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;   Dis_flag_3 = FALSE;}

				if ((Dis_flag_1 == FALSE) && (Dis_flag_2 == FALSE) && (Dis_flag_3 == FALSE)) {Lane_num = 2; obstacle_mode = 0;}
			}
		}
		else if (Lane_num == 2) {
			if(Dis_flag_1) {
				if(Dis[3] > 60) {Dis_flag_1 = TRUE;   Dis_flag_2 = FALSE;	Dis_flag_3 = FALSE;}
				else{Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE;	Dis_flag_3 = FALSE;}
			}
			if(Dis_flag_2){
				YS(-30.0);
				if (Dis[3] > 15 && Dis[3] <= 60) {Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE; Dis_flag_3 = FALSE; in_out_count = 0;}
				else{
					in_out_count++;
					if(in_out_count > 8) {	Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;	Dis_flag_3 = TRUE;}
				}
			}
			if (Dis_flag_3) {
				YS(60.0);
				if( Dis_count < 55 ){Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE; Dis_flag_3 = TRUE;}
				else { Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;   Dis_flag_3 = FALSE;}
				Dis_count++;
			}

			if ((Dis_flag_1 == FALSE) && (Dis_flag_2 == FALSE) && (Dis_flag_3 == FALSE)) {Lane_num = 1;	obstacle_mode = 0;}
		}
		break;
	case 3:   // 좌회전
		goal_speed = 30;
		mode_count = 0;
		if (Lane_num == 1) {
			if(Dis_flag_1) {
				if(Dis[0] > 60) {Dis_flag_1 = TRUE;   Dis_flag_2 = FALSE;	Dis_flag_3 = FALSE;}
				else{Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE;	Dis_flag_3 = FALSE;}
			}
			if(Dis_flag_2){
				YS(20.0);
				if (Dis[0] > 15 && Dis[0] <= 60) {Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE; Dis_flag_3 = FALSE; in_out_count = 0;}
				else{
					in_out_count++;
					if(in_out_count > 8) {	Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;	Dis_flag_3 = TRUE;}
				}
			}
			if (Dis_flag_3) {
				YS(-57.0);
				if( Dis_count < 52 ){Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE; Dis_flag_3 = TRUE;}
				else { Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;   Dis_flag_3 = FALSE;}
				Dis_count++;
			}

			if ((Dis_flag_1 == FALSE) && (Dis_flag_2 == FALSE) && (Dis_flag_3 == FALSE)) {Lane_num = 2;	obstacle_mode = 0;}
		}

		else if (Lane_num == 2) {
			if(Dis_flag_1){
				YS(-80.0);
				if( Dis_count < 40 ){Dis_flag_1 = TRUE;   Dis_flag_2 = FALSE;	Dis_flag_3 = FALSE;}
				else{Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE;	Dis_flag_3 = FALSE;}
				Dis_count++;
			}
			if (Dis_flag_2) {
				YS(-80.0);
				if (Dis[3] > 15 && Dis[3] < 65) { Dis_flag_1 = FALSE;   Dis_flag_2 = TRUE;   Dis_flag_3 = FALSE; }
				else { Dis_flag_1 = FALSE;   Dis_flag_2 = FALSE;   Dis_flag_3 = FALSE; }
			}

			if ((Dis_flag_1 == FALSE) && (Dis_flag_2 == FALSE) && (Dis_flag_3 == FALSE)) {Lane_num = 1;	obstacle_mode = 0;}
		}
		break;
	}
	mission_count++;
	if (mission_count > 1000) {
		mission_count = 300;
	}
}


void MissionZone_Detect(int MissionZone_flag){
	if(MissionZone_flag == 0 || MissionZone_flag == 2) {
		InfineonRacer_control_normal();
	}
	else if(MissionZone_flag == 1) {
		if(FindLane_flag) FindLane_Mission();
		InfineonRacer_modeselect_mission();
		InfineonRacer_detectLane_mission();
	}
}

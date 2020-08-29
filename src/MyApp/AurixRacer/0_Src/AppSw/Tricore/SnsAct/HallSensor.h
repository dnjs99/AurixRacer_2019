/*
 * HallSensor.h
 *
 *  Created on: 2019. 6. 29.
 *      Author: sal9s
 */

#ifndef HALL_SENSOR_H
#define HALL_SENSOR_H 1

#include <Ifx_Types.h>
#include "Configuration.h"
#include "SysSe/Bsp/Bsp.h"

#include "Gtm/Tim/In/IfxGtm_Tim_In.h"

#define getSpeed_rps() Hall_val.speed_rps		// Get Current Speed

#define PI 3.141592

#define getSpeed() Hall_val.Speed

typedef struct{
	float32 speed_rps;
}Hall_val_t;

void HallSensor_init();							// Configuration
void HallSensor_run();							// Calculate Current Speed

IFX_EXTERN Hall_val_t Hall_val;

#endif

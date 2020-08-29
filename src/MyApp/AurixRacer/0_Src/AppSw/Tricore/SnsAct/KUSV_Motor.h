#ifndef KUSV_MOTOR_H_
#define KUSV_MOTOR_H_ 1

#include <Ifx_Types.h>
#include "Configuration.h"
#include "SysSe/Bsp/Bsp.h"

#include "Gtm/Tom/PwmHl/IfxGtm_Tom_PwmHl.h"

#define getMotor0Vol()	IR_Motor.Motor0Vol
#define getSrvAngle() 	IR_Srv.Angle

typedef struct{
	float32 Motor0Vol;
	float32 Motor0VolU;
	float32 Motor0VolV;
	float32 Motor0VolW;
}IR_Motor_t;

typedef struct{
	float32 Angle;
}IR_Srv_t;

IFX_EXTERN IR_Motor_t IR_Motor;
IFX_EXTERN IR_Srv_t IR_Srv;

IFX_EXTERN void setMotorVelocity(float32 vel);

IFX_EXTERN void setSrvAngle(float32 angle);

IFX_EXTERN void Motor_init(void);
IFX_EXTERN void EveryMotor_run(void);

#endif

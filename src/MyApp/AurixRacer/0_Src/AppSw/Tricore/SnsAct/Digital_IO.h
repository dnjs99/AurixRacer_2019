/**
 * \file BasicPort.h
 * \brief BasicPort
 *
 * \version InfineonRacer 1_0_0
 */

#ifndef BASICPORT_H
#define BASICPORT_H 1

#include <Ifx_Types.h>
#include <stdio.h>
#include "Bsp.h"
#include "Configuration.h"
#include "ConfigurationIsr.h"
#include "Cpu/Irq/IfxCpu_Irq.h"
#include "IfxPort.h"
#include "Cpu0_Main.h"
#include "Cpu/Irq/IfxCpu_Irq.h"

#define IR_getLed0() IR_Port.led0
#define IR_getLed1() IR_Port.led1
#define IR_getLed2() IR_Port.led2
#define IR_getPort00_0() IR_Port.port00_0
#define IR_getPort00_1() IR_Port.port00_1
#define IR_getMotor0En() IR_MotorEn.Motor0Enable

typedef struct
{
	volatile boolean led0;
	volatile boolean led1;
	volatile boolean led2;
	volatile boolean port00_0;
	volatile boolean port00_1;

	volatile boolean m_inh_u;
	volatile boolean m_inh_v;
	volatile boolean m_inh_w;
} Basic_Port;

typedef struct{
	boolean Motor0Enable;
} IR_MotorEn_t;

IFX_EXTERN Basic_Port IR_Port;
IFX_EXTERN IR_MotorEn_t IR_MotorEn;

IFX_EXTERN void IR_setLed0(boolean led);
IFX_EXTERN void IR_setLed1(boolean led);
IFX_EXTERN void IR_setLed2(boolean led);

IFX_EXTERN void IR_setMotor0En(boolean enable);

IFX_EXTERN void BasicPort_init(void);
IFX_EXTERN void BasicPort_run(void);

#endif

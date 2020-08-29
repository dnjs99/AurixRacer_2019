/**
 * \file BasicPort.c
 * \brief BasicPort
 *
 * \version InfineonRacer 1_0_0
 */

#include <stdio.h>
#include <IfxPort_PinMap.h>

#include "Digital_IO.h"
#include "Configuration.h"

Basic_Port IR_Port;
IR_MotorEn_t IR_MotorEn = {FALSE};
IFX_EXTERN int isMission;
IFX_EXTERN int Lane_num;
IFX_EXTERN int obstacle_mode;
IFX_EXTERN boolean Dis_flag_1;
IFX_EXTERN boolean Dis_flag_2;
static void setOutputPin(Ifx_P *port, uint8 pin, boolean state);
static void setOutputPin(Ifx_P *port, uint8 pin, boolean state)
{
	if (state)
	{
		IfxPort_setPinState(port, pin, IfxPort_State_high);
	}
	else
	{
		IfxPort_setPinState(port, pin, IfxPort_State_low);
	}
}

void BasicPort_init(void)
{
	/* disable interrupts */
	boolean interruptState = IfxCpu_disableInterrupts();

	IR_Port.led0 = TRUE;
	IR_Port.led1 = TRUE;
	IR_Port.led2 = TRUE;

	/* LED Port output */
	IfxPort_setPinMode(LED0.port, LED0.pinIndex, IfxPort_Mode_outputPushPullGeneral);
	IfxPort_setPinPadDriver(LED0.port, LED0.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
	setOutputPin(LED0.port, LED0.pinIndex, IR_Port.led0);

	IfxPort_setPinMode(LED1.port, LED1.pinIndex, IfxPort_Mode_outputPushPullGeneral);
	IfxPort_setPinPadDriver(LED1.port, LED1.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
	setOutputPin(LED1.port, LED1.pinIndex, IR_Port.led0);

	IfxPort_setPinMode(LED2.port, LED2.pinIndex, IfxPort_Mode_outputPushPullGeneral);
	IfxPort_setPinPadDriver(LED2.port, LED2.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
	setOutputPin(LED2.port, LED2.pinIndex, IR_Port.led0);

	/* Motor Port output */

	IfxPort_setPinMode(M_INH_U.port, M_INH_U.pinIndex, IfxPort_Mode_outputPushPullGeneral);
	IfxPort_setPinPadDriver(M_INH_U.port, M_INH_U.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
	setOutputPin(M_INH_U.port, M_INH_U.pinIndex, IR_Port.m_inh_u);

	IfxPort_setPinMode(M_INH_V.port, M_INH_V.pinIndex, IfxPort_Mode_outputPushPullGeneral);
	IfxPort_setPinPadDriver(M_INH_V.port, M_INH_V.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
	setOutputPin(M_INH_V.port, M_INH_V.pinIndex, IR_Port.m_inh_v);

	IfxPort_setPinMode(M_INH_W.port, M_INH_W.pinIndex, IfxPort_Mode_outputPushPullGeneral);
	IfxPort_setPinPadDriver(M_INH_W.port, M_INH_W.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
	setOutputPin(M_INH_W.port, M_INH_W.pinIndex, IR_Port.m_inh_w);

	/* Analog Input */
	IfxPort_setPinModeInput(VADC_0.port, VADC_0.pinIndex, IfxPort_InputMode_undefined);
	IfxPort_setPinModeInput(VADC_1.port, VADC_1.pinIndex, IfxPort_InputMode_noPullDevice);
	IfxPort_setPinModeInput(VADC_2.port, VADC_2.pinIndex, IfxPort_InputMode_noPullDevice);
	IfxPort_setPinModeInput(VADC_3.port, VADC_3.pinIndex, IfxPort_InputMode_noPullDevice);

	/* Digital Input */
	IfxPort_setPinModeInput(PORT00_0.port, PORT00_0.pinIndex, IfxPort_InputMode_noPullDevice);
	IfxPort_setPinModeInput(PORT00_1.port, PORT00_1.pinIndex, IfxPort_InputMode_noPullDevice);

	IR_Port.port00_0 =  IfxPort_getPinState(PORT00_0.port, PORT00_0.pinIndex);
	IR_Port.port00_1 =  IfxPort_getPinState(PORT00_1.port, PORT00_1.pinIndex);

	/* enable interrupts again */
	IfxCpu_restoreInterrupts(interruptState);
}

void BasicPort_run(void)
{
	if(Lane_num == 1)
		IR_setLed0(TRUE);
	else if(Lane_num == 0 || Lane_num == 2)
		IR_setLed0(FALSE);
//	if(Dis_flag_1 == FALSE && Dis_flag_2 == FALSE) {
//		IR_setLed1(FALSE);
//		IR_setLed2(FALSE);
//	}
//	else if(Dis_flag_1 == TRUE && Dis_flag_2 == FALSE) {
//		IR_setLed1(TRUE);
//		IR_setLed2(FALSE);
//	}
//	else if(Dis_flag_1 == FALSE && Dis_flag_2 == TRUE) {
//		IR_setLed1(TRUE);
//		IR_setLed2(TRUE);
//	}

		if(obstacle_mode == 0){
			IR_setLed1(FALSE);
			IR_setLed2(FALSE);
		}
		else if(obstacle_mode == 1){
			IR_setLed1(FALSE);
			IR_setLed2(TRUE);
		}
		else if(obstacle_mode == 2){
			IR_setLed1(TRUE);
			IR_setLed2(FALSE);
		}
		else if(obstacle_mode == 3){
			IR_setLed1(TRUE);
			IR_setLed2(TRUE);
		}
	/* LED Port output */
	setOutputPin(LED0.port, LED0.pinIndex, IR_Port.led0);
	setOutputPin(LED1.port, LED1.pinIndex, IR_Port.led1);
	setOutputPin(LED2.port, LED2.pinIndex, IR_Port.led2);

	/* Motor output */
	setOutputPin(M_INH_U.port, M_INH_U.pinIndex, IR_Port.m_inh_u);
	setOutputPin(M_INH_V.port, M_INH_V.pinIndex, IR_Port.m_inh_v);
	setOutputPin(M_INH_W.port, M_INH_W.pinIndex, IR_Port.m_inh_w);
	/* Digital Input */
	IR_Port.port00_0 =  IfxPort_getPinState(PORT00_0.port, PORT00_0.pinIndex);
	IR_Port.port00_1 =  IfxPort_getPinState(PORT00_1.port, PORT00_1.pinIndex);
}

void IR_setMotor0En(boolean enable){
	if(enable != FALSE){
		enable = TRUE;
	}
	IR_MotorEn.Motor0Enable = enable;
	IR_Port.m_inh_u = enable;
	IR_Port.m_inh_v = enable;
	IR_Port.m_inh_w = enable;
}

void IR_setLed0(boolean led){
	if(led != FALSE){
		led = TRUE;
	}
	IR_Port.led0 = led;
}

void IR_setLed1(boolean led){
	if(led != FALSE){
		led = TRUE;
	}
	IR_Port.led1 = led;
}

void IR_setLed2(boolean led){
	if(led != FALSE){
		led = TRUE;
	}
	IR_Port.led2 = led;
}

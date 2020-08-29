#include "KUSV_Motor.h"

typedef struct
{
	float32           gtmFreq;
	float32           gtmGclkFreq;
	float32           gtmCmuClk0Freq;
}Basic_Gtm;

typedef struct
{
    Ifx_TimerValue    pwmPeriod;
    Ifx_TimerValue    tOn[3];
    struct
    {
        IfxGtm_Tom_Timer timer;
        IfxGtm_Tom_PwmHl pwm;
    }drivers;
}Motor_Pwm;

typedef struct
{
	float32 onTime; /* 0.5: -90, 1.5: 0, 2.5: +90 */
	struct
    {
        IfxGtm_Tom_Timer timerSrv;
    }drivers;
} Srv_Set;

Basic_Gtm g_Gtm;
Motor_Pwm m_Pwm;
Srv_Set srv_Set = {
		.onTime = 1.5
};

IR_Motor_t IR_Motor = {
		.Motor0Vol = 0.0,
		.Motor0VolU = 0.0,
		.Motor0VolV = 0.0,
		.Motor0VolW = 0.0
};

IR_Srv_t IR_Srv = {
		.Angle = 0.0
};

void Motor_run(void);

void MotorPWM_initTimer(void)
{
    {
        IfxGtm_Tom_Timer_Config timerConfig;
        IfxGtm_Tom_PwmHl_Config pwmHlConfig;

        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
        timerConfig.base.frequency                  = 10000; /*10KHz */
        timerConfig.base.minResolution              = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled            = FALSE;
		timerConfig.tom                             = M_TRIGGER.tom;
		timerConfig.timerChannel                    = M_TRIGGER.channel;
        timerConfig.triggerOut						= &M_TRIGGER;
        timerConfig.clock                           = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk0;

        timerConfig.base.trigger.outputEnabled      = TRUE;
        timerConfig.base.trigger.enabled            = TRUE;
        timerConfig.base.trigger.triggerPoint       = 500;
        timerConfig.base.trigger.risingEdgeAtPeriod = TRUE;

        IfxGtm_Tom_Timer_init(&m_Pwm.drivers.timer, &timerConfig);

        IfxGtm_Tom_PwmHl_initConfig(&pwmHlConfig);

        IfxGtm_Tom_ToutMapP ccx[3], coutx[3];
        ccx[0]		= &M_IN_UT;
        coutx[0]	= &M_IN_UB;
        ccx[1]		= &M_IN_VT;
        coutx[1]	= &M_IN_VB;
        ccx[2]		= &M_IN_WT;
        coutx[2]	= &M_IN_WB;

        pwmHlConfig.timer                 = &m_Pwm.drivers.timer;
        pwmHlConfig.tom                   = timerConfig.tom;
        pwmHlConfig.base.deadtime         = 0.0;
        pwmHlConfig.base.minPulse         = 1e-6;
        pwmHlConfig.base.channelCount     = 3;
        pwmHlConfig.base.emergencyEnabled = FALSE;
        pwmHlConfig.base.outputMode       = IfxPort_OutputMode_pushPull;
        pwmHlConfig.base.outputDriver     = IfxPort_PadDriver_cmosAutomotiveSpeed1;
        pwmHlConfig.base.ccxActiveState   = Ifx_ActiveState_high;
        pwmHlConfig.base.coutxActiveState = Ifx_ActiveState_high;
        pwmHlConfig.ccx                   = ccx;
        pwmHlConfig.coutx                 = coutx;

        IfxGtm_Tom_PwmHl_init(&m_Pwm.drivers.pwm, &pwmHlConfig);

        IfxGtm_Tom_Timer_run(&m_Pwm.drivers.timer);
    }

}

void Srv_initTimer(void){
    {
        IfxGtm_Tom_Timer_Config timerConfig;
        IfxGtm_Tom_Timer_initConfig(&timerConfig, &MODULE_GTM);
        timerConfig.base.frequency       = 100;
        timerConfig.base.minResolution   = (1.0 / timerConfig.base.frequency) / 1000;
        timerConfig.base.trigger.enabled = FALSE;
        timerConfig.tom                  = SRV.tom;
        timerConfig.timerChannel         = SRV.channel;
        timerConfig.clock                = IfxGtm_Tom_Ch_ClkSrc_cmuFxclk2;

        timerConfig.triggerOut                      = &SRV;
        timerConfig.base.trigger.outputEnabled      = TRUE;
        timerConfig.base.trigger.enabled            = TRUE;
        timerConfig.base.trigger.triggerPoint       = 150000/16/16;
        timerConfig.base.trigger.risingEdgeAtPeriod = TRUE;

        IfxGtm_Tom_Timer_init(&srv_Set.drivers.timerSrv, &timerConfig);

        IfxGtm_Tom_Timer_run(&srv_Set.drivers.timerSrv);
    }
}

void Motor_init(void){
    boolean  interruptState = IfxCpu_disableInterrupts();
	Ifx_GTM *gtm = &MODULE_GTM;

    {
		g_Gtm.gtmFreq = IfxGtm_Cmu_getModuleFrequency(gtm);
		IfxGtm_enable(gtm);
		IfxGtm_Cmu_setGclkFrequency(gtm, g_Gtm.gtmFreq);
		g_Gtm.gtmGclkFreq = IfxGtm_Cmu_getGclkFrequency(gtm);
		IfxGtm_Cmu_setClkFrequency(gtm, IfxGtm_Cmu_Clk_0, g_Gtm.gtmGclkFreq);
		g_Gtm.gtmCmuClk0Freq = IfxGtm_Cmu_getClkFrequency(gtm, IfxGtm_Cmu_Clk_0, TRUE);
    }

    {
    	MotorPWM_initTimer();
    	m_Pwm.pwmPeriod =  IfxGtm_Tom_Timer_getPeriod(&m_Pwm.drivers.timer);
    	m_Pwm.tOn[0] = m_Pwm.pwmPeriod /2;
    	m_Pwm.tOn[1] = m_Pwm.pwmPeriod /2;
    	m_Pwm.tOn[2] = m_Pwm.pwmPeriod /2;
    }

    {
    	Srv_initTimer();
    }

    IfxCpu_restoreInterrupts(interruptState);

    IfxGtm_Cmu_enableClocks(gtm, IFXGTM_CMU_CLKEN_FXCLK | IFXGTM_CMU_CLKEN_CLK0);

}

void Motor_run(void){
	IfxGtm_Tom_PwmHl *pwmHl = &m_Pwm.drivers.pwm;
    IfxGtm_Tom_Timer *timer = &m_Pwm.drivers.timer;
    Ifx_TimerValue halfPeriod = (m_Pwm.pwmPeriod /2);

    IR_Motor.Motor0VolU = -1; //IR_Motor.Motor0Vol; // -0.5;
    IR_Motor.Motor0VolV = IR_Motor.Motor0Vol; //-1; //-1.0 * IR_Motor.Motor0Vol;

    m_Pwm.tOn[0] =  halfPeriod + halfPeriod * IR_Motor.Motor0VolU;
    m_Pwm.tOn[1] =  halfPeriod + halfPeriod * IR_Motor.Motor0VolV;


	IfxGtm_Tom_PwmHl_setMode(pwmHl, Ifx_Pwm_Mode_centerAligned);
	IfxGtm_Tom_Timer_disableUpdate(timer);
	IfxGtm_Tom_PwmHl_setOnTime(pwmHl, m_Pwm.tOn);
	IfxGtm_Tom_Timer_applyUpdate(timer);
}

void Srv_run(void){
	IfxGtm_Tom_Timer *timer = &srv_Set.drivers.timerSrv;

	if(IR_Srv.Angle > 1.0){
		IR_Srv.Angle = 1.0;
	} else if(IR_Srv.Angle < -1.0) {
		IR_Srv.Angle = -1.0;
	}
	srv_Set.onTime = 0.8 * IR_Srv.Angle + 1.5;
	Ifx_TimerValue triggerPoint= (srv_Set.onTime * 100000) /16/16;
	IfxGtm_Tom_Timer_disableUpdate(timer);
	IfxGtm_Tom_Timer_setTrigger(timer, triggerPoint);
	IfxGtm_Tom_Timer_applyUpdate(timer);
}

void EveryMotor_run(void){
	Motor_run();
	Srv_run();
}

void setMotorVelocity(float32 vel){
	if(vel > 1.0){
		vel = 1.0;
	}
	else if(vel < -1.0){
		vel = -1.0;
	}
	IR_Motor.Motor0Vol = vel;
}

void setSrvAngle(float32 angle){
//	if(angle > 0.235){
//		angle = 0.235;
//	}
//	else if(angle < -0.483){
//		angle = -0.483;
//	}
	IR_Srv.Angle = angle;
}

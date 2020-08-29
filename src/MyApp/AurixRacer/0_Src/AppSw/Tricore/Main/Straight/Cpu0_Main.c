/**
 * \file Cpu0_Main.c
 * \brief System initialisation and main program implementation.
 *
 * \version InfineonRacer 1_0_0
 */

#include "Cpu0_Main.h"
#include "SysSe/Bsp/Bsp.h"
#include "IfxScuWdt.h"
#include "BasicStm.h"

App_Cpu g_AppCpu0; /**< \brief CPU 0 global data */

int core0_main(void)
{

    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

    g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
    g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
    g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
    g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

    IfxCpu_enableInterrupts();

    printf("Initialization started\n");

    BasicStm_init();

    printf("Background loop started\n");
    waitTime(2*TimeConst_1s);
    while (TRUE)
    {
        BasicStm_run();
        REGRESSION_RUN_STOP_PASS;
    }

    return 0;
}

/**
 * \file Configuration.h
 * \brief Global configuration
 *
 */

#ifndef CONFIGURATION_H
#define CONFIGURATION_H
/******************************************************************************/
/*----------------------------------Includes----------------------------------*/
/******************************************************************************/
#include "Ifx_Cfg.h"
#include "ConfigurationIsr.h"
#include "_Impl/IfxGlobal_cfg.h"
#include <_PinMap/IfxQspi_PinMap.h>
#include <_PinMap/IfxPort_PinMap.h>
#include <_PinMap/IfxScu_PinMap.h>
#include <_PinMap/IfxGtm_PinMap.h>

/* APPLICATION_KIT_TC237 SHIELD_BUDDY*/
#define APPLICATION_KIT_TC237 	1
#define SHIELD_BUDDY 			2

/* SHELL_ASCLIN assign, ASCLIN0*/
#define ASCLIN0			0		// For HC06 Bluetooth module
#define ASCLIN3			3		// For USB
#define SHELL_ASCLIN	ASCLIN3

#define CODE_HAND	0		// Hand code : default
#define CODE  CODE_HAND

#define CFG_ASC0_BAUDRATE       (115200.0)                   /**< \brief Define the Baudrate */
#define CFG_ASC0_RX_BUFFER_SIZE (512)                        /**< \brief Define the Rx buffer size in byte. */
#define CFG_ASC0_TX_BUFFER_SIZE (6 * 1024)                   /**< \brief Define the Tx buffer size in byte. */
	/** \} */

#if SHELL_ASCLIN == ASCLIN0
	#define SHELL_RX        IfxAsclin0_RXB_P15_3_IN
	#define SHELL_TX        IfxAsclin0_TX_P15_2_OUT
#elif SHELL_ASCLIN == ASCLIN3
	#define SHELL_RX        IfxAsclin3_RXD_P32_2_IN
	#define SHELL_TX        IfxAsclin3_TX_P15_7_OUT
#endif

	#define M_TRIGGER					IfxGtm_TOM0_0_TOUT77_P15_6_OUT
	#define M_IN_UT						IfxGtm_TOM0_3_TOUT105_P10_3_OUT
	#define M_IN_UB						IfxGtm_TOM0_4_TOUT22_P33_0_OUT
	#define M_IN_VT						IfxGtm_TOM0_2_TOUT107_P10_5_OUT
	#define M_IN_VB						IfxGtm_TOM0_5_TOUT23_P33_1_OUT
	#define M_IN_WT						IfxGtm_TOM0_1_TOUT103_P10_1_OUT
	#define M_IN_WB						IfxGtm_TOM0_6_TOUT24_P33_2_OUT

	#define SRV							IfxGtm_TOM0_12_TOUT98_P11_9_OUT
	#define SRV_SCAN                    IfxGtm_TOM0_13_TOUT99_P11_10_OUT

	#define LED_TICK					IfxPort_P10_2
	#define LED0						IfxPort_P00_4
	#define LED1						IfxPort_P00_3
	#define LED2						IfxPort_P00_2

	#define PORT00_0					IfxPort_P00_0
	#define PORT00_1					IfxPort_P00_1

	#define M_INH_U						IfxPort_P02_4
	#define M_INH_V						IfxPort_P02_3
	#define M_INH_W						IfxPort_P02_1

	#define TSL1401_SI					IfxPort_P14_0
	#define TSL1401_CLK					IfxPort_P14_1
	#define TSL1401_AO_1				0
	#define TSL1401_AO_2				1

	#define VADC_0						IfxPort_P33_10
//	#define VADC_0						IfxPort_P22_2
	#define VADC_1						IfxPort_P33_11
	#define VADC_2						IfxPort_P20_7
	#define VADC_3						IfxPort_P20_8

	#define HALL_IN						IfxGtm_TIM0_7_TIN25_P33_3_IN

#ifndef REGRESSION_RUN_STOP_PASS
#define REGRESSION_RUN_STOP_PASS
#endif

#ifndef REGRESSION_RUN_STOP_FAIL
#define REGRESSION_RUN_STOP_FAIL
#endif

#endif

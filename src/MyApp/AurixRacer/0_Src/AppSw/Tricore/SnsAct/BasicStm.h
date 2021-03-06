/**
 * \file BasicStm.h
 * \brief BasicStm
 *
 * \version InfineonRacer 1_0_0
 */


#ifndef BASICSTM_H
#define BASICSTM_H 1

#include <Ifx_Types.h>
#include <stdio.h>
#include "Bsp.h"
#include "ConfigurationIsr.h"
#include "Cpu/Irq/IfxCpu_Irq.h"
#include "IfxPort.h"
#include <Stm/Std/IfxStm.h>
#include <Src/Std/IfxSrc.h>
#include "Cpu0_Main.h"
#include "Cpu/Irq/IfxCpu_Irq.h"

IFX_EXTERN void BasicStm_init(void);
IFX_EXTERN void BasicStm_run(void);

#endif

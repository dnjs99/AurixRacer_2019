#ifndef BASICLINESCAN_H
#define BASICLINESCAN_H 1

#include <Vadc/Std/IfxVadc.h>
#include <Vadc/Adc/IfxVadc_Adc.h>

typedef struct{
   uint32 adcResult[2][128];
}IR_LineScan_t;

IFX_EXTERN IR_LineScan_t IR_LineScan;

IFX_EXTERN void LineScan_init(void);
IFX_EXTERN void LineScan_run(void);

#endif

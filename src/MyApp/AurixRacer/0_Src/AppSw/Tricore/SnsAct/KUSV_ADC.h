#ifndef KUSV_ADC_H
#define KUSV_ADC_H 1

#include <Vadc/Std/IfxVadc.h>
#include <Vadc/Adc/IfxVadc_Adc.h>
#include <Ifx_Types.h>
#include "Configuration.h"

IFX_EXTERN float32 DisScan_Raw_Result[];
IFX_EXTERN float Dis[4];

IFX_EXTERN void DisScan_init(void);
IFX_EXTERN void DisScan_run(void);
IFX_EXTERN void Distance_Get(void);
IFX_EXTERN float Dis_func(float);

#endif

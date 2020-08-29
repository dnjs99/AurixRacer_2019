#ifndef LINESCAN_H_
#define LINESCAN_H_ 1



#include <Ifx_Types.h>
#include "Configuration.h"

#define IR_getLs0Margin()      IR_Ctrl.Ls0Margin
#define IR_getLs1Margin()      IR_Ctrl.Ls1Margin




/*typedef struct{
   sint32 Ls0Margin;
   sint32 Ls1Margin;
   boolean basicTest;
}InfineonRacer_t;*/

//IFX_EXTERN InfineonRacer_t IR_Ctrl;

IFX_EXTERN void InfineonRacer_init(void);
IFX_EXTERN void DetectLane();
IFX_EXTERN void InfineonRacer_control_MS();
IFX_EXTERN int InfineonRacer_detect_mission(void);
IFX_EXTERN void InfineonRacer_control_mission(void);
IFX_EXTERN void MissionZone_Detect(int);
#endif

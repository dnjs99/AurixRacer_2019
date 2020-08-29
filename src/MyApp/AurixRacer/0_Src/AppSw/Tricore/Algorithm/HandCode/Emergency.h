#ifndef EMERGENCY_H_
#define EMERGENCY_H_ 1

#include <Ifx_Types.h>
#include "Configuration.h"
#include "SysSe/Bsp/Bsp.h"

IFX_EXTERN void emergency_detect(void);
IFX_EXTERN void emergency_run(void);

IFX_EXTERN boolean FLAG;

#endif

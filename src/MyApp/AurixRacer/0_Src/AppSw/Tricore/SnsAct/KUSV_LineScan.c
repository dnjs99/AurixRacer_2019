#include <Cpu/Std/IfxCpu.h>
#include <IfxPort_PinMap.h>

#include <SysSe/Bsp/Bsp.h>
#include <Port/Std/IfxPort.h>

#include "KUSV_LineScan.h"
#include "Configuration.h"

typedef struct
{
    IfxVadc_Adc			vadc;
    IfxVadc_Adc_Group	adcGroup;
    IfxVadc_Adc_Channel	adcChannel[2];
} LineAutoScan;

LineAutoScan LineScan;

IR_LineScan_t IR_LineScan;

void LineScan_init(void)
{
    IfxVadc_Adc_Config adcConfig;
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    IfxVadc_Adc_initModule(&LineScan.vadc, &adcConfig);

    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &LineScan.vadc);

    adcGroupConfig.groupId = IfxVadc_GroupId_0;
    adcGroupConfig.master  = adcGroupConfig.groupId;
    adcGroupConfig.arbiter.requestSlotScanEnabled = TRUE;

    adcGroupConfig.scanRequest.autoscanEnabled = TRUE;

    adcGroupConfig.scanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;

    IfxVadc_Adc_initGroup(&LineScan.adcGroup, &adcGroupConfig);

    uint32                    chnIx;
    unsigned channels;
    unsigned mask;

    IfxVadc_Adc_ChannelConfig adcChannelConfig[2];

    {
       chnIx = 0;
       IfxVadc_Adc_initChannelConfig(&adcChannelConfig[chnIx], &LineScan.adcGroup);

        adcChannelConfig[chnIx].channelId      = (IfxVadc_ChannelId)(TSL1401_AO_1);
        adcChannelConfig[chnIx].resultRegister = (IfxVadc_ChannelResult)(TSL1401_AO_1);  /* use dedicated result register */

        IfxVadc_Adc_initChannel(&LineScan.adcChannel[chnIx], &adcChannelConfig[chnIx]);

        channels = (1 << adcChannelConfig[chnIx].channelId);
        mask     = channels;
        IfxVadc_Adc_setScan(&LineScan.adcGroup, channels, mask);

       chnIx = 1;
       IfxVadc_Adc_initChannelConfig(&adcChannelConfig[chnIx], &LineScan.adcGroup);
        adcChannelConfig[chnIx].channelId      = (IfxVadc_ChannelId)(TSL1401_AO_2);
        adcChannelConfig[chnIx].resultRegister = (IfxVadc_ChannelResult)(TSL1401_AO_2);  /* use dedicated result register */

        IfxVadc_Adc_initChannel(&LineScan.adcChannel[chnIx], &adcChannelConfig[chnIx]);

        channels = (1 << adcChannelConfig[chnIx].channelId);
        mask     = channels;
        IfxVadc_Adc_setScan(&LineScan.adcGroup, channels, mask);

    }

    {
       initTime();

       IfxPort_setPinMode(TSL1401_SI.port, TSL1401_SI.pinIndex, IfxPort_Mode_outputPushPullGeneral);
      IfxPort_setPinPadDriver(TSL1401_SI.port, TSL1401_SI.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
      IfxPort_setPinState(TSL1401_SI.port, TSL1401_SI.pinIndex, IfxPort_State_low);

      IfxPort_setPinMode(TSL1401_CLK.port, TSL1401_CLK.pinIndex, IfxPort_Mode_outputPushPullGeneral);
      IfxPort_setPinPadDriver(TSL1401_CLK.port, TSL1401_CLK.pinIndex, IfxPort_PadDriver_cmosAutomotiveSpeed1);
      IfxPort_setPinState(TSL1401_CLK.port, TSL1401_CLK.pinIndex, IfxPort_State_low);

    }

}

void LineScan_run(void)
{
   uint32 chnIx;
   uint32 idx;

   IfxPort_setPinState(TSL1401_SI.port, TSL1401_SI.pinIndex, IfxPort_State_high);
   IfxPort_setPinState(TSL1401_CLK.port, TSL1401_CLK.pinIndex, IfxPort_State_low);
   waitTime(5*TimeConst_100ns);

   IfxPort_setPinState(TSL1401_SI.port, TSL1401_SI.pinIndex, IfxPort_State_high);
   IfxPort_setPinState(TSL1401_CLK.port, TSL1401_CLK.pinIndex, IfxPort_State_high);
   waitTime(5*TimeConst_100ns);

   IfxPort_setPinState(TSL1401_SI.port, TSL1401_SI.pinIndex, IfxPort_State_low);
   IfxPort_setPinState(TSL1401_CLK.port, TSL1401_CLK.pinIndex, IfxPort_State_high);
   waitTime(5*TimeConst_100ns);
    IfxVadc_Adc_startScan(&LineScan.adcGroup);


   for(idx = 0; idx < 128 ; ++idx)
   {

      IfxPort_setPinState(TSL1401_SI.port, TSL1401_SI.pinIndex, IfxPort_State_low);
       IfxPort_setPinState(TSL1401_CLK.port, TSL1401_CLK.pinIndex, IfxPort_State_low);
       waitTime(3*TimeConst_1us);

       IfxPort_setPinState(TSL1401_SI.port, TSL1401_SI.pinIndex, IfxPort_State_low);
       IfxPort_setPinState(TSL1401_CLK.port, TSL1401_CLK.pinIndex, IfxPort_State_high);
       waitTime(2*TimeConst_1us);

        for (chnIx = 0; chnIx < 2; ++chnIx)
        {
            Ifx_VADC_RES conversionResult;

            do
            {
                conversionResult = IfxVadc_Adc_getResult(&LineScan.adcChannel[chnIx]);
            } while (!conversionResult.B.VF);

            IR_LineScan.adcResult[chnIx][idx] = conversionResult.B.RESULT;
        }

   }

   IfxPort_setPinState(TSL1401_SI.port, TSL1401_SI.pinIndex, IfxPort_State_low);
   IfxPort_setPinState(TSL1401_CLK.port, TSL1401_CLK.pinIndex, IfxPort_State_low);

}

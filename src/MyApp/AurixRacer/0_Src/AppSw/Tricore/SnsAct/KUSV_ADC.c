#include <Cpu/Std/IfxCpu.h>
#include "KUSV_ADC.h"
#include "Configuration.h"
#include <math.h>

#define ADC_CHN_MAX  4

typedef struct
{
    IfxVadc_Adc vadc;
    IfxVadc_Adc_Group adcGroup;
    IfxVadc_Adc_Channel adcChannel[ADC_CHN_MAX];
} Distance_adcScan;

Distance_adcScan DisScan;

static uint32 adcChannelNum[ADC_CHN_MAX] = {
      4, 5, 6, 7
};

float32 DisScan_Raw_Result[ADC_CHN_MAX];


typedef struct
{
	float32           Value1;
	float32           Value2;
	float32           Value3;
	float32           Value4;
}DisVoltage_Value; //0 ~ 5V °ª

DisVoltage_Value value;

float Dis[4];


void DisScan_init(void){
    IfxVadc_Adc_Config adcConfig;
    IfxVadc_Adc_initModuleConfig(&adcConfig, &MODULE_VADC);

    IfxVadc_Adc_initModule(&DisScan.vadc, &adcConfig);

    IfxVadc_Adc_GroupConfig adcGroupConfig;
    IfxVadc_Adc_initGroupConfig(&adcGroupConfig, &DisScan.vadc);

    adcGroupConfig.groupId = IfxVadc_GroupId_5;
    adcGroupConfig.master  = adcGroupConfig.groupId;

    adcGroupConfig.arbiter.requestSlotBackgroundScanEnabled = TRUE;

    adcGroupConfig.backgroundScanRequest.autoBackgroundScanEnabled = TRUE;

    adcGroupConfig.backgroundScanRequest.triggerConfig.gatingMode = IfxVadc_GatingMode_always;

    IfxVadc_Adc_initGroup(&DisScan.adcGroup, &adcGroupConfig);

    uint32                    chnIx;

    IfxVadc_Adc_ChannelConfig adcChannelConfig;

    for (chnIx = 0; chnIx < ADC_CHN_MAX; ++chnIx)
    {
        IfxVadc_Adc_initChannelConfig(&adcChannelConfig, &DisScan.adcGroup);

        adcChannelConfig.channelId         = (IfxVadc_ChannelId)(adcChannelNum[chnIx]);
        adcChannelConfig.resultRegister    = (IfxVadc_ChannelResult)(adcChannelNum[chnIx]); // use register #5 and 6 for results
        adcChannelConfig.backgroundChannel = TRUE;

        IfxVadc_Adc_initChannel(&DisScan.adcChannel[chnIx], &adcChannelConfig);

        unsigned channels = (1 << adcChannelConfig.channelId);
        unsigned mask     = channels;
        IfxVadc_Adc_setBackgroundScan(&DisScan.vadc, &DisScan.adcGroup, channels, mask);
    }

    IfxVadc_Adc_startBackgroundScan(&DisScan.vadc);
}

void DisScan_run(void)
{
    uint32                    chnIx;
    volatile Ifx_VADC_RES conversionResult;

        for (chnIx = 0; chnIx < ADC_CHN_MAX; ++chnIx)
        {
            do
            {
                conversionResult = IfxVadc_Adc_getResult(&DisScan.adcChannel[chnIx]);
            } while (!conversionResult.B.VF);

            DisScan_Raw_Result[chnIx] = (float32) conversionResult.B.RESULT / 4095;

        }
}

void Distance_Get(void){
	value.Value1 = DisScan_Raw_Result[0] * 5;
	value.Value2 = DisScan_Raw_Result[1] * 5;
	value.Value3 = DisScan_Raw_Result[2] * 5;
	value.Value4 = DisScan_Raw_Result[3] * 5;

	if( Dis_func(value.Value1) > 150.0 ) Dis[0] = 150.0;
	else Dis[0] = Dis_func(value.Value1) - 10.0;

	if( Dis_func(value.Value2) > 150.0 ) Dis[1] = 150.0;
	else Dis[1] = Dis_func(value.Value2);

	if( Dis_func(value.Value3) > 150.0 ) Dis[2] = 150.0;
	else Dis[2] = Dis_func(value.Value3);

	if( Dis_func(value.Value4) > 150.0 ) Dis[3] = 150.0;
	else Dis[3] = Dis_func(value.Value4);
}

float Dis_func(float x){
	float y = 0;
	y = -18.811*pow(x, 5) + 174.63*pow(x, 4) - 631.21*pow(x,3)+ 1117.4*pow(x, 2) - 1003.7*x + 424.36;
	return y;
}

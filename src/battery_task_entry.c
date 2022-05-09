#include "battery_task.h"
#include "inc/collect_ADC.h"
#include "inc/key.h"
/* battery entry function */
int differ = 0;
uint16_t mic_old = 0;
uint8_t low_time = 0;
uint8_t off_time = 0;
bool Low_electricity=0;
/* pvParameters contains TaskHandle_t */
void battery_task_entry(void *pvParameters)
{
    FSP_PARAMETER_NOT_USED (pvParameters);

    R_ADC_Open(&g_adc0_ctrl, &g_adc0_cfg);
    R_ADC_ScanCfg(&g_adc0_ctrl, &g_adc0_channel_cfg);

    /* TODO: add your own code here */
    while (1)
    {
        read_adc();
        differ = adc_mic-mic_old;
        if(battery_voltage>3.2 && battery_voltage<3.4) //低电量警告
        {
            low_time++;
            if(low_time >= 200) //10s警告一次
            {
                low_time=0;
                Low_electricity = 1;
            }
        }
        else if(battery_voltage<=3.2) //低电量关机
        {
            off_time++;
            if(off_time >= 60)  //3S后关机
                model = 10;
        }
        else
        {
            off_time = 0;
            low_time = 0;
        }
        mic_old = adc_mic;
        vTaskDelay (50);
    }
}


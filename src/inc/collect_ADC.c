/*
 * collect_ADC.c
 *
 *  Created on: 2022年5月5日
 *      Author: Ning
 */

#include "collect_ADC.h"

bool scan_complete_flag = false;
uint16_t adc_data2=0;
uint16_t adc_data5=0;
uint16_t adc_data_old=0;
uint16_t adc_mic=0;
float battery_voltage = 0;
float coefficient=0.5; //一阶低通滤波系数

#define value_N 10
uint16_t value_buf[value_N];
uint8_t value_i=0;

void read_adc(void)
{
   R_ADC_ScanStart(&g_adc0_ctrl);
   scan_complete_flag = false;
   while (!scan_complete_flag){
       vTaskDelay (1);
   }
   R_ADC_Read(&g_adc0_ctrl, ADC_CHANNEL_2, &adc_data2);

   adc_data2 = coefficient*adc_data2+(1-coefficient)*adc_data_old;
   adc_data_old = adc_data2;           //一阶低通滤波

   value_buf[value_i++] = adc_data2;
   if(value_i>=value_N)
   {
       value_i=0;
       filter(); //中位值平均滤波法
       battery_voltage=(adc_data2/4095.0)*5.0 + 0.1;
   }

   R_ADC_Read(&g_adc0_ctrl, ADC_CHANNEL_5, &adc_data5);
   adc_mic = adc_data5;
}

void filter(void)
{
    uint8_t i=0,j=0;
    uint16_t temp=0,sum=0;

    for(j = 0; j < value_N - 1; j++) {
        for(i = 0; i < value_N - j; i++) {
            if(value_buf[i] > value_buf[i + 1]) {
                temp = value_buf[i];
                value_buf[i] = value_buf[i + 1];
                value_buf[i + 1] = temp;
            }
        }
    }
    for(i = 1; i < value_N - 1; i++) {
            sum += value_buf[i];
    }

    adc_data2=sum / (value_N - 2);
}


void adc_callback (adc_callback_args_t * p_args)
{
    FSP_PARAMETER_NOT_USED(p_args);
    scan_complete_flag = true;
}


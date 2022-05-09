/*
 * collect_ADC.h
 *
 *  Created on: 2022年5月5日
 *      Author: Ning
 */

#ifndef INC_COLLECT_ADC_H_
#define INC_COLLECT_ADC_H_

#include "hal_data.h"

extern bool scan_complete_flag;
extern float battery_voltage;
extern uint16_t adc_mic;
extern int differ;

void read_adc(void);
void filter(void);

#endif /* INC_COLLECT_ADC_H_ */

/*
 * key.h
 *
 *  Created on: 2022年5月1日
 *      Author: Ning
 */

#ifndef INC_KEY_H_
#define INC_KEY_H_
#include "hal_data.h"

extern bool open_flag;
extern uint8_t model;
extern int16_t Key1_IN[7];
extern bool Low_electricity;
//uint16_t Key2_IN[7]={0};
//uint16_t Key3_IN[7]={0};

void SmartConfigKey(void);


#endif /* INC_KEY_H_ */

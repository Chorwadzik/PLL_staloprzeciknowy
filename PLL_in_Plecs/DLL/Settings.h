/*
 * Settings.h
 *
 *  Created on: 28 sty 2022
 *      Author: MrTea
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifndef FLAG_SIMULATION

#define PWM_CLOCK 125000000
#define SD_CLOCK 20000000
#define CONV_FREQUENCY 50000
#define CONV_PERIOD (1.0/CONV_FREQUENCY)
#define OVERSAMPLE 1
//1-ADC, 0-SD
#define SELECT_MEAS 0

#define ADC_SAMPLES 1
#define SAMPLING_TIME (1.0/CONV_FREQUENCY/(1.0+OVERSAMPLE))
#define CYCLE_PERIOD (PWM_CLOCK/CONV_FREQUENCY/2)
#define DEF_OSR (SD_CLOCK/CONV_FREQUENCY/2)

#endif // !FLAG_SIMULATION

#define DC_VOLTAGE_FILTER_SIMPLE 0
#define DC_VOLTAGE_FILTER_CIC 1
#define DC_VOLTAGE_FILTER_KALMAN 0

void Common_variable_init();
void CIC1_filter_init(struct CIC1_struct *CIC, float max_value, Uint16 OSR, Uint16 decimation_ratio);
void CIC2_filter_init(struct CIC2_struct *CIC, float max_value, Uint16 OSR, Uint16 decimation_ratio);
void CIC1_adaptive_filter_init(struct CIC1_adaptive_struct *CIC, float max_value, Uint16 OSR);

#ifdef __cplusplus
}
#endif // extern "C"

#endif /* SETTINGS_H_ */

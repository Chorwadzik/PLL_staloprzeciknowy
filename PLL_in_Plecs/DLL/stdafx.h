// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include "DllHeader.h"
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

typedef UINT16 Uint16;
typedef UINT32 Uint32;
typedef UINT64 Uint64;
typedef INT64 int64;
typedef INT32 int32;
typedef INT16 int16;

#define Resonant_mult3_calc_CLAasm Resonant_mult3_calc 
#define Resonant_mult3_calc2_CLAasm Resonant_mult3_calc2 
#define Resonant_filter_calc_CLAasm Resonant_filter_calc 
#define Filter1_calc_CLAasm Filter1_calc 
#define PI_antiwindup_fast_ff_CLAasm PI_antiwindup_fast_ff 
#define PI_antiwindup_fast_CLAasm PI_antiwindup_fast 
#define PI_antiwindup_CLAasm PI_antiwindup 
#define Resonant_mult_calc_CLAasm Resonant_mult_calc 
#define CIC2_filter_CLAasm CIC2_filter 
#define CIC1_filter_CLAasm CIC1_filter 
#define Resonant_calc_CLAasm Resonant_calc 
#define CIC1_adaptive_filter_CLAasm CIC1_adaptive_filter 
#define CIC1_adaptive_global_CLAasm CIC1_adaptive_global_calc 
#define Kalman_calc_CPUasm Kalman_calc 

#define GPIO_SET(pin) aState_global->outputs[pin] = 1  
#define GPIO_CLEAR(pin) aState_global->outputs[pin] = 0  
#define GPIO_TOGGLE(pin) aState_global->outputs[pin] ^= 1  
#define GPIO_READ(pin) ((Uint32)aState_global->inputs[pin]) 
#define GPIO_WRITE(pin, val) aState_global->outputs[pin] = val

#define PWM_EN_AC1_CM          2
#define PWM_EN_AC2_CM          3
#define PWM_EN_LV1_CM          8
#define PWM_EN_LV2_CM          9
#define REL_GRID_CM          10

#define TRIG_0 aState_global->inputs[0]
#define TRIG_180 (!aState_global->inputs[0])

#define SINCOS_HARMONICS 50

#define CIC_upsample1 10
#define CIC_upsample2 100

#define FLAG_SIMULATION 1

#define PWM_CLOCK 125000000
#define SD_CLOCK 20000000
#define CONV_FREQUENCY (1.0/aState_global->parameters[0])
#define CONV_PERIOD (1.0/CONV_FREQUENCY)
#define OVERSAMPLE (aState_global->parameters[5])
//1-ADC, 0-SD
#define SELECT_MEAS (aState_global->parameters[6])

#define ADC_SAMPLES 1
#define SAMPLING_TIME (aState_global->parameters[0]/(1.0 + OVERSAMPLE))
#define CYCLE_PERIOD (PWM_CLOCK/FREQUENCY)
#define DEF_OSR (SD_CLOCK/FREQUENCY)

#include "Controllers.h"
#include "Converter.h"
#include "Settings.h"
#include "Kalman.h"
#include "Kalman_gains.h"



union ALARM
{
    Uint32 all[2];
    struct
    {
        Uint16 FLT1A : 1;
        Uint16 RDY1A : 1;
        Uint16 FLT1B : 1;
        Uint16 RDY1B : 1;
        Uint16 FLT2A : 1;
        Uint16 RDY2A : 1;
        Uint16 FLT2B : 1;
        Uint16 RDY2B : 1;
        Uint16 FLT3A : 1;
        Uint16 RDY3A : 1;
        Uint16 FLT3B : 1;
        Uint16 RDY3B : 1;
        Uint16 FLT4A : 1;
        Uint16 RDY4A : 1;
        Uint16 FLT4B : 1;
        Uint16 RDY4B : 1;
        //16bits
        Uint16 I_conv_a_H : 1;
        Uint16 I_conv_a_L : 1;
        Uint16 I_conv_b_H : 1;
        Uint16 I_conv_b_L : 1;

        Uint16 I_conv_c_H : 1;
        Uint16 I_conv_c_L : 1;
        Uint16 I_conv_n_H : 1;
        Uint16 I_conv_n_L : 1;

        Uint16 I_conv_rms_a : 1;
        Uint16 I_conv_rms_b : 1;
        Uint16 I_conv_rms_c : 1;
        Uint16 I_conv_rms_n : 1;

        Uint16 U_dc_p_H : 1;
        Uint16 U_dc_p_L : 1;
        Uint16 U_dc_n_H : 1;
        Uint16 U_dc_n_L : 1;
        //32bits
        Uint16 U_dc_balance : 1;
        Uint16 Temperature_H : 1;
        Uint16 Temperature_L : 1;

        Uint16 no_comm_REL1 : 1;
        Uint16 no_comm_REL2 : 1;
        Uint16 no_comm_PHASE : 1;
        Uint16 FLT_DRV1 : 1;
        Uint16 FLT_DRV2 : 1;
        Uint16 FLT_24V : 1;

        Uint16 Not_enough_data : 1;
        Uint16 CONV_SOFTSTART : 1;
        Uint16 FLT_SUPPLY : 1;

        Uint16 TZ_FPGA_FLT : 1;
        Uint16 TZ_CLOCKFAIL : 1;
        Uint16 TZ_EMUSTOP : 1;
        Uint16 TZ : 1;
        //16bits
        Uint16 rx1_error_slave : 1;
        Uint16 rx1_overrun_slave : 1;
        Uint16 rx2_error_slave : 1;
        Uint16 rx2_overrun_slave : 1;

        Uint16 rsvd1 : 12;
    }bit;
};

struct Measurements_struct
{
    float input;
    float Temperature1;
    float Temperature2;
};

struct Measurements_alarm_struct
{
    float I_conv;
    float I_conv_rms;
    float U_dc;
    float U_dc_balance;
    float Temp;
};

extern union ALARM alarm;
extern struct Measurements_struct Meas;
extern struct Measurements_alarm_struct Meas_alarm_H;
extern struct Measurements_alarm_struct Meas_alarm_L;

extern struct trigonometric_struct sincos_table[SINCOS_HARMONICS];
extern struct trigonometric_struct sincos_table_comp[SINCOS_HARMONICS];

extern struct CIC1_adaptive_global_struct CIC1_adaptive_global;

extern struct SimulationState *aState_global;
// reference additional headers your program requires here

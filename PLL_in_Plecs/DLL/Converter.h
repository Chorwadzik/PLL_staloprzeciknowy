// Tomasz Święchowicz swiechowicz.tomasz@gmail.com

#include "stdafx.h"

#pragma once
#ifndef Converter_H_
#define Converter_H_

enum Converter_state_enum
{
    Conv_softstart,
    Conv_relay,
    Conv_active,
    __dummybig_Conv = 300000
};

struct Converter_struct
{
    struct Resonant_struct Resonant_U_grid;
    struct CIC1_adaptive_struct CIC1_U_grid_1h;
    float U_grid_1h;
    float U_grid_1h_div;

    struct CIC1_adaptive_struct CIC1_I_conv;
    float I_conv;

    struct Filter1_struct U_in_Filter1;
    struct Filter1_struct U_dc_Filter1;
    struct Filter1_struct U_dc_ref_Filter1;
    struct Filter1_struct Iq_ref_Filter1;
    struct CIC1_adaptive_struct CIC1_U_dc;
    float U_dc_Kalman;
    float U_dc_filter;

    struct PI_struct PI_U_dc;
    struct Integrator_struct Integrator;

    float Id_ref, Iq_ref;
    float I_ref, I_err, U_ref;
    float zero_error;

    //Resonant
    float compensation;
    float resonant_odd_number;
    float resonant_even_number;
    float Kp_I;
    struct Resonant_struct Resonant_I_a_odd[25];
    struct Resonant_struct Resonant_I_a_even[2];

    float F_SAB;
    float P_ref;
    float P_ref_internal;
    float I_ref_internal;
    float alpha_DCM;
    float alpha_CCM;
    float alpha;

    float I_TR_max;
    float alpha_max_dcm;
    float alpha_max_ccm;
    float alpha_max;
    float I_ref_max_dcm;
    float I_ref_max_ccm;
    float I_ref_max;
    float P_ref_max;

    float Ts;
    float I_lim;
    float U_dc_ref;

    float w_filter;
    float f_filter;
    struct trigonometric_struct trig_table;
    float theta;
    float R_load;

    float C_conv;
    float L_conv;
    float L_TR;
    float TR_ratio;
    float C_dc;

    float duty[2];
    float shift_LV[2];
    float shift_HV[2];
    float RDY;
    float enable;

    enum Converter_state_enum state, state_last;
};

extern struct Converter_struct Conv;

void Converter_1PH_calc();

#endif /* Converter_H_ */

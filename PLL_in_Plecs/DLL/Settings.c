/*
 * Settings.cpp
 *
 *  Created on: 28 sty 2022
 *      Author: MrTea
 */

#include "stdafx.h"
#include <math.h>

void CIC1_filter_init(struct CIC1_struct *CIC, float max_value, Uint16 OSR, Uint16 decimation_ratio)
{
    CIC->decimation_ratio = decimation_ratio;
    CIC->OSR = OSR;
    CIC->div_OSR = 1.0f / OSR;
    CIC->range_modifier = (float)(1UL << 31) / OSR / max_value;
    CIC->div_range_modifier = 1.0f / CIC->range_modifier;
}

void CIC2_filter_init(struct CIC2_struct *CIC, float max_value, Uint16 OSR, Uint16 decimation_ratio)
{
    CIC->decimation_ratio = decimation_ratio;
    CIC->OSR = OSR;
    CIC->div_OSR = 1.0f / (float)OSR;
    CIC->range_modifier = (float)(1UL << 31) / (float)OSR / (float)OSR / max_value;
    CIC->div_range_modifier = 1.0f / CIC->range_modifier;
}

void CIC1_adaptive_filter_init(struct CIC1_adaptive_struct *CIC, float max_value, Uint16 OSR)
{
    CIC->range_modifier = (float)(1UL << 31) / OSR / max_value;
    CIC->div_range_modifier = 1.0f / CIC->range_modifier;
}

void Common_variable_init()
{
    CIC1_adaptive_global.Ts = Conv.Ts;

    Conv.compensation = 2.0f;
    Conv.I_lim = 3.0f;
    Conv.U_dc_ref = 700.0f;
    Conv.I_TR_max = 900.0f;

    Conv.f_filter = 50.0f;
    Conv.w_filter = Conv.f_filter * MATH_2PI;
    Conv.R_load = 100.0f;

    ///////////////////////////////////////////////////////////////////

    Conv.Resonant_U_grid.trigonometric.ptr = &sincos_table[0];

    Conv.Resonant_U_grid.trigonometric_comp.ptr = &sincos_table[0];

    Conv.Resonant_U_grid.gain = 2.0f * (1.0f / (MATH_1_E * 0.02f)) / (MATH_2PI * 50.0f);

    float OSR = (Uint16)(0.02f / Conv.Ts + 0.5f);
    CIC1_adaptive_filter_init(&Conv.CIC1_U_grid_1h, 1000.0f, OSR);
    
    CIC1_adaptive_filter_init(&Conv.CIC1_I_conv, powf(2.0f * 32.0f, 2.0f), OSR);

    ///////////////////////////////////////////////////////////////////

    CIC1_adaptive_filter_init(&Conv.CIC1_U_dc, 1000.0f, OSR);
    Conv.U_in_Filter1.Ts_Ti = Conv.Ts / (0.005f);
    Conv.U_dc_Filter1.Ts_Ti = Conv.Ts / (0.005f);
    Conv.Iq_ref_Filter1.Ts_Ti = Conv.Ts / (0.005f);
    Conv.U_dc_ref_Filter1.Ts_Ti = Conv.Ts / (0.005f);
    Conv.U_dc_ref_Filter1.out = Conv.U_dc_ref;

    register float alfa = 2.0f;
    register float STC = 0.005f;
    if (DC_VOLTAGE_FILTER_CIC) STC = 0.63212 * 0.02f;
    float kp_dc = Conv.C_dc / (alfa * STC);
    float ti_dc = alfa * alfa * STC;

    Conv.PI_U_dc.Ts_Ti = Conv.Ts / ti_dc;
    Conv.PI_U_dc.Kp = kp_dc;
    Conv.PI_U_dc.lim_H = 0.0f*Conv.I_lim;
    Conv.PI_U_dc.lim_L = -Conv.I_lim;

    ///////////////////////////////////////////////////////////////////

    register float p_pr_i = Conv.L_conv / (3.0f * Conv.Ts);
    Conv.Kp_I = p_pr_i;
    register float r_pr_i = Conv.L_conv * MATH_PI / Conv.Ts;
    r_pr_i /= MATH_2PI * 50.0f;

    Conv.resonant_odd_number = 1.0f;
    Conv.resonant_even_number = 0.0f;

    Uint16 i;
    for (i = 0; i < sizeof(Conv.Resonant_I_a_odd) / sizeof(Conv.Resonant_I_a_odd[0]); i++)
    {
       Conv.Resonant_I_a_odd[i].gain = 10.0f * 2.0f * r_pr_i / (float)(2 * i + 1);
       Conv.Resonant_I_a_odd[i].trigonometric.ptr = &sincos_table[2 * i];
       Conv.Resonant_I_a_odd[i].trigonometric_comp.ptr = &sincos_table_comp[2 * i];
    }

    for (i = 0; i < sizeof(Conv.Resonant_I_a_even) / sizeof(Conv.Resonant_I_a_even[0]); i++)
    {
       Conv.Resonant_I_a_even[i].gain = 10.0f * 2.0f * r_pr_i / (float)(2 * i + 2);
       Conv.Resonant_I_a_even[i].trigonometric.ptr = &sincos_table[2 * i + 1];
       Conv.Resonant_I_a_even[i].trigonometric_comp.ptr = &sincos_table_comp[2 * i + 1];
    }

    for (i = 0; i < SINCOS_HARMONICS; i++)
    {
        sincos_table[i].cosine = cosf(Conv.w_filter * Conv.Ts * (float)(i + 1));
        sincos_table[i].sine = sinf(Conv.w_filter * Conv.Ts * (float)(i + 1));
        sincos_table_comp[i].cosine = cosf(Conv.compensation * Conv.w_filter * Conv.Ts * (float)(i + 1));
        sincos_table_comp[i].sine = sinf(Conv.compensation * Conv.w_filter * Conv.Ts * (float)(i + 1));
    }
}




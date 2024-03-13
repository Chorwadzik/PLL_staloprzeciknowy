// Tomasz Œwiêchowicz swiechowicz.tomasz@gmail.com

#include "stdafx.h"

struct Converter_struct Conv;

struct Measurements_struct Meas;
union ALARM alarm = { 0 };

struct Measurements_alarm_struct Meas_alarm_H;
struct Measurements_alarm_struct Meas_alarm_L;

struct trigonometric_struct sincos_table[SINCOS_HARMONICS];
struct trigonometric_struct sincos_table_comp[SINCOS_HARMONICS];
struct CIC1_adaptive_global_struct CIC1_adaptive_global;

struct Kalman_struct Kalman_I_grid[3];
struct Kalman_struct Kalman_U_grid[3];
struct Kalman_struct Kalman_U_dc;

float Kalman_gain_ac[2 * KALMAN_HARMONICS];
float Kalman_gain_dc[2 * KALMAN_HARMONICS];

struct trigonometric_struct sincos_kalman_dc_table[KALMAN_HARMONICS];
struct trigonometric_struct sincos_kalman_ac_table[KALMAN_HARMONICS];

struct SimulationState *aState_global;

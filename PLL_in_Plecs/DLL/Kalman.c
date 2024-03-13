// Tomasz Œwiêchowicz swiechowicz.tomasz@gmail.com

#include "stdafx.h" 
#include "math.h"

void Kalman_calc(struct Kalman_struct *Kalman, struct trigonometric_struct sincos_table[], float input)
{
    Uint16 i;

    register float prediction = Kalman->states[0];
    Kalman->states[1] = 0;
    for (i = 1; i < KALMAN_HARMONICS; i++)
    {
        register float temp = sincos_table[i - 1].cosine * Kalman->states[2 * i] - sincos_table[i - 1].sine * Kalman->states[2 * i + 1];
        Kalman->states[2 * i + 1] = sincos_table[i - 1].sine * Kalman->states[2 * i] + sincos_table[i - 1].cosine * Kalman->states[2 * i + 1];
        Kalman->states[2 * i] = temp;
        prediction += Kalman->states[2 * i];
    }
    Kalman->estimate = prediction;
    register float error = input - prediction;
    register float *gain = (float*)Kalman->gain.ptr;
    for (i = 0; i < KALMAN_HARMONICS; i++)
    {
        Kalman->states[2 * i] += *gain++ * error;
        Kalman->states[2 * i + 1] += *gain++ * error;
        Kalman->rms_values[i] = sqrtf(Kalman->states[2 * i + 1] * Kalman->states[2 * i + 1] + Kalman->states[2 * i] * Kalman->states[2 * i]);
    }
}

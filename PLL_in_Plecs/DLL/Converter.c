// Tomasz Święchowicz swiechowicz.tomasz@gmail.com

#include "stdafx.h"

void Converter_1PH_calc()
{
    ////////////////////////////////////////////////////////////////////////////////////////////


    Integrator_Calc(&Conv.Integrator, Meas.input);
    //Conv.Integrator.out = 10;
    aState_global->outputs[0] = Conv.Integrator.out;
}

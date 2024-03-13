// Tomasz �wi�chowicz swiechowicz.tomasz@gmail.com

// main.c : Defines the exported functions for the DLL application.

#include "stdafx.h"
#include "stddef.h"

//! Debug :
//. Change the view to expert view using Tools > Settings > Expert settings.
//2. Attach the DLL to the PLECS process using Debug > Attach to process > PLECS.exe.
//3. In main.c, create a breakpoint at the line y = kp * e + ki * i.

DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
	aSizes->numInputs = 1;
	aSizes->numOutputs = 2;
	aSizes->numStates = 0;
	aSizes->numParameters = 1; //number of user parameters passed in
}

//This function is automatically called at the beginning of the simulation
DLLEXPORT void plecsStart(struct SimulationState* aState)
{
	memset(&Conv, 0, sizeof(Conv));

	Conv.Ts = aState->parameters[0];
	Conv.PI_U_dc.Kp = 1.0;
	Conv.PI_U_dc.Ts_Ti = Conv.Ts / 3e-3;
	//Conv.PI_U_dc.lim_H = 1000.0f;
	//Conv.PI_U_dc.lim_L = -1000.0f;
	
	//////////////////////////////////////////////////////////////////
	aState_global = aState;
}

//This function is automatically called every sample time
//output is written to DLL output port after the output delay
DLLEXPORT void plecsOutput(struct SimulationState* aState)
{
    memset(&Conv, 0, sizeof(Conv));

    if (TRIG_0 || TRIG_180)
	{
		Meas.input = aState_global->inputs[0];

		////////////////////////////////////////////
		//Conv.Integrator.out = 10;
		//Conv.Integrator.out = 10;

 
		aState_global->outputs[1] = Meas.input;



		/////////////////////////////////////////////

		static float first = 0;
		Converter_1PH_calc();

		//aState_global->outputs[0] = 1;
    }


}

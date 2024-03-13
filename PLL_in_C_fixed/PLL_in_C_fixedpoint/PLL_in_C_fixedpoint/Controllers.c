#include "stdafx.h"


void reciprocal_calc_INT32(struct reciprocal_struct_INT32 *reciprocal, int16 Num, int16 Den)
{
	reciprocal->Yp = 16384;

	reciprocal->Ypp = reciprocal->Yp * Den;
	reciprocal->Ypp = reciprocal->Ypp >> 14;
	reciprocal->Ypp = 32767 - (INT16)reciprocal->Ypp;
	reciprocal->Yp = (INT16)reciprocal->Yp * (INT16)reciprocal->Ypp;
	reciprocal->Yp = reciprocal->Yp >> 14;

	reciprocal->Ypp = reciprocal->Yp * Den;
	reciprocal->Ypp = reciprocal->Ypp >> 14;
	reciprocal->Ypp = 32767 - (INT16)reciprocal->Ypp;
	reciprocal->Yp = (INT16)reciprocal->Yp * (INT16)reciprocal->Ypp;
	reciprocal->Yp = reciprocal->Yp >> 14;

	reciprocal->Ypp = reciprocal->Yp * Den;
	reciprocal->Ypp = reciprocal->Ypp >> 14;
	reciprocal->Ypp = 32767 - (INT16)reciprocal->Ypp;
	reciprocal->Yp = (INT16)reciprocal->Yp * (INT16)reciprocal->Ypp;
	reciprocal->Yp = reciprocal->Yp >> 14;

	reciprocal->Ypp = reciprocal->Yp * Den;
	reciprocal->Ypp = reciprocal->Ypp >> 14;
	reciprocal->Ypp = 32767 - (INT16)reciprocal->Ypp;
	reciprocal->Yp = (INT16)reciprocal->Yp * (INT16)reciprocal->Ypp;
	reciprocal->Yp = reciprocal->Yp >> 14;		

	reciprocal->out = reciprocal->Yp;
}


float to_float_calc_INT32(struct to_float_strtuct_INT32* to_float, int16 x)
{
	to_float->out = (float)x / (float)(1 << 14);

	return to_float->out;
}

int16 to_fixed_calc_INT32(struct to_fixed_strtuct_INT32* to_fixed, float x)
{
	register float y;
	y = x * (float)(1 << 14);
	to_fixed->out = (int16)y;

	return to_fixed->out;
}
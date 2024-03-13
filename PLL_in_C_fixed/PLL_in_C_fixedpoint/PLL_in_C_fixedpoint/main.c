#include "stdafx.h"

void main() {

	float x, x_1, x_2, M, one;
	int16 xf;
	M = 271; /// (256,1024)
	x = M/(float)(1<<9);

	xf = to_fixed_calc_INT32(&to_fixed, x);
	x_1 = to_float_calc_INT32(&to_float, xf);

	reciprocal_calc_INT32(&reciprocal, 1, xf);
	x_2 = to_float_calc_INT32(&to_float, reciprocal.out>>9);


	one = M * x_2;

}
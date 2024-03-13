
#include "stdafx.h"


#pragma once
#ifndef Controllers_H_
#define Controllers_H_

struct reciprocal_struct_INT32
{
	int16 out;
	int32 Yp;
	int32 Ypp;
};

struct to_float_strtuct_INT32
{
	float out;
};

struct to_fixed_strtuct_INT32
{
	int16 out;
};

void reciprocal_calc_INT32(struct reciprocal_struct_INT32 *reciprocal, int16 Num, int16 Den);
float to_float_calc_INT32(struct to_float_strtuct_INT32* to_float, int16 x);
int16 to_fixed_calc_INT32(struct to_fixed_strtuct_INT32* to_fixed, float x);

struct reciprocal_struct_INT32 reciprocal;
struct to_float_strtuct_INT32 to_float;
struct to_fixed_strtuct_INT32 to_fixed;

#endif /* Controllers_H_ */
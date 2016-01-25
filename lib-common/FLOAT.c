#include "FLOAT.h"

FLOAT F_mul_F(FLOAT a, FLOAT b) {
	long long c = (long long)a * (long long)b;
	return (FLOAT)(c >> 16);
}

FLOAT F_div_F(FLOAT a, FLOAT b) {
	int sign = 1;
	if (a < 0) 
	{
		sign = -sign;
		a = -a;
	}
	if (b < 0) 
	{
		sign = -sign;
		b = -b;
	}
	int res = a / b;
	a = a % b;
	int i;
	for (i = 0; i < 16; i++) 
	{
		a <<= 1;
		res <<= 1;
		if (a >= b) 
		{
			a -= b;
			res++;
		}
	}
	return res * sign;
}

FLOAT f2F(float a) {
	int b = *(int *)&a;
	int sign = b >> 31;
	int exp = (b >> 23) & 0xff;
	FLOAT k = b & 0x7fffff;
	if (exp != 0) k += 1 << 23;
	exp -= 150;
	if (exp < -16) k >>= -16 - exp;
	if (exp > -16) k <<= exp + 16;
	return sign == 0 ? k : -k;
}

FLOAT Fabs(FLOAT a) {
	FLOAT b;
	if (a < 0)
		b = - a;
	else
		b = a;
	return b;
}

FLOAT sqrt(FLOAT x) {
	FLOAT dt, t = int2F(2);
	do {
		dt = F_div_int((F_div_F(x, t) - t), 2);
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}

FLOAT pow(FLOAT x, FLOAT y) {
	/* we only compute x^0.333 */
	FLOAT t2, dt, t = int2F(2);

	do {
		t2 = F_mul_F(t, t);
		dt = (F_div_F(x, t2) - t) / 3;
		t += dt;
	} while(Fabs(dt) > f2F(1e-4));

	return t;
}


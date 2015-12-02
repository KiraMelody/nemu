#include "trap.h"
#include "FLOAT.h"

FLOAT f(FLOAT x) { 
	/* f(x) = 1/(1+25x^2) */
	return F_div_F(int2F(1), int2F(1) + F_mul_int(F_mul_F(x, x), 25));
}

FLOAT computeT(int n, FLOAT a, FLOAT b, FLOAT (*fun)(FLOAT)) {
	int k;
	FLOAT s,h;
	h = F_div_int((b - a), n);
	s = F_div_int(fun(a) + fun(b), 2 );
	for(k = 1; k < n; k ++) {
		s += fun(a + F_mul_int(h, k));
	}
	s = F_mul_F(s, h);
	return s;
}

int main() { 
	FLOAT a,b,c;
	float d=1.2;
	float ans = 1.44;
	a=f2F (d);
	b=int2F (1);
	c=int2F (-1);
	nemu_assert(Fabs (Fabs(c)-b)<f2F (1e-4));
	nemu_assert(F_mul_int(a,1) == a);
	nemu_assert(Fabs (F_mul_F(a,b) - a ) < Fabs (f2F (1e-4)));
	nemu_assert(Fabs (F_mul_F(a,a) - f2F (ans) ) < f2F (1e-4));
	HIT_GOOD_TRAP;


	//FLOAT a = computeT(10, f2F(-1.0), f2F(1.0), f);
	//FLOAT ans = f2F(0.551222);

	nemu_assert(Fabs(a - ans) < f2F(1e-4));
	HIT_GOOD_TRAP;
	return 0;
}

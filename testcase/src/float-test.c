#include "trap.h"
#include "FLOAT.h"


int main() { 
	FLOAT a,b,c;
	float d=1.2;
	float ans = 1.44;
	a=f2F (d);
	b=int2F (1);
	c=int2F (-1);
	nemu_assert(Fabs (Fabs(c) - b) < f2F (1e-4));
	//nemu_assert(F_mul_int(a,1) == a);
	nemu_assert(Fabs (F_mul_F(a,b) - a ) < Fabs (f2F (1e-4)));
	nemu_assert(Fabs (F_mul_F(a,a) - f2F (ans) ) < f2F (1e-4));
	HIT_GOOD_TRAP;
	return 0;
}

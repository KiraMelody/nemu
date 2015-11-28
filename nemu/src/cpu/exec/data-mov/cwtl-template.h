#include "cpu/exec/template-start.h"

#define instr cwtl

static void do_execute () {
	if ((REG(R_EAX)>>15) & 1)
	{
		REG (R_EAX) |= 0xffff0000;
	}
	else
	{
		REG (R_EAX) &= 0xffff;
	}
	print_asm("cwtl");
}
make_instr_helper(n)


#include "cpu/exec/template-end.h"

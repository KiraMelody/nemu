#include "cpu/exec/template-start.h"

#define instr cltd

static void do_execute () {
	uint64_t len = (DATA_BYTE << 3);
	DATA_TYPE result = (1 << len) - 1;
	printf ("0x%x",result);
	if (REG(R_EAX) < 0)
	{
		REG (R_EDX) = result;
	}
	else
	{
		REG (R_EDX) = 0;
	}
	print_asm("cltd");
}
make_instr_helper(n)


#include "cpu/exec/template-end.h"

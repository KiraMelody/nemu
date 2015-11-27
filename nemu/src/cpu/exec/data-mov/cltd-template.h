#include "cpu/exec/template-start.h"

#define instr cltd

static void do_execute () {
	int len = (DATA_BYTE << 3) - 1;
	uint32_t result = (1 << len) - 1;
	printf ("0x%x",result);
	if (REG(R_EAX) < 0)
	{
		MEM_W (REG (R_EDX) , result);
	}
	else
	{
		MEM_W (REG (R_EDX) , 0);
	}
	print_asm("cltd");
}
make_instr_helper(n)


#include "cpu/exec/template-end.h"

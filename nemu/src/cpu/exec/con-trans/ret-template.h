#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute () {
	cpu.eip = MEM_R (REG (R_ESP)) - 1;
	if (DATA_BYTE == 2)cpu.eip &= 0xffff;
	REG (R_ESP) += DATA_BYTE;
	print_asm("ret");
}
make_instr_helper(n)

make_helper(concat(ret_i_, SUFFIX))
{
	int val = instr_fetch(eip + 1, 2);
	int i;
	cpu.eip = MEM_R (REG (R_ESP));
	if (DATA_BYTE == 2)cpu.eip &= 0xffff;
	REG (R_ESP) += DATA_BYTE;
	for (i = 0;i < val; i+=DATA_BYTE)
	MEM_W (REG (R_ESP) + i,0);
	REG (R_ESP) += val;
	print_asm("ret $%d",val);
	return 1;
}

#include "cpu/exec/template-end.h"

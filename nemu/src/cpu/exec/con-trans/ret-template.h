#include "cpu/exec/template-start.h"

#define instr ret

make_helper(concat(ret_n_, SUFFIX))
{
	current_sreg = R_SS;
	cpu.eip = MEM_R (reg_l (R_ESP));
	//if (DATA_BYTE == 2)cpu.eip &= 0xffff;
	reg_l (R_ESP) += DATA_BYTE;
	print_asm("ret");
	return 1;
}

make_helper(concat(ret_i_, SUFFIX))
{
	int val = instr_fetch(eip + 1, 2);
	int i;
	current_sreg = R_SS;
	cpu.eip = MEM_R (REG (R_ESP));
	if (DATA_BYTE == 2)cpu.eip &= 0xffff;
	REG (R_ESP) += DATA_BYTE;
	for (i = 0;i < val; i+=DATA_BYTE)
	MEM_W (REG (R_ESP) + i,0);
	REG (R_ESP) += val;
	print_asm("ret $0x%x",val);
	return 1;
}

#include "cpu/exec/template-end.h"

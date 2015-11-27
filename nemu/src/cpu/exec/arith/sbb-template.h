#include "cpu/exec/template-start.h"

#define instr sbb

static void do_execute() {
	DATA_TYPE src = op_src->val;
	if (op_src->size == 1 && op_dest->size != 1)
	{
		op_src->val = (int8_t)op_src->val;
	}
	src += cpu.CF;
	DATA_TYPE result = op_dest->val - src;
	int len = (DATA_BYTE << 3) - 1;
	cpu.CF = op_dest->val < src;
	cpu.SF=result >> len;
    	int s1,s2;
	s1=op_dest->val>>len;
	s2=src>>len;
    	cpu.OF=(s1 != s2 && s2 == cpu.SF) ;
    	cpu.ZF=!result;
    	OPERAND_W(op_dest, result);
	result ^= result >>4;
	result ^= result >>2;
	result ^= result >>1;
	cpu.PF=!(result & 1);
	print_asm_no_template2();
}
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)


#include "cpu/exec/template-end.h"

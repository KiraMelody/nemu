#include "cpu/exec/template-start.h"

#define instr sub
/*
static void do_execute() {
	uint32_t result = op_dest->val - op_src->val;
	OPERAND_W(op_dest, result);
	int len = (DATA_BYTE << 3) - 1;
	cpu.CF = op_dest->val < op_src->val;
	int x = result >> len;
	cpu.SF=x;
    	x = x + (x & 1);
    	cpu.OF=!x;
	cpu.ZF=!result;
	result ^= result >>4;
	result ^= result >>2;
	result ^= result >>1;
	cpu.PF=!(result & 1);
	print_asm_template2();
}
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

make_instr_helper(i2a)
make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
*/

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr not

static void do_execute() {
	DATA_TYPE result = ~op_src->val;
	int len = (DATA_BYTE << 3) - 1;
	cpu.CF=0;
	cpu.OF=0;
	cpu.SF=result >> len;
    	cpu.ZF=!result;
    	OPERAND_W(op_src, result);
	result ^= result >>4;
	result ^= result >>2;
	result ^= result >>1;
	cpu.PF=!(result & 1);
	print_asm_template1();
}

make_instr_helper(rm)

#include "cpu/exec/template-end.h"

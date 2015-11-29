#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
	DATA_TYPE result = op_dest->val & op_src->val;
	int len = (DATA_BYTE << 3) - 1;
	cpu.CF=0;
	cpu.OF=0;
	cpu.SF=result >> len;
    	cpu.ZF=!result;
    	result ^= result >>4;
	result ^= result >>2;
	result ^= result >>1;
	cpu.PF=!(result & 1);
	print_asm_no_template2();
}
make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)


#include "cpu/exec/template-end.h"

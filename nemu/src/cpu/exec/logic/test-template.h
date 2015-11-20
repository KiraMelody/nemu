#include "cpu/exec/template-start.h"

#define instr test

static void do_execute() {
	uint32_t result = op_dest->val & op_src->val;
	cpu.CF=0;
	cpu.OF=0;
	cpu.ZF=!result;
	print_asm_no_template2();
}
make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)


#include "cpu/exec/template-end.h"

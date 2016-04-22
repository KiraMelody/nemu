#include "cpu/exec/template-start.h"

#define instr cmova

static void do_execute() {
	if (cpu.ZF == 0 || cpu.OF == 0)
	OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}

make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr setne

static void do_execute() {
	if (cpu.ZF == 0) OPERAND_W(op_src, 1);
	else OPERAND_W(op_src, 0);
	print_asm_no_template1();
}


make_instr_helper(rm)

#include "cpu/exec/template-end.h"

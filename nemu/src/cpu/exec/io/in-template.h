#include "cpu/exec/template-start.h"

#define instr in

static void do_execute() {
	OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}

make_instr_helper(i2a)
make_instr_helper(r2rm)



#include "cpu/exec/template-end.h"

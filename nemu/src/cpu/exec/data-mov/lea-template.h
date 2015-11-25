#include "cpu/exec/template-start.h"

#define instr lea

static void do_execute() {
	printf ("%d to %d \n",op_src->val,op_dest->val);
	OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}


make_instr_helper(r2rm)
make_instr_helper(rm2r)


#include "cpu/exec/template-end.h"

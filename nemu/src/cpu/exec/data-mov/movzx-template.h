#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute() {
	//printf ("%d : %d\n",op_src->val,op_dest->val);
	DATA_TYPE result = op_src->val;
	OPERAND_W(op_dest, result);
	//printf ("%d : %d\n",(int)op_src->size,(int)op_dest->size);
	print_asm_template2();
}


make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"

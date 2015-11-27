#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute() {
	DATA_TYPE_S result;
	printf ("%lu",sizeof (DATA_TYPE_S));
	printf ("src.size = %d,dest.size = %d\n",(int)op_src->size,(int)op_dest->size);
	if (op_dest->size == 1)result = (int32_t)(op_dest->val & 0xff);
	else if (op_dest->size == 2)result = (DATA_TYPE_S)(op_dest->val &0xffff);
	else result = (DATA_TYPE_S)op_dest->val;
	printf ("%d : %x -> %x\n",DATA_BYTE,op_dest->val,result);
	OPERAND_W(op_src, result);
	print_asm_template2();
}


make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"

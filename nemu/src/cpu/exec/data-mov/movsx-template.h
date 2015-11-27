#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute() {
	DATA_TYPE_S result;
	if (op_dest->size == 1)result = (int8_t)(op_dest->val & 0xff);
	else if (op_dest->size == 2)result = (int16_t)(op_dest->val &0xffff);
	else result = (int32_t)op_dest->val;
	OPERAND_W(op_src, result);
	print_asm_template2();
}


make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"

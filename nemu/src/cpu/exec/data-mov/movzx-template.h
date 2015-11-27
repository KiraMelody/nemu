#include "cpu/exec/template-start.h"

#define instr movzx

static void do_execute() {
	DATA_TYPE_S result;
	if (op_dest->size == 1)result = (uint8_t)(op_src->val & 0xff);
	else if (op_dest->size == 2)result = (uint16_t)(op_src->val &0xffff);
	else result = (uint32_t)op_src->val;
	OPERAND_W(op_dest, result);
	print_asm_template2();
}


make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"

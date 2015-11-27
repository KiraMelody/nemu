#include "cpu/exec/template-start.h"

#define instr movsx

static void do_execute() {
	DATA_TYPE_S result;
	printf ("size %d %d\n",(int)op_src->size,(int)op_src->size);
	if (ops_decoded.opcode == 0xbe)result = (int8_t)(op_src->val & 0xff);
	else result = (int16_t)(op_src->val &0xffff);
	OPERAND_W(op_dest, result);
	print_asm_template2();
}

make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"

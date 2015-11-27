#include "cpu/exec/template-start.h"

#define instr movsx

static void do_movsx_b() {
	DATA_TYPE_S result;
	result = (int8_t)(op_src->val & 0xff);
	OPERAND_W(op_dest, result);
	print_asm_template2();
}
static void do_movsx_w() {
	DATA_TYPE_S result;
	result = (int16_t)(op_src->val & 0xffff);
	OPERAND_W(op_dest, result);
	print_asm_template2();
}

make_helper(movsx_rm2r_b)
{
	return idex(eip,decode_rm2r_b, do_movsx_b);
}

make_helper(movsx_rm2r_w)
{
	return idex(eip,decode_rm2r_w, do_movsx_w);
}

#include "cpu/exec/template-end.h"

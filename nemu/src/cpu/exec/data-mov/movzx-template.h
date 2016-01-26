#include "cpu/exec/template-start.h"

#define instr movzx

static void do_movzx_b() {
	DATA_TYPE result;
	result = op_src->val & 0xff;
	if (op_dest->size == 1)result = (uint8_t)result;
	else if (op_dest->size == 2)result = (uint16_t)result;
	else result = (uint32_t)result;
	OPERAND_W(op_dest, result);
	print_asm_template2();
}
static void do_movzx_w() {
	DATA_TYPE result;
	result = op_src->val & 0xffff;
	if (op_dest->size == 1)result = (uint8_t)result;
	else if (op_dest->size == 2)result = (uint16_t)result;
	else result = (uint32_t)result;
	OPERAND_W(op_dest, result);
	print_asm_template2();
}

make_helper(movzx_rm2r_b)
{
	return idex(eip,decode_rm2r_b, do_movzx_b);
}

make_helper(movzx_rm2r_w)
{
	return idex(eip,decode_rm2r_w, do_movzx_w);
}

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute () {
	cpu.eip = MEM_R (REG (R_ESP));
	if (DATA_BYTE == 2)cpu.eip &= 0xffff;
	REG (R_ESP) += DATA_BYTE;
	if (op_src->type == OP_TYPE_IMM)
		REG (R_ESP) += op_src->val;
	print_asm("ret");
}
make_instr_helper(n)
make_instr_helper(i)

#include "cpu/exec/template-end.h"

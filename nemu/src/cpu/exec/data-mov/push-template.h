#include "cpu/exec/template-start.h"

#define instr push

static void do_execute () {
	//DATA_TYPE result = op_src->val + 1;
	//OPERAND_W(op_src, result);

	/* TODO: Update EFLAGS. */
	//panic("please implement me");

	print_asm_template1();
}

make_instr_helper(i)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
make_instr_helper(rm)
#endif

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr push

static void do_execute () {
	printf("push byte %d\n", DATA_BYTE);
	if (DATA_BYTE == 1)
	{
		REG (R_ESP) -= 4;
		MEM_W (reg_l (R_ESP) , op_src->val);
	}
	else
	{
		REG (R_ESP) -= DATA_BYTE;
		MEM_W (REG (R_ESP) , op_src->val);
	}
	print_asm_no_template1();
}

make_instr_helper(i)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
make_instr_helper(rm)
#endif

#include "cpu/exec/template-end.h"

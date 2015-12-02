#include "cpu/exec/template-start.h"

#define instr push

static void do_execute () {
	int32_t result = op_src->val;
	if (DATA_BYTE == 1)
	{
		reg_l (R_ESP) -= 4;
		swaddr_write (reg_l (R_ESP) , 4 ,result);
	}
	else
	{
		REG (R_ESP) -= DATA_BYTE;
		MEM_W (REG (R_ESP) , result);
	}
	print_asm_no_template1();
}

make_instr_helper(i)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
make_instr_helper(rm)
#endif

#include "cpu/exec/template-end.h"

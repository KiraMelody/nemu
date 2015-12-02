#include "cpu/exec/template-start.h"

#define instr push

static void do_execute () {
	int32_t result = op_src->val;
	printf ("0x%08x\n",result);
	reg_l (R_ESP) -= 4;
	swaddr_write (reg_l (R_ESP) , 4 ,result);
	print_asm_no_template1();
}

make_instr_helper(i)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
make_instr_helper(rm)
#endif

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr push

static void do_execute () {
	printf ("push %d\n",op_src->val);
	if (DATA_BYTE == 1)
	{
		printf ("0x%x ->",reg_l (R_ESP));
		reg_l (R_ESP) -= 4;
		printf ("0x%x\n",reg_l (R_ESP));
		swaddr_write (reg_l (R_ESP) , 4 ,op_src->val );
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

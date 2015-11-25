#include "cpu/exec/template-start.h"

#define instr push

static void do_execute () {
	printf ("push %d to %d(esp)\n",op_src->val,REG (4) );
	MEM_W (REG (4) , op_src->val);
	REG (4) -= DATA_BYTE;
	print_asm_no_template1();
}

make_instr_helper(i)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
make_instr_helper(rm)
#endif

#include "cpu/exec/template-end.h"

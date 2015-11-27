#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute () {
	cpu.eip = MEM_R (REG (R_ESP));
	printf ("EIP = %d\n",cpu.eip);
	if (DATA_BYTE == 2)cpu.eip &= 0xffff;
	REG (R_ESP) += DATA_BYTE;
	if (op_src->type == OP_TYPE_IMM)
	{
		swaddr_t i;
		printf ("%d\n",op_src->val);
		for (i = 0;i < op_src->val; i+=DATA_BYTE)
		MEM_W (REG (R_ESP) + i,0);
		REG (R_ESP) += op_src->val;
		print_asm_no_template1();
	}		
	else print_asm("ret");
}
make_instr_helper(n)
make_instr_helper(i)

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr movsw

static void do_execute() {
	cpu.CR0 = op_src->val;
	printf ("movsr %x\n",cpu.CR0);
	print_asm("mov %%CR0,%s",op_src->str);
}

make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"

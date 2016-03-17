#include "cpu/exec/template-start.h"

#define instr movsr

static void do_execute() {
	write_operand_l(op_src, cpu.CR0);
	printf ("movsr %x\n",cpu.CR0);
	print_asm("mov %%CR0,%s",op_src->str);
}

make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"

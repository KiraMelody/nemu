#include "cpu/exec/template-start.h"

#define instr ljmp


static void do_execute() {
	printf ("val = %x\n",op_src->imm);
	cpu.eip = concat (decode_i_,SUFFIX)(cpu.eip+1) - 1;
	printf ("eip = %d",cpu.eip);
	print_asm("ljmp");
}
make_instr_helper(i)
make_instr_helper(rm)

#include "cpu/exec/template-end.h"

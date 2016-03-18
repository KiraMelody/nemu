#include "cpu/exec/template-start.h"

#define instr ljmp


static void do_execute() {
	printf ("val = %x\n",op_src->imm);
	printf ("ppos = %x\n",cpu.eip+1+DATA_BYTE);
	int dis = concat (decode_i_,w)(cpu.eip+1+DATA_BYTE);
	printf ("dis = %x\n",dis);
	print_asm("ljmp");
}
make_instr_helper(i)
make_instr_helper(rm)

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr ljmp


static void do_execute() {
	printf ("val = %x\n",op_src->imm);
	int dis = concat (decode_i_,w)(cpu.eip+1+DATA_BYTE);
	printf ("dis = %d",dis);
	print_asm("ljmp");
}
make_instr_helper(i)
make_instr_helper(rm)

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr ljmp


static void do_execute() {
	int EIP = op_src->imm;
	concat (decode_i_,w)(cpu.eip+1+DATA_BYTE);
	cpu.cs = op_src->imm;
	cpu.eip = EIP - DATA_BYTE;
	print_asm("ljmp $%x,$%x",cpu.cs,EIP);
}
make_instr_helper(i)

#include "cpu/exec/template-end.h"

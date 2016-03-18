#include "cpu/exec/template-start.h"

#define instr ljmp


static void do_execute() {
	cpu.cs = op_src->imm;
	cpu.eip = op_dest->imm;
	print_asm_template2();
}
make_instr_helper(ii)

#include "cpu/exec/template-end.h"

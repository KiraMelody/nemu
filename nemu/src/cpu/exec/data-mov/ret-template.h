#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute () {
	cpu.eip = MEM_R (REG (R_EBP));
	REG (R_EBP) += DATA_BYTE;
	print_asm("ret");
}
make_instr_helper(n)
make_instr_helper(i)

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr stos

static void do_execute () {
	MEM_W (REG (R_EDI),REG (R_EAX));
	if (cpu.DF == 0)REG (R_EDI) += DATA_BYTE;
	else REG (R_EDI) -= DATA_BYTE;
	print_asm("stos");
}

make_instr_helper(n)


#include "cpu/exec/template-end.h"

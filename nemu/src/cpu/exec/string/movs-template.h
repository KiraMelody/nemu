#include "cpu/exec/template-start.h"

#define instr movs

static void do_execute () {
	MEM_W (REG (R_EDI),MEM_R (REG (R_ESI)));
	printf ("%x %x\n",REG (R_EDI),MEM_R (REG (R_ESI)));
	REG (R_EDI) += DATA_BYTE;
	REG (R_ESI) += DATA_BYTE;
	print_asm("movs");
}

make_instr_helper(n)


#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr ret

static void do_execute () {
	REG (R_ESP) += DATA_BYTE;
	cpu.eip = MEM_R (REG (R_ESP));
	printf ("%x : %x",REG (R_ESP),MEM_R (REG (R_ESP)));
	print_asm("ret");
}
make_instr_helper(n)
make_instr_helper(i)

#include "cpu/exec/template-end.h"

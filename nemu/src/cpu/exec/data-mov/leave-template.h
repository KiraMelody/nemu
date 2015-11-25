#include "cpu/exec/template-start.h"

#define instr leave

static void do_execute () {
	REG(R_ESP) = REG (R_EBP);
	REG(R_EBP) = MEM_R (REG (R_ESP));
	REG(R_ESP)+=DATA_BYTE;
	print_asm("leave");
}
make_instr_helper(n)


#include "cpu/exec/template-end.h"

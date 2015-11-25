#include "cpu/exec/template-start.h"

#define instr leave

static void do_execute () {
	printf ("leave %d to esp\n",REG (5) );
	REG(R_ESP) = REG (R_EBP);
	REG(R_EBP) = MEM_R (REG (R_ESP));
	printf ("now ebp = %d\n",REG(5));
	print_asm("leave");
}
make_instr_helper(n)


#include "cpu/exec/template-end.h"

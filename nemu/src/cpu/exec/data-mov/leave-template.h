#include "cpu/exec/template-start.h"

#define instr leave

static void do_execute () {
	MEM_W (REG (4) , MEM_R (REG (5) ));
	REG (5) += DATA_BYTE;
	print_asm("leave");
}
make_instr_helper(n)
/*
make_helper(concat(leave_n_, SUFFIX)) {
	return DATA_BYTE;
}*/

#include "cpu/exec/template-end.h"

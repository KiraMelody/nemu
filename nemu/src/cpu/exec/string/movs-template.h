#include "cpu/exec/template-start.h"

#define instr movs

static void do_execute () {
	if (ops_decoded.is_stack_size_16)
	{
		swaddr_write (reg_w(R_EDI),2,swaddr_read (reg_w(R_ESI),4));
		REG (R_EDI) += 2;
		REG (R_ESI) += 2;
	}
	else
	{
		swaddr_write (reg_l(R_EDI),4,swaddr_read (reg_l(R_ESI),4));
		REG (R_EDI) += 4;
		REG (R_ESI) += 4;
	}
	print_asm("movs");
}

make_instr_helper(n)


#include "cpu/exec/template-end.h"

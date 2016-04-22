#include "cpu/exec/template-start.h"

#define instr popa
#if DATA_BYTE == 2
static void pop(int x)
{
	current_sreg = R_SS;
	if (x != 4)reg_l (x) = swaddr_read(reg_l (R_ESP) , 4);
	swaddr_write (reg_l (R_ESP) , 4 , 0);
	reg_l (R_ESP) += 4;
}
#endif
static void do_execute () {
	current_sreg = R_SS;
	int i;
	for (i = 7;i >= 0;i --)
	{
		pop(i);
	}
	print_asm("popa");
}
make_instr_helper(n)

#include "cpu/exec/template-end.h"

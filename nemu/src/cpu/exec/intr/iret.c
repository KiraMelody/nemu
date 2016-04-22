#include "cpu/exec/helper.h"
#include <nemu.h>

/* for instruction encoding overloading */
int pop ()
{
	uint32_t tmp = swaddr_read (reg_l(R_ESP) , 4);
	swaddr_write (reg_l(R_ESP) , 4 , 0);
	reg_l (R_ESP) += 4;
	return tmp;
}
make_helper(iret)
{
	if (cpu.cr0.protect_enable == 0)
	{
		cpu.eip = pop();
		cpu.cs.selector = pop ();
		cpu.eflags = pop ();
	}
	else
	{
		current_sreg = R_SS;
		cpu.eip = pop();
		cpu.cs.selector = pop ();
		cpu.eflags = pop();
		current_sreg = R_CS;
		sreg_load ();
	}
	print_asm("iret");
	return 0;
}

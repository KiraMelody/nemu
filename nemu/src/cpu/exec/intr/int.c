#include "cpu/exec/helper.h"
#include <nemu.h>
void raise_intr(uint8_t);
make_helper(intr) {
	int NO = instr_fetch(eip + 1, 1);
	if (cpu.cr0.protect_enable == 0)
	{
		cpu.IF = 0;
		cpu.TF = 0;
		reg_l (R_ESP) -= 4;
		swaddr_write (reg_l (R_ESP) , 4 , cpu.cs.selector);
		reg_l (R_ESP) -= 4;
		swaddr_write (reg_l (R_ESP) , 4 , cpu.eip + 2);
		raise_intr (NO);
	}
	else
	{
		//if (idt_des->privilege_level <=3)printf ("dpl = %d\n",idt_des->privilege_level);
	}
	print_asm("int %x",NO);
	return 2;
}

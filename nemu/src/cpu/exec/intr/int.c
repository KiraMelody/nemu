#include "cpu/exec/helper.h"
#include <nemu.h>
void raise_intr(uint8_t);
make_helper(intr) {
	int NO = instr_fetch(eip + 1, 1);
	printf ("no = %d\n",NO);
	printf ("fuck1!\n");
	if (cpu.cr0.protect_enable == 0)
	{
		printf ("fuck2!\n");
		reg_l (R_ESP) -= 4;
		swaddr_write (reg_l (R_ESP) , 4 , cpu.eflags);
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
		printf ("fuck3!\n");
		if (idt_des->privilege_level <=3)printf ("dpl = %d\n",idt_des->privilege_level);
	}
	printf ("fuck!\n");
	print_asm("int %x",NO);
	return 2;
}

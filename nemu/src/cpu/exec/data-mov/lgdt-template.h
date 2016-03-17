#include "cpu/exec/template-start.h"

#define instr lgdt

static void do_execute () {
	printf ("val = %x\n",op_src->val);
	if (op_src->size == 2)
	{
		cpu.GDTR.gdl = swaddr_read (op_src->val,2);
		cpu.GDTR.gda = swaddr_read (op_src->val + 16,3);
	}
	else if (op_src->size == 4)
	{
		cpu.GDTR.gdl = swaddr_read (op_src->val,2);
		cpu.GDTR.gda = swaddr_read (op_src->val + 16,4);
	}
	printf ("gdl = 0x%x gda = 0x%x\n",cpu.GDTR.gdl,cpu.GDTR.gda);
	print_asm("lgdt\n");
}
make_instr_helper(rm)


#include "cpu/exec/template-end.h"

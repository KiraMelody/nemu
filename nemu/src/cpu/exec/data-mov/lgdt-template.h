#include "cpu/exec/template-start.h"

#define instr lgdt

static void do_execute () {
	if (op_src->size == 2)
	{
		cpu.gdtr.seg_limit = swaddr_read (op_src->addr , 2);
		cpu.gdtr.base_addr = swaddr_read (op_src->addr + 2,3);
	}
	else if (op_src->size == 4)
	{
		cpu.gdtr.seg_limit = swaddr_read (op_src->addr , 2);
		cpu.gdtr.base_addr = swaddr_read (op_src->addr + 2,4);
	}
	//printf ("limit = 0x%x base = 0x%x\n",cpu.gdtr.seg_limit,cpu.gdtr.base_addr);
	print_asm_template1();
}
make_instr_helper(rm)


#include "cpu/exec/template-end.h"

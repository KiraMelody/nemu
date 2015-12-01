#include "cpu/exec/template-start.h"

#define instr call


static void do_execute() {
	REG (R_ESP) -= DATA_BYTE;
	MEM_W (REG (R_ESP) , cpu.eip + DATA_BYTE);
	printf ("call push %d\n",cpu.eip + DATA_BYTE);
	DATA_TYPE_S displacement = op_src->val;
	if (op_src->type == OP_TYPE_IMM)
	{
		print_asm("call %x",cpu.eip + 1 + DATA_BYTE + displacement);
		cpu.eip +=displacement;
	}
	else
	{
		print_asm("call %x",displacement);
		cpu.eip =displacement - 2;
		printf ("%x\n",cpu.eip);
	}
}
make_instr_helper(i)
make_instr_helper(rm)


#include "cpu/exec/template-end.h"

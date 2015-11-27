#include "cpu/exec/template-start.h"

#define instr jg


static void do_execute() {
	DATA_TYPE_S displacement = op_src->val;
	print_asm("jg %x",cpu.eip + 1 + DATA_BYTE + displacement);
	if (cpu.ZF == 0 && cpu.SF == cpu.OF)cpu.eip +=displacement;
}
make_instr_helper(i)


#include "cpu/exec/template-end.h"

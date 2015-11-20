#include "cpu/exec/template-start.h"

#define instr call

make_helper(exec);
/*THIS IS WRONG*/
static void do_execute() {
	uint32_t displacement = instr_fetch(cpu.eip + 1, DATA_BYTE);
	printf ("0x%x + 0x%x\n",cpu.eip,displacement);
	print_asm("call %x\n",cpu.eip + DATA_BYTE + displacement);
	//print_asm(" %s", cpu.eip + op_src->str);
	//cpu.eip = cpu.eip + 1 + displacement;
	//exec (cpu.eip);
}
make_instr_helper(i)


#include "cpu/exec/template-end.h"

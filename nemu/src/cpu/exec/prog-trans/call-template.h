#include "cpu/exec/template-start.h"

#define instr call


static void do_execute() {
	REG (4) -= DATA_BYTE;
	MEM_W (REG (4) , cpu.eip + 1 + DATA_BYTE);
	int32_t displacement = instr_fetch(cpu.eip + 1, DATA_BYTE);
	print_asm("call %x",cpu.eip + 1 + DATA_BYTE + displacement);
	cpu.eip +=displacement;
}
make_instr_helper(i)


#include "cpu/exec/template-end.h"

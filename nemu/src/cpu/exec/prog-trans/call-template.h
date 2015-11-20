#include "cpu/exec/template-start.h"

#define instr call


static void do_execute() {
	uint32_t displacement = instr_fetch(cpu.eip + 1, DATA_BYTE);
	print_asm("call %x",cpu.eip + 1 + DATA_BYTE + displacement);
	cpu.eip +=displacement;
}
make_instr_helper(i)


#include "cpu/exec/template-end.h"

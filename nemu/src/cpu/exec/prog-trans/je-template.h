#include "cpu/exec/template-start.h"

#define instr je


static void do_execute() {
	int32_t displacement = instr_fetch(cpu.eip + 1, DATA_BYTE);
	print_asm("je %x",cpu.eip + 1 + DATA_BYTE + displacement);
	if (cpu.ZF == 1)cpu.eip +=displacement;
}
make_instr_helper(i)


#include "cpu/exec/template-end.h"

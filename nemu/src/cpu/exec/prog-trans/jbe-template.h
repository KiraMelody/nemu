#include "cpu/exec/template-start.h"

#define instr jbe


static void do_execute() {
	int32_t displacement = instr_fetch(cpu.eip + 1, DATA_BYTE);
	displacement &= 0xff;
	print_asm("jbe %x",cpu.eip + 1 + DATA_BYTE + displacement);
	if (cpu.CF == 1 || cpu.ZF == 1)cpu.eip +=displacement;
}
make_instr_helper(i)


#include "cpu/exec/template-end.h"

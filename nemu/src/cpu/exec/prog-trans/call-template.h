#include "cpu/exec/template-start.h"

#define instr call

make_helper(exec);

static void do_execute() {
	uint32_t displacement = instr_fetch(cpu.eip, DATA_BYTE);
	printf ("0x%x",cpu.eip);
	exec(cpu.eip + displacement);
	print_asm_template1();
}
make_instr_helper(i)


#include "cpu/exec/template-end.h"

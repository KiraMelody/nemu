#include "cpu/exec/template-start.h"

#define instr out
uint32_t pio_write(ioaddr_t, size_t,  uint32_t);

static void do_execute() {
	pio_write(op_dest -> addr, DATA_BYTE, op_src -> val);
	print_asm("out");
}

make_instr_helper(i2a)
make_instr_helper(r2rm)



#include "cpu/exec/template-end.h"

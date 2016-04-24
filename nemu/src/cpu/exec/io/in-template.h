#include "cpu/exec/template-start.h"

#define instr in
uint32_t pio_read(ioaddr_t, size_t);

static void do_execute() {
	OPERAND_W(op_dest, pio_read (op_src->addr , DATA_BYTE));
	print_asm("in");
}

make_instr_helper(i2a)
make_instr_helper(r2rm)



#include "cpu/exec/template-end.h"

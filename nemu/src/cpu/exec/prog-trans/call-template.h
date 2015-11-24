#include "cpu/exec/template-start.h"

#define instr call


static void do_execute() {
	REG (4) -= DATA_BYTE;
	MEM_W (REG (4) , cpu.eip + 1 + DATA_BYTE);
	DATA_TYPE_S displacement = op_src->val;
	print_asm("call %x",cpu.eip + 1 + DATA_BYTE + displacement);
	cpu.eip +=displacement;
}
make_instr_helper(i)


#include "cpu/exec/template-end.h"

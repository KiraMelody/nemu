#include "cpu/exec/template-start.h"

#define instr leave

static void do_execute () {
	//REG (4) -= DATA_BYTE;
	//MEM_W (REG (4) , op_src->val);
	print_asm_no_template1();
}

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr inc

static void do_execute () {
	DATA_TYPE result = op_src->val + 1;
	int len = (DATA_BYTE << 3) - 1;
	cpu.OF=(result < op_dest->val);
	cpu.SF=result >> len;
	cpu.ZF=!result;
	OPERAND_W(op_src, result);
	result ^= result >>4;
	result ^= result >>2;
	result ^= result >>1;
	cpu.PF=!(result & 1);
	/* TODO: Update EFLAGS. */
	//panic("please implement me");
	print_asm_template1();
}

make_instr_helper(rm)
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(r)
#endif

#include "cpu/exec/template-end.h"

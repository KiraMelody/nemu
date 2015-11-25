#include "cpu/exec/template-start.h"

#define instr add

static void do_execute() {
	int32_t result = op_dest->val + op_src->val;
	int len = (DATA_BYTE << 3) - 1;
	int s1,s2;
	s1=op_dest->val;
	s2=op_src->val;
	int i,c = 0;
	for (i=0;i<len;i++)
	{
		c = ((s1&1)+(s2&1)+c)&2;
		s1>>=1;s2>>=1;
	}
	cpu.CF=c;
	cpu.SF=result >> len;
	s1=op_dest->val>>len;
	s2=op_src->val>>len;
    	cpu.OF=(s1 == s2 && s1 != cpu.SF) ;
	cpu.ZF=!result;
	OPERAND_W(op_dest, result);
	result ^= result >>4;
	result ^= result >>2;
	result ^= result >>1;
	cpu.PF=!(result & 1);
	print_asm_no_template2();
}
#if DATA_BYTE == 2 || DATA_BYTE == 4
make_instr_helper(si2rm)
#endif

make_instr_helper(i2a)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

#include "cpu/exec/template-end.h"

#include "cpu/exec/template-start.h"

#define instr cmps

static void do_execute () {
	DATA_TYPE src = MEM_R (REG (R_ESI));
	DATA_TYPE dest = MEM_R (REG (R_EDI));
	DATA_TYPE result = dest - src;
	int len = (DATA_BYTE << 3) - 1;
	cpu.CF = dest < src;
	cpu.SF=result >> len;
    	int s1,s2;
	s1=dest>>len;
	s2=src>>len;
    	cpu.OF=(s1 != s2 && s2 == cpu.SF) ;
    	cpu.ZF=!result;
	result ^= result >>4;
	result ^= result >>2;
	result ^= result >>1;
	cpu.PF=!(result & 1);
	if (cpu.DF == 0)REG (R_EDI) += DATA_BYTE,REG (R_ESI) += DATA_BYTE;
	else REG (R_EDI) -= DATA_BYTE,REG (R_ESI) -= DATA_BYTE;
	print_asm("cmps");
}

make_instr_helper(n)


#include "cpu/exec/template-end.h"

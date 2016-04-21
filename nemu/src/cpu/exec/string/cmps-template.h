#include "cpu/exec/template-start.h"

#define instr cmps

static void do_execute () {
	DATA_TYPE src,dest;
	if (ops_decoded.is_stack_size_16)
	{
		current_sreg = R_DS;
		src = swaddr_read (reg_w (R_SI),DATA_BYTE);
		current_sreg = R_ES;
		dest = swaddr_read (reg_w (R_DI),DATA_BYTE);
	}
	else
	{
		current_sreg = R_DS;
		src = swaddr_read (reg_l (R_ESI),DATA_BYTE);
		current_sreg = R_ES;
		dest = swaddr_read (reg_l (R_EDI),DATA_BYTE);
	}
	DATA_TYPE result = dest - src;
	int len = (DATA_BYTE << 3) - 1;
	cpu.CF = dest < src;
	cpu.SF= result >> len;
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

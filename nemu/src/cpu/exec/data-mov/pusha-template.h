#include "cpu/exec/template-start.h"

#define instr pusha

#if DATA_BYTE == 2
static void push2(int x)
{
	reg_w (R_SP) -= 2;
	swaddr_write (reg_w (R_SP) , 2 , x);
}
static void push4(int x)
{
	reg_l (R_ESP) -= 4;
	swaddr_write (reg_l (R_ESP) , 4 , x);
}
#endif
static void do_execute () {
	current_sreg = R_SS;
	if (DATA_BYTE == 2)
	{
		DATA_TYPE temp = reg_w (R_SP);
		push2 (reg_w(R_AX));
		push2 (reg_w(R_CX));
		push2 (reg_w(R_DX));
		push2 (reg_w(R_BX));
		push2 (temp);
		push2 (reg_w(R_BP));
		push2 (reg_w(R_SI));
		push2 (reg_w(R_DI));
	}
	else
	{
		DATA_TYPE temp = reg_l (R_ESP);
		push4 (reg_l(R_EAX));
		push4 (reg_l(R_ECX));
		push4 (reg_l(R_EDX));
		push4 (reg_l(R_EBX));
		push4 (temp);
		push4 (reg_l(R_EBP));
		push4 (reg_l(R_ESI));
		push4 (reg_l(R_EDI));
	}
	print_asm_no_template1();
}

make_instr_helper(n)


#include "cpu/exec/template-end.h"

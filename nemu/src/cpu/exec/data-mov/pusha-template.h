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
	//printf ("push %s at %x\n",REG_NAME(x),reg_l (R_ESP));
	reg_l (R_ESP) -= 4;
	swaddr_write (reg_l (R_ESP) , 4 , x);
}
#endif
static void do_execute () {
	current_sreg = R_SS;
	if (DATA_BYTE == 2)
	{
		DATA_TYPE temp = reg_w (R_SP);
		push2 (R_AX);
		push2 (R_CX);
		push2 (R_DX);
		push2 (R_BX);
		push2 (temp);
		push2 (R_BP);
		push2 (R_SI);
		push2 (R_DI);
	}
	else
	{
		DATA_TYPE temp = reg_l (R_ESP);
		push4 (R_EAX);
		push4 (R_ECX);
		push4 (R_EDX);
		push4 (R_EBX);
		push4 (temp);
		push4 (R_EBP);
		push4 (R_ESI);
		push4 (R_EDI);
	}
	print_asm_no_template1();
}

make_instr_helper(n)


#include "cpu/exec/template-end.h"

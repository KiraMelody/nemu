#include "cpu/exec/template-start.h"

#define instr popa
#if DATA_BYTE == 2
static void pop(int x)
{
	Log ("pop %s as %x",regsl[x],reg_l (R_ESP));
	current_sreg = R_SS;
	reg_l (x) = swaddr_read(reg_l (R_ESP) , 4);
	swaddr_write (reg_l (R_ESP) , 4 , 0);
	reg_l (R_ESP) += 4;
}
#endif
static void do_execute () {
	current_sreg = R_SS;
	int i;
	for (i = 7;i >= 0;i --)
	{
		if (i == 4)continue;
		pop(i);
	}
	print_asm_no_template1();
}
make_instr_helper(n)

#include "cpu/exec/template-end.h"

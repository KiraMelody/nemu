#include "cpu/exec/template-start.h"

#define instr popa
#if DATA_BYTE == 2
static void pop(int x)
{
	printf ("pop %s\n",REG_NAME(x));
	REG (x) = MEM_R(REG (R_ESP));
	MEM_W(REG (R_ESP) , 0);
	REG (R_ESP) += DATA_BYTE;
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

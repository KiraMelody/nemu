#include "cpu/exec/helper.h"
#include "cpu/decode/modrm.h"


make_helper(movsr) {
	write_operand_l(op_src, cpu.CR0);
	printf ("movsr %x\n",cpu.CR0);
	print_asm("mov CR0,%s",op_src->str);
	return 5;
}

make_helper(movsw) {
	cpu.CR0 = op_src->val;
	printf ("movsw %x\n",cpu.CR0);
	if (cpu.PE == 1){

	}
	print_asm("mov %s,CR0",op_src->str);
	return 5;
}

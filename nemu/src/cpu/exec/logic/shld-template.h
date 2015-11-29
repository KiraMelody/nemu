#include "cpu/exec/template-start.h"

#define instr shld

#if DATA_BYTE == 2 
static DATA_TYPE shld_do_loop_w (DATA_TYPE in,DATA_TYPE out,uint8_t count)
{
	count &= 0x1f;
	int tmp;
	int len = (DATA_BYTE << 3) - 1;
	while(count != 0) {
		tmp = in >> len;
		in<<=1;
		in |= out & (1 << len);
		out <<=1;
		out |= tmp;
		count --;
	}
	cpu.CF=0;
	cpu.OF=0;
	cpu.SF=out >> len;
    	cpu.ZF=!out;
    	return out;
}
static void do_execute_w () {
	DATA_TYPE in = op_dest->val;
	DATA_TYPE out = op_src2->val;
	uint8_t count = op_src->val;
	out = shld_do_loop_w (in,out,count);
	OPERAND_W(op_src2, out);
	out ^= out >>4;
	out ^= out >>2;
	out ^= out >>1;
	cpu.PF=!(out & 1);
	print_asm("shld" str(SUFFIX) " %s,%s,%s", op_src->str, op_dest->str, op_src2->str);
}

make_helper(concat(shld_i_, SUFFIX)) {
	int len = concat(decode_si_rm2r_, SUFFIX) (eip + 1);  /* use decode_si_rm2r to read 1 byte immediate */
	op_dest->val = REG(op_dest->reg);
	do_execute_w();
	return len + 1;
}

static void do_execute_cl_w () {
	DATA_TYPE in = op_dest->val;
	DATA_TYPE out = op_src->val;
	uint8_t count = reg_b (R_CL);
	out = shld_do_loop_w (in,out,count);
	OPERAND_W(op_src, out);
	out ^= out >>4;
	out ^= out >>2;
	out ^= out >>1;
	cpu.PF=!(out & 1);
	print_asm("shld" str(SUFFIX) " $cl,%s,%s", op_dest->str, op_src->str);
}
make_helper(concat(shld_cl_, SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX) (eip + 1);
	do_execute_cl_w();
	return len + 1;
}
#endif

#if DATA_BYTE == 4
static DATA_TYPE shld_do_loop_l (DATA_TYPE in,DATA_TYPE out,uint8_t count)
{
	count &= 0x1f;
	int tmp;
	int len = (DATA_BYTE << 3) - 1;
	while(count != 0) {
		tmp = in >> len;
		in<<=1;
		in |= out & (1 << len);
		out <<=1;
		out |= tmp;
		count --;
	}
	cpu.CF=0;
	cpu.OF=0;
	cpu.SF=out >> len;
    	cpu.ZF=!out;
    	return out;
}
static void do_execute_l () {
	DATA_TYPE in = op_dest->val;
	DATA_TYPE out = op_src2->val;
	uint8_t count = op_src->val;
	out = shld_do_loop_l (in,out,count);
	OPERAND_W(op_src2, out);
	out ^= out >>4;
	out ^= out >>2;
	out ^= out >>1;
	cpu.PF=!(out & 1);
	print_asm("shld" str(SUFFIX) " %s,%s,%s", op_src->str, op_dest->str, op_src2->str);
}

make_helper(concat(shld_i_, SUFFIX)) {
	int len = concat(decode_si_rm2r_, SUFFIX) (eip + 1);  /* use decode_si_rm2r to read 1 byte immediate */
	op_dest->val = REG(op_dest->reg);
	do_execute_l();
	return len + 1;
}

static void do_execute_cl_l () {
	DATA_TYPE in = op_dest->val;
	DATA_TYPE out = op_src->val;
	uint8_t count = reg_b (R_CL);
	out = shld_do_loop_l (in,out,count);
	OPERAND_W(op_src, out);
	out ^= out >>4;
	out ^= out >>2;
	out ^= out >>1;
	cpu.PF=!(out & 1);
	print_asm("shld" str(SUFFIX) " $cl,%s,%s", op_dest->str, op_src->str);
}
make_helper(concat(shld_cl_, SUFFIX)) {
	int len = concat(decode_rm2r_, SUFFIX) (eip + 1);
	do_execute_cl_l();
	return len + 1;
}
#endif

#include "cpu/exec/template-end.h"

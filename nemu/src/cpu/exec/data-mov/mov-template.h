#include "cpu/exec/template-start.h"
#if DATA_BYTE == 1
#define TLB_SIZE 64
extern struct Tlb
{
	bool valid;
	int tag;
	int page_number;
}tlb[TLB_SIZE];
#endif

#define instr mov

static void do_execute() {
	OPERAND_W(op_dest, op_src->val);
	print_asm_template2();
}

make_instr_helper(i2r)
make_instr_helper(i2rm)
make_instr_helper(r2rm)
make_instr_helper(rm2r)

make_helper(concat(mov_a2moffs_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	current_sreg = R_DS;
	MEM_W(addr, REG(R_EAX));
	print_asm("mov" str(SUFFIX) " %%%s,0x%x", REG_NAME(R_EAX), addr);
	return 5;
}

make_helper(concat(mov_moffs2a_, SUFFIX)) {
	swaddr_t addr = instr_fetch(eip + 1, 4);
	current_sreg = R_DS;
	REG(R_EAX) = MEM_R(addr);
	print_asm("mov" str(SUFFIX) " 0x%x,%%%s", addr, REG_NAME(R_EAX));
	return 5;
}

#if DATA_BYTE == 4
make_helper(mov_cr2r) {
	uint8_t opcode = instr_fetch(eip + 1, 1);
	switch (opcode) {
		case 0xc0:
		cpu.eax = cpu.cr0.val;
		print_asm("mov %%cr0,%%%s", REG_NAME(R_EAX));
		break;
		case 0xd8:
		cpu.eax = cpu.cr3.val;
		int i;
		for (i = 0;i < TLB_SIZE;i ++) 
		{
		 	tlb[i].valid = false;
		}
		print_asm("mov %%cr3,%%%s", REG_NAME(R_EAX));
		break;
		default:
		cpu.eax = cpu.cr0.val;
		print_asm("mov %%cr0,%%%s", REG_NAME(R_EAX));
		break;
	}
	return 2;
}
make_helper(mov_r2cr) {
	uint8_t opcode = instr_fetch(eip + 1, 1);
	switch (opcode) {
		case 0xc0:
		cpu.cr0.val = cpu.eax;
		print_asm("mov %%%s,%%cr0", REG_NAME(R_EAX));
		break;
		case 0xd8:
		cpu.cr3.val = cpu.eax;
		print_asm("mov %%%s,%%cr3", REG_NAME(R_EAX));
		break;
		default:
		cpu.cr0.val = cpu.eax;
		print_asm("mov %%%s,%%cr0", REG_NAME(R_EAX));
		break;
	}
	return 2;
}
#endif

#if DATA_BYTE == 2
make_helper(mov_seg) {
	uint8_t opcode = instr_fetch(eip + 1, 1);
	switch(opcode) {
		case 0xd8:
			cpu.ds.selector = reg_w(R_EAX);
			current_sreg = R_DS;
			sreg_load();
			print_asm("mov %%%s, ds", REG_NAME(R_EAX));
			break;
		case 0xc0:
			cpu.es.selector = reg_w(R_EAX);
			current_sreg = R_ES;
			sreg_load();
			print_asm("mov %%%s, es", REG_NAME(R_EAX));
			break;
		break;
		case 0xd0:
			cpu.ss.selector = reg_w(R_EAX);
			current_sreg = R_SS;
			sreg_load();
			print_asm("mov %%%s, ss", REG_NAME(R_EAX));
			break;
		break;
		default:
		break;
	}
	return 2;
}
#endif 

#include "cpu/exec/template-end.h"

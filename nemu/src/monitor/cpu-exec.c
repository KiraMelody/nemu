#include "monitor/monitor.h"
#include "cpu/helper.h"
#include <setjmp.h>
#include "monitor/watchpoint.h"
#include "cpu/reg.h"
/* The assembly code of instructions executed is only output to the screen
 * when the number of instructions executed is less than this value.
 * This is useful when you use the ``si'' command.
 * You can modify this value as you want.
 */
#define MAX_INSTR_TO_PRINT 101

int nemu_state = STOP;

int exec(swaddr_t);
void raise_intr(uint8_t);
char assembly[80];
char asm_buf[128];

/* Used with exception handling. */
jmp_buf jbuf;
static inline void push (int val)
{
	current_sreg = R_SS;
	reg_l (R_ESP) -= 4;
	swaddr_write (reg_l (R_ESP) , 4 , val);
}
void raise_intr(uint8_t NO) {
	/* TODO: Trigger an interrupt/exception with ``NO''.
	 * That is, use ``NO'' to index the IDT.
	 */
    	Assert(NO * 8 <= cpu.idtr.seg_limit, "Interrupt number exceeded");
    	GATE_descriptor gate;
	idt_des = &gate;
   	lnaddr_t pidt = cpu.idtr.base_addr + NO * 8;
   	idt_des->first_part = lnaddr_read(pidt + 4, 4);
	idt_des->second_part = lnaddr_read(pidt, 4);
	Log ("%x %x\n",idt_des->first_part ,idt_des->second_part);

	uint64_t idt_des2 = ((uint64_t) lnaddr_read(pidt + 4, 4) << 32) | lnaddr_read(pidt, 4); 
	Log ("%lx\n",idt_des2);
	Log ("%x %lx\n",idt_des -> segment,((uint64_t)idt_des2 >> 16) & 0xFFFF);
    	//uint64_t idt_des = ((uint64_t) lnaddr_read(pidt + 4, 4) << 32) | lnaddr_read(pidt, 4); 
    	//Assert((idt_des >> 47) & 1, "IDT descripter does not present, Interrupt # = %#x", NO);
    	//uint8_t gate_type = (idt_des >> 40) & 0x7;
	push (cpu.eflags);
	push (cpu.cs.selector);
	push (cpu.eip); 
    // long jump
    	cpu.cs.selector = idt_des -> segment;
    	Log ("%ld %ld\n",((uint64_t)idt_des2 >> 16) & 0xFFFF,(uint64_t)cpu.cs.selector);
    	current_sreg = R_CS;
    	sreg_load();
    	//cpu.eip = cpu.cs.seg_base + idt_des -> offset_15_0 + (idt_des -> offset_31_16 << 16);
    	cpu.eip = ((uint64_t)idt_des2 & 0xFFFF) | (((uint64_t)idt_des2 >> 32LL) & 0xFFFF0000);
    /* Jump back to cpu_exec() */
    	longjmp(jbuf, 1);
}
/*
void raise_intr(uint8_t NO) {
	
	push (cpu.eflags);
	push (cpu.cs.selector);
	push (cpu.eip); 
	Log ("eip = %x\n",cpu.eip);
	GATE_descriptor gate;
	idt_des = &gate;
	idt_des->first_part = lnaddr_read((cpu.idtr.base_addr) + (NO << 3), 4);
	idt_des->second_part = lnaddr_read((cpu.idtr.base_addr) + (NO << 3) + 4, 4);
	Assert ((NO << 3) <= cpu.idtr.seg_limit,"idt out limit %hd, %d", (NO<<3), cpu.idtr.seg_limit);
	Log ("selector = %x dpl = %d type = %x\n",idt_des -> segment,idt_des->privilege_level,idt_des->type);
	Log ("cs.selector = %x\n",cpu.cs.selector);
	Log ("idtr.base = %x\n",cpu.idtr.base_addr);
	cpu.cs.selector = idt_des -> segment;
	//Assert(((cpu.cs.selector>>3)<<3) <= cpu.gdtr.seg_limit, "segment out limit %d, %d", ((cpu.cs.selector>>3)<<3), cpu.gdtr.seg_limit);
	seg_des->first_part = instr_fetch(cpu.gdtr.base_addr + ((cpu.cs.selector>>3)<<3), 4);
	seg_des->second_part = instr_fetch(cpu.gdtr.base_addr + ((cpu.cs.selector>>3)<<3)+4, 4);
	Assert(seg_des->p == 1, "segment error");
	cpu.cs.seg_base1 = seg_des->seg_base1;
	cpu.cs.seg_base2 = seg_des->seg_base2;
	cpu.cs.seg_base3 = seg_des->seg_base3;
	cpu.cs.seg_limit1 = seg_des->seg_limit1;
	cpu.cs.seg_limit2 = seg_des->seg_limit2;
	cpu.cs.seg_limit3 = 0xfff;
	Log("base = %x offset = %x\n",cpu.cs.seg_base , idt_des -> offset_15_0 + (idt_des -> offset_31_16 << 16));
	cpu.eip = cpu.cs.seg_base + idt_des -> offset_15_0 + (idt_des -> offset_31_16 << 16);
	Assert (0,"eip = %x\n",cpu.eip);
	longjmp(jbuf, 1);
}*/
void print_bin_instr(swaddr_t eip, int len) {
	int i;
	int l = sprintf(asm_buf, "%8x:   ", eip);
	for(i = 0; i < len; i ++) {
		l += sprintf(asm_buf + l, "%02x ", instr_fetch(eip + i, 1));
	}
	sprintf(asm_buf + l, "%*.s", 50 - (12 + 3 * len), "");
}

/* This function will be called when an `int3' instruction is being executed. */
void do_int3() {
	printf("\nHit breakpoint at eip = 0x%08x\n", cpu.eip);
	nemu_state = STOP;
}

/* Simulate how the CPU works. */
void cpu_exec(volatile uint32_t n) {
	if(nemu_state == END) {
		printf("Program execution has ended. To restart the program, exit NEMU and run again.\n");
		return;
	}
	nemu_state = RUNNING;

#ifdef DEBUG
	volatile uint32_t n_temp = n;
#endif

	setjmp(jbuf);

	for(; n > 0; n --) {
#ifdef DEBUG
		swaddr_t eip_temp = cpu.eip;
		if((n & 0xffff) == 0) {
			/* Output some dots while executing the program. */
			fputc('.', stderr);
		}
#endif

		/* Execute one instruction, including instruction fetch,
		 * instruction decode, and the actual execution. */
		int instr_len = exec(cpu.eip);

		cpu.eip += instr_len;
#ifdef DEBUG
		print_bin_instr(eip_temp, instr_len);
		strcat(asm_buf, assembly);
		Log_write("%s\n", asm_buf);
		if(n_temp < MAX_INSTR_TO_PRINT) {
			printf("%s\n", asm_buf);
		}
#endif
		/* TODO: check watchpoints here. */
		if (!check_wp())nemu_state = STOP;
		if(nemu_state != RUNNING) { return; }
	}

	if(nemu_state == RUNNING) { nemu_state = STOP; }
}

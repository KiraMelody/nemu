#include "irq.h"

#include <sys/syscall.h>

void add_irq_handle(int, void (*)(void));
void mm_brk(uint32_t);
void serial_printc(char);
static void sys_brk(TrapFrame *tf) {
#ifdef IA32_PAGE
	mm_brk(tf->ebx);
#endif
	tf->eax = 0;
}

static void sys_write(TrapFrame *tf)
{
	uint32_t fd = tf->ebx;
    	char *buf = (char *)tf->ecx;
 	uint32_t len = tf->edx;
 	uint32_t result = 0;
 	if (fd == 1 || fd == 2) 
 	{
 	    	while (len--) 
 	    		serial_printc(*(buf++));
        		result = tf->edx;
 	} 
 	else 
 	{
 	    	//result = fs_write(fd, buf, len);
 	}
 	tf->eax = result;
}
void do_syscall(TrapFrame *tf) {
	switch(tf->eax) {
		/* The ``add_irq_handle'' system call is artificial. We use it to 
		 * let user program register its interrupt handlers. But this is 
		 * very dangerous in a real operating system. Therefore such a 
		 * system call never exists in GNU/Linux.
		 */
		case 0: 
			cli();
			add_irq_handle(tf->ebx, (void*)tf->ecx);
			sti();
			break;

		case SYS_brk: sys_brk(tf); break;
		case SYS_write: sys_write(tf); break;
		/* TODO: Add more system calls. */

		default: panic("Unhandled system call: id = %d", tf->eax);
	}
}

